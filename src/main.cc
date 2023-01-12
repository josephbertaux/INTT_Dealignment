#include "GenericIndex.h"
#include "IndexSet.h"

#include <string>
#include <vector>
#include <iostream>

int main()
{
	GenericIndex foo("foo", 7, 0, 10);
	GenericIndex bar("bar", 2, -4, 3);

	IndexSet biz;

	biz.AddIndex(foo);
	biz.AddIndex(bar);

	int safe = 0;
	int SAFE = 200;

	auto itr = biz.indices.begin();

	for(biz = biz.begin(); biz != biz.end(); ++biz)
	{
		for(itr = biz.indices.begin(); itr != biz.indices.end(); ++itr)
		{
			std::cout << itr->first << ": " << itr->second.index << " ";

			if(++safe >= SAFE)goto label;
		}
		std::cout << std::endl;
	}

	label:

	return 0;
}
