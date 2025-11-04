//
// Created by soven on 26.03.2023.
//

#ifndef TASK3_SQUARE_H
#define TASK3_SQUARE_H

#include "shape.h"
#include <iostream>

class square :  public shape {
private:  double side_ ;
    public: square ( double side):side_(side){};
    double area() override{
        return side_*side_;
    };
    void print(){
        std::cout<<side_;
    };
};

#endif //TASK3_SQUARE_H
