//
//  SymbTGen.cpp
//  
//  always have the : after a separation
//  Created by Ramit on 04/02/13.
//
//
#include <list>
#include <iterator>
#include <string>
#include "OpcodeTable.h"
using namespace std;
int tokenize_pass(FILE *f);
int replace(FILE *,FILE *);
int chk4Macro(String s);
int mcro=0;
list<Macr> m[1000];

/*string string::operator+(string s)
{
    string temp;
    strcpy(temp.str,str);
    strcat(temp.str,s.str);
    return(temp);
}*/
int chk4Macro(String s)
{
    int flg=-1;
    list<Macr>:: iterator it;
    for (int i=0; i<mcro; i++)
    {   it=m[i].begin();//printf("%d..%s... %s..\n",i,s,it->mc_name);
        if(strcmp(s,it->mc_name)==0)
        {
            flg=i; //printf("hey hey..%d.. %s... %s\n",i,s,it->mc_name);break;
        }
    }
    //printf("Chk4Macro.. %d..%s\n",flg,s);
    return flg;
}
int tokenize_pass(FILE *f)
{
    
    size_t buf_limit = 65500;
    char *sentence = (char *) malloc(buf_limit);
    char *tok_1,*tok_2=(char *) malloc(buf_limit);
    int i=0;
    String tokensInLine[MaxWrds];
    while(getline(&sentence,&buf_limit,f)!=EOF)
    {
        tok_2 = strtok(sentence,";");
        int j;
        tok_1 = strtok(tok_2," \t\n");
        for(i=0;tok_1;i++)
        {
             tokensInLine[i]=NULL;
            tokensInLine[i]=(char *)malloc(strlen(tok_1)*sizeof(char));
            //copying
            //printf("%s...",tok_1);
            for (j=0; j<strlen(tok_1); j++)
            {
                tokensInLine[i][j]=tok_1[j];
                //if(i==0)printf("%d..%c..%c\n",j,tokensInLine[i][j],tok_1[j]);
            }tokensInLine[i][j]=0;
            
            tok_1 = strtok(NULL," \t\n");
        }
        
            if(i>1 && strcmp(tokensInLine[1],"MACRO")==0)
            {
                Macr  *m1=(Macr *)malloc(sizeof(Macr));
                j=-1;
                m1->mc_name=(char *)malloc(sizeof(char)*strlen(tokensInLine[0]));
                while((++j)<strlen(tokensInLine[0]))m1->mc_name[j]=tokensInLine[0][j];
                m1->i=-1;
                //printf("Found A Macro... %s..%s\n",m1->mc_name,tokensInLine[0]);
                m[mcro].push_back(*m1);
                while(getline(&sentence,&buf_limit,f)!=EOF)
                {
                   // printf("Inside WHile\n%s\n",sentence);
                    
                    tok_2 = strtok(sentence,";");
                    int j;
                    tok_1 = strtok(tok_2," \t\n");
                    for(i=0;tok_1;i++)
                    {
                        tokensInLine[i]=(char *)malloc(strlen(tok_1)*sizeof(char));
                        //copying
                        for (j=0; j<strlen(tok_1); j++)
                        {
                            tokensInLine[i][j]=tok_1[j];
                        }
                        tok_1 = strtok(NULL," \t\n");
                    }
                   // for(int j=0;j<i;j++)printf("%s-",tokensInLine[j]);
                   // printf("\n");
                    
                    if(strcmp(tokensInLine[0],"ENDM\n")==0||strcmp(tokensInLine[0],"ENDM")==0)
                    {mcro++;break;}
                    else
                    {
                        j=0;//adding the macro at the end
                        while(j<i)
                        {
                            Macr *m1=(Macr *)malloc(sizeof(Macr));
                            int k=-1;
                            
                            m1->mc_name=(char *)malloc(sizeof(char)*strlen(tokensInLine[j]));
                            while((++k)<strlen(tokensInLine[j]))m1->mc_name[k]=tokensInLine[j][k];
                            if(tokensInLine[1][0]==':' && j==0)m1->i=0;// macros have to have a space between labels
                            else m1->i=-1;
                           // printf("Found A Macro... %s..%d\n",m1->mc_name,m1->i);
                            
                            m[mcro].push_back(*m1);
                            j++;
                        }
                        Macr *m1=(Macr *)malloc(sizeof(Macr));
                        m1->mc_name=(char *)malloc(sizeof(char));
                        m1->mc_name=(char *)"\n";
                        m1->i=-1;
                        m[mcro].push_back(*m1);
                    }
                }
            
           }
        
    }
    fclose(f);
    return mcro;
}
int replace(FILE *f,FILE *f1)
{
    size_t buf_limit = 65500;
    char *sentence = (char *) malloc(buf_limit);
    char *tok_1,*tok_2;
    int i=0;
    String tokensInLine[MaxWrds];
    while(getline(&sentence,&buf_limit,f)!=EOF)
    {
        tok_2 = strtok(sentence,";");
        int j;
        tok_1 = strtok(tok_2," \t\n");
        for(i=0;tok_1;i++)
        {
            tokensInLine[i]=(char *)malloc(strlen(tok_1)*sizeof(char));
            //copying
            for (j=0; j<strlen(tok_1); j++)
            {
                tokensInLine[i][j]=tok_1[j];
            }
            
            tok_1 = strtok(NULL," \n");
        }
        
       // printf("No of words..%d...\n",i);
        //for(int j=0;j<i;j++)printf("%s...",tokensInLine[j]);
        //printf("\n");
        if(i>1 && strcmp(tokensInLine[1],"MACRO")!=0)
        {
            j=0;
            while (j<i)
            {
                fprintf(f1,"%s ",tokensInLine[j++]);
            }
            fprintf(f1,"\n");
        }
        else if(i>1 && strcmp(tokensInLine[1],"MACRO")==0)
        {
           while(getline(&sentence,&buf_limit,f)!=EOF)
  		  {
        		tok_2 = strtok(sentence,";");
        	        tok_1 = strtok(tok_2," \t\n");
       		        /*for(i=0;tok_1;i++)
       		          {
          			  tokensInLine[i]=(char *)malloc(strlen(tok_1)*sizeof(char));
          			  //copying
          			  for (j=0; j<strlen(tok_1); j++)
         				   {
                				tokensInLine[i][j]=tok_1[j];
           				   }
            
            			  tok_1 = strtok(NULL," \n");
        		}
        		if(i==1 && strcmp(tokensInLine[0],"ENDM"))
        			break;
        		*/
        		if(!strcmp(tok_1,"ENDM"))
        			break;		
        	    }
        }
        else if(i==1)
        {
            int flg=chk4Macro(tokensInLine[0]);//printf("Hello.. one word..%s.. %d\n",tokensInLine[0],flg);
            
            if(flg>=0)
            {
                //printf("Hello.. one word..%s\n",tokensInLine[0]);
                list<Macr> :: iterator it;
                it=m[flg].begin();it++;//printf("***********\n");
                for(;it!=m[flg].end();it++)
                    {
                        //printf("%s...",it->mc_name);
                       if(it->i==-1)fprintf(f1,"%s ",it->mc_name);
                       else {
                               fprintf(f1,"%s%%%d ",it->mc_name,it->i);
                               it->i++;
                            }
                    }
                //printf("***********\n");
            }
            else fprintf(f1,"%s\n",tokensInLine[0]);
        }
        
    } 
}
int main(int argc, char *argv[])
{
    
    if(argc==2)
    {
        //printf("HIIII\n");
        FILE *f=fopen(argv[1],"r");
        fclose(f);f=fopen(argv[1],"r");
        int i=tokenize_pass(f);
        printf("No. of macros %d.\n",i);
        f=fopen(argv[1],"r");
        FILE *f1=fopen("PASS1","w");
        /*printf("THE MACRO STORED ...\n");
        list<Macr> :: iterator it;
        for(it=m[0].begin();it!=m[0].end();it++)
              {
                 printf("%s...%d\n",it->mc_name,it->i);
              }
        printf("THE MACRO LOOOO ...\n");*/
   /* string s="ramit",s1=" das";
        //strcpy(s,s1);
    s=s+s1;
    printf("%s\n",s.c_str());*/
        replace(f,f1);
        fclose(f);
        fclose(f1);
        //system("cat PASS1");
    }
}
