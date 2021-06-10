#ifndef STATISTICS_STATISTICS_H_
#define STATISTICS_STATISTICS_H_
#include <fstream>
#include <vector>
using namespace std;

class Statistics
{
public:
	Statistics(double start_time, double stop_time);
	~Statistics();

	void Initialize();
	void GatherTableWaitingTime(double current_time, double waiting_time, int group_id);
	void GatherWaiterWaitingTime(double current_time, double waiting_time, int group_id);
	void GatherTableQueueLength(double current_time, double q_time, int q_length);
	void GatherCashiersQueueLength(double current_time, double q_time, int q_length);
	void DisplayResults();

private:
	double start_time_;
	double stop_time_;

	ofstream TBL_WAIT_FILE;
	ofstream WTR_WAIT_FILE;

	int tbl_nr_of_groups_wait;
	double tbl_total_waiting_time;
	int wtr_nr_of_groups_wait;
	double wtr_total_waiting_time;

	int nr_of_observ_table_q;
	double table_q_length;
	int nr_of_observ_cashier_q;
	double cashier_q_length;

	int temp_tbl_counter;
	int temp_wtr_counter;
};
#endif /*STATISTICS_STATISTICS_H_*/