#include <iostream>
#include "StringList.h"

StringList f() {
    char buffer[] = "1235616";
    StringList s(buffer);
    buffer[0] = '7';
    return s;
}

int main() {
    StringList s1("163641");
    StringList s2("5875");
    StringList s3;
    //s1=s2;
    std::cout<<s1[0]<<std::endl;
    std::cout<<"----------------"<<!s1;
    std::cout<<"----------------"<<!s3;
  //  std::cout<< &s1<<"\t";
    // std::cout<<s1+s2<<"\t";
   // std::cout <<(s1+=s2);
  /* int i=3;
   (char* )i;*/
}