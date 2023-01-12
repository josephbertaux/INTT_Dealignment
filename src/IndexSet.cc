#include "IndexSet.h"

bool operator==(const IndexSet& a, const IndexSet& b)
{
	auto a_itr = a.indices.begin();
	auto b_itr = b.indices.begin();

	for(a_itr = a.indices.begin(); a_itr != a.indices.end(); ++a_itr)
	{
		b_itr = b.indices.find(a_itr->first);

		if(b_itr == b.indices.end())return false;

		if(a_itr->second != b_itr->second)return false;
	}

	for(b_itr = b.indices.begin(); b_itr != b.indices.end(); ++b_itr)
	{
		a_itr = a.indices.find(b_itr->first);

		if(a_itr == a.indices.end())return false;

		if(a_itr->second != b_itr->second)return false;
	}

	return true;
}

bool operator!=(const IndexSet& a, const IndexSet& b)
{
	auto a_itr = a.indices.begin();
	auto b_itr = b.indices.begin();

	for(a_itr = a.indices.begin(); a_itr != a.indices.end(); ++a_itr)
	{
		b_itr = b.indices.find(a_itr->first);

		if(b_itr == b.indices.end())return true;

		if(a_itr->second != b_itr->second)return true;
	}

	for(b_itr = b.indices.begin(); b_itr != b.indices.end(); ++b_itr)
	{
		a_itr = a.indices.find(b_itr->first);

		if(a_itr == a.indices.end())return true;

		if(a_itr->second != b_itr->second)return true;
	}

	return false;
}

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

bool IndexSet::operator!=(const IndexSet& b)
{
	auto itr = indices.begin();
	auto b_itr = b.indices.begin();

	for(itr = indices.begin(); itr != indices.end(); ++itr)
	{
		b_itr = b.indices.find(itr->first);

		if(b_itr == b.indices.end())return true;

		if(itr->second != b_itr->second)return true;
	}

	for(b_itr = b.indices.begin(); b_itr != b.indices.end(); ++b_itr)
	{
		itr = indices.find(b_itr->first);

		if(itr == indices.end())return true;

		if(itr->second != b_itr->second)return true;
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
	if(itr == indices.end())return 0;

	i = itr->second.index;

	return 1;
}

int IndexSet::SetIndex(std::string s, int i)
{
	auto itr = indices.find(s);
	if(itr == indices.end())return 0;

	itr->second.index = i;

	return 1;
}
