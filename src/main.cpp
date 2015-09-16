/*!
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

#include "main.hpp"
#include "timer.hpp"
#include "voter_experiment.hpp"
#include "voter_graph.hpp"


bool VERBOSE = false;




int main(int argc, char *argv[])
{
    srand(time(NULL));
    //srand(4);

	/*
	for (int size = 1; size <= 50; size++)
	{
		MarkovProcess *MP = new MarkovProcess (size);

		for (int i = 0; i < size; i++)
			MP->distribution[i] = 1./size;

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				MP->transition[j*size+i] = 1./size;

		MP->computeStationaryDistribution(0.00001);

		delete MP;
	}
	*/
	
	testLandUseModel();
	
	/*
	int size = 100;
    double contrarian = 1./(size+1);

    int time = 10000;
    int delay = 10;
	int prior = 1;

	int trainSize = 2000;
	int testSize = 100;
	int trainLength = 100;
	int testLength = 0;

	int incrStep = 10;

	
	std::string fileName = "../data/optbin_small-test.csv";
	testSize = 50;

	std::ofstream file;
	deleteCSV(fileName);
	openOutputCSV(file,fileName);
	addCSVField(file,"VAR");
	addCSVField(file,"SCORE");
	addCSVField(file,"BINS");
	addCSVField(file,"CUTS",false);
	endCSVLine(file);
	
	
    CompleteVoterGraph *VG = new CompleteVoterGraph (size,UPDATE_EDGES,contrarian);
 	VoterDataSet *DS = new VoterDataSet (VG, time, delay, trainSize, testSize, trainLength, testLength);

	VoterMeasurement *preM = getMeasurement (VG, M_MACRO, MACRO_STATE);
	VoterMeasurement *postM = getMeasurement (VG, M_MACRO, MACRO_STATE);

	for (int t = incrStep; t <= trainSize; t += incrStep)
	{
		VoterBinning *binning = DS->getOptimalBinning(preM, postM, prior, t);
		std::cout << "OPTIMAL BINNING FOR " << t << " TRAJECTORIES" << std::endl;
		binning->print(false);

		addCSVField(file,t);
		addCSVField(file,binning->score);
		addCSVField(file,binning->binNumber);

		std::string str = "";
		for (int i = 0; i < binning->binNumber; i++)
		{
			if (i > 0) { str += ","; }
			str += int2string(binning->cuts[i]);
		}
		addCSVField(file,str,false);
		endCSVLine(file);

		delete binning;
	}
	
	closeOutputCSV(file);

	*/
	
    /*
    int size = 7;
    double contrarian = 1./(size+1);

    int time = -1;
    int delay = 1;
    int dataSize = 100;
    int dataLength = 101;
    int trainingLength = 95;

    TwoCommunitiesVoterGraph *VG = new TwoCommunitiesVoterGraph (size,0, 1,0,0,0, contrarian,0);
    MarkovProcess *MP = VG->getMarkovProcess();
    MP->computeStationaryDistribution(0.0001);

    VoterMeasurement *preM = getMeasurement (M_MICRO, MACRO_STATE, VG);
    VoterMeasurement *postM = getMeasurement (M_MICRO, MACRO_STATE, VG);
    Partition *preP = VG->getMarkovPartition(preM);
    Partition *postP = VG->getMarkovPartition(postM);

    for (int ds = 100; ds <= 1000; ds += 100)
    {
	MarkovDataSet *DS = new MarkovDataSet (MP, ds, time, dataLength);
	std::cout << DS->computeScore (preP, postP, delay, trainingLength) << std::endl;
    }
    */

    return EXIT_SUCCESS;
}


void testScoreFunctions ()
{
	int size = 4;
	int time = 0;
    int delay = 1;

	int trainSize = 17;
	int testSize = 10;
	int trainLength = 1;
	int testLength = 0;

    CompleteVoterGraph *VG = new CompleteVoterGraph (size);
	VoterDataSet *DS = new VoterDataSet (VG, time, delay, trainSize, testSize, trainLength, testLength);

	int t = 0; bool *s0; bool *s1;
	
	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 1; s1[1] = 0; s1[2] = 0; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 1; s1[2] = 0; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 1; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 1; s1[1] = 0; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 1; s1[1] = 1; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 1; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 1; s1[1] = 0; s1[2] = 0; s1[3] = 0;
	
	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 0; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 1; s0[2] = 1; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 1; s1[1] = 0; s1[2] = 0; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 0; s0[1] = 0; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 0; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 1; s0[1] = 0; s0[2] = 0; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 0; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 1; s0[1] = 1; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 1; s1[1] = 0; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 1; s0[1] = 1; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 0; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 1; s0[1] = 1; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 1; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 1; s0[1] = 1; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 1; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;     s0[0] = 1; s0[1] = 1; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;   s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 0;


	VoterMeasurement *preM = getMeasurement (VG, M_MACRO, MACRO_STATE);
	VoterMeasurement *postM = getMeasurement (VG, M_MACRO, MACRO_STATE);

	DS->estimateTransitionMap (preM, postM);
	DS->printTransitionMap ();


	DS->testSize = 1;
	
	s0 = DS->trajectories[t]->states[0]->agentStates;    s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 1;
	
	std::cout << std::endl;
	std::cout << "FIRST CASE" << std::endl;
	std::cout << DS->getLogScore (preM, postM, 0) << " / " << DS->getQuadScore (preM, postM, 0) << std::endl;
	std::cout << DS->getLogScore (preM, postM, 1) << " / " << DS->getQuadScore (preM, postM, 1) << std::endl;

	
	s0 = DS->trajectories[t]->states[0]->agentStates;    s0[0] = 1; s0[1] = 0; s0[2] = 1; s0[3] = 0;
	s1 = DS->trajectories[t]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 1; s1[3] = 1;
	
	std::cout << std::endl;
	std::cout << "SECOND CASE" << std::endl;
	std::cout << DS->getLogScore (preM, postM, 0) << " / " << DS->getQuadScore (preM, postM, 0) << std::endl;
	std::cout << DS->getLogScore (preM, postM, 1) << " / " << DS->getQuadScore (preM, postM, 1) << std::endl;

	
	s0 = DS->trajectories[t]->states[0]->agentStates;    s0[0] = 0; s0[1] = 0; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t]->states[1]->agentStates;    s1[0] = 0; s1[1] = 1; s1[2] = 1; s1[3] = 1;
	
	std::cout << std::endl;
	std::cout << "THIRD CASE" << std::endl;
	std::cout << DS->getLogScore (preM, postM, 0) << " / " << DS->getQuadScore (preM, postM, 0) << std::endl;
	std::cout << DS->getLogScore (preM, postM, 1) << " / " << DS->getQuadScore (preM, postM, 1) << std::endl;

	
	s0 = DS->trajectories[t]->states[0]->agentStates;    s0[0] = 1; s0[1] = 1; s0[2] = 1; s0[3] = 0;
	s1 = DS->trajectories[t]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 0;
	
	std::cout << std::endl;
	std::cout << "FOURTH CASE" << std::endl;
	std::cout << DS->getLogScore (preM, postM, 0) << " / " << DS->getQuadScore (preM, postM, 0) << std::endl;
	std::cout << DS->getLogScore (preM, postM, 1) << " / " << DS->getQuadScore (preM, postM, 1) << std::endl;


	DS->testSize = testSize;
	
	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 0; s0[1] = 0; s0[2] = 0; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 1; s0[1] = 0; s0[2] = 1; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 1; s0[1] = 0; s0[2] = 1; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 0; s0[1] = 0; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 1; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 0; s0[1] = 0; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 1; s1[1] = 0; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 0; s0[1] = 1; s0[2] = 0; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 1; s1[1] = 1; s1[2] = 1; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 1; s0[1] = 0; s0[2] = 0; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 1; s1[2] = 1; s1[3] = 1;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 1; s0[1] = 1; s0[2] = 1; s0[3] = 0;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 1; s0[1] = 0; s0[2] = 1; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 0;

	s0 = DS->trajectories[t]->states[0]->agentStates;      s0[0] = 1; s0[1] = 1; s0[2] = 0; s0[3] = 1;
	s1 = DS->trajectories[t++]->states[1]->agentStates;    s1[0] = 0; s1[1] = 0; s1[2] = 0; s1[3] = 0;

	std::cout << std::endl;
	std::cout << "BEST CUT WITH NO PRIOR" << std::endl;
	DS->getOptimalBinning(preM, postM, 0, true);

	std::cout << std::endl;
	std::cout << "BEST CUT WITH PRIOR" << std::endl;
	DS->getOptimalBinning(preM, postM, 1, true);
}


void computeInformationMeasures ()
{
    std::string fileName = "DATA.CSV";

    bool compactModel = true;
    bool chain = false;
    bool partDecomposition = true;

    bool basicMeasures = false;
    bool allSizes = false;
    bool twoCommunitiesMeasures = false;

    ChainExperimentSet *expChainSet = new ChainExperimentSet();
    TwoCommunitiesExperimentSet *exp2CSet = new TwoCommunitiesExperimentSet();

    SpecMeasurementSet* preM = new SpecMeasurementSet();
    SpecMeasurementSet* postM = new SpecMeasurementSet();

    postM->insert(std::make_pair(M_AGENT1,MACRO_STATE));
    //postM->insert(std::make_pair(M_MACRO,MACRO_STATE));


    /*
    ChainExperiment *exp;
    exp = new ChainExperiment(9,0,true,0,0,preM,postM); exp->delayMax = 100; expChainSet->insert(exp);
    exp = new ChainExperiment(9,0.1,true,0,0,preM,postM); exp->delayMax = 100; expChainSet->insert(exp);
    exp = new ChainExperiment(9,0.1,true,-1,0,preM,postM); exp->delayMax = 100; expChainSet->insert(exp);
    preM->insert(std::make_pair(M_EMPTY,MACRO_STATE));
    preM->insert(std::make_pair(M_MICRO,MACRO_STATE));
    preM->insert(std::make_pair(M_AGENT1,MACRO_STATE));
    preM->insert(std::make_pair(M_ALLNEIGHBORHOODS,MACRO_STATE));
    */


    TwoCommunitiesExperiment *exp;

    /*
    exp = new TwoCommunitiesExperiment(10,10,1,1,0,0,0,0,0,0,preM,postM);
    exp->delayMax = 100;
    exp->interR1Min = 0;
    exp->interR1Step = 0.01;
    exp->interR1Max = 1.05;
    exp->equalInterRate = false;
    exp->compactModel = compactModel; exp->partDecomposition = partDecomposition; exp2CSet->insert(exp);
    */

    //exp = new TwoCommunitiesExperiment(2,1,1,1,1,1,0,0,0,1,preM,postM); exp->compactModel = compactModel; exp->partDecomposition = partDecomposition; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(10,10,1,1,0.2,0.2,0,0,0,50,preM,postM); exp->compactModel = compactModel; exp->partDecomposition = partDecomposition; exp2CSet->insert(exp);

    //preM->insert(std::make_pair(M_AGENT1_MACRO,MACRO_STATE));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MACRO_STATE));
    preM->insert(std::make_pair(M_MESO1,MACRO_STATE));

/*    

    int N1 = 10;        int N2 = 10;

    double f = 1./5;
    double b11 = 1./(N1*(N1-1));   double s11 = f*b11;
    double b22 = 1./(N2*(N2-1));   double s22 = f*b22;
    double b12 = 1./(N1*N2);       double s12 = f*b12;
    double b21 = 1./(N2*N1);       double s21 = f*b21;

    exp = new TwoCommunitiesExperiment(N1,N2,b11,b22,b12,b21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(N1,N2,b11,b22,s12,s21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(N1,N2,b11,b22,s12,b21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(N1,N2,b11,b22,b12,s21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(N1,N2,s11,b22,s12,b21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(N1,N2,b11,s22,b12,s21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(N1,N2,s11,b22,b12,b21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
    exp = new TwoCommunitiesExperiment(N1,N2,b11,s22,b12,b21,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp2CSet->insert(exp);
*/

    //preM->insert(std::make_pair(M_SOMESIZES1,MACRO_STATE));
    //preM->insert(std::make_pair(M_AGENT1_ALLSIZES1,MACRO_STATE));    

    if (basicMeasures)
    {
	preM->insert(std::make_pair(M_AGENT1,MACRO_STATE));
	preM->insert(std::make_pair(M_EMPTY,MACRO_STATE));
	preM->insert(std::make_pair(M_MACRO,MACRO_STATE));
	if (!compactModel) { preM->insert(std::make_pair(M_MICRO,MACRO_STATE)); }
    }

    if (allSizes)
    {
	preM->insert(std::make_pair(M_ALLSIZES1,MACRO_STATE));
	//preM->insert(std::make_pair(M_AGENT1_ALLSIZES1,MACRO_STATE));
    }

    if (twoCommunitiesMeasures)
    {
	preM->insert(std::make_pair(M_MESO1,MACRO_STATE));
	preM->insert(std::make_pair(M_MESO2,MACRO_STATE));

	preM->insert(std::make_pair(M_AGENT1_MACRO,MACRO_STATE));
	preM->insert(std::make_pair(M_AGENT1_MESO1,MACRO_STATE));
	preM->insert(std::make_pair(M_AGENT1_MESO2,MACRO_STATE));
	preM->insert(std::make_pair(M_AGENT1_MESO1_MESO2,MACRO_STATE));
	preM->insert(std::make_pair(M_MESO1_MESO2,MACRO_STATE));
    }
    
    //preM->insert(std::make_pair(M_MACRO,MAJORITY));
    //preM->insert(std::make_pair(M_AGENT1_MACRO,MAJORITY));

    /*
    preM->insert(std::make_pair(M_MACRO,MAJ_2B));
    preM->insert(std::make_pair(M_MACRO,MAJ_3B));
    preM->insert(std::make_pair(M_MACRO,MAJ_4B));
    preM->insert(std::make_pair(M_MACRO,MAJ_6B));
    preM->insert(std::make_pair(M_MACRO,MAJ_8B));
    preM->insert(std::make_pair(M_MACRO,MAJ_12B));

    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_2B));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_3B));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_4B));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_6B));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_8B));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_12B));
    */

    /*
    preM->insert(std::make_pair(M_MACRO,MAJ_1PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_2PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_3PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_4PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_5PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_6PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_7PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_8PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_9PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_10PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_20PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_30PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_40PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_50PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_60PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_70PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_80PC));
    preM->insert(std::make_pair(M_MACRO,MAJ_90PC));

    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_1PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_2PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_3PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_4PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_5PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_6PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_7PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_8PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_9PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_10PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_20PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_30PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_40PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_50PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_60PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_70PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_80PC));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_90PC));
    */

    if (chain) { chainExperiment(expChainSet,"/home/lamarche/programming/multilevel_prediction/data/" + fileName); }
    else { twoCommunitiesExperiment(exp2CSet,"/home/lamarche/programming/multilevel_prediction/data/" + fileName); }
}



void testVoterGraph ()
{
    VoterGraph *VG = new VoterGraph ();
    VoterNode *n = VG->addNode();
    VoterNode *n1 = VG->addNode();
    VoterNode *n2 = VG->addNode();
    VG->addEdge(n,n1);
    VG->addEdge(n,n2);
    VG->addEdge(n1,n2);
    VG->addEdge(n2,n1);
    VG->print();

    MarkovProcess *MP = VG->getMarkovProcess();
    MP->getDistribution(2);
    MP->getTransition(2);
    MP->print();

    VoterProbe *probe = new VoterProbe(VG);
    VoterMeasurement *preM = new VoterMeasurement(VG,"preM");
    probe->addNode(n);
    preM->addProbe(probe,MACRO_STATE);

    VoterProbe *probe1 = new VoterProbe(VG);
    VoterProbe *probe2 = new VoterProbe(VG);
    VoterMeasurement *postM = new VoterMeasurement(VG,"postM");
    probe1->addNode(n1);
    probe2->addNode(n2);
    postM->addProbe(probe1,MACRO_STATE);
    postM->addProbe(probe2,MACRO_STATE);

    Partition *preP = VG->getMarkovPartition(preM);
    Partition *postP = VG->getMarkovPartition(postM);
    preP->print(true);
    postP->print(true);

    std::cout << "preH_0 = " << MP->getEntropy(preP,0) << std::endl;
    std::cout << "preH_1 = " << MP->getEntropy(preP,1) << std::endl;
    std::cout << "preH_2 = " << MP->getEntropy(preP,2) << std::endl;
	
    std::cout << "postH_0 = " << MP->getEntropy(postP,0) << std::endl;
    std::cout << "postH_1 = " << MP->getEntropy(postP,1) << std::endl;
    std::cout << "postH_2 = " << MP->getEntropy(postP,2) << std::endl;
	
    std::cout << "preI_00 = " << MP->getMutualInformation(postP,preP,0,0) << std::endl;
    std::cout << "preI_01 = " << MP->getMutualInformation(postP,preP,1,0) << std::endl;
    std::cout << "preI_02 = " << MP->getMutualInformation(postP,preP,2,0) << std::endl;
    std::cout << "preI_12 = " << MP->getMutualInformation(postP,preP,2,1) << std::endl;

    std::cout << "postI_00 = " << MP->getMutualInformation(preP,postP,0,0) << std::endl;
    std::cout << "postI_01 = " << MP->getMutualInformation(preP,postP,1,0) << std::endl;
    std::cout << "postI_02 = " << MP->getMutualInformation(preP,postP,2,0) << std::endl;
    std::cout << "postI_12 = " << MP->getMutualInformation(preP,postP,2,1) << std::endl;

    delete VG;
    delete MP;
    delete preP;
    delete postP;
    delete preM;
    delete postM;
}


void testMeasuresWithAggregation ()
{
    CompleteVoterGraph *VG = new CompleteVoterGraph (4);
    MarkovProcess *MP = VG->getMarkovProcess();
	
    VoterProbe *probe = new VoterProbe(VG);
    for (std::set<VoterNode*>::iterator it = VG->nodeSet->begin(); it != VG->nodeSet->end(); ++it) { probe->addNode(*it); }	
    VoterMeasurement *m = new VoterMeasurement(VG,"M");
    m->addProbe(probe,MACRO_STATE);
    Partition *p = VG->getMarkovPartition(m);

    VoterProbe *aprobe = new VoterProbe(VG);
    aprobe->addNode(*VG->nodeSet->begin());	
    VoterMeasurement *am = new VoterMeasurement(VG,"AM");
    am->addProbe(aprobe,MACRO_STATE);
    Partition *ap = VG->getMarkovPartition(am);

    std::set<OrderedPartition*> *pSet = MP->getOptimalOrderedPartition (ap,p,1,0,0.00001);
    for (std::set<OrderedPartition*>::iterator it = pSet->begin(); it != pSet->end(); ++it)
    {
	std::cout << (*it)->string << std::endl;
    }
}


void testLandUseModel ()
{
	double quality [2] = {1, 2};
	double breaks [2] = {1.5, 1.9};
	double gamma = 1./3;
		
	int sizeMin = 3;
	int sizeMax = 3;

	bool saveData = false;
	bool newData = false;
	std::string fileName = "../data/landuse_flow.csv";


	std::ofstream file;

	if (saveData)
	{
		if (newData) { deleteCSV(fileName); }	
		openOutputCSV(file,fileName);	

		if (newData)
		{
			addCSVField(file,"SIZE");
			addCSVField(file,"HY");
			addCSVField(file,"IYpY");
			addCSVField(file,"HYpY");
			addCSVField(file,"HYpX");
			addCSVField(file,"FLOW",false);
			endCSVLine(file);
		}
	}

	std::cout << "SIZE     H(Y)     I(Y;Y')     H(Y'|Y)     H(Y'|X)     FLOW"  << std::endl;

	
	for (int s = sizeMin; s <= sizeMax; s++)
	{
		int agentNb = s;
		int size = pow(agentNb+1,2);

		MarkovProcess *MP = new MarkovProcess (size);

		for (int i = 0; i < size; i++)
		{
			int i01 = i % (agentNb+1);
			int i11 = (i-i01) / (agentNb+1);

			double prob0 = nChoosek(agentNb,i01) * pow(0.5,agentNb);
			double prob1 = nChoosek(agentNb,i11) * pow(0.5,agentNb);
		
			MP->distribution[i] = prob0 * prob1;
		}	

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				MP->transition[j*size+i] = 0;

		for (int i = 0; i < size; i++)
		{
			int i01 = i % (agentNb+1);
			int i11 = (i-i01) / (agentNb+1);
			int i00 = agentNb - i01;
			int i10 = agentNb - i11;

			int q = i01 * quality[0] + i11 * quality[1];
			bool d0 = (q < breaks[0] * agentNb);
			bool d1 = (q < breaks[1] * agentNb);

			for (int d00 = 0; d00 <= i00; d00++)
			{
				double prob00 = nChoosek(i00,d00) * pow(gamma,d00) * pow(1.-gamma,i00-d00);

				for (int d01 = 0; d01 <= i01; d01++)
				{
					double prob01 = nChoosek(i01,d01) * pow(gamma,d01) * pow(1.-gamma,i01-d01);

					for (int d10 = 0; d10 <= i10; d10++) {
						double prob10 = nChoosek(i10,d10) * pow(gamma,d10) * pow(1.-gamma,i10-d10);

						for (int d11 = 0; d11 <= i11; d11++)
						{
							double prob11 = nChoosek(i11,d11) * pow(gamma,d11) * pow(1.-gamma,i11-d11);

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

		MP->computeStationaryDistribution(0.00001);
		
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

		MP->print();
		partition->print(true);

		int time = -1;
		int delay = 1;
		
		double H = MP->getEntropy(partition,time);
		double I = MP->getMutualInformation(partition,partition,delay,time);
		double H1 = MP->getNextEntropy(partition,false,delay,time);
		double H2 = MP->getNextEntropy(partition,true,delay,time);
		double F = H1-H2;

		if (saveData)
		{
			addCSVField(file,agentNb);
			addCSVField(file,H);
			addCSVField(file,I);
			addCSVField(file,H1);
			addCSVField(file,H2);
			addCSVField(file,F,false);
			endCSVLine(file);
		}

		std::cout << agentNb << "     " << H << "     " << I << "     " << H1 << "     " << H2 << "     " << F << std::endl;
		
		
		delete partition;
		delete MP;
	}

	closeOutputCSV(file);
	
}
