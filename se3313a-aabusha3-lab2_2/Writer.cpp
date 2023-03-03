#include <iostream>
#include "thread.h"
#include "SharedObject.h"
#include "Blockable.h"
#include <time.h>
#include <stack>
#include <thread>
#include <unistd.h>
#include "Semaphore.h"


using namespace std;

struct MyShared{
	int threadNum;
	int reportId;
	int timePassed;	
};


Semaphore readerSem("reader", 1, true);
Semaphore writerSem("writer", 1, true);


class WriterThread : public Thread{
	public:
		int threadNum;
		bool flag = false;
		int delay;
		int reportId = 0;
		
		WriterThread(int in, int delayTime):Thread(delayTime*1000){
			this->threadNum = in; 
			this->delay = delayTime;			
		}

		virtual long ThreadMain(void) override{
			Shared<MyShared> sharedMemory ("sharedMemory");
			
			while(true){
				this->reportId++;

				time_t start = time(0);
				writerSem.Wait();
				sleep(delay);				
				time_t end = time(0);

				int timeElapsed = end - start;
				sharedMemory-> threadNum = threadNum; 
				sharedMemory-> timePassed = timeElapsed;
				sharedMemory-> reportId = reportId;	

				readerSem.Signal();	
				
				if(flag){
					break;
				}
			}
		return 1;
		}
};


int main(void){
	cout << "I am a Writer" << endl;

	Shared<MyShared> shared("sharedMemory", true);

	int threadNum = 0;
	string delay;
	string input;
	
	WriterThread * thread1;
	stack<WriterThread*> threadStack;


	while(true){
		cout << "Would You Like To Create A Writer Thread?" << endl;
		getline(cin, input);
		
		if (input != "y"){
			break;	
		}
		else{
			cout <<"What Is The Delay Time For This Thread?" << endl;
			getline(cin, delay);
			threadNum++;
			int delayInt = stoi(delay);
			thread1 = new WriterThread(threadNum, delayInt);
			threadStack.push(thread1);
			
		}
	}
	
	cout << "Broken" << endl;
	for(auto i = 0; i < threadStack.size(); i++){
		thread1 = threadStack.top();
		thread1->flag = true;
		delete thread1;
		threadStack.pop();
	}
	cout << "Ended" << endl;
}