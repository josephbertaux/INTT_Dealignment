#ifndef GENERIC_INDEX_H
#define GENERIC_INDEX_H

#include <string>

class GenericIndex
{
protected:
public:
	int lower = 0;
	int index = 0;
	int upper = 0;

	std::string label;

public:
	GenericIndex(std::string, int, int, int);
	GenericIndex(const GenericIndex&);

	bool operator==(const GenericIndex&) const;
	bool operator!=(const GenericIndex&) const;

	GenericIndex& operator++();
	GenericIndex& operator--();

	const GenericIndex begin();
	const GenericIndex end();
};

#endif
