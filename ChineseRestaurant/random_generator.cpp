#include "random_generator.h"


UniformGenerator::UniformGenerator(int kernel):kernel_(kernel), M(2147483647.0), A(16807), Q(127773), R(2836)
{
}

UniformGenerator::~UniformGenerator()
{
}


double UniformGenerator::Rand()
{
	int h = kernel_ / Q;
	kernel_ = A * (kernel_ - Q * h) - R * h;
	if (kernel_ < 0)
		kernel_ = kernel_ + static_cast<int>(M);

	return kernel_ / M;
}

int UniformGenerator::GetKernel()
{
	return kernel_;
}


double UniformGenerator::Rand(int start, int end)
{
	return Rand()*(end - start) + start;
}


//Exponential distribution
ExpoGenerator::ExpoGenerator(double lambda, UniformGenerator* uni_gen):
							lambda_(lambda), uniform_generator_(uni_gen)
{
}

ExpoGenerator::~ExpoGenerator()
{
	delete uniform_generator_;
}

double ExpoGenerator::Rand()
{
	double k = this->uniform_generator_->Rand();	//uniform variable
	return -(1.0 / lambda_)*log(k);			
}


//Normal distribution
NormGenerator::NormGenerator(double mean, double stddev, vector<UniformGenerator*> uni_gen) :
							mean_(mean), stddev_(stddev), uniform_generator_(uni_gen)
{
}

NormGenerator::~NormGenerator()
{
	for (auto* u_g : uniform_generator_)
		delete u_g;
}

double NormGenerator::Rand()
{
	double random_num = 0;
	double k[12] = {};
	for(int i=0;i<12;i++)
	{
		k[i] = uniform_generator_[i]->Rand();	//12 independent uniform variables
		random_num += k[i];
	}
	
	return (random_num - 6)*stddev_ + mean_;	//scaling
}