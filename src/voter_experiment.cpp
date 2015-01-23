#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

#include "voter_experiment.hpp"
#include "voter_graph.hpp"

#include "timer.hpp"
#include "csv_tools.hpp"


VoterProbe *macroPr;
VoterProbe *agent1Pr;
VoterProbe *meso1Pr;
VoterProbe *meso2Pr;

int VoterExperiment::id_number = 0;

void voterExperiment (ExperimentSet *expSet, std::string fileName)
{
	for (ExperimentSet::iterator it = expSet->begin(); it != expSet->end(); ++it)
	{
		VoterExperiment *exp = *it;
		

		// initialization

		Timer timer;
		std::cout << "===== EXP " << exp->id << " =====" << std::endl;
		
		addHeaderToCSV(fileName);
		std::ofstream csvFile;
		openOutputCSV(csvFile,fileName);
	

		// set the local variables according to the programmed experiment

		int update = exp->update;
		double threshold = exp->threshold;
		
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
	
		double contrarianMin = exp->contrarianMin; double contrarianMax = exp->contrarianMax; double contrarianStep = exp->contrarianStep;
	
		int timeMin = exp->timeMin;		int timeMax = exp->timeMax;		int timeStep = exp->timeStep;
		int delayMin = exp->delayMin;	int delayMax = exp->delayMax;	int delayStep = exp->delayStep;
		
		bool compactModel = exp->compactModel;
				
		std::string type = "GENERAL_MODEL";
		if (compactModel) { std::string type = "COMPACT_MODEL"; }
	

		// loop over model parameters
			
		for (int size1 = size1Min; size1 <= size1Max; size1 += size1Step)
		{
			for (int size2 = size2Min; size2 <= size2Max; size2 += size2Step)
			{
				for (double c = contrarianMin; c <= contrarianMax; c += contrarianStep)
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
		
		
						// build the Voter Model and its Markov chain
						
						timer.start(s1+s2,"BUILDING MODEL");
						timer.startTime();
						timer.startMemory();
	
						TwoCommunitiesVoterGraph *VG = new TwoCommunitiesVoterGraph (s1,s2,intraR1,intraR2,interR1,interR2,c,update);
		
						MarkovProcess *MP;
						if (compactModel) { MP = VG->getCompactMarkovProcess(); } else { MP = VG->getMarkovProcess(); }
						MP->getDistribution(timeMax);
						MP->getTransition(delayMax);
						if (timeMin == -1) { MP->computeStationaryDistribution(threshold); }


						// build the observation probes
						
						std::set<VoterMetric> MS;				
						MS.insert(MACRO_STATE);

						macroPr = new VoterProbe(VG);
						for (std::set<VoterNode*>::iterator it = VG->nodeSet->begin(); it != VG->nodeSet->end(); ++it) { macroPr->addNode(*it); }

						agent1Pr = new VoterProbe(VG);
						agent1Pr->addNode(*VG->community1->begin());
	
						meso1Pr = new VoterProbe(VG);
						for (std::set<VoterNode*>::iterator it = VG->community1->begin(); it != VG->community1->end(); ++it) { meso1Pr->addNode(*it); }

						meso2Pr = new VoterProbe(VG);							
						for (std::set<VoterNode*>::iterator it = VG->community2->begin(); it != VG->community2->end(); ++it) { meso2Pr->addNode(*it); }
	
						
						// build the pre- and post-measurements

						MeasurementSet *preMSet = new MeasurementSet();
						for (std::set<MeasurementType>::iterator it = exp->preMeasurements->begin(); it != exp->preMeasurements->end(); ++it) { addMeasurement (*it,preMSet,VG); }
						for (MeasurementSet::iterator it = preMSet->begin(); it != preMSet->end(); ++it)
						{
							VoterMeasurement *m = *it;
							if (compactModel) { m->partition = VG->getCompactMarkovPartition(m); }
							else { m->partition = VG->getMarkovPartition(m); }
						}

						MeasurementSet *postMSet = new MeasurementSet();
						for (std::set<MeasurementType>::iterator it = exp->postMeasurements->begin(); it != exp->postMeasurements->end(); ++it) { addMeasurement (*it,postMSet,VG); }
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
							VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MESO1_MESO2_MS");
							m->addProbe(meso1Pr,MACRO_STATE);
							m->addProbe(meso2Pr,MACRO_STATE);
							m->addProbe(agent1Pr,MACRO_STATE);
							microP = VG->getCompactMarkovPartition(m);
						}
						
						else {
							VoterMeasurement *m = new MicroVoterMeasurement(VG,MS);
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
																				
										// run experiment
										addLineToCSV(csvFile,MP,type,update,s1,s2,intraR1,intraR2,interR1,interR2,c,preM,postM,t,d,microP);
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
}


void addMeasurement (MeasurementType measurement, MeasurementSet *set, VoterGraph *VG)
{
	switch (measurement)
	{
		case M_MACRO :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"MACRO_MS");
			m->addProbe(macroPr,MACRO_STATE);
			set->insert(m);
			break;
		}
		
		case M_EMPTY :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"EMPTY");
			set->insert(m);
			break;
		}
		
		case M_AGENT1 :		
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MS");
			m->addProbe(agent1Pr,MACRO_STATE);
			set->insert(m);
			break;
		}

		case M_AGENT1_MACRO :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MACRO_MS");
			m->addProbe(agent1Pr,MACRO_STATE);
			m->addProbe(macroPr,MACRO_STATE);
			set->insert(m);
			break;
		}
		
		case M_MICRO:
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"MICRO_MS");
			for (std::set<VoterNode*>::iterator it = VG->nodeSet->begin(); it != VG->nodeSet->end(); ++it)
			{
				VoterProbe *probe = new VoterProbe(VG);
				probe->addNode(*it);
				m->addProbe(probe,MACRO_STATE);
			}
			set->insert(m);
			break;
		}
		
		case M_MESO1 :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"MESO1_MS");
			m->addProbe(meso1Pr,MACRO_STATE);
			set->insert(m);
			break;
		}

		case M_MESO2 :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"MESO2_MS");
			m->addProbe(meso2Pr,MACRO_STATE);
			set->insert(m);
			break;
		}

		case M_MESO1_MESO2 :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"MESO1_MESO2_MS");
			m->addProbe(meso1Pr,MACRO_STATE);
			m->addProbe(meso2Pr,MACRO_STATE);
			set->insert(m);
			break;
		}
			
		case M_AGENT1_MESO1 :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MESO1_MS");
			m->addProbe(agent1Pr,MACRO_STATE);
			m->addProbe(meso1Pr,MACRO_STATE);
			set->insert(m);
			break;
		}

		case M_AGENT1_MESO2 :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MESO2_MS");
			m->addProbe(agent1Pr,MACRO_STATE);
			m->addProbe(meso2Pr,MACRO_STATE);
			set->insert(m);
			break;
		}
			
		case M_AGENT1_MESO1_MESO2 :
		{
			VoterMeasurement *m = new VoterMeasurement(VG,"AGENT1_MESO1_MESO2_MS");
			m->addProbe(meso1Pr,MACRO_STATE);
			m->addProbe(meso2Pr,MACRO_STATE);
			m->addProbe(agent1Pr,MACRO_STATE);
			set->insert(m);
			break;
		}
		
		case M_ALLSIZES1 :
		{
			TwoCommunitiesVoterGraph *TCVG = (TwoCommunitiesVoterGraph*) VG;
			int s1 = TCVG->size1;
			
			VoterProbe **prList = new VoterProbe *[s1-1];
			VoterMeasurement **mList = new VoterMeasurement *[s1-1];

			for (int i = 1; i < s1; i++)
			{
				std::stringstream ss;
				ss << i;
				std::string str = ss.str();
				prList[i-1] = new VoterProbe(TCVG);
				mList[i-1] = new VoterMeasurement(TCVG,"SIZE" + str + "_MS");
				set->insert(mList[i-1]);
			}
	
			int j = 1;
			
			std::set<VoterNode*>::iterator it = TCVG->community1->begin();
			it++;
			for (; it != TCVG->community1->end(); ++it)
			{
				for (int i = j; i < s1; i++) { prList[i-1]->addNode(*it); }
				j++;
			}
	
			for (int i = 1; i < s1; i++) { mList[i-1]->addProbe(prList[i-1],MACRO_STATE); }
			break;
		}
			
		default :
		{
			std::cout << "ERROR: unknown measurement!" << std::endl;
		}
	}
}



void addHeaderToCSV (std::string fileName)
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
		line.push_back("CONTRARIAN");

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


void addLineToCSV (std::ofstream &csvFile, MarkovProcess *MP, std::string type, int update,
	int size1, int size2, double intraR1, double intraR2, double interR1, double interR2, double contrarian,
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
	addCSVField(csvFile,contrarian);
	
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




VoterExperiment::VoterExperiment (int size1, int size2, double intraR1, double intraR2, double interR1, double interR2,
	double contrarian, double time, double delay, std::set<MeasurementType> *preM, std::set<MeasurementType> *postM)
{
	id = ++id_number;
	update = UPDATE_EDGES;
	threshold = 1.0e-10;
	compactModel = false;
		
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
		
	contrarianMin = contrarian; contrarianMax = contrarian;	contrarianStep = 0.1;
		
	timeMin = time;		timeMax = time;		timeStep = 1;
	delayMin = delay;	delayMax = delay;	delayStep = 1;
	
	preMeasurements = preM;
	postMeasurements = postM;
}

