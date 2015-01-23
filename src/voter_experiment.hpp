#ifndef INCLUDE_VOTER_EXPERIMENT
#define INCLUDE_VOTER_EXPERIMENT

/*!
 * \file voter_experiment.hpp
 * \brief Tools to run prediction experiments on Voter Models
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */


#include <fstream>

#include "csv_tools.hpp"
#include "partition.hpp"
#include "voter_graph.hpp"
#include "markov_process.hpp"

class VoterExperiment;
typedef std::set<VoterExperiment*> ExperimentSet;



/*!
 * \brief Run a set of programmed experiments
 * \param expSet : Experiment set
 * \param fileName : Output file name
 */
void voterExperiment (std::set<VoterExperiment*> *expSet, std::string fileName);

void addMeasurement (MeasurementType measurement, MeasurementSet *set, VoterGraph *VG);

void addHeaderToCSV (std::string fileName);

void addLineToCSV (std::ofstream &csvFile, MarkovProcess *MP, std::string type, int update,
	int size1, int size2, double intraR1, double intraR2, double interR1, double interR2, double contrarian,
	VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay, Partition *microP);


/*!
 * \class VoterExperiment
 * \brief Programming a prediction experiment on a two-communities Voter Model
 */
class VoterExperiment
{
	public:
		static int id_number;
		int id;					/*!< A unique experiment number*/
		
		UpdateProcess update;	/*!< The update process of the built Voter Model*/
		double threshold;		/*!< The precision threshold to compute the stationary distribution of the Markov chain (see computeStationaryDistribution method in MarkovProcess class)*/
		bool compactModel;		/*!< If true, the computed microscopic Markov chain is lumped according to the macro-state of community 1, the macro-state of community 2, and the state of the first agent in community 1*/
		
		int size1Min;			/*!< The size of community 1 in the first experiment*/
		int size1Max;			/*!< The size of community 1 in the last experiment*/
		int size1Step;			/*!< The size of community 1 between two consecutive experiments*/
		int size2Min;			/*!< The size of community 2 in the first experiment*/
		int size2Max;			/*!< The size of community 2 in the last experiment*/
		int size2Step;			/*!< The size of community 2 between two consecutive experiments*/
		bool equalSize;			/*!< If true, the size of community 2 is the same as the size of community 1 in all experiments*/
	
		double intraR1Min;		/*!< The weight of edges within community 1 in the first experiment*/
		double intraR1Max;		/*!< The weight of edges within community 1 in the last experiment*/
		double intraR1Step;		/*!< The weight of edges within community 1 between two consecutive experiments*/
		double intraR2Min;		/*!< The weight of edges within community 2 in the first experiment*/
		double intraR2Max;		/*!< The weight of edges within community 2 in the last experiment*/
		double intraR2Step;		/*!< The weight of edges within community 2 between two consecutive experiments*/
		double interR1Min;		/*!< The weight of edges from community 1 to community 2 in the first experiment*/
		double interR1Max;		/*!< The weight of edges from community 1 to community 2 in the last experiment*/
		double interR1Step;		/*!< The weight of edges from community 1 to community 2 between two consecutive experiments*/
		double interR2Min;		/*!< The weight of edges from community 2 to community 1 in the first experiment*/
		double interR2Max;		/*!< The weight of edges from community 2 to community 1 in the last experiment*/
		double interR2Step;		/*!< The weight of edges from community 2 to community 1 between two consecutive experiments*/
		bool equalIntraRate;	/*!< If true, the weight of edges within community 2 is the same as the weight of edges within community 2 in all experiments*/
		bool equalInterRate;	/*!< If true, the weight of edges from community 2 to community 1 is the same as the weight of edges from community 1 to community 2 in all experiments*/
		bool oppositeInterRate;	/*!< If true, the weight of edges from community 2 to community 1 is the opposite of the weight of edges from community 1 to community 2 in all experiments (w2 = 1 - w1)*/
	
		double contrarianMin;	/*!< The contrarian rate of nodes in the first experiment*/
		double contrarianMax;	/*!< The contrarian rate of nodes in the last experiment*/
		double contrarianStep;	/*!< The contrarian rate of nodes between two consecutive experiments*/
	
		int timeMin;			/*!< The time of pre-measurement (-1 for stationary distribution) in the first experiment*/
		int timeMax;			/*!< The time of pre-measurement (-1 for stationary distribution) in the last experiment*/
		int timeStep;			/*!< The time of pre-measurement (-1 for stationary distribution) between two consecutive experiments*/
		int delayMin;			/*!< The delay before post-measurement in the first experiment*/
		int delayMax;			/*!< The delay before post-measurement in the last experiment*/
		int delayStep;			/*!< The delay before post-measurement between two consecutive experiments*/
		
		std::set<MeasurementType> *preMeasurements;			/*!< A set of pre-measurement for prediction*/
		std::set<MeasurementType> *postMeasurements;		/*!< A set of post-measurement to be predicted*/
		
		/*!
		 * \brief Constructor
		 * \param size1 : The size of community 1 in all experiments
		 * \param size2 : The size of community 2 in all experiments
		 * \param intraR1 : The weight of edges within community 1 in all experiments
		 * \param intraR2 : The weight of edges within community 2 in all experiments
		 * \param interR1 : The weight of edges from community 1 to community 2 in all experiments
		 * \param interR2 : The weight of edges from community 2 to community 1 in all experiments
		 * \param contrarian : The contrarian rate of nodes in all experiments
		 * \param time : The time of pre-measurement (-1 for stationary distribution) in all experiments
		 * \param delay : The delay before post-measurement in all experiments
		 * \param preMeasurements : A set of pre-measurement for prediction
		 * \param postMeasurements : A set of post-measurement to be predicted
		 */
		VoterExperiment (int size1, int size2, double intraR1, double intraR2, double interR1, double interR2,
			double contrarian, double time, double delay, std::set<MeasurementType> *preMeasurements, std::set<MeasurementType> *postMeasurements);

		/*!
		 * \brief Destructor
		 */
		~VoterExperiment ();

};

#endif
