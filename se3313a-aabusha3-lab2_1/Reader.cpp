#include <iostream>
#include "SharedObject.h"

using namespace std;

struct MyShared{
	int threadNum;
	int reportId;
	int timePassed;

};

int main(void){
	int count = 0;
	while(count < 100){
		cout << "I am a reader" << endl;
		Shared<MyShared> sharedMemory ("sharedMemory");

		cout << "Reader Thread: " << sharedMemory->threadNum << " "
		<< sharedMemory->reportId << " "
		<< sharedMemory->timePassed << " ";
		
		count++;
		sleep(1);
	}
}
