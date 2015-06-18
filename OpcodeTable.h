//
//  OpcodeTable.h
//  
//
//  Created by Ramit on 11/01/13.
//
//

#ifndef ____OpcodeTable__
#define ____OpcodeTable__

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#define SymTab_MaxSize 10000
#define BUFLMT 65500
#define MaxWrds 1000
#define Mot "symbols8085.txt"
#define SPF "SemiProcessedFile" 
#define prime1 223
#define prime2 200
typedef char * String;
typedef struct { int adrs; char hex[8];} Addrss;
Addrss a;
int linecount=0,codelc=0,motsize=0,symtbsize=0,reloc=0;//line count, code line count, relocation value


String reg[]={"A","B","C","D","E","H","L","M","PSW","SP"};
String macro[]={"END","ORG"};

struct Macro
{
    char *mc_name;
    int i;
    //struct Macro * nxt;
}  ;
typedef struct Macro  Macr;
struct sym
{
    char address[5];
    char sym_name[0];
};
struct op
{
    char code[5];//largest opcode name 4 char long
    char flag;
    /*
      involves other operands
      1-1,2-2
     */
    char codelcincr;
    char op1[4];
    char op2[2];
    char hexCode[3];
    char waste[0];
} ;
void *hashsymb[1000];
String AddofLine[1000];
int hashcodes[1000];
typedef op * Opcodes;
typedef sym * Symbol;
Opcodes MOT[1000];
Symbol SymbolTable[SymTab_MaxSize];
#endif /* defined(____OpcodeTable__) */
