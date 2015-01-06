//
//  main.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 14/12/25.
//  Copyright (c) 2014年 TimmyXu. All rights reserved.
//

#include <iostream>
#include <set>
#include <cstdio>
#include <cstring>

using namespace::std;

//常量定义
const int norw = 13, // 保留字个数
          txmax = 100, //符号表最大长度
          nmax = 14, //数字最长位数
          al = 10, //标识符最大长度
          amax = 2047, //最大寻址
          levmax = 3, //嵌套最深层数
          cxmax = 200; //源代码最大长度

//定义新类型
enum symbol {nul, ident, number, pluss, minuss, times, slash, oddsym, eql, neq, lss, leq, gtr, geq,
            lparen, rparen, comma, semicolon, period, becomes, beginsym, endsym, ifsym, thensym,
            whilesym, dosym, callsym, constsym, varsym, procsym, readsym, writesym}; //保留字枚举类型
enum objecttyp {constant, variable, procedure}; //对象类型
enum fct {lit, opr, lod, sto, cal, inta, jmp, jpc, red, wrt}; //P-code函数

typedef char alfa[al]; //标识符名称

typedef set<symbol> symset; //保留字集合
symbol sym, //最后读的保留字
       wsym[norw],
       ssym[256];

struct instruction {
    fct f; //指令代码
    int l, //嵌套层级
        a; //寻址
};

struct tab {
    alfa name;
    objecttyp kind;
    int val, level, adr;
} table;

char ch, //最后一个读的字符
     line[81],
     mnemonic[10][5];

alfa id, //最后读的标识符
     a,
     word[norw];

int num, //最后读的数字
    cc, //字符所在行计数
    ll, //行号
    kk, err,
    cx; //代码收集索引

instruction code[cxmax + 1];

symset declbegsys, statbegsys, facbegsys;

int main(int argc, const char * argv[]) {
    memset(ssym, 0, sizeof(ssym));
    
    //初始化保留字
    strcpy(word[0], "begin");   strcpy(word[1], "call");        strcpy(word[2], "const");
    strcpy(word[3], "do");      strcpy(word[4], "end");         strcpy(word[5], "if");
    strcpy(word[6], "odd");     strcpy(word[7], "procedure");   strcpy(word[8], "read");
    strcpy(word[9], "then");    strcpy(word[10], "var");        strcpy(word[11], "while");
    strcpy(word[12], "write");
    
    wsym[0] = beginsym;     wsym[1] = callsym;      wsym[2] = constsym;     wsym[3] = dosym;
    wsym[4] = endsym;       wsym[5] = ifsym;        wsym[6] = oddsym;       wsym[7] = procsym;
    wsym[8] = readsym;      wsym[9] = thensym;      wsym[10] = varsym;      wsym[11] = whilesym;
    wsym[12] = writesym;
    
    ssym['+'] = pluss;      ssym['-'] = minuss;     ssym['*'] = times;      ssym['/'] = slash;
    ssym['('] = lparen;     ssym[')'] = rparen;     ssym['='] = eql;        ssym[','] = comma;
    ssym['.'] = period;     ssym['<'] = lss;        ssym['>'] = gtr;        ssym[';'] = semicolon;
    
    strcpy(mnemonic[lit], "LIT");    strcpy(mnemonic[opr], "OPR");    strcpy(mnemonic[lod], "LOD");
    strcpy(mnemonic[sto], "STO");    strcpy(mnemonic[cal], "CAL");    strcpy(mnemonic[inta], "INT");
    strcpy(mnemonic[jmp], "JMP");    strcpy(mnemonic[jpc], "JPC");    strcpy(mnemonic[red], "RED");
    strcpy(mnemonic[wrt], "WRT");
    
    declbegsys.clear();
    declbegsys.insert(constsym);
    declbegsys.insert(varsym);
    declbegsys.insert(procsym);
    
    statbegsys.clear();
    statbegsys.insert(beginsym);
    statbegsys.insert(callsym);
    statbegsys.insert(ifsym);
    statbegsys.insert(whilesym);
    
    facbegsys.clear();
    facbegsys.insert(ident);
    facbegsys.insert(number);
    facbegsys.insert(lparen);
    
    err = cc = cx = ll = 0;
    ch = NULL;
    kk = al;
    
    //取第一个词
    //调用语法分析
    
    if (sym != period) {
        //错误处理 9
    }
    
    if (err == 0) {
        //输出P-code
    } else {
        cout << "ERRORS IN PL/0 PROGRAM" << endl;
    }
}
