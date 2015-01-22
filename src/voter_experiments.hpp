#ifndef INCLUDE_VOTER_EXPERIMENTS
#define INCLUDE_VOTER_EXPERIMENTS

#include <fstream>

#include "csv_tools.hpp"
#include "partition.hpp"
#include "voter_graph.hpp"
#include "markov_process.hpp"

class VoterExperiment;
typedef std::set<VoterExperiment*> ExperimentSet;

const int M_MICRO				= 0;
const int M_AGENT1				= 1;
const int M_AGENT1_MESO1		= 2;
const int M_AGENT1_MESO2		= 3;
const int M_AGENT1_MACRO		= 4;
const int M_AGENT1_MESO1_MESO2	= 5;
const int M_MESO1				= 6;
const int M_MESO1_MESO2			= 7;
const int M_MESO2				= 8;
const int M_MACRO				= 9;
const int M_EMPTY				= 10;
const int M_ALLSIZES1			= 11;

void voterExperiment (std::set<VoterExperiment*> *expSet);

void addMeasurement (int measurement, MeasurementSet *set, VoterGraph *VG);

void addHeaderToCSV (std::string fileName);

void addLineToCSV (std::ofstream &csvFile, MarkovProcess *MP, std::string type, int update,
	int size1, int size2, double intraR1, double intraR2, double interR1, double interR2, double contrarian,
	VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay, Partition *microP);


class VoterExperiment
{
	public:
		int id;
		static int id_number;
		
		int update;
		double threshold;
		bool compactModel;
		
		int size1Min;	int size1Max;	int size1Step;
		int size2Min;	int size2Max;	int size2Step;
		bool equalSize;
	
		double intraR1Min;	double intraR1Max;	double intraR1Step;
		double intraR2Min;	double intraR2Max;	double intraR2Step;
		double interR1Min;	double interR1Max;	double interR1Step;
		double interR2Min;	double interR2Max;	double interR2Step;
		bool equalIntraRate;
		bool equalInterRate;
		bool oppositeInterRate;
	
		double contrarianMin; double contrarianMax; double contrarianStep;
	
		int timeMin;	int timeMax;	int timeStep;
		int delayMin;	int delayMax;	int delayStep;
		
		std::set<int> *preMeasurements;
		std::set<int> *postMeasurements;
				
		VoterExperiment (int size1, int size2, double intraR1, double intraR2, double interR1, double interR2,
			double contrarian, double time, double delay, std::set<int> *preMeasurements, std::set<int> *postMeasurements);
		~VoterExperiment ();

};

#endif
