
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "coconut.hpp"
#include "markov_process.hpp"
#include "main.hpp"

enum Distribution {MICRO_UNIFORM, MACRO_UNIFORM, ALL_ZERO, ALL_ONE};

void testCoconutModel ()
{

	std::cout << "LINE     SIZE     H(Y)     I(Y;Y')     H(Y'|Y)     H(Y'|X)     FLOW"  << std::endl;

	// PARAMETERS
	bool verbose = false;
	double treeRate = 0.8;

	int minAgentNb = 10;
	int maxAgentNb = 10;
	int stepAgentNb = 1;
	
	double minCost = 0;
	double maxCost = 1;

	double homogeneousStrategy = 0.8;

	bool readStrategyFromFile = true;
	std::string strategyFileName = "../data/coconut/CCind.csv";
	std::string flowName = "../data/coconut/coconut_flow.csv";

	int lineStep = 1000;

	Distribution initialDistribution = MICRO_UNIFORM;

	for (int agentNb = minAgentNb; agentNb <= maxAgentNb; agentNb += stepAgentNb)
	{
		int lineNum = 0;
		bool pursue = true;
		std::ifstream strategyFile;
		std::ofstream flowFile;
		CSVLine line;
		
		if (readStrategyFromFile) {
			openInputCSV(strategyFile,strategyFileName);
			pursue = hasCSVLine(strategyFile);

			deleteCSV(flowName);
			openOutputCSV(flowFile,flowName);	
			addCSVField(flowFile,"LINE");
			addCSVField(flowFile,"SIZE");
			addCSVField(flowFile,"HY");
			addCSVField(flowFile,"IYpY");
			addCSVField(flowFile,"HYpY");
			addCSVField(flowFile,"HYpX");
			addCSVField(flowFile,"FLOW",false);
			endCSVLine(flowFile);
			closeOutputCSV(flowFile);
		}

		while (pursue) {
			
			double *strategy = new double [agentNb];

			if (readStrategyFromFile) {
				getCSVLine (strategyFile, line, agentNb);
				for (int n = 0; n < agentNb; n++) { strategy[n] = string2double(line[n]); }
			}

			else {
				for (int n = 0; n < agentNb; n++) { strategy[n] = homogeneousStrategy; }
			}

			// CREATING MARKOV PROCESS
			int time = 0; int delay = 1;
			unsigned long int size = 1 << agentNb;
			MarkovProcess *MP = new MarkovProcess (size);

			// COMPUTING MICRO-UNIFORM DISTRIBUTION
			switch (initialDistribution)
			{
			case MICRO_UNIFORM :
				for (unsigned long int i = 0; i < size; i++)
					MP->distribution[i] = pow(2,-agentNb);
				break;

			case MACRO_UNIFORM :
				for (unsigned long int i = 0; i < size; i++)
				{
					int q = 0;
					unsigned long int j = i;
					while (j > 0) { q += j%2; j = j >> 1; }

					MP->distribution[i] = 1. / ((agentNb + 1) * nChoosek(agentNb,q));
				}
				break;

			case ALL_ZERO :
				MP->distribution[0] = 1;
				for (unsigned long int i = 1; i < size; i++)
					MP->distribution[i] = 0;
				break;

			case ALL_ONE :
				MP->distribution[size-1] = 1;
				for (unsigned long int i = 0; i < size-1; i++)
					MP->distribution[i] = 0;
				break;
			}

			// COMPUTING TRANSITION MATRIX
			for (unsigned long int i = 0; i < size; i++)
				for (unsigned long int j = 0; j < size; j++)
					MP->transition[j*size+i] = 0.;

			double meetingRate = 1. / (agentNb * (agentNb - 1));
			double *climbingRate = new double [agentNb];
			for (int n = 0; n < agentNb; n++)
				climbingRate[n] = (treeRate * (strategy[n] - minCost)) / (agentNb * (maxCost - minCost));
		
			for (unsigned long int i = 0; i < size; i++)
			{
				double remainingProb = 1.;

				for (int n1 = 0; n1 < agentNb; n1++)
				{
					int s1 = (i >> n1) % 2;
					if (s1 == 0)
					{
						unsigned long int j = i + (1 << n1);
						MP->transition[j*size+i] = climbingRate[n1];
						remainingProb -= climbingRate[n1];
					}

					else {
						for (int n2 = 0; n2 < agentNb; n2++) {
							if (n2 == n1) continue;

							int s2 = (i >> n2) % 2;
							if (s2 == 0) continue;

							unsigned long int j = i - (1 << n1) - (1 << n2);
							MP->transition[j*size+i] += meetingRate;
							remainingProb -= meetingRate;
						}
					}
				}
		
				MP->transition[i*size+i] = remainingProb;
			}

			// COMPUTING MACRO-PARTITION
			Partition *partition = new Partition();

			int partNb = agentNb + 1;
			Part **parts = new Part*[partNb];
			for (int p = 0; p < partNb; p++)
			{
				parts[p] = new Part();
				partition->addPart(parts[p]);
			}

			for (unsigned long int i = 0; i < size; i++)
			{
				int q = 0;
				unsigned long int j = i;
				while (j > 0) { q += j%2; j = j >> 1; }
				parts[q]->addIndividual(i);
			}

			// COMPUTING INFORMATION FLOWS
			double H = MP->getEntropy(partition,time);
			double I = MP->getMutualInformation(partition,partition,delay,time);
			double H1 = MP->getNextEntropy(partition,false,delay,time);
			double H2 = MP->getNextEntropy(partition,true,delay,time);
			double F = H1-H2;
	
			// PRINTING RESULTS
			if (verbose)
			{
				MP->print();
				partition->print(true);
				std::cout << std::endl;
			}

			std::cout << lineNum << "     " << agentNb << "     " << H << "     " << I << "     " << H1 << "     " << H2 << "     " << F << std::endl;

			if (readStrategyFromFile)
			{
				openOutputCSV(flowFile,flowName);
				addCSVField(flowFile,lineNum);
				addCSVField(flowFile,agentNb);
				addCSVField(flowFile,H);
				addCSVField(flowFile,I);
				addCSVField(flowFile,H1);
				addCSVField(flowFile,H2);
				addCSVField(flowFile,F,false);
				endCSVLine(flowFile);
				closeOutputCSV(flowFile);
			}
			
			// FREE MEMORY
			delete MP;
			delete climbingRate;
			delete strategy;
			
			if (readStrategyFromFile) {
				int n = lineStep;
				while (pursue && n > 0) { pursue = hasCSVLine(strategyFile); getCSVLine(strategyFile,line,agentNb); n--; lineNum++; }
			} else { pursue = false; lineNum++; }
		}

		if (readStrategyFromFile) { closeInputCSV(strategyFile); }
	}
}
