#ifndef GENERIC_GEO_WRAPPER_H
#define GENERIC_GEO_WRAPPER_H

#include "../align/AlignTransform.h"
#include "../index/IndexSetWrapper.h"

class GenericGeoWrapper
{
protected:
	IndexSet indices;
	IndexSetWrapper<std::pair<AlignTransform*, AlignTransform*>> transforms;

public:
	GenericGeoWrapper();
	~GenericGeoWrapper();

	virtual void MakeIndices();
	virtual AlignTransform MakeNominalTransform();

	//This is a Wrapper for its protected IndexSetWrapper
	//GenericGeoWrapper& operator++();
	//AlignTransform& GetNominalLocal
	//AlignTransform& GetActualLocal
};

#endif
