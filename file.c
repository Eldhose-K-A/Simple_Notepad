#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "data.h"
#include "SampleConio.h"
#include "MyHeader.h"

extern char filename[20];
extern struct node *first,*last,*cur,*next,*t1,*delnode;

void writetoFile()
{
	FILE *f1;
	if(strcmp(filename,"")==0)
	{
		gotoxy(6,1);
		printf("Enter the file name : ");
		scanf(" %s",filename);
	}
	f1=fopen(filename,"w");
	t1=first;
	while(t1!=NULL)
	{
		fprintf(f1,"%c",t1->data);
		t1=t1->right;
	}
	fclose(f1);
	t1=first;
	while(t1!=NULL)
	{
		delnode=t1;
		t1=t1->right;
		free(delnode);
	}
	strcpy(filename,"");
	initializepointers();
	clrscr();
	initialize_Notepad_window();
	printlinebyline();
}
void readfromFile(int v)
{
	FILE *f1;
	char ch;
	if(v==1)
	{
		gotoxy(6,1);
		printf("Enter the file name : ");
		scanf(" %s",filename);
	}
	t1=first;
	while(t1!=NULL)
	{
		delnode=t1;
		t1=t1->right;
		free(delnode);
	}
	initializepointers();
	clrscr();
	initialize_Notepad_window();
	f1=fopen(filename,"r");
	if(f1==NULL)
	{
		strcpy(filename,"");
		return;
	}
	while(!feof(f1))
	{
		ch=fgetc(f1);
		if(ch==EOF)
			break;
		else
			CharacterKeyPress(ch);
	}
	fclose(f1);
}
void newfile()
{
	t1=first;
	while(t1!=NULL)
	{
		delnode=t1;
		t1=t1->right;
		free(delnode);
	}
	strcpy(filename,"");
	initializepointers();
	clrscr();
	initialize_Notepad_window();
}
