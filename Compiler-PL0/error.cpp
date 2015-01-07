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
    cout << "error(" << ln << ", " << cc << "): 错误代码：" << n << "，错误信息：" << errmsg[n-1] << endl;
    err++;
}