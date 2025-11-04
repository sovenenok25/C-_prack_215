//
// Created by soven on 09.05.2023.
//
#include "syntax.h"
#include <string>


void Parser::analyze () {
    gl ();
    P ();
    for ( Lex l : poliz )
        cout << l;
    cout << endl << "Yes!!!" << endl;
}

void Parser::P () {
    if ( c_type == LEX_PROGRAM ) {
        gl ();
    }
    else
        throw curr_lex;
    B ();
}

/*void Parser::D1 () {
    if ( c_type == LEX_VAR ) {
        gl ();
        D ();
        while ( c_type == LEX_COMMA ) {
            gl ();
            D ();
        }
    }
    else
        throw curr_lex;
} */

void Parser::D (type_of_lex type) {
    if ( c_type != LEX_ID )
        throw curr_lex;
    else {
        st_int.push ( c_val );
        int i=c_val;
        gl ();
        if ( c_type == LEX_ASSIGN )
        {
            gl();
            if ((type==LEX_INT)&&(c_type!=LEX_NUM))
                throw curr_lex;
            if ((type==LEX_STRING)&&(c_type!=LEX_STR))
                throw curr_lex;
            if (type==LEX_INT)
            {
                Lex::TID[i].put_value (c_val);
                Lex::TID[i].put_assign();
            }
            else
            {
                Lex::TID[i].put_value (s_val);
                Lex::TID[i].put_assign();
            }
            gl();
        }
        while ( c_type == LEX_COMMA )
        {
            gl ();
            if ( c_type != LEX_ID )
                throw curr_lex;
            else {
                st_int.push ( c_val );
                int j=c_val;
                gl ();
                if ( c_type == LEX_ASSIGN )
                {
                    gl();
                    if ((type==LEX_INT)&&(c_type!=LEX_NUM))
                        throw curr_lex;
                    if ((type==LEX_STRING)&&(c_type!=LEX_STR))
                        throw curr_lex;
                    if (type==LEX_INT)
                    {
                        Lex::TID[j].put_value (c_val);
                        Lex::TID[j].put_assign();
                    }
                    else
                    {
                        Lex::TID[j].put_value(s_val);
                        Lex::TID[j].put_assign();
                    }
                    gl();
                }
            }
        }
        if ( c_type != LEX_SEMICOLON )
            throw curr_lex;
        else {
            if ( type==LEX_INT ) {
                dec ( LEX_INT );
                //gl ();
            }
            else
            if ( type == LEX_STRING ) {
                dec ( LEX_STRING );
                //gl ();
            }
            else
                throw curr_lex;
        }
    }
}

void Parser::B ()
{
    if ( c_type == LEX_LBRACE )
    {
        gl ();
        S ();
        while ( c_type == LEX_SEMICOLON ) {
            gl ();
            S ();
        }
    }
    else
        throw curr_lex;
    if ( c_type != LEX_RBRACE )
        throw curr_lex;
}

void Parser::S () {
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_INT)
    {
        gl();
        D(LEX_INT);
    }
    if (c_type==LEX_STRING)
    {
        gl();
        D(LEX_STRING);
    }
    if ( c_type == LEX_IF ) {
        gl ();
        if (c_type==LEX_LPAREN)
        {
            gl();
            E ();
        }
        else
            throw curr_lex;
        eq_bool ();
        if (c_type!=LEX_RPAREN)
            throw curr_lex;
        else
            gl();
        pl2 = poliz.size();
        poliz.push_back ( Lex() );
        poliz.push_back ( Lex(POLIZ_FGO) );
        if ( c_type == LEX_LBRACE )
            B();
        else
        {
            S ();
        }
        pl3 = poliz.size ();
        poliz.push_back ( Lex () );
        poliz.push_back ( Lex ( POLIZ_GO ) );
        poliz[pl2] = Lex ( POLIZ_LABEL, poliz.size() );
        gl();
        if ( c_type == LEX_ELSE ) {
            gl();
            if ( c_type == LEX_LBRACE )
                B();
            else
            {
                S ();
            }
        }
        /*else
            throw curr_lex; */
        poliz[pl3] = Lex ( POLIZ_LABEL, poliz.size() );

        S();
    }//end if
    else if ( c_type == LEX_WHILE ) {
        pl0 = poliz.size ();
        gl ();
        E ();
        eq_bool ();
        pl1 = poliz.size ();
        poliz.push_back ( Lex () );
        poliz.push_back ( Lex (POLIZ_FGO) );
        /* if ( c_type == LEX_DO ) {
            gl();
            S(); */
        //poliz.push_back ( Lex ( POLIZ_LABEL, pl0 ) );
        //poliz.push_back ( Lex ( POLIZ_GO) );
        //poliz[pl1] = Lex ( POLIZ_LABEL, poliz.size() );


        if ( c_type == LEX_LBRACE )
            B();
        else
        {
            S ();
        }
        gl();
        poliz.push_back ( Lex ( POLIZ_LABEL, pl0 ) );
        poliz.push_back ( Lex ( POLIZ_GO) );
        poliz[pl1] = Lex ( POLIZ_LABEL, poliz.size() );
        S();
    }
        /*else
            throw curr_lex; */
        //end while
    else if ( c_type == LEX_READ ) {
        gl ();
        if ( c_type == LEX_LPAREN ) {
            gl ();
            if ( c_type == LEX_ID ) {
                check_id_in_read ();
                poliz.push_back ( Lex( POLIZ_ADDRESS, c_val) );
                gl();
            }
            else
                throw curr_lex;
            if ( c_type == LEX_RPAREN ) {
                gl ();
                poliz.push_back ( Lex (LEX_READ) );
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }//end read
    else if ( c_type == LEX_WRITE ) {
        gl ();
        if ( c_type == LEX_LPAREN ) {
            gl ();
            E ();
            while (c_type==LEX_COMMA)
            {
                poliz.push_back ( Lex ( LEX_WRITE ) );
                gl();
                E();
            }
            if ( c_type == LEX_RPAREN ) {
                gl ();
                poliz.push_back ( Lex ( LEX_WRITE ) );
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }//end write */
    else if ( c_type == LEX_ID ) {
        check_id ();
        poliz.push_back (Lex ( POLIZ_ADDRESS, c_val ) );
        gl();
        if ( c_type == LEX_ASSIGN ) {
            gl ();
            E ();
            eq_type ();
            poliz.push_back ( Lex ( LEX_ASSIGN ) );
        }
        else
            throw curr_lex;
    }//assign-end
    //else
    //B();
    //B();
}

void Parser::E () {
    /*if (c_type!=LEX_LPAREN)
        throw curr_lex;
    gl(); */
    E1 ();
    if ( c_type == LEX_EQ  || c_type == LEX_LSS || c_type == LEX_GTR ||
         c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ ) {
        st_lex.push ( c_type );
        gl ();
        E1 ();
        check_op ();
    }
    /*if (c_type!=LEX_RPAREN)
		throw curr_lex;
	gl(); */
}

void Parser::E1 () {
    T ();
    while ( c_type == LEX_PLUS || c_type == LEX_MINUS || c_type==LEX_OR) {
        st_lex.push ( c_type );
        gl ();
        T ();
        check_op ();
    }
}

void Parser::T () {
    F ();
    while ( c_type == LEX_TIMES || c_type == LEX_SLASH || c_type==LEX_AND) {
        st_lex.push ( c_type );
        gl ();
        F ();
        check_op ();
    }
}

void Parser::F () {
    if ( c_type == LEX_ID ) {
        check_id ();
        poliz.push_back ( Lex ( LEX_ID, c_val ) );
        gl ();
    }
    else if ( c_type == LEX_NUM ) {
        st_lex.push ( LEX_INT );
        poliz.push_back ( curr_lex );
        gl ();
    }
        /*else if ( c_type == LEX_TRUE ) {
            st_lex.push ( LEX_BOOL );
            poliz.push_back ( Lex (LEX_TRUE, 1) );
            gl ();
        }
        else if ( c_type == LEX_FALSE) {
            st_lex.push ( LEX_BOOL );
            poliz.push_back ( Lex (LEX_FALSE, 0) );
            gl ();
        } */
    else if ( c_type == LEX_STR ) {
        st_lex.push ( LEX_STRING );
        poliz.push_back ( curr_lex );
        gl ();
    }
    else if ( c_type == LEX_NOT ) {
        gl ();
        F ();
        check_not ();
    }
    else if ( c_type == LEX_LPAREN ) {
        gl ();
        E ();
        if ( c_type == LEX_RPAREN)
            gl ();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

////////////////////////////////////////////////////////////////

void Parser::dec ( type_of_lex type ) {
    int i;
    while ( !st_int.empty () ) {
        from_st ( st_int, i );
        if ( Lex::TID[i].get_declare () )
        {
            cout << "Error in str " << Lex::numb_of_str << endl;
            throw "twice";
        }
        else {
            Lex::TID[i].put_declare ();
            Lex::TID[i].put_type ( type );
        }
    }
}

void Parser::check_id () {
    if ( Lex::TID[c_val].get_declare() )
    {
        st_lex.push ( Lex::TID[c_val].get_type () );
    }
    else
    {
        cout << "Error in str " << Lex::numb_of_str << endl;
        throw "not declared";
    }
}

void Parser::check_op () {
    type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;

    from_st ( st_lex, t2 );
    from_st ( st_lex, op );
    from_st ( st_lex, t1 );

    if (op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH )
        r = LEX_INT;
    if (op == LEX_PLUS)
        if (t1==LEX_STRING)
        {
            r=LEX_STRING;
            t=LEX_STRING;
        }
        else
            r=LEX_INT;
    if ( op == LEX_OR || op == LEX_AND )
        t = LEX_BOOL;
    if (op == LEX_EQ  || op == LEX_LSS || op == LEX_GTR || op==LEX_NEQ)
        if (t1==LEX_STRING)
            t=LEX_STRING;
    if ( t1 == t2  &&  t1 == t )
        st_lex.push (r);
    else
    {
        cout << "Error in str " << Lex::numb_of_str << endl;
        throw "wrong types are in operation";
    }
    poliz.push_back (Lex(op));
}

void Parser::check_not () {
    if (st_lex.top() != LEX_BOOL)
    {
        cout << "Error in str " << Lex::numb_of_str << endl;
        throw "wrong type is in not";
    }
    else
        poliz.push_back ( Lex (LEX_NOT) );
}

void Parser::eq_type () {
    type_of_lex t;
    from_st ( st_lex, t );
    if ( t != st_lex.top () )
    {
        cout << "Error in str " << Lex::numb_of_str << endl;
        throw "wrong types are in :=";
    }
    st_lex.pop();
}

void Parser::eq_bool () {
    if ( st_lex.top () != LEX_BOOL )
    {
        cout << "Error in str " << Lex::numb_of_str << endl;
        throw "expression is not boolean";
    }
    st_lex.pop ();
}

void Parser::check_id_in_read () {
    if ( !Lex::TID [c_val].get_declare() )
    {
        cout << "Error in id " <<Lex::TID [c_val].get_name() << " in str " << Lex::numb_of_str << endl;
        throw "not declared";
    }
}
