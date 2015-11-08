/*
 * This file is part of Multilevel Prediction.
 *
 * Multilevel Prediction is a toolbox to compute optimal predictors of Markov
 * chains, and in particular multilevel agent-based systems, by using the
 * information bottleneck method. For details regarding the formal grounds of
 * this method, please refer to:
 * 
 * Robin Lamarche-Perrin, Sven Banisch, and Eckehard Olbrich. The Information
 * Bottleneck Method for Optimal Prediction of Multilevel Agent-based Systems.
 * Technical Report MIS-Preprint 55/2015, Max Planck Institute for Mathematics
 * in the Sciences, Leipzig, Germany, 2015.
 * 
 * <http://www.mis.mpg.de/publications/preprints/2015/prepr2015-55.html>
 * 
 * Copyright © 2015 Robin Lamarche-Perrin (<Robin.Lamarche-Perrin@lip6.fr>)
 * 
 * Multilevel Prediction is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * Multilevel Prediction is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */


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

class TwoCommunitiesExperiment;
class ChainExperiment;

typedef std::set<TwoCommunitiesExperiment*> TwoCommunitiesExperimentSet;
typedef std::set<ChainExperiment*> ChainExperimentSet;



/*!
 * \brief Run a set of programmed experiments
 * \param expSet : Experiment set
 * \param fileName : Output file name
 */
void twoCommunitiesExperiment (TwoCommunitiesExperimentSet *expSet, std::string fileName);
void chainExperiment (ChainExperimentSet *expSet, std::string fileName);

void addMeasurement (MeasurementSet *set, VoterGraph *VG, MeasurementType type, VoterMetric metric);
void addMultiMeasurement (MeasurementSet *set, VoterGraph *VG, MeasurementType type, VoterMetric metric);
VoterMeasurement *getMeasurement (VoterGraph *VG, MeasurementType type, VoterMetric metric = MACRO_STATE, int binning = 0);

void addTwoCommunitiesHeaderToCSV (std::string fileName);
void addTwoCommunitiesPartHeaderToCSV (std::string fileName, std::string type);

void computeTwoCommunitiesMeasures (std::ofstream &csvFile, MarkovProcess *MP, std::string type, int update,
				    int size1, int size2, double intraR1, double intraR2, double interR1, double interR2, double contrarian1, double contrarian2,
				    VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay, Partition *microP);

void computeTwoCommunitiesMeasuresWithAggregation (std::ofstream &csvFile, MarkovProcess *MP, std::string type, int update,
						   int size1, int size2, double intraR1, double intraR2, double interR1, double interR2, double contrarian1, double contrarian2,
						   VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay, double threshold);

void computeTwoCommunitiesPartMeasures (std::ofstream &csvFile, MarkovProcess *MP, int size1, int size2,
					VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay);


/*!
 * \class TwoCommunitiesExperiment
 * \brief Programming a prediction experiment on a two-communities Voter Model
 */
class TwoCommunitiesExperiment
{
public:
    static int id_number;
    int id;					/*!< A unique experiment number*/
		
    UpdateProcess update;	/*!< The update process of the built Voter Model*/
    double threshold;		/*!< The precision threshold to compute the stationary distribution of the Markov chain (see computeStationaryDistribution method in MarkovProcess class)*/
    bool compactModel;		/*!< If true, the computed microscopic Markov chain is lumped according to the macro-state of community 1, the macro-state of community 2, and the state of the first agent in community 1*/
    bool withAggregation;
    bool partDecomposition;
		
    int size1Min;			/*!< The size of community 1 in the first experiment*/
    int size1Max;			/*!< The size of community 1 in the last experiment*/
    int size1Step;			/*!< The size of community 1 between two consecutive experiments*/
    int size2Min;			/*!< The size of community 2 in the first experiment*/
    int size2Max;			/*!< The size of community 2 in the last experiment*/
    int size2Step;			/*!< The size of community 2 between two consecutive experiments*/
    bool equalSize;			/*!< If true, the size of community 2 is the same than the size of community 1 in all experiments*/
	
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
    bool equalIntraRate;	/*!< If true, the weight of edges within community 2 is the same than the weight of edges within community 2 in all experiments*/
    bool equalInterRate;	/*!< If true, the weight of edges from community 2 to community 1 is the same than the weight of edges from community 1 to community 2 in all experiments*/
    bool oppositeInterRate;	/*!< If true, the weight of edges from community 2 to community 1 is the opposite of the weight of edges from community 1 to community 2 in all experiments (w2 = 1 - w1)*/
	
    double contrarian1Min;	/*!< The contrarian rate of nodes within community 1 in the first experiment*/
    double contrarian1Max;	/*!< The contrarian rate of nodes within community 1 in the last experiment*/
    double contrarian1Step;	/*!< The contrarian rate of nodes within community 1 between two consecutive experiments*/
    double contrarian2Min;	/*!< The contrarian rate of nodes within community 2 in the first experiment*/
    double contrarian2Max;	/*!< The contrarian rate of nodes within community 2 in the last experiment*/
    double contrarian2Step;	/*!< The contrarian rate of nodes within community 2 between two consecutive experiments*/
    bool equalContrarian;	/*!< If true, the contrarian rate of nodes within community 2 is the same than the contrarian rate of nodes within community 1 in all experiments*/
	
    int timeMin;			/*!< The time of pre-measurement (-1 for stationary distribution) in the first experiment*/
    int timeMax;			/*!< The time of pre-measurement (-1 for stationary distribution) in the last experiment*/
    int timeStep;			/*!< The time of pre-measurement (-1 for stationary distribution) between two consecutive experiments*/
    int delayMin;			/*!< The delay before post-measurement in the first experiment*/
    int delayMax;			/*!< The delay before post-measurement in the last experiment*/
    int delayStep;			/*!< The delay before post-measurement between two consecutive experiments*/
		
    SpecMeasurementSet *preMeasurements;		/*!< A set of pre-measurement for prediction*/
    SpecMeasurementSet *postMeasurements;		/*!< A set of post-measurement to be predicted*/
		
    /*!
     * \brief Constructor
     * \param size1 : The size of community 1 in all experiments
     * \param size2 : The size of community 2 in all experiments
     * \param intraR1 : The weight of edges within community 1 in all experiments
     * \param intraR2 : The weight of edges within community 2 in all experiments
     * \param interR1 : The weight of edges from community 1 to community 2 in all experiments
     * \param interR2 : The weight of edges from community 2 to community 1 in all experiments
     * \param contrarian1 : The contrarian rate of nodes within community 1 in all experiments
     * \param contrarian2 : The contrarian rate of nodes within community 2 in all experiments
     * \param time : The time of pre-measurement (-1 for stationary distribution) in all experiments
     * \param delay : The delay before post-measurement in all experiments
     * \param preMeasurements : A set of pre-measurement for prediction
     * \param postMeasurements : A set of post-measurement to be predicted
     */
    TwoCommunitiesExperiment (int size1, int size2, double intraR1, double intraR2, double interR1, double interR2,
			      double contrarian1, double contrarian2, double time, double delay,
			      SpecMeasurementSet *preMeasurements, SpecMeasurementSet *postMeasurements);

    /*!
     * \brief Destructor
     */
    ~TwoCommunitiesExperiment ();
};



class ChainExperiment
{
public:
    static int id_number;
    int id;					/*!< A unique experiment number*/
		
    UpdateProcess update;	/*!< The update process of the built Voter Model*/
    double threshold;		/*!< The precision threshold to compute the stationary distribution of the Markov chain (see computeStationaryDistribution method in MarkovProcess class)*/
    bool withAggregation;
    bool ring;
		
    int sizeMin;
    int sizeMax;
    int sizeStep;
		
    double contrarianMin;	/*!< The contrarian rate of nodes within community 1 in the first experiment*/
    double contrarianMax;	/*!< The contrarian rate of nodes within community 1 in the last experiment*/
    double contrarianStep;	/*!< The contrarian rate of nodes within community 1 between two consecutive experiments*/
	
    int timeMin;			/*!< The time of pre-measurement (-1 for stationary distribution) in the first experiment*/
    int timeMax;			/*!< The time of pre-measurement (-1 for stationary distribution) in the last experiment*/
    int timeStep;			/*!< The time of pre-measurement (-1 for stationary distribution) between two consecutive experiments*/
    int delayMin;			/*!< The delay before post-measurement in the first experiment*/
    int delayMax;			/*!< The delay before post-measurement in the last experiment*/
    int delayStep;			/*!< The delay before post-measurement between two consecutive experiments*/
		
    SpecMeasurementSet *preMeasurements;		/*!< A set of pre-measurement for prediction*/
    SpecMeasurementSet *postMeasurements;		/*!< A set of post-measurement to be predicted*/
		
    ChainExperiment (int size, double contrarian, bool ring, double time, double delay,
		     SpecMeasurementSet *preMeasurements, SpecMeasurementSet *postMeasurements);

    ~ChainExperiment ();
};

#endif
