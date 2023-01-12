#include "GenericIndex.h"
#include "IndexSet.h"

#include <string>
#include <vector>
#include <iostream>

int main()
{
	GenericIndex foo("foo", 0, 10);
	GenericIndex bar("bar", -4, 3);

	IndexSet biz;

	biz.AddIndex(foo);
	biz.AddIndex(bar);

	for(biz = biz.begin(); biz != biz.end(); ++biz)
	{
		for(auto itr = biz.indices.begin(); itr != biz.indices.end(); ++itr)
		{
			std::cout << itr->first << ":\t" << (itr->second).index << "\t\t";
		}
		std::cout << std::endl;
		++biz;
	}
	std::cout << "here" << std::endl;

	return 0;
}
