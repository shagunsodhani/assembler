#ifndef OPTAB_H
#define OPTAB_H
string REGISTER[6][2]={"0","A",
                       "1","X",
                       "2","L",
                       "3","B",
                       "4","S",
                       "5","T"};
string OPTAB[45][3]={"ADD","18","3",
                     "ADDR","90","2",
                     "AND","40","3",
                     "CLEAR","B4","2",
                     "COMP","28","3",
                     "COMPR","A0","2",
                     "DIV","24","3",
                     "DIVR","9C","2",
                     "J","3C","3",
                     "JEQ","30","3",
                     "JGT","34","3",
                     "JLT","38","3",
                     "JSUB","48","3",
                     "LDA","00","3",
                     "LDB","68","3",
                     "LDCH","50","3",
                     "LDL","08","3",
                     "LDS","6C","3",
                     "LDT","74","3",
                     "LDX","04","3",
                     "LPS","D0","3",
                     "MUL","20","3",
                     "MULR","98","2",
                     "OR","44","3",
                     "RD","D8","3",
                     "RMO","AC","2",
                     "RSUB","4C","3",
                     "SHIFTL","A4","2",
                     "SHIFTR","A8","2",
                     "STA","0C","3",
                     "STB","78","3",
                     "STCH","54","3",
                     "STI","D4","3",
                     "STL","14","3",
                     "STS","7C","3",
                     "STSW","E8","3",
                     "STT","84","3",
                     "STX","10","3",
                     "SUB","1C","3",
                     "SUBR","94","2",
                     "SVC","B0","2",
                     "TD","E0","3",
                     "TIX","2C","3",
                     "TIXR","B8","2",
                     "WD","DC","3"};
string SYMTAB[100][3];
#endif