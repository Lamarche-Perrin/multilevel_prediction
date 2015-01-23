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
		std::list<int> *individuals;
	
		Part ();
		Part (Part *part);
		~Part ();
	
		void addIndividual (int i, bool front = false);
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
		std::list<Part*> *parts;
		
		Partition ();
		Partition (Partition *partition);
		~Partition ();
		
		void addPart (Part *p, bool front = false);
		bool equal (Partition *p);
		void print (bool endl = false);
};

#endif
