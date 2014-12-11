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
	static const int	POPULATION_SIZE;			// must be an even number
	static const int	CHROMOSOME_LENGTH;
	static const int	GENE_LENGTH;
	static const int	MAX_ALLOWABLE_GENERATIONS;

// Definition of the Chromosome's Data Structure: In this case, a binary std::string
	struct chromosomeType {
 	// binary std::string for the Data Structure
 	string	bits;  

 	// float number for the Fitness Score (metric analysis)
	float	fitness;

	chromosomeType(): bits(""), fitness(0.0f){};
	chromosomeType(string in_bits, float in_fitness): bits(in_bits), fitness(in_fitness){};
	};

public:

// Auxiliary Methods (Signatures)
	void    printGeneSymbol(int val);
	string  getRandomBits(int length);
	float	binToFloat(string bits);
	string	floatToBin(float value)
	string 	getChromosome(string filename)
	string 	setChromosome(string filename)
	float   assignFitness(string bits, int target_value);
	void    printChromosome(string bits);
	void    crossover(string &offspring1, string &offspring2);
	void    mutate(string &bits);
	string  roulette(int total_fitness, chromosomeType* Population);
	void	printParameters(string bits);
};

#endif // DRIVERGENETICALGORITHM_H