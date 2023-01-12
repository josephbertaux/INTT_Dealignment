#include "GenericIndex.h"

bool operator==(const GenericIndex& a, const GenericIndex& b)
{
	if(a.label != b.label)return false;

	if(a.index != b.index)return false;
	if(a.lower != b.lower)return false;
	if(a.upper != b.upper)return false;

	return true;
}

bool operator!=(const GenericIndex& a, const GenericIndex& b)
{
	if(a.label != b.label)return true;

	if(a.index != b.index)return true;
	if(a.lower != b.lower)return true;
	if(a.upper != b.upper)return true;

	return false;
}

GenericIndex::GenericIndex(std::string s, int i, int l, int u)
{
	label = s;

	index = i;
	lower = l;
	upper = u;
}

GenericIndex::GenericIndex(const GenericIndex& b)
{
	label = b.label;

	index = b.index;
	lower = b.lower;
	upper = b.upper;
}

bool GenericIndex::operator==(const GenericIndex& b) const
{
	if(label != b.label)return false;

	if(index != b.index)return false;
	if(lower != b.lower)return false;
	if(upper != b.upper)return false;

	return true;
}

bool GenericIndex::operator!=(const GenericIndex& b) const
{
	if(label != b.label)return true;

	if(index != b.index)return true;
	if(lower != b.lower)return true;
	if(upper != b.upper)return true;

	return false;
}

GenericIndex& GenericIndex::operator++()
{
	++index;

	return *this;
}

GenericIndex& GenericIndex::operator--()
{
	--index;

	return *this;
}

const GenericIndex GenericIndex::begin()
{
	GenericIndex b(this->label, this->lower, this->lower, this->upper);
	return b;
}

const GenericIndex GenericIndex::end()
{
	GenericIndex b(this->label, this->upper, this->lower, this->upper);
	return b;
}
