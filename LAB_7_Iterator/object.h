#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <regex>
#include <map>
#include <cstdlib>
#include "iterator.h"


using namespace std;



class Object{
public:
    enum obj_type{
        IntObject,
        DoubleObject,
        StringObject,
    };
    //#override
    //virtual enum Object::obj_type whatAmI() const =0;
    virtual obj_type whatAmI() const =0;
    virtual string toString() const=0;
    virtual Object* clone() const=0;
    virtual Object& append(Object&)=0;
    virtual ~Object(){}
};

class StringObject: public Object{
    string text;
public:
    StringObject()=default;
    StringObject(const StringObject& str){
        text=str.toString();
    }
    ~StringObject(){
        cout<<"To ja destruktor StringObject"<<endl<<endl;
    }

    //    StringObject()=default;
    //    StringObject(string str): text(str){}

    enum Object::obj_type whatAmI() const {
        return Object::obj_type::StringObject;
    }
    string toString() const{
        return text;
    }

    StringObject* clone() const{
        StringObject* deepcopy= new StringObject;
        deepcopy->text=this->text;
        return deepcopy;
    }
    StringObject& append( Object& string){
        if(string.whatAmI() != this->whatAmI() ){
            cerr<<"ERROR"<<endl;
        }
        else{
            StringObject* conversion= dynamic_cast<StringObject*>(&string);
            this->text+=conversion->text;
        }
        return *this;
    }

    StringObject& operator=(const string text){
        this->text=text;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const StringObject& str);
    friend std::istream& operator>>(std::istream& is, StringObject& str);
};
std::ostream& operator<<(std::ostream& os, const StringObject& str){
    return os<<str.text;
}
std::istream& operator>>(std::istream& is, StringObject& str){
    is >> str.text;
    return is;
}



class IntObject: public Object{
    int number;
public:
    IntObject()=default;
    IntObject(const IntObject& copy){
        number=copy.number;
    }
    ~IntObject(){
        cout<<"To ja destruktor IntObject"<<endl<<endl;
    }
    enum Object::obj_type whatAmI() const{
        return Object::obj_type::IntObject;
    }
    string toString() const{
        string text;
        text= to_string(number);
        return text;
    }
    IntObject* clone() const{
        IntObject* deepcopy= new IntObject;
        deepcopy->number=this->number;
        return deepcopy;
    }
    IntObject& append( Object& number){
        if(number.whatAmI() != Object::obj_type::IntObject){
            cerr<<"ERROR"<<endl;
        }
        else{
            IntObject* conversion= dynamic_cast<IntObject*>(&number);
            this->number+=conversion->number;
        }
        return *this;
    }
    IntObject& operator=(const int number){
        this->number=number;
        return *this;
    }

    int getInt(){
        return this->number;
    }

    friend std::ostream& operator<<(std::ostream& os, const IntObject& intnmb);
    friend std::istream& operator>>(std::istream& is, IntObject& intnmb);
};
std::ostream& operator<<(std::ostream& os, const IntObject& intnmb){
    return os<<intnmb.number;
}
std::istream& operator>>(std::istream& is, IntObject& intnmb){
    is>>intnmb.number;
    return is;
}



class DoubleObject: public Object{
    double number;
public:
    ~DoubleObject(){
        cout<<"To ja destruktor DoubleObject"<<endl<<endl;
    }
    enum Object::obj_type whatAmI() const{
        return Object::obj_type::DoubleObject;
    }
    string toString() const{
        string text;
        text= to_string(number);
        return text;
    }
    DoubleObject* clone() const{
        DoubleObject* deepcopy= new DoubleObject;
        deepcopy->number=this->number;
        return deepcopy;
    }
    DoubleObject& append( Object& number){
        if(number.whatAmI() != Object::obj_type::DoubleObject){
            cerr<<"ERROR"<<endl;
        }
        else{
            DoubleObject* conversion= dynamic_cast<DoubleObject*>(&number);
            this->number+=conversion->number;
        }
        return *this;
    }
    DoubleObject& operator=(const double number){
        this->number=number;
        return *this;
    }
    double getDouble(){
        return this->number;
    }

    friend std::ostream& operator<<(std::ostream& os, const DoubleObject& doublenmb);
    friend std::istream& operator>>(std::istream& is, DoubleObject& doublenmb);
};
std::ostream& operator<<(std::ostream& os, const DoubleObject& doublenmb){
    return os<<doublenmb.number;
}
std::istream& operator>>(std::istream& is, DoubleObject& doublenmb){
    is>>doublenmb.number;
    return is;
}
#endif // OBJECT_H
