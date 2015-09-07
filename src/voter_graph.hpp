#ifndef INCLUDE_VOTER_GRAPH
#define INCLUDE_VOTER_GRAPH

/*!
 * \file voter_graph.hpp
 * \brief Classes to build an interaction graph (nodes and edges) describing a Voter Model and some observation tools (probes and measurements)
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */
 

#include <map>
#include <cstdlib>

#include "markov_process.hpp"
#include "partition.hpp"

/*!
 * \brief A metric associated to a probe
 */
enum VoterMetric {
    MACRO_STATE,		/*!< The probe returns the number of observed nodes in state 1*/
    MAJORITY,			/*!< The probe returns 0 (resp. 1) if the majority of agents are in state 0 (resp. 1), and NA if there is a strict equality*/
    MAJ_1PC, MAJ_2PC, MAJ_3PC, MAJ_4PC, MAJ_5PC, MAJ_6PC, MAJ_7PC, MAJ_8PC, MAJ_9PC,
    MAJ_10PC, MAJ_20PC, MAJ_30PC, MAJ_40PC, MAJ_50PC, MAJ_60PC, MAJ_70PC, MAJ_80PC, MAJ_90PC,
    MAJ_2B, MAJ_3B, MAJ_4B, MAJ_6B, MAJ_8B, MAJ_10B, MAJ_12B, MAJ_20B, MAJ_40B,
    ACTIVE_EDGES		/*!< The probe returns the probability that one of the observed nodes will change during the next simulation step*/
};

/*!
 * \brief The way a Voter Model evolves at each simulation step, by randomly choosing a node or an edge for interaction
 */
enum UpdateProcess {
    UPDATE_NODES,		/*!< Node-driven interactions: A node is chosen at each simulation step, it acts on one of its outcoming nodes*/
    UPDATE_EDGES		/*!< Edge-driven interactions: An edge is chosen at each simulation step, its incoming node acts on its outcoming node*/
};


/*!
 * \brief A specific measurement in the case of a two-communities interaction graphs
 */
enum MeasurementType {
    M_MICRO,				/*!< Microscopic state*/
    M_AGENT1,				/*!< State of the first node in community 1*/
    M_MESO1,				/*!< Aggregated state of all nodes in community 1*/
    M_MESO2,				/*!< Aggregated state of all nodes in community 2*/
    M_MACRO,				/*!< Aggregated state of nodes in both communities*/
    M_EMPTY,				/*!< No observation*/
    M_ALLSIZES1,			/*!< Aggregated state of node subsets of all sizes within community 1*/
    M_SOMESIZES1,			/*!< Aggregated state of node subsets of some sizes within community 1*/
    M_AGENT1_ALLSIZES1,		/*!< Join measurement (see above)*/
    M_AGENT1_SOMESIZES1,	/*!< Join measurement (see above)*/
    M_ALLNEIGHBORHOODS,
    M_AGENT1_MESO1,			/*!< Join measurement (see above)*/
    M_AGENT1_MESO2,			/*!< Join measurement (see above)*/
    M_AGENT1_MACRO,			/*!< Join measurement (see above)*/
    M_AGENT1_MESO1_MESO2,	/*!< Join measurement (see above)*/
    M_MESO1_MESO2			/*!< Join measurement (see above)*/
};


class VoterNode;
class VoterEdge;
class VoterGraph;
class VoterProbe;
class VoterState;
class VoterTrajectory;
class VoterMeasurement;
class VoterMeasurementState;
class VoterMeasurementTrajectory;

long unsigned int nChoosek (int n, int k);

typedef std::set<VoterMeasurement*> MeasurementSet;
typedef std::set< std::pair<MeasurementType,VoterMetric> > SpecMeasurementSet;

typedef std::map<VoterMeasurementState,double> ProbabilityMap;
typedef std::map<VoterMeasurementState,ProbabilityMap*> TransitionMap;

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

    VoterEdge *getRandomEdge();
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
    virtual ~VoterGraph ();
		
    /*!
     * \brief Print the graph structure and details
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

    
    VoterNode *getRandomNode ();
		
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
    Partition *getMarkovPartition (VoterProbe *probe, VoterMetric metric);

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
		
    double contrarian1;	/*!< The contrarian rate of nodes in community 1*/
    double contrarian2; /*!< The contrarian rate of nodes in community 2*/

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
     * \param contrarian1 : The contrarian rate of nodes in community 1
     * \param contrarian2 : The contrarian rate of nodes in community 2
     * \param update : How the system evolves at each simulation step (UPDATE_NODES or UPDATE_EDGES)
     */
    TwoCommunitiesVoterGraph (int size1, int size2,
			      double intraRate1, double intraRate2, double interRate1, double interRate2,
			      double contrarian1, double contrarian2, int update = UPDATE_EDGES);

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
    Partition *getCompactMarkovPartition (VoterProbe *probe, VoterMetric metric);

    /*!
     * \brief Build the partition of the lumped Markov chain state space (see getCompactMarkovProcess) associated to a measurement (i.e., a set of probes)
     * \param measurement : The measurement used to partition the lumped state space
     * \return The computed partition over the lumped state space
     */
    Partition *getCompactMarkovPartition (VoterMeasurement *measurement);
};




class ChainVoterGraph : public VoterGraph
{
public :
    int size;
    double contrarian;
    VoterNode **nodeArray;
    bool ring;
    
    ChainVoterGraph (int size, double contrarian = 0, bool ring = false, int update = UPDATE_EDGES);
    ~ChainVoterGraph ();
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
     * \brief Set the set of observed nodes
     * \param node : The set to be associated
     */
    void setNodeSet (std::set<VoterNode*> *set);

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

	int getState (VoterState *state, VoterMetric metric);

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
    std::map<int,VoterMetric> *metricMap;	/*!< The map of metrics (e.g., METRIC_MACRO_STATE of METRIC_ACTIVE_EDGES) associated to each constituting probe organized by probe numbers*/
		
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
    void addProbe (VoterProbe *probe, VoterMetric metric);

	VoterMeasurementState *getState (VoterState *state);
	
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
     * \param metrics : The set of metrics associated to the macro-probe
     */
    MacroVoterMeasurement (VoterGraph *graph, std::set<VoterMetric> metrics);
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
     * \param metric : The set of metric associated to the micro-probe
     */
    MicroVoterMeasurement (VoterGraph *graph, std::set<VoterMetric> metric);
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



class VoterState
{
public:
    VoterGraph *graph;

    int size;
    bool *agentStates;

    VoterState (VoterGraph *graph);
    VoterState (VoterState *state);
    ~VoterState ();

    void print ();

    void setFromMicroUniform();
    void setFromMacroUniform();

    VoterState *getNextState();
};


class VoterMeasurementState
{
public:
	VoterMeasurement *measurement;
	int size;
	int *probeStates;

	VoterMeasurementState (VoterMeasurement *measurement);
	VoterMeasurementState (const VoterMeasurementState& state);
	~VoterMeasurementState ();

	void init (int value);
	void computeId ();
	
	void print ();
};

	
class VoterTrajectory
{
public:
    VoterGraph *graph;

    int length;
    VoterState **states;

    VoterTrajectory (VoterGraph *graph, int length);
    ~VoterTrajectory ();

    void print ();
};


class VoterMeasurementTrajectory
{
public:
	VoterMeasurement *measurement;
    VoterGraph *graph;

    int length;
    VoterMeasurementState **states;

    VoterMeasurementTrajectory (VoterMeasurement *measurement, VoterTrajectory *trajectory);
    ~VoterMeasurementTrajectory ();

    void print ();
};


class VoterDataSet
{
public:
	VoterGraph *graph;

    int size;
	int time;
    int length;
    VoterTrajectory **trajectories;

    VoterDataSet (VoterGraph *graph, int size, int time, int length);
    ~VoterDataSet ();

    double computeScore (VoterMeasurement *preM, VoterMeasurement *postM, int delay, int trainingLength);
};

#endif
