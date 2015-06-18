#include<stdio.h>
#include<time.h>
#include<windows.h>
#include "bank.h"


extern const int vis[8],cur[8],printselect[2];
extern const int maxnumber,counts,vmaxnumber,vcounts,current,vcurrent,iswait,tactic,isclose;

void fileprint()//实现文件输出
{
	FILE *fptr;
    if((fptr=fopen("bank.log","a"))!=NULL)
    {
		int i;
		time_t timer;
		time(&timer);
    	fprintf(fptr,"\n----------------The bank`s business log------------------\n");
    	fprintf(fptr,"Time:%s\n",ctime(&timer));
    	fprintf(fptr,"The quantity of waiting customer is:   common:%d     VIP:%d\n",counts,vcounts);
    	fprintf(fptr,"The maxnumer of customer is:           ");
    	if(maxnumber!=-1) fprintf(fptr,"common:%d%d%d     ",maxnumber/100,(maxnumber/10)%10,maxnumber%10);
    	else fprintf(fptr,"common:NULL\t");
    	if(vmaxnumber!=-1) fprintf(fptr,"VIP:V%d%d\n",vmaxnumber/10,vmaxnumber%10);
    	else fprintf(fptr,"VIP:NULL\n");
    	fprintf(fptr,"The state of all windows is:\n");
    	fprintf(fptr,"windows: VIP1\tVIP2\t3\t4\t5\t6\t7\t8\t\n");
    	fprintf(fptr,"State:   ");
     	for(i=0;i<8;i++)
    	{
	    	if(cur[i]!=-1||vis[i]==1) fprintf(fptr,"work\t");
    		else if(vis[i]==-1) fprintf(fptr,"pause\t");
    		else fprintf(fptr,"close\t");
    	}
    	fprintf(fptr,"\ncurrent: ");
    	for(i=0;i<8;i++)
     	{
     		if(cur[i]!=-1){
                if(i<=1&&printselect[i]){
		    		fprintf(fptr,"V%d%d\t",cur[i]/10,cur[i]%10);
		     	}
		    	else fprintf(fptr,"%d%d%d\t",cur[i]/100,(cur[i]/10)%10,cur[i]%10);
	  	    }
	    	else fprintf(fptr,"NULL\t");
    	}
    	fprintf(fptr,"\nIs waiting for closed?");
    	if(iswait) fprintf(fptr,"\tYes.\n");
    	else fprintf(fptr,"\tNo.\n");
    	fprintf(fptr,"----------------------------------------------------------\n\n");
    	fclose(fptr);
	}
}
