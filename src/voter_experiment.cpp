/*!
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <math.h>

#include "voter_experiment.hpp"
#include "voter_graph.hpp"

#include "timer.hpp"
#include "csv_tools.hpp"



int TwoCommunitiesExperiment::id_number = 0;
int ChainExperiment::id_number = 0;


void twoCommunitiesExperiment (TwoCommunitiesExperimentSet *expSet, std::string fileName)
{
    addTwoCommunitiesHeaderToCSV(fileName);
    std::ofstream csvFile;
    openOutputCSV(csvFile,fileName);

    for (TwoCommunitiesExperimentSet::iterator it = expSet->begin(); it != expSet->end(); ++it)
    {
	TwoCommunitiesExperiment *exp = *it;
		

	// initialization

	Timer timer;
	std::cout << "===== EXP " << exp->id << " =====" << std::endl;
		

	// set the local variables according to the programmed experiment

	int update = exp->update;
	double threshold = exp->threshold;
	bool compactModel = exp->compactModel;
	bool withAggregation = exp->withAggregation;
	bool partDecomposition = exp->partDecomposition;

	double aggregationThreshold = 1e-10;
		
	int size1Min = exp->size1Min;	int size1Max = exp->size1Max;	int size1Step = exp->size1Step;
	int size2Min = exp->size2Min;	int size2Max = exp->size2Max;	int size2Step = exp->size2Step;
	bool equalSize = exp->equalSize;
	
	double intraR1Min = exp->intraR1Min;	double intraR1Max = exp->intraR1Max;	double intraR1Step = exp->intraR1Step;
	double intraR2Min = exp->intraR2Min;	double intraR2Max = exp->intraR2Max;	double intraR2Step = exp->intraR2Step;
	double interR1Min = exp->interR1Min;	double interR1Max = exp->interR1Max;	double interR1Step = exp->interR1Step;
	double interR2Min = exp->interR2Min;	double interR2Max = exp->interR2Max;	double interR2Step = exp->interR2Step;		
	bool equalIntraRate = exp->equalIntraRate;
	bool equalInterRate = exp->equalInterRate;
	bool oppositeInterRate = exp->oppositeInterRate;
	
	double contrarian1Min = exp->contrarian1Min; double contrarian1Max = exp->contrarian1Max; double contrarian1Step = exp->contrarian1Step;
	double contrarian2Min = exp->contrarian2Min; double contrarian2Max = exp->contrarian2Max; double contrarian2Step = exp->contrarian2Step;
	bool equalContrarian = exp->equalContrarian;
	
	int timeMin = exp->timeMin;		int timeMax = exp->timeMax;		int timeStep = exp->timeStep;
	int delayMin = exp->delayMin;	int delayMax = exp->delayMax;	int delayStep = exp->delayStep;
						
	std::string type = "GENERAL_MODEL";
	if (compactModel) { type = "COMPACT_MODEL"; }
	

	// loop over model parameters
			
	for (int size1 = size1Min; size1 <= size1Max; size1 += size1Step)
	    for (int size2 = size2Min; size2 <= size2Max; size2 += size2Step)
	    {
		for (double c1 = contrarian1Min; c1 <= contrarian1Max; c1 += contrarian1Step)
		    for (double c2 = contrarian2Min; c2 <= contrarian2Max; c2 += contrarian2Step)
		    {
			for (double intraRate1 = intraR1Min; intraRate1 <= intraR1Max; intraRate1 += intraR1Step)
			    for (double intraRate2 = intraR2Min; intraRate2 <= intraR2Max; intraRate2 += intraR2Step)
				for (double interRate1 = interR1Min; interRate1 <= interR1Max; interRate1 += interR1Step)
				    for (double interRate2 = interR2Min; interRate2 <= interR2Max; interRate2 += interR2Step)
				    {
					int s1 = size1; int s2 = size2;
					double intraR1 = intraRate1; double intraR2 = intraRate2;
					double interR1 = interRate1; double interR2 = interRate2;
					
					if (equalSize) { s2 = s1; }
					if (equalIntraRate) { intraR2 = intraR1; }
					if (equalInterRate) { interR2 = interR1; }
					if (oppositeInterRate) { interR2 = 1 - interR1; }
					if (equalContrarian) { c2 = c1; }
	
	
					// build the Voter Model and its Markov chain
					
					timer.start(s1+s2,"BUILDING MODEL");
					timer.startTime();
					timer.startMemory();


					TwoCommunitiesVoterGraph *VG = new TwoCommunitiesVoterGraph (s1,s2,intraR1,intraR2,interR1,interR2,c1,c2,update);


					MarkovProcess *MP;
					if (compactModel) { MP = VG->getCompactMarkovProcess(); } else { MP = VG->getMarkovProcess(); }
					MP->getDistribution(timeMax);
					MP->getTransition(delayMax);
					if (timeMin == -1) { MP->computeStationaryDistribution(threshold); }
					
					//					double *sd = MP->getDistribution(-1);
					//					for (int i = 0; i < MP->size; i++) { std::cout << sd[i] << "   "; }



					// build the pre- and post-measurements

					MeasurementSet *preMSet = new MeasurementSet();
					for (SpecMeasurementSet::iterator it = exp->preMeasurements->begin(); it != exp->preMeasurements->end(); ++it)
					{
					    MeasurementType type = (*it).first;
					    VoterMetric metric = (*it).second;
					    addMeasurement (preMSet,VG,type,metric);
					}

					
					for (MeasurementSet::iterator it = preMSet->begin(); it != preMSet->end(); ++it)
					{
					    VoterMeasurement *m = *it;
					    if (compactModel) { m->partition = VG->getCompactMarkovPartition(m); }
					    else { m->partition = VG->getMarkovPartition(m); }
					}

					MeasurementSet *postMSet = new MeasurementSet();
					for (SpecMeasurementSet::iterator it = exp->postMeasurements->begin(); it != exp->postMeasurements->end(); ++it)
					{
					    MeasurementType type = (*it).first;
					    VoterMetric metric = (*it).second;
					    addMeasurement (postMSet,VG,type,metric);
					}
					
					for (MeasurementSet::iterator it = postMSet->begin(); it != postMSet->end(); ++it)
					{
					    VoterMeasurement *m = *it;
					    if (compactModel) { m->partition = VG->getCompactMarkovPartition(m); }
					    else { m->partition = VG->getMarkovPartition(m); }
					}

	
					// build the microscopic partition
						
					Partition *microP;
					if (compactModel)
					{
					    VoterMeasurement *m = getMeasurement(VG, M_AGENT1_MESO1_MESO2, MACRO_STATE);
					    m->type = "MICRO_PARTITION";
					    microP = VG->getCompactMarkovPartition(m);
					}
					
					else {
					    VoterMeasurement *m = getMeasurement(VG, M_MICRO, MACRO_STATE);
					    m->type = "MICRO_PARTITION";
					    microP = VG->getMarkovPartition(m);
					}


					// loop over the prediction parameters
					
					for (int t = timeMin; t <= timeMax; t += timeStep)
					{	
					    for (int d = delayMin; d <= delayMax; d += delayStep)
					    {
						timer.step("COMPUTING " + int2string(t) + " + " + int2string(d));

						for (MeasurementSet::iterator it1 = preMSet->begin(); it1 != preMSet->end(); ++it1)
						{
						    VoterMeasurement *preM = *it1;
						    for (MeasurementSet::iterator it2 = postMSet->begin(); it2 != postMSet->end(); ++it2)
						    {
							VoterMeasurement *postM = *it2;

							// Run experiment
							if (partDecomposition)
							{
							    std::string name = type + "_size_" + int2string(s1) + "+" + int2string(s2)
								+ "_rate_" + double2string(interR1,2)
								+ "," + double2string(interR2,2)
								+ "_time_" + int2string(t) + "_delay_" + int2string(d) + "_" + preM->type + ".csv";
							    addTwoCommunitiesPartHeaderToCSV(name,preM->type);
							    std::ofstream file;
							    openOutputCSV(file,name);
    
							    computeTwoCommunitiesPartMeasures(file,MP,s1,s2,preM,postM,t,d);

							    closeOutputCSV(file);
							}

							else if (withAggregation)
							{
							    computeTwoCommunitiesMeasuresWithAggregation(csvFile,MP,type,update,s1,s2,
													 intraR1,intraR2,interR1,interR2,c1,c2,
													 preM,postM,t,d,aggregationThreshold);
							}

							else
							{
							    computeTwoCommunitiesMeasures(csvFile,MP,type,update,s1,s2,
											  intraR1,intraR2,interR1,interR2,c1,c2,preM,postM,t,d,microP);
							}
						    }
						}
					    }
					}
		
		
					// free memory
					 
					delete VG;
					delete MP;
					delete microP;
					
					preMSet->clear();
					postMSet->clear();
					delete preMSet;
					delete postMSet;
					
					timer.stopTime();
					timer.stopMemory();
					timer.stop();
				    }
		    }
	    }	       
    }

    closeOutputCSV(csvFile);
}



void chainExperiment (ChainExperimentSet *expSet, std::string fileName)
{		
    addTwoCommunitiesHeaderToCSV(fileName);
    std::ofstream csvFile;
    openOutputCSV(csvFile,fileName);

    for (ChainExperimentSet::iterator it = expSet->begin(); it != expSet->end(); ++it)
    {
	ChainExperiment *exp = *it;
		
	// initialization

	Timer timer;
	std::cout << "===== EXP " << exp->id << " =====" << std::endl;
	

	// set the local variables according to the programmed experiment

	int update = exp->update;
	bool ring = exp->ring;
	double threshold = exp->threshold;
	//bool withAggregation = exp->withAggregation;
	//double aggregationThreshold = 1e-10;
		
	int sizeMin = exp->sizeMin;	int sizeMax = exp->sizeMax;	int sizeStep = exp->sizeStep;

	double contrarianMin = exp->contrarianMin; double contrarianMax = exp->contrarianMax; double contrarianStep = exp->contrarianStep;
	
	int timeMin = exp->timeMin;		int timeMax = exp->timeMax;		int timeStep = exp->timeStep;
	int delayMin = exp->delayMin;	int delayMax = exp->delayMax;	int delayStep = exp->delayStep;
						
	std::string type = "CHAIN";
	if (ring) { type = "RING"; }
	

	// loop over model parameters
			
	for (int size = sizeMin; size <= sizeMax; size += sizeStep)
	    for (double c = contrarianMin; c <= contrarianMax; c += contrarianStep)
	    {	
	
		// build the Voter Model and its Markov chain
		
		timer.start(size,"BUILDING MODEL");
		timer.startTime();
		timer.startMemory();

		ChainVoterGraph *VG = new ChainVoterGraph (size,c,ring,update);

		MarkovProcess *MP = VG->getMarkovProcess();
		MP->getDistribution(timeMax);
		MP->getTransition(delayMax);
		if (timeMin == -1) { MP->computeStationaryDistribution(threshold); }
		

		// build the pre- and post-measurements
		
		MeasurementSet *preMSet = new MeasurementSet();
		for (SpecMeasurementSet::iterator it = exp->preMeasurements->begin(); it != exp->preMeasurements->end(); ++it)
		{
		    MeasurementType type = (*it).first;
		    VoterMetric metric = (*it).second;
		    addMeasurement (preMSet,VG,type,metric);
		}
		
		for (MeasurementSet::iterator it = preMSet->begin(); it != preMSet->end(); ++it)
		{
		    VoterMeasurement *m = *it;
		    m->partition = VG->getMarkovPartition(m);
		}

		MeasurementSet *postMSet = new MeasurementSet();
		for (SpecMeasurementSet::iterator it = exp->postMeasurements->begin(); it != exp->postMeasurements->end(); ++it)
		{
		    MeasurementType type = (*it).first;
		    VoterMetric metric = (*it).second;
		    addMeasurement (postMSet,VG,type,metric);
		}
					
		for (MeasurementSet::iterator it = postMSet->begin(); it != postMSet->end(); ++it)
		{
		    VoterMeasurement *m = *it;
		    m->partition = VG->getMarkovPartition(m);
		}
	

		// build the microscopic partition
		
		VoterMeasurement *m = new VoterMeasurement(VG,"MICRO_PARTITION");
		for (std::set<VoterNode*>::iterator it = VG->nodeSet->begin(); it != VG->nodeSet->end(); ++it)
		{
		    VoterProbe *probe = new VoterProbe(VG);
		    probe->addNode(*it);
		    m->addProbe(probe,MACRO_STATE);
		}
		
		Partition *microP = VG->getMarkovPartition(m);


		// loop over the prediction parameters
					
		for (int t = timeMin; t <= timeMax; t += timeStep)
		{	
		    for (int d = delayMin; d <= delayMax; d += delayStep)
		    {
			timer.step("COMPUTING " + int2string(t) + " + " + int2string(d));
			
			for (MeasurementSet::iterator it1 = preMSet->begin(); it1 != preMSet->end(); ++it1)
			{
			    VoterMeasurement *preM = *it1;
			    for (MeasurementSet::iterator it2 = postMSet->begin(); it2 != postMSet->end(); ++it2)
			    {
				VoterMeasurement *postM = *it2;
				
				// Run experiment
				computeTwoCommunitiesMeasures(csvFile,MP,type,update,size,0,0,0,0,0,c,0,preM,postM,t,d,microP);
			    }
			}
		    }
		}
		
		
		// free memory
		
		delete VG;
		delete MP;
		delete microP;
		
		preMSet->clear();
		postMSet->clear();
		delete preMSet;
		delete postMSet;
		
		timer.stopTime();
		timer.stopMemory();
		timer.stop();
	    }
    }
    closeOutputCSV(csvFile);
}



void addMeasurement (MeasurementSet *set, VoterGraph *VG, MeasurementType type, VoterMetric metric)
{
    switch (type)
    {
    case M_MACRO :
    case M_EMPTY :
    case M_AGENT1 :		
    case M_AGENT1_MACRO :
    case M_MICRO:
    case M_MESO1 :
    case M_MESO2 :
    case M_MESO1_MESO2 :
    case M_AGENT1_MESO1 :
    case M_AGENT1_MESO2 :
    case M_AGENT1_MESO1_MESO2 :
		set->insert(getMeasurement (VG, type, metric));
	break;

    default : addMultiMeasurement (set, VG, type, metric);
    }
}


VoterMeasurement *getMeasurement (VoterGraph *VG, MeasurementType type, VoterMetric metric, int binning)
{
    std::string postfix = "";
    switch (metric)
    {
    case MACRO_STATE :          postfix = "_MS";	break;
    case MAJORITY :		postfix = "_MAJ";	break;
    case MAJ_1PC :		postfix = "_1PC";	break;
    case MAJ_2PC :		postfix = "_2PC";	break;
    case MAJ_3PC :		postfix = "_3PC";	break;
    case MAJ_4PC :		postfix = "_4PC";	break;
    case MAJ_5PC :		postfix = "_5PC";	break;
    case MAJ_6PC :		postfix = "_6PC";	break;
    case MAJ_7PC :		postfix = "_7PC";	break;
    case MAJ_8PC :		postfix = "_8PC";	break;
    case MAJ_9PC :		postfix = "_9PC";	break;
    case MAJ_10PC :		postfix = "_10PC";	break;
    case MAJ_20PC :		postfix = "_20PC";	break;
    case MAJ_30PC :		postfix = "_30PC";	break;
    case MAJ_40PC :		postfix = "_40PC";	break;
    case MAJ_50PC :		postfix = "_50PC";	break;
    case MAJ_60PC :		postfix = "_60PC";	break;
    case MAJ_70PC :		postfix = "_70PC";	break;
    case MAJ_80PC :		postfix = "_80PC";	break;
    case MAJ_90PC :		postfix = "_90PC";	break;
    case MAJ_2B :		postfix = "_2B";	break;
    case MAJ_3B :		postfix = "_3B";	break;
    case MAJ_4B :		postfix = "_4B";	break;
    case MAJ_6B :		postfix = "_6B";	break;
    case MAJ_8B :		postfix = "_8B";	break;
    case MAJ_10B :		postfix = "_10B";	break;
    case MAJ_12B :		postfix = "_12B";	break;
    case MAJ_20B :		postfix = "_20B";	break;
    case MAJ_40B :		postfix = "_40B";	break;
    case ACTIVE_EDGES :	        postfix = "_AE";	break;
    default :			postfix = "_NA";	break;
    }

    // build probes
    TwoCommunitiesVoterGraph *TCVG = dynamic_cast<TwoCommunitiesVoterGraph*>(VG);
    ChainVoterGraph *CVG = dynamic_cast<ChainVoterGraph*>(VG);

    VoterProbe *macroPr = new VoterProbe(VG);
    for (std::set<VoterNode*>::iterator it = VG->nodeSet->begin(); it != VG->nodeSet->end(); ++it) { macroPr->addNode(*it); }

    VoterProbe *agent1Pr = new VoterProbe(VG);
    if (TCVG != NULL) { agent1Pr->addNode(*TCVG->community1->begin()); }
    if (CVG != NULL) { agent1Pr->addNode(CVG->nodeArray[0]); }

	VoterProbe *meso1Pr = new VoterProbe(VG);
	VoterProbe *meso2Pr = new VoterProbe(VG);							
	if (TCVG != NULL)
	{
		for (std::set<VoterNode*>::iterator it = TCVG->community1->begin(); it != TCVG->community1->end(); ++it) { meso1Pr->addNode(*it); }
		for (std::set<VoterNode*>::iterator it = TCVG->community2->begin(); it != TCVG->community2->end(); ++it) { meso2Pr->addNode(*it); }
	}
    
    switch (type)
    {
    case M_MACRO :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"MACRO" + postfix);
	m->addProbe(macroPr,metric,binning);
	return m;
    }
		
    case M_EMPTY :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"EMPTY");
	return m;
    }
		
    case M_AGENT1 :		
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1" + postfix);
	m->addProbe(agent1Pr,metric,binning);
	return m;
    }

    case M_AGENT1_MACRO :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MACRO" + postfix);
	m->addProbe(agent1Pr,metric,binning);
	m->addProbe(macroPr,metric,binning);
	return m;
    }
		
    case M_MICRO:
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"MICRO" + postfix);
	for (std::set<VoterNode*>::iterator it = VG->nodeSet->begin(); it != VG->nodeSet->end(); ++it)
	{
	    VoterProbe *probe = new VoterProbe(VG);
	    probe->addNode(*it);
	    m->addProbe(probe,metric,binning);
	}
	return m;
    }
		
    case M_MESO1 :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"MESO1" + postfix);
	m->addProbe(meso1Pr,metric,binning);
	return m;
    }

    case M_MESO2 :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"MESO2" + postfix);
	m->addProbe(meso2Pr,metric,binning);
	return m;
    }

    case M_MESO1_MESO2 :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"MESO1_MESO2" + postfix);
	m->addProbe(meso1Pr,metric,binning);
	m->addProbe(meso2Pr,metric,binning);
	return m;
    }
			
    case M_AGENT1_MESO1 :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MESO1" + postfix);
	m->addProbe(agent1Pr,metric,binning);
	m->addProbe(meso1Pr,metric,binning);
	return m;
    }

    case M_AGENT1_MESO2 :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MESO2" + postfix);
	m->addProbe(agent1Pr,metric,binning);
	m->addProbe(meso2Pr,metric,binning);
	return m;
    }
			
    case M_AGENT1_MESO1_MESO2 :
    {
	VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MESO1_MESO2" + postfix);
	m->addProbe(meso1Pr,metric,binning);
	m->addProbe(meso2Pr,metric,binning);
	m->addProbe(agent1Pr,metric,binning);
	return m;
    }
    	    
    default : std::cout << "ERROR: unknown measurement!" << std::endl;
    }

    return 0;
}


void addMultiMeasurement (MeasurementSet *set, VoterGraph *VG, MeasurementType type, VoterMetric metric)
{
    std::string postfix = "";
    switch (metric)
    {
    case MACRO_STATE :          postfix = "_MS";	break;
    case MAJORITY :		postfix = "_MAJ";	break;
    case MAJ_1PC :		postfix = "_1PC";	break;
    case MAJ_2PC :		postfix = "_2PC";	break;
    case MAJ_3PC :		postfix = "_3PC";	break;
    case MAJ_4PC :		postfix = "_4PC";	break;
    case MAJ_5PC :		postfix = "_5PC";	break;
    case MAJ_6PC :		postfix = "_6PC";	break;
    case MAJ_7PC :		postfix = "_7PC";	break;
    case MAJ_8PC :		postfix = "_8PC";	break;
    case MAJ_9PC :		postfix = "_9PC";	break;
    case MAJ_10PC :		postfix = "_10PC";	break;
    case MAJ_20PC :		postfix = "_20PC";	break;
    case MAJ_30PC :		postfix = "_30PC";	break;
    case MAJ_40PC :		postfix = "_40PC";	break;
    case MAJ_50PC :		postfix = "_50PC";	break;
    case MAJ_60PC :		postfix = "_60PC";	break;
    case MAJ_70PC :		postfix = "_70PC";	break;
    case MAJ_80PC :		postfix = "_80PC";	break;
    case MAJ_90PC :		postfix = "_90PC";	break;
    case MAJ_2B :		postfix = "_2B";	break;
    case MAJ_3B :		postfix = "_3B";	break;
    case MAJ_4B :		postfix = "_4B";	break;
    case MAJ_6B :		postfix = "_6B";	break;
    case MAJ_8B :		postfix = "_8B";	break;
    case MAJ_10B :		postfix = "_10B";	break;
    case MAJ_12B :		postfix = "_12B";	break;
    case MAJ_20B :		postfix = "_20B";	break;
    case MAJ_40B :		postfix = "_40B";	break;
    case ACTIVE_EDGES :	        postfix = "_AE";	break;
    default :			postfix = "_NA";	break;
    }

    // build probes
    TwoCommunitiesVoterGraph *TCVG = dynamic_cast<TwoCommunitiesVoterGraph*>(VG);
    ChainVoterGraph *CVG = dynamic_cast<ChainVoterGraph*>(VG);

    VoterProbe *macroPr = new VoterProbe(VG);
    for (std::set<VoterNode*>::iterator it = VG->nodeSet->begin(); it != VG->nodeSet->end(); ++it) { macroPr->addNode(*it); }

    VoterProbe *agent1Pr = new VoterProbe(VG);
    if (TCVG != NULL) { agent1Pr->addNode(*TCVG->community1->begin()); }
    if (CVG != NULL) { agent1Pr->addNode(CVG->nodeArray[0]); }

    VoterProbe *meso1Pr = new VoterProbe(VG);
    for (std::set<VoterNode*>::iterator it = TCVG->community1->begin(); it != TCVG->community1->end(); ++it) { meso1Pr->addNode(*it); }

    VoterProbe *meso2Pr = new VoterProbe(VG);							
    for (std::set<VoterNode*>::iterator it = TCVG->community2->begin(); it != TCVG->community2->end(); ++it) { meso2Pr->addNode(*it); }

    
    switch (type)
    {
    case M_ALLSIZES1 : case M_SOMESIZES1 : case M_AGENT1_ALLSIZES1 : case M_AGENT1_SOMESIZES1 :
    {
	std::set<VoterNode*> *nodeSet = VG->nodeSet;
	TwoCommunitiesVoterGraph *TCVG = dynamic_cast<TwoCommunitiesVoterGraph*>(VG);
	if (TCVG != NULL) { nodeSet = TCVG->community1; }
	int size = VG->nodeSet->size();
	
	VoterProbe **prList = new VoterProbe *[size-1];
	VoterMeasurement **mList = new VoterMeasurement *[size-1];

	for (int i = 1; i <= size; i++)
	{
	    std::string str = int2string(i);

	    std::string prefix = "";
	    if (type == M_AGENT1_ALLSIZES1 || type == M_AGENT1_SOMESIZES1) { prefix = "AGENT1_"; }	    
	    
	    prList[i-1] = new VoterProbe(VG);
	    mList[i-1] = new VoterMeasurement(VG,prefix + "SIZE" + str + postfix);
	    mList[i-1]->addProbe(prList[i-1],metric);
				
	    if (type == M_AGENT1_ALLSIZES1 || type == M_AGENT1_SOMESIZES1) { mList[i-1]->addProbe(agent1Pr,metric); }
				
	    switch (type)
	    {
	    case M_ALLSIZES1 : case M_AGENT1_ALLSIZES1 : set->insert(mList[i-1]); break;
	    case M_SOMESIZES1 : case M_AGENT1_SOMESIZES1 : if (i % (size/5) == 0) { set->insert(mList[i-1]); } break;	
	    default : break;
	    }
	}
	
	int j = 1;
	
	for (std::set<VoterNode*>::iterator it = nodeSet->begin(); it != nodeSet->end(); ++it)
	{
	    for (int i = j; i <= size; i++) { prList[i-1]->addNode(*it); }
	    j++;
	}

	//delete [] prList;
	//delete [] mList;

	break;
    }


    case M_ALLNEIGHBORHOODS :
    {
	ChainVoterGraph *CVG = dynamic_cast<ChainVoterGraph*>(VG);
	if (CVG != NULL)
	{
	    if (CVG->ring)
	    {
		int size = CVG->size;
		VoterProbe **prList = new VoterProbe *[size/2];
		VoterMeasurement **mList = new VoterMeasurement *[size/2];
		
		for (int i = 1; i <= size/2; i++)
		{
		    std::stringstream ss; ss << i;
		    std::string str = ss.str();
		
		    prList[i-1] = new VoterProbe(VG);
		    prList[i-1]->addNode(CVG->nodeArray[0]);
		    for (int j = 1; j <= i; j++)
		    {
			prList[i-1]->addNode(CVG->nodeArray[j]);
			prList[i-1]->addNode(CVG->nodeArray[size-j]);
		    }

		    mList[i-1] = new VoterMeasurement(VG,"NEIGHBORHOOD" + str + postfix);
		    mList[i-1]->addProbe(prList[i-1],metric);
		    set->insert(mList[i-1]);
		}
	    
		delete [] prList;
		delete [] mList;
	    }
	}
	break;
    }
	    
    default : std::cout << "ERROR: unknown measurement!" << std::endl;
    }
}

		

void addTwoCommunitiesHeaderToCSV (std::string fileName)
{
    std::ifstream testFile;
    openInputCSV(testFile,fileName);
    bool emptyFile = isInputCSVEmpty(testFile);
    closeInputCSV(testFile);
	
    if (emptyFile)
    {
	std::ofstream csvFile;
	openOutputCSV(csvFile,fileName);

	CSVLine line;
	line.push_back("TYPE");
	line.push_back("UPDATE");
	line.push_back("SIZE1");
	line.push_back("SIZE2");
	line.push_back("INTRARATE1");
	line.push_back("INTRARATE2");
	line.push_back("INTERRATE1");
	line.push_back("INTERRATE2");
	line.push_back("CONTRARIAN1");
	line.push_back("CONTRARIAN2");

	line.push_back("PREM");
	line.push_back("POSTM");
	line.push_back("TIME");
	line.push_back("DELAY");

	line.push_back("CURRENT_MICRO_H");
	line.push_back("CURRENT_MACRO_H");
	line.push_back("NEXT_MICRO_H");
	line.push_back("NEXT_MACRO_H");
		
	line.push_back("MICRO_I");
	line.push_back("MACRO_I");
	line.push_back("CURRENT_I");
	line.push_back("NEXT_I");

	addCSVLine(csvFile,line);

	closeOutputCSV(csvFile);
    }
}


void computeTwoCommunitiesMeasures (std::ofstream &csvFile, MarkovProcess *MP, std::string type, int update,
				    int size1, int size2, double intraR1, double intraR2, double interR1, double interR2, double contrarian1, double contrarian2,
				    VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay, Partition *microP)
{
    addCSVField(csvFile,type);

    switch (update)
    {
    case UPDATE_NODES : addCSVField(csvFile,"NODES"); break;
    case UPDATE_EDGES : addCSVField(csvFile,"EDGES"); break;
    default : addCSVField(csvFile,"NA");
    }

    addCSVField(csvFile,size1);
    addCSVField(csvFile,size2);
    addCSVField(csvFile,intraR1);
    addCSVField(csvFile,intraR2);
    addCSVField(csvFile,interR1);
    addCSVField(csvFile,interR2);
    addCSVField(csvFile,contrarian1);
    addCSVField(csvFile,contrarian2);
	
    addCSVField(csvFile,preM->type);
    addCSVField(csvFile,postM->type);
    addCSVField(csvFile,time);
    addCSVField(csvFile,delay);

    int nextTime = time + delay;
    if (time == -1) { nextTime = -1; }
		
    double currentMicroH = MP->getEntropy(microP,time);
    double currentMacroH = MP->getEntropy(preM->partition,time);
    double nextMicroH = MP->getEntropy(microP,nextTime);
    double nextMacroH = MP->getEntropy(postM->partition,nextTime);
	
    double microI = MP->getMutualInformation(microP,microP,delay,time);
    double macroI = MP->getMutualInformation(postM->partition,preM->partition,delay,time);
    double currentI = MP->getMutualInformation(preM->partition,microP,0,time);
    double nextI = MP->getMutualInformation(postM->partition,microP,0,nextTime);

    if (currentI > 1.0e-10 && currentMacroH > 1.0e-10 && abs(currentI/currentMacroH - 1) > 1.0e-10)
    { std::cout << "ERROR! currentI = " << currentI << " and currentMacroH = " << currentMacroH << std::endl; }
	
    if (nextI > 1.0e-10 && nextMacroH > 1.0e-10 && abs(nextI/nextMacroH - 1) > 1.0e-10)
    { std::cout << "ERROR! nextI = " << nextI << " and nextMacroH = " << nextMacroH << std::endl; }
	
    addCSVField(csvFile,currentMicroH,true,15);
    addCSVField(csvFile,currentMacroH,true,15);
    addCSVField(csvFile,nextMicroH,true,15);
    addCSVField(csvFile,nextMacroH,true,15);
	
    addCSVField(csvFile,microI,true,15);
    addCSVField(csvFile,macroI,true,15);
    addCSVField(csvFile,currentI,true,15);
    addCSVField(csvFile,nextI,false,15);
	
    endCSVLine(csvFile);
}


void computeTwoCommunitiesMeasuresWithAggregation (std::ofstream &csvFile, MarkovProcess *MP, std::string type, int update,
						   int size1, int size2, double intraR1, double intraR2, double interR1, double interR2, double contrarian1, double contrarian2,
						   VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay, double threshold)
{
    std::set<OrderedPartition*> *pSet = MP->getOptimalOrderedPartition(postM->partition,preM->partition,delay,time,threshold);
    for (std::set<OrderedPartition*>::iterator it = pSet->begin(); it != pSet->end(); ++it)
    {
	OrderedPartition *p = *it;
	addCSVField(csvFile,type);
		
	switch (update)
	{
	case UPDATE_NODES : addCSVField(csvFile,"NODES"); break;
	case UPDATE_EDGES : addCSVField(csvFile,"EDGES"); break;
	default : addCSVField(csvFile,"NA");
	}
	
	addCSVField(csvFile,size1);
	addCSVField(csvFile,size2);
	addCSVField(csvFile,intraR1);
	addCSVField(csvFile,intraR2);
	addCSVField(csvFile,interR1);
	addCSVField(csvFile,interR2);
	addCSVField(csvFile,contrarian1);
	addCSVField(csvFile,contrarian2);
		
	addCSVField(csvFile,preM->type + "_" + p->string);
	addCSVField(csvFile,postM->type);
	addCSVField(csvFile,time);
	addCSVField(csvFile,delay);
	
	addCSVField(csvFile,"NA",true);
	addCSVField(csvFile,"NA",true);
	addCSVField(csvFile,"NA",true);
	addCSVField(csvFile,"NA",true);
		
	addCSVField(csvFile,"NA",true);
	addCSVField(csvFile,p->information,true,15);
	addCSVField(csvFile,p->entropy,true,15);
	addCSVField(csvFile,"NA",false);
	
	endCSVLine(csvFile);
    }
}



void addTwoCommunitiesPartHeaderToCSV (std::string fileName, std::string type)
{
    std::ifstream testFile;
    openInputCSV(testFile,fileName);
    bool emptyFile = isInputCSVEmpty(testFile);
    closeInputCSV(testFile);
	
    if (emptyFile)
    {
	std::ofstream csvFile;
	openOutputCSV(csvFile,fileName);

	CSVLine line;
	if (type == "AGENT1_MESO1_MESO2_MS")
	{
	    line.push_back("AGENT");
	    line.push_back("MESO1");
	    line.push_back("MESO2");
	}

	if (type == "MESO1_MS")
	{
	    line.push_back("MESO1");
	}

	if (type == "AGENT1_MACRO_MS")
	{
	    line.push_back("AGENT");
	    line.push_back("MACRO");
	}

	line.push_back("PROBABILITY");
	line.push_back("INFORMATION");

	addCSVLine(csvFile,line);

	closeOutputCSV(csvFile);
    }
}


void computeTwoCommunitiesPartMeasures (std::ofstream &csvFile, MarkovProcess *MP, int size1, int size2,
					VoterMeasurement *preM, VoterMeasurement *postM, int time, int delay)
{
    for (std::list<Part*>::iterator it = preM->partition->parts->begin(); it != preM->partition->parts->end(); ++it)
    {
	Part *part = *it;
	int i = part->individuals->front();

	int a = i % 2;
	int n1 = (i-a)/2 % size1;
	int n2 = (i-a-2*n1)/(2*size1);

	if (preM->type == "AGENT1_MESO1_MESO2_MS")
	{
	    addCSVField(csvFile,a);
	    addCSVField(csvFile,a+n1);
	    addCSVField(csvFile,n2);
	}

	if (preM->type == "MESO1_MS")
	{
	    addCSVField(csvFile,a+n1);
	}

	if (preM->type == "AGENT1_MACRO_MS")
	{
	    addCSVField(csvFile,a);
	    addCSVField(csvFile,a+n1+n2);
	}

	double probability = MP->getProbability(part,time);
	double information = MP->getPartMutualInformation(postM->partition,part,delay,time);

	addCSVField(csvFile,probability,true,15);
	addCSVField(csvFile,information,false,15);
	
	endCSVLine(csvFile);
    }
}



TwoCommunitiesExperiment::TwoCommunitiesExperiment (int size1, int size2, double intraR1, double intraR2, double interR1, double interR2,
						    double contrarian1, double contrarian2, double time, double delay, SpecMeasurementSet *preM, SpecMeasurementSet *postM)
{
    id = ++id_number;
    update = UPDATE_EDGES;
    threshold = 1.0e-10;
    compactModel = false;
    withAggregation = false;
    partDecomposition = false;
		
    size1Min = size1;	size1Max = size1;	size1Step = 1;
    size2Min = size2;	size2Max = size2;	size2Step = 1;
    equalSize = false;
	
    intraR1Min = intraR1;	intraR1Max = intraR1;	intraR1Step = 1;
    intraR2Min = intraR2;	intraR2Max = intraR2;	intraR2Step = 1;
    interR1Min = interR1;	interR1Max = interR1;	interR1Step = 0.1;
    interR2Min = interR2;	interR2Max = interR2;	interR2Step = 0.1;
    equalIntraRate = false;
    equalInterRate = false;
    oppositeInterRate = false;
		
    contrarian1Min = contrarian1; contrarian1Max = contrarian1;	contrarian1Step = 0.1;
    contrarian2Min = contrarian2; contrarian2Max = contrarian2;	contrarian2Step = 0.1;
    equalContrarian = false;
	
    timeMin = time;		timeMax = time;		timeStep = 1;
    delayMin = delay;	delayMax = delay;	delayStep = 1;
	
    preMeasurements = preM;
    postMeasurements = postM;
}



ChainExperiment::ChainExperiment (int size, double contrarian, bool r, double time, double delay, SpecMeasurementSet *preM, SpecMeasurementSet *postM)
{
    id = ++id_number;
    update = UPDATE_EDGES;
    threshold = 1.0e-10;
    withAggregation = false;
    ring = r;
		
    sizeMin = size;	sizeMax = size;	sizeStep = 1;
    contrarianMin = contrarian; contrarianMax = contrarian;	contrarianStep = 0.1;
	
    timeMin = time;		timeMax = time;		timeStep = 1;
    delayMin = delay;	delayMax = delay;	delayStep = 1;
	
    preMeasurements = preM;
    postMeasurements = postM;
}

