#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "foo/InttParameters.h"
#include "foo/AlignTransform.h"
#include "foo/LadderReader.h"
#include "foo/BarrelReader.h"

const std::string target_file = "/sphenix/u/jbertaux/Data/Repositories/INTT_Dealignment/dat/intt_align_transforms.txt";



int main()
{
	const int LAYER = 4;
	const std::array<uint, LAYER> LADDER = {12, 12, 16, 16};
	const int SENSOR = 4;

	unsigned int layer;
	unsigned int ladder;
	unsigned int sensor;

	unsigned long hitsetid;
	unsigned long layer_long;
	unsigned long ladder_long;
	unsigned long sensor_long;

	const unsigned int layer_bitshift = 16;
	const unsigned int ladder_bitshift = 10;
	const unsigned int sensor_bitshift = 14;
	char buff[128];
	std::string s;

	LadderReader lr;
	AlignTransform sensor_to_ladder;
	//The transform from the sensor's coordinate frame to the the ladder's coordinate frame
	// --OR, EQUIVALENTLY--
	//The align transformation that places the sensor, starting aligned with the ladder's frame,
	//to its actual position in the ladder frame

	BarrelReader br;
	AlignTransform ladder_to_barrel;
	//The transform from the ladder's coordinate frame to the the barrel's coordinate frame
	// --OR, EQUIVALENTLY--
	//The align transformation that places the ladder, starting aligned with the barrel's frame,
	//to its actual position in the barrel frame

	AlignTransform at;
	//An align transform to store the product of ladder_to_barrel * sensor_to_ladder
	//And call SetAnglesFromTransform after the multiplication

	std::ofstream file;
	file.open(target_file.c_str(), std::ofstream::out | std::ofstream::trunc);

	if(!file.good())
	{
		std::cout << "Could not open target output file:" << std::endl;
		std::cout << "\t" << target_file << std::endl;
		std::cout << "Exiting" << std::endl;

		return 1;
	}

	file << "hitsetid\talpha\t\tbeta\t\tgamma\t\tx\t\ty\t\tz" << std::endl;

	for(layer = 0; layer < LAYER; ++layer)
	{
		layer_long = layer;
		layer_long = layer_long << layer_bitshift;
		for(ladder = 0; ladder < LADDER[layer]; ++ladder)
		{
			ladder_long = ladder;
			ladder_long = ladder_long << ladder_bitshift;

			sprintf(buff, "B%1dL%03d.txt", layer / 2, (layer % 2) * 100 + ladder);
			std::cout << "\"" << buff << "\"" << std::endl;
			s = buff;
			lr.SetMarksFromFile(s);
			//ladder_to_barrel = br.GetNominalLadderToBarrel(layer, ladder);
			ladder_to_barrel = br.GetNominalTransformToWorld(layer, ladder);
			for(sensor = 0; sensor < SENSOR; ++sensor)
			{
				sensor_long = sensor;
				sensor_long = sensor_long << sensor_bitshift;

				hitsetid = layer_long + ladder_long + sensor_long;

				sensor_to_ladder = lr.GetActualSensorToLadder(sensor);
				at = ladder_to_barrel * sensor_to_ladder;
				at.SetAnglesFromTransform();
				sprintf
				(
					buff,
					"%lu\t%+15.10f\t%+15.10f\t%+15.10f\t%+15.10f\t%+15.10f\t%+15.10f",
					hitsetid, at.Ang(0), at.Ang(1), at.Ang(2), at.Pos(0), at.Pos(1), at.Pos(2)
				);

				file << buff << std::endl;
			}
		}
	}

	return 0;
}
