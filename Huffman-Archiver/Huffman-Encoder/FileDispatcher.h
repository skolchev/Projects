// A very basic Win32 based library for filesystem manipulation.
#ifndef FILE_DISPATCHER_H
#define FILE_DISPATCHER_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class FileDispatcher
{
public:
	/** Checks whether the given absolute or relative path is a valid directory.
	*/
	bool static IsDirectory(const string& directory);

	/** Checks whether the given absolute or relative path is a valid file.
	*/
	bool static IsFile(const string& file);
	/**
	* Checks whether the given absolute or relative path actually exists in the
	* filesystem.
	*/
	bool static IsValid(const string& file);

	/** Returns the names of all files and directories directly contained in a
	*  given directory specified by its absolute or relative path.
	*/
	vector<string> static TraverseDirectory(string& const basepath);

	/** Returns the names of all files and directories directly or indirectly
	* (recursively) contained in a given directory specified by it's absolute
	* or relative path. The names are stored in the output parameter:
	* files_and_directories and are included using an in-order traversal of
	* the filesystem.
	*/
	void static TraverseDirectoryRecursively(vector<string>& filepaths, string& const basepath);

	/** If path has base_path as it's prefix the prefix is removed along with any
	* leading forward or backward slashes. If path does not have base_path as
	* it's prefix then the value of path is returned.
	*/
	string static StripBasePath(const string& path, const string& base_path);

	/** Returns a new path string with the last component of the input path removed.
	* For example removing the last component from the path:
	*
	* D:\\foo\\bar
	*
	* Results in:
	*
	* D:\\foo\
	*/
	string static StripLastPathComponent(const string& path);

private:

};

#endif