//  语法分析子程序
//  syntax.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/5.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#include "syntax.h"

void block(int lev, int tx, symset fsys) {
    int dx, tx0, cx0;
    dx = 3;
    tx0 = tx;
    table[tx].adr = cx;
    gen(jmp, 0, 0);
    if (lev > levmax) {
        error(32);
    }
    do {
        if (sym == constsym) {
            getsym();
            do {
                constdeclaration(lev, tx, dx);
                while (sym == comma) {
                    getsym();
                    constdeclaration(lev, tx, dx);
                }
                if (sym == semicolon) {
                    getsym();
                } else {
                    error(5);
                }
            } while (sym == ident);
        }
        if (sym == varsym) {
            getsym();
            do {
                vardeclaration(lev, tx, dx);
                while (sym == comma) {
                    getsym();
                    vardeclaration(lev, tx, dx);
                }
                if (sym == semicolon) {
                    getsym();
                } else {
                    error(5);
                }
            } while (sym == ident);
        }
        
        while (sym == procsym) {
            getsym();
            if (sym == ident) {
                enter(procedure, dx, lev, tx);
                getsym();
            } else {
                error(4);
            }
            if (sym == semicolon) {
                getsym();
            } else {
                error(5);
            }
            symset tmp;
            tmp.clear();
            tmp.insert(fsys.begin(), fsys.end());
            tmp.insert(semicolon);
            block(lev+1, tx, tmp);
            if (sym == semicolon) {
                getsym();
                symset tmp2;
                tmp2.clear();
                tmp2.insert(statbegsys.begin(), statbegsys.end());
                tmp2.insert(ident);
                tmp2.insert(procsym);
                test(tmp2, fsys, 6);
            } else {
                error(5);
            }
        }
        symset tmp3;
        tmp3.clear();
        tmp3.insert(statbegsys.begin(), statbegsys.end());
        tmp3.insert(ident);
        test(tmp3, declbegsys, 7);
    } while (declbegsys.count(sym));
    code[table[tx0].adr].a = cx;
    table[tx0].adr = cx;
    cx0 = cx;
    gen(inta, 0, dx);
    symset tmp;
    tmp.clear();
    tmp.insert(fsys.begin(), fsys.end());
    tmp.insert(semicolon);
    tmp.insert(endsym);
    statement(tmp, lev, tx);
    gen(opr, 0, 0);
    symset tmp2;
    tmp2.clear();
    test(fsys, tmp2, 8);
    //listcode(cx0);
}

void constdeclaration(int lev, int &tx, int &dx) {
    if (sym == ident) {
        getsym();
        if (sym == eql || sym == becomes) {
            if (sym == becomes) {
                error(1);
            }
            getsym();
            if (sym == number) {
                enter(constant, dx, lev, tx);
                getsym();
            } else {
                error(2);
            }
        } else {
            error(3);
        }
    } else {
        error(4);
    }
}

void vardeclaration(int lev, int &tx, int &dx) {
    if (sym == ident) {
        enter(variable, dx, lev, tx);
        getsym();
    } else {
        error(4);
    }
}

void statement(symset fsys, int lev, int &tx) {
    int i, cx1, cx2;
    if (sym == ident) {
        i = position(id, tx);
        if (i == 0) {
            error(11);
        } else if (table[i].kind != variable){
            error(12);
            i = 0;
        }
        getsym();
        if (sym == becomes) {
            getsym();
        } else {
            error(13);
        }
        expression(fsys, lev, tx);
        if (i != 0) {
            gen(sto, lev-table[i].level, table[i].adr);
        }
    } else if (sym == callsym) {
        getsym();
        if (sym != ident) {
            error(14);
        } else {
            i = position(id, tx);
            if (i == 0) {
                error(11);
            } else {
                if (table[i].kind == procedure) {
                    gen(cal, lev-table[i].level, table[i].adr);
                } else {
                    error(15);
                }
            }
            getsym();
        }
    } else if (sym == ifsym) {
        getsym();
        symset tmp;
        tmp.clear();
        tmp.insert(fsys.begin(), fsys.end());
        tmp.insert(thensym);
        tmp.insert(dosym);
        condition(tmp, lev, tx);
        if (sym == thensym) {
            getsym();
        } else {
            error(16);
        }
        cx1 = cx;
        gen(jpc, 0, 0);
        statement(fsys, lev, tx);
        code[cx1].a = cx;
    } else if (sym == beginsym) {
        getsym();
        symset tmp;
        tmp.clear();
        tmp.insert(fsys.begin(), fsys.end());
        tmp.insert(semicolon);
        tmp.insert(endsym);
        statement(tmp, lev, tx);
        
        symset tmp2;
        tmp2.clear();
        tmp2.insert(statbegsys.begin(), statbegsys.end());
        tmp2.insert(semicolon);
        while (tmp2.count(sym)) {
            if (sym == semicolon) {
                getsym();
            } else {
                error(10);
            }
            statement(tmp, lev, tx);
        }
        if (sym == endsym) {
            getsym();
        } else {
            error(17);
        }
    } else if (sym == whilesym) {
        cx1 = cx;
        getsym();
        symset tmp;
        tmp.clear();
        tmp.insert(fsys.begin(), fsys.end());
        tmp.insert(dosym);
        condition(tmp, lev, tx);
        cx2 = cx;
        gen(jpc, 0, 0);
        if (sym == dosym) {
            getsym();
        } else {
            error(18);
        }
        statement(fsys, lev, tx);
        gen(jmp, 0, cx1);
        code[cx2].a = cx;
    } else if (sym == readsym) {
        getsym();
        if (sym == lparen) {
            do {
                getsym();
                if (sym == ident) {
                    i = position(id, tx);
                    if (i == 0) {
                        error(11);
                    } else {
                        if (table[i].kind != variable) {
                            error(12);
                            i = 0;
                        } else {
                            gen(red, lev-table[i].level, table[i].adr);
                        }
                    }
                } else {
                    error(4);
                }
                getsym();
            } while (sym == comma);
        } else {
            error(40);
        }
        if (sym != rparen) {
            error(22);
        }
        getsym();
    } else if (sym == writesym) {
        getsym();
        if (sym == lparen) {
            symset tmp;
            tmp.clear();
            tmp.insert(fsys.begin(), fsys.end());
            tmp.insert(rparen);
            tmp.insert(comma);
            do {
                getsym();
                expression(tmp, lev, tx);
                gen(wrt, 0, 0);
            } while (sym == comma);
            if (sym != rparen) {
                error(22);
            }
            getsym();
        } else {
            error(40);
        }
    }
    symset tmp;
    tmp.clear();
    test(fsys, tmp, 19);
}

void expression(symset fsys, int lev, int &tx) {
    symbol addop;
    symset tmp;
    tmp.clear();
    tmp.insert(fsys.begin(), fsys.end());
    tmp.insert(pluss);
    tmp.insert(minuss);
    
    if (sym == pluss || sym == minuss) {
        addop = sym;
        getsym();
        term(tmp, lev, tx);
        if (addop == minuss) {
            gen(opr, 0, 1);
        }
    } else {
        term(tmp, lev, tx);
    }
    
    while (sym == pluss || sym == minuss) {
        addop = sym;
        getsym();
        term(tmp, lev, tx);
        if (addop == pluss) {
            gen(opr, 0, 2);
        } else {
            gen(opr, 0, 3);
        }
    }
}

void term(symset fsys, int lev, int &tx) {
    symbol mulop;
    symset tmp;
    tmp.clear();
    tmp.insert(fsys.begin(), fsys.end());
    tmp.insert(times);
    tmp.insert(slash);
    factor(tmp, lev, tx);
    
    while (sym == times || sym == slash) {
        mulop = sym;
        getsym();
        factor(tmp, lev, tx);
        if (mulop == times) {
            gen(opr, 0, 4);
        } else {
            gen(opr, 0, 5);
        }
    }
}

void factor(symset fsys, int lev, int &tx) {
    int i;
    test(facbegsys, fsys, 24);
    while (facbegsys.count(sym)) {
        if (sym == ident) {
            i = position(id, tx);
            if (i == 0) {
                error(11);
            } else {
                switch (table[i].kind) {
                    case constant:
                        gen(lit, 0, table[i].val);
                        break;
                    case variable:
                        gen(lod, lev-table[i].level, table[i].adr);
                        break;
                    case procedure:
                        error(21);
                        break;
                    default:
                        break;
                }
            }
            getsym();
        } else if (sym == number) {
            if (num > amax) {
                error(30);
                num = 0;
            }
            gen(lit, 0, num);
            getsym();
        } else if (sym == lparen) {
            getsym();
            symset tmp;
            tmp.clear();
            tmp.insert(fsys.begin(), fsys.end());
            tmp.insert(rparen);
            expression(tmp, lev, tx);
            if (sym == rparen) {
                getsym();
            } else {
                error(22);
            }
        }
        symset tmp;
        tmp.clear();
        tmp.insert(lparen);
        test(fsys, tmp, 23);
    }
}

void condition(symset fsys, int lev, int &tx) {
    symbol relop;
    if (sym == oddsym) {
        getsym();
        expression(fsys, lev, tx);
        gen(opr, 0, 6);
    } else {
        symset tmp;
        tmp.clear();
        tmp.insert(fsys.begin(), fsys.end());
        tmp.insert(eql);        tmp.insert(neq);        tmp.insert(lss);
        tmp.insert(gtr);        tmp.insert(leq);        tmp.insert(geq);
        expression(tmp, lev, tx);
        tmp.clear();
        tmp.insert(eql);        tmp.insert(neq);        tmp.insert(lss);
        tmp.insert(gtr);        tmp.insert(leq);        tmp.insert(geq);
        if (!tmp.count(sym)) {
            error(20);
        } else {
            relop = sym;
            getsym();
            expression(fsys, lev, tx);
            switch (relop) {
                case eql:
                    gen(opr, 0, 8);
                    break;
                case neq:
                    gen(opr, 0, 9);
                    break;
                case lss:
                    gen(opr, 0, 10);
                    break;
                case geq:
                    gen(opr, 0, 11);
                    break;
                case gtr:
                    gen(opr, 0, 12);
                    break;
                case leq:
                    gen(opr, 0, 13);
                    break;
                default:
                    break;
            }
        }
    }
}