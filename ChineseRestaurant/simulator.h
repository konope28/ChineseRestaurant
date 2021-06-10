#ifndef SIMULATOR_SIMULATOR_H_
#define SIMULATOR_SIMULATOR_H_
#include "logger.h"
struct ChineseRestaurant;
struct RNG;
class Agenda;
class Statistics;

class Simulator
{
public:
	Simulator(double stop_time, double mng_serv_time, int nr_of_tbl2, int nr_of_tbl3, int nr_of_tbl4, int nr_of_wtrs, int nr_of_cshrs, int nr_of_buff_sts);

	~Simulator();

	void Initialize(std::string kernels_file_path, int sim_set_idx, double start_time, bool step_by_step, Logger::LogVerbosity verb, double lambda_wtrs, double lambda_cshrs, double mean_arrivals, double stddev_arrivals, double mean_buffet, double stddev_buffet);

	void Start();

private:
	const double kStopTime_;
	const double kMngServTime_;
	const int kNumOfTables2_;
	const int kNumOfTables3_;
	const int kNumOfTables4_;
	const int kNumOfWaiters_;
	const int kNumOfCashiers_;
	const int kNumOfBuffetSeats_;

	double current_time_;
	bool step_by_step_;

	ChineseRestaurant* restaurant_;
	Agenda* agenda_;
	RNG* rng_;
	Statistics* statistics_;
};

#endif /* SIMULATOR_SIMULATOR_H_ */