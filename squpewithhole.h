//
// Created by soven on 26.03.2023.
//

#ifndef TASK3_SQUPEWITHHOLE_H
#define TASK3_SQUPEWITHHOLE_H

#include "shape.h"
#include "circle.h"
#include "square.h"

class squpewithhole :  public square {
        circle hole_;
public:squpewithhole (double side,double radidehole):square (side),hole_(radidehole){};
void print(){} ;
        double area() {
            return square::area()-hole_.area();
        }
};

#endif //TASK3_SQUPEWITHHOLE_H
