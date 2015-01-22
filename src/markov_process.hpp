#ifndef INCLUDE_MARKOV_PROCESS
#define INCLUDE_MARKOV_PROCESS

#include <vector>

#include "partition.hpp"

class MarkovProcess
{
	public:
		int size;

		double *distribution;
		std::vector<double*> *distributions;
		int lastTime;

		double *transition;
		std::vector<double*> *transitions;
		int lastDelay;
				
		MarkovProcess (int size);
		~MarkovProcess ();
		void print();

		void setDistribution (double *array);
		void setTransition (int j, double *array);
		void setTransition (double *array);

		double *getDistribution (int time);
		double *getTransition (int delay);
		void computeStationaryDistribution (double threshold);
		double *getStationaryDistribution ();

		double getProbability (int individuals, int currentTime);
		double getProbability (Part *part, int currentTime);

		double getNextProbability (int nextIndividual, int currentIndividual, int delay);
		double getNextProbability (Part *nextPart, int currentIndividual, int delay);
		double getNextProbability (Part *nextPart, Part *currentPart, int delay, int time);

		double getEntropy (Partition *partition, int currentTime);
		double getMutualInformation (Partition *nextPartition, Partition *currentPartition, int delay, int time);

		double getNextEntropy (Partition *partition, bool micro, int time);
		double getClosureMeasure (Partition *partition, int time);
};


#endif
