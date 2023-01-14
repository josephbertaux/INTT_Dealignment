#include "index/IndexSetWrapper.h"
#include "align/AlignTransform.h"

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

//	for(biz = biz.begin(); biz != biz.end(); ++biz)
//	{
//		for(auto itr = biz.indices.begin(); itr != biz.indices.end(); ++itr)
//		{
//			std::cout << itr->first << ":\t" << (itr->second).index << "\t\t";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << "here" << std::endl;

	int i;
	std::string s;
	IndexSetWrapper<std::string> bax(biz);

	bax.GotoBegin();
	while(!bax.AtEnd())
	{
		s = "";
		s += "foo: ";
		bax.GetIndex("foo", i);
		s += std::to_string(i);
		s += "\t";
		s += "bar: ";
		bax.GetIndex("bar", i);
		s += std::to_string(i);

		std::cout << s << std::endl;
		bax.Set(s);
		
		++bax;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	bax.SetIndex("foo", 2);
	bax.SetIndex("bar", 1);

	bax.Get(s);

	std::cout << s << std::endl;

	AlignTransform t;
	t.Ang(0) = 0.3;
	t.Ang(1) = -0.12;
	t.Ang(2) = 0.456;

	t.Pos(0) = 325.425;
	t.Pos(1) = -14254.542;
	t.Pos(2) = 53245.32452;

	t.SetTransformFromAngles();

	std::cout << "\t" << "t" << "\t" << std::endl;
	t.Print();

	AlignTransform u = t.Inverse();
	
	std::cout << "\t" << "u" << "\t" << std::endl;
	u.Print();

	u = u * t;
	std::cout << "\t" << "i" << "\t" << std::endl;
	u.Print();

	u.SetAnglesFromTransform();
	std::cout << u.Ang(0) << std::endl;
	std::cout << u.Ang(1) << std::endl;
	std::cout << u.Ang(2) << std::endl;

	return 0;
}
