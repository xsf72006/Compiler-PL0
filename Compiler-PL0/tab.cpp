//  符号表子程序
//  tab.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#include "tab.h"

void enter(objecttyp k, int &dx, int lev, int &tx) {
    //strcpy(table[++tx].name, id);
    table[++tx].name = id;
    table[tx].kind = k;
    switch (k) {
        case constant:
            if (num > amax) {
                error(30);
                num = 0;
            }
            table[tx].val = num;
            break;
        case variable:
            table[tx].level = lev;
            table[tx].adr = dx++;
            break;
        case procedure:
            table[tx].level = lev;
            break;
        default:
            break;
    }
}

int position(string id, int tx) {
    int i;
    //strcpy(table[0].name, id);
    table[0].name = id;
    i = tx;
    while (table[i].name != id) {
        i--;
    }
    return i;
}