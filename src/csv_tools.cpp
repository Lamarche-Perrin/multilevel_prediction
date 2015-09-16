/*!
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>

#include "csv_tools.hpp"


void deleteCSV (std::string fileName) { remove(fileName.c_str()); }

void openInputCSV (std::ifstream &file, std::string fileName)
{
	if (VERBOSE) { std::cout << "opening " << fileName << " for reading" << std::endl; }
	file.open(fileName.c_str(),std::ifstream::in);
}

bool isInputCSVEmpty(std::ifstream &file) { return file.peek() == std::ifstream::traits_type::eof(); }

void closeInputCSV (std::ifstream &file)
{
	if (VERBOSE) { std::cout << "closing file" << std::endl; }
	file.close();
}

bool hasCSVLine (std::ifstream &file) { return file.good() && file.peek() != EOF; }

void getCSVLine (std::ifstream &file, CSVLine &line, int sizeMax)
{
	std::string field;
	line.clear();
	line.resize(sizeMax);

	int i = 0;
	bool inQuote(false);
	bool escaping(false);
	
	while (file.good() && file.peek() != EOF)
	{
		char c;
		file.get(c);

		switch (c)
		{
			case QUOTE_CHAR:
				if (CSV_QUOTES)
				{
					if (escaping) { field += c; }
					else { inQuote = !inQuote; }
					escaping = false;
				}
				break;
				
			case ESCAPE_CHAR:
				escaping = true;
				field += c;
				break;

			case FIELD_DELIM:
				if (inQuote == true) { field += c; }
				else
				{
					line[i++] = field;
					field.clear();
				}
				escaping = false;
			break;

			case LINE_DELIM:
				if (inQuote == true) { field += c; }
				else {
					line[i++] = field;
					field.clear();
					return;
				}
				escaping = false;
				break;

			default:
				field += c;
				escaping = false;
				break;
		}
	}
}

void printCSVLine (CSVLine &line)
{
	for (CSVLine::iterator it = line.begin(); it != line.end(); ++it) { std::cout << "[" << *it << "] "; }
	std::cout << std::endl;
}

void parseCSVFile (std::string fileName)
{
	std::ifstream file;
	openInputCSV(file,fileName+".csv");
	CSVLine line;

	while (hasCSVLine(file))
	{
		getCSVLine(file,line);
		printCSVLine(line);
	}
	closeInputCSV(file);
}


int getCSVSize (std::string fileName)
{
	int size = 0;
	std::ifstream file;
	CSVLine line;
	openInputCSV(file,fileName);
	while (hasCSVLine(file))
	{
		getCSVLine(file,line);
		size++;
	}
	closeInputCSV(file);
	return size;
}


void openOutputCSV (std::ofstream &file, std::string fileName, bool erase)
{
	if (VERBOSE) { std::cout << "opening " << fileName << " for writing" << std::endl; }
	if (erase) { file.open(fileName.c_str(),std::ofstream::out); }
	else { file.open(fileName.c_str(),std::ofstream::out | std::ios_base::out | std::ios_base::app); }
}

void closeOutputCSV (std::ofstream &file)
{
	if (VERBOSE) { std::cout << "closing file" << std::endl; }
	file.close();
}

void addCSVLine (std::ofstream &file, CSVLine &line)
{
	bool firstLine (true);
	for (CSVLine::iterator it = line.begin(); it != line.end(); ++it)
	{
		if (!firstLine) { file << FIELD_DELIM; }
		file << QUOTE_CHAR << *it << QUOTE_CHAR;
		firstLine = false;
	}
	file << LINE_DELIM;
}

void addCSVField (std::ofstream &file, int field, bool endField)
{
	file << field;
	if (endField) { endCSVField(file); }
}

void addCSVField (std::ofstream &file, double field, bool endField, int prec)
{
	int p = -1;
	if (prec != 0) { p = file.precision(); file.precision(prec); }
	file << std::fixed << field;
	if (endField) { endCSVField(file); }
	if (p != -1) { file.precision(p); }
}

void addCSVField (std::ofstream &file, std::string field, bool endField)
{
	file << QUOTE_CHAR << field << QUOTE_CHAR;
	if (endField) { endCSVField(file); }
}

void addCSVNAField (std::ofstream &file, bool endField)
{
	file << "NA";
	if (endField) { endCSVField(file); }
}

void addCSVNULLField (std::ofstream &file, bool endField)
{
	file << "NULL";
	if (endField) { endCSVField(file); }
}

void endCSVField (std::ofstream &file) { file << FIELD_DELIM; }
void endCSVLine (std::ofstream &file) { file << LINE_DELIM; }


std::string int2string (int value)
{
	std::ostringstream strValue;
	strValue << value;
	return strValue.str();
}

std::string float2string (float value, int prec)
{
	std::ostringstream strValue;
	strValue.precision(prec);
	strValue << std::fixed <<  value;
	return strValue.str();
}

std::string double2string (double value, int prec)
{
	std::ostringstream strValue;
	strValue.precision(prec);
	strValue << std::fixed << value;
	return strValue.str();
}

time_t date2time (std::string date)
{
	struct tm time = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	time.tm_year = atoi(date.substr(0,4).c_str())-1900;
	time.tm_mon = atoi(date.substr(5,2).c_str())-1;
	time.tm_mday = atoi(date.substr(8,2).c_str());
	return mktime(&time);
}

