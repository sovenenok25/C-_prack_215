#include "circle.h"
#include "square.h"
#include "squpewithhole.h"
#include "culinder.h"
#include "mixfigir.h"
#include "triangle.h"


int main (){
    circle  C1(5);
   // square S1(2);
   // squpewithhole q(5,2);
      triangle tr(2,3);
    //  std::cout<< C1.area()<<"\t";
  //  std::cout<< S1.area()<<"\t";
  //  std::cout<< q.area()<<"\t";
  //  conus con(2,5);
 //   std::cout<<con.area()<<"\t";
    mix a1(&tr,&C1);
    mix b1(&tr,&tr);
    b1.print();
    std::cout << "Area: " << b1.area()<<std::endl;
    a1.print();
    std::cout<<a1.area()<<"\t";

}
