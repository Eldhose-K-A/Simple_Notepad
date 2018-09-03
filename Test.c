#include<stdio.h>
#include<stdlib.h>
#include "SampleConio.h"
#include "MyHeader.h"
#include "data.h"
#include "file.h"
#include<string.h>

extern char filename[20];

int main(int argc,char *argv[])
{
 char i;
 int k;
 if(argc>2)
 {
	printf("\nPlease enter only one file name!.........\n");
	return(0);
 }
 else if(argc==2)
 {
  strcpy(filename,argv[1]);
  clrscr();
  initialize_Notepad_window();
  initializepointers();
  readfromFile(0);
  driver();
 }
 else
 {
  strcpy(filename,"");		
  clrscr();
  initialize_Notepad_window();
  initializepointers();
  driver();
 }
 clrscr();
 return(0);
}

