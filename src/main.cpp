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



    ExperimentSet *expSet = new ExperimentSet();
	
    SpecMeasurementSet* preM = new SpecMeasurementSet();

    preM->insert(std::make_pair(M_EMPTY,MACRO_STATE));
    preM->insert(std::make_pair(M_MACRO,MACRO_STATE));

    preM->insert(std::make_pair(M_AGENT1,MACRO_STATE));
    preM->insert(std::make_pair(M_AGENT1_MACRO,MACRO_STATE));
    
    preM->insert(std::make_pair(M_MICRO,MACRO_STATE));
    //preM->insert(std::make_pair(M_ALLSIZES1,MACRO_STATE));
    //preM->insert(std::make_pair(M_SOMESIZES1,MACRO_STATE));
    //preM->insert(std::make_pair(M_AGENT1_ALLSIZES1,MACRO_STATE));


    preM->insert(std::make_pair(M_MESO1,MACRO_STATE));
    preM->insert(std::make_pair(M_MESO2,MACRO_STATE));
    preM->insert(std::make_pair(M_AGENT1_MESO1,MACRO_STATE));
    preM->insert(std::make_pair(M_AGENT1_MESO2,MACRO_STATE));
    preM->insert(std::make_pair(M_AGENT1_MESO1_MESO2,MACRO_STATE));
    preM->insert(std::make_pair(M_MESO1,MACRO_STATE));
    preM->insert(std::make_pair(M_MESO2,MACRO_STATE));
    preM->insert(std::make_pair(M_MESO1_MESO2,MACRO_STATE));

    
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

    SpecMeasurementSet* postM = new SpecMeasurementSet();
    postM->insert(std::make_pair(M_AGENT1,MACRO_STATE));
    //postM->insert(std::make_pair(M_MACRO,MACRO_STATE));

    VoterExperiment *exp;

    //exp = new VoterExperiment(20,0,1,1,1,1,0,0,0,0,preM,postM); exp->delayMax = 100; exp->compactModel = true; exp->withAggregation = true; expSet->insert(exp);
    exp = new VoterExperiment(4,4,1,1,0.2,0.2,0,0,0,1,preM,postM); exp->timeMax = 50; expSet->insert(exp);
    //exp = new VoterExperiment(4,4,1,1,0.2,0.2,0,0,0,3,preM,postM); exp->timeMax = 100; expSet->insert(exp);
    //exp = new VoterExperiment(4,4,1,1,0.2,0.2,0,0,0,5,preM,postM); exp->timeMax = 100; expSet->insert(exp);multilevel_prediction/

    voterExperiment(expSet,"/home/robin/programming/multilevel_prediction/data/DATA.CSV");

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
