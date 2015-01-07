//
//  def.h
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/6.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#ifndef Compiler_PL0_def_h
#define Compiler_PL0_def_h
#include <iostream>
#include <fstream>
#include <set>
#include <cstdio>
#include <cstring>
#include <string>
#include <setjmp.h>

using namespace std;

//常量定义
const int norw = 14, // 保留字个数
          txmax = 100, //符号表最大长度
          nmax = 14, //数字最长位数
          al = 10, //标识符最大长度
          amax = 2047, //最大寻址
          levmax = 3, //嵌套最深层数
          cxmax = 200; //源代码最大长度

//定义新类型
enum symbol {nul, ident, number, pluss, minuss, times, slash, oddsym, eql, neq, lss, leq, gtr, geq,
    lparen, rparen, comma, semicolon, period, becomes, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, readsym, writesym, elsesym}; //保留字枚举类型
enum objecttyp {constant, variable, procedure}; //对象类型
enum fct {lit, opr, lod, sto, cal, inta, jmp, jpc, red, wrt}; //P-code函数

typedef set<symbol> symset; //保留字集合

struct instruction {
    fct f; //指令代码
    int l, //嵌套层级
        a; //寻址
};

struct tab {
    string name;
    objecttyp kind;
    int val, level, adr;
};

extern symbol sym, //最后读的保留字
              wsym[norw+1],
              ssym[256];

extern tab table[txmax + 2];

extern char ch; //最后一个读的字符

extern string mnemonic[11];

extern string line;

extern string id, //最后读的标识符
              a,
              word[norw+1];

extern int num, //最后读的数字
            cc, //字符所在行计数
            ll,ln, //行长度
            kk, err,
            cx; //代码收集索引

extern instruction code[cxmax + 1];

extern symset declbegsys, statbegsys, facbegsys;

extern string errmsg[40];

extern ifstream fin;

extern jmp_buf buf;

#endif