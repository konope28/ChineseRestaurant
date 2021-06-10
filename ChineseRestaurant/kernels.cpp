#include "kernels.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include "random_generator.h"
using namespace std;


Kernels::Kernels() : kNrofSets(100), kSetLength(1000000)
{
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER1, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER2, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER3, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER4, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER5, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER6, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER7, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER8, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER9, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER10, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER11, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(NEW_CUSTOMER12, vector<int>()));
	
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME1, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME2, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME3, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME4, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME5, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME6, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME7, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME8, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME9, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME10, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME11, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(BUFFET_TIME12, vector<int>()));
	
	kernelSet_.insert(pair<GTypes, vector<int>>(WAITER_TIME, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(CASHIER_TIME, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(GROUP_AMOUNT, vector<int>()));
	kernelSet_.insert(pair<GTypes, vector<int>>(TBL_OR_BUFF, vector<int>()));

	kernels_loaded_ = false;
}

Kernels::~Kernels()
{
}

int Kernels::GetKernel(GTypes gtype, int set) const
{
   assert(kernels_loaded_ && "Kernels::GetKernel(): Kernels not loaded from the file!");
   assert(gtype != COUNT && "Kernels::GetKernel(): Wrong generator type!");
   auto setSize = kernelSet_.at(gtype);
   assert(set >= 0 && set < setSize.size() && "Kernels::GetKernel(): set index out of range!");
	int seed = kernelSet_.at(gtype)[set];
	return seed;
}


void Kernels::GenerateKernels(std::string filePath)
{
   printf("Kernels generation...\n");
   int k = 1;
   ofstream fout(filePath);
   UniformGenerator *uniform = new UniformGenerator(k);

   if (fout.is_open())
   {
      for (int genTypeIdx = 0; genTypeIdx < COUNT; genTypeIdx++)
      {
         printf("\n  Generator Type %d/%d\n  Set: ", genTypeIdx+1, COUNT);
         for (int i = 0; i < kNrofSets; i++)
         {
            printf("%d/%d, ", i+1, kNrofSets);
            for (int j = 0; j < kSetLength; j++)
            {
               uniform->Rand();
            }
            fout << uniform->GetKernel() << " ";
         }
         fout << endl;
      }
      fout.close();
   }
}


void Kernels::ReadKernels(const std::string input_file_path)
{
   printf("   Reading kernels from %s file....", input_file_path.c_str());
   ifstream fin(input_file_path);

   if (fin.is_open())
   {
      string line; int line_idx = 0;
      

      while (getline(fin, line) && line_idx < COUNT)
      {      

		 std::vector<std::string> splitted;
		 vector<int> kernels;

		 Split(line, splitted);

         for (auto val : splitted)
            kernels.push_back(atoi(val.c_str()));
      
         kernelSet_[static_cast<GTypes>(line_idx)] = kernels;
         line_idx++;
      }
      printf("OK!\n");
      kernels_loaded_ = true;
      fin.close();
   }
   else
   {
      printf("FILE ERROR!\n");
   }
}

void Kernels::Split(const std::string& str, std::vector<std::string>& v) 
{
	std::stringstream ss(str);
	ss >> std::noskipws;
	std::string field;
	char ws_delim;
	while (1) {
		if (ss >> field)
			v.push_back(field);
		else if (ss.eof())
			break;
		else
			v.push_back(std::string());
		ss.clear();
		ss >> ws_delim;
	}
}