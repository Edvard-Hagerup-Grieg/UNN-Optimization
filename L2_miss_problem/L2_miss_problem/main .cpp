#include <iostream>
#include "omp.h"
#include <boost/thread.hpp>

using namespace std;

class threadS 
{
private:
   unsigned char* theVector; 
   unsigned int   theVSize; 

public:
   threadS(unsigned char *aVector, unsigned int aVSize):theVector(aVector), theVSize(aVSize) {}

   void operator()() 
   {
      unsigned long long COUNT = 1000000000;
      while(--COUNT) 
          for (int i = 0; i < theVSize; i++)
              theVector[i]++;
   }
};

int main(int argc, char* argv[])
{
	double start = 0, finish = 0;

	if (argv[1][0] == '0')
	{
		start = omp_get_wtime();

		unsigned char vectorA[100]; 
		unsigned char vectorB[100];

		cout << hex;
		cout << "A:[" <<  (int)&vectorA[0] << "-" << (int)&vectorA[9] << "]" << endl;
		cout << "B:[" <<  (int)&vectorB[0] << "-" << (int)&vectorB[9] << "]" << endl;

		threadS threadA(vectorA, 10);
		threadS threadB(vectorB, 10);

		boost::thread_group tg;
		tg.create_thread(threadA);
		tg.create_thread(threadB);

		tg.join_all();

		finish = omp_get_wtime();
	}
	else if (argv[1][0] == '1')
	{
		start = omp_get_wtime();

		unsigned char vectorA[10];
		unsigned char vectorB[10];

		cout << hex;
		cout << "A:[" << (int)&vectorA[0] << "-" << (int)&vectorA[9] << "]" << endl;
		cout << "B:[" << (int)&vectorB[0] << "-" << (int)&vectorB[9] << "]" << endl;

		threadS threadA(vectorA, 10);
		threadS threadB(vectorB, 10);

		boost::thread_group tg;
		tg.create_thread(threadA);
		tg.create_thread(threadB);

		tg.join_all();

		finish = omp_get_wtime();
	}
	else
	{
		cout << "Invalid argument." << endl;
	}

	cout << "Time: " << (finish - start);
	//cin.get();
}