
//#include <math.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>

#include "markov_process.hpp"


MarkovProcess::MarkovProcess (int s)
{
	size = s;

	distribution = new double [size];
	distributions = new std::vector<double*>(1);
	distributions->at(0) = distribution;
	lastTime = 0;

	transition = new double [size*size];
	transitions = new std::vector<double*>(2);
	transitions->at(1) = transition;
	lastDelay = 1;
	
	double *trivialTransition = new double [size*size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (i == j) { trivialTransition[j*size+i] = 1; } else { trivialTransition[j*size+i] = 0; }
	transitions->at(0) = trivialTransition;
}


MarkovProcess::~MarkovProcess ()
{
	delete[] distribution;
	distributions->clear();
	delete distributions;

	delete[] transition;
	transitions->clear();
	delete transitions;	
}


void MarkovProcess::setDistribution (double *array)
{
	for (int i = 0; i < size; i++) { distribution[i] = array[i]; }
}


void MarkovProcess::setTransition (double *array)
{
	for (int j = 0; j < size; j++)
	{ 
		for (int i = 0; i < size; i++) { transition[j*size+i] = array[j*size+i]; }
	}
}


void MarkovProcess::setTransition (int i, double *array)
{
	for (int j = 0; j < size; j++) { transition[j*size+i] = array[j]; }
}


double *MarkovProcess::getDistribution (int time)
{
	if (time == -1) { return distributions->at(lastTime); }
	
	if (lastTime < time)
	{
		distributions->resize(time+1);
		
		double *currentDist = getDistribution(lastTime);
		for (int t = lastTime + 1; t <= time; t++)
		{
			std::cout << "Distribution " << t << std::endl;
			double *newDist = new double [size];
			for (int i = 0; i < size; i++)
			{
				newDist[i] = 0;
				for (int j = 0; j < size; j++) { newDist[i] += currentDist[j] * getNextProbability(i,j,1); }
			}
			distributions->at(t) = newDist;
			currentDist = newDist;
		}
		lastTime = time;
	}
	
	return distributions->at(time);
}


void MarkovProcess::computeStationaryDistribution (double threshold)
{
	if (lastTime == 0) { getDistribution(1); }
	
	double *dist1 = getDistribution(lastTime-1);
	double *dist2 = getDistribution(lastTime);

	bool stationary = true;
	for (int i = 0; i < size && stationary; i++) { stationary = std::abs(dist1[i] - dist2[i]) < threshold; }
	
	while (!stationary)
	{
		dist1 = dist2;
		dist2 = getDistribution(lastTime+1);
		
		stationary = true;
		for (int i = 0; i < size && stationary; i++) { stationary = std::abs(dist1[i] - dist2[i]) < threshold; }
	}
}


double *MarkovProcess::getTransition (int delay)
{
	if (lastDelay < delay)
	{
		transitions->resize(delay+1);
		
		double *currentTrans = getTransition(lastDelay);
		for (int d = lastDelay + 1; d <= delay; d++)
		{
			std::cout << "Transition " << d << " (size " << size << ")" << std::endl;
			double *newTrans = new double [size*size];

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					newTrans[j*size+i] = 0;
					for (int k = 0; k < size; k++)
						newTrans[j*size+i] += transition[j*size+k] * currentTrans[k*size+i];
				}
			}

			transitions->at(d) = newTrans;
			currentTrans = newTrans;

		}
		lastDelay = delay;
	}
	
	return transitions->at(delay);
}


double MarkovProcess::getProbability (int individual, int time)
{
	double *dist = getDistribution(time);
	return dist[individual];
}


double MarkovProcess::getProbability (Part *part, int time)
{
	double probability = 0;
	for (std::list<int>::iterator it = part->individuals->begin(); it != part->individuals->end(); ++it)
	{
		int individual = *it;
		probability += getProbability(individual,time);
	}
	return probability;
}


double MarkovProcess::getNextProbability (int nextIndividual, int currentIndividual, int delay)
{
	double *trans = getTransition(delay);
	return trans[nextIndividual*size+currentIndividual];
}


double MarkovProcess::getNextProbability (Part *nextPart, int currentIndividual, int delay)
{
	double probability = 0;
	for (std::list<int>::iterator it = nextPart->individuals->begin(); it != nextPart->individuals->end(); ++it)
	{
		int nextIndividual = *it;
		probability += getNextProbability(nextIndividual,currentIndividual,delay);
	}
	return probability;
}


double MarkovProcess::getNextProbability (Part *nextPart, Part *currentPart, int delay, int time)
{	
	double probability = 0;
	double condProbability = 0;
	
	for (std::list<int>::iterator currentIt = currentPart->individuals->begin(); currentIt != currentPart->individuals->end(); ++currentIt)
		condProbability += getProbability(*currentIt,time);

	for (std::list<int>::iterator currentIt = currentPart->individuals->begin(); currentIt != currentPart->individuals->end(); ++currentIt)
	{
		int currentIndividual = *currentIt;
		for (std::list<int>::iterator nextIt = nextPart->individuals->begin(); nextIt != nextPart->individuals->end(); ++nextIt)
		{
			int nextIndividual = *nextIt;
			probability += getProbability(currentIndividual,time) / condProbability * getNextProbability(nextIndividual,currentIndividual,delay);
		}
	}
	return probability;
}


double MarkovProcess::getEntropy (Partition *partition, int time)
{
	double entropy = 0;
	
	for (std::list<Part*>::iterator it1 = partition->parts->begin(); it1 != partition->parts->end(); ++it1)
	{
		double prob = getProbability(*it1,time);
		if (prob > 0) { entropy += - prob * log2(prob); }
	}
	
	return entropy;
}


double MarkovProcess::getMutualInformation (Partition *nextPartition, Partition *currentPartition, int delay, int time)
{
	int nextTime = time + delay;
	if (time == -1) { nextTime = -1; }
	
	double information = 0;
	
	for (std::list<Part*>::iterator it1 = currentPartition->parts->begin(); it1 != currentPartition->parts->end(); ++it1)
	{
		Part *currentPart = *it1;
		double probCurrentPart = getProbability(currentPart,time);
		
		for (std::list<Part*>::iterator it2 = nextPartition->parts->begin(); it2 != nextPartition->parts->end(); ++it2)
		{
			Part *nextPart = *it2;
			double probNextPart = getProbability(nextPart,nextTime);
			
			double condProb = getNextProbability(nextPart,currentPart,delay,time);
			if (condProb > 0 && probNextPart > 0) { information += probCurrentPart * condProb * log2(condProb / probNextPart); }
		}
	}
	
	return information;
}


double MarkovProcess::getNextEntropy (Partition *partition, bool micro, int time)
{
	double entropy = 0;
	
	if (micro)
	{
		for (int currentIndividual = 0; currentIndividual < size; currentIndividual++)
		{
			for (std::list<Part*>::iterator nextIt = partition->parts->begin(); nextIt != partition->parts->end(); ++nextIt)
			{
				Part *nextPart = *nextIt;
				double nextProbability = getNextProbability(nextPart,currentIndividual,0);
				if (nextProbability > 0)
					entropy += - getProbability(currentIndividual,time) * nextProbability * log2(nextProbability);
			}
		}		
	}
	
	else {
		for (std::list<Part*>::iterator currentIt = partition->parts->begin(); currentIt != partition->parts->end(); ++currentIt)
		{
			Part *currentPart = *currentIt;
			for (std::list<Part*>::iterator nextIt = partition->parts->begin(); nextIt != partition->parts->end(); ++nextIt)
			{
				Part *nextPart = *nextIt;
				double nextProbability = getNextProbability(nextPart,currentPart,0,time);
				if (nextProbability > 0)
					entropy += - getProbability(currentPart,time) * nextProbability * log2(nextProbability);
			}
		}
	}
	
	return entropy;
}


double MarkovProcess::getClosureMeasure (Partition *partition, int time)
{
	return getNextEntropy(partition,false,time) - getNextEntropy(partition,true,time);
}


void MarkovProcess::print ()
{
	int width = 6;
	int prec = 3;
	
	for (int t = 0; t <= lastTime; t++)
	{
		double *dist = getDistribution(t);

		std::cout << "p(X" << t << ") = {";
		if (size > 0) { std::cout << std::setw(width) << std::setprecision(prec) << dist[0]; }
		if (size > 1)
		{
			for (int i = 1; i < size; i++) { std::cout << ", " << std::setw(width) << std::setprecision(prec) << dist[i]; }
		}
		std::cout << "}" << std::endl << std::endl;
	}

	for (int t = 0; t <= lastDelay; t++)
	{
		double *trans = getTransition(t);

		for (int i = 0; i < size; i++)
		{
			std::cout << "p(X" << (t+1) << "|x" << i << ") = {";
			if (size > 0) { std::cout << std::setw(width) << std::setprecision(prec) << trans[0*size+i]; }
			if (size > 1)
			{
				for (int j = 1; j < size; j++) { std::cout << ", " << std::setw(width) << std::setprecision(prec) << trans[j*size+i]; }
			}
			std::cout << "}" << std::endl;
		}
		std::cout << std::endl;
	}
}


