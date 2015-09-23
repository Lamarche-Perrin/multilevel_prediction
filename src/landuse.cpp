
#include <iostream>
#include <fstream>
#include <cmath>

#include "landuse.hpp"
#include "timer.hpp"
#include "csv_tools.hpp"
#include "markov_process.hpp"


void testLanduseModel ()
{
	double quality [2] = {1, 2};
	double breaks [2] = {1.5, 1.9};

	double gamma = 2./3;
	std::string suffix = "0.67";

	int time = -1;
	int delay = 1;
	
	int sizeMin = 1;
	int sizeMax = 50;
	int sizeStep = 1;

	bool saveFlow = true;
	bool saveDist = false;
	bool saveTrans = false;

	bool newData = true;
	bool verbose = false;
	bool logCalculus = true;

	std::string flowName = "../data/landuse/landuse_logflow_" + suffix + ".csv";
	//std::string flowName = "../data/temp.csv";
	std::string distName = "../data/landuse/landuse_dist_" + suffix + ".csv";
	std::string transName = "../data/landuse/landuse_trans_" + suffix + ".csv";
	char *timerName = (char*) "../data/landuse/timer.csv";

	std::ofstream flowFile;
	std::ofstream distFile;
	std::ofstream transFile;

	if (saveFlow && newData)
	{
		deleteCSV(flowName);
		openOutputCSV(flowFile,flowName);	
		addCSVField(flowFile,"SIZE");
		addCSVField(flowFile,"HY");
		addCSVField(flowFile,"IYpY");
		addCSVField(flowFile,"HYpY");
		addCSVField(flowFile,"HYpX");
		addCSVField(flowFile,"FLOW",false);
		endCSVLine(flowFile);
		closeOutputCSV(flowFile);

		std::cout << "SIZE     H(Y)     I(Y;Y')     H(Y'|Y)     H(Y'|X)     FLOW"  << std::endl;
	}

	if (saveDist && newData) { deleteCSV(distName); }
	if (saveTrans && newData) { deleteCSV(transName); }


	Timer timer (timerName);

	for (int s = sizeMin; s <= sizeMax; s += sizeStep)
	{
		
		timer.start(s,"LAND USE MODEL");
		timer.startTime();
		timer.startMemory();

		int agentNb = s;
		int size = pow(agentNb+1,2);

		double *logFact;
		double logGamma = log(gamma);
		double logNotGamma = log(1.-gamma);

		double *choose;
		double *gammaPow;
		double *notGammaPow;

		
		// Compute binomial coefficients

		if (logCalculus)
		{
			logFact = new double [agentNb+1];
			for (int n = 0; n <= agentNb; n++) { logFact[n] = lgamma(n+1.0); }
		}

		else {
			choose = new double [(agentNb+2)*(agentNb+1)/2];
			for (int n = 0; n <= agentNb; n++)
				choose[trindex(n,0)] = choose[trindex(n,n)] = 1;
			for (int n = 2; n <= agentNb; n++)
				for (int k = 1; k <= n/2; k++)
					choose[trindex(n,k)] = choose[trindex(n,n-k)] = choose[trindex(n-1,k-1)] + choose[trindex(n-1,k)];

			gammaPow = new double [agentNb+1];
			notGammaPow = new double [agentNb+1];
			gammaPow[0] = notGammaPow[0] = 1;
			for (int n = 1; n <= agentNb; n++)
			{
				gammaPow[n] = gammaPow[n-1] * gamma;
				notGammaPow[n] = notGammaPow[n-1] * (1. - gamma);
			}
		}

		
		
		MarkovProcess *MP = new MarkovProcess (size);

		double p = pow(0.5,agentNb);
		double logP = agentNb * log(0.5);
		
		for (int i = 0; i < size; i++)
		{
			int i01 = i % (agentNb+1);
			int i11 = (i-i01) / (agentNb+1);

			if (logCalculus) {
				double logProb0 = logFact[agentNb] - logFact[i01] - logFact[agentNb-i01] + logP;
				double logProb1 = logFact[agentNb] - logFact[i11] - logFact[agentNb-i11] + logP;
				MP->distribution[i] = exp(logProb0 + logProb1);
			}

			else {
				double prob0 = choose[trindex(agentNb,i01)] * p;
				double prob1 = choose[trindex(agentNb,i11)] * p;
				MP->distribution[i] = prob0 * prob1;
			}
		}	

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				MP->transition[j*size+i] = 0;

		for (int i = 0; i < size; i++)
		{
			if (size > 1000 && i % (size/100) == 0) { std::cout << (i*100/size) << "% " << std::flush; }

			int i01 = i % (agentNb+1);
			int i11 = (i-i01) / (agentNb+1);
			int i00 = agentNb - i01;
			int i10 = agentNb - i11;

			int q = i01 * quality[0] + i11 * quality[1];
			bool d0 = (q < breaks[0] * agentNb);
			bool d1 = (q < breaks[1] * agentNb);

			if (logCalculus)
			{
				for (int d00 = 0; d00 <= i00; d00++)
				{
					double logProb00 = logFact[i00] - logFact[d00] - logFact[i00-d00] + (d00) * logGamma + (i00-d00) * logNotGamma;

					for (int d01 = 0; d01 <= i01; d01++)
					{
						double logProb01 = logFact[i01] - logFact[d01] - logFact[i01-d01] + (d01) * logGamma + (i01-d01) * logNotGamma;

						for (int d10 = 0; d10 <= i10; d10++)
						{
							double logProb10 = logFact[i10] - logFact[d10] - logFact[i10-d10] + (d10) * logGamma + (i10-d10) * logNotGamma;

							for (int d11 = 0; d11 <= i11; d11++)
							{
								double logProb11 = logFact[i11] - logFact[d11] - logFact[i11-d11] + (d11) * logGamma + (i11-d11) * logNotGamma;

								int j01;
								if (d0) { j01 = i01 + d00; } else { j01 = i01 - d01; }

								int j11;
								if (d1) { j11 = i11 + d10; } else { j11 = i11 - d11; }

								int j = j11 * (agentNb+1) + j01;
								MP->transition[j*size+i] += exp(logProb00 + logProb01 + logProb10 + logProb11);
							}
						}
					}
				}
			}
			
			else {
				for (int d00 = 0; d00 <= i00; d00++)
				{
					double prob00 = choose[trindex(i00,d00)] * gammaPow[d00] * notGammaPow[i00-d00];

					for (int d01 = 0; d01 <= i01; d01++)
					{
						double prob01 = choose[trindex(i01,d01)] * gammaPow[d01] * notGammaPow[i01-d01];

						for (int d10 = 0; d10 <= i10; d10++) {
							double prob10 = choose[trindex(i10,d10)] * gammaPow[d10] * notGammaPow[i10-d10];

							for (int d11 = 0; d11 <= i11; d11++)
							{
								double prob11 = choose[trindex(i11,d11)] * gammaPow[d11] * notGammaPow[i11-d11];

								int j01;
								if (d0) { j01 = i01 + d00; } else { j01 = i01 - d01; }

								int j11;
								if (d1) { j11 = i11 + d10; } else { j11 = i11 - d11; }

								int j = j11 * (agentNb+1) + j01;
								MP->transition[j*size+i] += prob00 * prob01 * prob10 * prob11;
							}
						}
					}
				}
			}
		}
		if (size > 1000) { std::cout << std::endl; }
		
		Partition *partition = new Partition();

		int partNb = agentNb * (quality[0] + quality[1]) + 1;
		Part **parts = new Part*[partNb];
		for (int p = 0; p < partNb; p++)
		{
			parts[p] = new Part();
			partition->addPart(parts[p]);
		}
	
		
		for (int i = 0; i < size; i++)
		{
			int i01 = i % (agentNb+1);
			int i11 = (i-i01) / (agentNb+1);
			int qi = i01 * quality[0] + i11 * quality[1];
			parts[qi]->addIndividual(i);
		}

		timer.step("BUILDING TRANSITION MATRIX");
		
		if (saveFlow || saveDist)
		{
			MP->computeStationaryDistribution(0.00001);
			timer.step("COMPUTING STATIONARY DISTRIBUTION");
		}

		if (verbose)
		{
			MP->print();
			partition->print(true);
		}
		
		std::cout << agentNb;

		if (saveFlow)
		{
			double H = MP->getEntropy(partition,time);
			double I = MP->getMutualInformation(partition,partition,delay,time);
			double H1 = MP->getNextEntropy(partition,false,delay,time);
			double H2 = MP->getNextEntropy(partition,true,delay,time);
			double F = H1-H2;

			std::cout << "     " << H << "     " << I << "     " << H1 << "     " << H2 << "     " << F;

			openOutputCSV(flowFile,flowName);
			addCSVField(flowFile,agentNb);
			addCSVField(flowFile,H);
			addCSVField(flowFile,I);
			addCSVField(flowFile,H1);
			addCSVField(flowFile,H2);
			addCSVField(flowFile,F,false);
			endCSVLine(flowFile);
			closeOutputCSV(flowFile);
		}

		if (saveDist)
		{
			openOutputCSV(distFile,distName);

			addCSVField(distFile,agentNb);
			addCSVField(distFile,"UNIFORM");
			std::string str = "";
			for (int i = 0; i < size; i++) { if (i>0) { str += ";"; } str += double2string(MP->distribution[i]); }
			addCSVField(distFile,str,false);
			endCSVLine(distFile);

			addCSVField(distFile,agentNb);
			addCSVField(distFile,"STATIONARY");
			str = "";
			for (int i = 0; i < size; i++) { if (i>0) { str += ";"; } str += double2string(MP->distributions->at(MP->lastTime)[i]); }
			addCSVField(distFile,str,false);
			endCSVLine(distFile);

			closeOutputCSV(distFile);
		}

		if (saveTrans)
		{
			double *expectedTrans = new double [2*size];

			for (int i = 0; i < size; i++)
			{
				double e01 = 0;
				double e11 = 0;

				for (int j = 0; j < size; j++)
				{
					int j01 = j % (agentNb+1);
					int j11 = (j-j01) / (agentNb+1);

					double prob = MP->transition[j*size+i];
					e01 += prob*j01;
					e11 += prob*j11;
				}
				expectedTrans[i*2] = e01;
				expectedTrans[i*2+1] = e11;
			}
			
			openOutputCSV(transFile,transName);

			addCSVField(transFile,agentNb);
			std::string str = "";
			for (int i = 0; i < 2*size; i++) { if (i>0) { str += ";"; } str += double2string(expectedTrans[i],16); }
			addCSVField(transFile,str,false);
			endCSVLine(transFile);

			closeOutputCSV(transFile);

			delete [] expectedTrans;
		}

		std::cout << std::endl;

		if (saveFlow) { timer.step("COMPUTING INFORMATION FLOW"); }

		delete partition;
		delete MP;

		if (logCalculus) { delete [] logFact; }
		else {
			delete [] choose;
			delete [] gammaPow;
			delete [] notGammaPow;			
		}

		timer.stopTime();
		timer.stopMemory();
		timer.stop();
	}

	
}


int trindex (int n, int k) { return n*(n+1)/2+k; }

/*
long unsigned int smart_nChoosek (int n, int k)
{
	std::cout << n << "     " << k << std::endl;
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;
	
    long unsigned int result = n;
    for( int i = 2; i <= k; ++i ) {
		result *= (n-i+1);
		result /= i;
    }
    return result;
}
*/
