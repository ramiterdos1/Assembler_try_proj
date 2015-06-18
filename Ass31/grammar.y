%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 701
#define YYSTYPE char*

struct symbol
{
 char *name;
 int type; //type is 0 for int,1 for char and 2 for float
};
 
  struct node
  {
    char *identifierName;
    int type; 
    struct node * next;
  };
  
 
  struct node * hashtable[SIZE];
   
  int GetHashCode(char *str);
  struct node * InsertIntoHashTable(char *, int);
  struct node * InsertIntoSLL(struct node *, char *, int);
  void PrintTable();    
  struct node * GetNode(char *,int);
  struct symbol* IsSymbolPresent(char *);
  struct node *ptr;


int yydebug=1;
int presIden=-1;


void yyerror(const char * str)
{
  fprintf(stderr,"error: %s \n",str);
}

int yywrap()
{
  return 1;
}

main()
{
  yyparse();
  PrintTable();
}

//get the hash 
int GetHashCode(char * str)
{
  int i=0;
  int val=0;
  while(str[i]!='\0')
   {
    val=(val+(str[i]-'\0'))%SIZE;
    i++;
   }
  return val;
}

//get a linked list node
struct node * GetNode(char *str, int type)
 {
  struct node *newNode;
  newNode=(struct node *)malloc(sizeof(struct node));
  newNode->identifierName=(char *)malloc((sizeof(char))*(strlen(str)+5));	
  strcpy(newNode->identifierName,str);
  newNode->type=type;
  newNode->next=NULL;
  return newNode;
 }

//insert value into singly linked list
struct node * InsertIntoSLL(struct node * start, char * str, int type)
{
 
 if(start==NULL)
  {
    start=GetNode(str,type);
    return start;
  }
 else
  {
    struct node *tmp;
    tmp=start;
    while(tmp->next!=NULL)
    {
      tmp=tmp->next;
    }
    tmp->next=GetNode(str,type);
    return tmp->next;
  } 
 
}

//insert value in hash table
struct node * InsertIntoHashTable(char * str,int type)
{
   int hash=GetHashCode(str);
   if(IsSymbolPresent(str)==NULL)
    {
   	if(hashtable[hash]==NULL)
    	   {
      		hashtable[hash]=InsertIntoSLL(hashtable[hash],str,type);
      		return hashtable[hash];
    	   }
   	else
    	   {
      		return InsertIntoSLL(hashtable[hash],str,type);
           }
   }
  else
   {
       return NULL;
   } 	
}

void PrintSLLNodes(struct node * start)
{
  struct node * tmp;
  tmp=start;
  while(tmp!=NULL)
   {
     printf("%s  ",tmp->identifierName);
     if(tmp->type==0) printf("INT");
     if(tmp->type==1) printf("CHAR");
     if(tmp->type==2) printf("FLOAT");
     tmp=tmp->next;
   }
}

void PrintTable()
{
  int i;
  printf("\nThe hash table is :\n");
  for(i=0;i<SIZE;i++)
   {
      if(hashtable[i]!=NULL)
        {
          PrintSLLNodes(hashtable[i]);
          printf("\n");
        }
   }
}

struct symbol* IsSymbolPresent(char *str)
 {
   int hash=GetHashCode(str);
   struct node *tmp;
   tmp=hashtable[hash];
   struct symbol * newSymbol;
   
   while(tmp!=NULL)
    {
      //identifier is found
      if(strcmp(tmp->identifierName,str)==0)
        {
           newSymbol=(struct symbol *)malloc(sizeof(struct symbol));   
           
           newSymbol->name=(char *)malloc((strlen(str)+1)*sizeof(char));
           strcpy(newSymbol->name,str);
           
           newSymbol->type=tmp->type; 
           
           return newSymbol;
        }
       tmp=tmp->next;
    }
   //identifier is not found
  return NULL;
 }

char * GetType(int type)
{
  if(type==0) return "INT";
  if(type==1) return "CHAR";
  if(type==2) return "FLOAT";
}

void InsertSymbol(char *symName)
{
 struct symbol *sym;
 sym=IsSymbolPresent(symName);
 if(sym==NULL)
   {
     InsertIntoHashTable(symName,presIden);
   } 
 else
   {
     printf("Redeclaration error!\nSymbol %s is declared earlier with type %s",symName,GetType(sym->type));
     yyerror("Symbol redeclared");	
   }
}

void SearchSymbol(char * symName)
{
   struct symbol *sym; 
   sym=IsSymbolPresent(symName); 
   if(sym==NULL)
     {
	printf("Symbol: %s is not declared",symName);
        yyerror("Symbol not declared"); 
     }
}
/*End of hash-table operations*/
%}

%token TOKNAME TOKINT TOKFLOAT TOKCHAR SEMICOLON COMMA EQUAL PLUS MINUS MULT MOD DIV NUMBER AND OR NOT GREATERTHAN LESSTHAN LESSTHANEQUAL GREATERTHANEQUAL NOTEQUAL OPENPAREN CLOSEPAREN OPENBRACE CLOSEBRACE TOKWHILE TOKFOR TOKIF TOKELSE COMPEQUAL TOKVOID INC DEC TOKRETURN

%%
lines:/*empty*/
|lines decl
|lines def
|lines whl
|lines ifelse
|lines forloop
|lines func
;

decl:iden var SEMICOLON
| iden var EQUAL exp SEMICOLON		
;

funcdecl:
|iden TOKNAME		{InsertSymbol($2);}
|funcdecl COMMA iden TOKNAME  {InsertSymbol($4);}
;	

var:TOKNAME                     {InsertSymbol($1);} 
|var COMMA TOKNAME	        {InsertSymbol($3);}
;

iden: TOKINT	                {presIden=0;}
|TOKFLOAT			{presIden=2;}
|TOKCHAR	                {presIden=1;}
;

def:TOKNAME EQUAL exp SEMICOLON {/*printf("Definition found");*/SearchSymbol($1);} 
|TOKNAME optr EQUAL exp SEMICOLON{SearchSymbol($1);}
;

exp:TOKNAME {SearchSymbol($1);}
|NUMBER
|exp optr NUMBER		
|exp optr TOKNAME {SearchSymbol($3);}
|OPENPAREN exp CLOSEPAREN
|TOKNAME INC {SearchSymbol($1);}
|INC TOKNAME {SearchSymbol($2);}
|TOKNAME DEC {SearchSymbol($1);}
|DEC TOKNAME {SearchSymbol($2);}
;

optr:PLUS
|MINUS
|MULT
|MOD
|DIV
;

cond: NOT cond 
| OPENPAREN cond CLOSEPAREN
| TOKNAME GREATERTHAN TOKNAME
| TOKNAME LESSTHAN TOKNAME
| TOKNAME GREATERTHAN NUMBER
| NUMBER GREATERTHAN TOKNAME
| NUMBER GREATERTHAN NUMBER
| TOKNAME LESSTHAN NUMBER
| NUMBER LESSTHAN TOKNAME
| NUMBER LESSTHAN NUMBER
| TOKNAME GREATERTHANEQUAL TOKNAME 
| TOKNAME GREATERTHANEQUAL NUMBER
| NUMBER GREATERTHANEQUAL TOKNAME
| NUMBER GREATERTHANEQUAL NUMBER
| TOKNAME LESSTHANEQUAL TOKNAME
| TOKNAME LESSTHANEQUAL NUMBER
| NUMBER LESSTHANEQUAL TOKNAME
| NUMBER LESSTHANEQUAL NUMBER
| TOKNAME COMPEQUAL TOKNAME
| TOKNAME COMPEQUAL NUMBER
| NUMBER COMPEQUAL TOKNAME
| NUMBER COMPEQUAL NUMBER
| TOKNAME NOTEQUAL TOKNAME
| TOKNAME NOTEQUAL NUMBER
| NUMBER NOTEQUAL TOKNAME
| NUMBER NOTEQUAL NUMBER
| TOKNAME AND TOKNAME
| TOKNAME OR TOKNAME
| NOT TOKNAME
;

whl:TOKWHILE OPENPAREN cond CLOSEPAREN OPENBRACE lines CLOSEBRACE {printf("\nWhile loop found!");}
;

ifelse:TOKIF OPENPAREN cond CLOSEPAREN OPENBRACE lines CLOSEBRACE {printf("\nIf found!");}
|TOKIF OPENPAREN cond CLOSEPAREN OPENBRACE lines CLOSEBRACE TOKELSE OPENBRACE lines CLOSEBRACE {printf("\nIf-else found!");}
;

forloop:TOKFOR OPENPAREN def cond SEMICOLON TOKNAME EQUAL exp CLOSEPAREN OPENBRACE lines CLOSEBRACE {printf("\nfor loop found!");}
|TOKFOR OPENPAREN decl cond SEMICOLON TOKNAME EQUAL exp CLOSEPAREN OPENBRACE lines CLOSEBRACE {printf("\nfor loop found!");}
;

func:iden TOKNAME OPENPAREN funcdecl CLOSEPAREN OPENBRACE lines TOKRETURN exp SEMICOLON CLOSEBRACE
|TOKVOID TOKNAME OPENPAREN funcdecl CLOSEPAREN OPENBRACE lines CLOSEBRACE
;


%%

