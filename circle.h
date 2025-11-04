//
// Created by soven on 25.03.2023.
//

#ifndef TASK3_CIRCLE_H
#define TASK3_CIRCLE_H

#include "shape.h"

class circle: virtual public shape {
    double radius_;
public:
    circle(double radius ):radius_(radius) {};
    void print() {} ;
    double area() override{
        return 3.141592653589793238 * radius_ * radius_;
    }
    ;
     double getr(){
     return radius_;}
};


#endif //TASK3_CIRCLE_H
