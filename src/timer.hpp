#ifndef INCLUDE_TIMER
#define INCLUDE_TIMER

/*!
 * \file timer.hpp
 * \brief Tools to mesure computation times and memory consumption during the program execution
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */


#include <list>
#include <time.h>

/*!
 * \brief The computation time and memory consumption associated to an experiment of a given size
 */
typedef struct DataPointStruct
{
	int size;
	float time;
	int memory;
} DataPoint;


/*!
 * \brief A timer mesuring computation times and memory consumption during the program execution
 */
class Timer
{
	public:
		Timer (char *file = 0);
		~Timer ();

		void start (int size, std::string text = "");
		void startTime ();
		void startMemory ();
		
		void stop (std::string text = "");
		void stopTime ();
		void stopMemory ();

		void step (std::string text = "");
		void print (char *fName);

	private:
		int id;
		char *fileName;
		clock_t sTime;
		clock_t eTime;
		clock_t iTime;
		float time;
		
		int sMemory;
		int eMemory;
		int iMemory;
		int memory;
	
		std::list<DataPoint*> *data;
		DataPoint *currentDataPoint;
};

int getMemory ();

#endif
