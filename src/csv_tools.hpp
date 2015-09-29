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
