#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "bank.h"

extern int maxnumber,counts,vmaxnumber,vcounts,current,vcurrent,MaxSeqLen;
extern char ch;

void pnumber()
{
	if(ch=='G'){//普通客户到达 
    	if(counts<MaxSeqLen){
	    	counts++;
    		maxnumber++;
    		printf("------A common customer come!-------\n\n");
	    }
	    else printf("-----The queue is reach to its maxseqlen.-----\n\n");
	}
	else if(ch=='V')//vip客户到达 
	{
		FILE *fptr;
		customer a;
		int wrong=0;
		if((fptr=fopen("vip.dat","r"))==NULL){
			printf("File can not open.\n");
		}
		else{
			while(wrong<3){ 
				printf("Please input the vip ID:\n\n");
	    		char temp[20];
    			int oks=0;
	    		scanf("%s",temp);
	    		rewind(fptr); 
    			fread(&a,sizeof(customer),1,fptr);
    			while(!feof(fptr)){
    				if(!strcmp(&temp[2],a.ID)){
    					oks=1;
     					break;
    				}
    				fread(&a,sizeof(customer),1,fptr);
    			}
    			if(!oks){//id号码输入错误 
    				wrong++;
			    	printf("Sorry,your ID is wrong.\n\n");
			    	printf("You left %d times!\n\n",3-wrong);
			    }
    			else{
    				if(vcounts<MaxSeqLen){
				    	vcounts++;
    		     		vmaxnumber++;
        				printf("------A vip customer come!------\n\n");
				    }
				    else printf("-----The queue is reach to its maxseqlen.-----\n\n");
    				break;
    			}
			}
			if(wrong==3){//连续输错三次默认普通客户 
				counts++;
        		maxnumber++;
	        	printf("------A common customer come!-------\n\n");
			}
			fclose(fptr); 
		}
	}
}
