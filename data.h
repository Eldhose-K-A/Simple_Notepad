struct node
{
	char data;
	struct node *top,*bottom,*left,*right;
};

struct node *first,*last,*cur,*next;
struct node *newnode,*delnode,*t1,*t2,*t3,*t4;
char NEWLINE;
struct node *substring,*replacestring,*copystart,*copyend;

void initializepointers();
void initialize(char);
void insertnode(char);
void insertnewline();
void printlinebyline();
void removenode();
void deletePreviousNode();
struct node *findlocation(struct node*);
void FindString();
void copynodes();
void ReplaceString();
