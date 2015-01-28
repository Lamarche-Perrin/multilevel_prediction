#ifndef INCLUDE_PARTITION
#define INCLUDE_PARTITION

/*!
 * \file partition.hpp
 * \brief Classes to build partitions of the state space of Markov chains
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */
 

#include <set>
#include <list>

class Part;
class Partition;

typedef std::set<Part*> PartSet;
typedef std::list<Partition*> PartitionList;

/*!
 * \class Part
 * \brief A part of a partition (i.e., a set of individuals)
 */
class Part
{
	public:
		int id;
		int size;
		
		int value;
		std::list<int> *individuals;
	
		Part ();
		Part (Part *part);
		~Part ();
	
		void addIndividual (int i, bool front = false, int value = -1);
		virtual bool equal (Part *p);
		
		virtual void print (bool endl = false);
		virtual int printSize ();
};



/*!
 * \class Partition
 * \brief A partition (i.e., a set of disjoint and covering parts)
 */
class Partition
{
	public:
		int size;
		std::list<Part*> *parts;
		
		Partition ();
		Partition (Partition *partition);
		~Partition ();
		
		void addPart (Part *p, bool front = false);
		Part *getPartFromValue (int value);
		
		bool equal (Partition *p);
		void print (bool endl = false);
};


class OrderedPartition
{
	public:
		int microSize;
		int *optimalCut;
		double param;
		double beta;
	
		std::string string;
		double entropy;
		double information;
	
		OrderedPartition (int s, double p) : microSize(s), param(p) { beta = param / (1 - param); };
	
		void print ()
		{
			std::cout << "beta = " << beta << " -> ";
			for (int i = 0; i < microSize; i++) { std::cout << optimalCut[i] << "\t"; }
			std::cout << std::endl;
		}
};

#endif
