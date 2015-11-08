/*
 * This file is part of Multilevel Prediction.
 *
 * Multilevel Prediction is a toolbox to compute optimal predictors of Markov
 * chains, and in particular multilevel agent-based systems, by using the
 * information bottleneck method. For details regarding the formal grounds of
 * this method, please refer to:
 * 
 * Robin Lamarche-Perrin, Sven Banisch, and Eckehard Olbrich. The Information
 * Bottleneck Method for Optimal Prediction of Multilevel Agent-based Systems.
 * Technical Report MIS-Preprint 55/2015, Max Planck Institute for Mathematics
 * in the Sciences, Leipzig, Germany, 2015.
 * 
 * <http://www.mis.mpg.de/publications/preprints/2015/prepr2015-55.html>
 * 
 * Copyright © 2015 Robin Lamarche-Perrin (<Robin.Lamarche-Perrin@lip6.fr>)
 * 
 * Multilevel Prediction is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * Multilevel Prediction is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */


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
	//void print (char *fName);

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
