//从config.ini配置文件中读入银行配置信息//

#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

extern int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen;

int cconfig()
{
	int i,flag=1;
	FILE *fptr;
    char ch[20],ch2[20];
    if ((fptr=fopen("config.ini","r"))==NULL){
    	printf("can not open this file\n");
        return 0;
    } 	   
    else{
	    while(!feof(fptr)){
	    	flag=1;
		    fgets(ch,sizeof(ch),fptr);
		    for(i=0;ch[i]!='\n'&&ch[i]!='\0';i++)
		    {
		    	if(ch[i]!=']'&&flag==1){
	    			ch2[i]=ch[i];
	    			continue;
	    		}
	    		if(ch[i]==']'){
	    			flag=0;
	    			ch2[i]=0;
		    		continue;
		    	}
	    		if(!strcmp(ch2,"[MaxSeqLen")) MaxSeqLen=MaxSeqLen*10+ch[i]-'0';
		    	else if(!strcmp(ch2,"[MinSec")) MinSec=MinSec*10+ch[i]-'0';
	    		else if(!strcmp(ch2,"[MaxSec")) MaxSec=MaxSec*10+ch[i]-'0';
		   		else if(!strcmp(ch2,"[MinRestSec")) MinRestSec=MinRestSec*10+ch[i]-'0';
				else if(!strcmp(ch2,"[MaxRestSec")) MaxRestSec=MaxRestSec*10+ch[i]-'0';
				else if(!strcmp(ch2,"[VIPSERVLen")) VIPSERVLen=VIPSERVLen*10+ch[i]-'0';
		    }
     	}
    }
    fclose(fptr);
    return 1;
}
