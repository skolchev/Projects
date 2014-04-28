#include "FileDispatcher.h"

bool FileDispatcher::IsDirectory(const string& directory)
{
	DWORD attribute = GetFileAttributesA(directory.c_str());
	return attribute & FILE_ATTRIBUTE_DIRECTORY;
}

bool FileDispatcher::IsFile(const string& file)
{
	DWORD attribute = GetFileAttributesA(file.c_str());
	return !(attribute & FILE_ATTRIBUTE_DIRECTORY);
}

bool FileDispatcher::IsValid(const string& file)
{
	DWORD attributes = GetFileAttributesA(file.c_str());
	return attributes != INVALID_FILE_ATTRIBUTES;
}

vector<string> FileDispatcher::TraverseDirectory(string& const basepath)
{
	vector<string> files_and_directories;

	string path = basepath + "\\*";
	WIN32_FIND_DATAA find_data;
	HANDLE find_data_handle = FindFirstFileA(path.c_str(), &find_data);

	if (find_data_handle == INVALID_HANDLE_VALUE) {
		return files_and_directories;
	}

	while (true) {
		if (string(find_data.cFileName) != "." &&
			string(find_data.cFileName) != "..") {
			files_and_directories.push_back(find_data.cFileName);
		}
		if (!FindNextFileA(find_data_handle, &find_data)) break;
	}
	FindClose(find_data_handle);
	return files_and_directories;

}

void FileDispatcher::TraverseDirectoryRecursively(vector<string>& filepaths, string& const basepath)
{
	filepaths.push_back(basepath);
	if (IsDirectory(basepath)) {
		vector<string> files_and_directories_flat =
			TraverseDirectory(basepath);
		for (int i = 0; i < files_and_directories_flat.size(); i++) {
			string name = files_and_directories_flat[i];
			TraverseDirectoryRecursively(filepaths,
				basepath + "\\" + name);
		}
	}
}

string FileDispatcher::StripBasePath(const string& path, const string& base_path) {
	if (base_path == path.substr(0, base_path.size())) {
		string new_path = path.substr(base_path.size());
		while (new_path.size() > 0 && (new_path[0] == '\\' || new_path[0] == '/')) {
			new_path.erase(new_path.begin());
		}
		return new_path;
	}
	else {
		return path;
	}
}

string FileDispatcher::StripLastPathComponent(const string& path) {
	string result = path;
	int n = result.size();
	// Remove trailing forward and backward slashes.
	while (n > 0 && (result[n - 1] == '/' || result[n - 1] == '\\')) {
		n--;
		result.erase(result.begin() + n);
	}
	// Remove everything until a forward or backward slash.
	while (n > 0 && result[n - 1] != '/' && result[n - 1] != '\\') {
		n--;
		result.erase(result.begin() + n);
	}
	return result;
}