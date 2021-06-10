#ifndef RANDOM_GENERATOR_RNG_H_
#define RANDOM_GENERATOR_RNG_H_
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class UniformGenerator;
class ExpoGenerator;
class NormGenerator;
class Kernels;

struct RNG
{
	RNG();
	~RNG();

	void Initialize(Kernels* kernels, int set_idx, double lambda_wtrs, double lambda_cshrs, double mean_arrivals, double stddev_arrivals, double mean_buffet, double stddev_buffet);

	
	vector<UniformGenerator*> uni_gen_arriv_time;
	vector<UniformGenerator*> uni_gen_buffet_time;
	NormGenerator* new_customer_arrival_time_generator;
	NormGenerator* buffet_eating_time_generator;

	UniformGenerator* probability_tables_buffet_generator;
	UniformGenerator* probability_amount_of_customer_group_generator;
	
	ExpoGenerator* waiter_service_time_generator;
	ExpoGenerator* cashier_service_time_generator;
};


#endif /*RANDOM_GENERATOR_RNG_H_*/