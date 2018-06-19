#include <string> // includes string 
#include <iostream> // includes input/output services
#include <iomanip> // it is part of input/output services, defines the manipulator functions
#include <vector> // vector declaration 
#include <iterator> // to derive iteration class
#include <deque> // constructing deques
using namespace std;

//process structure to store each process information
struct Process
{
	int priority; //variable to store queue priorities
	int arrival_time; // variable to store arrival time of the process
	int burst_time; // variable to store process burst time
	int waiting_time; // variable to store process wait time
	int turnaround_time; // variable to store turnaround time
	int first_response; // variable to store first response to calculate response time
	int finished_time; // variable to store completion time
	int left_time; //variable to store process left time from the queue, value required to push the process to next queue
	int num; // num variable
};

// function to print final output
void print(string algo, Process p[], int size){ 
    
	//output turnaround times for prcoesses
	cout <<algo <<endl; // outputs the algo
	cout <<"------------------------"<<endl<<"------------------------"<<endl;
	for(int i = 0; i < size; i++){
		cout <<"PID"<<p[i].num<<" WT: " << p[i].waiting_time <<"\t RT: " << p[i].first_response << "\t TAT: " << p[i].turnaround_time<<endl;
	}
	cout << endl;
	double sumTAT=0, avgTAT=0; // defining and initialling sumTATA and avgTAT

	//to sum up the turnaround times
	for(int i = 0; i < size; i++)
			sumTAT+=p[i].turnaround_time;
	
	//output avg as two decimals
	avgTAT=sumTAT/size;
	avgTAT = double(100 * avgTAT) / 100; // calculating the average
	cout << "Average Turn around time : " << avgTAT << endl;
	
	//to calculate average waiting time
	double sumWT=0, avgWT=0; // Defining and initiallizing sumWT and avgWT
	
	//to get average waiting times
	for(int i = 0; i < size; i++)
			sumWT+=p[i].waiting_time; 
	
	//output avg as two decimals
	avgWT=sumWT/size;
	avgWT = double(100 * avgWT) / 100; // calculating average waiting time
	cout << "Average Waiting Time : " << avgWT << endl;
	
	//average response time calculation
	double sumRT=0, avgRT=0;
	for(int i = 0; i < size; i++)
			sumRT+=p[i].first_response; //sums up response times
	
	//output avg as two decimals
	avgRT=sumRT/size;
	avgRT = double(100 * avgRT) / 100; //calculating average response time
	cout << "Average Response Time : " << avgRT << endl;
	cout<<endl;
}

//queue of processes
struct queue{             // using struct to create queues
	deque<Process> processes;
	int quantum; //to store quantum values
	vector<int> queueTime;
};
//multilevel feedback quequ algorithm
void mlf(Process p[], int size){

	//queue to traverse in loops
	deque<Process> original;

	//define queues and their quantums
	struct queue queue0;
	queue0.quantum = 0; // Last queue for FCFS
	struct queue queue1; 
	queue1.quantum = 16; // Queue for quantum 16
	struct queue queue2; 
	queue2.quantum = 8;  // Queue for quantum 8
	deque<Process> final;

	//loop defining a queue to traveser
	for(int i=0; i < size; i++){
		struct Process new_process; // creating new_process using struct to get arrival time, burst time, num, priority, waiting time, finished time
		new_process.arrival_time = p[i].arrival_time; //arrival time
		new_process.burst_time = p[i].burst_time; // burst time
		new_process.num = p[i].num;
		new_process.priority = p[i].priority; // priority
		new_process.waiting_time = 0; // waiting time =0
		new_process.finished_time =0; // completion time = 0
		new_process.left_time=new_process.burst_time; 
		new_process.first_response = -1;
		original.push_back(new_process); // creating original to store all the values of arrival times, burst time, completion time and to push the processes out of queue
	}

	//start time of the algorithm
	int total_time = 0;
	while(true){
	//loop break when all processes are complete
		if(final.size() == original.size()){
			Process newP[100] = {};
			for(int i = 0; i < original.size(); i++){
				original[i].turnaround_time = original[i].finished_time-original[i].arrival_time;
				newP[i] = original[i];
			}
			print("** Multi-Level Feedback Queue Scheduler  **", newP, size);
			break;
		}
	
	//adding process to the queues on the basis of arrival times
		for(int i = 0; i != original.size(); i++){
			if(original[i].arrival_time == total_time){
				if(original[i].priority == 2){              // if the priority is two then then the process will enter the first que
					queue2.processes.push_back(original[i]);
					queue2.queueTime.push_back(0);
				}
				if(original[i].priority == 1){              // if the priority is one, then the process will enter second que 
					queue1.processes.push_back(original[i]);
					queue1.queueTime.push_back(0);
				}
				if(original[i].priority == 0){              // if the priority is 0, then the process will enter the last que
					queue0.processes.push_back(original[i]);
					queue0.queueTime.push_back(0);
				}
			}
		}
	
		//Top priority queue execution. Following executes the first queue.
		if(queue2.processes.size() != 0){
			int current_time = 1;
			for(int i = 0; i != original.size(); i++){
				if(original[i].left_time != 0){    //if left queue is not equal to zero, the process enters the loop
					original[i].finished_time = original[i].finished_time + current_time; 
					original[i].waiting_time = original[i].waiting_time + current_time;  
				}
				if(original[i].num == queue2.processes[0].num){
					original[i].waiting_time = original[i].waiting_time - current_time;
					original[i].left_time = original[i].left_time - current_time;
					if(original[i].first_response == -1){
						original[i].first_response = total_time - original[i].arrival_time;
					}
				}
			}
			queue2.processes[0].left_time = queue2.processes[0].left_time - current_time;
			queue2.queueTime[0] += 1;
		
			//to remove the process from the queue and adding to final check queue
			if(queue2.processes[0].left_time == 0){
				final.push_back(queue2.processes[0]);
				queue2.processes.erase(queue2.processes.begin());
				queue2.queueTime.erase(queue2.queueTime.begin());
			}
			
			//to moving the process to next queue
			else{
				if(queue2.quantum == queue2.queueTime[0]){
					queue1.processes.push_back(queue2.processes[0]); // pushing process from queue 1 to queue 2
					queue1.queueTime.push_back(0);
					queue2.processes.erase(queue2.processes.begin()); // erasing the process from queue 2
					queue2.queueTime.erase(queue2.queueTime.begin()); 	
				}
			}
			total_time = total_time+current_time;
		}
		
		//following is executing the second queue
		else if(queue1.processes.size() != 0){  //checking the queue size
			int current_time = 1;    // initializing current time to 1
			for(int i = 0; i != original.size(); i++){ 
				if(original[i].left_time != 0){    // if left time is not equal to zero process enters the loop.
					original[i].finished_time = original[i].finished_time + current_time; // calculation of completion time in second queue
					original[i].waiting_time = original[i].waiting_time + current_time; //calculation of waiting time in second queue
				}
				if(original[i].num == queue1.processes[0].num){   
					original[i].waiting_time = original[i].waiting_time - current_time;
					original[i].left_time = original[i].left_time - current_time;
					if(original[i].first_response == -1){
						original[i].first_response = total_time - original[i].arrival_time; //calculating first response time in second queue
					}
				}
			}
			queue1.processes[0].left_time = queue1.processes[0].left_time - current_time;
			queue1.queueTime[0] += 1;
			
			// to remove process from the queue
			if(queue1.processes[0].left_time == 0){  
				final.push_back(queue1.processes[0]); 
				queue1.processes.erase(queue1.processes.begin());
				queue1.queueTime.erase(queue1.queueTime.begin());
			}
			
			// to add process to the queue
			else{
				if(queue1.quantum == queue1.queueTime[0]){
					queue0.processes.push_back(queue1.processes[0]);
					queue0.queueTime.push_back(0);
					queue1.processes.erase(queue1.processes.begin());
					queue1.queueTime.erase(queue1.queueTime.begin());
				}
			}
			total_time = total_time+current_time;
		}
		
		//to execute final queue using fcfs
		else if(queue0.processes.size() != 0){  // last queue, queue0
			int current_time = 1;
			total_time = total_time+current_time;
			for(int i = 0; i != original.size(); i++){
				if(original[i].left_time != 0){
					original[i].finished_time = original[i].finished_time + current_time; //getting the completion time in last que
					original[i].waiting_time = original[i].waiting_time + current_time; //getting the waiting time in last que
				}
				if(original[i].num == queue0.processes[0].num){
					original[i].waiting_time = original[i].waiting_time - current_time;
					original[i].left_time = original[i].left_time - current_time;
					if(original[i].first_response == -1){
						original[i].first_response = total_time - original[i].arrival_time;
					}
				}
			}
			queue0.processes[0].left_time = queue0.processes[0].left_time - current_time;
			if(queue0.processes[0].left_time == 0){
				final.push_back(queue0.processes[0]);
				queue0.processes.erase(queue0.processes.begin());
			}
		}
		else{
			total_time = total_time + 1;
			for(int i = 0; i != original.size(); i++){
				if(original[i].left_time != 0){
					original[i].finished_time = original[i].finished_time + 1;
					original[i].waiting_time = original[i].waiting_time + 1;
				}
			}	
		}
	}
}

int main(){
	//to build process queues array
	int processIDs[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};    //Process ID can be changed or added here
	int arrivalTimes[] = {0,2,3,8,7,5,3,7,12,8,3,17,4,8,3,6,2,4,2,4}; // arrival times to be entered here
	int burstTimes[] = {12,25,33,2,23,11,53,34,4,6,8,3,9,7,11,16,19,5,7,1}; // burst times to be entered here
	int priorities[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};    // priority remains same as the process has to enter from the very first queue
	Process process[(sizeof(processIDs)/sizeof(*processIDs))] = {};
	for(int i=0; i<(sizeof(processIDs)/sizeof(*processIDs));i++){
		// allocating the inputs
		Process p;
		p.arrival_time = arrivalTimes[i];
		p.burst_time = burstTimes[i];
		p.priority = priorities[i];
		p.num = processIDs[i];
		process[i] = p;
	}
	mlf(process, (sizeof(processIDs)/sizeof(*processIDs)));
}
