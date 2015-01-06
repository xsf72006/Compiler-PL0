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
       wsym[norw],
       ssym[256];

tab table[txmax + 1];

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
        interpret();
    } else {
        cout << "ERRORS IN PL/0 PROGRAM" << endl;
    }
}
