#include <fstream>
#include "logger.h"
#include "simulator.h"
#include "kernels.h"
#include <iostream>
using namespace std;

int main()
{
	////////////////////////////////////////////////
	// ONLY ONCE ///////////////////////////////////
	// Kernels *kernels = new Kernels(); ///////////
	// kernels->GenerateKernels("./kernels.txt"); //
	////////////////////////////////////////////////

	//PARAMETERS////////////////////////////////////
	double stop_time = 10000000;
	double start_time = 6500;
	int nr_of_tbls_2 = 4;
	int nr_of_tbls_3 = 5;
	int nr_of_tbls_4 = 4;
	int nr_of_wtrs = 4;
	int nr_of_cshrs = 2;
	int nr_of_buff_sts = 14;
	double mng_serv_time = 600;
	double lambda_wtrs = 1.0 / 2700;
	double lambda_cshrs = 1.0 / 600;
	double mean_arriv = 400;
	double stddv_arriv = 100;
	double mean_buff = 1850;
	double stddv_buff = 200;
	////////////////////////////////////////////////

	printf("------------------------------------------------------------------------\n");
	printf("                           INITIALIZATION\n");
	printf("------------------------------------------------------------------------\n");

	Simulator* simulator = new Simulator(stop_time, mng_serv_time, nr_of_tbls_2, nr_of_tbls_3, nr_of_tbls_4, nr_of_wtrs, nr_of_cshrs, nr_of_buff_sts);		

	
	string kernels_path = "kernels.txt";
	bool step_by_step = true;
	int logger_verbosity;
	int sim_set_idx;

	do
	{
		printf("Choose simulation mode (1 - step by step, 0 - continues): ");
		std::cin >> step_by_step;
	} while (step_by_step != 0 && step_by_step != 1);

	do
	{
		printf("Choose logger verbosity level (1-4): ");
		std::cin >> logger_verbosity;
	} while (logger_verbosity < 1 || logger_verbosity > 4);
	
	printf("Give simulation set index: ");
	std::cin >> sim_set_idx;
	

	simulator->Initialize(kernels_path, sim_set_idx, start_time, step_by_step, static_cast<Logger::LogVerbosity>(logger_verbosity), lambda_wtrs, lambda_cshrs, mean_arriv, stddv_arriv, mean_buff, stddv_buff);

	printf("------------------------------------------------------------------------\n");
	printf("                           SIMULATION\n");
	printf("------------------------------------------------------------------------\n");

	
	simulator->Start();

	
	printf("------------------------------------------------------------------------\n");
	printf("                           FINISHED\n");
	printf("------------------------------------------------------------------------\n");

	delete simulator;

	system("Pause");
}
