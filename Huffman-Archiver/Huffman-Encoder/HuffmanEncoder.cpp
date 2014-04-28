#include "HuffmanEncoder.h"

HuffmanEncoder::HuffmanEncoder(const std::map<char, unsigned int>& frequencies)
{
	this->frequencyTable = frequencies;
	this->huffmanHeap = new HuffmanBinaryHeap(this->frequencyTable.size());
}

HuffmanEncoder::~HuffmanEncoder()
{
	delete huffmanHeap;
}

void HuffmanEncoder::BuildTree()
{
	for (std::map<char, unsigned int>::iterator it = this->frequencyTable.begin();
		it != this->frequencyTable.end(); ++it)
	{
		this->huffmanHeap->Add(new HuffmanNode(it->second, it->first));
	}

	// Fixes bug if file consists of only one byte
	// or one byte repeated many times
	if (this->huffmanHeap->GetSize() == 1)
	{
		huffmanTable.insert(std::pair<char, std::string>(huffmanHeap->GetMin()->GetLetter(), std::string(1, (char)0)));
		return;
	}

	while (!huffmanHeap->IsEmpty())
	{
		if (huffmanHeap->GetSize() == 1) break;
		HuffmanNode* first = huffmanHeap->RemoveMin();
		HuffmanNode* second = huffmanHeap->RemoveMin();
		huffmanHeap->Add(new HuffmanNode(first, second));
	}

	// std::string code = "";
	// BuildTable(huffmanTree->GetMin(), code);
}

void HuffmanEncoder::BuildTable(HuffmanNode* root, std::string code)
{
		if (root->GetLeftChild() == NULL)
		{
			root->SetCode(code);
			huffmanTable.insert(std::pair<char, std::string>(root->GetLetter(), code));
			return;
		}
		else
		{
			BuildTable(root->GetLeftChild(), code + std::string(1, (char)0));
			BuildTable(root->GetRightChild(), code + std::string(1, (char)1));
		}
}

HuffmanNode* HuffmanEncoder::GetTree()
{
	return this->huffmanHeap->GetMin();
}

std::map<char, std::string> HuffmanEncoder::GetTable()
{
	return this->huffmanTable;
}