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


#ifndef INCLUDE_CSV_TOOLS
#define INCLUDE_CSV_TOOLS

/*!
 * \file csv_tools.hpp
 * \brief Tools to handle input and output CSV files
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */


#include <vector>
#include <string>
#include <time.h>

extern bool VERBOSE;
extern int VERBOSE_TAB;

const bool CSV_QUOTES = false;
const char QUOTE_CHAR = '"';
const char ESCAPE_CHAR = '\\';
const char FIELD_DELIM = ',';
const char LINE_DELIM = '\n';

const int DATE_INDEX = 3;
const int TITLE_INDEX = 4;
const int BODY_INDEX = 5;
const int MAX_INDEX = 17;

typedef std::vector<std::string> CSVLine;

void deleteCSV (std::string fileName);

void openInputCSV (std::ifstream &file, std::string fileName);
bool isInputCSVEmpty(std::ifstream &file);
bool hasCSVLine (std::ifstream &file);
void getCSVLine (std::ifstream &file, CSVLine &line, int sizeMax = 8);
void printCSVLine (CSVLine &line);
void parseCSVFile (std::string fileName);
int getCSVSize (std::string fileName);
void closeInputCSV (std::ifstream &file);

void openOutputCSV (std::ofstream &file, std::string fileName, bool erase = false);

void addCSVLine (std::ofstream &file, CSVLine &line);
void addCSVField (std::ofstream &file, int field, bool endField = true);
void addCSVField (std::ofstream &file, double field, bool endField = true, int prec = 0);
void addCSVField (std::ofstream &file, std::string field, bool endField = true);
void addCSVNAField (std::ofstream &file, bool endField = true);
void addCSVNULLField (std::ofstream &file, bool endField = true);

void endCSVField (std::ofstream &file);
void endCSVLine (std::ofstream &file);

void closeOutputCSV (std::ofstream &file);

double string2double (std::string str);
std::string int2string (int value);
std::string float2string (float value, int prec = 10);
std::string double2string (double value, int prec = 10);
time_t date2time (std::string date);

#endif
