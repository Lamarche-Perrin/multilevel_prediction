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
	
	std::set<MeasurementType>* preM = new std::set<MeasurementType>();
//	preM->insert(M_MICRO);
//	preM->insert(M_ALLSIZES1);
	preM->insert(M_MACRO);
	preM->insert(M_EMPTY);
	preM->insert(M_AGENT1);
	preM->insert(M_MESO1);
	preM->insert(M_MESO2);
	preM->insert(M_AGENT1_MESO1);
	preM->insert(M_AGENT1_MESO2);
	preM->insert(M_AGENT1_MESO1_MESO2);
	preM->insert(M_AGENT1_MACRO);
	preM->insert(M_MESO1);
	preM->insert(M_MESO2);
	preM->insert(M_MESO1_MESO2);
	preM->insert(M_MACRO);
	
	std::set<MeasurementType>* postM = new std::set<MeasurementType>();
	postM->insert(M_AGENT1);

	VoterExperiment *exp;
	exp = new VoterExperiment(10,10,1,1,1,1,0,0,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1./21,1./21,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1./21,0,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,0,1./21,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1,1,-1,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

	exp = new VoterExperiment(10,10,1,1,1,1,1./21,1./21,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1./21,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,0,1./21,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1,1,1,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; expSet->insert(exp);

/*
	exp = new VoterExperiment(10,10,1,1,1,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);

	exp = new VoterExperiment(10,10,1,1,2,2,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,3,3,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,4,4,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,5,5,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,10,10,0,0,0); exp->delayMax = 100; expSet.insert(exp);

	exp = new VoterExperiment(10,10,1,1,1./2,1./2,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./3,1./3,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./4,1./4,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./5,1./5,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./10,1./10,0,0,0); exp->delayMax = 100; expSet.insert(exp);

	exp = new VoterExperiment(10,10,1,1,2,1./2,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,3,1./3,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,4,1./4,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,5,1./5,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,10,1./10,0,0,0); exp->delayMax = 100; expSet.insert(exp);

	exp = new VoterExperiment(10,10,1,1,1./2,2,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./3,3,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./4,4,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./5,5,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./10,10,0,0,0); exp->delayMax = 100; expSet.insert(exp);

	exp = new VoterExperiment(10,10,1,1,1,2,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,3,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,4,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,5,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,10,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	
	exp = new VoterExperiment(10,10,1,1,2,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,3,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,4,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,5,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,10,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);

	exp = new VoterExperiment(10,10,1,1,1,1./2,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./3,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./4,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./5,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1,1./10,0,0,0); exp->delayMax = 100; expSet.insert(exp);

	exp = new VoterExperiment(10,10,1,1,1./2,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./3,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./4,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./5,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
	exp = new VoterExperiment(10,10,1,1,1./10,1,0,0,0); exp->delayMax = 100; expSet.insert(exp);
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


