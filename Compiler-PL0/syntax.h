//  语法分析子程序
//  syntax.h
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#ifndef __Compiler_PL0__syntax__
#define __Compiler_PL0__syntax__

#include "def.h"
#include "words.h"
#include "tab.h"
#include "pcode.h"
#include "error.h"

void block(int lev, int tx, symset fsys); //子程序语法分析
void constdeclaration(int lev, int &tx, int &dx); //常量定义分析
void vardeclaration(int lev, int &tx, int &dx); //变量定义分析
void statement(symset fsys, int lev, int &tx); //语句分析
void expression(symset fsys, int lev, int &tx); //表达式分析
void term(symset fsys, int lev, int &tx); //项分析
void factor(symset fsys, int lev, int &tx); //因子分析
void condition(symset fsys, int lev, int &tx); //条件语句分析


#endif /* defined(__Compiler_PL0__syntax__) */
