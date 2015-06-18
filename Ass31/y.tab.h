/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKNAME = 258,
     TOKINT = 259,
     TOKFLOAT = 260,
     TOKCHAR = 261,
     SEMICOLON = 262,
     COMMA = 263,
     EQUAL = 264,
     PLUS = 265,
     MINUS = 266,
     MULT = 267,
     MOD = 268,
     DIV = 269,
     NUMBER = 270,
     AND = 271,
     OR = 272,
     NOT = 273,
     GREATERTHAN = 274,
     LESSTHAN = 275,
     LESSTHANEQUAL = 276,
     GREATERTHANEQUAL = 277,
     NOTEQUAL = 278,
     OPENPAREN = 279,
     CLOSEPAREN = 280,
     OPENBRACE = 281,
     CLOSEBRACE = 282,
     TOKWHILE = 283,
     TOKFOR = 284,
     TOKIF = 285,
     TOKELSE = 286,
     COMPEQUAL = 287,
     TOKVOID = 288,
     INC = 289,
     DEC = 290,
     TOKRETURN = 291
   };
#endif
/* Tokens.  */
#define TOKNAME 258
#define TOKINT 259
#define TOKFLOAT 260
#define TOKCHAR 261
#define SEMICOLON 262
#define COMMA 263
#define EQUAL 264
#define PLUS 265
#define MINUS 266
#define MULT 267
#define MOD 268
#define DIV 269
#define NUMBER 270
#define AND 271
#define OR 272
#define NOT 273
#define GREATERTHAN 274
#define LESSTHAN 275
#define LESSTHANEQUAL 276
#define GREATERTHANEQUAL 277
#define NOTEQUAL 278
#define OPENPAREN 279
#define CLOSEPAREN 280
#define OPENBRACE 281
#define CLOSEBRACE 282
#define TOKWHILE 283
#define TOKFOR 284
#define TOKIF 285
#define TOKELSE 286
#define COMPEQUAL 287
#define TOKVOID 288
#define INC 289
#define DEC 290
#define TOKRETURN 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


