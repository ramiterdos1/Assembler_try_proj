//
//  OpcodeTable.cpp
//  
//
//  Created by Ramit on 11/01/13.
//
//
#include <string>
#include "OpcodeTable.h"
using namespace std;
int tokenize_pass(FILE *);
int LoadMOT(FILE *);
int hash1(String);
int hash2(String);
int hashSymbols(String);
void SymHashEntry(int,String,FILE *);
void hashCode();
//void generateCode();
int checkMacro(String s);
int MacroAction(int macro,String s[],int len);
int generateCode(FILE *);
int chkOpcde(String s);
int chkReg(String s);
void *chkLabel(String s);
int getstartaddress(FILE *);
int OperateOnOpcode(String s[],String add,int indx,FILE *f);
int hash1(String s )
{
    int i=0,cal=0,len=strlen(s);
    while(i<len|| s[i]!=0){
        cal+=(i+1)*((s[i]-'A'+1)*(s[i]-'A'+1));i++;
    }
    return cal%prime1;
}
int hash2(String s )
{
    int i=0,cal=0,len=strlen(s);
    while(i<len || s[i]!=0)
    {
        cal+=(s[i]-0)/(s[i]-'A'+1);
        i++;
    }cal*=(i+211);
    return cal%prime2;
    //return cal;
}
void convert2hex()
{
    int r=0,i=3;
    //printf("%d..y.y.y.\n",a.adrs);
    
    while(i>=0)
    {
        r=a.adrs%16;
        //printf("blaa blaa %d\n",r);
        a.adrs/=16;
        a.hex[i--]=(r<10)?'0'+r:'A'+r-10;
    }
    a.hex[4]=0;
    //printf("\n%s\n",a.hex);
}

void setAddress()
{
   // printf("%d..i.i.i.\n",codelc);
    a.adrs=codelc;
    convert2hex();
    //printf("%s hullo .\n",a.hex);
    
}
int hashSymbols(String s)
{
    int i=1,flag=0;//linear probe
    void *p;
    int hashval=(hash1(s)+i*hash2(s))%449;
    while (hashsymb[hashval]!=NULL)
    {
        i++;
        p=hashsymb[hashval];
        if(strcmp(((Symbol)p)->sym_name,s)==0)
        {
            //same symbol
            printf("ERR:SAME SYMBOL NAME USED!!\n");hashval=-1;
            break;
        }
    hashval=(hash1(s)+i*hash2(s))%449;
    }
    
    return hashval;
}
void SymHashEntry(int indx,String s,FILE *f)
{
    SymbolTable[symtbsize]=(Symbol)malloc(sizeof(sym )+sizeof(char)*strlen(s));
    int j=0;
    while(j<5)
    {
        SymbolTable[symtbsize]->address[j]=a.hex[j];
        j++;
    }
    //printf("CHECKADDRESS %s\n",a.hex);//check
    j=-1;
    
    while((++j)<strlen(s))
        SymbolTable[symtbsize]->sym_name[j]=s[j];
    fprintf(f,"%15s %15s\n",SymbolTable[symtbsize]->address,SymbolTable[symtbsize]->sym_name);
   // printf("SYMHASHENTRY at %d of %s stored as %s!\n",indx,s,SymbolTable[symtbsize]->sym_name);
    hashsymb[indx]=SymbolTable[symtbsize++];
}
void hashCode()
{
    for(int i=0;i<motsize;i++)
    {
        int hashval=(hash1(MOT[i]->code)+hash2(MOT[i]->code)-10)%211,corr=0;
        //int hashval=hash2(MOT[i]->code)%211;
        if(hashcodes[hashval]==-1)hashcodes[hashval]=i;
        else if(corr=strcmp(MOT[hashcodes[hashval]]->code,MOT[i]->code))//collision resolution
               {
                   //printf("Collision ->%s...%s\n",MOT[hashcodes[hashval]]->code,MOT[i]->code);
                   corr=(corr>0)?-1:1;
                   if(hashcodes[hashval+corr]==-1)hashcodes[hashval+corr]=i;
                   
               }
    }
    /*int count=0;
    for(int i=0;i<211;i++)
        if(hashcodes[i]!=-1)
        {
            printf("hashcodes[%d]=%d..MOT[%d]=%s\n",i,hashcodes[i],hashcodes[i],MOT[hashcodes[i]]->code);
            count++;
        }
    printf("Distinct->%d\n",count)=63;*/
}
int getstartaddress(FILE *f)
{
    size_t buf_limit = BUFLMT;
    char *sentence = (char *) malloc(buf_limit);
    char *tok_1;
    int s_addr=0;
    getline(&sentence,&buf_limit,f);
    tok_1 = strtok(sentence," \n;");
    if(strcmp(tok_1,"ORG")==0)
        {
            tok_1 = strtok(NULL," \n;");
            int p=1;
            for(int i=3;i>=0;i--)
               {
                   s_addr+=((tok_1[i]>='0'&& tok_1[i]<='9')?(tok_1[i]-'0'):(tok_1[i]-'A'+10))*p;
                   p*=16;
               }
        }
    return s_addr;
}
int main(int argc, char *argv[])
{
if(argc<2)
{
    printf("WRONG FORMAT OF INPUT\nProper format : ./machineCodeGen AssemblyCode(s) (Relocation_Position)\n");
}
else{
    printf("%s\n",argv[1]);
    FILE *f1=fopen(Mot,"r");
    string s="cat ",s2=" ",s3="> Input";
    /*for(int i=1;i<argc;i++)
        s+=argv[i]+s2;
    s+=s3;
    system(s.c_str());*/
    FILE *f;//=fopen("Input","r");
    
    if (f1==NULL) {
        printf("MACHINE OPCODE TABLE CONTAINING FILE CANNOT BE OPENED!\n");
    }
    else
    {
        if(LoadMOT(f1)!=1)printf("ERROR AT LOADING THE MACHINE OPCODE TABLE!\n");
        if(argc>2)
            {
                /*int i=atoi(argv[argc-1]);
                if(i!=0)
                    {
                        printf("RELOCATING THE CODE TO  LOCATION %4X\n",i);
                        int n=0;
                        for(int i=1;i<5;i++)
                           {
                              int n=i%10;
                        codelc=i;
                        setAddress();
                    }else printf("NO RELOCATION");*/
                codelc=0;//printf("j\n");
                if(strlen(argv[argc-1])==4)
                {//printf("jj\n");
                        int p=1;
                    for(int i=3;i>=0;i--)
                        {
                        if(!((argv[argc-1][i]>='0'&& argv[argc-1][i]<='9')||(argv[argc-1][i]>='A'&& argv[argc-1][i]<='F')))
                            {
                                codelc=0;break;
                            }
                        else
                            {
                                //printf("%d...",p);
                            codelc+=((argv[argc-1][i]>='0'&& argv[argc-1][i]<='9')?(argv[argc-1][i]-'0'):(argv[argc-1][i]-'A'+10))*p;
                             p*=16;
                                //printf("%d...\n",codelc);
                            }
                        }
                    if(!codelc){
                                 printf("NO RELOCATION\n");
                                 for(int i=1;i<argc;i++)
                                      s+=argv[i]+s2;
                                 s+=s3;
                                 system(s.c_str());
                                //checking for macro
                                system("./Macroman Input");
                               }
                    else {
                        for(int i=1;i<argc-1;i++)
                            s+=argv[i]+s2;
                        s+=s3;
                        system(s.c_str());
                        f=fopen("Input","r");
                        printf("Yes RELOCATION.. at..%4X\n",codelc);//setAddress();
                        fclose(f);
                        //checking for macro
                        system("./Macroman Input");
                        f=fopen("PASS1","r");
                        int startaddress=getstartaddress(f);
                        reloc=codelc-startaddress;
                        printf("reloc=%4X",reloc,startaddress);
                        fclose(f);
                        
                          }
                    }
            
            }
         else printf("NO RELOCATION");
        //opening the PASS1 for machine code Generation
        
        f=fopen("PASS1","r");
        //hashing the symbol table
        for (int i=0; i<1000; i++)
        {
            hashsymb[i]=NULL;
            AddofLine[i]=(String)malloc(sizeof(char)*5);
            hashcodes[i]=-1;
        }
        hashCode();
        
        if(tokenize_pass(f)!=1){printf("ERROR AT GENERATING SYMBOL TABLE!\n");}
        else
        {
            
            fclose(f);
            printf("\n\n\nSYMBOL TABLE\n\n\n");
            system("cat SYMBOLTABLE");
            printf("\n\n\n");
            f=fopen(SPF,"r");
            if(generateCode(f)!=1){printf("ERROR GENERATING THE CODE\n");}
            else
            {
                printf("OBJECT CODE SUCCESSFULLY GENERATED. OUTPUT AVAILABLE ON MACHINECODE FILE!\n\n\n");
                printf("\n\nMACHINE CODE\n\n");
                system("cat MACHINECODE");
            }            
        }fclose(f);fclose(f1);
       
    }
}
}

int tokenize_pass(FILE *f)
{
size_t buf_limit = BUFLMT;
char *sentence = (char *) malloc(buf_limit);
char *tok_1;
int i=0;
FILE *symTbl=fopen("SYMBOLTABLE","w");
FILE *spf=fopen(SPF,"w");
fprintf(symTbl,"%15s %15s\n","Location","Symbol");
    fflush(stdin);
while(getline(&sentence,&buf_limit,f)!=EOF)
{
       // codelc++;//this has to be changed-lineinc
        //lineinc++;
        setAddress();
        //int flag=3;//already accessed a macro or opcode
        tok_1 = strtok(sentence,";");
        int j;
        tok_1 = strtok(sentence," \n");
        String tokensInLine[MaxWrds];
        //parsing && (tok_1[0]!=';' || tok_1[strlen(tok_1)-2]!=';')
        for(i=0;tok_1;i++)
        {
          //int n = atoi(tok_1);
          // printf("%d ",n);
        tokensInLine[i]=(char *)malloc(strlen(tok_1)*sizeof(char));
        //tokensInLine[i]="";
        for (j=0; j<strlen(tok_1); j++)
        {
            tokensInLine[i][j]=tok_1[j];
        }
        //strcpy(tokensInLine[i],tok_1);
            tok_1 = strtok(NULL," \n");
        }
        
        //case of a symbol definition
        if(tokensInLine[0][strlen(tokensInLine[0])-1]==':' || tokensInLine[1][0]==':')
        {
            //symbol found
            short flag=(tokensInLine[1][0]==':')?1:0;
            int indx=0,flg;
            if(flag==0)tokensInLine[0][strlen(tokensInLine[0])-1]=0;
            //error check
            if((indx=hashSymbols(tokensInLine[0]))==-1)
            {
                fclose(symTbl);return 0;//exitting on error
            }
            //lines executed if error free
            
            SymHashEntry(indx,tokensInLine[0],symTbl);
                flg=-1;
                flg=chkOpcde(tokensInLine[flag+1]);
                if(flg==-1)
                {
                   //printf("IN MACROcheck\n");
                    flg=checkMacro(tokensInLine[flag+1]);
                    if(flg==-1)
                    {
                        printf("%s : UNKNOWN OPCODE OR MACRO!!\n",tokensInLine[flag+1]);
                        fclose(symTbl);
                        return 0;
                    }
                    else if(flg>=2)
                    if(MacroAction(flg-2,tokensInLine,i)!=1)
                        {
                            printf(" %s --PSEUDO-OPCODE MISTAKE!!\n",tokensInLine[flag+1]);
                            fclose(symTbl);
                            return 0;
                        }
                 }
                else 
                {
                    j=-1;//printf("IN OPcodeCheck\n");
                    while((++j)<5)
                    { AddofLine[linecount][j]=a.hex[j];}
                    codelc++;
                    linecount++;
                    codelc+=MOT[flg]->codelcincr;
                    flg=0;
                }
            j=flag+1;
           // printf("FILE INPUTTING--hui\n");
            while (j<i)
            {
                fprintf(spf,"%s ",tokensInLine[j++]);
            }
            fprintf(spf,"\n");

        }
        else 
        {
                int flg=-1;
                //int hashval=hash2(MOT[i]->code)%211;
                //checking for opcode
                flg=chkOpcde(tokensInLine[0]);
                if(flg==-1)
                {
                    //checking for Macro
                    flg=checkMacro(tokensInLine[0]);
                    //printf("%d --> flg result of macro\n",flg);
                    if(flg==-1)
                       {
                           printf("%s : UNKNOWN OPCODE OR MACRO!!\n",tokensInLine[0]);
                           return 0;
                       }
                    else if(flg>=2)
                        if(MacroAction(flg-2,tokensInLine,i)!=1)
                        {
                            printf("%s --PSEUDO-OPCODE MISTAKE..!\n",tokensInLine[0]);
                            fclose(symTbl);
                            return 0;
                        }
                }
                else
                {
                    //flag=i;printf("%d\n",flag);
                    j=-1;//printf("IN OPcodeCheck\n");
                    while((++j)<5)
                    { AddofLine[linecount][j]=a.hex[j];}
                    codelc++;
                    linecount++;
                    codelc+=MOT[flg]->codelcincr;
                    flg=0;
                }
            j=0;
            //printf("FILE INPUTTING--hui hui\n");
            while (j<i)
            {
                fprintf(spf,"%s ",tokensInLine[j++]);
            }
            fprintf(spf,"\n");

            
        }
       
    /*if(flg>2)
        if(MacroAction(flg-2,tokensInLine,i))
            {
                printf("MACRO MISTAKE!!\n");
                return 0;
            }*/
}
fclose(spf);
fclose(symTbl);
return 1;
}

int checkMacro(String s)
{
    
   // printf("IN chkMacro... %s\n",s);
    for( int i=0;i<2;i++)
        if(0==strcmp(macro[i],s))
        {return (2+i);}
    return -1;
}
int MacroAction(int macro,String s[],int len)
{
    switch (macro) {
        case 0:
            AddofLine[linecount]=a.hex;
            linecount++;
            break;
        case 1:
            //printf("%s\n",s[1]);
            if(s[1][strlen(s[1])-1]=='h'||s[1][strlen(s[1])-1]=='H')
            {
                int n=0;
                for(int i=0;i<strlen(s[1])-1;i++)
                    {
                       if(isdigit(s[1][i]))
                       { n=n*16+s[1][i]-'0';}//printf("%chuiii%d",s[1][i],n);}
                       else if(isalpha(s[1][i]))
                              { if(s[1][i]<'A'+6 && s[1][i]>='A')
                                    {
                                        n=n*16+(s[1][i]-'A'+10);
                                        //printf("%chui3%d",s[1][i],n);
                                    }
                                else return 0;
                              }
                       else return 0;
                    }
                codelc=n+reloc;//for enabling relocation
                //printf("lllll%d\n",codelc);
                linecount++;
                setAddress();
                //printf("chking %d..%d..%s\n",codelc,a.adrs,a.hex);
                    
            }
        default:
            break;
    }
    return 1;
}
int LoadMOT(FILE *f)
{
    size_t buf_limit = BUFLMT;
    char *sentence = (char *) malloc(buf_limit);
    char *tok_1;
    int i=0; fflush(stdin);
    while(getline(&sentence,&buf_limit,f)!=EOF)
    {
        tok_1 = strtok(sentence," ");
        
        String tokensInLine[MaxWrds];
        int j=0;
        
        for(i=0;tok_1;i++)
        {
           
            tokensInLine[i]=(char *)malloc(strlen(tok_1)*sizeof(char));
            //tokensInLine[i]="";
            if(tokensInLine[i][3]<0)tokensInLine[i][3]=0;//hard code ? removal
            for (j=0; j<strlen(tok_1); j++)
            {
                tokensInLine[i][j]=tok_1[j];//copying tokens
            }
            tok_1 = strtok(NULL," ");
        }
        
        MOT[motsize]=(Opcodes)malloc(sizeof(op));
        j=0;MOT[motsize]->flag=-1;
        while((MOT[motsize]->code[j]=tokensInLine[0][j])!=0)j++;
        j=0;
        if(tokensInLine[1][0]>='0'&& tokensInLine[1][0]<='9')
          {
              MOT[motsize]->codelcincr=tokensInLine[1][0]-'0';
              MOT[motsize]->flag=0;
          }
        else while((MOT[motsize]->op1[j]=tokensInLine[1][j])!=0)j++;
        if(MOT[motsize]->flag!=0)
        {
            if(tokensInLine[2][0]>='0'&& tokensInLine[2][0]<='9')
            {
                MOT[motsize]->codelcincr=tokensInLine[2][0]-'0';
                MOT[motsize]->flag=1;
            }
          else
           {
               MOT[motsize]->flag=2;j=0;
               while((MOT[motsize]->op2[j]=tokensInLine[2][j])!=0)j++;
               MOT[motsize]->codelcincr=0;
           }
        }
        j=0;
        while((MOT[motsize]->hexCode[j]=tokensInLine[3][j])!=0)j++;
        MOT[motsize]->hexCode[j-1]=0;
        motsize++;
    }
    /*printf("%6s %4s %4s %15s %8s %10s\n","OPCODE","op1","op2","HEXCODE","FLAG","ADDINR");
    for(i=0;i<motsize;i++)
        printf("%5s %4s %4s %15s %8d %10d\n",MOT[i]->code,MOT[i]->op1,MOT[i]->op2,MOT[i]->hexCode,MOT[i]->flag-'\0',MOT[i]->codelcincr-'\0');
    */return 1;
}
int chkOpcde(String s)
{
    int hashval=(hash1(s )+hash2(s )-10)%211,corr=0,flg=-1;
    //int hashval=hash2(MOT[i]->code)%211;
    if(hashcodes[hashval]!=-1)
    {
    if((corr=strcmp(MOT[hashcodes[hashval]]->code,s))==0)
        flg=hashval;
    else
    {
        //printf("Collision ->%s...%s\n",MOT[hashcodes[hashval]]->code,MOT[i]->code);
        corr=(corr>0)?-1:1;
        hashval+=corr;
        if(hashcodes[hashval]!=-1)
        {
        if(strcmp(MOT[hashcodes[hashval]]->code,s)==0)
            flg=hashval;
        }
    }
    }
    return flg==-1?flg:hashcodes[hashval];
    
}
int chkReg(String s)
{
    int j=0;
    //printf("IN chkReg\n");
    for (j=0; j<10; j++)
    {
        //printf("%s ... %s---%d\n",s,reg[j],strcmp(s,reg[j]));
        if(strcmp(s,reg[j])==0)
            break;
    }j=(j==10)?-1:j;
    return j;
}
int OperateOnOpcode(String s[],String add,int indx,FILE *f)
{
    int l=MOT[indx]->codelcincr;
    int no_operands=MOT[indx]->flag;
    //printf(" HELLO %s .. l=%d .. no_op=%d\n",MOT[indx]->code,l,no_operands);
    //String c=MOT[motindx]->code;
    if(l==0)
    {
        if(no_operands==2)
        {
            int i=chkReg(s[1]);
            if(i==-1){printf("%s : NOT A VALID REGISTER!\n",s[1]);return -1;}
            int j=chkReg(s[2]);
            if(j==-1){printf("%s : NOT A VALID REGISTER!\n",s[2]);return -1;}
            fprintf(f,"%6s  %4s\n",add,MOT[indx+i*7+j]->hexCode);
        }
        else if(no_operands==1)
        {
            int flag=-1, i=0;
            while(strcmp(MOT[indx]->code,MOT[indx+i]->code)==0)
            {
                if(strcmp(MOT[indx+i]->op1,s[1])==0)
                {
                    fprintf(f,"%6s  %4s\n",add,MOT[indx+i]->hexCode);
                    flag=1;break;
                }
                i++;
            }
            if(flag==-1)
            {printf("%s : NOT A VALID REGISTER!\n",s[1]);return -1;}
            
        }
        else if(no_operands==0)fprintf(f,"%6s  %4s\n",add,MOT[indx]->hexCode);
    }
    else if(l==1)
    {
        if(no_operands==1)
        {
            int flag=-1,i=0;//printf("%s\n",s[1]);
            while(strcmp(MOT[indx]->code,MOT[indx+i]->code)==0)
            {
                //printf("%5s.. its operand--%3s!!\n",MOT[indx+i]->code,MOT[indx+i]->op1);/////
                if(strcmp(MOT[indx+i]->op1,s[1])==0)
                {
                    //indx=indx+i;
                    
                    fprintf(f,"%6s  %4s\n",add,MOT[indx+i]->hexCode);
                    flag=1;break;
                }
                i++;
            }
            if(flag==-1)
            {printf("%s : NOT A VALID REGISTER!\n",s[1]);return -1;}
            if(s[2][strlen(s[2])-1]=='h'||s[2][strlen(s[2])-1]=='H')
            {
                s[2][strlen(s[2])-1]='\0';
                fprintf(f,"%6s  %4s\n"," ",s[2]);
            }
            else {printf("%s : NOT A VALID HEX VALUE!\n",s[2]);return -1;}
            
        }
        else return -1;

    }
    else if(l==2)
    {
        if(no_operands==1)
        {
            int flag=-1, i=0;
            while(strcmp(MOT[indx]->code,MOT[indx+i]->code)==0)
            {
                printf("HI %s\n",MOT[indx+i]->code);
                if(strcmp(MOT[indx+i]->op1,s[1])==0)
                {
                    indx=indx+i;
                    fprintf(f,"%6s  %4s\n",add,MOT[indx]->hexCode);
                    flag=1;break;
                }
                i++;
            }
            if(flag==-1)
              {
                  printf("NOT A VALID REGISTER!\n");
                  return -1;
              }
            if(s[2][strlen(s[2])-1]=='h'||s[2][strlen(s[2])-1]=='H')
            {
                fprintf(f,"%6s  %3c%c\n"," ",s[2][2],s[2][3]);
                fprintf(f,"%6s  %3c%c\n"," ",s[2][0],s[2][1]);
            }
            else {printf("NOT A VALID HEX VALUE!\n");return -1;}
            
        }
        else if(no_operands==0)
        {
            fprintf(f,"%6s  %4s\n",add,MOT[indx]->hexCode);
            if(s[1][strlen(s[2])-1]=='h'||s[1][strlen(s[2])-1]=='H')
            {
                fprintf(f,"%6s  %3c%c\n"," ",s[1][2],s[1][3]);
                fprintf(f,"%6s  %3c%c\n"," ",s[1][0],s[1][1]);
            }
            else
            {
                void *p=chkLabel(s[1]);
                if(p==NULL)
                {
                    printf("%s : UNKNOWN LABEL!\n",s[1]);
                    return -1;
                }
                else
                {
                    String labeladd=((Symbol)p)->address;
                    fprintf(f,"%6s  %3c%c\n"," ",labeladd[2],labeladd[3]);
                    fprintf(f,"%6s  %3c%c\n"," ",labeladd[0],labeladd[1]);
                }
            }
        }
    }
    return 1;
}
void *chkLabel(String s)
{
    void *p;
    p=NULL;
    int i=1,flag=0,val2=0;//linear probe
    int hashval=val2=(hash1(s)+i*hash2(s))%449;
    while (hashsymb[hashval]!=NULL || val2!=hashval)
    {
        i++;
        p=hashsymb[hashval];
        if(strcmp(((Symbol)p)->sym_name,s)==0)
        {
           return p;
        }
        hashval=(hash1(s)+i*hash2(s))%449;
    }
    return p;
}
int generateCode(FILE *f)
{
    
    size_t buf_limit = BUFLMT;
    char *sentence = (char *) malloc(buf_limit);
    char *tok_1;
    int i=-1; fflush(stdin);
    FILE *MC_code=fopen("MACHINECODE","w");
    //fprintf(symTbl,"%15s %15s\n","Location","Symbol");
    while(getline(&sentence,&buf_limit,f)!=EOF)
    {
        //tok_1 = strtok(sentence,";");
        tok_1 = strtok(sentence," ,\n");
        String tokensInLine[MaxWrds];
        int j=0,k=0;
        //tokens of the line
        for(k=0;tok_1 ;k++)
        {
            
            tokensInLine[k]=(char *)malloc(strlen(tok_1)*sizeof(char));
           
            for (j=0; j<strlen(tok_1); j++)
                tokensInLine[k][j]=tok_1[j];//copying tokens
            
            tok_1 = strtok(NULL," ,\n");
         }
       // j=0;
        //while(j<k)printf("%d->%s,\n",j,tokensInLine[j++]);
        //printf("\nEOL\n");printf("%s\n",AddofLine[i+1]);
        if(AddofLine[++i]==NULL)
            continue;//if macro
        else
        {
            int motindx=0;//printf("HI %s\n",tokensInLine[0]);
            if((motindx=chkOpcde(tokensInLine[0]))>=0)
                {
                    // printf("MOT[%d]->%s\n",motindx,MOT[motindx]->code);
                    if(OperateOnOpcode(tokensInLine,AddofLine[i],motindx,MC_code)==-1)
                    {fclose(MC_code);return 0;}//opcode correct-- operation unsuccessful
                }
           // printf("%d\n",motindx);
            
        }
        
    }
    fclose(MC_code);
    return 1;
}