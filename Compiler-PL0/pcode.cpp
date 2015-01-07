//  生成P-code子程序
//  pcode.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#include "pcode.h"

void gen(fct x, int y, int z) {
    if (cx > cxmax) {
        cout << "Program too long!" << endl;
        //TODO 关闭文件
        return;
    }
    code[cx].f = x;
    code[cx].l = y;
    code[cx].a = z;
    cx++;
}

void listcode(int cx0) {
    for (int i = cx0; i < cx; i++) {
        cout << i << " " << mnemonic[code[i].f] << " " << code[i].l << " " << code[i].a << endl;
    }
}