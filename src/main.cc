#include "index/IndexSetWrapper.h"
#include "align/AlignTransform.h"
#include "dtctr/InttSensorSurveyReader.h"

#include <string>
#include <vector>
#include <iostream>

#include "TH1D.h"
#include "TTree.h"
#include "TFile.h"

int main()
{
	std::string sensor_survey_dir = "/sphenix/u/jbertaux/Data/Repositories/INTT_Dealignment/dat/sensor_survey_data/";
	std::string sensor_survey_file = "/sphenix/u/jbertaux/Data/Repositories/INTT_Dealignment/dat/sensor_survey.root";

	std::string sensor_hist_name = "sensor_hist";
	std::string pixel_hist_name = "pixel_hist";

	int sensor_bins = 20;
	int pixel_bins = 120;
	double bin_min = 0.0;
	double bin_max = 0.6;

	int layer = 0;
	int ladder = 0;
	int sensor = 0;
	int strip_z = 0;
	int strip_x = 0;

	double c = 0.0;
	double d = 0.0;

	char buff[16] = {"\0"};
	std::string s = "";

	AlignTransform t;	//nominal
	AlignTransform u;	//actual

	TVector3 a;
	TVector3 b;

	InttSensorSurveyReader sensor_reader;

	TFile* file = nullptr;
	TH1D* sensor_hist = nullptr;
	TH1D* pixel_hist = nullptr;

	file = TFile::Open(sensor_survey_file.c_str(), "RECREATE");
	if(!file)
	{
		std::cout << "Couldn't get file:" << std::endl;
		std::cout << "\t" << sensor_survey_file << std::endl;

		return 1;
	}
	file->cd();

	sensor_hist = new TH1D(sensor_hist_name.c_str(), "Distribution of Worst-Case Nominal-Actual Distances over INTT Sensors", sensor_bins, bin_min, bin_max);
	pixel_hist = new TH1D(pixel_hist_name.c_str(), "Distribution of Strip Nominal-Actual Distances over INTT Sensors", pixel_bins, bin_min, bin_max);
	sensor_hist->GetXaxis()->SetTitle("Strip distance from nominal (cm)");
	pixel_hist->GetXaxis()->SetTitle("Strip distance from nominal (cm)");

	for(layer = 0; layer < INTT::LAYER; ++layer)
	{
		for(ladder = 0; ladder < INTT::LADDER[layer]; ++ladder)
		{
			sprintf(buff, "B%iL%03i.txt", layer / 2, (layer % 2) * 100 + ladder);
			s = sensor_survey_dir + buff;
			std::cout << buff << std::endl;

			if(sensor_reader.ReadSurveyFile(s))continue;

			for(sensor = 0; sensor < INTT::SENSOR; ++sensor)
			{
				if(sensor_reader.SetMarks(sensor))continue;

				d = 0.0;
				for(strip_x = 0; strip_x < INTT::STRIP_X; ++strip_x)
				{
					for(strip_z = 0; strip_z < INTT::STRIP_Z[sensor]; ++strip_z)
					{
						if(sensor_reader.GetNominalPixelToLadder(sensor, strip_x, strip_z, t))continue;
						if(sensor_reader.GetActualPixelToLadder(sensor, strip_x, strip_z, u))continue;

						a[0] = t.Pos(0);
						a[1] = 0.0;//t.Pos(1);
						a[2] = t.Pos(2);

						b[0] = u.Pos(0);
						b[1] = 0.0;//u.Pos(1);
						b[2] = u.Pos(2);

						a = a - b;
						c = a.Mag();

						pixel_hist->Fill(c);
						if(c > d)d = c;
					}
				}
				std::cout << "\t\t" << sensor << ":\t" << d << "\t (cm)" << std::endl;
				sensor_hist->Fill(d);
				sensor_reader.GetWorstCross(d);
				std::cout << "\tworst cross:\t" << d << "\t (cm)" << std::endl;
			}
			std::cout << std::endl;
		}
	}

	if(sensor_hist)
	{
		sensor_hist->Write();
		delete sensor_hist;
	}
	if(pixel_hist)
	{
		pixel_hist->Write();
		delete pixel_hist;
	}

	if(file)file->Write();
	if(file)file->Close();

	return 0;
}
