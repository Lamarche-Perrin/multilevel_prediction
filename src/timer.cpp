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


/*!
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */

#include <iostream>
#include <time.h>
#include <cstdio>
#include <stdio.h>
//#include <Psapi.h>
//#include <Windows.h>

#include "timer.hpp"

int timer_id = 0;


Timer::Timer (char *fName)
{
	id = timer_id++;
	fileName = fName;
	data = new std::list<DataPoint*>();
	
	if (fileName != 0)
	{
		FILE *file;
		if ((file = std::fopen(fileName,"w")) == NULL)
		{
			std::cerr << "Unable to open file " << fileName << " for writing." << std::endl;
			return;
		}
		
		fprintf(file,"SIZE,TIME,MEMORY\n");	
		fclose(file);
	}
}


Timer::~Timer ()
{
	for (std::list<DataPoint*>::iterator it = data->begin(); it != data->end(); ++it)
	{
		delete *it;
	}
	delete data;
}


void Timer::start (int size, std::string text)
{
	currentDataPoint = new DataPoint();
	currentDataPoint->size = size;
	
	if (text != "") { std::cout << text << ": "; }
	std::cout << "BEGIN TIMER " << id << " (size " << size << ")" << std::endl;
}

void Timer::startTime () { sTime = clock(); iTime = sTime; }
void Timer::startMemory () { sMemory = getMemory(); iMemory = sMemory; }


void Timer::stop (std::string text)
{
	clock_t clickNb = eTime - sTime;
	time = ((float)clickNb)/CLOCKS_PER_SEC;
	memory = eMemory - sMemory;

	if (text != "") { std::cout << text << ": "; }
	std::cout << "END TIMER " << id << " (" << time << " sec, " << memory << " bytes)" << std::endl;

	currentDataPoint->time = time;
	currentDataPoint->memory = memory;
	data->push_back(currentDataPoint);
	
	if (fileName != 0)
	{
		FILE *file;
		if ((file = std::fopen(fileName,"a")) == NULL)
		{
			std::cerr << "Unable to open file " << fileName << " for writing." << std::endl;
			return;
		}
	
		fprintf(file,"%d,%f,%d\n",currentDataPoint->size,currentDataPoint->time,currentDataPoint->memory);	
		fclose(file);
	}
}


void Timer::stopTime () { eTime = clock(); }
void Timer::stopMemory () { eMemory = getMemory(); }

void Timer::step (std::string text)
{
	stopTime();
	stopMemory();

	clock_t clickNb = eTime - iTime;
	time = ((float)clickNb)/CLOCKS_PER_SEC;
	memory = eMemory - iMemory;

	if (text != "") { std::cout << text << ": "; }
	std::cout << "STEP TIMER " << id << " (" << time << " sec, " << memory << " bytes)" << std::endl;
	
	iTime = clock();
	iMemory = getMemory();
}


int getMemory ()
{
//	PROCESS_MEMORY_COUNTERS memCounter;
//	bool result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
//	return memCounter.WorkingSetSize;
	return 0;
}

