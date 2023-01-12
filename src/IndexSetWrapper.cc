#include "IndexSetWrapper.h"

template<typename T>
IndexSetWrapper<T>::IndexSetWrapper(IndexSet s)
{
	wrapper.clear();
	index_set = s;

	for(index_set = index_set.begin(); index_set != index_set.end(); ++index_set)
	{
		wrapper.insert({index_set, T()});
	}
}
