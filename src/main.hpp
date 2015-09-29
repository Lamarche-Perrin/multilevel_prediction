#ifndef INCLUDE_MAIN
#define INCLUDE_MAIN

/*!
 * \file main.hpp
 * \brief Main program to run tests and experiments (see for example class VoterExperiment)
 * \author Robin Lamarche-Perrin
 * \date 22/01/2015
 */


#include "csv_tools.hpp"
#include "voter_graph.hpp"
#include "markov_process.hpp"

void computeInformationMeasures ();

void testScoreFunctions ();
void testMarkovProcess ();
void testVoterGraph ();
void testMeasuresWithAggregation ();

long unsigned int nChoosek (int n, int k);
//double nChoosekProb (int n, int k, double p = 1./2);

#endif
