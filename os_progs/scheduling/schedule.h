#ifndef _schedule_h_
#define _schedule_h_




struct Process
{

	int Pid,doneOrder;
	int AT,BT,CT,TAT,WT,RT,queued,priority;

} ;


class Scheduler
{
	public:

	//const int MaxTasks=10;
	Process process[10];
	Process LastProcessed;
	int NoOfProcess,CurrentTime;
	int ReadyQueue[10];
	int TQ,front,end,ProcessInQueue;



	// member functions

	Scheduler();

	void Initialise(int pid,int at,int bt,int p);

	void Refresh(); // Refreshes Calculated Values to 0

	void Clear(); // Clears all stored and calculated data

	void Set_TQ(int t); // sets user defined TQ

	void NPE_Execute(int i, int Order); //  for non premtive execution

	int PE_Execute(int i, int Order, int rr);//  for premtive execution. set rr=1 if scheduling is round r

	void MakeFcfsSchedule();

	void MakeSjfSchedule();

	void MakeSrtSchedule();

	void Queue(int p);   // for round robin scheduling

	int Dequeue();       // for round robin scheduling

	void MakeRoundRobinSchedule();

	void MakeHrrnSchedule();

	void MakeStaticPrioritySchedule();

	void DisplaySchedule();   //Displays details of recently executed schedule

	float AvgWaitingTime();   // average waiting time for recently executed schedule



};




#include "Schedules.cpp"
#endif
