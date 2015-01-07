//  词法分析子程序
//  words.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#include "words.h"

//TODO 统一输入输出风格

void getch() {
    if (cc == ll) { //到达行末，读下一行
        if (fin.eof()) {
            cout << "程序未完成" << endl;
            return;
        }
        ll = cc = 0;
        printf("%d ", cx);
        getline(fin, line);
        while (line == "") {
            getline(fin, line);
        }
        cout << line << endl;
        ll = (int)line.length();
    }
    ch = line[cc++];
}

void getsym() {
    int i,j,k;
    while (ch == ' ')
        getch();
    
    if ((ch >= 'a') && (ch <= 'z')) { //识别保留字
        k = 0;
        a.clear();
        do {
            if (k < al) {
                a += ch;
            }
            getch();
        } while (((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')));
        k = kk = (int)a.length();
        id.clear();
        id = a;
        i = 1;
        j = norw; //二分检索保留字表
        do {
            k = (i + j) / 2;
            if (id <= word[k]) {
                j = k - 1;
            }
            if (id >= word[k]) {
                i = k + 1;
            }
        } while (i <= j);
        
        if (i - 1 > j) {
            sym = wsym[k];
        } else {
            sym = ident;
        }
    } else if ((ch >= '0') && (ch <= '9')){ //处理数字
        k = num = 0;
        sym = number;
        do {
            num = 10 * num + (ch - '0');
            k++;
            getch();
        } while ((ch >= '0') && (ch <= '9'));
        if (k > nmax) { //数太大
            error(30);
        }
    } else if (ch == ':') { //处理冒号
        getch();
        if (ch == '=') {
            sym = becomes;
            getch();
        } else {
            sym = nul;
        }
    } else if (ch == '<') { //处理小于号和小于等于和不等于
        getch();
        if (ch == '=') {
            sym = leq;
            getch();
        } else if (ch == '>') {
            sym = neq;
            getch();
        } else {
            sym = lss;
        }
    } else if (ch == '>') { //处理大于号和大于等于
        getch();
        if (ch == '=') {
            sym =geq;
            getch();
        } else {
            sym = gtr;
        }
    } else {
        sym = ssym[ch];
        getch();
    }
}

void test(symset s1, symset s2, int n) {
    if (!s1.count(sym)) {
        error(n);
        while (!s1.count(sym) && !s2.count(sym)) {
            getsym();
        }
    }
}