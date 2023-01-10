// Ver 2
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
int daysOFmonth[]={0,31,28,31,30,31,30,31,31,30,31,30,31};	
char *months[]=
{
	" ",
	"\n\n\nJanuary",
	"\n\n\nFebruary",
	"\n\n\nMarch",
	"\n\n\nApril",
	"\n\n\nMay",
	"\n\n\nJune",
	"\n\n\nJuly",
	"\n\n\nAugust",
	"\n\n\nSeptember",
	"\n\n\nOctober",
	"\n\n\nNovember",
	"\n\n\nDecember"
};


int inputyear()
{
	int year,n;
	printf("Enter a year: ");
	// scanf("%d", &year);
	n=scanf("%d",&year);
    	if (n==1)
    	{
		printf("Entered year is valid");
		return year;
	}
    	else
    	{
		printf("Entered year is not valid");
		exit(0);
	}
	
}

int Finding_Jan_1st_Day(int year)
{
	int First_Jan_Day;
	int Days_Divisible_By_4, Days_Divisible_By_100, Days_Divisible_By_400;
	
	Days_Divisible_By_4 = (year - 1.0)/ 4.0;  		// gives no of leap year
	Days_Divisible_By_100 = (year - 1.0)/ 100.0; 	// gives no of non leap years cause divisible by 100
	Days_Divisible_By_400 = (year - 1.0)/ 400.0; 	// gives no of leap year that are divisible by 400
	// these can be used to calculate total no of leap year till date
	First_Jan_Day = (year + (Days_Divisible_By_4 - Days_Divisible_By_100 + Days_Divisible_By_400)) %7;
	return First_Jan_Day;
}


int Finding_If_Leap_Year(int year)
{
	if(year% 4 == 0 && year%100 != 0 || year%400 == 0)
	{
		daysOFmonth[2] = 29;	//changes feb to 29 days
	}
	else
	{
		daysOFmonth[2] = 28;	//changes feb to 28 days
	}
}

void Display_Calendar(int year, int First_Jan_Day)
{
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("%s", months[month]);			//months is string array, month is position in array
		printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		//  First_Jan_Day just tells us what day jan 1st was for that year
		// Correct the position for the first date
		for ( day = 1; day <= 1 + First_Jan_Day * 5; day++ )
		{
			printf(" ");
		}
		
		// Print all the dates for one month
		for ( day = 1; day <= daysOFmonth[month]; day++ )
		{
			printf("%2d", day );
			
			// Is day before Sat? Else start next line Sun.
			if ( ( day + First_Jan_Day ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
			// Set position for next month
			First_Jan_Day = ( First_Jan_Day + daysOFmonth[month] ) % 7;
	}
}

void view_calender()
{
	int year,First_Jan_Day;
	year = inputyear();
	First_Jan_Day = Finding_Jan_1st_Day(year);
	Finding_If_Leap_Year(year);
	Display_Calendar(year, First_Jan_Day);
	printf("\n");
}
// under construction
void Display_Month(int year, int month)
{
	int day;
	int cumulative_daysOFmonth[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
	int Position = ( Finding_Jan_1st_Day(year) + cumulative_daysOFmonth[month] ) % 7;
	printf("%s", months[month]);			//months is string array, month is position in array
	printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
	//  First_Jan_Day just tells us what day jan 1st was for that year
	// Correct the position for the first date
	for ( day = 1; day <= 1 + Position * 5; day++ )
	{
		printf(" ");
	}
	
	// Print all the dates for one month
	for ( day = 1; day <= daysOFmonth[month]; day++ )
	{
		printf("%2d", day );
		
		// Is day before Sat? Else start next line Sun.
		if ( ( (day + Position )% 7 > 0 ))
			printf("   " ); 

		else
			printf("\n " );
	}
	
}
void add_event()
{
	time_t s;
	struct tm* current_time;
	s=time(NULL);
	current_time = localtime(&s);
	char arr[500];
	FILE *fp = fopen("Event.csv","a");
	if(fp==NULL)
	{
		printf("File cannot be opened");
	}
			
	int event_day;
	int event_month;
	char event[100];
	char ch;
	int idx =0;
	
	printf("Enter the event day and event month(dd mm): \n");
	scanf("%d %d",&event_day,&event_month);
	
	printf("Enter the name of the event: ");
	scanf(" %[^\n]s",event);
	
	printf("Event name \'%s\' has been scheduled for %d/%d/%d\n\n",event,event_day,event_month,(current_time->tm_year+1900));
	fprintf(fp,"%s,%d,%d\n",event,event_day,event_month);	
	fclose(fp);
}

int read_events()
{
	FILE *fp = fopen("Event.csv","r");
	if (fp == NULL)
	{
		printf("No File Found\n");
	}
	else
	{
		struct table
		{
			char *event;
			int date_,month_;	
		}csv[100];
		char line[100];
//		fprintf(stdout,"%s,%d,%d",fp);
		while(fgets(line,100,fp)!=NULL)
		{
			int i=0;
			csv[i].event = strtok(line,",");
			csv[i].date_ = atoi(strtok(NULL,","));
			csv[i].month_ = atoi(strtok(NULL,","));
			
			printf("Event Name:%s\ndate:%d\nmonth:%d\n",csv[i].event,csv[i].date_,csv[i].month_);
		}
		fclose(fp);
//		printf("Event Name:%s\ndate:%d\nmonth:%d\n",event,date_,month_);

	}
}

void filter_events()
{
	FILE *fp = fopen("Event.csv","r");
	int date_day;
	int date_month;
	int count =0;
	char arr[1000];
	char event_name[1000];
	int event_day;
	int event_month;
	int idx=0;
	
	int a =0;
	
	
	printf("Enter the month and date of the event(dd mm): ");
	scanf("%d %d",&date_day,&date_month);
	
	struct table
	{
		char event[1000];
		int date_,month_;	
	}event_info[100];
	
	while((fgets(arr,1000,fp))!=NULL)
	{
		
		
		//event_info[idx].event = strtok(arr,",");
		strcpy(event_info[idx].event,strtok(arr,","));
		event_info[idx].date_ = atoi(strtok(NULL,","));
		event_info[idx].month_ = atoi(strtok(NULL,","));
		idx++;
		count++;
		
	}
	printf("The following events were found scheduled for the given date: \n");
	fseek(fp,0,SEEK_SET);
	for(int i =0;i<count;i++)
	{
		if (event_info[i].date_ == date_day && event_info[i].month_ == date_month)
		{
			
			printf("%s \n",event_info[i].event);
			a++;
		}
		
	}
	
	if (a==0)
		printf("No event for the given date was found\n");
	
	
	fclose(fp);	
}

void delete_event()
{
	FILE *fp = fopen("Event.csv","r");
	time_t s;
	struct tm* current_time;
	s=time(NULL);
	current_time = localtime(&s);
	struct table
	{
		char event[1000];
		int date_,month_;	
	}event_info2[100];
	char line[100];
	int count =0;
	int idx=0;
	int choice;

	while(fgets(line,100,fp)!=NULL)
	{
		
		
		strcpy(event_info2[idx].event,strtok(line,","));
		event_info2[idx].date_ = atoi(strtok(NULL,","));
		event_info2[idx].month_ = atoi(strtok(NULL,","));
		count++;
		idx++;
			
		
	}
	printf("Select from the following scheduled events: \n");
	for(int i=0;i<count;i++)
	{
		printf("%d.\t\t%s\t\t%d/%d/%d \n",(i+1),event_info2[i].event,event_info2[i].date_,event_info2[i].month_,(current_time->tm_year+1900));
	}
	
	fclose(fp);
	
	printf("Enter the event to be deleted\n");
	scanf("%d",&choice);
	
	
	FILE *fp2 = fopen("Event.csv","w");
	
	for(int i =0;i<count;i++)
	{
		if((i+1) == choice)
		{
			printf(" ");
		}
		
		else
		{
			fprintf(fp,"%s,%d,%d\n",event_info2[i].event,event_info2[i].date_,event_info2[i].month_);
		}
		
	}
	
	fclose(fp2);	
	
}
int main()
{
	int option=1;
	do
	{
	printf("What do you want to do\n\t(1) View calendar\n\t(2) Add Event\n\t(3) Current Datetime\n\t(4) Monthly View\n\t(5) Display Events\n\t(6) Filter events\n\t(7) Delete events\n\t(0)Exit\n\n");
	scanf("%d",&option);
	if(option == 1)
	{
		view_calender();
	}
	else if(option == 2)
	{
		add_event();		
	}
	else if(option == 3)
	{
		time_t t = time(NULL);
		printf("Current time is: \t\t%s",ctime(&t));
	}
	else if(option == 4)
	{
		int years,Month ;
		printf("Select Year\t:");
		scanf("%d" ,&years);
		printf("\nSelect Month\t:");
		scanf("%d" ,&Month);
		Display_Month(years,Month);
	}
	else if (option == 5)
	{
		read_events();
	}
	else if(option==6)
	{
		filter_events();
	}
	
	else if(option==7)
	{
		delete_event();
	}
	
	else if(option == 0) 			// might be useless
	{
		exit(0);
	}
	else
	{
		printf("You messed up");
		// view_calender();
	}

	}while(option!=0);
	return 0;
}


