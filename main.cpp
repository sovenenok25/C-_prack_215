
#include <iostream>

#include "syntax.h"

int main () {
    Scanner scan1("test.txt");
    try {
        Lex lex1;
        int i = 1;
        lex1 = scan1.get_lex();
        while (lex1.get_type() != LEX_EOF) {
//           std::cout << lex1 <<std::endl;
            lex1 = scan1.get_lex();
            i++;
        }
    }
  /*  catch (char str) {
        std::cout << "mistake" << std::endl;
        std::cout << str << std::endl;
    }*/
    catch (...) {
        std::cout << "..." << std::endl;
    }

    // Проверка работы лексич+семантич анализа и генерации полиза
    Parser pars1("test.txt");
    try {
        pars1.popul();
        pars1.analyze();
        for (int i = 0; i < pars1.poliz.size(); i++) {
            std::cout << pars1.poliz[i] << std::endl;
            //  pars1.prog.print();}
        }
    }
//std::cout<<"mistake"<<std::endl;
    catch (Lex l) {
        std::cout << "mistake" << std::endl;
        std::cout << l << std::endl;
    }
    catch (...) {
        std::cout << "mistake";
        std::cout << "..." << std::endl;
    }
}
