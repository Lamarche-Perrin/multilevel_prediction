
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <cmath>
#include <iterator>

#include "voter_graph.hpp"


VoterNode::VoterNode (int i, double w, double c)
{
	id = i;
	weight = w;
	contrarian = c;
	
	inEdgeWeight = 0;
	inEdgeNumber = 0;
	inEdgeSet = new std::set<VoterEdge*>();

	outEdgeWeight = 0;
	outEdgeNumber = 0;	
	outEdgeSet = new std::set<VoterEdge*>();
}


VoterNode::~VoterNode ()
{
	delete inEdgeSet;
	delete outEdgeSet;
}


VoterEdge::VoterEdge (VoterNode *n1, VoterNode *n2, double w)
{
	node1 = n1;
	node2 = n2;
	weight = w;
}


VoterEdge::~VoterEdge () {}


VoterGraph::VoterGraph (int update)
{
	updateProcess = update;
	nodeNumber = 0;
	edgeNumber = 0;
	nodeWeight = 0;
	edgeWeight = 0;
	nodeMap = new std::map<int,VoterNode*>();
	nodeSet = new std::set<VoterNode*>();
	edgeSet = new std::set<VoterEdge*>();
	
	process = 0;
}


VoterGraph::~VoterGraph ()
{
	delete nodeMap;
	delete nodeSet;
	delete edgeSet;
}


CompleteVoterGraph::CompleteVoterGraph (int size, int update, double contrarian) : VoterGraph (update)
{
	for (int i = 0; i < size; i++) { addNode(1,contrarian); }

	for (std::set<VoterNode*>::iterator it1 = nodeSet->begin(); it1 != nodeSet->end(); ++it1)
	{
		VoterNode *n1 = *it1;
		for (std::set<VoterNode*>::iterator it2 = nodeSet->begin(); it2 != nodeSet->end(); ++it2)
		{
			VoterNode *n2 = *it2;
			if (n1 != n2) { addEdge(n1,n2); }
		}
	}
}


TwoCommunitiesVoterGraph::TwoCommunitiesVoterGraph (int s1, int s2,
	double intraR1, double intraR2, double interR1, double interR2,
	double contrarian, int update) : VoterGraph (update)
{
	size1 = s1;
	size2 = s2;

	intraRate1 = intraR1;
	intraRate2 = intraR2;
	interRate1 = interR1;
	interRate2 = interR2;
	
	community1 = new std::set<VoterNode*>();
	community2 = new std::set<VoterNode*>();

	for (int i = 0; i < size1; i++) { community1->insert(addNode(1,contrarian)); }
	for (int i = 0; i < size2; i++) { community2->insert(addNode(1,contrarian)); }

	for (std::set<VoterNode*>::iterator it1 = community1->begin(); it1 != community1->end(); ++it1)
		for (std::set<VoterNode*>::iterator it2 = community1->begin(); it2 != community1->end(); ++it2)
			if (*it1 != *it2) { addEdge(*it1,*it2,intraR1); }

	for (std::set<VoterNode*>::iterator it1 = community2->begin(); it1 != community2->end(); ++it1)
		for (std::set<VoterNode*>::iterator it2 = community2->begin(); it2 != community2->end(); ++it2)
			if (*it1 != *it2) { addEdge(*it1,*it2,intraR2); }

	for (std::set<VoterNode*>::iterator it1 = community1->begin(); it1 != community1->end(); ++it1)
	{
		for (std::set<VoterNode*>::iterator it2 = community2->begin(); it2 != community2->end(); ++it2)
		{
			addEdge(*it1,*it2,interR1);
			addEdge(*it2,*it1,interR2);
		}
	}
}


TwoCommunitiesVoterGraph::~TwoCommunitiesVoterGraph ()
{
	delete community1;
	delete community2;
}


VoterNode *VoterGraph::addNode (double weight, double contrarian)
{
	if (weight > 0) {		
		VoterNode *node = new VoterNode(nodeNumber,weight,contrarian);
		nodeSet->insert(node);
		nodeMap->insert(std::make_pair(node->id,node));
		nodeNumber++;
		nodeWeight += weight;

		return node;
	}
	
	else { return 0; }
}


VoterEdge *VoterGraph::addEdge (VoterNode *n1, VoterNode *n2, double weight)
{
	if (weight > 0) {
		edgeNumber++;
		edgeWeight += weight;
		
		VoterEdge *e = new VoterEdge(n1,n2,weight);
		edgeSet->insert(e);
		
		n1->outEdgeSet->insert(e);
		n1->outEdgeWeight += weight;	
		n1->outEdgeNumber++;	

		n2->inEdgeSet->insert(e);
		n2->inEdgeWeight += weight;	
		n2->inEdgeNumber++;	
		
		return e;
	}
	
	else { return 0; }
}


void VoterGraph::fillEdges ()
{
	for (std::set<VoterNode*>::iterator it1 = nodeSet->begin(); it1 != nodeSet->end(); ++it1)
	{
	    VoterNode *n1 = *it1;
	    
		for (std::set<VoterNode*>::iterator it2 = it1; it2 != nodeSet->end(); ++it2)
		{
		    VoterNode *n2 = *it2;
		    if (n1 != n2)
			{
				addEdge(n1,n2);
				addEdge(n2,n1);
			}
		}
	}
}


void VoterGraph::print ()
{
	for (std::set<VoterNode*>::iterator it1 = nodeSet->begin(); it1 != nodeSet->end(); ++it1)
	{
	    VoterNode *n1 = *it1;
	    
	    std::cout << "node " << n1->id << " connected to nodes ";
		for (std::set<VoterEdge*>::iterator it2 = n1->outEdgeSet->begin(); it2 != n1->outEdgeSet->end(); ++it2)
		{
		    VoterNode *n2 = (*it2)->node2;
		    std::cout << n2->id << ", ";
		}
		std::cout << std::endl;
	}
}


MarkovProcess *VoterGraph::getMarkovProcess()
{
	unsigned long int size = 1 << nodeNumber;

	process = new MarkovProcess(size);

	for (unsigned long int i = 0; i < size; i++)
		process->distribution[i] = 1./size;

	for (unsigned long int i = 0; i < size; i++)
		for (unsigned long int j = 0; j < size; j++)
			process->transition[j*size+i] = 0.;

	if (updateProcess == UPDATE_EDGES)
	{
		for (unsigned long int i = 0; i < size; i++)
		{
			if (edgeNumber == 0 || edgeWeight == 0.) { process->transition[i*size+i] = 1.; std::cout << "NO EDGE!\n"; }
			else {
				for (std::set<VoterEdge*>::iterator it = edgeSet->begin(); it != edgeSet->end(); ++it)
				{
					VoterEdge *e = *it;
					int n1 = e->node1->id;
					int n2 = e->node2->id;
		
					bool s1 = (i >> n1) % 2;
					bool s2 = (i >> n2) % 2;
					
					unsigned long int j;
					if (s1 && !s2) { j = i + (1 << n2); }
					else if (!s1 && s2) { j = i - (1 << n2); }
					else { j = i; }
					
					process->transition[j*size+i] += e->weight/edgeWeight * (1 - e->node2->contrarian);


					if (s1 && s2) { j = i - (1 << n2); }
					else if (!s1 && !s2) { j = i + (1 << n2); }
					else { j = i; }
					
					process->transition[j*size+i] += e->weight/edgeWeight * e->node2->contrarian;
				}
			}
		}
	}
	
	if (updateProcess == UPDATE_NODES)
	{
		for (unsigned long int i = 0; i < size; i++)
		{
			for (std::set<VoterNode*>::iterator it1 = nodeSet->begin(); it1 != nodeSet->end(); ++it1)
			{
				VoterNode *node2 = *it1;
				int n2 = node2->id;
				bool s2 = (i >> n2) % 2;

				unsigned long int j;
				if (s2) { j = i - (1 << n2); } else { j = i + (1 << n2); }
				process->transition[j*size+i] += node2->weight/nodeWeight * node2->contrarian;
				
				for (std::set<VoterEdge*>::iterator it2 = node2->inEdgeSet->begin(); it2 != node2->inEdgeSet->end(); ++it2)
				{
					VoterEdge *e = *it2;
					int n1 = e->node1->id;

					bool s1 = (i >> n1) % 2;
					
					if (s1 && !s2) { j = i + (1 << n2); }
					else if (!s1 && s2) { j = i - (1 << n2); }
					else { j = i; }
						
					process->transition[j*size+i] += node2->weight/nodeWeight * e->weight/node2->inEdgeWeight * (1 - node2->contrarian);
				}
			}
		}
	}

	return process;
}


int nChoosek (int n, int k )
{
	if (k > n) return 0;
	if (k * 2 > n) k = n-k;
	if (k == 0) return 1;
	
	int result = n;
	for( int i = 2; i <= k; ++i ) {
		result *= (n-i+1);
		result /= i;
	}
	return result;
}




Partition *VoterGraph::getMarkovPartition (VoterProbe *probe, int metric)
{
	unsigned long int size = 1 << nodeNumber;
	Partition *partition = new Partition();
	
	if (metric == METRIC_MACRO_STATE)
	{
		std::map<int,Part*> partMap;
		for (int nb = 0; nb <= probe->nodeNumber; nb++)
		{
			Part *part = new Part();
			partition->addPart(part);
			partMap[nb] = part;
		}
			
		for (unsigned long int i = 0; i < size; i++)
		{
			int nb = 0;
			for (std::set<VoterNode*>::iterator it = probe->nodeSet->begin(); it != probe->nodeSet->end(); ++it)
				nb += (i >> (*it)->id) % 2;
			partMap[nb]->addIndividual(i);
		}
	}
	
	if (metric == METRIC_ACTIVE_EDGES)
	{
		if (probe->nodeNumber == 0)
		{
			Part *part = new Part();
			partition->addPart(part);
			for (unsigned long int i = 0; i < size; i++) { part->addIndividual(i); }
		}
		
		else {
			std::map<int,Part*> partMap;
	
			for (unsigned long int i = 0; i < size; i++)
			{
				int nb = 0;
				for (std::set<VoterNode*>::iterator it1 = probe->nodeSet->begin(); it1 != probe->nodeSet->end(); ++it1)
				{
					VoterNode *n2 = *it1;
					int s2 = (i >> n2->id) % 2;
					
					for (std::set<VoterEdge*>::iterator it2 = n2->inEdgeSet->begin(); it2 != n2->inEdgeSet->end(); ++it2)
					{
						VoterEdge *e = *it2;
						VoterNode *n1 = e->node1;
						int s1 = (i >> n1->id) % 2;
						
						if (s1 != s2) { nb += e->weight; }
					}
				}
			
				if (partMap.find(nb) == partMap.end())
				{
					Part *part = new Part();
					partition->addPart(part);
					partMap[nb] = part;
				}
							
				partMap[nb]->addIndividual(i);
			}
		}
	}
	
	return partition;
}


Partition *VoterGraph::getMarkovPartition (VoterMeasurement *m)
{
	if (m->probeNumber == 0)
	{
		Partition *partition = new Partition();
		Part *part = new Part();
		partition->addPart(part);

		unsigned long int size = 1 << nodeNumber;
		for (unsigned long int i = 0; i < size; i++) { part->addIndividual(i); }

		return partition;
	}
	
	Partition *partition1 = 0;
	for (int num = 0; num < m->probeNumber; num++)
	{
		VoterProbe *p = m->probeMap->at(num);
		int metric = m->metricMap->at(num);
		
		if (partition1 == 0) { partition1 = getMarkovPartition(p,metric); }
		else {
			Partition *partition2 = getMarkovPartition(p,metric);
			Partition *partition = new Partition();
			
			for (std::list<Part*>::iterator it1 = partition1->parts->begin(); it1 != partition1->parts->end(); ++it1)
			{
				Part *p1 = *it1;

				for (std::list<Part*>::iterator it2 = partition2->parts->begin(); it2 != partition2->parts->end(); ++it2)
				{
					Part *p2 = *it2;

					Part *newPart = new Part();
					for (std::list<int>::iterator itp1 = p1->individuals->begin(); itp1 != p1->individuals->end(); ++itp1)
						for (std::list<int>::iterator itp2 = p2->individuals->begin(); itp2 != p2->individuals->end(); ++itp2)
							if (*itp1 == *itp2) { newPart->addIndividual(*itp1); }
					
					if (newPart->individuals->size() > 0) { partition->addPart(newPart); }
					else { delete newPart; }
				}
			}
			
			delete partition1;
			partition1 = partition;
		}
	}
	
	return partition1;
}



MarkovProcess *TwoCommunitiesVoterGraph::getCompactMarkovProcess ()
{
	unsigned long int size = 2*size1*(size2+1);

	process = new MarkovProcess(size);

	for (unsigned long int i = 0; i < size; i++)
	{
		int a = i % 2;
		int n1 = (i-a)/2 % size1;
		int n2 = (i-a-2*n1)/(2*size1);
		
		process->distribution[i] = ((double) nChoosek(size1-1,n1) * nChoosek(size2,n2)) * pow(2.,-(size1+size2));
	}

	double sumP = 0;
	for (unsigned long int i = 0; i < size; i++) { sumP += process->distribution[i]; }
	if (std::abs(sumP - 1) > 1e-10) { std::cout << "ERROR: probabilities do not sum to 1!" << std::endl; }
	
	for (unsigned long int i = 0; i < size; i++)
		for (unsigned long int j = 0; j < size; j++)
			process->transition[j*size+i] = 0.;

	if (true && updateProcess == UPDATE_EDGES)
	{
		for (unsigned long int i = 0; i < size; i++)
		{
			int a = i % 2;
			int n1 = (i-a)/2 % size1;
			int n2 = (i-a-2*n1)/(2*size1);

			sumP = 0;
			double p;
			unsigned long int j;
			j = a + n1 * 2 + n2 * 2 * size1;
			
			// a -> n1
			if (n1 > 0)
			{
				if (a) { j = a + n1 * 2 + n2 * 2 * size1; }
				else { j = a + (n1-1) * 2 + n2 * 2 * size1; }
				p = intraRate1 * n1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// a -> !n1
			if (n1 < size1-1)
			{
				if (a) { j = a + (n1+1) * 2 + n2 * 2 * size1; }
				else { j = a + n1 * 2 + n2 * 2 * size1; }
				p = intraRate1 * (size1-1 - n1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// a -> n2
			if (n2 > 0)
			{
				if (a) { j = a + n1 * 2 + n2 * 2 * size1; }
				else { j = a + n1 * 2 + (n2-1) * 2 * size1; }
				p = interRate1 * n2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// a -> !n2
			if (n2 < size2)
			{
				if (a) { j = a + n1 * 2 + (n2+1) * 2 * size1; }
				else { j = a + n1 * 2 + n2 * 2 * size1; }
				p = interRate1 * (size2 - n2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n1 -> a
			if (n1 > 0)
			{
				j = 1 + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * n1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// !n1 -> a
			if (n1 < size1-1)
			{
				j = 0 + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// n2 -> a
			if (n2 > 0)
			{
				j = 1 + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * n2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// !n2 -> a
			if (n2 < size2)
			{
				j = 0 + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// n1 -> !n1
			if (n1 > 0 && n1 < size1-1)
			{
				j = a + (n1+1) * 2 + n2 * 2 * size1;
				p = intraRate1 * n1 * (size1-1 - n1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// !n1 -> n1
			if (n1 > 0 && n1 < size1-1)
			{
				j = a + (n1-1) * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1) * n1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n2 -> !n2
			if (n2 > 0 && n2 < size2)
			{
				j = a + n1 * 2 + (n2+1) * 2 * size1;
				p = intraRate2 * n2 * (size2 - n2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n2 -> n2
			if (n2 > 0 && n2 < size2)
			{
				j = a + n1 * 2 + (n2-1) * 2 * size1;
				p = intraRate2 * (size2 - n2) * n2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n1 -> !n2
			if (n1 > 0 && n2 < size2)
			{
				j = a + n1 * 2 + (n2+1) * 2 * size1;
				p = interRate1 * n1 * (size2 - n2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n1 -> n2
			if (n1 < size1-1 && n2 > 0)
			{
				j = a + n1 * 2 + (n2-1) * 2 * size1;
				p = interRate1 * (size1-1 - n1) * n2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n2 -> !n1
			if (n2 > 0 && n1 < size1-1)
			{
				j = a + (n1+1) * 2 + n2 * 2 * size1;
				p = interRate2 * n2 * (size1-1 - n1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n2 -> n1
			if (n2 < size2 && n1 > 0)
			{
				j = a + (n1-1) * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2) * n1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
						
			// n1 -> n1 || !n1 -> !n1 || n2 -> n2 || !n2 -> !n2 || n1 -> n2 || !n1 -> !n2 || n2 -> n1 || !n2 -> !n1
			j = a + n1 * 2 + n2 * 2 * size1;
			p = intraRate1 * n1 * (n1-1) + intraRate1 * (size1-1 - n1) * (size1-1 - n1 - 1)
				+ intraRate2 * n2 * (n2-1) + intraRate2 * (size2 - n2) * (size2 - n2 - 1)
				+ interRate1 * n1 * n2 + interRate1 * (size1-1 - n1) * (size2 - n2)
				+ interRate2 * n2 * n1 + interRate2 * (size2 - n2) * (size1-1 - n1);
			process->transition[j*size+i] += p/edgeWeight;
			sumP += p/edgeWeight;
			
			if (std::abs(sumP - 1) > 1e-10) { std::cout << "ERROR: probabilities do not sum to 1!" << std::endl; }
		}
	}

	return process;
}


Partition *TwoCommunitiesVoterGraph::getCompactMarkovPartition (VoterProbe *probe, int metric)
{
	unsigned long int size = 2 * size1 * (size2 + 1);
	Partition *partition = new Partition();
	
	if (metric == METRIC_MACRO_STATE)
	{
		std::map<int,Part*> partMap;
		for (int nb = 0; nb <= probe->nodeNumber; nb++)
		{
			Part *part = new Part();
			partition->addPart(part);
			partMap[nb] = part;
		}

		if (probe->nodeNumber == 1 && *probe->nodeSet->begin() == *community1->begin())
		{
			for (unsigned long int i = 0; i < size; i++)
			{
				int a = i % 2;
				partMap[a]->addIndividual(i);
			}
		}

		else if (*probe->nodeSet == *community1)
		{
			for (unsigned long int i = 0; i < size; i++)
			{
				int a = i % 2;
				int n1 = (i-a)/2 % size1;
				partMap[a+n1]->addIndividual(i);
			}
		}

		else if (*probe->nodeSet == *community2)
		{
			for (unsigned long int i = 0; i < size; i++)
			{
				int a = i % 2;
				int n1 = (i-a)/2 % size1;
				int n2 = (i-a-2*n1)/(2*size1);
				partMap[n2]->addIndividual(i);
			}
		}

		else if (*probe->nodeSet == *nodeSet)
		{
			for (unsigned long int i = 0; i < size; i++)
			{
				int a = i % 2;
				int n1 = (i-a)/2 % size1;
				int n2 = (i-a-2*n1)/(2*size1);
				partMap[a+n1+n2]->addIndividual(i);
			}
		}
		
		else { std::cout << "ERROR: incompatible probe!" << std::endl; probe->print(true); }
	}
		
	return partition;
}


Partition *TwoCommunitiesVoterGraph::getCompactMarkovPartition (VoterMeasurement *m)
{
	if (m->probeNumber == 0)
	{
		Partition *partition = new Partition();
		Part *part = new Part();
		partition->addPart(part);

		unsigned long int size = 2 * size1 * (size2 + 1);
		for (unsigned long int i = 0; i < size; i++) { part->addIndividual(i); }

		return partition;
	}
	
	Partition *partition1 = 0;
	for (int num = 0; num < m->probeNumber; num++)
	{
		VoterProbe *p = m->probeMap->at(num);
		int metric = m->metricMap->at(num);
		
		if (partition1 == 0) { partition1 = getCompactMarkovPartition(p,metric); }
		else {
			Partition *partition2 = getCompactMarkovPartition(p,metric);
			Partition *partition = new Partition();
			
			for (std::list<Part*>::iterator it1 = partition1->parts->begin(); it1 != partition1->parts->end(); ++it1)
			{
				Part *p1 = *it1;

				for (std::list<Part*>::iterator it2 = partition2->parts->begin(); it2 != partition2->parts->end(); ++it2)
				{
					Part *p2 = *it2;

					Part *newPart = new Part();
					for (std::list<int>::iterator itp1 = p1->individuals->begin(); itp1 != p1->individuals->end(); ++itp1)
						for (std::list<int>::iterator itp2 = p2->individuals->begin(); itp2 != p2->individuals->end(); ++itp2)
							if (*itp1 == *itp2) { newPart->addIndividual(*itp1); }
					
					if (newPart->individuals->size() > 0) { partition->addPart(newPart); }
					else { delete newPart; }
				}
			}
			
			delete partition1;
			partition1 = partition;
		}
	}
	
	return partition1;
}


VoterProbe::VoterProbe (VoterGraph *g)
{
	graph = g;
	nodeNumber = 0;
	nodeSet = new std::set<VoterNode*>();
}


VoterProbe::~VoterProbe ()
{
	delete nodeSet;
}


void VoterProbe::addNode (VoterNode *n)
{
	nodeNumber++;
	nodeSet->insert(n);
}


void VoterProbe::addNodes (unsigned long int i)
{
	int id = 0;
	while (i != 0)
	{
		if (i % 2)
		{
			nodeNumber++;
			nodeSet->insert(graph->nodeMap->at(id));
		}
		i = i >> 1;
		id++;
	}
}


void VoterProbe::print (bool endl)
{
	std::cout << "{";
	bool first = true;
	for (std::set<VoterNode*>::iterator it = nodeSet->begin(); it != nodeSet->end(); ++it)
	{
	    VoterNode *n = *it;
	    if (!first) { std::cout << ", "; }
	    std::cout << n->id;
	    first = false;
	}
	std::cout << "}";
	if (endl) { std::cout << std::endl; }
}


VoterMeasurement::VoterMeasurement (VoterGraph *g, std::string t)
{
	graph = g;
	type = t;
	partition = 0;
	
	probeNumber = 0;
	probeMap = new std::map<int,VoterProbe*>();
	metricMap = new std::map<int,int>();
}


VoterMeasurement::~VoterMeasurement ()
{
	if (partition != 0) { delete partition; }
	delete probeMap;
	delete metricMap;
}


void VoterMeasurement::addProbe (VoterProbe *p, int metric)
{
	probeMap->insert(std::make_pair(probeNumber,p));
	metricMap->insert(std::make_pair(probeNumber,metric));
	probeNumber++;
}


void VoterMeasurement::print (bool endl)
{
	for (int num = 0; num < probeNumber; num++) { probeMap->at(num)->print(true); }
	if (endl) { std::cout << std::endl; }
}


MacroVoterMeasurement::MacroVoterMeasurement (VoterGraph *g, std::set<int> metrics) : VoterMeasurement(g,"MACRO")
{
	for (std::set<int>::iterator it = metrics.begin(); it != metrics.end(); ++it)
	{
		int metric = *it;
		if (metric == METRIC_MACRO_STATE) { type = type + "_MS"; }
		if (metric == METRIC_ACTIVE_EDGES) { type = type + "_AE"; }
		
		VoterProbe *probe = new VoterProbe(g);
		for (std::set<VoterNode*>::iterator it = g->nodeSet->begin(); it != g->nodeSet->end(); ++it) { probe->addNode(*it); }
		addProbe(probe,metric);
	}
}


MicroVoterMeasurement::MicroVoterMeasurement (VoterGraph *g, std::set<int> metrics) : VoterMeasurement(g,"MICRO")
{
	for (std::set<int>::iterator it = metrics.begin(); it != metrics.end(); ++it)
	{
		int metric = *it;
		if (metric == METRIC_MACRO_STATE) { type = type + "_MS"; }
		if (metric == METRIC_ACTIVE_EDGES) { type = type + "_AE"; }
		
		for (std::set<VoterNode*>::iterator it = g->nodeSet->begin(); it != g->nodeSet->end(); ++it)
		{
			VoterProbe *probe = new VoterProbe(g);
			probe->addNode(*it);
			addProbe(probe,metric);
		}
	}
}


EmptyVoterMeasurement::EmptyVoterMeasurement (VoterGraph *g) : VoterMeasurement(g,"EMPTY") {}

