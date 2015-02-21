/* * * * * * * * * * * * * * * * * * DriverGeneticAlgorithm.h * * * * * * * * * * * * * * * * * */
/* 																								*/
/* Auxiliary Library of a Genetic Algorithm to evolve the racing parameters of FSMDriver [TORCS]*/
/* GitHub Repository: (https://github.com/bruno147/fsmdriver)									*/
/* 																								*/
/* Code derived from, and inspired by, AI junkie (www.ai-junkie.com)							*/
/* 																								*/
/* * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	*/

#ifndef DRIVERGENETICALGORITHM_H
#define DRIVERGENETICALGORITHM_H

#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <bitset>

namespace DriverGeneticAlgorithm {
/*
	static const float	CROSSOVER_RATE;
	static const float	MUTATION_RATE;
	static const int	POPULATION_SIZE;			// must be an even number
	static const int	CHROMOSOME_LENGTH;
	static const int	GENE_LENGTH;
	static const int	MAX_ALLOWABLE_GENERATIONS;
*/
	static const float	CROSSOVER_RATE	=			0.7;	// Rate defined by AI-junkie
	static const float	MUTATION_RATE	=			0.001; 	// Rate defined by AI-junkie
	static const int 	POPULATION_SIZE	=			100;	// Must be an even number
	static const int 	GENE_LENGTH		=			32;
	static const int 	MAX_ALLOWABLE_GENERATIONS =	400;
	static const int 	NUMBER_OF_PARAMETERS	=	22;		// Adjust to problem needs
	static const int 	CHROMOSOME_LENGTH		=	GENE_LENGTH * NUMBER_OF_PARAMETERS;

// Definition of the Chromosome's Data Structure: In this case, a binary std::string
	struct chromosomeType {
	 	// binary std::string for the Data Structure
		std::string	bits;

	 	// float number for the Fitness Score (metric analysis)
		float	fitness;

		chromosomeType(): bits(""), fitness(0.0f){};
		chromosomeType(std::string in_bits, float in_fitness): bits(in_bits), fitness(in_fitness){};
	};


// Auxiliary Methods (Signatures)
	void    printGeneSymbol(int val);
	std::string  getRandomBits(int length);
	float	binToFloat(std::string bits);
	std::string	floatToBin(float value);
	std::string 	getChromosome(std::string filename);
	std::string 	setChromosome(std::string filename);
	void	setChromosome(std::string chromosome, std::string filename);
	float   assignFitness(std::string bits, int target_value);
	float	assignFitness(std::string bits);
	void    printChromosome(std::string bits);
	void    crossover(std::string &offspring1, std::string &offspring2);
	void    mutate(std::string &bits);
	std::string  roulette(int total_fitness, chromosomeType* Population);
	void	printParameters(std::string bits);
}

#endif // DRIVERGENETICALGORITHM_H