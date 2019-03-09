#include "schedule.h"
#include <iostream>

using namespace std;

int main()
{

	Scheduler A;

/*
	A.Initialise(1,5,5,0);
	A.Initialise(2,4,6,0);
	A.Initialise(3,3,7,0);
	A.Initialise(4,1,9,0);
	A.Initialise(5,2,2,0);
	A.Initialise(6,6,3,0);*/


	A.Initialise(1,0,3,1);
	A.Initialise(2,2,6,2);
	A.Initialise(3,4,4,3);
	A.Initialise(4,6,5,4);
	A.Initialise(5,8,2,5);
	A.Initialise(6,5,3,6);
	A.Set_TQ(2);



  cout<<"\n\n ----------------------------------First Come First Serve Schedule -------------------------------";
	A.MakeFcfsSchedule();
	A.DisplaySchedule();
  cout<<"\n\nAverage waiting time :"<<A.AvgWaitingTime()<<endl<<endl;



	cout<<"\n\n ----------------------------------  Shortest Job First Schedule ---------------------------------";
	A.MakeSjfSchedule();
  A.DisplaySchedule();
  cout<<"\n\nAverage waiting time :"<<A.AvgWaitingTime()<<endl<<endl;



	cout<<"\n\n ----------------------------------  Shortest Remaining Time Schedule ---------------------------------";
	A.MakeSrtSchedule();
	A.DisplaySchedule();
	cout<<"\n\nAverage waiting time :"<<A.AvgWaitingTime()<<endl<<endl;


	cout<<"\n\n ----------------------------------  Round robin Schedule ---------------------------------";
	A.MakeRoundRobinSchedule();
	A.DisplaySchedule();
	cout<<"\n\nAverage waiting time :"<<A.AvgWaitingTime()<<endl<<endl;



	cout<<"\n\n ----------------------------------  Highest Response Ratio Next Schedule ---------------------------------";
	A.MakeHrrnSchedule();
	A.DisplaySchedule();
	cout<<"\n\nAverage waiting time :"<<A.AvgWaitingTime()<<endl<<endl;


	cout<<"\n\n ---------------------------------- Static Priority Schedule ---------------------------------";

	A.MakeStaticPrioritySchedule();
	A.DisplaySchedule();
	cout<<"\n\nAverage waiting time :"<<A.AvgWaitingTime()<<endl<<endl;



return 0;

}
