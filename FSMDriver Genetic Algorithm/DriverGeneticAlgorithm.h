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

class DriverGeneticAlgorithm : {
private:

	static const float	CROSSOVER_RATE;
	static const float	MUTATION_RATE;
	static const int	POPULATION_SIZE;			// must be an even number (according to AI junkie)
	static const int	CHROMOSOME_LENGTH;
	static const int	GENE_LENGTH;
	static const int	MAX_ALLOWABLE_GENERATIONS;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// Definition of the Chromosome's Data Structure: In this case, a binary std::string
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	struct chromosomeType {
 	// binary std::string for the Data Structure
 	string	bits;  

 	// float number for the Fitness Score (metric analysis)
	float	fitness;

	chromosomeType(): bits(""), fitness(0.0f){};
	chromosomeType(string in_bits, float in_fitness): bits(in_bits), fitness(in_fitness){};
	};

public:
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// Auxiliary Methods (Signatures)
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	void    PrintGeneSymbol(int val);
	string  GetRandomBits(int length);
	int     BinToDec(string bits);
	string 	DecToBin(int decimal);
	float   AssignFitness(string bits, int target_value);
	void    PrintChromosome(string bits);
	void    PrintGeneSymbol(int val);
	int     ParseBits(string bits, int* buffer);
	string  Roulette(int total_fitness, chromosomeType* Population);
	void    Mutate(string &bits);
	void    Crossover(string &offspring1, string &offspring2);
};

#endif // DRIVERGENETICALGORITHM_H