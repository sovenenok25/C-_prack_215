//
// Created by  on 28.02.23.
//
#include "StringList.h"
#include <cstring>
#include <bits/stdc++.h>
#include <typeinfo>

StringList::StringList(const char * el) noexcept{
    head = new Node(el);
    tail = head;
    length_ = 1;
}

StringList::~StringList(){
    if (length_ <= 1) {
        delete tail;
    } else {
        Node* cur;
        for (cur = head->next; cur->next != nullptr; cur = cur->next) {
            delete cur->prev;
        }
        delete cur->prev;
        delete cur;
    }
}

StringList& StringList::operator+=(const StringList &other) noexcept{
    for (Node* cur = other.head; cur != nullptr;cur = cur->next) {
        if (this->head == nullptr){
            head = new Node(cur);
            tail = head;
        } else {
            tail->next = new Node(cur);
            tail->next->prev = tail;
            tail = tail->next;
            if (length_ == 1) {
                head->next = tail;
            }
        }
        length_++;
    }
    return *this;
}

StringList::StringList() noexcept{
    this->tail = this->head = nullptr;
    this->length_ = 0;
}

StringList::StringList(const StringList &other) noexcept{
    this->head = tail = nullptr;
    this->length_ = 0;
    *this+=other;
}

int StringList::length() const noexcept{
    return length_;
}



/*void StringList:: swap(StringList&& tempObj)
{// StringList a("111111");
       // const char * b= (char *) other[i].get();
      auto buf=tempObj.getValue();
      tempObj.setValue(this->head);
       this->setValue(buf);
       // std::cout << typeid(this[i]).name()   << std::endl;
       // std::cout << typeid(other).name()   << std::endl;
      //  std::cout<< list[i]<<"\t";
      //  std::cout<<*this<<"\t";
       // std::cout<< a[i]<<"\t";
       // std::swap(b,a);
       // std::cout <<b<<"\t";
       // std::cout <<&a <<"\t";
// (char *) b;
}*/

StringList &StringList::operator=(const StringList &other)  noexcept{
    if (this == &other){
        return *this;
    }
    this->~StringList();
    this->head = this->tail = nullptr;
    this->length_ = 0;
    *this+=other;
    return *this;
}

StringList:: operator bool ( )
{ StringList a("0");
    if (*this == a)
        return true;
    return false;
}

 StringList& operator!( StringList& list) {
         if (list.length_ == 0) {
             StringList a("000");
             list = a;
         } else {
             StringList a("111");
             list = a;
         }
         // std:: cout<< list;}
         return list;
     }
     StringList StringList::operator+(const StringList &other) const noexcept {
         auto res = *this;
         res += other;
         return res;
     }

     StringList &StringList::operator+(const char *el) noexcept {
         *this += StringList(el);
         return *this;
     }

     char *StringList::operator[](int i) const {
         if (i >= length_) {
             throw std::range_error("out of range");
         }
         int j = 0;
         Node *cur;
         for (cur = this->head; j < i; j++, cur = cur->next) {}
         char *res = new char[strlen(cur->value)];
         strcpy(res, cur->value);
         //std::cout<<res<<"\t";
         //delete[] cur;
         return res;
     }

     StringList &operator+(const char *el, StringList &list) noexcept {
         auto *node = new StringList::Node(el);
         if (list.length_ != 0) {
             node->next = list.head;
             list.head->prev = node;
             list.head = node;
         } else {
             list.head = list.tail = node;
             list.head->prev = nullptr;
             list.head->next = nullptr;
             list.tail->next = nullptr;
             list.tail->prev = nullptr;
         }
         list.length_++;
         return list;
     }

     StringList &StringList::operator-(const char *el) noexcept {
         Node *cur;
         for (cur = this->head; cur != nullptr && strcmp(cur->value, el) != 0; cur = cur->next) {}
         if (cur != nullptr) {
             cur->prev->next = cur->next;
             cur->next->prev = cur->prev;
             delete cur;
             length_--;
         }
         return *this;
     }

     std::ostream &operator<<(std::ostream &out, const StringList &other) {
         for (int i = 0; i < other.length_; i++) {
             out << other[i] << "\n";;
         }
         return out;
     }

     StringList::operator char *()
     noexcept {
             int N = 0;
             for (auto cur =head; cur != nullptr;cur = cur->next){
                 N += strlen(cur->value);
             }
             N+=length_;
             char* res = new char[N];
             res[0] = 0;
             for (auto cur =head; cur != nullptr;cur = cur->next){
                 strcat(res, cur->value);
                 strcat(res, "\n");
             }
             return res;
     }


