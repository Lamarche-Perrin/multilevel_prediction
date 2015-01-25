#ifndef INCLUDE_MARKOV_PROCESS
#define INCLUDE_MARKOV_PROCESS

/*!
 * \file markov_process.hpp
 * \brief Class to build a finite Markov chain
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */

#include <vector>

#include "partition.hpp"

/*!
 * \class MarkovProcess
 * \brief A finite Markov chain described by a discrete state space, an initial distribution, and a transition kernel
 */
class MarkovProcess
{
	public:
		int size;								/*!< The size of the Markov chain state space*/

		double *distribution;					/*!< The initial probability distribution of the system state (time 0)*/
		std::vector<double*> *distributions;	/*!< A vector of probability distributions through time (from 0 to lastTime)*/
		int lastTime;							/*!< The time of the furthest computed probability distribution in the distributions vector*/

		double *transition;						/*!< The transition kernel of the Markov chain (1 step)*/
		std::vector<double*> *transitions;		/*!< A vector of transition kernels for several steps (from 1 to lastDelay)*/
		int lastDelay;							/*!< The delay of the furthest computed transition kernel in the transitions vector*/
				
		/*!
		 * \brief Constructor
		 * \param size : The size of the Markov chain state space
		 */
		MarkovProcess (int size);

		/*!
		 * \brief Destructor
		 */
		~MarkovProcess ();

		/*!
		 * \brief Print the Markov chain structure and details
		 */
		void print();

		/*!
		 * \brief Set the initial distribution
		 * \param array : An array of probabilities (summing to 1) with the size of the Markov chain state space
		 */
		void setDistribution (double *array);

		/*!
		 * \brief Set the transition kernel
		 * \param array : A 2D-array of probabilities (summing to 1 within each row) with the square of the size of the Markov chain state space
		 */
		void setTransition (double *array);

		/*!
		 * \brief Set one line of the transition kernel
		 * \param j : The index of the row to be set
		 * \param array : An array of probabilities (summing to 1) with the size of the Markov chain state space
		 */
		void setTransition (int j, double *array);

		/*!
		 * \brief Get the state distribution at a given time (-1 for the stationary distribution)
		 */
		double *getDistribution (int time);

		/*!
		 * \brief Get the transition kernel for a given number of simulation steps (delay)
		 */
		double *getTransition (int delay);

		/*!
		 * \brief Compute the stationary distribution of the Markov chain by iterating the transition kernel
		 * \param threshold : Determines stationarity by giving the minimal difference between two probability values in two different but consecutive distributions
		 * \warning Will endlessly loop for periodic Markov chains
		 */
		void computeStationaryDistribution (double threshold);

		/*!
		 * \brief Get the probability to be in a given state at a given time (-1 for the stationary distribution)
		 */
		double getProbability (int individual, int currentTime);

		/*!
		 * \brief Get the probability to be in a given subset of states at a given time (-1 for the stationary distribution)
		 */
		double getProbability (Part *part, int currentTime);

		/*!
		 * \brief Get the probability to be in a given state after a given delay knowing the current state
		 */
		double getNextProbability (int nextIndividual, int currentIndividual, int delay);

		/*!
		 * \brief Get the probability to be in a given subset of states after a given delay knowing the current state
		 */
		double getNextProbability (Part *nextPart, int currentIndividual, int delay);

		/*!
		 * \brief Get the probability to be in a given subset of states after a given delay knowing the current subset of states at a given time (-1 for the stationary distribution)
		 */
		double getNextProbability (Part *nextPart, Part *currentPart, int delay, int time);

		/*!
		 * \brief Get the Shannon entropy of the state distribution at a given time (-1 for the stationary distribution) when lumped according to a given partition of the state space
		 */
		double getEntropy (Partition *partition, int currentTime);

		/*!
		 * \brief Get the mutual information between the state distribution at a given time (-1 for the stationary distribution) and the state distribution after a given delay, when both are lumped according to a given partition of the state space
		 */
		double getMutualInformation (Partition *nextPartition, Partition *currentPartition, int delay, int time);

		/*!
		 * \brief Get the Shannon entropy of the next state distribution knowing the current state distribution at a given time (-1 for the stationary distribution), when the next distribution is lumped according to a given partition of the state space, and when the current partition is also lumped by the same partition (when micro is true)
		 */
		double getNextEntropy (Partition *partition, bool micro, int time);

		/*!
		 * \brief Get the information flow at a given time (-1 for the stationary distribution) between the Markov chain lumped according to a given partition of the state space and the microscopic Markov chain
		 */
		double getInformationFlow (Partition *partition, int time);
};


#endif
