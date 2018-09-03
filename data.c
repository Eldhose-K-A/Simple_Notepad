#include<stdio.h>
#include<stdlib.h>
#include "SampleConio.h"
#include "MyHeader.h"
#include "data.h"

extern int x,y;

extern struct node *first,*last,*cur,*next;
extern struct node *newnode,*delnode,*t1,*t2,*t3,*t4;
extern char NEWLINE;
extern struct node *substring,*replacestring,*copystart,*copyend;

void initializepointers()
{
	first=last=cur=next=NULL;
	delnode=newnode=t1=t2=t3=t4=NULL;
	NEWLINE='\n';
	replacestring=copystart=copyend=substring=NULL;
}
void initialize(char v)
{
	if(newnode!=NULL)
	{
		newnode->data=v;
		newnode->top=newnode->bottom=newnode->left=newnode->right=NULL;
	}
}
void insertnode(char v)
{
	newnode=NULL;
	newnode=(struct node*)malloc(sizeof(struct node));
	if(newnode!=NULL)
	{
		initialize(v);
		if(cur==NULL)
		{
			first=last=cur=newnode;
		}
		else if(cur->data==NEWLINE)
		{
			t1=cur->right;
			cur->right=newnode;
			newnode->left=cur;
			newnode->right=t1;
			if(t1!=NULL)
				t1->left=newnode;
			cur=newnode;
			
			t2=cur->left;
			while(t2->top==NULL)
			{
				if(t2->left==NULL)
					break;
				t2=t2->left;
			}
			cur->top=t2;
			t2->bottom=cur;
		}
		else
		{
			
			t1=cur->right;
			cur->right=newnode;
			newnode->left=cur;
			newnode->right=t1;
			if(t1!=NULL)
				t1->left=newnode;
			cur=newnode;
		}
	}
	t1=t2=newnode=NULL;
	y=y+1;
	printposition();
}
void insertnewline()
{
	insertnode(NEWLINE);
	x=x+1;
	y=1;
	printposition();
}
void removenode()
{
	int CASE;
	if(delnode!=NULL)
	{
		t1=delnode->top;
		t2=delnode->bottom;
		t3=delnode->left;
		t4=delnode->right;
		if(t3==NULL)
			CASE=1;
		else if(t1!=NULL)
			CASE=2;
		else if(delnode->data==NEWLINE)
			CASE=3;
		else
			CASE=4;
		switch(CASE)
		{
			case 1:  first=first->right;
				 if(first!=NULL)
				 {
				 	first->bottom=t2;
				 	if(t2!=NULL)
						t2->top=first;
				 	first->left=NULL;
				 }
				 free(delnode);
				 break;
			case 2:  t3->right=t4;
				 t1->bottom=t4;
				 if(t4!=NULL)
				 {
					t4->left=t3;
					t4->top=t1;
					t4->bottom=t2;
				 }
				 if(t2!=NULL)
				 	t2->top=t4;
				 free(delnode);
				 break;
			case 3:  if(t4!=NULL)
				 {
				 	t1=t4->top;
				 	t2=t4->bottom;
				 	t3->right=t4;
				 	t4->left=t3;
				 	t4->bottom=t4->top=NULL;
				 	t1->bottom=t2;
				 	if(t2!=NULL)
						t2->top=t1;
				 }
				 else
				 {
					t3->right=NULL;
				 }
				 free(delnode);
				 break;
		       default:  t3->right=t4;
				 if(t4!=NULL)
					t4->left=t3;
				 free(delnode);
		}
	}
	delnode=t1=t2=t3=t4=NULL;
}
void deletePreviousNode()
{
	delnode=cur;
	if(cur!=NULL)
	{
		cur=cur->left;
		removenode();
		if(cur!=NULL)
			next=cur->right;
	}
	delnode=NULL;
}
struct node *findlocation(struct node *mainstring)
{
	struct node *tpms;
	t4=substring;
	while((t4!=NULL)&&(mainstring!=NULL))
	{
		if(t4->data!=mainstring->data)
		{
			return(NULL);
		}
		t4=t4->right;
		tpms=mainstring;
		mainstring=mainstring->right;
	}
	if(t4==NULL)
		return(tpms);
	else
	{
		t4=NULL;
		return(NULL);
	}
}
void FindString()
{
	char i1;
	int k1,flag;
	flag=1;
	t1=substring;
	substring=NULL;
	while(t1!=NULL)
	{
		delnode=t1;
		t1=t1->right;
		free(delnode);
	}
	printf("\e[s");
	gotoxy(6,1);
	printf("Enter the String to Search : ");
	do{
		i1=getch();
		if(i1=='\e')
			break;
		k1=detectchar(i1);
		switch(k1)
		{
			case 0: newnode=(struct node*)malloc(sizeof(struct node));
				initialize(i1);
				if(substring==NULL)
					t1=substring=newnode;
				else
				{
					t1->right=newnode;
					newnode->left=t1;
					t1=newnode;
				}
				newnode=NULL;
				printf("%c",i1);
				break;
			case 5: delnode=t1;
				if(t1!=NULL)
				{
					t1=t1->left;
					if(t1!=NULL)
						t1->right=NULL;
					free(delnode);
					delnode=NULL;
					printf("\e[D \e[D");
				}
				else
					substring=NULL;
				break;
			case 1: printf("\n");
				flag=0;
				break;
		       case -2: flag=3;
				break;
		       default: break;
		}
	}while(flag==1);
	printf("*\e[u");
	if(flag==0&&substring!=NULL)
	{
		t1=first;
		clrscr();
		initialize_Notepad_window();
		while(t1!=NULL)
		{
			t2=t1;
			while(t2!=NULL)
			{
				if(t2->data==NEWLINE)
					break;
				t3=findlocation(t2);
				if(t3!=NULL)
				{
					t2=t3;
					printf("\e[31m");
					for(t3=substring;t3!=NULL;t3=t3->right)
						printf("%c",t3->data);
					printf("\e[0m");
				}
				else
					printf("%c",t2->data);
				t2=t2->right;
			}
			if(t2!=NULL)
				printf("\n");
			t1=t1->bottom;
		}
	}
	else
	{
		clrscr();
		initialize_Notepad_window();
		printlinebyline();
	}
	newnode=delnode=t1=t2=t3=t4=NULL;
}
void copynodes()
{
	copystart=copyend=NULL;
	delnode=replacestring;
	while(delnode!=NULL)
	{
		newnode=(struct node*)malloc(sizeof(struct node));
		initialize(delnode->data);
		if(copystart==NULL)
			copystart=copyend=newnode;
		else
		{
			copyend->right=newnode;
			newnode->left=copyend;
			copyend=newnode;
		}
		delnode=delnode->right;
	}
	newnode=delnode=NULL;
}
void ReplaceString()
{
	char i1;
	int k1,flag;
	struct node *t5,*t6,*t7;
	flag=1;
	t1=substring;
	substring=NULL;
	while(t1!=NULL)
	{
		delnode=t1;
		t1=t1->right;
		free(delnode);
	}
	t1=replacestring;
	replacestring=NULL;
	while(t1!=NULL)
	{
		delnode=t1;
		t1=t1->right;
		free(delnode);
	}
	printf("\e[s");
	gotoxy(5,1);
	printf("Enter the String to be Replaced : ");
	do{
		i1=getch();
		if(i1=='\e')
			break;
		k1=detectchar(i1);
		switch(k1)
		{
			case 0: newnode=(struct node*)malloc(sizeof(struct node));
				initialize(i1);
				if(substring==NULL)
					t1=substring=newnode;
				else
				{
					t1->right=newnode;
					newnode->left=t1;
					t1=newnode;
				}
				newnode=NULL;
				printf("%c",i1);
				break;
			case 5: delnode=t1;
				if(t1!=NULL)
				{
					t1=t1->left;
					if(t1!=NULL)
						t1->right=NULL;
					free(delnode);
					delnode=NULL;
					printf("\e[D \e[D");
				}
				else
					substring=NULL;
				break;
			case 1: //printf("\n");
				flag=0;
				break;
		       case -2: flag=3;
				break;
		       default: break;
		}
	}while(flag==1);
	printf("\e[u");
	if(flag==0)
	{
		flag=1;
		printf("\e[s");
		gotoxy(6,1);
		printf("Enter the String to be replace with : ");
		do{
			i1=getch();
			if(i1=='\e')
				break;
			k1=detectchar(i1);
			switch(k1)
			{
				case 0: newnode=(struct node*)malloc(sizeof(struct node));
					initialize(i1);
					if(replacestring==NULL)
						t1=replacestring=newnode;
					else
					{
						t1->right=newnode;
						newnode->left=t1;
						t1=newnode;
					}
					newnode=NULL;
					printf("%c",i1);
					break;
				case 5: delnode=t1;
					if(t1!=NULL)
					{
						t1=t1->left;
						if(t1!=NULL)
							t1->right=NULL;
						free(delnode);
						delnode=NULL;
						printf("\e[D \e[D");
					}
					else
						replacestring=NULL;
					break;
				case 1: //printf("\n");
					flag=0;
					break;
		       		case -2: flag=3;
					break;
		       		default: break;
			}
		}while(flag==1);
		printf("\e[u");
	}
	if(flag==0&&substring!=NULL)
	{
		clrscr();
		x=1; y=1;
		initialize_Notepad_window();
		t1=first;
		while(t1!=NULL)
		{
			t2=t1;
			y=1;
			while(t2!=NULL)
			{
				if(t2->data==NEWLINE)
				{
					x=x+1;
					break;
				}
				t3=findlocation(t2);
				if(t3!=NULL&&replacestring!=NULL)
				{
					t5=t3->right;
					if(t5!=NULL)
						t5->left=NULL;
					t3->right=NULL;
					t6=t2->left;
					t2->left=NULL;
					if(t6!=NULL)
						t6->right=NULL;
					copynodes();
					for(t7=copystart;t7!=NULL;t7=t7->right) { printf("\e[31m%c\e[0m",t7->data); y=y+1; }
					copystart->left=t6;
					copystart->top=t2->top;
					if(t2->top!=NULL)
						(t2->top)->bottom=copystart;
					copystart->bottom=t2->bottom;
					if(t2->bottom!=NULL)
						(t2->bottom)->top=copystart;
					if(t6!=NULL)
						t6->right=copystart;
					else
						first=copystart;
					copyend->right=t5;
					if(t5!=NULL)
						t5->left=copyend;
					for(t7=t2;t7!=NULL;)
					{
						delnode=t7;
						t7=t7->right;
						free(delnode);
					}
					t2=copyend;
					copystart=copyend=NULL;
				}
				else if(t3!=NULL)
				{
					t5=t2->left;
					t2->left=NULL;
					t6=t3->right;
					t3->right=NULL;

					if(t5!=NULL)
						t5->right=t6;
					else
						first=t6;
					if(t6!=NULL)
					{
						t6->left=t5;
						t6->top=t2->top;
						t6->bottom=t2->bottom;
						if(t2->top!=NULL)
							(t2->top)->bottom=t6;
						if(t2->bottom!=NULL)
							(t2->bottom)->top=t6;
					}
					for(t7=t2;t7!=NULL;)
					{
						delnode=t7;
						t7=t7->right;
						free(delnode);
					}
					t2=t6;
					if(t2!=NULL)
					{
						printf("%c",t2->data);
						y=y+1;
					}
				}
				else
				{
					if(t2->data!=NEWLINE)
					{
						printf("%c",t2->data);
						y=y+1;
					}
					else
					{
						printf("\n");
						x=x+1;
					}
				}
				if(t2!=NULL)
					t2=t2->right;
			}
			if(t2!=NULL)
			{
				printf("\n");
				x=x+1;
			}
			if(t1!=NULL)
				t1=t1->bottom;
		}
	}
	else
	{
		clrscr();
		initialize_Notepad_window();
		printlinebyline();
	}
	newnode=t1=t2=t3=t4=delnode=NULL;
}
void printlinebyline()
{
	x=1;
	y=1;
	t1=first;
	while(t1!=NULL)
	{
		x++;
		t2=t1;
		y=1;
		while(t2!=NULL)
		{
			printf("%c",t2->data);
			y=y+1;
			if(t2->data==NEWLINE)
			{
				x=x+1;
				break;
			}
			t2=t2->right;
		}
		t1=t1->bottom;
	}
	printposition();
}
