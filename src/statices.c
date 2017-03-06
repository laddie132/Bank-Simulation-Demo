#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#include"bank.h"

extern int maxnumber,vmaxnumber;
extern tongji sta[8];

void statices()//输出每个窗口的统计信息 
{
	FILE *fptr;
    int count;
	if((fptr=fopen("statices.log","a"))==NULL)
		printf("File could not be opened.\n");
	else {
		time_t timer;
		time(&timer);
		fprintf(fptr,"----------------------------------------------------------\n"); 
		fprintf(fptr,"Time:%s\n",ctime(&timer));
		fprintf(fptr,"Window\tTotal customer\tTotal time\tAverage time\n");
		for (count=0;count<=7;count++){
			fprintf(fptr,"%d\t%d\t\t%d\t\t%.2f\n",count+1,sta[count].renshu,sta[count].shichang,sta[count].renshu==0?0:((float)sta[count].shichang/sta[count].renshu));
		}
		fprintf(fptr,"\n");
		fprintf(fptr,"Total ordinary customer:%d\n",maxnumber+1);
		fprintf(fptr,"Total vip customer:%d\n",vmaxnumber+1);
		fprintf(fptr,"----------------------------------------------------------\n\n");
		fclose(fptr);
	}
}
