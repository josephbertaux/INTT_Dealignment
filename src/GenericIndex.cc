#include "GenericIndex.h"

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

bool GenericIndex::operator==(const GenericIndex& b)
{
	if(label != b.label)return false;

	if(index != b.index)return false;
	if(lower != b.lower)return false;
	if(upper != b.upper)return false;

	return true;
}

bool GenericIndex::operator<(const GenericIndex& b)
{
	return index < b.index;
}

bool GenericIndex::operator>(const GenericIndex& b)
{
	return index > b.index;
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
