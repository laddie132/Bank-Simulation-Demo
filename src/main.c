#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<graphics.h> 
#include "bank.h"

char ch;
tongji sta[8];//保存每个窗口统计结果
time_t cstart,start[8],end[8],rest[8],rstart[8];//end[8]保存每个客户服务时长
int MaxSeqLen=0,MinSec=0,MaxSec=0,MinRestSec=0,MaxRestSec=0,VIPSERVLen=0;
int vis[]={1,0,1,1,1,0,0,0}; //保存当前窗口"上班"或“关闭”状态或“休息”状态
int cur[]={-1,-1,-1,-1,-1,-1,-1,-1};//保存当前窗口服务客户编号
int maxnumber=-1,counts=0,vmaxnumber=-1,vcounts=0,current=-1,vcurrent=-1,iswait=0,isclose=0,flag=1,tactic=1;

int main()
{
	system("color 71"); 
	printf("\t\tWelcome to the vitual bank system!\n\n\n\n\n");
	printf("X:VIP update\n\n");
	printf("W:Enter bank system\n\n");
	printf("Q:Quit\n\n\n\n");
	printf("Please input 'X' 'Q' or 'W' to choose the function you want.\n\n");
	scanf("%c",&ch);
	if(ch=='W'||ch=='X'){
		if(ch=='X') vip();//vip客户资料更新
        srand((int)time(0));
        memset(sta,0,sizeof(sta));
     	cconfig();//从配置文件中导入参数
        DWORD ThreadID1 = 1;
        HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)work,NULL,0,&ThreadID1);
        DWORD ThreadID2 = 2;
        HANDLE hRead2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)reprint,NULL,0,&ThreadID2);
        CloseHandle(hRead1);
        CloseHandle(hRead2);
        while(scanf("%c",&ch)){
         	if(ch=='G'||ch=='V'){//新客户到达抽号
    	    	pnumber();
    	    }
        	else if(ch=='R'){//窗口暂停
    	    	pause();
    	    }
        	else if(ch=='Q'){//等待下班状态
          		printf("------The bank will enter the state of waitting.-----\n\n");
        		iswait=1;
    	    	break;
    	    }
    	    else if(ch!='\n') printf("-----illegal input!------\n\n");
        }
        int isok=0,i=0;
        while(counts!=0||vcounts!=0||!isok)
        {
        	for(i=0,isok=1;i<8;i++)
        	{
	        	if(cur[i]!=-1){
	        		isok=0;
	        		break;
	        	}
	        }
        	Sleep(1000);
        }
        statices();//输出统计结果文件
        printf("--------The bank will be closed.--------\n\n");
	}
	else if(ch!='Q') printf("-------illegal input!------\n\n");
	isclose=1;
	system("pause");
	return 0;
}
void reprint()//每隔10秒打印一次银行运行情况
{
	printf("\n\n****Please input 'G','V','Rx' or 'Q' to choose your function.****\n\n");
	Sleep(1000);
	while(!isclose){
		print();
		Sleep(10000);
	}
}
