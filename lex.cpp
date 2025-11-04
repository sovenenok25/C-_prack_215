//
// Created by soven on 09.05.2023.
//
#include <iostream>
#include <string>
#include <cstdio>
#include <cctype>
#include <vector>

#include "Lex.h"

int Lex::numb_of_str=1;
vector<Ident> Lex::TID;

int put ( const string & buf ) {
    vector<Ident>::iterator k;

    if ( ( k = find ( Lex::TID.begin (), Lex::TID.end (), buf ) ) != Lex::TID.end () )
        return k - Lex::TID.begin();
    Lex::TID.push_back ( Ident(buf) );
    return Lex::TID.size () - 1;
}
const char *
        Scanner::TW    [] = { "", "and", "not", "or", "else", "if", "int", "program", "read", "string", "while", "write", NULL };

const char *
        Scanner::TD    [] = { "@", "{", "}", ";", ",", ":", "=", "(", ")", "==", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=", "\"", NULL };

type_of_lex Ident::get_type() {
    return type;
}

Lex Scanner::get_lex () {
    enum    state { H, IDENT, NUMB, COM, ALE, NEQ, STR};
    int     d, j;
    string  buf;
    state   CS = H;
    do {
        gc ();
        switch ( CS ) {
            case H:
                if ( c==' ' || c== '\r' || c == '\t' );
                else
                if (c=='\n')
                {
                    ++Lex::numb_of_str;
                }
                else if (c=='"')
                {
                    CS=STR;
                }
                else if ( isalpha (c) ) {
                    buf.push_back (c);
                    CS  = IDENT;
                }
                else if ( isdigit (c) ) {
                    d   = c - '0';
                    CS  = NUMB;
                }
                else if ( c == '=' || c == '<' || c == '>' ) {
                    buf.push_back (c);
                    CS  = ALE;
                }
                else if (c == '@')
                    return Lex ( LEX_FIN);
                else if (c == '!') {
                    buf.push_back (c);
                    CS  = NEQ;
                }
                else {
                    buf.push_back (c);
                    if ( ( j = look ( buf, TD) ) ){
                        return Lex ( (type_of_lex)( j + (int) LEX_FIN ), j );
                    }
                    else
                        throw c;
                }
                break;
            case IDENT:
                if ( isalpha (c) || isdigit (c) ) {
                    buf.push_back (c);
                    if (buf.size()>25)
                        cout << "loo long id";
                }
                else {
                    ungetc ( c, fp );
                    if ( (j = look ( buf, TW) ) ) {
                        return Lex ( (type_of_lex) j, j );
                    }
                    else {
                        j   = put ( buf );
                        return Lex ( LEX_ID, j );
                    }
                }
                break;
            case STR:
                if (c=='"')
                {
                    return Lex(LEX_STR, 0, buf);
                }
                buf.push_back(c);
                break;
            case NUMB:
                if ( isdigit (c) ) {
                    d = d * 10 + ( c - '0' );
                }
                else {
                    ungetc ( c, fp );
                    return Lex ( LEX_NUM, d );
                }
                break;
            case ALE:
                if ( c == '=' ) {
                    buf.push_back ( c );
                    j   = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_FIN ), j );
                }
                else {
                    ungetc ( c, fp );
                    j   = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_FIN ), j );
                }
                break;
            case NEQ:
                if ( c == '=' ) {
                    buf.push_back(c);
                    j   = look ( buf, TD );
                    return Lex ( LEX_NEQ, j );
                }
                else
                    throw '!';
                break;
        } //end switch
    } while (true);
    return Lex();
}

ostream & operator<< ( ostream &s, Lex& l ) {
    string t;
    if ( l.t_lex <= LEX_WRITE )
        t = Scanner::TW[l.t_lex];
    else if ( l.t_lex >= LEX_FIN && l.t_lex <= LEX_GEQ )
        t = Scanner::TD[ l.t_lex - LEX_FIN ];
    else if ( l.t_lex == LEX_NUM )
        t = "NUMB";
    else if ( l.t_lex == LEX_ID )
        t = Lex::TID[l.v_lex].get_name ();
    else if ( l.t_lex == POLIZ_LABEL )
        t = "Label";
    else if ( l.t_lex == POLIZ_ADDRESS )
        t = "Addr";
    else if ( l.t_lex == POLIZ_GO )
        t = "!";
    else if ( l.t_lex == POLIZ_FGO )
        t = "!F";
    else if (l.t_lex==LEX_STR)
        t="STR";
    else
        throw l;
    s << '(' << t << ',' << l.v_lex << ");" << "numb of str " << l.nst << endl;
    return s;
}
