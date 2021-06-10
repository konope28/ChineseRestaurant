#ifndef RANDOM_GENERATOR_RANDOM_GENERATOR_H_
#define RANDOM_GENERATOR_RANDOM_GENERATOR_H_
#include <vector>
#include <cmath>
using namespace std;


class UniformGenerator
{
public:
	UniformGenerator(int kernel);
	virtual ~UniformGenerator();
	double Rand();
	double Rand(int start, int end);
	int GetKernel();

private:
	const double M;
	const int A;
	const int Q;
	const int R;
	int kernel_;
};

class ExpoGenerator
{
public:
	ExpoGenerator(double lambda, UniformGenerator* uni_gen);
	~ExpoGenerator();
	double Rand();
private:
	double lambda_;
	UniformGenerator* uniform_generator_;
};

class NormGenerator
{
public:
	NormGenerator(double mean, double stddev, std::vector<UniformGenerator*> uni_gen);
	~NormGenerator();
	double Rand();
private:
	std::vector<UniformGenerator*> uniform_generator_;
	double mean_;
	double stddev_;
};
#endif /*RANDOM_GENERATOR_RANDOM_GENERATOR_H_*/