#ifndef INCLUDE_VOTER_GRAPH
#define INCLUDE_VOTER_GRAPH

/*!
 * \file voter_graph.hpp
 * \brief  Building the interaction graph and measurement of a Voter Model
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 *
 * Classes to build an interaction graph (nodes and edges) describing a Voter Model and some observation tools (probes and measurements)
 *
 */
 

#include <map>

#include "markov_process.hpp"
#include "partition.hpp"

const bool METRIC_MACRO_STATE = 0;	/*!< Metric of a probe indicating the number of observed nodes in state 1*/
const bool METRIC_ACTIVE_EDGES = 1; /*!< Metric of a probe indicating the probability that one of the observed nodes will change during the next simulation step*/

const bool UPDATE_NODES = 0;	/*!< Update process of the Voter Model where a node is chosen at each simulation step, and this node acts on one of its outcoming nodes*/
const bool UPDATE_EDGES = 1;	/*!< Update process of the Voter Model where an edge is chosen at each simulation step, and the incoming node acts on the outcoming node*/


class VoterNode;
class VoterEdge;
class VoterGraph;
class VoterProbe;
class VoterMeasurement;

typedef std::set<VoterMeasurement*> MeasurementSet;

/*!
 * \class VoterNode
 * \brief A node of the interaction graph
 */
class VoterNode
{
	public:
		int id;					/*!< Unique id within the graph*/
		double weight;			/*!< Determines the probability to select this node (relatively to other nodes) at each simulation step when the updateProcess variable of the graph is set to UPDATE_NODES*/
		double contrarian;		/*!< Contrarian rate of the node*/

		int inEdgeWeight;		/*!< Sum of the weight of incoming nodes*/
		int inEdgeNumber;		/*!< Sum of the weight of incoming edges*/
		std::set<VoterEdge*> *inEdgeSet;	/*!< Set of incoming edges*/

		int outEdgeWeight;		/*!< Sum of the weight of outcoming nodes*/
		int outEdgeNumber;		/*!< Sum of the weight of outcoming edges*/
		std::set<VoterEdge*> *outEdgeSet;	/*!< Set of outcoming edges*/

		/*!
		* \brief Constructor
		* \param id : Unique id within the graph
		* \param weight : Determines the probability to select this node (relatively to other nodes) at each simulation step when the updateProcess variable of the graph is set to UPDATE_NODES
		* \param contrarian : Contrarian rate of the node
		*/
		VoterNode (int id, double weight = 1, double contrarian = 0);

		/*!
		* \brief Destructor
		*/
		~VoterNode ();
};


/*!
 * \class VoterEdge
 * \brief An edge of the interaction graph
 */
class VoterEdge
{
	public:
		VoterNode *node1;		/*!< Incoming node*/
		VoterNode *node2;		/*!< Outcoming node*/
		double weight;			/*!< Determines the probability to select this edge (relatively to other edges) at each simulation step when the updateProcess variable of the graph is set to UPDATE_EDGES*/

		/*!
		* \brief Constructor
		* \param node1 : Incoming node
		* \param node2 : Outcoming node
		* \param weight : Determines the probability to select this edge (relatively to other edges) at each simulation step when the updateProcess variable of the graph is set to UPDATE_EDGES
		*/
		VoterEdge (VoterNode *node1, VoterNode *node2, double weight = 1);

		/*!
		* \brief Destructor
		*/
		~VoterEdge ();		
};


/*!
 * \class VoterGraph
 * \brief The interaction graph describing a Voter Model
 */
class VoterGraph
{
	public:
		int updateProcess;		/*!< How the system evolves at each simulation step (UPDATE_NODES or UPDATE_EDGES)*/
		
		int nodeNumber;			/*!< The total number of nodes in the graph*/
		int edgeNumber;			/*!< The total number of edges in the graph*/

		double nodeWeight;		/*!< The sum of the weight of all nodes*/
		double edgeWeight;		/*!< The sum of the weight of all edges*/
		
		std::map<int,VoterNode*> *nodeMap;	/*!< The map of all nodes organized by id*/
		std::set<VoterNode*> *nodeSet;		/*!< The set of all nodes*/
		std::set<VoterEdge*> *edgeSet;		/*!< The set of all edges*/
		
		MarkovProcess *process;		/*!< The Markov chain associated to the described Voter Model*/
		
		/*!
		* \brief Constructor
		* \param update : How the system evolves at each simulation step (UPDATE_NODES or UPDATE_EDGES)
		*/
		VoterGraph (int update = UPDATE_EDGES);

		/*!
		* \brief Destructor
		*/
		~VoterGraph ();
		
		/*!
		* \brief Print the graph
		*/
		void print ();

		/*!
		* \brief Add a node to the graph
		* \param weight : Determines the probability to select the node to be added (relatively to other nodes) at each simulation step when the updateProcess variable of the graph is set to UPDATE_NODES
		* \param contrarian : The contrarian rate of the node to be added
		* \return The added node
		*/
		VoterNode *addNode (double weight = 1, double contrarian = 0);

		/*!
		* \brief Add an edge to the graph
		* \param node1 : Incoming node
		* \param node2 : outcoming node
		* \param weight : Determines the probability to select the edge to be added (relatively to other edges) at each simulation step when the updateProcess variable of the graph is set to UPDATE_EDGES
		* \return The added edge
		*/
		VoterEdge *addEdge (VoterNode *node1, VoterNode *node2, double weight = 1);

		/*!
		* \brief Add an edge between each pair of nodes in the graph (in both direction, with equal weight for each edge)
		*/
		void fillEdges ();
		
		/*!
		* \brief Build the Markov chain associated to the described Voter Model
		* \return The computed Markov chain
		*/
		MarkovProcess *getMarkovProcess ();
		
		/*!
		* \brief Build the partition of the Markov chain state space associated to a probe with a given metric (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES)
		* \param probe : The probe used to partition the state space
		* \param metric : The metric of the probe (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES)
		* \return The computed partition
		*/
		Partition *getMarkovPartition (VoterProbe *probe, int metric);

		/*!
		* \brief Build the partition of the Markov chain state space associated to a measurement (i.e., a set of probes)
		* \param measurement : The measurement used to partition the state space
		* \return The computed partition
		*/
		Partition *getMarkovPartition (VoterMeasurement *measurement);
};


/*!
 * \class CompleteVoterGraph
 * \brief An interaction graph with edges between each pair of nodes (in both direction, with equal weight for each edge)
 */
class CompleteVoterGraph : public VoterGraph
{
	public :
		/*!
		* \brief Constructor
		* \param size : Size of the graph
		* \param update : How the system evolves at each simulation step (UPDATE_NODES or UPDATE_EDGES)
		* \param contrarian : The contrarian rate of each node
		*/
		CompleteVoterGraph (int size, int update = UPDATE_EDGES, double contrarian = 0);
};


/*!
 * \class TwoCommunitiesVoterGraph
 * \brief An interaction graph consisting in two communities of nodes (complete graph within each community, complete interaction between the two communities, possibly with different weights)
 */
class TwoCommunitiesVoterGraph : public VoterGraph
{
	public :
		int size1;			/*!< The size of community 1*/
		int size2;			/*!< The size of community 2*/
		
		double intraRate1;	/*!< The weight of edges within community 1*/
		double intraRate2;	/*!< The weight of edges within community 2*/
		double interRate1;	/*!< The weight of edges from community 1 to community 2*/
		double interRate2;	/*!< The weight of edges from community 2 to community 1*/
		
		std::set<VoterNode*> *community1;	/*!< The set of nodes in community 1*/
		std::set<VoterNode*> *community2;	/*!< The set of nodes in community 2*/
		
		/*!
		* \brief Constructor
		* \param size1 : The size of community 1
		* \param size2 : The size of community 2
		* \param intraRate1 : The weight of edges within community 1
		* \param intraRate2 : The weight of edges within community 2
		* \param interRate1 : The weight of edges from community 1 to community 2
		* \param interRate2 : The weight of edges from community 2 to community 1
		* \param contrarian : The contrarian rate of each node
		* \param update : How the system evolves at each simulation step (UPDATE_NODES or UPDATE_EDGES)
		*/
		TwoCommunitiesVoterGraph (int size1, int size2,
			double intraRate1, double intraRate2, double interRate1, double interRate2,
			double contrarian = 0, int update = UPDATE_EDGES);

		/*!
		* \brief Destructor
		*/
		~TwoCommunitiesVoterGraph ();

		/*!
		* \brief Build the Markov chain associated to the graph, lumped according to the macro-state of community 1, the macro-state of community 2, and the state of the first agent in community 1
		* \return The computed lumped Markov chain
		*/
		MarkovProcess *getCompactMarkovProcess();

		/*!
		* \brief Build the partition of the lumped Markov chain state space (see getCompactMarkovProcess) associated to a probe with a given metric (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES)
		* \param probe : The probe used to partition the lumped state space
		* \param metric : The metric of the probe (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES)
		* \return The computed partition over the lumped state space
		*/
		Partition *getCompactMarkovPartition (VoterProbe *probe, int metric);

		/*!
		* \brief Build the partition of the lumped Markov chain state space (see getCompactMarkovProcess) associated to a measurement (i.e., a set of probes)
		* \param measurement : The measurement used to partition the lumped state space
		* \return The computed partition over the lumped state space
		*/
		Partition *getCompactMarkovPartition (VoterMeasurement *measurement);
};



/*!
 * \class VoterProbe
 * \brief A probe to observe the Voter Model according to a subset of nodes
 */
class VoterProbe
{
	public:
		VoterGraph *graph;					/*!< The interaction graph to be observed*/
		int nodeNumber;						/*!< The number of observed nodes*/
		std::set<VoterNode*> *nodeSet;		/*!< The set of observed nodes*/

		/*!
		* \brief Constructor
		* \param graph : The interaction graph to be observed
		*/
		VoterProbe (VoterGraph *graph);

		/*!
		* \brief Destructor
		*/
		~VoterProbe ();

		/*!
		* \brief Add an observed node to the probe
		* \param node : The node to be added
		*/
		void addNode (VoterNode *node);

		/*!
		* \brief Add a set of observed nodes to the probe
		* \param graph : A binary number indicating for each node of the graph if it should (1) or should not (0) be added (the nodes are ordered according to their unique id)
		*/
		void addNodes (unsigned long int i);

		/*!
		* \brief Print the probe details
		* \param endl : Line break after printing if true
		*/
		void print (bool endl = false);
};


/*!
 * \class VoterMeasurement
 * \brief A measurement to observe the Voter Model according set of probes
 */
class VoterMeasurement
{
	public:
		VoterGraph *graph;		/*!< The interaction graph to be observed*/
		std::string type;		/*!< The name of the measurement*/
		Partition *partition;	/*!< The partition of the Markov chain state space corresponding to the measurement*/
		
		int probeNumber;		/*!< The number of probes constituting the measurement*/
		std::map<int,VoterProbe*> *probeMap;	/*!< The map of constituting probes organized by probe numbers*/
		std::map<int,int> *metricMap;			/*!< The map of metrics (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES) associated to each constituting probe organized by probe numbers*/
		
		/*!
		* \brief Constructor
		* \param graph : The interaction graph to be observed
		* \param type : The name of the measurement
		*/
		VoterMeasurement (VoterGraph *graph, std::string type);

		/*!
		* \brief Destructor
		*/
		~VoterMeasurement ();

		/*!
		* \brief Add a probe to the measurement
		* \param node : The probe to be added
		* \param metric : The metric associated to the added probe (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES)
		*/
		void addProbe (VoterProbe *probe, int metric);

		/*!
		* \brief Print the measurement details
		* \param endl : Line break after printing if true
		*/
		void print (bool endl = false);
};


/*!
 * \class MacroVoterMeasurement
 * \brief A measurement consisting in one probe observing all nodes of the interaction graph
 */
class MacroVoterMeasurement : public VoterMeasurement
{
	public :
		/*!
		* \brief Constructor
		* \param graph : The interaction graph to be observed
		* \param metric : The metric associated to the added probe (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES)
		*/
		MacroVoterMeasurement (VoterGraph *graph, std::set<int> metric);
};


/*!
 * \class MicroVoterMeasurement
 * \brief A measurement consisting in one probe for each node of the interaction graph
 */
class MicroVoterMeasurement : public VoterMeasurement
{
	public :
		/*!
		* \brief Constructor
		* \param graph : The interaction graph to be observed
		* \param metric : The metric associated to the added probe (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES)
		*/
		MicroVoterMeasurement (VoterGraph *graph, std::set<int> metric);
};


/*!
 * \class EmptyVoterMeasurement
 * \brief A measurement without any probe (no observation)
 */
class EmptyVoterMeasurement : public VoterMeasurement
{
	public :
		/*!
		* \brief Constructor
		* \param graph : The interaction graph to be observed
		*/
		EmptyVoterMeasurement (VoterGraph *graph);
};



#endif
