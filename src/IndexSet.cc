#include "IndexSet.h"

bool IndexSet::operator==(const IndexSet& b)
{
	auto itr = indices.begin();
	auto b_itr = b.indices.begin();

	for(itr = indices.begin(); itr != indices.end(); ++itr)
	{
		b_itr = b.indices.find(itr->first);

		if(b_itr == b.indices.end())return false;

		if(itr->second != b_itr->second)return false;
	}

	for(b_itr = b.indices.begin(); b_itr != b.indices.end(); ++b_itr)
	{
		itr = indices.find(b_itr->first);

		if(itr == indices.end())return false;

		if(itr->second != b_itr->second)return false;
	}

	return true;
}

bool IndexSet::operator<(const IndexSet& b)
{
	if(indices.size() < b.indices.size())return true;
	if(indices.size() > b.indices.size())return false;

	auto itr = indices.begin();
	auto b_itr = b.indices.begin();

	while(true)
	{
		if(itr->second < b_itr->second)return true;
		if(itr->second > b_itr->second)return false;

		++itr;
		++b_itr;

		if(itr == indices.end())break;
		if(b_itr == indices.end())break;
	}

	return false;
}

bool IndexSet::operator>(const IndexSet& b)
{
	if(indices.size() < b.indices.size())return false;
	if(indices.size() > b.indices.size())return true;

	auto itr = indices.begin();
	auto b_itr = b.indices.begin();

	while(true)
	{
		if(itr->second < b_itr->second)return false;
		if(itr->second > b_itr->second)return true;

		++itr;
		++b_itr;

		if(itr == indices.end())break;
		if(b_itr == indices.end())break;
	}

	return false;
}

IndexSet& IndexSet::operator++()
{
	bool carry = false;
	auto itr = indices.begin();

	for(itr = indices.begin(); itr != indices.end(); ++itr)
	{
		++(itr->second);
		carry = itr->second.index == itr->second.upper;

		if(carry)itr->second.index = itr->second.lower;
		else break;
	}

	if(carry)
	{
		for(itr = indices.begin(); itr != indices.end(); ++itr)itr->second.index = itr->second.upper;
	}

	return *this;
}

IndexSet& IndexSet::operator--()
{
	bool carry = false;
	auto itr = indices.begin();

	for(itr = indices.begin(); itr != indices.end(); ++itr)
	{
		--(itr->second);
		carry = itr->second.index == itr->second.lower - 1;

		if(carry)itr->second.index = itr->second.upper - 1;
		else break;
	}

	if(carry)
	{
		for(itr = indices.begin(); itr != indices.end(); ++itr)itr->second.index = itr->second.upper;
	}

	return *this;
}

const IndexSet IndexSet::begin()
{
	IndexSet b = *this;
	for(auto itr = b.indices.begin(); itr != b.indices.end(); ++itr)itr->second.index = itr->second.lower;

	return b;
}

const IndexSet IndexSet::end()
{
	IndexSet b = *this;
	for(auto itr = b.indices.begin(); itr != b.indices.end(); ++itr)itr->second.index = itr->second.upper;

	return b;
}

void IndexSet::AddIndex(GenericIndex i)
{
	indices.insert({i.label, i});
}

int IndexSet::GetIndex(std::string s, int& i)
{
	auto itr = indices.find(s);
	if(itr == indices.end())return 1;

	i = itr->second.index;

	return 0;
}

int IndexSet::SetIndex(std::string s, int i)
{
	auto itr = indices.find(s);
	if(itr == indices.end())return 1;

	itr->second.index = i;

	return 0;
}
