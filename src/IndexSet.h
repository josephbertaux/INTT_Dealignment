#ifndef INDEX_SET_H
#define INDEX_SET_H

#include "GenericIndex.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

class IndexSet
{
protected:
public:
	std::map<std::string, GenericIndex> indices;

public:
	bool operator==(const IndexSet&);
	bool operator!=(const IndexSet& b){return !operator==(b);}

	bool operator<(const IndexSet&);
	bool operator>(const IndexSet&);
	bool operator<=(const IndexSet& b){return !operator>(b);}
	bool operator>=(const IndexSet& b){return !operator<(b);}

	IndexSet& operator++(); 
	IndexSet& operator--(); 

	const IndexSet begin();
	const IndexSet end();

	void AddIndex(GenericIndex);

	int GetIndex(std::string, int&);
	int SetIndex(std::string, int);
};

#endif
