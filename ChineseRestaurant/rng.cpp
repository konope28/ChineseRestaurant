#include "rng.h"
#include "kernels.h"
#include "random_generator.h"


RNG::RNG()
{
	probability_tables_buffet_generator = nullptr;
	probability_amount_of_customer_group_generator = nullptr;
	waiter_service_time_generator = nullptr;
	cashier_service_time_generator = nullptr;
	new_customer_arrival_time_generator = nullptr;
	buffet_eating_time_generator = nullptr;
}

RNG::~RNG()
{
	delete probability_tables_buffet_generator;
	delete probability_amount_of_customer_group_generator;
	delete waiter_service_time_generator;
	delete cashier_service_time_generator;
	delete new_customer_arrival_time_generator;
	delete buffet_eating_time_generator;
}

void RNG::Initialize(Kernels* kernels, int set_idx, double lambda_wtrs, double lambda_cshrs, double mean_arrivals, double stddev_arrivals, double mean_buffet, double stddev_buffet)
{
	
	for (int i = 0; i < 12; i++)	//create vector of uni generators for Normal Dist for arrival time
	{
		int enum_index = Kernels::NEW_CUSTOMER1 + i;
		uni_gen_arriv_time.push_back(new UniformGenerator(kernels->GetKernel(static_cast<Kernels::GTypes>(enum_index), set_idx)));
	}
	
	for (int i = 0; i < 12; i++)	//create vector of uni generators for Normal Dist for buffet time
	{
		int enum_index = Kernels::BUFFET_TIME1 + i;
		uni_gen_buffet_time.push_back(new UniformGenerator(kernels->GetKernel(static_cast<Kernels::GTypes>(enum_index), set_idx)));
	}

	new_customer_arrival_time_generator = new NormGenerator(mean_arrivals, stddev_arrivals, uni_gen_arriv_time);
	buffet_eating_time_generator = new NormGenerator(mean_buffet, stddev_buffet, uni_gen_buffet_time);

	
	probability_tables_buffet_generator = new UniformGenerator(kernels->GetKernel(Kernels::TBL_OR_BUFF, set_idx));
	probability_amount_of_customer_group_generator = new UniformGenerator(kernels->GetKernel(Kernels::GROUP_AMOUNT, set_idx));

	waiter_service_time_generator = new ExpoGenerator(lambda_wtrs, new UniformGenerator(kernels->GetKernel(Kernels::WAITER_TIME, set_idx)));
	cashier_service_time_generator = new ExpoGenerator(lambda_cshrs, new UniformGenerator(kernels->GetKernel(Kernels::CASHIER_TIME, set_idx)));

}

