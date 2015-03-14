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
	if(POPULATION_SIZE%2){
		cout << "ERROR\nPOPULATION_SIZE must be an even number\n";
		return 0;
	}

	// Random number generator's seeder
	srand ((int)time(NULL));

	// Defines the best chromosome in the evolved population
	float 			bestFitness = 0;
	std::vector<float> bestRace;
	chromosomeType	bestChromosome;

	//flag
	bool	evolved			= false;

	while (!evolved) {
		chromosomeType Population[POPULATION_SIZE];

		/*Population[0].bits = floatToBin(4.0) + floatToBin(1500) + floatToBin(4000) + floatToBin(9500) + floatToBin(5)
						   + floatToBin(100) + floatToBin(300) + floatToBin(50) + floatToBin(0.12) + floatToBin(0.7)
						   + floatToBin(80) + floatToBin(3) + floatToBin(0.1) + floatToBin(90) + floatToBin(70)
						   + floatToBin(40) + floatToBin(0.7) + floatToBin(0.5) + floatToBin(1000) + floatToBin(500)
						   + floatToBin(400) + floatToBin(300);
		Population[0].fitness = 0.0f;*/

		//cout << "Population i = 0 => length = " << Population[0].bits.length() << endl;

		// Creation of an initial population (randomic, entirely with zero fitness)
		for (int i = 0; i < POPULATION_SIZE; i++) {
			Population[i].bits	  = getRandomBits (CHROMOSOME_LENGTH);
			Population[i].fitness = 0.0f;
		}

		int 	generationsRequired = 0;

		// Genetic Algorithm actual loop
		while (!evolved) {

#ifdef ROULLETE
			// Defines the size of the sorting sample for roulette Wheel
			float 	totalFitness = 0.0;

			// Assigns a fitness score to every chromosome through testing in race
			for (int i = 0; i < POPULATION_SIZE; i++) {
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
#endif //ROULLETE

#ifdef ELITISM
			for (int i = 0; i < POPULATION_SIZE; ++i)	Population[i].track1 = getDataTrack(Population[i]);

			std::vector<chromosomeType> sortPopulation;

			for (int i = 0; i < POPULATION_SIZE; ++i)	sortPopulation.push_back(Population[i]);

			sortPopulation = merge_sort(sortPopulation);

			bestRace = sortPopulation.at(0).track1;
			bestChromosome = sortPopulation.at(0);


#endif //ELITISM

			// @toDo Include Log Method to keep every generation archived
			log(generationsRequired, Population, bestChromosome);

			// Creates new population members through crossover and/or mutation (by chance)
			chromosomeType	newPopulation[POPULATION_SIZE];
			int 			populationCounter=0;

#ifdef ELITISM
			for (int i = 0; i < 6; ++i) newPopulation[i] = sortPopulation.at(i);

			populationCounter = 6;
#endif //ELITISM
			while (populationCounter < POPULATION_SIZE) {
				// Selects 2 new members to apply crossover and mutation
				string offspring1;
				string offspring2;

#ifdef ROULLETE
			
				offspring1 = roulette (totalFitness, Population);
				offspring2 = roulette (totalFitness, Population);

#endif //ROULLETE

#ifdef ELITISM

				offspring1 = pool(sortPopulation);
				offspring2 = pool(sortPopulation);

#endif //ELITISM

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
			cout << endl << endl;
			cout << "Generation: " << generationsRequired << "  Generation: " << generationsRequired 
				 << "  Generation: " << generationsRequired << "  Generation: " << generationsRequired;
			cout << endl << endl << endl;

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
	
	std::vector<float> result1, result2, result3;
	string track1("forza");
	string track2("cg1");
	string track3("cs");

	cout << "Track: " << track1 << endl;
	result1 = runTest(track1, bits);

	cout << "Track: " << track2 << endl;
	result2 = runTest(track2, bits);

	cout << "Track: " << track3 << endl;
	result3 = runTest(track3, bits);

	float mean = totalMean(result1, result2, result3);	
	//cout << "mean: " << mean << endl;
	//cout << "resultado: " << result1 << endl;

	return mean;
}

std::vector<float> DriverGeneticAlgorithm::getDataTrack (chromosomeType specimen)
{
	std::vector<float> result1;
	string track1("forza");
	// string track2("cg1");
	// string track3("cs");

	cout << "Size " << specimen.track1.size() << endl;
	if(!specimen.track1.size())
	{
		cout << "Track: " << track1 << endl;
		result1 = runTest(track1, specimen.bits);
	}
	else	result1 = specimen.track1;
/*
	cout << "Track: " << track2 << endl;
	result2 = runTest(track2, bits);

	cout << "Track: " << track3 << endl;
	result3 = runTest(track3, bits);

	float mean = totalMean(result1, result2, result3);
	//cout << "mean: " << mean << endl;
	//cout << "resultado: " << result1 << endl;
*/
	return result1;
}

std::vector<float> DriverGeneticAlgorithm::runTest (string track1, string bits) {
	string bin_path(boost::filesystem::current_path().native());
	unsigned pos = bin_path.find("bin");
	string str1 = bin_path.substr(0,pos);
	string track_path( bin_path.substr(0,pos) + "configs/" );
	string command1, command2;
	track_path += track1;

	char* shared_memory;	//for communication between TORCS and GA
	string strID = SharedMemory();
	int myID = stoi(strID);
	command1 = "torcs -r " + track_path + ".xml &";
	//command2 = "./FSMDriver " + bits + " " + strID;
	command2 = "./FSMDriver " + bits + " " + strID;
	
	
	if(system("fuser -k 3001/udp")); 
	if(system(command1.c_str()) == -1)	cout << "ERROR" << endl;
	if(system(command2.c_str()) == -1)	cout << "ERROR" << endl;

	/* Reattach the shared memory segment, at a different address. */
	shared_memory = (char*) shmat (myID, (void*) 0x5000000, 0);
	//result = atof(shared_memory);
	string temp(shared_memory);
	cout << "shared_memory: "<< shared_memory << endl;
	unsigned pos2=temp.find(' ');
	unsigned pos3=temp.substr(pos2+1).find(' ');
	float result1=stof(temp.substr(0, pos2));
	float result2=stof(temp.substr(pos2+1,pos3));
	float result3=stof(temp.substr(pos2+pos3+1));
	cout << "result1: " << result1 << endl;
	cout << "result2: " << result2 << endl;
	cout << "result3: " << result3 << endl;
	std::vector<float> results = { result1, result2, result3 };

	/* Detach the shared memory segment. */
	shmdt (shared_memory);

	

	/* Deallocate the shared memory segment. */
	shmctl (myID, IPC_RMID, 0);

	return results;
}

string DriverGeneticAlgorithm::SharedMemory(){
	int segment_id;
	const int shared_segment_size = 0xC;//0x6400;

	/* Allocate a shared memory segment. */
	segment_id = shmget (IPC_PRIVATE, shared_segment_size,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);


	return(to_string(segment_id));
}

float DriverGeneticAlgorithm::totalMean (std::vector<float> result1, std::vector<float> result2, std::vector<float> result3) {
	
	return result1.at(2)+result2.at(2)+result3.at(2);

}


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
		if (fitnessSoFar >= slice || !slice)
			return Population[i].bits;
	}
	return "";
}	

void DriverGeneticAlgorithm::log(int generation, chromosomeType population[], chromosomeType bestChromosome){
	ofstream logFile;
    logFile.open("log.txt", std::ios_base::app);
    logFile << endl << endl;
    logFile << endl << "Generation " << generation << endl;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    logFile << asctime(timeinfo);

#ifdef ROULLETE
    logFile << endl << "Best Chromosome so far: " << setw(164) << "\tFitness:" << endl;
#endif //ROULLETE

#ifdef ELITISM
    logFile << endl << "Best Chromosome so far: " << setw(164) << "\tTime:\t" << "\tDamage:\t" << "\tDistRaced:\t" << endl;
    logFile << binToHex(bestChromosome.bits) << "\t\t" << bestChromosome.track1.at(0) << "\t\t" << bestChromosome.track1.at(1) << "\t\t" << bestChromosome.track1.at(2) << endl;
#endif //ELITISM
    logFile << endl << "Population: " << endl;

    std::vector<chromosomeType> sortPopulation;

    for(unsigned int i = 0; i < POPULATION_SIZE; i++)	sortPopulation.push_back(population[i]);

	sortPopulation = merge_sort(sortPopulation);

#ifdef ROULLETE
	for(unsigned int i=0; i < sortPopulation.size(); i++){
		logFile << binToHex(sortPopulation[i].bits) << "\t" << sortPopulation[i].fitness << endl;
	}
#endif //ROULLETE

#ifdef ELITISM
	for(unsigned int i=0; i < sortPopulation.size(); i++){
		logFile << binToHex(sortPopulation[i].bits) << "\t\t" << sortPopulation[i].track1.at(0) << "\t\t" << sortPopulation[i].track1.at(1) << "\t\t" << sortPopulation[i].track1.at(2) << endl;
	}
#endif //ELITISM

	logFile.close();
}


char DriverGeneticAlgorithm::getHexCharacter(std::string str)
{
	if(str.compare("1111") == 0) return 'F';
	else if(str.compare("1110") == 0) return 'E';
	else if(str.compare("1101")== 0) return 'D';
	else if(str.compare("1100")== 0) return 'C';
	else if(str.compare("1011")== 0) return 'B';
	else if(str.compare("1010")== 0) return 'A';
	else if(str.compare("1001")== 0) return '9';
	else if(str.compare("1000")== 0) return '8';
	else if(str.compare("0111")== 0) return '7';
	else if(str.compare("0110")== 0) return '6';
	else if(str.compare("0101")== 0) return '5';
	else if(str.compare("0100")== 0) return '4';
	else if(str.compare("0011")== 0) return '3';
	else if(str.compare("0010")== 0) return '2';
	else if(str.compare("0001")== 0) return '1';
	else if(str.compare("0000")== 0) return '0';
	else if(str.compare("111")== 0) return '7';
	else if(str.compare("110")== 0) return '6';
	else if(str.compare("101")== 0) return '5';
	else if(str.compare("100")== 0) return '4';
	else if(str.compare("011")== 0) return '3';
	else if(str.compare("010")== 0) return '2';
	else if(str.compare("001")== 0) return '1';
	else if(str.compare("000")== 0) return '0';
	else if(str.compare("11")== 0) return '3';
	else if(str.compare("10")== 0) return '2';
	else if(str.compare("01")== 0) return '1';
	else if(str.compare("00")== 0) return '0';
	else if(str.compare("1")== 0) return '1';
	else if(str.compare("0")== 0) return '0';
	return '0';
}


string DriverGeneticAlgorithm::hexToBin (string sHex)
{
	string sReturn = "";
	for (unsigned int i = 0; i < sHex.length (); ++i)
	{
		switch (sHex [i])
		{
			case '0': sReturn.append ("0000"); break;
			case '1': sReturn.append ("0001"); break;
			case '2': sReturn.append ("0010"); break;
			case '3': sReturn.append ("0011"); break;
			case '4': sReturn.append ("0100"); break;
			case '5': sReturn.append ("0101"); break;
			case '6': sReturn.append ("0110"); break;
			case '7': sReturn.append ("0111"); break;
			case '8': sReturn.append ("1000"); break;
			case '9': sReturn.append ("1001"); break;
			case 'A': sReturn.append ("1010"); break;
			case 'B': sReturn.append ("1011"); break;
			case 'C': sReturn.append ("1100"); break;
			case 'D': sReturn.append ("1101"); break;
			case 'E': sReturn.append ("1110"); break;
			case 'F': sReturn.append ("1111"); break;
		}
	}
	return sReturn;
}


std::string DriverGeneticAlgorithm::binToHex(string rowresult)
{
	std::string endresult = "";
	for(unsigned int i = 0; i < rowresult.length(); i = i+4)
	{
		endresult += getHexCharacter(rowresult.substr(i,4));
	}
	return endresult;
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

string DriverGeneticAlgorithm::pool(const std::vector<chromosomeType> &population)
{
	return population.at( rand()%10 ).bits;
}
