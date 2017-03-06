#include<stdlib.h>
#include<stdio.h>
#include "bank.h"

int vip()
{
	    printf("-------update VIP customer`s informaiton-------\n\n");
	    printf("Please input V+,V- or V/ to add,delete or update a vip information:\n");
        FILE *fptr;
		int i;
		char c,d;
		customer a,temp[10000],b;
		while(scanf(" %c",&c)&&c!='E'){
			scanf("%c",&d);
			if((fptr=fopen("vip.dat","r+b"))==NULL){
	        	printf("File can not open.\n");
	         	return 0;
	        }
			if(d=='+'){
				printf("Please input the customer`s name,ID and deposit you want to add:\n");
				scanf("%s%s%d",&a.name,&a.ID,&a.account);
				fseek(fptr,0L,SEEK_END); 
				fwrite(&a,sizeof(customer),1,fptr);
				fclose(fptr);
				printf("-------writen successfully!------\n\n"); 
			}
			else if(d=='-'){
				printf("Please input the customer`s name you want to delete:\n");
				scanf("%s",&a.name);
				rewind(fptr); 
				fread(&b,sizeof(customer),1,fptr);
				i=0;
				while(!feof(fptr)){
					if(strcmp(b.name,a.name)){
						temp[i++]=b;
					}
					fread(&b,sizeof(customer),1,fptr);
				}
	        	fclose(fptr);
	        	if((fptr=fopen("vip.dat","w"))==NULL){
		        	printf("can`t open this file.");
	        	}
	        	else{
		         	fwrite(temp,sizeof(customer),i,fptr);
		        	fclose(fptr);
	        	}
	        	printf("------delete successfully!-------\n\n");
			}
			else if(d=='/'){
				printf("Please input the customer`s name you want to update:\n");
				scanf("%s",&a.name);
				printf("PLease input the new ID and new deposit:\n");
				scanf("%s%d",&a.ID,&a.account);
				rewind(fptr);
				fread(&b,sizeof(customer),1,fptr);
				i=0;
				while(!feof(fptr)){
					if(strcmp(b.name,a.name)){
						temp[i++]=b;
					}
					else{
						temp[i++]=a;
					}
					fread(&b,sizeof(customer),1,fptr);
				}
				fclose(fptr);
	        	if((fptr=fopen("vip.dat","w"))==NULL){
		        	printf("can`t open this file.");
	        	}
	        	else{
		         	fwrite(temp,sizeof(customer),i,fptr);
		        	fclose(fptr);
	        	}
	        	printf("-----update successfully!------\n\n");
			}
			else printf("-------illegal input!------\n\nPlease input again:\n");
		}
    printf("-------VIP data update finished.-------\n");
	return 1;
}
