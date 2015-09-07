/*!
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */

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


VoterEdge *VoterNode::getRandomEdge ()
{
    double r = ((double) rand() / (RAND_MAX));
    for (std::set<VoterEdge*>::iterator it = outEdgeSet->begin(); it != outEdgeSet->end(); ++it)
    {
		VoterEdge *e = *it;
		double p = e->weight/outEdgeWeight;
		if (r < p) { return e; }
		r -= p;
    }
    return 0;
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


ChainVoterGraph::ChainVoterGraph (int s, double c, bool r, int update) : VoterGraph (update)
{
    size = s;
    contrarian = c;
    ring = r;
    nodeArray = new VoterNode* [size];

    for (int i = 0; i < size; i++) { nodeArray[i] = addNode(1,contrarian); }
    for (int i = 1; i < size; i++) { addEdge(nodeArray[i-1],nodeArray[i]); addEdge(nodeArray[i],nodeArray[i-1]); }
    if (ring) { addEdge(nodeArray[0],nodeArray[size-1]); addEdge(nodeArray[size-1],nodeArray[0]); }
}


ChainVoterGraph::~ChainVoterGraph ()
{
    delete [] nodeArray;
}


TwoCommunitiesVoterGraph::TwoCommunitiesVoterGraph (int s1, int s2,
													double intraR1, double intraR2, double interR1, double interR2,
													double c1, double c2, int update) : VoterGraph (update)
{
    size1 = s1;
    size2 = s2;

    intraRate1 = intraR1;
    intraRate2 = intraR2;
    interRate1 = interR1;
    interRate2 = interR2;
	
    contrarian1 = c1;
    contrarian2 = c2;
	
    community1 = new std::set<VoterNode*>();
    community2 = new std::set<VoterNode*>();

    for (int i = 0; i < size1; i++) { community1->insert(addNode(1,c1)); }
    for (int i = 0; i < size2; i++) { community2->insert(addNode(1,c2)); }

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


VoterNode *VoterGraph::getRandomNode ()
{
    double r = ((double) rand() / (RAND_MAX));
    for (std::set<VoterNode*>::iterator it = nodeSet->begin(); it != nodeSet->end(); ++it)
    {
		VoterNode *n = *it;
		double p = n->weight/nodeWeight;
		if (r < p) { return n; }
		r -= p;
    }
    return 0;
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


long unsigned int nChoosek (int n, int k)
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;
	
    long unsigned int result = n;
    for( int i = 2; i <= k; ++i ) {
		result *= (n-i+1);
		result /= i;
    }
    return result;
}


double nChoosekProb (int n, int k)
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1 * pow(2.,-n);
	
    double result = n * pow(2.,-n);
    for (int i = 2; i <= k; ++i) {
		result *= (n-i+1);
		result /= i;
    }
    return result;
}


Partition *VoterGraph::getMarkovPartition (VoterProbe *probe, VoterMetric metric)
{
    unsigned long int size = 1 << nodeNumber;
    Partition *partition = new Partition();
	
    switch (metric)
    {
    case MACRO_STATE :
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
			partMap[nb]->addIndividual(i,false,nb);
		}
		break;
    }

    /*
	  case MAJORITY : case MAJ_1PC : case MAJ_2PC : case MAJ_3PC : case MAJ_4PC : case MAJ_5PC : case MAJ_6PC : case MAJ_7PC : 
	  case MAJ_8PC : case MAJ_9PC : case MAJ_10PC : case MAJ_20PC : case MAJ_30PC : case MAJ_40PC : case MAJ_50PC :
	  case MAJ_60PC : case MAJ_70PC : case MAJ_80PC : case MAJ_90PC :
	  {
	  Part *part0 = new Part();
	  Part *part1 = new Part();
	  Part *partNA = new Part();

	  partition->addPart(part0);
	  partition->addPart(part1);
	  partition->addPart(partNA);

	  double pc = 0;
	  switch (metric)
	  {
	  case MAJORITY : pc = 0; break;
	  case MAJ_1PC : pc = 0.01; break;
	  case MAJ_2PC : pc = 0.02; break;
	  case MAJ_3PC : pc = 0.03; break;
	  case MAJ_4PC : pc = 0.04; break;
	  case MAJ_5PC : pc = 0.05; break;
	  case MAJ_6PC : pc = 0.06; break;
	  case MAJ_7PC : pc = 0.07; break;
	  case MAJ_8PC : pc = 0.08; break;
	  case MAJ_9PC : pc = 0.09; break;
	  case MAJ_10PC : pc = 0.1; break;
	  case MAJ_20PC : pc = 0.2; break;
	  case MAJ_30PC : pc = 0.3; break;
	  case MAJ_40PC : pc = 0.4; break;
	  case MAJ_50PC : pc = 0.5; break;
	  case MAJ_60PC : pc = 0.6; break;
	  case MAJ_70PC : pc = 0.7; break;
	  case MAJ_80PC : pc = 0.8; break;
	  case MAJ_90PC : pc = 0.9; break;
	  default : break;
	  }
				
	  for (unsigned long int i = 0; i < size; i++)
	  {
	  int nb = 0;
	  for (std::set<VoterNode*>::iterator it = probe->nodeSet->begin(); it != probe->nodeSet->end(); ++it)
	  nb += (i >> (*it)->id) % 2;

	  if (2*nb - size < pc * probe->nodeNumber) { part0->addIndividual(i); }
	  else if (2*nb - size > pc * probe->nodeNumber) { part1->addIndividual(i); }
	  else { partNA->addIndividual(i); }
	  }
	  break;
	  }
		
	
	  case MAJ_2BINS : case MAJ_3BINS : case MAJ_4BINS : case MAJ_6BINS : case MAJ_8BINS : case MAJ_12BINS : case MAJ_24BINS :
	  {
	  int partNumber;
	  switch (metric)
	  {
	  case MAJ_2BINS : partNumber = std::min(2,probe->nodeNumber+1); break;
	  case MAJ_3BINS : partNumber = std::min(3,probe->nodeNumber+1); break;
	  case MAJ_4BINS : partNumber = std::min(4,probe->nodeNumber+1); break;
	  case MAJ_6BINS : partNumber = std::min(6,probe->nodeNumber+1); break;
	  case MAJ_8BINS : partNumber = std::min(8,probe->nodeNumber+1); break;
	  case MAJ_12BINS : partNumber = std::min(12,probe->nodeNumber+1); break;
	  case MAJ_24BINS : partNumber = std::min(24,probe->nodeNumber+1); break;
	  default : std::cout << "ERROR: unimplemented majority measurement!" << std::endl; return 0;
	  }

	  if (probe->nodeNumber+1 % partNumber != 0) { std::cout << "ERROR: not a proper bin size for majority measurement!" << std::endl; return 0; }
	
	  int partVector [partNumber];
	  for (int i = 0; i < partNumber; i++) { partVector[i] = 0; }
		
	  int nb1 = 0;
	  double c = pow(2.,-probe->nodeNumber);
	  for (int i = 0; i < partNumber/2; i++)
	  {
	  int nb2 = nb1;
	  double add = nChoosekProb(probe->nodeNumber,nb2+1);
	  while (c + add < ((double)i+1)/partNumber) { c += add; nb2++; add = nChoosekProb(probe->nodeNumber,nb2+1); }
			
	  partVector[2*i] = nb1;
	  partVector[2*i+1] = nb2;
	  partVector[2*(partNumber-1-i)] = probe->nodeNumber-nb2;
	  partVector[2*(partNumber-1-i)+1] = probe->nodeNumber-nb1;
		
	  nb1 = nb2+1;
	  c += nChoosekProb(probe->nodeNumber,nb1);
	  }
			
	  if (partNumber % 2)
	  {
	  int i = partNumber/2;
	  partVector[2*(partNumber-1-i)] = partVector[2*(partNumber-1-i)-1]+1;
	  partVector[2*(partNumber-1-i)+1] = partVector[2*(partNumber-1-i)+2]-1;
	  }
		
//			for (int i = 0; i < partNumber; i++)
//				std::cout << partVector[2*i] << " - " << partVector[2*i+1] << "\t" << std::endl;

std::map<int,Part*> partMap;
for (int n = 0; n < partNumber; n++)
{
Part *part = new Part();
partition->addPart(part);
partMap[n] = part;
}
				
Part *partNA = new Part();
partition->addPart(partNA);

for (unsigned long int i = 0; i < size; i++)
{
int nb = 0;
for (std::set<VoterNode*>::iterator it = probe->nodeSet->begin(); it != probe->nodeSet->end(); ++it)
nb += (i >> (*it)->id) % 2;

bool found = false;
for (int n = 0; !found && n < partNumber; n++)
if (nb >= partVector[2*n] && nb <= partVector[2*n+1] ) { partMap[n]->addIndividual(i); found = true; }
if (!found) { partNA->addIndividual(i); }
}
break;
}
    */	
		
    case ACTIVE_EDGES :
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
		break;
    }
			
    default : std::cout << "ERROR: unimplemented metric!" << std::endl;
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
		for (unsigned long int i = 0; i < size; i++) { part->addIndividual(i,false,0); }

		return partition;
    }
	
    Partition *partition1 = 0;
    for (int num = 0; num < m->probeNumber; num++)
    {
		VoterProbe *p = m->probeMap->at(num);
		VoterMetric metric = m->metricMap->at(num);
		
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

    if (updateProcess == UPDATE_EDGES)
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
				p = intraRate1 * n1 * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				if (a) { j = a + (n1-1) * 2 + n2 * 2 * size1; }
				else { j = a + n1 * 2 + n2 * 2 * size1; }
				p = intraRate1 * n1 * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// a -> !n1
			if (n1 < size1-1)
			{
				if (a) { j = a + (n1+1) * 2 + n2 * 2 * size1; }
				else { j = a + n1 * 2 + n2 * 2 * size1; }
				p = intraRate1 * (size1-1 - n1) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				if (a) { j = a + n1 * 2 + n2 * 2 * size1; }
				else { j = a + (n1+1) * 2 + n2 * 2 * size1; }
				p = intraRate1 * (size1-1 - n1) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// a -> n2
			if (n2 > 0)
			{
				if (a) { j = a + n1 * 2 + n2 * 2 * size1; }
				else { j = a + n1 * 2 + (n2-1) * 2 * size1; }
				p = interRate1 * n2 * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				if (a) { j = a + n1 * 2 + (n2-1) * 2 * size1; }
				else { j = a + n1 * 2 + n2 * 2 * size1; }
				p = interRate1 * n2 * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// a -> !n2
			if (n2 < size2)
			{
				if (a) { j = a + n1 * 2 + (n2+1) * 2 * size1; }
				else { j = a + n1 * 2 + n2 * 2 * size1; }
				p = interRate1 * (size2 - n2) * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				if (a) { j = a + n1 * 2 + n2 * 2 * size1; }
				else { j = a + n1 * 2 + (n2+1) * 2 * size1; }
				p = interRate1 * (size2 - n2) * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n1 -> a
			if (n1 > 0)
			{
				j = 1 + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * n1 * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = 0 + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * n1 * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// !n1 -> a
			if (n1 < size1-1)
			{
				j = 0 + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = 1 + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// n2 -> a
			if (n2 > 0)
			{
				j = 1 + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * n2 * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = 0 + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * n2 * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// !n2 -> a
			if (n2 < size2)
			{
				j = 0 + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = 1 + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// n1 -> !n1
			if (n1 > 0 && n1 < size1-1)
			{
				j = a + (n1+1) * 2 + n2 * 2 * size1;
				p = intraRate1 * n1 * (size1-1 - n1) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * n1 * (size1-1 - n1) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// !n1 -> n1
			if (n1 > 0 && n1 < size1-1)
			{
				j = a + (n1-1) * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1) * n1 * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1) * n1 * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n2 -> !n2
			if (n2 > 0 && n2 < size2)
			{
				j = a + n1 * 2 + (n2+1) * 2 * size1;
				p = intraRate2 * n2 * (size2 - n2) * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate2 * n2 * (size2 - n2) * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n2 -> n2
			if (n2 > 0 && n2 < size2)
			{
				j = a + n1 * 2 + (n2-1) * 2 * size1;
				p = intraRate2 * (size2 - n2) * n2 * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate2 * (size2 - n2) * n2 * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n1 -> !n2
			if (n1 > 0 && n2 < size2)
			{
				j = a + n1 * 2 + (n2+1) * 2 * size1;
				p = interRate1 * n1 * (size2 - n2) * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate1 * n1 * (size2 - n2) * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n1 -> n2
			if (n1 < size1-1 && n2 > 0)
			{
				j = a + n1 * 2 + (n2-1) * 2 * size1;
				p = interRate1 * (size1-1 - n1) * n2 * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate1 * (size1-1 - n1) * n2 * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n2 -> !n1
			if (n2 > 0 && n1 < size1-1)
			{
				j = a + (n1+1) * 2 + n2 * 2 * size1;
				p = interRate2 * n2 * (size1-1 - n1) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * n2 * (size1-1 - n1) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n2 -> n1
			if (n2 < size2 && n1 > 0)
			{
				j = a + (n1-1) * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2) * n1 * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2) * n1 * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n1 -> n1
			if (n1 > 1)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * n1 * (n1 - 1) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + (n1-1) * 2 + n2 * 2 * size1;
				p = intraRate1 * n1 * (n1 - 1) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}

			// !n1 -> !n1
			if (n1 < size1-2)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1) * (size1-1 - n1 - 1) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + (n1+1) * 2 + n2 * 2 * size1;
				p = intraRate1 * (size1-1 - n1) * (size1-1 - n1 - 1) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n2 -> n2
			if (n2 > 1)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate2 * n2 * (n2 - 1) * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + (n2-1) * 2 * size1;
				p = intraRate2 * n2 * (n2 - 1) * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n2 -> !n2
			if (n2 < size2-1)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = intraRate2 * (size2 - n2) * (size2 - n2 - 1) * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + (n2+1) * 2 * size1;
				p = intraRate2 * (size2 - n2) * (size2 - n2 - 1) * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n1 -> n2
			if (n1 > 0 && n2 > 0)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate1 * n1 * n2 * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + (n2-1) * 2 * size1;
				p = interRate1 * n1 * n2 * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n1 -> !n2
			if (n1 < size1-1 && n2 < size2)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate1 * (size1-1 - n1) * (size2 - n2) * (1 - contrarian2);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + n1 * 2 + (n2+1) * 2 * size1;
				p = interRate1 * (size1-1 - n1) * (size2 - n2) * contrarian2;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// n2 -> n1
			if (n2 > 0 && n1 > 0)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * n2 * n1 * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + (n1-1) * 2 + n2 * 2 * size1;
				p = interRate2 * n2 * n1 * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
			
			// !n2 -> !n1
			if (n2 < size2 && n1 < size1-1)
			{
				j = a + n1 * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2) * (size1-1 - n1) * (1 - contrarian1);
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;

				j = a + (n1+1) * 2 + n2 * 2 * size1;
				p = interRate2 * (size2 - n2) * (size1-1 - n1) * contrarian1;
				process->transition[j*size+i] += p/edgeWeight;
				sumP += p/edgeWeight;
			}
						
			if (std::abs(sumP - 1) > 1e-10) { std::cout << "ERROR: probabilities do not sum to 1!" << std::endl; }
		}
    }

    return process;
}


Partition *TwoCommunitiesVoterGraph::getCompactMarkovPartition (VoterProbe *probe, VoterMetric metric)
{
    unsigned long int size = 2 * size1 * (size2 + 1);
    Partition *partition = new Partition();
	
    switch (metric)
    {
    case MACRO_STATE :
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
				partMap[a]->addIndividual(i,false,a);
			}
		}
	
		else if (*probe->nodeSet == *community1)
		{
			for (unsigned long int i = 0; i < size; i++)
			{
				int a = i % 2;
				int n1 = (i-a)/2 % size1;
				partMap[a+n1]->addIndividual(i,false,a+n1);
			}
		}
	
		else if (*probe->nodeSet == *community2)
		{
			for (unsigned long int i = 0; i < size; i++)
			{
				int a = i % 2;
				int n1 = (i-a)/2 % size1;
				int n2 = (i-a-2*n1)/(2*size1);
				partMap[n2]->addIndividual(i,false,n2);
			}
		}
	
		else if (*probe->nodeSet == *nodeSet)
		{
			for (unsigned long int i = 0; i < size; i++)
			{
				int a = i % 2;
				int n1 = (i-a)/2 % size1;
				int n2 = (i-a-2*n1)/(2*size1);
				partMap[a+n1+n2]->addIndividual(i,false,a+n1+n2);
			}
		}
		
		else { std::cout << "ERROR: incompatible probe!" << std::endl; probe->print(true); }
		break;
    }
		
    case MAJORITY : case MAJ_1PC : case MAJ_2PC : case MAJ_3PC : case MAJ_4PC : case MAJ_5PC : case MAJ_6PC : case MAJ_7PC : 
    case MAJ_8PC : case MAJ_9PC : case MAJ_10PC : case MAJ_20PC : case MAJ_30PC : case MAJ_40PC : case MAJ_50PC :
    case MAJ_60PC : case MAJ_70PC : case MAJ_80PC : case MAJ_90PC :
    {
		Part *part0 = new Part();
		Part *part1 = new Part();
		Part *partNA = new Part();

		partition->addPart(part0);
		partition->addPart(part1);
		partition->addPart(partNA);

		double pc = 0;
		switch (metric)
		{
		case MAJORITY : pc = 0; break;
		case MAJ_1PC : pc = 0.01; break;
		case MAJ_2PC : pc = 0.02; break;
		case MAJ_3PC : pc = 0.03; break;
		case MAJ_4PC : pc = 0.04; break;
		case MAJ_5PC : pc = 0.05; break;
		case MAJ_6PC : pc = 0.06; break;
		case MAJ_7PC : pc = 0.07; break;
		case MAJ_8PC : pc = 0.08; break;
		case MAJ_9PC : pc = 0.09; break;
		case MAJ_10PC : pc = 0.1; break;
		case MAJ_20PC : pc = 0.2; break;
		case MAJ_30PC : pc = 0.3; break;
		case MAJ_40PC : pc = 0.4; break;
		case MAJ_50PC : pc = 0.5; break;
		case MAJ_60PC : pc = 0.6; break;
		case MAJ_70PC : pc = 0.7; break;
		case MAJ_80PC : pc = 0.8; break;
		case MAJ_90PC : pc = 0.9; break;
		default : break;
		}
			
		for (unsigned long int i = 0; i < size; i++)
		{
			int a = i % 2;
			int n1 = (i-a)/2 % size1;
			int n2 = (i-a-2*n1)/(2*size1);

			int nb = -1; int s = -1;
			if (probe->nodeNumber == 1 && *probe->nodeSet->begin() == *community1->begin()) { nb = a; s = 1; }
			else if (*probe->nodeSet == *community1) { nb = a+n1; s = size1; }
			else if (*probe->nodeSet == *community2) { nb = n2; s = size2; }
			else if (*probe->nodeSet == *nodeSet) { nb = a+n1+n2; s = size1+size2; }
			else { std::cout << "ERROR: incompatible probe!" << std::endl; probe->print(true); }
				
			if (nb >= 0)
			{
				if (2*nb - s < pc * probe->nodeNumber) { part0->addIndividual(i); }
				else if (2*nb - s > pc * probe->nodeNumber) { part1->addIndividual(i); }
				else { partNA->addIndividual(i); }
			}	
		}
		break;
    }

    case MAJ_2B : case MAJ_3B : case MAJ_4B : case MAJ_6B : case MAJ_8B : case MAJ_10B : case MAJ_12B : case MAJ_20B : case MAJ_40B :
    {
		int partNumber;
		switch (metric)
		{
		case MAJ_2B : partNumber = 2; break;
		case MAJ_3B : partNumber = 3; break;
		case MAJ_4B : partNumber = 4; break;
		case MAJ_6B : partNumber = 6; break;
		case MAJ_8B : partNumber = 8; break;
		case MAJ_10B : partNumber = 10; break;
		case MAJ_12B : partNumber = 12; break;
		case MAJ_20B : partNumber = 20; break;
		case MAJ_40B : partNumber = 40; break;
		default : break;
		}
	
		partNumber = std::min(partNumber,probe->nodeNumber+1);
		if ((probe->nodeNumber+1) % partNumber != 0) { std::cout << "ERROR: not a proper bin size for majority measurement!" << std::endl; return 0; }
		int l = (probe->nodeNumber+1) / partNumber;
	
		std::map<int,Part*> partMap;
		for (int n = 0; n < partNumber; n++)
		{
			Part *part = new Part();
			partition->addPart(part);
			partMap[n] = part;
		}
				
		Part *partNA = new Part();
		partition->addPart(partNA);

		for (unsigned long int i = 0; i < size; i++)
		{
			int a = i % 2;
			int n1 = (i-a)/2 % size1;
			int n2 = (i-a-2*n1)/(2*size1);

			int nb = -1;
			if (probe->nodeNumber == 1 && *probe->nodeSet->begin() == *community1->begin()) { nb = a; }
			else if (*probe->nodeSet == *community1) { nb = a+n1; }
			else if (*probe->nodeSet == *community2) { nb = n2; }
			else if (*probe->nodeSet == *nodeSet) { nb = a+n1+n2; }
			else { std::cout << "ERROR: incompatible probe!" << std::endl; probe->print(true); return 0; }
				
			int n = floor(nb/l);
			partMap[n]->addIndividual(i);

			/*
			  int lim = ((probe->nodeNumber+1) - ((probe->nodeNumber+1) % 2))/2;
			  if (nb < lim)
			  {
			  int n = (nb - (nb % (2*lim/partNumber))) / (2*lim/partNumber);
			  partMap[n]->addIndividual(i);
			  }
	    
			  else if (probe->nodeNumber - nb < lim)
			  {
			  int n = ((probe->nodeNumber - nb) - ((probe->nodeNumber - nb) % (2*lim/partNumber))) / (2*lim/partNumber);
			  partMap[partNumber-n-1]->addIndividual(i);						
			  }
	    
			  else
			  {
			  partNA->addIndividual(i);
			  }
			*/
		}
		break;
    }
		
    default : std::cout << "ERROR: unimplemented metric!" << std::endl;			
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
		for (unsigned long int i = 0; i < size; i++) { part->addIndividual(i,false,0); }

		return partition;
    }
	
    Partition *partition1 = 0;
    for (int num = 0; num < m->probeNumber; num++)
    {
		VoterProbe *p = m->probeMap->at(num);
		VoterMetric metric = m->metricMap->at(num);
		
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

void VoterProbe::setNodeSet (std::set<VoterNode*> *set)
{
    delete nodeSet;
    nodeSet = set;
    nodeNumber = set->size();
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


int VoterProbe::getState (VoterState *state, VoterMetric metric)
{
	switch (metric)
	{
	case MACRO_STATE :
	{
		int probeState = 0;
		for (std::set<VoterNode*>::iterator it = nodeSet->begin(); it != nodeSet->end(); ++it)
		{
			VoterNode *n = *it;
			probeState += state->agentStates[n->id];
		}
		return probeState;
	}
		
	default :
		std::cout << "ERROR: this metric has not been implemented!" << std::endl;
		return -1;
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
    metricMap = new std::map<int,VoterMetric>();
}


VoterMeasurement::~VoterMeasurement ()
{
    if (partition != 0) { delete partition; }
    delete probeMap;
    delete metricMap;
}


void VoterMeasurement::addProbe (VoterProbe *p, VoterMetric metric)
{
    probeMap->insert(std::make_pair(probeNumber,p));
    metricMap->insert(std::make_pair(probeNumber,metric));
    probeNumber++;
}


VoterMeasurementState *VoterMeasurement::getState (VoterState *state)
{
	VoterMeasurementState *measurementState = new VoterMeasurementState(this);

    for (int num = 0; num < probeNumber; num++)
	{
		VoterProbe *probe = probeMap->at(num);
		VoterMetric metric = metricMap->at(num);
		measurementState->probeStates[num] = probe->getState(state,metric);
	}
	return measurementState;
}


void VoterMeasurement::print (bool endl)
{
    for (int num = 0; num < probeNumber; num++) { probeMap->at(num)->print(true); }
    if (endl) { std::cout << std::endl; }
}


MacroVoterMeasurement::MacroVoterMeasurement (VoterGraph *g, std::set<VoterMetric> metrics) : VoterMeasurement(g,"MACRO")
{
    for (std::set<VoterMetric>::iterator it = metrics.begin(); it != metrics.end(); ++it)
    {
		VoterMetric metric = *it;
		if (metric == MACRO_STATE) { type = type + "_MS"; }
		if (metric == ACTIVE_EDGES) { type = type + "_AE"; }
		
		VoterProbe *probe = new VoterProbe(g);
		for (std::set<VoterNode*>::iterator it = g->nodeSet->begin(); it != g->nodeSet->end(); ++it) { probe->addNode(*it); }
		addProbe(probe,metric);
    }
}


MicroVoterMeasurement::MicroVoterMeasurement (VoterGraph *g, std::set<VoterMetric> metrics) : VoterMeasurement(g,"MICRO")
{
    for (std::set<VoterMetric>::iterator it = metrics.begin(); it != metrics.end(); ++it)
    {
		VoterMetric metric = *it;
		if (metric == MACRO_STATE) { type = type + "_MS"; }
		if (metric == ACTIVE_EDGES) { type = type + "_AE"; }
		
		for (std::set<VoterNode*>::iterator it = g->nodeSet->begin(); it != g->nodeSet->end(); ++it)
		{
			VoterProbe *probe = new VoterProbe(g);
			probe->addNode(*it);
			addProbe(probe,metric);
		}
    }
}


EmptyVoterMeasurement::EmptyVoterMeasurement (VoterGraph *g) : VoterMeasurement(g,"EMPTY") {}


VoterState::VoterState (VoterGraph *VG)
{
    graph = VG;
    size = graph->nodeNumber;
    agentStates = new bool [size];
}


VoterState::VoterState (VoterState *state)
{
    graph = state->graph;
    size = state->size;
    agentStates = new bool [size];
    for (int i = 0; i < size; i++) { agentStates[i] = state->agentStates[i]; }
}


VoterState::~VoterState ()
{
    delete [] agentStates;
}


void VoterState::print ()
{
    for (int i = 0; i < size; i++) { std::cout << agentStates[i]; }    
}


void VoterState::setFromMicroUniform ()
{
    for (int i = 0; i < size; i++) { agentStates[i] = rand() % 2; }
}


void VoterState::setFromMacroUniform ()
{
//for (int i = 0; i < size; i++) { agentStates[i] = rand() % 2; }
}

VoterMeasurementState::VoterMeasurementState (VoterMeasurement *m)
{
	measurement = m;
	size = m->probeNumber;
	probeStates = new int [size];
}


VoterMeasurementState::VoterMeasurementState(const VoterMeasurementState& state){
	this->measurement = state.measurement;
	this->size = state.size;
    this->probeStates = new int [size];
	for (int i = 0; i < size; i++) { this->probeStates[i] = state.probeStates[i]; };
}


VoterMeasurementState::~VoterMeasurementState ()
{
	delete [] probeStates;
}


bool operator< (const VoterMeasurementState& s1, const VoterMeasurementState& s2)
{
	/*
	std::cout << "COMPARE ";
	std::cout << "(";
	if (s1.size > 0)
	{
		std::cout << s1.probeStates[0];
		for (int i = 1; i < s1.size; i++) { std::cout << "," << s1.probeStates[i]; }
	}
	std::cout << ")";
	std::cout << " AND ";
	std::cout << "(";
	if (s2.size > 0)
	{
		std::cout << s2.probeStates[0];
		for (int i = 1; i < s2.size; i++) { std::cout << "," << s2.probeStates[i]; }
	}
	std::cout << ") ";
	*/

	if (s1.size != s2.size) { std::cout << "ERROR: measurement states are not comparable!" << std::cout; return false; }
	for (int i = 0; i < s1.size; i++) {
		//std::cout << "COMPARE " << s1.probeStates[i] << " AND "<< s2.probeStates[i] << std::endl;
		if (s1.probeStates[i] < s2.probeStates[i])
		{
			//std::cout << "RETURN TRUE" << std::endl;
			return true;
		}
	}
	
	//std::cout << "RETURN FALSE" << std::endl;
	return false;
}


void VoterMeasurementState::init (int value)
{
	for (int i = 0; i < size; i++) { probeStates[i] = value; }
}


void VoterMeasurementState::print ()
{
	std::cout << "(";
	if (size > 0)
	{
		std::cout << probeStates[0];
		for (int i = 1; i < size; i++) { std::cout << "," << probeStates[i]; }
	}
	std::cout << ")";
}


VoterState *VoterState::getNextState()
{
    VoterState *state = new VoterState(this);
    VoterNode *n = graph->getRandomNode();
    VoterEdge *e = n->getRandomEdge();
    state->agentStates[e->node2->id] = state->agentStates[e->node1->id];
    return state;
}


VoterTrajectory::VoterTrajectory (VoterGraph *VG, int l)
{
    graph = VG;
    length = l;

    states = new VoterState *[length];

    if (length > 0)
    {
		states[0] = new VoterState(graph);
		states[0]->setFromMicroUniform();

		for (int l = 1; l < length; l++)
			states[l] = states[l-1]->getNextState();
    }
}


VoterTrajectory::~VoterTrajectory ()
{
    for (int l = 0; l < length; l++)
		delete states[l];
	delete [] states;
}


void VoterTrajectory::print ()
{
    std::cout << "START:  ";

    if (length > 0)
    {
		std::cout << "[0] ";
		states[0]->print();

		for (int l = 1; l < length; l++)
		{
			std::cout << "  ->  [" << l << "] ";
			states[l]->print();
		}
    }
    std::cout << std::endl;
}


VoterMeasurementTrajectory::VoterMeasurementTrajectory (VoterMeasurement *m, VoterTrajectory *trajectory)
{
	measurement = m;
    graph = measurement->graph;
    length = trajectory->length;

    states = new VoterMeasurementState *[length];

	for (int l = 0; l < length; l++)
		states[l] = measurement->getState(trajectory->states[l]);
}


VoterMeasurementTrajectory::~VoterMeasurementTrajectory ()
{
    for (int l = 0; l < length; l++)
		delete states[l];
	delete [] states;
}


void VoterMeasurementTrajectory::print ()
{
    std::cout << "START:  ";

    if (length > 0)
    {
		std::cout << "[0] ";
		states[0]->print();

		for (int l = 1; l < length; l++)
		{
			std::cout << "  ->  [" << l << "] ";
			states[l]->print();
		}
    }
    std::cout << std::endl;
}


VoterDataSet::VoterDataSet (VoterGraph *g, int s, int t, int l)
{
    graph = g;
    size = s;
    time = t;
    length = l;

    trajectories = new VoterTrajectory *[size];
    for (int tr = 0; tr < size; tr++) { trajectories[tr] = new VoterTrajectory(graph, length); }
}


VoterDataSet::~VoterDataSet ()
{
    for (int t = 0; t < size; t++) { delete trajectories[t]; }
    delete[] trajectories;
}



double VoterDataSet::computeScore (VoterMeasurement *preM, VoterMeasurement *postM, int delay, int trainingLength)
{
    if (trainingLength + delay > length) { std::cout << "ERROR: the size of the training set is inconsistent!" << std::endl; return -1; }


    // Estimate the transition matrix by the empirical distribution on the training set

    // initialise
	TransitionMap *trainMap = new TransitionMap();
	
    // count occurrences
    for (int t = 0; t < size; t++)
    {
		VoterTrajectory *traj = trajectories[t];
		for (int l = 0; l < trainingLength; l++)
		{
			VoterMeasurementState preS = *preM->getState(traj->states[l]);
			VoterMeasurementState postS = *postM->getState(traj->states[l+delay]);

			//preS.print();
			//postS.print();
			//std::cout << std::endl;

			bool found1 = false;
			TransitionMap::iterator it1;
			for (it1 = trainMap->begin(); it1 != trainMap->end() && !found1; ++it1)
			{
				VoterMeasurementState pS = it1->first;
				if (!(preS < pS || pS < preS)) { found1 = true; break; }
			}

			if (found1)
			{
				ProbabilityMap *probMap = it1->second;

				bool found2 = false;
				ProbabilityMap::iterator it2;
				for (it2 = probMap->begin(); it2 != probMap->end() && !found2; ++it2)
				{
					VoterMeasurementState pS = it2->first;
					if (!(postS < pS || pS < postS)) { found2 = true; break; }
				}

				if (found2)
				{
					it2->second = it2->second+1;
					//std::cout << "INCR" << std::endl;
				}
						
				else {
					probMap->insert(std::pair<VoterMeasurementState,double>(postS,1));
					//std::cout << "ADD 2" << std::endl;
				}
			}

			else {
				ProbabilityMap *probMap = new ProbabilityMap();
				probMap->insert(std::pair<VoterMeasurementState,double>(postS,1));
				trainMap->insert(std::pair<VoterMeasurementState,ProbabilityMap*>(preS,probMap));
				//std::cout << "ADD 1" << std::endl;
			}
		}
	}

    // normalise
	for (TransitionMap::iterator it1 = trainMap->begin(); it1 != trainMap->end(); ++it1)
	{
		VoterMeasurementState preS = it1->first;
		ProbabilityMap *probMap = it1->second;
		double total = 0;
		
		for (ProbabilityMap::iterator it2 = probMap->begin(); it2 != probMap->end(); ++it2)
		{
			VoterMeasurementState postS = it2->first;
			total += it2->second;
		}

		for (ProbabilityMap::iterator it2 = probMap->begin(); it2 != probMap->end(); ++it2)
		{
			VoterMeasurementState postS = it2->first;
			it2->second /= total;
		}
	}
	
	// print
	for (TransitionMap::iterator it1 = trainMap->begin(); it1 != trainMap->end(); ++it1)
	{
		VoterMeasurementState preS = it1->first;
		ProbabilityMap *probMap = it1->second;
		for (ProbabilityMap::iterator it2 = probMap->begin(); it2 != probMap->end(); ++it2)
		{
			VoterMeasurementState postS = it2->first;
			double prob = it2->second;

			std::cout << "from ";
			preS.print();
			std::cout << " to ";
			postS.print();
			std::cout << " with probability " << prob << std::endl;
		}
	}
	
	/*
		  int width = 10; int prec = 4;

		  std::cout << "        ";
		  for (int j = 0; j < postP->size; j++) { std::cout << std::setw(width+2) << j; }
		  std::cout << std::endl;

		  for (int i = 0; i < preM->probeNumber; i++)
		  {
		  std::cout << "p(.|" << i << ") = {";
		  if (postP->size > 0) { std::cout << std::setw(width) << std::setprecision(prec) << trainDist[0 * preM->probeNumber + i]; }
		  if (postP->size > 1)
		  {
		  for (int j = 1; j < postP->size; j++) { std::cout << ", " << std::setw(width) << std::setprecision(prec) << trainDist[j * preM->probeNumber + i]; }
		  }
		  std::cout << "}" << std::endl;
		  }
		  std::cout << std::endl;
		*/

		/*
		// compute score
		int count = 0;
		double score = 0;
		for (int t = 0; t < size; t++)
		{
		VoterTrajectory *traj = trajectories[t];
		for (int time = trainingLength; time < length - delay; time++)
		{
	    Part *prePart = preP->findPart(traj->states[time]);
	    Part *postPart = postP->findPart(traj->states[time+delay]);
	    double prob = trainDist[postPart->id * preM->probeNumber + prePart->id];
	    if (prob == 0) { return -1; }

	    score += -log(prob);
	    count++;
		}
		}
		if (count > 0) { return score/count; }
		else { return 0; }
		*/
		return 0;	
}

