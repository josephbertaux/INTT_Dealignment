#ifndef INDEX_SET_WRAPPER_H
#define INDEX_SET_WRAPPER_H

#include <string>
#include <vector>
#include <map>

#include "IndexSet.h"

template <typename T>
class IndexSetWrapper
{
protected:
	IndexSet index_set;
	std::map<IndexSet, T> wrapper;

public:
	IndexSetWrapper(IndexSet);

	IndexSetWrapper& operator++();
	IndexSetWrapper& operator--();

	int Get(T& t);
	int Set(T t);
};

#endif
