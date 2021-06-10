#include "statistics.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

Statistics::Statistics(double start_time, double stop_time):
	start_time_(start_time), stop_time_(stop_time)
{
	tbl_nr_of_groups_wait = 0;
	tbl_total_waiting_time = 0;
	wtr_nr_of_groups_wait = 0;
	wtr_total_waiting_time = 0;
	table_q_length = 0;
	cashier_q_length = 0;
	nr_of_observ_table_q = 0;
	nr_of_observ_cashier_q = 0;


	temp_tbl_counter = 0;
	temp_wtr_counter = 0;
}

Statistics::~Statistics()
{
}

void Statistics::Initialize()
{
	TBL_WAIT_FILE.open("table_waiting_time.tsv");
	if (!TBL_WAIT_FILE.is_open())
	{
		std::cerr << "Failed to open output file" << std::endl;
	}

	WTR_WAIT_FILE.open("waiter_waiting_time.tsv");
	if (!WTR_WAIT_FILE.is_open())
	{
		std::cerr << "Failed to open output file" << std::endl;
	}
}

void Statistics::GatherTableWaitingTime(double current_time, double waiting_time, int group_id)
{
	if (current_time >= start_time_ && current_time <= stop_time_)
	{
		
		while (group_id > temp_tbl_counter)
		{
			TBL_WAIT_FILE << "x" << " \t " << temp_tbl_counter << " \t " << "x" << endl;
			temp_tbl_counter++;
		}
		temp_tbl_counter++;
		tbl_nr_of_groups_wait++;
		tbl_total_waiting_time += waiting_time;
		TBL_WAIT_FILE << current_time << " \t " << group_id << " \t " << waiting_time << endl;
			
	}
}

void Statistics::GatherWaiterWaitingTime(double current_time, double waiting_time, int group_id)
{
	if (current_time >= start_time_ && current_time <= stop_time_)
	{
		while (group_id > temp_wtr_counter)
		{
			WTR_WAIT_FILE << "x" << " \t " << temp_wtr_counter << " \t " << "x" << endl;
			temp_wtr_counter++;
		}
		temp_wtr_counter++;
		wtr_nr_of_groups_wait++;
		wtr_total_waiting_time += waiting_time;
		WTR_WAIT_FILE << current_time << " \t " << group_id << " \t " << waiting_time << endl;
	}
		
}

void Statistics::GatherTableQueueLength(double current_time, double q_time, int q_length)
{
	if (current_time >= start_time_ && current_time <= stop_time_)
	{
		table_q_length += q_time * q_length;
		nr_of_observ_table_q++;
	}
}

void Statistics::GatherCashiersQueueLength(double current_time, double q_time, int q_length)
{
	if (current_time >= start_time_ && current_time <= stop_time_)
	{
		cashier_q_length += q_time * q_length;
		nr_of_observ_cashier_q++;
	}
}

void Statistics::DisplayResults()
{

	printf("\n------------------------------------------------------------------------\n");
	printf("                           RESULTS\n");
	printf("------------------------------------------------------------------------\n");
	cout << "Average waiting time for the table: " << tbl_total_waiting_time / tbl_nr_of_groups_wait <<
		"\t Number of observations: "<< tbl_nr_of_groups_wait << endl <<
		"Average table queue length: " << table_q_length / stop_time_ <<
		"\t\t Number of observations: " << nr_of_observ_table_q << endl <<
		"Average waiting time for the waiter: " << wtr_total_waiting_time / wtr_nr_of_groups_wait <<
		"\t Number of observations: " << wtr_nr_of_groups_wait << endl <<
		"Average cashier queue length: " << cashier_q_length / stop_time_ <<
		"\t\t Number of observations: " << nr_of_observ_cashier_q << endl;
}

