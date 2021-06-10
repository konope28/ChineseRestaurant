#ifndef GENERATORS_KERNELS_H_
#define GENERATORS_KERNELS_H_

#include <string>
#include <map>
#include <vector>

using namespace std;

class Kernels
{
   public:
      enum GTypes
      {
        NEW_CUSTOMER1 = 0, // New customer arrives event
		NEW_CUSTOMER2,
		NEW_CUSTOMER3,
		NEW_CUSTOMER4,
		NEW_CUSTOMER5,
		NEW_CUSTOMER6,
		NEW_CUSTOMER7,
		NEW_CUSTOMER8,
		NEW_CUSTOMER9,
		NEW_CUSTOMER10,
		NEW_CUSTOMER11,
		NEW_CUSTOMER12,

		BUFFET_TIME1,	//Time spent in the buffet
		BUFFET_TIME2,
		BUFFET_TIME3,
		BUFFET_TIME4,
		BUFFET_TIME5,
		BUFFET_TIME6,
		BUFFET_TIME7,
		BUFFET_TIME8,
		BUFFET_TIME9,
		BUFFET_TIME10,
		BUFFET_TIME11,
		BUFFET_TIME12,

		WAITER_TIME,	//Waiter service time
      	CASHIER_TIME,	//Cashier service time

      	GROUP_AMOUNT,	//Amount of people in the group
      	TBL_OR_BUFF,	//Probability group goes buffet or tables

      	COUNT,
      };
      
      Kernels();

      virtual ~Kernels();

      int GetKernel(GTypes gtype, int set) const;

      void GenerateKernels(std::string filePath);

      void ReadKernels(const std::string input_file_path);

   private:

      const int kNrofSets;
      const int kSetLength;
      
      bool kernels_loaded_;

      std::map<GTypes, std::vector<int> > kernelSet_;

	  void Split(const std::string& str, std::vector<std::string>& v);
};

#endif /*GENERATORS_KERNELS_H_*/
