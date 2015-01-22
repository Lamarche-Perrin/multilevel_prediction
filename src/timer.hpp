#ifndef INCLUDE_TIMER
#define INCLUDE_TIMER

#include <list>
#include <time.h>


typedef struct DataPointStruct
{
	int size;
	float time;
	int memory;
} DataPoint;


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
