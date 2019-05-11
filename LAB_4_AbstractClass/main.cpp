#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>


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
    ~StringObject(){
        cout<<endl<<"To ja destruktor StringObject"<<endl;
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
    ~IntObject(){
        cout<<endl<<"To ja destruktor IntObject"<<endl;
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
        cout<<endl<<"To ja destruktor DoubleObject"<<endl;
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




/**
~list       Destruktor. (destruktor)
back        Zwraca referencję na ostatni element listy. (metoda)
begin       Zwraca iterator wskazujący na pierwszy element listy. (metoda)
clear       Usuwa wszystkie elementy z kontenera. (metoda)
empty       Sprawdza, czy kontener listy jest pusty. (metoda)
end	Zwraca  iterator wskazujący na element będący za ostatnim elementem listy. (metoda)
erase       Usuwa jeden element lub wiele elementów z kontenera listy występujących na podanej pozycji lub w podanym zakresie. (metoda)
front       Zwraca referencję na pierwszy element w kontenerze listy. (metoda)
get_allocator	Zwraca kopię alokatora używanego do tworzenia elementów kontenera listy. (metoda)
insert	Wstawia jeden element lub wiele elementów do kontenera listy na określonej pozycji. (metoda)
max_size	Maksymalna możliwa liczba elementów jaką może przechować kontener listy. (metoda)
pop_back	Usuwa jeden element z kontenera listy, znajdujący się na jego końcu. (metoda)
pop_front	Usuwa jeden element z kontenera znajdujący się na początku listy. (metoda)
push_back	Dodaje nowy element na końcu kontenera listy. (metoda)
push_front	Dodaje nowy element na początek kontenera listy. (metoda)
rbegin      Zwraca iterator odwrotny wskazujący na ostatni element listy. (metoda)
rend        Zwraca iterator odwrotny wskazujący na element występujący bezpośrednio przed pierwszym elementem listy. (metoda)
resize      Ustawia nowy rozmiar kontenera listy. (metoda)
size        Zwraca liczbę elementów przechowywanych przez listę. (metoda)
swap        Kontenery » standard C++ ♦ list zamieniają się posiadanymi danymi. (metoda)
**/


void print_list(list<Object*> objects){
    for( list<Object*>::iterator iter=objects.begin(); iter != objects.end(); ++iter){
        cout<< (*iter)->toString() <<endl;
    }
}

void print_vector(vector<int> int_vector){
    for( vector<int>::iterator iter=int_vector.begin(); iter!=int_vector.end(); ++iter){
        cout<<*iter<<endl;
    }
}

void save2file(const std::list<Object*> objects){
//    fstream plik;
//    plik.open("file_to_list.txt", ios::out);
    ofstream plik("file_to_list.txt");
    if(plik.good()==false) exit(EXIT_FAILURE);

    for( list<Object*>::const_iterator iter=objects.begin(); iter != objects.end(); ++iter){
        plik<<(*iter)->toString()<<endl;
    }
//for(Object* element: objects){};
    plik.close();
}

list<Object*> create_list_of_DoubleObjects(const std::list<Object*> objects){
    list<Object*> double_list;
    for( list<Object*>::const_iterator iter=objects.begin(); iter != objects.end(); ++iter){
        if(((*iter)->whatAmI())==Object::obj_type::DoubleObject){
            double_list.push_back(*iter);
        }
    }
    return double_list;
}

std::vector<int> create_vector_of_IntObjects(const std::list<Object*> objects){
    vector<int> int_vector;
    for( list<Object*>::const_iterator iter=objects.begin(); iter != objects.end(); ++iter){
        if(((*iter)->whatAmI())==Object::obj_type::IntObject){
            IntObject *conversion= dynamic_cast<IntObject*>(*iter);
            int_vector.push_back(conversion->getInt());
        }
    }
    return int_vector;

}

string create_string_from_list(const std::list<Object*> objects){
    string ret;
    for( list<Object*>::const_iterator iter=objects.begin(); iter != objects.end(); ++iter){
        ret+=("\n"+(*iter)->toString());
    }
    return ret;
}

bool fun_sort(Object* arg1, Object* arg2){
    //sortowanie 1:int 2:double 3:string
    return ((*arg1).whatAmI()<(*arg2).whatAmI());
}
void sort_list(std::list<Object*>& objects){
    objects.sort(fun_sort);
}


int main()
{
    list <Object*> objects;

    StringObject s1;
    s1="Ala ma kota";
    StringObject s2;
    s2="Ala nie ma kota";

    IntObject i1;
    i1=25;
    IntObject i2;
    i2=29;

    DoubleObject d1;
    d1=25.52;
    DoubleObject d2;
    d2=29.92;

    objects.push_back(&s1);
    objects.push_back(&s2);
    objects.push_back(&i1);
    objects.push_back(&i2);
    objects.push_back(&d1);
    objects.push_back(&d2);

    cout<<endl<<"PRINT_LIST: "<<endl;
    print_list(objects);

    cout<<endl<<"PRINT_LIST: double "<<endl;
    list<Object*> double_object;
    double_object=create_list_of_DoubleObjects(objects);
    print_list(double_object);


    cout<<endl<<"PRINT_LIST: int "<<endl;
    vector<int> int_vector;
    int_vector=create_vector_of_IntObjects(objects);
    print_vector(int_vector);

    cout<<endl<<"PRINT STRING: "<<endl;
    string str;
    str=create_string_from_list(objects);
    cout<<str<<endl;

    save2file(objects);

    cout<<endl<<"PRINT AFTER SORT: "<<endl;
    sort_list(objects);
    print_list(objects);


    return 0;
}
