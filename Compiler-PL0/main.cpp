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
    ll, //行号
    kk, err,
    cx; //代码收集索引

instruction code[cxmax + 1];

symset declbegsys, statbegsys, facbegsys;

ifstream fin;

int main(int argc, const char * argv[]) {
    fin.open("/Users/timmyxu/Sites/Compiler-PL0/test/3.in");
    memset(ssym, 0, sizeof(ssym));
    
    //初始化保留字
    word[1] = "begin"; word[2] = "call"; word[3] = "const"; word[4] = "do"; word[5] = "end";
    word[6] = "if"; word[7] = "odd"; word[8] = "procedure"; word[9] = "read"; word[10] = "then";
    word[11] = "var"; word[12] = "while"; word[13] = "write";
    
    wsym[1] = beginsym;     wsym[2] = callsym;      wsym[3] = constsym;     wsym[4] = dosym;
    wsym[5] = endsym;       wsym[6] = ifsym;        wsym[7] = oddsym;       wsym[8] = procsym;
    wsym[9] = readsym;      wsym[10] = thensym;      wsym[11] = varsym;      wsym[12] = whilesym;
    wsym[13] = writesym;
    
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
    
    err = cc = cx = ll = 0;
    ch = ' ';
    kk = al+1;
    
    //取第一个词
    getsym();
    //调用语法分析
    symset tmp;
    tmp.clear();
    tmp.insert(declbegsys.begin(), declbegsys.end());
    tmp.insert(statbegsys.begin(), statbegsys.end());
    tmp.insert(period);
    block(0, 0, tmp);
    
    if (sym != period) {
        //错误处理 9
        error(9);
    }
    
    if (err == 0) {
        //输出P-code
        //解释
        listcode(1);
        interpret();
    } else {
        cout << "ERRORS IN PL/0 PROGRAM" << endl;
    }
}
