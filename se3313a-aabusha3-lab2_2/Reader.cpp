#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

using namespace std;

struct MyShared{
	int threadNum;
	int reportId;
	int timePassed;
};


int main(void){
	Semaphore readerSem("reader", 1);
	Semaphore writerSem("writer", 1);

	Shared<MyShared> sharedMemory("sharedMemory");
	
	
	while (true){
		cout << "I am a reader" << endl;
		readerSem.Wait();
	
		cout<<"Reader Thread: " << sharedMemory->threadNum << " "
		<< sharedMemory->reportId << " "
		<< sharedMemory->timePassed << " ";
		
		writerSem.Signal();
	}
}
