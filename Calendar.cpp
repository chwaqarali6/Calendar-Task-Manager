#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct Activity
{
	string title;
	string user_id;
	string act_id;
	float priority;
	int duration;
};
void textcolor(int c);
void gotoxy(int x, int y);
void clrscr();
int PrintMenu();
void Initialize(Activity **** & Calendar,int MonthDays[]);
void ReadFile (Activity **** & Calendar);
void SaveActivity(Activity **** & Calendar,int Date,int Month,int StartTime,int EndTime,char UserID[],char ActID[],char Title[],float Priority);
Activity * ExtendBy1(Activity **** & Calendar,int Date,int Month,int StartTime, int size);
Activity * ReduceBy1(Activity **** & Calendar,char ID[],int Date,int Month,int StartTime, int size);
void PrintCalendar(Activity **** & Calendar,int MonthDays[]);
void Choice0(Activity **** & Calendar,int MonthDays[]);
void Choice1(Activity **** & Calendar,int MonthDays[]);
void Choice2(Activity **** & Calendar,int MonthDays[]);
void Choice3(Activity **** & Calendar,int MonthDays[],int StartDay, int StartMonth, int EndDay, int EndMonth,int ActivitiesToShow);
void Choice4(Activity **** & Calendar,int MonthDays[]);
void Choice5(Activity **** & Calendar,int MonthDays[]);
void Choice6(Activity **** & Calendar,int MonthDays[]);
void Choice7(Activity **** & Calendar,int MonthDays[]);
void main()
{
	int Choice=0;		
	Activity **** Calendar;	
	int MonthDays[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int StartMonth=0;
	int StartDay=0;
	int EndMonth=0;
	int EndDay=0;
	int ActivitiesToShow=5;
	textcolor(15);
	Initialize(Calendar,MonthDays);
	ReadFile(Calendar);
	PrintCalendar(Calendar,MonthDays);
	Choice=PrintMenu();
	while(Choice!=9)
	{
		switch(Choice)
		{
			case 0:
				Choice0(Calendar,MonthDays);
				break;	
			case 1:
				Choice1(Calendar,MonthDays);
				break;		
			case 2:
				Choice2(Calendar,MonthDays);
				break;	
			case 3:				
				cout<<"Enter Starting Date Day 1-31:-";
				cin>>StartDay;
				cout<<"Enter Starting Date Month 1-12:-";
				cin>>StartMonth;
				cout<<"Enter Ending Date Day 1-31:-";
				cin>>EndDay;
				cout<<"Enter Ending Date Month 1-12:-";
				cin>>EndMonth;
				Choice3(Calendar,MonthDays,StartDay,StartMonth,EndDay,EndMonth,ActivitiesToShow);
				break;
			case 4:
				Choice4(Calendar,MonthDays);
				break;
			case 5:
				Choice5(Calendar,MonthDays);
				break;			
			case 6:
				Choice6(Calendar,MonthDays);
				PrintCalendar(Calendar,MonthDays);				
				break;
			case 7:
				Choice7(Calendar,MonthDays);
				break;
			case 8:
				PrintCalendar(Calendar,MonthDays);
				break;
			case 9:
				break;
			default:
				cout<<"Please Enter Valid Option.";
		}	
		cout<<endl;
		Choice=PrintMenu();
	}
	cout<<"Program Successfuly Ended.";
	_getch();
}
void textcolor(int c)
{
	static HANDLE hStdout = NULL;
	if(!hStdout)
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,c);
}
void gotoxy(int x, int y)
{
	static HANDLE hStdout = NULL;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	if(!hStdout)
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout,coord);
}
void clrscr()
{
	static HANDLE hStdout = NULL;      
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	const COORD startCoords = {0,0};   
	DWORD dummy;
	if(!hStdout){
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout,&csbi);}
	FillConsoleOutputCharacter(hStdout,' ',csbi.dwSize.X * csbi.dwSize.Y,startCoords,&dummy);    
	gotoxy(0,0);
}
int PrintMenu()
{
	int Choice=0;
	cout<<" -----------------------Menu------------------------------- "<<endl;
	cout<<"0-------------- Clean the Calendar."<<endl;
	cout<<"1-------------- List All Activities Of A Given User During A Time Period."<<endl;
	cout<<"2-------------- List The Top 5 Activities Of A Given User During A Time Period."<<endl;
	cout<<"3-------------- List The Five Busiest Users In A Given Time Period."<<endl;
	cout<<"4-------------- Print Activity Stats For A Given Month."<<endl;
	cout<<"5-------------- Print Calendar Stats."<<endl;
	cout<<"6-------------- Remove A User From The Calendar."<<endl;
	cout<<"7-------------- Save The Calendar."<<endl;
	cout<<"8-------------- Print The Calendar."<<endl;
	cout<<"9-------------- Exit."<<endl;
	cout<<endl;
	cout<<"Please Enter Your Choice:- ";
	cin>>Choice;
	return Choice;
}
void Initialize(Activity **** & Calendar,int MonthDays[])
{
	Calendar= new Activity *** [12] ;
	for(int i=0; i<12; i++)
		Calendar[i]= new Activity ** [MonthDays[i]];	
	for(int i=0; i<12; i++)
		for(int j=0; j<MonthDays[i]; j++)
			Calendar[i][j]= new Activity *[24];	
	for(int i=0; i<12; i++)
		for(int j=0; j<MonthDays[i]; j++)
			for(int k=0; k<24; k++)
			{
				Calendar[i][j][k]= new Activity [1];
				Calendar[i][j][k][0].title="";
			}	
}
void ReadFile (Activity **** & Calendar)
{
	ifstream fin;
	const int size=256;
	char skip;
	char enter[1]={'\0'};
	int Date=0;
	int Month=0;
	int StartTime=0;
	int EndTime=0;	
	char UserID[size]={'\0'};
	char ActID[size]={'\0'};
	char Title[size]={'\0'};
	float Priority=0;
	fin.open("Input.txt",ios::in);
	if(!fin)
	{	
		cout<<"Could Not Open File";
	}
	else
	{
		while(!fin.eof())
		{		
			fin>>Date;
			fin>>skip;
			fin>>Month;
			fin>>skip;
			fin>>StartTime;
			fin>>skip;
			fin>>EndTime;	
			fin>>skip;
			fin.getline(UserID,size,',');
			fin.getline(ActID,size,',');	
			fin.getline(Title,size,',');
			fin>>Priority;
			fin.getline(enter,1,'\n');
			if(Date>0 && Month>0)
				SaveActivity(Calendar,Date-1,Month-1,StartTime,EndTime,UserID,ActID,Title,Priority);
		}
		
	}	
	fin.close();
}
void SaveActivity(Activity **** & Calendar,int Date,int Month,int StartTime,int EndTime,char UserID[],char ActID[],char Title[],float Priority)
{
	int count=0;
	for(int i=0; Calendar[Month][Date][StartTime][i].title!=""; i++,count++);	
	Calendar[Month][Date][StartTime]=ExtendBy1(Calendar,Date,Month,StartTime,count+1);
	Calendar[Month][Date][StartTime][count].title=Title;
	Calendar[Month][Date][StartTime][count].user_id=UserID;
	Calendar[Month][Date][StartTime][count].act_id=ActID;
	Calendar[Month][Date][StartTime][count].priority=Priority;
	Calendar[Month][Date][StartTime][count].duration=EndTime-StartTime;
	Calendar[Month][Date][StartTime][count+1].title="";
}
Activity * ExtendBy1(Activity **** & Calendar,int Date,int Month,int StartTime, int size)
{
	Activity *extend=new Activity [size+1] ;
	for(int i=0; i<size; i++)
		extend[i]=Calendar[Month][Date][StartTime][i];
	delete []Calendar[Month][Date][StartTime];
	return extend;
}
Activity * ReduceBy1(Activity **** & Calendar,char ID[],int index,int Date,int Month,int StartTime, int size)
{
	Activity *Reduce=new Activity [size-1] ;
	for(int i=0,j=0; i<size; i++)
		if(Calendar[Month][Date][StartTime][i].user_id!=ID && i!=index)
			Reduce[j++]=Calendar[Month][Date][StartTime][i];
	delete []Calendar[Month][Date][StartTime];
	return Reduce;
}
void PrintCalendar(Activity **** & Calendar,int MonthDays[])
{
	clrscr();
	int y=0;
	int a[12]={0,25,50,0,25,50,0,25,50,0,25,50};
	int b[12]={3,3,3,13,13,13,23,23,23,33,33,33};
	string MonthName[12]={"\tJANUARY","\tFEBURARY","\tMARCH","\tAPRIL","\t  MAY","\tJUNE",
						  "\tJULY","\tAUGUST","\tSEPTEMBER","\tOCTOBER","\tNOVEMBER","\tDECEMBER"};	
	int FirstDay=5, Month=0;
	int count=0;
	textcolor(12);
	cout<<endl<<"----------------------------------2015---------------------------------"<<endl;
	textcolor(15);
	while (Month <= 11)
	{
		gotoxy(a[Month],b[Month]);
		textcolor(14);
		cout<<MonthName[Month]<<endl<<endl;
		textcolor(128);
		y=b[Month]+1;
		gotoxy(a[Month],y);
		cout<<" S  M  T  W  T  F  S "<<endl;
		textcolor(15);
		gotoxy(a[Month],++y);
		for(int i=1;i<FirstDay;i++) 
			cout<<"   ";
		if(Month==7)
				cout<<"                  ";
		for(int j = 1; j <= MonthDays[Month]; j++) 
		{ 
			if(((j+FirstDay-2)%7==0) && (j!=1))
				gotoxy(a[Month],++y);
			if(j<10)
					cout<<" ";
			for(int k=0; k<24; k++)
				for(int l=0; Calendar[Month][j-1][k][l].title!=""; l++,count++);
			if(count>=1)
			{					
				textcolor(10);				
				cout<<j<<" ";	
				textcolor(15);
			}
			else
				cout<<j<<" ";
			count=0;
		} 			
		cout<<endl<<endl<<endl;
		FirstDay=((MonthDays[Month]+FirstDay)%7);
		Month++;	
	}
}
void Choice0(Activity **** & Calendar,int MonthDays[])
{
	int count=0;
	for(int i=0; i<12; i++)
		for(int j=0; j<MonthDays[i]; j++)
			for(int k=0; k<24; k++)
				for(int l=0; Calendar[i][j][k][l].title!="";l++)					
					for(int m=l+1; Calendar[i][j][k][m].title!=""; m++)
					{
						count=0;
						for(int n=0; Calendar[i][j][k][n].title!=""; n++,count++);
						if(Calendar[i][j][k][l].user_id==Calendar[i][j][k][m].user_id)
						{
							if(Calendar[i][j][k][l].priority>Calendar[i][j][k][m].priority)
							{
								Calendar[i][j][k]=ReduceBy1(Calendar,"",m,j,i,k,count+1);
								Calendar[i][j][k][count-1].title="";	
								--m;
							}
							else if(Calendar[i][j][k][l].priority<Calendar[i][j][k][m].priority)
							{
								Calendar[i][j][k]=ReduceBy1(Calendar,"",l,j,i,k,count+1);
								Calendar[i][j][k][count-1].title="";	
								--m;
							}	
						}
					}	
	cout<<endl<<"Calendar Cleaned!."<<endl;
}
void Choice1(Activity **** & Calendar,int MonthDays[])
{
	char ID[256]={'\0'};
	int StartMonth=0;
	int StartDay=0;
	int EndMonth=0;
	int EndDay=0;
	int count =0;
	cout<<"Please Enter The UserID:- ";
	cin.ignore(1);
	cin.getline(ID,256,'\n');
	cout<<"Enter Starting Date Day 1-31:-";
	cin>>StartDay;
	cout<<"Enter Starting Date Month 1-12:-";
	cin>>StartMonth;
	cout<<"Enter Ending Date Day 1-31:-";
	cin>>EndDay;
	cout<<"Enter Ending Date Month 1-12:-";
	cin>>EndMonth;
	if((StartDay>=1 && StartDay<=31) && (StartMonth>=1 && StartMonth<=12) && (EndDay>=1 && EndDay<=31) && (EndMonth>=1 && EndMonth<=12) && (StartDay<=EndDay && StartMonth<=EndMonth))
	{
		MonthDays[EndMonth-1]=EndDay;
		for(int i=(StartMonth-1); i<=(EndMonth-1); i++)
			for(int j=(StartDay-1); j<=(MonthDays[i]-1); j++)
				for(int k=0; k<24; k++)
					for(int l=0; Calendar[i][j][k][l].title!=""; l++)
						if(Calendar[i][j][k][l].user_id==ID){
							cout<<endl;
							cout<<"Title:- "<<Calendar[i][j][k][l].title<<endl;
							cout<<"User ID:- "<<Calendar[i][j][k][l].user_id<<endl;
							cout<<"Activity ID:- "<<Calendar[i][j][k][l].act_id<<endl;
							cout<<"Priority:- "<<Calendar[i][j][k][l].priority<<endl;
							cout<<"Duration:- "<<Calendar[i][j][k][l].duration<<endl;
							cout<<endl<<endl;
							count++;}
		if(count==0)
			cout<<"ERROR: No Data Found.";
	}
	else
		cout<<"Please Enter Correct Dates And Months."<<endl;
}
void Choice2(Activity **** & Calendar,int MonthDays[])
{
	char ID[256]={'\0'};
	int StartMonth=0;
	int StartDay=0;
	int EndMonth=0;
	int EndDay=0;
	int TotalActivities =0;	
	int index=0;
	float *Highest;
	int count=0;
	cout<<"Please Enter The UserID:- ";
	cin.ignore(1);
	cin.getline(ID,256,'\n');
	cout<<"Enter Starting Date Day 1-31:-";
	cin>>StartDay;
	cout<<"Enter Starting Date Month 1-12:-";
	cin>>StartMonth;
	cout<<"Enter Ending Date Day 1-31:-";
	cin>>EndDay;
	cout<<"Enter Ending Date Month 1-12:-";
	cin>>EndMonth;
	if((StartDay>=1 && StartDay<=MonthDays[EndMonth-1]) && (StartMonth>=1 && StartMonth<=12) && (EndDay>=1 && EndDay<=MonthDays[EndMonth-1]) && (EndMonth>=1 && EndMonth<=12))
	{
		MonthDays[EndMonth-1]=EndDay;
		for(int i=(StartMonth-1); i<=(EndMonth-1); i++)
			for(int j=(StartDay-1); j<=(MonthDays[i]-1); j++)
				for(int k=0; k<24; k++)
					for(int l=0; Calendar[i][j][k][l].title!=""; l++){
						if(Calendar[i][j][k][l].user_id==ID)
							TotalActivities++;}
		if(TotalActivities==0)
			cout<<"No Activities Of This User. ";
		else if(TotalActivities<=5)
			Highest=new float [5];
		else
			Highest=new float [TotalActivities];
		for(int i=(StartMonth-1); i<=(EndMonth-1); i++)
			for(int j=(StartDay-1); j<=(MonthDays[i]-1); j++)
				for(int k=0; k<24; k++)
					for(int l=0; Calendar[i][j][k][l].title!=""; l++){
						if(Calendar[i][j][k][l].user_id==ID)
							Highest[index++]=Calendar[i][j][k][l].priority;}		
		for(int i=0; i<TotalActivities; i++)
			for(int j=i;j<TotalActivities;j++)
				if(Highest[j]>Highest[i]){
					float temp=Highest[j];
					Highest[j]=Highest[i];
					Highest[i]=temp;}
		for(int a=0; a<5 && a<TotalActivities; )
			for(int i=(StartMonth-1); i<=(EndMonth-1); i++)
				for(int j=(StartDay-1); j<=(MonthDays[i]-1); j++)
					for(int k=0; k<24; k++)
						for(int l=0; Calendar[i][j][k][l].title!=""; l++)				
								if(Calendar[i][j][k][l].user_id==ID && Calendar[i][j][k][l].priority==Highest[a]){
									cout<<endl;
									cout<<"Title:- "<<Calendar[i][j][k][l].title<<endl;
									cout<<"User ID:- "<<Calendar[i][j][k][l].user_id<<endl;
									cout<<"Activity ID:- "<<Calendar[i][j][k][l].act_id<<endl;
									cout<<"Priority:- "<<Calendar[i][j][k][l].priority<<endl;
									cout<<"Duration:- "<<Calendar[i][j][k][l].duration<<endl;
									cout<<endl<<endl;
									count++;
									a++;}
		if(count==0)
			cout<<"ERROR: No Data Found."<<endl;
	}
	else
		cout<<"Please Enter Correct Dates And Months."<<endl;
	
}
void Choice3(Activity **** & Calendar,int MonthDays[],int StartDay, int StartMonth, int EndDay, int EndMonth,int ActivitiesToShow)
{
	string *ID;
	int TotalUsers=0;
	int index=0;
	int count=0;
	int TotalActivities=0;
	if((StartDay>=1 && StartDay<=MonthDays[EndMonth-1]) && (StartMonth>=1 && StartMonth<=12) && (EndDay>=1 && EndDay<=MonthDays[EndMonth-1]) && (EndMonth>=1 && EndMonth<=12))
	{ 
		MonthDays[EndMonth-1]=EndDay;
		for(int i=(StartMonth-1); i<=(EndMonth-1); i++)
			for(int j=(StartDay-1); j<=(MonthDays[i]-1); j++)
				for(int k=0; k<24; k++)
					for(int l=0; Calendar[i][j][k][l].title!=""; l++,TotalActivities++);
		ID=new string[TotalActivities];
		for(int i=(StartMonth-1); i<=(EndMonth-1); i++)			
			for(int j=(StartDay-1); j<=(MonthDays[i]-1); j++)
				for(int k=0; k<24; k++)
					for(int l=0; Calendar[i][j][k][l].title!=""; l++)
					{
						for(string* p = &ID[0]; p != &ID[TotalActivities]; ++p)
							if(Calendar[i][j][k][l].user_id==*p)
								count++;
						if(count==0)
							ID[index++]=Calendar[i][j][k][l].user_id;		
						count=0;
					}
		int *Frequency=new int [index];
		for(int i=0; i<index; i++)
			Frequency[i]=0;
		for(int i=(StartMonth-1); i<=(EndMonth-1); i++)			
			for(int j=(StartDay-1); j<=(MonthDays[i]-1); j++)
				for(int k=0; k<24; k++)
					for(int l=0; Calendar[i][j][k][l].title!=""; l++)
						for(int m=0; m<index; m++)
							if(Calendar[i][j][k][l].user_id==ID[m])
								++Frequency[m];				
		for(int i=0; i<index; i++)
			for(int j=i; j<index; j++)
				if(Frequency[i]<Frequency[j]){
					int temp=Frequency[i];
					string copy=ID[i];
					Frequency[i]=Frequency[j];
					ID[i]=ID[j];
					Frequency[j]=temp;
					ID[j]=copy;}
		for(int i=0;i<ActivitiesToShow && i<index; i++,count++)
				cout<<"User '"<<ID[i]<<"' With "<<Frequency[i]<<" Activities."<<endl;		
		if(count==0)
			cout<<"ERROR: No Data Found."<<endl;
		cout<<endl;
	}
	else
		cout<<"Please Enter Correct Dates And Months."<<endl;
}
void Choice4(Activity **** & Calendar,int MonthDays[])
{
	int DayActivities=0;
	int Sum=0;
	float Average=0;
	float MonthActivities=0;
	int Month=0;
	cout<<"Enter The Month Number from 1-12:- ";
	cin>>Month;	

	if(Month>=1 && Month<=12)
	{
		int *ActInADay=new int [MonthDays[Month-1]];
		for(int j=0; j<MonthDays[Month-1]; j++)
		{
			for(int k=0; k<24; k++)
				for(int l=0; Calendar[Month-1][j][k][l].title!=""; l++,MonthActivities++,DayActivities++);		
			ActInADay[j]=DayActivities;
			DayActivities=0;
		}	
		int *Copy=new int [MonthDays[Month-1]];
			for(int i=0; i<MonthDays[Month-1]; i++)
				Copy[i]=ActInADay[i];
			for(int i=0; i<MonthDays[Month-1]; i++)
				for(int j=i; j<MonthDays[Month-1]; j++)
					if(Copy[i]<Copy[j]){
						int temp=Copy[i];
						Copy[i]=Copy[j];
						Copy[j]=temp;}
		cout<<endl<<"The Total Number Of Activities In Month:- "<<MonthActivities;
		Average=MonthActivities/MonthDays[Month-1];
		cout<<endl<<"The Average Number Of Activities Per Day:- "<<Average;
		for(int j=0,i=0; j<MonthDays[Month-1],i<1; j++)
			if(Copy[i]==ActInADay[j]){
				cout<<endl<<"The Busiest Day In Month is "<<j+1<<" with "<<Copy[i]<<" Activities";
				i++;}		
		cout<<endl<<"The Busiest User Of The Month Is ";
		Choice3(Calendar,MonthDays,1,Month,MonthDays[Month-1],Month,1);
	}
	else
		cout<<"Please Enter Correct Dates And Months."<<endl;
}
void Choice5(Activity **** & Calendar,int MonthDays[])
{
	int MonthActivities=0;
	int Sum=0;
	float Average=0;
	float TotalActivities=0;
	int ActInAMonth[12]={0};
	for(int i=0; i<12; i++)
	{
		for(int j=0; j<=(MonthDays[i]-1); j++)
			for(int k=0; k<24; k++)
				for(int l=0; Calendar[i][j][k][l].title!=""; l++,TotalActivities++,MonthActivities++);
		ActInAMonth[i]=MonthActivities;
		MonthActivities=0;
	}
	int Max=ActInAMonth[0];
	for(int i=0; i<12; i++)
		if(Max<ActInAMonth[i])
			Max=ActInAMonth[i];
	cout<<endl<<"The Total Number Of Activities In Year:- "<<TotalActivities;
	Average=TotalActivities/12;
	cout<<endl<<"The Average Number Of Activities Per Month:- "<<Average;
	for(int i=0; i<12; i++)
		if(Max==ActInAMonth[i])
			cout<<endl<<"The Busiest Month In Year is "<<i+1<<" with "<<Max<<" Activities."<<endl;	
	for(int i=0; i<12; i++){
		cout<<endl<<"The Busiest User Of The Month "<<i+1<<" is:- "<<endl;
		Choice3(Calendar,MonthDays,1,i+1,MonthDays[i],i+1,1);}
}
void Choice6(Activity **** & Calendar,int MonthDays[])
{
	char ID[256]={'\0'};
	int count=0;
	bool check=false;
	cout<<"Please Enter The UserID:- ";
	cin.ignore(1);
	cin.getline(ID,256,'\n');

	for(int i=0; i<12; i++)
		for(int j=0; j<MonthDays[i]; j++)
			for(int k=0; k<24; k++)
			{
				for(int l=0; Calendar[i][j][k][l].title!=""; l++,count++)
					if(Calendar[i][j][k][l].user_id==ID)
						check=true;			
				if(check)
				{
					Calendar[i][j][k]=ReduceBy1(Calendar,ID,-1,j,i,k,count+1);
					Calendar[i][j][k][count-1].title="";
				}
				check=false;
				count=0;			
			}	
}
void Choice7(Activity **** & Calendar,int MonthDays[])
{
	ofstream fout;
	fout.open("Input.txt",ios::out);
	
	for(int i=0; i<12; i++)
		for(int j=0; j<MonthDays[i]; j++)
			for(int k=0; k<24; k++)
				for(int l=0; Calendar[i][j][k][l].title!=""; l++)	
					fout<<j+1<<"/"<<i+1<<","<<k<<","<<k+Calendar[i][j][k][l].duration<<","<<Calendar[i][j][k][l].user_id<<","<<Calendar[i][j][k][l].act_id<<","<<Calendar[i][j][k][l].title<<","<<Calendar[i][j][k][l].priority<<endl;	
	fout.close();
	cout<<endl<<"Calendar Saved!."<<endl;
}

