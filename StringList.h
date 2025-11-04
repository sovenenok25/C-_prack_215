//
// Created by  on 28.02.23.
//

#ifndef CPP_STRINGLIST_H
#define CPP_STRINGLIST_H

#include <iostream>
#include <cstring>
#include <memory>
class StringList {
public:
    explicit StringList(const char*) noexcept;
    StringList() noexcept;
    StringList(const StringList& other) noexcept;
    ~StringList();
     operator bool () ;
    StringList operator+(const StringList& other)const noexcept ;
    friend StringList& operator!(StringList& list);
    StringList& operator+(const char* el) noexcept;
    StringList& operator-(const char* el) noexcept;
    StringList& operator+=(const StringList& other) noexcept;
    StringList& operator=(const StringList& other) noexcept;
    friend StringList& operator+(const char* el,StringList& list) noexcept;
    char* operator[](int i) const;
   // void swap(StringList&& );
    explicit operator char*() noexcept;
    int length() const noexcept;
    friend std::ostream& operator <<(std::ostream& out, const StringList& other );
private:
    struct Node{
        Node(const char* el){
            value = new char[strlen(el)];
            strcpy(this->value,el);
            next = prev = nullptr;
        }
        Node(const Node* other){
            //next = prev = nullptr;
            value = new char[strlen(other->value)];
            strcpy(this->value,other->value);
        }
        char* value;
        Node* next;
        Node* prev;
        ~Node(){
            delete[] value;
        }
    };
    int length_;
    Node* head;
    Node* tail;

   // void swap1(StringList &other);
};

;

#endif //CPP_STRINGLIST_H

