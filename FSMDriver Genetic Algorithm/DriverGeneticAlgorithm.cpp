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

using 	std::string;
using	namespace std;

static const float	CROSSOVER_RATE				0.7;
static const float	MUTATION_RATE				0.001;
static const int 	POPULATION_SIZE				100;	// must be an even number (according to AI junkie)
static const int 	CHROMOSOME_LENGTH			300;
static const int 	GENE_LENGTH					4;
static const int 	MAX_ALLOWABLE_GENERATIONS	400;

// returns a float between 0 & 1
#define RANDOM_NUMBER ((float)rand()/(RAND_MAX+1))

// @toDo Initialize class DriverGeneticAlgorithm

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// Chromosome generation process (Main Method)
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main(int argc, char* argv[]) {
	// Random number generator's seeder
	srand((int)time(NULL));

	// @toDo while(pre-defined condition) {
	while(true) {
		// Memory allocation for the population
		chromosomeType Population[POPULATION_SIZE];

		// Definition of a target Fitness Score by the user
		float target;
		cout 	<< "\nInput a target number: ";
		cin 	>> target;
		cout 	<< endl << endl;

		// Creation of an initial population (randomic, entirely with zero fitness)
		for (int i = 0; i < POPULATION_SIZE; i++) {
			Population[i].bits	  = GetRandomBits(CHROMOSOME_LENGTH);
			Population[i].fitness = 0.0f;
		}

	// @toDo continue Main Method
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// Auxiliary Methods (Implementations)
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// GetRandomBits (Auxiliary Method)
//
// * This method provides a filled binary string with the given length
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string	GetRandomBits(int length) {
	string bits;

	for (int i = 0; i < length; i++) {
		if (RANDOM_NUMBER > 0.5f)
			bits += "1";
		else
			bits += "0";
	}
	return bits;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// BinToDec and DecToBin(Auxiliary Method)
//
// * This method converts a given binary string into the correspondent decimal 
//	 integer and vice versa
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int	BinToDec(string bits) {
	int decimalValue	= 0;
	int valueToAdd	= 1;

	for (int i = bits.length(); i > 0; i--) {
		if (bits.at(i-1) == '1')
			decimalValue += valueToAdd;
		valueToAdd *= 2;
	}
	return decimalValue;
}

string DecToBin(int decimal) {
	if (decimal > 65535) {
		cout << "Decimal is out of conversion range." << endl;
		return;
	}

	string bits("0000000000000000");
	for (int i = 15; i >= 0; i--) {
		if (a%2)
			s[i] = '1';
		else
			s[i] = '0';
		decimal /= 2;
	}
	return bits;
}

void setChromossome(string filename) {
	string chromosome, aux;
	fstream fs;
	fs.open(filename);
	for (int i = 0; i < PARAMETER_COUNT; i++) {
		fs >> aux;
		chromosome += DecToBin(stoi(aux));
	}
	fs.close();
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// ParseBits (Auxiliary Method)
//
// * This method provides the final converted string given a chromosome
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int ParseBits(string bits, int* buffer) {
	// @toDo
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// AssignFitness (Auxiliary Method)
//
// * This method receives the target value defined by the user (defined metric) and a chromosome
// * and provides an adequate evaluation to the chromosome, in the form of its fitness parameter
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
float AssignFitness(string bits, int targetValue) {
	// @toDo Define a metric to evaluate a chromosome
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// PrintChromosome (Auxiliary Method)
//
// * This method decodes the chromosome and displays it on the screen as an output to the user
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void PrintChromo(string bits) {
	// @toDo Define if the size of the genes will be the same for every variable
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// PrintGeneSymbol (Auxiliary Method)
//
// * This method decodes each gene to a parameter in its original form
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void PrintGeneSymbol(int value) {
	// @toDo Define if all the variables will be float, or at least the codification it will have
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// Mutate (Auxiliary Method)
//
// * This method is activated randomly through the MUTATION_RATE's chance of happening
// * After this method, the binary chromosome string has one randomic chosen bit inverted
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Mutate(string &bits) {
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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// Crossover (Auxiliary Method)
//
// * This method is activated randomly through the CROSSOVER_RATE's chance of happening
// * After this method, the binary chromosome string has one randomic chosen part swapped with the
// * correspondent part of another binary chromosome string
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Crossover(string &offspring1, string &offspring2) {
	if (RANDOM_NUMBER < CROSSOVER_RATE) {
    // Randomic choice of the Crossover point
    int crossover = (int) (RANDOM_NUMBER * CHROMOSOME_LENGTH);

    string new1 = offspring1.substr(0, crossover) + offspring2.substr(crossover, CHROMOSOME_LENGTH);
    string new2 = offspring2.substr(0, crossover) + offspring1.substr(crossover, CHROMOSOME_LENGTH);

    offspring1 = new1; offspring2 = new2;				  
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// Roulette (Auxiliary Method)
//
// * This method chooses the next generation chromosome(s) via Roulette Wheel Selection
// * In this method of selection, the fittest have the most chance of being selected, as each
// * individual of the population has a percentage of choice chance proportional to its fitness
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string Roulette(int totalFitness, chromosomeType* Population) {
	// Generation of a random number between 0 & total fitness count
	float slice = (float)(RANDOM_NUMBER * totalFitness);
	
	// Sweeping of the chromosones adding up the fitness so far
	float fitnessSoFar = 0.0f;
	
	for (int i = 0; i < POPULATION_SIZE; i++) {
		fitnessSoFar += Population[i].fitness;
		// If the fitness so far >  random number generated, the current chromosome is returned
		if (fitnessSoFar >= slice)
			return Population[i].bits;
	}
	return "";
}	