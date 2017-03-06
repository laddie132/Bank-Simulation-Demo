#include<stdio.h>
#include<stdlib.h>
#include<time.h>

extern time_t rest[8],rstart[8];
extern int cur[8],vis[8],MinRestSec,MaxRestSec;

void pause()
{
	int curwin=0,vcurwin=0,i,restnum;
	for(i=0;i<2;i++)//计算当前开放VIP窗口数和普通窗口数 
	   if(vis[i]==1) vcurwin++;
    for(i=2;i<8;i++)
       if(vis[i]==1) curwin++;
    scanf("%d",&restnum);
    if(restnum>=1&&restnum<=2&&vcurwin==2||restnum>=3&&restnum<=8&&curwin>3){
    	if(cur[restnum-1]!=-1) vis[restnum-1]=-2;
    	else{
	    	vis[restnum-1]=-1;
	    	rstart[restnum-1]=time(NULL);
	    }
    	rest[restnum-1]=(rand()%(MaxRestSec-MinRestSec+1))+MinRestSec;
    	printf("-------The number %d window will rest for %d seconds.-----\n\n",restnum,rest[restnum-1]);
    }
    else printf("Sorry,the current window is too less.Please application later.\n\n");
}
