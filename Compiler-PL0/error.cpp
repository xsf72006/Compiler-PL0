//  错误分析子程序
//  error.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#include "error.h"

void error(int n) {
    //TODO 添加行号；添加中文错误信息
    cout << "error at column " << cc-1 << ", error code " << n << endl;
    err++;
}