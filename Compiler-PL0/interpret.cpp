//
//  interpret.cpp
//  Compiler-PL0
//
//  Created by TimmyXu on 15/1/6.
//  Copyright (c) 2015年 TimmyXu. All rights reserved.
//

#include "interpret.h"

int p,b,t,s[stacksize];
instruction i;

int base(int l) {
    int b1;
    b1 = b;
    while (l > 0) {
        b1 = s[b1];
        l--;
    }
    return b1;
}

void interpret() {
    cout << "START PL/0" << endl;
    t = p = 0;
    b = 1;
    s[1] = s[2] = s[3] = 0;
    do {
        i = code[p];
        p++;
        switch (i.f) {
            case lit:
                s[++t] = i.a;
                break;
            case opr:
                switch (i.a) {
                    case 0:
                        t = b-1;
                        p = s[t+3];
                        b = s[t+2];
                        break;
                    case 1:
                        s[t] = -s[t];
                        break;
                    case 2:
                        t--;
                        s[t] += s[t+1];
                        break;
                    case 3:
                        t--;
                        s[t] -= s[t+1];
                        break;
                    case 4:
                        t--;
                        s[t] *= s[t+1];
                        break;
                    case 5:
                        t--;
                        s[t] /= s[t+1];
                        break;
                    case 6:
                        s[t] %= 2;
                        break;
                    case 7:
                        t--;
                        s[t] = (s[t] = s[t+1]);
                        break;
                    case 8:
                        t--;
                        s[t] = (s[t] != s[t+1]);
                        break;
                    case 9:
                        t--;
                        s[t] = (s[t] < s[t+1]);
                        break;
                    case 10:
                        t--;
                        s[t] = (s[t] >= s[t+1]);
                        break;
                    case 11:
                        t--;
                        s[t] = (s[t] > s[t+1]);
                        break;
                    case 12:
                        t--;
                        s[t] = (s[t] <= s[t+1]);
                        break;
                    default:
                        break;
                }
                break;
            case lod:
                s[++t] = s[base(i.l) + i.a];
                break;
            case sto:
                s[base(i.l) + i.a] = s[t--];
                break;
            case cal:
                s[t+1] = base(i.l);
                s[t+2] = b;
                s[t+3] = p;
                b = t + i.l;
                p = i.a;
                break;
            case inta:
                t += i.a;
                break;
            case jmp:
                p = i.a;
                break;
            case jpc:
                if (s[t--] == 0) {
                    p = i.a;
                }
                break;
            case red:
                cout << "请输入:" << endl;
                cin >> s[base(i.l) + i.a];
                break;
            case wrt:
                cout << s[t++] << endl;
                break;
            default:
                break;
        }
    } while (p != 0);
    cout << "END PL/0" << endl;
}