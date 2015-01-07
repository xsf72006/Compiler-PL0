//  符号表子程序
//  tab.h
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#ifndef __Compiler_PL0__tab__
#define __Compiler_PL0__tab__

#include "def.h"
#include "error.h"

void enter(objecttyp k, int &dx, int lev, int &tx);
int position(string id, int tx);

#endif /* defined(__Compiler_PL0__tab__) */