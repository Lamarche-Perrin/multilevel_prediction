/*!
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */

#include <iostream>
#include <iomanip>

#include "partition.hpp"


Part::Part ()
{
    id = -1;
    size = 0;
    value = -2;
    individuals = new std::list<int>();
}


Part::Part (Part *p)
{
    individuals = new std::list<int>();
    for (std::list<int>::iterator it = p->individuals->begin(); it != p->individuals->end(); ++it) { addIndividual(*it); }
}


Part::~Part ()
{
    delete individuals;
}


void Part::addIndividual (int i, bool front, int v)
{
    size++;
    if (v != -1)
    {
	if (value == -2) { value = v; }
	else if (value != v) { value = -1; }
    }
	
    if (front) { individuals->push_front(i); }
    else { individuals->push_back(i); }
}


bool Part::contains (int i)
{
    for (std::list<int>::iterator it = individuals->begin(); it != individuals->end(); ++it)
	if (*it == i) return true;
    return false;
}


bool Part::equal (Part *p)
{
    if (individuals->size() != p->individuals->size()) return false;
	
    for (std::list<int>::iterator it1 = individuals->begin(); it1 != individuals->end(); ++it1)
    {
	int i1 = *it1;
		
	bool found = false;
	for (std::list<int>::iterator it2 = p->individuals->begin(); it2 != p->individuals->end(); ++it2)
	{
	    int i2 = *it2;
	    if (i1 == i2) { found = true; break; }
	}
		
	if (!found) return false;
    }
    return true;
}



void Part::print (bool endl)
{
    std::cout << "{";
    bool first = true;
    for (std::list<int>::iterator it = individuals->begin(); it != individuals->end(); ++it)
    {
	if (first) { first = false; } else { std::cout << ","; }
	std::cout << (*it);
    }
    std::cout << "}";
    if (endl) { std::cout << std::endl; }
}

int Part::printSize () { return 2*individuals->size()+1; }



Partition::Partition ()
{
    size = 0;
    parts = new std::list<Part*>();
}


Partition::Partition (Partition *p)
{
    parts = new std::list<Part*>();
    for (std::list<Part*>::iterator it = p->parts->begin(); it != p->parts->end(); ++it)
    {
	Part *part = new Part(*it);
	addPart(part);
    }
}


Partition::~Partition ()
{
    parts->clear();
    delete parts;
}


void Partition::addPart (Part *p, bool front)
{
    p->id = size++;
    if (front) { parts->push_front(p); } else { parts->push_back(p); }
}


Part *Partition::findPart (int i)
{
    for (std::list<Part*>::iterator it = parts->begin(); it != parts->end(); ++it)
    {
	Part *p = *it;
	if (p->contains(i)) { return p; }
    }
    return 0;
}


Part *Partition::getPartFromValue (int v)
{
    Part *rp = 0;
    for (std::list<Part*>::iterator it = parts->begin(); it != parts->end(); ++it)
    {
	Part *p = *it;
	if (p->value == v)
	{
	    if (rp != 0)
	    {
		std::cout << "ERROR: several parts with the same value!" << std::endl;
		return 0;
	    }
	    rp = p;
	}
    }
    return rp;
}


bool Partition::equal (Partition *p)
{
    if (parts->size() != p->parts->size()) return false;
	
    for (std::list<Part*>::iterator it1 = parts->begin(); it1 != parts->end(); ++it1)
    {
	Part *p1 = *it1;
		
	bool found = false;
	for (std::list<Part*>::iterator it2 = p->parts->begin(); it2 != p->parts->end(); ++it2)
	{
	    Part *p2 = *it2;
	    if (p1->equal(p2)) { found = true; break; }
	}
		
	if (!found) return false;
    }
    return true;
}


void Partition::print (bool endl)
{
    int printSize = 1;
    for (std::list<Part*>::iterator it = parts->begin(); it != parts->end(); ++it)
    {
	Part *part = *it;
	part->print();
	std::cout << " ";
	printSize += part->printSize() + 1;
    }
    if (endl) { std::cout << std::endl; }
}


