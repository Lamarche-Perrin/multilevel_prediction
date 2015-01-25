#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

#include "main.hpp"
#include "timer.hpp"
#include "voter_experiment.hpp"
#include "voter_graph.hpp"


bool VERBOSE = false;


int main(int argc, char *argv[]) {
	srand(time(NULL));

	ExperimentSet *expSet = new ExperimentSet();
	
	SpecMeasurementSet* preM = new SpecMeasurementSet();

//	preM->insert(std::make_pair(M_MACRO,MACRO_STATE));
//	preM->insert(std::make_pair(M_EMPTY,MACRO_STATE));
//	preM->insert(std::make_pair(M_AGENT1,MACRO_STATE));
//	preM->insert(std::make_pair(M_AGENT1_MACRO,MACRO_STATE));
//	preM->insert(std::make_pair(M_MACRO,MACRO_STATE));

//	preM->insert(std::make_pair(M_MICRO,MACRO_STATE));
//	preM->insert(std::make_pair(M_ALLSIZES1,MACRO_STATE));
//	preM->insert(std::make_pair(M_MESO1,MACRO_STATE));
//	preM->insert(std::make_pair(M_MESO2,MACRO_STATE));
//	preM->insert(std::make_pair(M_AGENT1_MESO1,MACRO_STATE));
//	preM->insert(std::make_pair(M_AGENT1_MESO2,MACRO_STATE));
//	preM->insert(std::make_pair(M_AGENT1_MESO1_MESO2,MACRO_STATE));
//	preM->insert(std::make_pair(M_MESO1,MACRO_STATE));
//	preM->insert(std::make_pair(M_MESO2,MACRO_STATE));
//	preM->insert(std::make_pair(M_MESO1_MESO2,MACRO_STATE));

/*
	preM->insert(std::make_pair(M_MACRO,MAJ_2B));
	preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_2B));

	preM->insert(std::make_pair(M_MACRO,MAJ_4B));
	preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_4B));

	preM->insert(std::make_pair(M_MACRO,MAJ_10B));
	preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_10B));

	preM->insert(std::make_pair(M_MACRO,MAJ_20B));
	preM->insert(std::make_pair(M_AGENT1_MACRO,MAJ_20B));
*/

	SpecMeasurementSet* postM = new SpecMeasurementSet();
	postM->insert(std::make_pair(M_AGENT1,MACRO_STATE));

	VoterExperiment *exp;

	exp = new VoterExperiment(10,10,1,1,1,1,0,0,0,0,preM,postM); exp->delayMax = 2; exp->compactModel = true; expSet->insert(exp);

//	exp = new VoterExperiment(8,0,1,1,1,1,1./21,1./21,-1,0,preM,postM); exp->delayMax = 30; exp->compactModel = false; expSet->insert(exp);
//	exp = new VoterExperiment(4,4,1,1,1,1,1./21,1./21,-1,0,preM,postM); exp->delayMax = 30; exp->compactModel = false; expSet->insert(exp);

/*
	exp = new VoterExperiment(10,10,1,1,1,1,0,0,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1./21,1./21,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1./21,0,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,0,1./21,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1,1,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,1,1,1./21,1./21,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1./21,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,0,1./21,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1,1,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
*/

/*
	double c = 1./21;

	exp = new VoterExperiment(10,10,1,1,1,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,2,2,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,3,3,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,4,4,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,5,5,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,10,10,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,1./2,1./2,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./3,1./3,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./4,1./4,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./5,1./5,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./10,1./10,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,2,1./2,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,3,1./3,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,4,1./4,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,5,1./5,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,10,1./10,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,1./2,2,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./3,3,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./4,4,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./5,5,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./10,10,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,1,2,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,3,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,4,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,5,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,10,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	
	exp = new VoterExperiment(10,10,1,1,2,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,3,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,4,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,5,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,10,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,1,1./2,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./3,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./4,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./5,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./10,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,1./2,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./3,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./4,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./5,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./10,1,c,c,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
*/

	voterExperiment(expSet,"../data/DATA.CSV");

	return EXIT_SUCCESS;
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


