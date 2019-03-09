// This prog reads the file in the current directory, takes Arrival time as 
// file creation time, Burst time as word count and pid as file name. Then Schedules it
// accordingly.


#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// class time to store time

class Time
{
public:
  // data members
  int min,hrs;

  // member functions
  Time();
  int IsGreaterThan(Time x);
  void Assign(int hours,int minutes);
  void Assign(Time t);
  Time Substract(Time b);
  Time Add(Time b);
  void DisplayTime();
};


Time::Time()
{
  hrs=0;
  min=0;
}


int Time::IsGreaterThan(Time x)
{
  if(hrs>x.hrs)
    return 1;

  else if(hrs==x.hrs && min>x.min)
    return 1;

  else
    return 0;
}




void Time::Assign(int hours, int minutes)
{
  hrs=hours+minutes/60;
  min=minutes%60;
}


void Time::Assign(Time t)
{
  hrs=t.hrs + t.min/60;
  min=t.min%60;
}


Time Time::Add(Time b)
{
  Time temp;
  temp.hrs=hrs+b.hrs;
  temp.min=min+b.min;

  return temp;

}


Time Time::Substract(Time b)
{
  Time temp;

  temp.hrs=hrs-b.hrs;
  temp.min=min-b.min;

  if(temp.min<0)
  {
    temp.hrs--;
    temp.min+=60;
  }

  return temp;

}


void Time::DisplayTime()
{
  cout<<" "<<hrs<<":"<<min;
}

// end of class Time





// class FileProcess holds the attributes of processes

class FileProcess
{
public:
  Time AT,CT,BT,TAT,WT;
  char FileName[20];
  int doneOrder;

};
// end of FileProcess




// Sheduling class

class FileScheduler
{

public:

  FileProcess process[20], LastProcessed;
  Time CurrentTime;
  int NoOfProcess;

  FileScheduler();

  void Initialise(char pid[],int at_hrs,int at_min, int bt);

	void Execute(int i, int Order);

	void MakeFcfsSchedule();

	void DisplaySchedule();

	//float AvgWaitingTime();



};


  FileScheduler::FileScheduler()
  {
    NoOfProcess=0;

  }


void  FileScheduler::Initialise(char pid[],int at_hrs,int at_min, int bt)
  {
    strcpy(process[NoOfProcess].FileName,pid);
    process[NoOfProcess].AT.Assign(at_hrs,at_min);
    process[NoOfProcess].BT.Assign(0,bt);
    NoOfProcess++;

  }



  void FileScheduler::Execute(int i,int Order)
  {
    process[i].CT.Assign(process[i].BT.Add(CurrentTime));
    process[i].TAT.Assign(process[i].CT.Substract(process[i].AT));
    process[i].WT.Assign( process[i].TAT.Substract(process[i].BT));
    process[i].doneOrder=Order;

    LastProcessed=process[i];
    CurrentTime.Assign(process[i].CT);


  }


  void FileScheduler::MakeFcfsSchedule()
  {
      LastProcessed.CT.Assign(0,0);
      CurrentTime.Assign(0,0);

    for(int i=0;i<NoOfProcess;i++)
    {
      if(process[i].AT.IsGreaterThan(LastProcessed.CT))
        CurrentTime=process[i].AT;

      Execute(i,i);
    }

  }




  void FileScheduler::DisplaySchedule()
  {


    cout<<"\n\n\n Pid\t\t\t\tAT\t\t BT    \t\tCT\t \tTAT\t\t WT\t \tOrder\n\n";
    for(int i=0;i<NoOfProcess;i++)
    {
      printf("%-30s",process[i].FileName);
      process[i].AT.DisplayTime();
      cout<<"\t\t";
      process[i].BT.DisplayTime();
      cout<<"\t\t";
      process[i].CT.DisplayTime();
      cout<<"\t\t";
      process[i].TAT.DisplayTime();
      cout<<"\t\t";
      process[i].WT.DisplayTime();
      cout<<"\t\t"<<process[i].doneOrder<<endl;

    }

  }


// End of FileSheduler






int main()
{

    FileScheduler A;


    system("ls -l > a.txt");
    FILE *fp;
    char a[10],b[10],c[10],d[10],e[10],f[10],filename[20], line[50],lines[20];

    int wordCount,hr,min;

    fp=fopen("a.txt","r");

    fscanf(fp,"%s %s",line,lines);

    while(!feof(fp))
    {

    fscanf(fp,"%s %s %s %s %d %s %s %d:%d %s",a,b,c,d,&wordCount,e,f,&hr,&min,filename);
    //cout<<"\n  qwe    : count : "<<wordCount<<" , hr"<<hr<<",  min "<<min<<"   ,file   "<<filename<<endl;

    A.Initialise(filename,hr,min,wordCount);

    }

    fclose(fp);


    A.MakeFcfsSchedule();
    cout<<"\n\n ----------------------------------First Come First Serve Schedule -------------------------------";


    cout<<"\n\n \n Time format-    hrs:min\n\n";
    A.DisplaySchedule();

    return 0;
}
