//  词法分析子程序
//  words.h
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#ifndef __Compiler_PL0__words__
#define __Compiler_PL0__words__

#include "def.h"
#include "error.h"

void getch(); //获取一个字符
void getsym(); //获取一个单词
void test(symset s1,symset s2, int n); //测试单词是否合法

#endif /* defined(__Compiler_PL0__words__) */