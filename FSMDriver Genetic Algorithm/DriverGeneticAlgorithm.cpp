/* * * * * * * * * * * * * * * * * * DriverGeneticAlgorithm.cpp * * * * * * * * * * * * * * * * */
/* 																								*/
/* Implementation of a Genetic Algorithm to evolve the racing parameters of FSMDriver [TORCS]	*/
/* GitHub Repository: (https://github.com/bruno147/fsmdriver)									*/
/* 																								*/
/* Code derived from, and inspired by, AI junkie (www.ai-junkie.com)							*/
/* 																								*/
/* * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	*/

//For shared memory
#include <sys/shm.h>
#include <sys/stat.h>
#include <cstdlib>

#include "DriverGeneticAlgorithm.h"

// using 	std::string;
using	namespace std;
using	namespace DriverGeneticAlgorithm;

/*const float	CROSSOVER_RATE	=			0.7;	// Rate defined by AI-junkie
const float	MUTATION_RATE	=			0.001; 	// Rate defined by AI-junkie
const int 	POPULATION_SIZE	=			100;	// Must be an even number
const int 	GENE_LENGTH		=			32;
const int 	MAX_ALLOWABLE_GENERATIONS =	400;
const int 	NUMBER_OF_PARAMETERS	=	22;		// Adjust to problem needs
const int 	CHROMOSOME_LENGTH		=	GENE_LENGTH * NUMBER_OF_PARAMETERS;*/

// Returns a float between 0 & 1
#define RANDOM_NUMBER ((float)rand()/(RAND_MAX))

// @toDo Initialize class DriverGeneticAlgorithm

// Chromosome generation process (Main Method)
int main (int argc, char* argv[]) {
	// Random number generator's seeder
	srand ((int)time(NULL));

	// Defines the best chromosome in the evolved population
	float 			bestFitness = 0;
	chromosomeType	bestChromosome;

	//flag
	bool	evolved			= false;

	while (!evolved) {
		chromosomeType Population[POPULATION_SIZE];

		// Creation of an initial population (randomic, entirely with zero fitness)
		for (int i = 0; i < POPULATION_SIZE; i++) {
			Population[i].bits	  = getRandomBits (CHROMOSOME_LENGTH);
			Population[i].fitness = 0.0f;
		}

		int 	generationsRequired = 0;

		// Genetic Algorithm actual loop
		while (!evolved) {
			// Defines the size of the sorting sample for roulette Wheel
			float 	totalFitness = 0.0;

			// Assigns a fitness score to every chromosome through testing in race
			for (int i = 0; i < POPULATION_SIZE; i++) {
				cout << endl << "i " << i << " population " << binToHex(Population[i].bits) << endl;
				Population[i].fitness = assignFitness (Population[i].bits);
				totalFitness += Population[i].fitness;
			}

			// Tests the best chromosome in the old population
			for (int i = 0; i < POPULATION_SIZE; i++) {
				if (Population[i].fitness > bestFitness) {
					bestFitness		= Population[i].fitness;
					bestChromosome 	= Population[i];
				}
			}

			// @toDo Include Log Method to keep every generation archived
			log(generationsRequired, Population, bestChromosome);

			// Creates new population members through crossover and/or mutation (by chance)
			chromosomeType	newPopulation[POPULATION_SIZE];
			int 			populationCounter=0;

			while (populationCounter < POPULATION_SIZE) {
				// Selects 2 new members to apply crossover and mutation
				string offspring1 = roulette (totalFitness, Population);
				string offspring2 = roulette (totalFitness, Population);

				//string offspring1 = Population[0].bits;
				//string offspring2 = Population[1].bits;

				crossover 	(offspring1, offspring2);

				mutate 		(offspring1);
				mutate 		(offspring2);
				// cout << "\nafter mutate" << endl;
				// cout << endl << "C1: " << binToHex(offspring1) << "\tC2: " << binToHex(offspring2)<< endl;
				// Replaces the old members for the new ones
				newPopulation[populationCounter++] = chromosomeType (offspring1, 0.0f);
				newPopulation[populationCounter++] = chromosomeType (offspring2, 0.0f);	
			}

			for (int i = 0; i < POPULATION_SIZE; i++) {
				Population[i] = newPopulation[i];
			}
			++generationsRequired;
			cout << generationsRequired << endl; 
			// If the maximum number of generations is reached, ends program
			if (generationsRequired >= MAX_ALLOWABLE_GENERATIONS) {
				cout << "Maximum allowable generations reached! Chromosome evolved." << endl;
				evolved = true;
			}
		}

	}

	return 0;
}

// Auxiliary Methods (Implementations)

string	DriverGeneticAlgorithm::getRandomBits (int length) {
	string bits;

	for (int i = 0; i < length; i++) {
		if (RANDOM_NUMBER > 0.5f)
			bits += "1";
		else
			bits += "0";
	}

	return bits;
}

float DriverGeneticAlgorithm::binToFloat (string bits) {
	bitset<32> a (bits);
	float *value = reinterpret_cast<float*>(&a);

	return *value;
}


string DriverGeneticAlgorithm::floatToBin (float value) {
	int bit = 0;
	string bits;
	int *b = reinterpret_cast<int*>(&value);

	for (int k = 31; k >=0; k--) {
		bit = ((*b >> k)&1);
		bits += to_string (bit);
	}

	return bits;
}
/*
string DriverGeneticAlgorithm::getChromosome (string filename) {
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

void DriverGeneticAlgorithm::setChromosome (string chromosome, string filename) {
	string aux;
	fstream fs;
	fs.open (filename,fstream::out);

	for (int i = 0; i < PARAMETER_COUNT; i++) {
		fs << binToFloat (chromosome.substr(0,32)) << endl;
		chromosome.erase (0,32);
	}

	fs.close();
}
*/
float DriverGeneticAlgorithm::assignFitness (string bits) {
	
	float result1, result2, result3;
	string track1("forza");
	string track2("cg1");
	string track3("cs");

//	result1 = runTest(track1, bits);
//	result2 = runTest(track2, bits);
//	result3 = runTest(track3, bits);

	float mean = totalMean(result1, result2, result3);	
	//cout << "mean: " << mean << endl;
	//cout << "resultado: " << result1 << endl;

	return RANDOM_NUMBER;
}

float DriverGeneticAlgorithm::runTest (string track1, string bits) {
	float result;
	string track, command, aux("");
	track = "~/" + track1;

	char* shared_memory;	//for communication between TORCS and GA
	string strID = SharedMemory();
	int myID = stoi(strID);
	command = "torcs -r " + track + ".xml & ./FSMDriver " + bits + " " + strID; 
	
	system("fuser -k 3001/udp"); 
	if(system(command.c_str()) == -1)	cout << "DEU PALA" << endl;

	/* Reattach the shared memory segment, at a different address. */
	shared_memory = (char*) shmat (myID, (void*) 0x5000000, 0);
	result = atof(shared_memory);
	/* Detach the shared memory segment. */
	shmdt (shared_memory);

	

	/* Deallocate the shared memory segment. */
	shmctl (myID, IPC_RMID, 0);

	return result;
}

string DriverGeneticAlgorithm::SharedMemory(){
	int segment_id;
	const int shared_segment_size = 0x6400;

	/* Allocate a shared memory segment. */
	segment_id = shmget (IPC_PRIVATE, shared_segment_size,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);


	return(to_string(segment_id));
}

float DriverGeneticAlgorithm::totalMean (float result1, float result2, float result3) {
	float weight1=1, weight2=1, weight3=1;
	float mean;
	// @toDo Define which mean to calculate using the results and the weights
	mean = ((result1 * weight1) + (result2 * weight2) + (result3 * weight3)) / (weight1 + weight2 + weight3);

	if(mean == 0)	return 0;
	else	return (1/mean);
}

// @toDo create communication to send the choromosome to a file to be read on TORCS
/*
void DriverGeneticAlgorithm::printChromosome (string bits) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		cout << Population[i].bits;
	}
	cout << endl;
}
*/
// @toDo implement a method that shows the actual values to be used on TORCS
/*
void DriverGeneticAlgorithm::printParameters () {

}
*/
void DriverGeneticAlgorithm::mutate (string &bits) {
	for (unsigned int i = 0; i < bits.length(); i++) {
		if (RANDOM_NUMBER < MUTATION_RATE) {
			if (bits.at(i) == '1')
				bits.at(i) = '0';
			else
				bits.at(i) = '1';
		}
	}
	return;
}

void DriverGeneticAlgorithm::crossover (string &offspring1, string &offspring2) {
	//if (RANDOM_NUMBER < DriverGeneticAlgorithm::CROSSOVER_RATE) {
    // Randomic choice of the crossover point
    int crossover 	= (int) (RANDOM_NUMBER * CHROMOSOME_LENGTH);

//    cout << "crossover " << crossover << endl;
    string new1		= offspring1.substr (0, crossover) + offspring2.substr (crossover, CHROMOSOME_LENGTH);
    string new2		= offspring2.substr (0, crossover) + offspring1.substr (crossover, CHROMOSOME_LENGTH);
//    cout << "offspring1 " << binToHex(offspring1) << endl;
//    cout << "offspring2 " << binToHex(offspring2) << endl;

    offspring1		= new1;
    offspring2		= new2;				  
	//}
}

string DriverGeneticAlgorithm::roulette (int totalFitness, chromosomeType* Population) {
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

void DriverGeneticAlgorithm::log(int generation, chromosomeType population[], chromosomeType bestChromosome){
	ofstream logFile;
    logFile.open("log.txt", std::ios_base::app);
    logFile << endl << endl;
    logFile << endl << "Generation " << generation << endl;
    logFile << endl << "Best Chromosome so far: " << setw(164) << "\tFitness:" << endl;
    logFile << binToHex(bestChromosome.bits) << "\t" << bestChromosome.fitness << endl;
    logFile << endl << "Population: " << endl;

    std::vector<chromosomeType> sortPopulation;

    for(int i = 0; i < POPULATION_SIZE; i++)	sortPopulation.push_back(population[i]);

	sortPopulation = merge_sort(sortPopulation);
    for(int i = 0; i < POPULATION_SIZE; i++){
    	//logFile << binToHex(population[i].bits) << "\t" << population[i].fitness << endl;
    	bitset<64> set1(sortPopulation[i].bits.substr(0,64));
    	bitset<64> set2(sortPopulation[i].bits.substr(64,128));
    	bitset<64> set3(sortPopulation[i].bits.substr(128,192));
    	bitset<64> set4(sortPopulation[i].bits.substr(192,256));
    	bitset<64> set5(sortPopulation[i].bits.substr(256,320));
    	bitset<64> set6(sortPopulation[i].bits.substr(320,384));
    	bitset<64> set7(sortPopulation[i].bits.substr(384,448));
    	bitset<64> set8(sortPopulation[i].bits.substr(448,512));
    	bitset<64> set9(sortPopulation[i].bits.substr(512,576));
    	bitset<64> set10(sortPopulation[i].bits.substr(576,640));
    	bitset<64> set11(sortPopulation[i].bits.substr(640,704));

    	stringstream ss;
    	string aux;
    	for(int k = 0; k < 11; k++)
    	{
    		ss << hex << sortPopulation[i].bits.substr(k*64 , (k + 1)* 64);
    	}
    	//cout << "string " << sortPopulation[i].bits << endl;
    	//cout << "hex " << hex << set1.to_ulong() << set2.to_ulong() << set3.to_ulong() << set4.to_ulong() << endl;
    	cout << endl;
    	ss << hex << set1.to_ullong();
    	ss << hex << set2.to_ullong();
    	ss << hex << set3.to_ullong();
    	ss << hex << set4.to_ullong();
    	ss << hex << set5.to_ullong();
    	ss << hex << set6.to_ullong();

    	// cout << hex << set1.to_ullong();
    	// cout << hex << set2.to_ullong();
    	// cout << hex << set3.to_ullong();
    	// cout << hex << set4.to_ullong();
    	// cout << hex << set5.to_ullong();
    	// cout << hex << set6.to_ullong();

    	cout << endl << hex << ss.str() << endl;

    	logFile << hex << set1.to_ullong(); // << "  ";
    	logFile << hex << set2.to_ullong(); // << "  ";
    	logFile << hex << set3.to_ullong(); // << "  ";
    	logFile << hex << set4.to_ullong(); // << "  ";
    	logFile << hex << set5.to_ullong(); // << "  ";
    	logFile << hex << set6.to_ullong(); // << "  ";
    	logFile << hex << set7.to_ullong(); // << "  ";
    	logFile << hex << set8.to_ullong(); // << "  ";
    	logFile << hex << set9.to_ullong(); // << "  ";
    	logFile << hex << set10.to_ullong(); // << "  ";
    	logFile << hex << set11.to_ullong(); // << "  ";
    	logFile << "\t    " << sortPopulation[i].fitness << endl;
    	logFile << ss.str() << endl;
    }

    logFile << endl << endl;
    //logFile << sortPopulation.size() << endl;
    //logFile << f << endl;
    logFile.close();
}

//string DriverGeneticAlgorithm::binToHex(string Chromosome){
char* DriverGeneticAlgorithm::binToHex(string Chromosome){
	// char* Chromosome.c_str() = Chromosome.c_str();
	char hexstr[176];
	char four[4];
	int hexnum;


	for(int i = 0;i < 176;++i)
	{
    	hexnum = 0;
	 
	    strncpy(four, Chromosome.c_str() + (i * 4), 4);
	    for(int j = 0;j < 4;++j)	hexnum += (four[j] - '0') << (3 - j);
	 
	    sprintf(hexstr + i, "%X", hexnum);
  	}

  	string ret(hexstr);

 	return (char*)ret.c_str();
//  	return ret;
}

std::vector<chromosomeType> DriverGeneticAlgorithm::merge_sort(const std::vector<chromosomeType> &data)
{
	if (data.size() <= 1) {
		return data;
	}
 
	int middle = data.size() / 2;
	std::vector<chromosomeType> left(data.begin(), data.begin()+middle);
	std::vector<chromosomeType> right(data.begin()+middle, data.end());
 
	left = merge_sort(left);
	right = merge_sort(right);
 
	std::vector<chromosomeType> result(data.size());
	std::merge(left.begin(), left.end(), 
	           right.begin(), right.end(),
	           result.begin());
 
	return result;
}
