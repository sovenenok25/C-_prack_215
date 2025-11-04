//
// Created by soven on 26.03.2023.
//

#ifndef TASK3_CULINDER_H
#define TASK3_CULINDER_H

#include "circle.h"
#include "shape.h"

class conus : public circle {
    double l_;
public: conus (double radius,double l) : l_(l),circle(radius){};
    void print(){};
    double area(){
        return circle::area()+3.14*getr()*l_;
    }
};

#endif //TASK3_CULINDER_H
