#include<stdio.h>
#include<stdlib.h>

void clrscr()
{
	printf("\e[0m");
	printf("\e[1J");
	printf("\e[H");
	printf("\e[0J");
}
void gotoxy(int x,int y)
{
	printf("\e[H");
	if(y>0)
	{
		printf("\e[%dC",y);
	}
	if(x>0)
	{
		printf("\e[%dB",x);
	}
}
char getch()
{
	char temp;
	system("stty -echo");
	system("stty cbreak");
	temp=getchar();
	system("stty echo");
	system("stty -cbreak");
	return(temp);
}
