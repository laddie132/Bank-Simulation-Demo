#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "bank.h"

extern int maxnumber,counts,vmaxnumber,vcounts,current,vcurrent,MaxSeqLen,iswait;
extern char vipid[20];

int pnumber(char ch)
{
    if(!iswait){
        if(ch=='G'){//普通客户到达
            if(counts<MaxSeqLen){
                counts++;
                maxnumber++;
                return 1;
            }
            else return 0;
        }
        else if(ch=='V')//vip客户到达
        {
            FILE *fptr;
            customer a;
            if((fptr=fopen("vip.dat","r"))==NULL){
                return -2;
            }
            else{
                int oks=0;
                fread(&a,sizeof(customer),1,fptr);
                while(!feof(fptr)){
                    if(!strcmp(&vipid[2],a.ID)){
                        oks=1;
                        break;
                    }
                    fread(&a,sizeof(customer),1,fptr);
                }
                fclose(fptr);
                if(!oks){//id号码输入错误
                    return -1;
                }
                else{
                    if(vcounts<MaxSeqLen){
                        vcounts++;
                        vmaxnumber++;
                        return 1;
                    }
                    else return 0;
                }
            }

        }
    }
    return 2;
}
