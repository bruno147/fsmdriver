/* * * * * * * * * * * * * * * * * * DriverGeneticAlgorithm.cpp * * * * * * * * * * * * * * * * */
/* 																								*/
/* Implementation of a Genetic Algorithm to evolve the racing parameters of FSMDriver [TORCS]	*/
/* GitHub Repository: (https://github.com/bruno147/fsmdriver)									*/
/* 																								*/
/* Code derived from, and inspired by, AI junkie (www.ai-junkie.com)							*/
/* 																								*/
/* * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	*/

#include "DriverGeneticAlgorithm.h"

#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <bitset>

using 	std::string;
using	namespace std;

static const float	CROSSOVER_RATE				0.7;
static const float	MUTATION_RATE				0.001;
static const int 	POPULATION_SIZE				100;	// Must be an even number (according to AI junkie)
static const int 	CHROMOSOME_LENGTH			300;
static const int 	GENE_LENGTH					4;
static const int 	MAX_ALLOWABLE_GENERATIONS	400;
static const int 	NUMBER_OF_PARAMETERS		22;		// Adjust to problem needs

// Returns a float between 0 & 1
#define RANDOM_NUMBER ((float)rand()/(RAND_MAX+1))

// @toDo Initialize class DriverGeneticAlgorithm

// Chromosome generation process (Main Method)
int main (int argc, char* argv[]) {
	// Random number generator's seeder
	srand ((int)time(NULL));

	while (true) {
		chromosomeType Population[POPULATION_SIZE];

		// Creation of an initial population (randomic, entirely with zero fitness)
		for (int i = 0; i < POPULATION_SIZE; i++) {
			Population[i].bits	  = getRandomBits (CHROMOSOME_LENGTH);
			Population[i].fitness = 0.0f;
		}

		int 	generationsRequired = 0;
		bool	evolved			= false;

		// Genetic Algorithm actual loop
		while (!evolved) {
			// Defines the size of the sorting sample for roulette Wheel
			float 	totalFitness = 0.0;

			// Assigns a fitness score to every chromosome through testing in race
			for (int i = 0; i < POPULATION_SIZE; i++) {
				Population[i].fitness = assignFitness (Population[i].bits);
				totalFitness += Population[i].fitness;
			}

			// Creates new population members through crossover and/or mutation (by chance)
			chromosomeType	newPopulation[POPULATION_SIZE];
			int 			populationCounter;

			while (populationCounter < POPULATION_SIZE) {
				// Selects 2 new members to apply crossover and mutation
				string offspring1 = roulette (totalFitness, Population);
				string offspring2 = roulette (totalFitness, Population);

				crossover 	(offspring1, offspring2)
				mutate 		(offspring1);
				mutate 		(offspring2);
				
				// Replaces the old members for the new ones
				newPopulation[populationCounter++] = chromosomeType (offspring1, 0.0f);
				newPopulation[populationCounter++] = chromosomeType (offspring2, 0.0f);

				for (int i = 0; i < POPULATION_SIZE; i++) {
					Population[i] = newPopulation[i];
				}

				++generationsRequired;

				// If the maximum number of generations is reached, ends program
				if (generationsRequired > MAX_ALLOWABLE_GENERATIONS) {
					cout << "Maximum allowable generations reached! Chromosome evolved." << endl;
					evolved = true;
				}
			}

			// Defines the best chromosome in the evolved population
			float 			bestFitness;
			chromosomeType	bestChromosome;

			for (int i = 0; i < POPULATION_SIZE; i++) {
				if (Population[i].fitness > bestFitness) {
					bestFitness		= Population[i].fitness;
					bestChromosome 	= Population[i];
				}
			}
		}

	}

	return 0;
}

// Auxiliary Methods (Implementations)

string	getRandomBits (int length) {
	string bits;

	for (int i = 0; i < length; i++) {
		if (RANDOM_NUMBER > 0.5f)
			bits += "1";
		else
			bits += "0";
	}

	return bits;
}

float binToFloat (string bits) {
	bitset<32> a (bits);
	float *value = reinterpret_cast<float*>(&a);

	return *value;
}


string floatToBin (float value) {
	int bit = 0;
	string bits;
	int *b = reinterpret_cast<int*>(&value);

	for (int k = 31; k >=0; k--) {
		bit = ((*b >> k)&1);
		bits += to_string (bit);
	}

	return bits;
}

string getChromosome (string filename) {
	string chromosome, aux;
	fstream fs;
	fs.open(filename);

	for (int i = 0; i < PARAMETER_COUNT; i++) {
		fs >> aux;
		chromosome += floatToBin (stof(aux));
	}

	fs.close();
	return chromosome;
}

void setChromosome (string chromosome, string filename) {
	string aux;
	fstream fs;
	fs.open (filename,fstream::out);

	for (int i = 0; i < PARAMETER_COUNT; i++) {
		fs << binToFloat (chromosome.substr(0,32)) << endl;
		chromosome.erase (0,32);
	}

	fs.close();
}

float assignFitness (string bits) {
	// @toDo Define a metric to evaluate a chromosome (through running on TORCS)
}

// @toDo create communication to send the choromosome to a file to be read on TORCS
void printChromosome (string bits) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		cout << Population[i].bits;
	}
	cout << endl;
}

// @toDo implement a method that shows the actual values to be used on TORCS
void printParameters () {

}

void mutate (string &bits) {
	for (int i = 0; i < bits.length(); i++) {
		if (RANDOM_NUMBER < MUTATION_RATE) {
			if (bits.at(i) == '1')
				bits.at(i) = '0';
			else
				bits.at(i) = '1';
		}
	}
	return;
}

void crossover (string &offspring1, string &offspring2) {
	if (RANDOM_NUMBER < CROSSOVER_RATE) {
    // Randomic choice of the crossover point
    int crossover 	= (int) (RANDOM_NUMBER * CHROMOSOME_LENGTH);

    string new1		= offspring1.substr (0, crossover) + offspring2.substr (crossover, CHROMOSOME_LENGTH);
    string new2		= offspring2.substr (0, crossover) + offspring1.substr (crossover, CHROMOSOME_LENGTH);

    offspring1		= new1;
    offspring2		= new2;				  
	}
}

string roulette (int totalFitness, chromosomeType* Population) {
	// Generation of a random number between 0 & total fitness count
	float slice = (float)(RANDOM_NUMBER * totalFitness);
	
	// Sweeping of the chromosones adding up the fitness so far
	float fitnessSoFar = 0.0f;
	
	for (int i = 0; i < POPULATION_SIZE; i++) {
		fitnessSoFar += Population[i].fitness;
		// If the fitness so far > random number generated, the current chromosome is returned
		if (fitnessSoFar >= slice)
			return Population[i].bits;
	}
	return "";
}	