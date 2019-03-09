#include<iostream>

using namespace std;


Scheduler::Scheduler()
{
LastProcessed.AT=0;
LastProcessed.BT=0;
LastProcessed.CT=1;
LastProcessed.TAT=0;
LastProcessed.WT=0;
CurrentTime=-1;
NoOfProcess=0;
ProcessInQueue=0;
TQ=3;
front=-1;
end=-1;

}




void Scheduler::Initialise(int pid,int at,int bt,int p)
{

	NoOfProcess++;

	process[NoOfProcess].Pid=pid;
	process[NoOfProcess].doneOrder=0;
	process[NoOfProcess].AT=at;
	process[NoOfProcess].BT=bt;
	process[NoOfProcess].RT=bt;
	process[NoOfProcess].priority=p;
	process[NoOfProcess].queued=0;



}


//------------------------------------------------ Function to clear all the calculated data ---------------------------------------------------------------


void Scheduler::Refresh()
{
	CurrentTime=-1;
	ProcessInQueue=0;
	front=-1;
	end=-1;
	LastProcessed.AT=0;
	LastProcessed.BT=0;
	LastProcessed.CT=1;
	LastProcessed.TAT=0;
	LastProcessed.WT=0;
	for(int i=0;i<10;i++)
	{
		process[i].doneOrder=0;
		process[i].queued=0;
		process[i].CT=0;
		process[i].TAT=0;
		process[i].WT=0;
		process[i].RT=process[i].BT;

	}
}




//-------------------------------------------------Function to clear all the data--------------------------------------------------------------------------


void Scheduler::Clear()
{


	TQ=3;
	for(int i=0;i<10;i++)
	{
		process[i].AT=0;
		process[i].BT=0;
		process[i].Pid=0;
	}

	Refresh();
	NoOfProcess=0;

}





// ------------------------------ Function to set custom Time Quantum. Default = 3 ------------------------------

void Scheduler::Set_TQ(int t)
{
	TQ=t;
}


// ----------------------------- Premtive Execution ----------------------------------------------------

int Scheduler::PE_Execute(int i,int Order,int rr) // rr means round robin
{

	if(rr)
	{

		int t;
		t=process[i].RT-TQ;
		//cout<<"\n process[i].RT= "<<process[i].RT;
		if(t<0)
		{

			CurrentTime+=process[i].RT;
			//cout<<"  CurrentTime(After)= "<<CurrentTime<<" process[i].RT= "<<process[i].RT;
			process[i].RT=0;
		}

		else
		{
			CurrentTime+=TQ;
			process[i].RT-=TQ;
		}


	}

	else
	{
		process[i].RT--;
		CurrentTime++;

	}


	if(process[i].RT==0)
	{
		process[i].CT=CurrentTime;
		process[i].TAT=process[i].CT-process[i].AT;
		process[i].WT=process[i].TAT-process[i].BT;
		process[i].doneOrder=Order;
		cout<<"\n\t "<<CurrentTime<<"\t\t"<<process[i].Pid<<"\t\t"<<process[i].RT<<"\t     done";
		return 1;

	}

	else
	{
		cout<<"\n\t "<<CurrentTime<<"\t\t"<<process[i].Pid<<"\t\t"<<process[i].RT;
		return 0;
	}

}






// ------------------------------ Non Premtive Execution ----------------------------------------------------

void Scheduler::NPE_Execute(int i,int Order)
{
	process[i].CT=process[i].BT+CurrentTime;
	process[i].TAT=process[i].CT-process[i].AT;
	process[i].WT=process[i].TAT-process[i].BT;
	process[i].doneOrder=Order;
	LastProcessed=process[i];
	CurrentTime=process[i].CT;

}




//---------------------- Function For First Come First Serve Schedule -------------------------------------

void Scheduler::MakeFcfsSchedule()
{
    CurrentTime=0;
    LastProcessed.CT=0;
  for(int i=1;i<=NoOfProcess;i++)
  {
    if(process[i].AT>LastProcessed.CT)
      CurrentTime=process[i].AT;

    NPE_Execute(i,i);

  }

}

// ------------------------------------------ End of FCFS Scheduling -----------------------------------------------




// --------------------------------------- Shortest Job First Scheduling --------------------------------------

void Scheduler::MakeSjfSchedule()
{

	Refresh();
	int TasksDone=0;

	while(TasksDone<NoOfProcess)
	{
			int k=0,bt=1000000000;
			for(int j=1;j<=NoOfProcess;j++)
				if(process[j].AT<=CurrentTime && process[j].doneOrder==0)
					if(process[j].BT<bt)
					{
						k=j;
						bt=process[j].BT;
					}

			if(k==0)
				CurrentTime++;


			else
				NPE_Execute(k,++TasksDone);

	}

}
//-------------------------------------------- End of SJF Scheduling -------------------------------------------------------




// -------------------------------  Shortest Remaining Time Scheduling  -------------------------------------

void Scheduler::MakeSrtSchedule()
{
	Refresh();
	int TasksDone=0;

	cout<<"\n\n\t  ---------process--------";
	cout<<"\n\n      CurrentTime\t Pid\t Remaining Time"<<endl;
	while(TasksDone<NoOfProcess)
	{
		int MinRemainningTime=100000,p=-1;
		for(int i=1;i<=NoOfProcess;i++)
		{

			if(process[i].AT<=CurrentTime && process[i].RT>0)
				if(process[i].RT<MinRemainningTime)
				{
					MinRemainningTime=process[i].RT;
					p=i;
				}


		}

		if(p==-1)
			CurrentTime++;

		else
			TasksDone+=PE_Execute(p,TasksDone+1,0);
	}

}
//  ----------------------------------------  End of SRT Schedule  --------------------------------------------------




// ----------------------------------------   Round Robin Scheduling   ---------------------------------------------

void Scheduler::Queue(int p)
{
	if(front==-1)
			front=end=0;

	else
		end=++end%10;


	cout<<"\n\t "<<CurrentTime<<"\t\t"<<process[p].Pid<<"\t\t"<<process[p].RT<<"\t     Queued  ";
	ReadyQueue[end]=p;
	process[p].queued=1;
	ProcessInQueue++;

}


int Scheduler::Dequeue()
{
	int temp;
	temp = ReadyQueue[front];
	cout<<"\n\t "<<CurrentTime<<"\t\t"<<process[temp].Pid<<"\t\t"<<process[temp].RT<<"\t     Dequeued   ";
	front = ++front%10;
	process[temp].queued=0;
	ProcessInQueue--;

	return temp;
}



void Scheduler::MakeRoundRobinSchedule()
{

	Refresh();
	int TasksDone=0;
	int task=0;

	cout<<"\n\n\t  ---------process--------";
	cout<<"\n\n      CurrentTime\t Pid\t Remaining Time"<<endl;

	while(TasksDone<NoOfProcess)
	{
		int prevTime=0;
		if(ProcessInQueue<=0)
		{
			CurrentTime++;
			task=0;
		}


		else
		{
			task=Dequeue();
			prevTime=CurrentTime;
			TasksDone+=PE_Execute(task,TasksDone+1,1);
			//cout<<"\n prevTime= "<<prevTime<<"CurrentTime= "<<CurrentTime;
			//cout<<"\n task="<<task;
		}

		for(int j=prevTime;j<=CurrentTime;j++)
		{
			for(int i=1;i<=NoOfProcess;i++)
			{
				//cout<<"\n i= "<<i<<"CurrentTime="<<CurrentTime;//<<" at= "<<process[i].AT<<" queued= "<<process[i].queued<<" doneOrder= "<<process[i].doneOrder;
				if(process[i].AT<=j && process[i].queued==0 && process[i].doneOrder==0 && (i!=task || task==0))
				{

					Queue(i);
					//cout<<"\n i= "<<i<<"CurrentTime="<<CurrentTime;
				}

			}


		}

		if(task>0)
		{

			if( process[task].RT>0)
				Queue(task);
			task=0;
	  }

}



}

// --------------------------------------- End Of Round Robin Scheduling ---------------------------------------




// ------------------------------------- Highest Response Ratio Next Scheduling -------------------------------------

void Scheduler::MakeHrrnSchedule()
{
	Refresh();
	int TasksDone=0,t=0;

	while(TasksDone<NoOfProcess)
	{
		float rr=0.0;
		int p=0;
		for(int i=1;i<=NoOfProcess;i++)
		{
			if(process[i].AT<=CurrentTime && process[i].doneOrder==0)
			{

				float Ratio = (CurrentTime-process[i].AT + process[i].BT)/(process[i].BT * 1.0) ;
				if(Ratio>rr)
				{
					rr=Ratio;
					p=i;
				}

			}

		}


		if(p==0)
			CurrentTime++;

		else
			NPE_Execute(p,++TasksDone);

	}

}
// -------------------------------------------- End of HRR ------------------------------------------------






//------------------------------------- Static Priority Scheduling --------------------------------------------------

void Scheduler::MakeStaticPrioritySchedule()
{
	Refresh();
	int TasksDone=0;

	cout<<"\n\n\t  ---------process--------";
	cout<<"\n\n      CurrentTime\t Pid\t Remaining Time"<<endl;

	while(TasksDone<NoOfProcess)
	{
		int task=0,hp=0;
		for(int i=0;i<=NoOfProcess;i++)
		{
			if(process[i].AT<=CurrentTime && process[i].doneOrder==0)
				if(process[i].priority>hp)
				{
					hp=process[i].priority;
					task=i;
				}
		}

		if(task==0)
			CurrentTime++;

		else
			TasksDone+=PE_Execute(task,TasksDone+1,0);
	}

}




//------------------------------------------End of Static Priority Schedule-------------------------------------------------





// ----------------------- Function to calculate Average waiting time of Recently Executed Schedule  -------------------------

float Scheduler::AvgWaitingTime()
{
  float WaitSum=0.0;
  for(int i=1;i<=NoOfProcess;i++)
    WaitSum+=process[i].WT;

  return WaitSum/NoOfProcess;

}
//------------------------ End of Average Waiting time Function ---------------------------------------







//  ------------------- Function to Display Recently Executed Schedule -------------------------------------

void Scheduler::DisplaySchedule()
{

	cout<<"\n\n\n Pid\tAT\tBT\tCT\tTAT\tWT\tOrder\n\n";

	for(int i=1;i<=NoOfProcess;i++)
		cout<<" "<<process[i].Pid<<"\t"<<process[i].AT<<"\t"<<process[i].BT<<"\t"<<process[i].CT<<"\t"<<process[i].TAT<<"\t"<<process[i].WT<<"\t"<<process[i].doneOrder<<endl;

}

// ------------------------End of Display Function --------------------------------------------------
