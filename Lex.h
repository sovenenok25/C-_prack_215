//
// Created by soven on 07.05.2023.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

enum type_of_lex {
    LEX_NULL,                                                                                   /* 0*/
    LEX_AND, LEX_NOT, LEX_OR, LEX_ELSE, LEX_IF, LEX_INT,        /*6*/
    LEX_PROGRAM, LEX_READ, LEX_STRING, LEX_WHILE, LEX_WRITE,  /*11*/
    LEX_FIN,  LEX_EOF,                                                                                  /*12*/
    LEX_LBRACE, LEX_RBRACE, LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ, LEX_LSS,   /*22*/
    LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_MARK,             /*30*/
    LEX_NUM,
    LEX_STR,
    LEX_BOOL,                                                                                    /*31*/
    LEX_ID,                                                                                     /*32*/
    POLIZ_LABEL,                                                                                /*33*/
    POLIZ_ADDRESS,                                                                              /*34*/
    POLIZ_GO,                                                                                   /*35*/
    POLIZ_FGO                                                                                   /*36*/
};

/////////////////////////  Класс Lex  //////////////////////////

class Ident {
    string      name;
    bool        declare;
    type_of_lex type;
    bool        assign;
    int          value;
    string value_s;
public:
    Ident() {
        declare = false;
        assign  = false;
    }
    bool operator== ( const string& s ) const {
        return name == s;
    }
    Ident ( const string n ) {
        name    = n;
        declare = false;
        assign  = false;
    }
    string get_name () const {
        return name;
    }
    bool get_declare () const {
        return declare;
    }
    void put_declare () {
        declare   = true;
    }
    type_of_lex get_type ();
    void put_type ( type_of_lex t ) {
        type      = t;
    }
    bool get_assign () const {
        return assign;
    }
    void put_assign () {
        assign    = true;
    }
    int  get_value () const {
        return value;
    }
    string  get_value_s () const {
        return value_s;
    }
    void put_value ( int v ) {
        value     = v;
    }
    void put_value ( string sss ) {
        value_s     = sss;
    }
};

class Lex {
    string s_lex;
    int           v_lex;
public:
    type_of_lex   t_lex;
    int nst;
    static int numb_of_str;
    Lex ( type_of_lex t = LEX_NULL, int v=0, string sss="", int n=numb_of_str): t_lex (t), v_lex (v), s_lex (sss), nst(n)  { }
    type_of_lex  get_type () const {
        return t_lex;
    }
    int get_value () const {
        return v_lex;
    }
    string get_value_s () const {
        return s_lex;
    }
    friend ostream & operator<< ( ostream &s, Lex& l );
    void operator= (Lex lexx)
    {
        (*this).t_lex=lexx.get_type();
        (*this).s_lex=lexx.get_value_s();
        (*this).v_lex=lexx.get_value();
        (*this).nst=lexx.nst;
    }
    static vector<Ident> TID;
};
// Таблица идентификаторов TID
/////////////////////  Класс Ident  ////////////////////////////

//////////////////////  TID  ///////////////////////
// Занести лексему в таблицу TID. Если она уже описана, вернуть ее номер
int put ( const string & buf );

class Scanner {
    FILE * fp;
    char   c;
    int look ( const string buf, const char ** list ) {
        int i = 0;
        while ( list[i] ) {
            if ( buf == list[i] )
                return i;
            ++i;
        }
        return 0;
    }
    void gc () {
        c = fgetc (fp);
    }
public:
    static const char * TW [], * TD [];
    Scanner ( const char *program):
            fp(fopen ( program, "r" ))
    {
        if ( !(fp) )
            throw  "can’t open file\0" ;
    }
    Scanner() { }
    Lex get_lex ();
};

template <class T, class T_EL>
void from_st ( T & st, T_EL & i ) {
    i = st.top(); st.pop();
}


