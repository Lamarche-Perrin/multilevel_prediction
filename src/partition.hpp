#ifndef INCLUDE_PARTITION
#define INCLUDE_PARTITION

#include <set>
#include <list>

class Part;
class Partition;

typedef std::set<Part*> PartSet;
typedef std::list<Partition*> PartitionList;


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
