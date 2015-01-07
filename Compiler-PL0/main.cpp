//
//  main.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 14/12/25.
//  Copyright (c) 2014年 TimmyXu. All rights reserved.
//


#include "def.h"
#include "error.h"
#include "words.h"
#include "syntax.h"
#include "tab.h"
#include "pcode.h"
#include "interpret.h"

symbol sym, //最后读的保留字
       wsym[norw+1],
       ssym[256];

tab table[txmax + 2];

char ch; //最后一个读的字符

string mnemonic[11];

string line;

string id, //最后读的标识符
        a,
        word[norw+1];

int num, //最后读的数字
    cc, //字符所在行计数
    ll,ln, //行号
    kk, err,
    cx; //代码收集索引

instruction code[cxmax + 1];

symset declbegsys, statbegsys, facbegsys;

string errmsg[40] = {
    "应是=而不是:=",
    "=后应为数",
    "标识符后应为=",
    "const,var,procedure后应为标识符",
    "漏掉逗号或分号",
    "过程说明后的符号不正确",
    "应为语句",
    "程序体内语句部分后的符号不正确",
    "应为句号",
    "语句之间漏分号",
    "标识符为说明",
    "不可向常量或过程赋值",
    "应为赋值运算符:=",
    "call后应为标识符",
    "不可调用常量或变量",
    "应为then",
    "应为分号或end",
    "应为do",
    "语句后的符号不正确",
    "应为关系运算符",
    "表达式内不可有过程标识符",
    "漏右括号",
    "因子后不可为此符号",
    "表达式不能以此符号开始"
};

ifstream fin;

jmp_buf buf;

int main(int argc, const char * argv[]) {
    fin.open("/Users/timmyxu/Sites/Compiler-PL0/test/6.in");
    memset(ssym, 0, sizeof(ssym));
    
    errmsg[29] = "这个数太大";
    errmsg[31] = "嵌套层数过多";
    errmsg[39] = "应为左括号";
    
    //初始化保留字
    word[1] = "begin"; word[2] = "call"; word[3] = "const"; word[4] = "do"; word[5] = "else";
    word[6] = "end";   word[7] = "if"; word[8] = "odd"; word[9] = "procedure"; word[10] = "read";
    word[11] = "then";  word[12] = "var"; word[13] = "while"; word[14] = "write";
    
    wsym[1] = beginsym;     wsym[2] = callsym;      wsym[3] = constsym;     wsym[4] = dosym;
    wsym[5] = elsesym;      wsym[6] = endsym;       wsym[7] = ifsym;        wsym[8] = oddsym;
    wsym[9] = procsym;      wsym[10] = readsym;      wsym[11] = thensym;      wsym[12] = varsym;
    wsym[13] = whilesym;    wsym[14] = writesym;
    
    ssym['+'] = pluss;      ssym['-'] = minuss;     ssym['*'] = times;      ssym['/'] = slash;
    ssym['('] = lparen;     ssym[')'] = rparen;     ssym['='] = eql;        ssym[','] = comma;
    ssym['.'] = period;     ssym['<'] = lss;        ssym['>'] = gtr;        ssym[';'] = semicolon;

    mnemonic[lit] = "LIT"; mnemonic[opr] = "OPR"; mnemonic[lod] = "LOD"; mnemonic[sto] = "STO";
    mnemonic[cal] = "CAL"; mnemonic[inta] = "INT"; mnemonic[jmp] = "JMP"; mnemonic[jpc] = "JPC";
    mnemonic[red] = "RED"; mnemonic[wrt] = "WRT";
    
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
    
    err = cc = cx = ll = ln = 0;
    ch = ' ';
    kk = al+1;   //???
    
    //取第一个词
    getsym();
    //调用语法分析
    symset tmp;
    tmp.clear();
    tmp.insert(declbegsys.begin(), declbegsys.end());
    tmp.insert(statbegsys.begin(), statbegsys.end());
    tmp.insert(period);
    
    if (!setjmp(buf)) {
        block(0, 0, tmp);
    }
    
    if (sym != period) {
        //错误处理 9
        error(9);
    }
    
    listcode(0);
    if (err == 0) {
        //解释
        interpret();
    } else {
        cout << err << " ERROR(S) IN PL/0 PROGRAM" << endl;
    }
}
