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
        if (scanf("%c", &ch) == EOF) {
            cout << "程序未完成" << endl;
            return;
        }
        ll = cc = 0;
        cout << cx;
        while (ch != '\n') {
            cout << ch;
            line[++ll] = ch;
            scanf("%c", &ch);
        }
        cout << endl;
        line[++ll] = ' ';
    }
    ch = line[++cc];
}

void getsym() {
    int i,j,k;
    while (ch == ' ')
        getch();
    
    if ((ch >= 'a') && (ch <= 'z')) { //识别保留字
        k = 0;
        do {
            if (k < al) {
                a[++k] = ch;
            }
            getch();
        } while (((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')));
        
        if (k >= kk) { // kk 是最后一个保留字的长度
            kk = k;
        } else {
            do {
                a[kk--] = ' ';
            } while (kk != k);
        }
        
        strcpy(id, a);
        i = 1;
        j = norw; //二分检索保留字表
        do {
            k = (i + j) / 2;
            if (strcmp(id, word[k]) <= 0) {
                j = k - 1;
            }
            if (strcmp(id, word[k]) >= 0) {
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
        while (!s1.count(sym) || !s2.count(sym)) {
            getsym();
        }
    }
}