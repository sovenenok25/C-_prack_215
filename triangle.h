//
// Created by soven on 26.03.2023.
//

#ifndef TASK3_TRIANGLE_H
#define TASK3_TRIANGLE_H
# include "shape.h"

class triangle: virtual public shape {
    double base_,height_;
public:
    triangle(double base,double height ) :base_(base),height_(height){};
    void print() {} ;
    double area() override{
        return 0.5*base_*height_;
    } ;
};


#endif //TASK3_TRIANGLE_H
