#include "GenericGeoWrapper.h"

GenericGeoWrapper::GenericGeoWrapper()
{
	//Do nothing
}

GenericGeoWrapper::~GenericGeoWrapper()
{
	//Delete the elements of our wrapper's map
}

void GenericGeoWrapper::MakeIndices()
{
	//Do nothing; the subsystem should overwrite this
}

AlignTransform GenericGeoWrapper::MakeNominalTransform()
{
	//Do nothing; the subsystem should overwrite this
	//note the the align transform should depend on the current value of member "indices"

	return AlignTransform();
}
