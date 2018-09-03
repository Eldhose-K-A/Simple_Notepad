#include<stdio.h>
#include<stdlib.h>
#include "SampleConio.h"
#include "MyHeader.h"
#include "data.h"
#include "file.h"
#include<string.h>

extern int mr,mc,x,y,workplace;
extern char menu[6][11];
//-------------------------------------------------------------------------------------
void printposition()
{
	printf("\e[s");
	gotoxy(6,mc-15);
	printf("\e[33m( l:%3d, c:%3d)\e[0m\e[u",x,y);
}
//-------------------------------------------------------------------------------------
void initialize_Notepad_window()
{
	int i,k;
	x=1; y=1; mc=80; mr=40;
	workplace=1;
	strcpy(menu[0],"   NEW   ");
	strcpy(menu[1],"  SAVE   ");
	strcpy(menu[2],"  OPEN   ");
	strcpy(menu[3],"  FIND   ");
	strcpy(menu[4]," REPLACE ");
	strcpy(menu[5],"  QUIT   ");

	gotoxy(0,0);
	for(i=1;i<=mc;++i) printf("\e[1;32m_\e[0m");
	gotoxy(2,mc/2-3); printf("\e[1;31mNOTEPAD\e[0m");
	gotoxy(4,8);
	for(i=0;i<6;++i)
	{
		printf("|");
		printf("\e[34m%s\e[0m",menu[i]);
	}
	printf("|");
	gotoxy(7,0); for(i=1;i<=mc;++i) printf("\e[1;32m_\e[0m");
	printposition();
	gotoxy(8,0);
}
//-------------------------------------------------------------------------------------
int detectchar(char v)
{
	int iv,tm1,tm2,tm3,tm4;
	iv=v;
	switch(iv)
	{
		case  10: 	return(1);
		case 127: 	return(5);
		case  27: 	tm1=getch();
				if(tm1==27) return(-1);
				tm2=getch();
				switch(tm1)
				{
					case 91: switch(tm2)
						 {
							case 65: return(8);
							case 66: return(2);
							case 67: return(6);
							case 68: return(4);
							case 51: tm3=getch();
								 if(tm3==126) return(3);
							default: return(-1);
						 }
					default: return(-1);
				}
		 default: 	return(0);
	}
}
//------------------------------------------------------------------------------------
void EnterKeyPress()
{
	insertnewline();
	printf("\n");
}
//-------------------------------------------------------------------------------------
void BackSpacePress()
{
	deletePreviousNode();
	clrscr();
	initialize_Notepad_window();
	printlinebyline();
}
//-------------------------------------------------------------------------------------
void DeleteKeyPress()
{
	;
}
//-------------------------------------------------------------------------------------
void UpKeyPress()
{
	;
}
//-------------------------------------------------------------------------------------
void DownKeyPress()
{
	;
}
//-------------------------------------------------------------------------------------
void LeftKeyPress()
{
	;
}
//-------------------------------------------------------------------------------------
void RightKeyPress()
{
	;
}
//-------------------------------------------------------------------------------------
void CharacterKeyPress(char v)
{
	insertnode(v);
	printf("%c",v);
}
//-------------------------------------------------------------------------------------
void driver()
{
	char co;
	int co_i,mi=0;
	int i3;
	do{
		co=getch();
		co_i=detectchar(co);
		if(co_i==-1)
		{
			workplace*=-1;
			if(workplace==-1)
			{
				mi=0;
				printf("\e[s");
			}
		}
		if(workplace==1)
		{
			switch(co_i)
			{
		 		case  1: EnterKeyPress();
			  		 break;
		 		case  5: BackSpacePress();
			  		 break;
		 		case  3: //DeleteKeyPress();
		 	  		 break;
		 		case  8: //UpKeyPress();
		 	  		 break;
		 		case  2: //DownKeyPress();
		 	 		 break;
				case  4: //LeftKeyPress();
			  		 break;
		 		case  6: //RightKeyPress();
		 	  		 break;
		 		case  0: CharacterKeyPress(co);
		 	  		 break;
				case -1: printf("\e[s");
					 gotoxy(4,8);
					 for(i3=0;i3<6;++i3)
					 {
					 	printf("|");
					 	printf("\e[34m%s\e[0m",menu[i3]);
					 }
					 printf("|");
					 printf("\e[u");
					 break;
			       default : ;
			}
		}
		else if(workplace==-1)
		{
			switch(co_i)
			{
			         case 6: if(mi<5) mi=mi+1;
					 break;
				 case 4: if(mi>0) mi=mi-1;
					 break;
				 case 1: if(mi==5) co_i=-2;
					 else if(mi==3) FindString();
					 else if(mi==4) ReplaceString();
					 else if(mi==1) writetoFile();
					 else if(mi==2) readfromFile(1);
					 else if(mi==0) newfile();
					 mi=-1;
					 workplace=1;
					 break;
			       default : ;
			}
			printf("\e[s");
			gotoxy(4,8);
			for(i3=0;i3<6;++i3)
			{
				printf("|");
				if(i3==mi)
					printf("\e[34;47m%s\e[0m",menu[i3]);
				else
					printf("\e[34m%s\e[0m",menu[i3]);
			}
			printf("|");
			printf("\e[u");
		}
	}while(co_i!=-2);
}
