//
// Created by soven on 05.04.2023.
//

#ifndef TASK3_MIXFIGIR_H
#define TASK3_MIXFIGIR_H
#include "shape.h"
#include "triangle.h"


class mix: public shape {
    shape* shape1_;
    shape* shape2_;
public:
    mix(shape* shape1, shape* shape2) : shape1_(shape1), shape2_(shape2) {}
    double area() override {
        double area1 = shape1_->area();
        double area2 = shape2_->area();
        return area1 > area2 ? area1 : area2;
    }
    void print() override {
        std::cout << "Mix shape with maximum area: \n";
        if ((shape1_->area() == shape2_->area()))
            shape1_->print();
        if (shape1_->area() > shape2_->area()) {
            shape1_->print();
        }
        else {
            shape2_->print();
        }
    }
};


#endif //TASK3_MIXFIGIR_H
