#include<stdio.h>
#include<windows.h>
#include<time.h>
#include "bank.h"

extern int counts,vcounts,current,vcurrent,isclose,VIPSERVLen,flag,tactic;
extern int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen;
extern int vis[8],cur[8],printselect[2];
extern tongji sta[8];
extern time_t cstart,start[8],end[8],rest[8],rstart[8];
time_t curtime;
int i;

void work()
{
    serve();//模拟办理业务
    check();//动态调整服务窗口
    if(tactic==0&&!vcounts){//vip客户服务普通客户
        for(i=0;i<8;i++)
        {
            if(vis[i]==1&&cur[i]==-1&&counts){
                cur[i]=++current;
                counts--;
                start[i]=time(NULL);
                end[i]=rand()%(MaxSec-MinSec+1)+MinSec;
                sta[i].renshu++;
                sta[i].shichang+=end[i];
                if(i<=1) printselect[i]=0;
            }
        }
    }
    else{//vip窗口服务vip客户
        for(i=0;i<2;i++)
        {
            if(vis[i]==1&&cur[i]==-1&&vcounts){
                cur[i]=++vcurrent;
                vcounts--;
                start[i]=time(NULL);
                end[i]=rand()%(MaxSec-MinSec+1)+MinSec;
                sta[i].renshu++;
                sta[i].shichang+=end[i];
                printselect[i]=1;
            }
        }
        for(i=2;i<8;i++)
        {
            if(vis[i]==1&&cur[i]==-1&&counts){
                cur[i]=++current;
                counts--;
                start[i]=time(NULL);
                end[i]=rand()%(MaxSec-MinSec+1)+MinSec;
                sta[i].renshu++;
                sta[i].shichang+=end[i];
            }
        }
    }
} 

void serve()//模拟办理业务 
{
	curtime=time(NULL);
    if(curtime-cstart>VIPSERVLen&&vcounts<3) vis[1]=0;//动态关闭vip窗口 
    else if(vcounts>=3) flag=1;
    for(i=0;i<8;i++)//检查当前窗口客户是否办理完业务以及窗口是否休息完毕 
    {
   	     if(cur[i]!=-1&&curtime-start[i]==end[i]){
	       	 cur[i]=-1;
	       	 if(vis[i]==-2){
     	 		rstart[i]=curtime;
      	 		vis[i]=-1;
       	 	}
        }
	    if(vis[i]==-1&&curtime-rstart[i]==rest[i]) vis[i]=1;
    }
}
