#ifndef INCLUDE_VOTER_GRAPH
#define INCLUDE_VOTER_GRAPH

#include <map>

#include "markov_process.hpp"
#include "partition.hpp"

const bool METRIC_MACRO_STATE = 0;
const bool METRIC_ACTIVE_EDGES = 1;

const bool UPDATE_NODES = 0;
const bool UPDATE_EDGES = 1;


class VoterNode;
class VoterEdge;
class VoterGraph;
class VoterProbe;
class VoterMeasurement;

typedef std::set<VoterMeasurement*> MeasurementSet;

class VoterNode
{
	public:
		int id;
		double weight;
		double contrarian;

		int inEdgeWeight;
		int inEdgeNumber;
		std::set<VoterEdge*> *inEdgeSet;

		int outEdgeWeight;
		int outEdgeNumber;
		std::set<VoterEdge*> *outEdgeSet;

		VoterNode (int id, double weight = 1, double contrarian = 0);
		~VoterNode ();
};


class VoterEdge
{
	public:
		VoterNode *node1;
		VoterNode *node2;
		double weight;

		VoterEdge (VoterNode *node1, VoterNode *node2, double weight = 1);
		~VoterEdge ();		
};


class VoterGraph
{
	public:
		int updateProcess;
		
		int nodeNumber;
		int edgeNumber;

		double nodeWeight;
		double edgeWeight;
		
		std::map<int,VoterNode*> *nodeMap;
		std::set<VoterNode*> *nodeSet;
		std::set<VoterEdge*> *edgeSet;
		
		MarkovProcess *process;
		
		VoterGraph (int update = UPDATE_EDGES);
		~VoterGraph ();
		
		void print ();

		VoterNode *addNode (double weight = 1, double contrarian = 0);
		VoterEdge *addEdge (VoterNode *node1, VoterNode *node2, double weight = 1);
		void fillEdges ();
		
		MarkovProcess *getMarkovProcess ();
		Partition *getMarkovPartition (VoterProbe *probe, int metric);
		Partition *getMarkovPartition (VoterMeasurement *measurement);
};


class CompleteVoterGraph : public VoterGraph
{
	public :
		CompleteVoterGraph (int size, int update = UPDATE_EDGES, double contrarian = 0);
};


class TwoCommunitiesVoterGraph : public VoterGraph
{
	public :
		int size1;
		int size2;
		
		double intraRate1;
		double intraRate2;
		double interRate1;
		double interRate2;
		
		std::set<VoterNode*> *community1;
		std::set<VoterNode*> *community2;
		
		TwoCommunitiesVoterGraph (int size1, int size2,
			double intraRate1, double intraRate2, double interRate1, double interRate2,
			double contrarian = 0, int update = UPDATE_EDGES);

		~TwoCommunitiesVoterGraph ();

		MarkovProcess *getCompactMarkovProcess();
		Partition *getCompactMarkovPartition (VoterProbe *probe, int metric);
		Partition *getCompactMarkovPartition (VoterMeasurement *measurement);
};


class VoterProbe
{
	public:
		VoterGraph *graph;
		int nodeNumber;
		std::set<VoterNode*> *nodeSet;

		VoterProbe (VoterGraph *graph);
		~VoterProbe ();

		void addNode (VoterNode *node);
		void addNodes (unsigned long int i);
		void print (bool endl = false);
};


class VoterMeasurement
{
	public:
		VoterGraph *graph;
		std::string type;
		Partition *partition;
		
		int probeNumber;
		std::map<int,VoterProbe*> *probeMap;
		std::map<int,int> *metricMap;
		
		VoterMeasurement (VoterGraph *graph, std::string type);
		~VoterMeasurement ();

		void addProbe (VoterProbe *probe, int metric);
		void print (bool endl = false);
};


class MacroVoterMeasurement : public VoterMeasurement
{
	public :
		MacroVoterMeasurement (VoterGraph *graph, std::set<int> metric);
};


class MicroVoterMeasurement : public VoterMeasurement
{
	public :
		MicroVoterMeasurement (VoterGraph *graph, std::set<int> metric);
};


class EmptyVoterMeasurement : public VoterMeasurement
{
	public :
		EmptyVoterMeasurement (VoterGraph *graph);
};



#endif
