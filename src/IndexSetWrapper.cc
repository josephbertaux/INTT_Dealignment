#include "IndexSetWrapper.h"

template <typename T>
IndexSetWrapper<T>::IndexSetWrapper(IndexSet s)
{
	wrapper.clear();
	index_set = s;

	for(index_set = index_set.begin(); index_set != index_set.end(); ++index_set)
	{
		wrapper.insert({index_set, T()});
	}
}

template <typename T>
IndexSetWrapper<T>& IndexSetWrapper<T>::operator++()
{
	++index_set;

	return *this;
}

template <typename T>
IndexSetWrapper<T>& IndexSetWrapper<T>::operator--()
{
	--index_set;

	return *this;
}

template <typename T>
int IndexSetWrapper<T>::Get(T& t)
{
	auto itr = wrapper.find(index_set);
	if(itr == wrapper.end())return 1;

	t = itr->second;

	return 0;
}

template <typename T>
int IndexSetWrapper<T>::Set(T t)
{
	auto itr = wrapper.find(index_set);
	if(itr == wrapper.end())return 1;

	itr->second = t;

	return 0;
}

template class IndexSetWrapper<std::string>;
