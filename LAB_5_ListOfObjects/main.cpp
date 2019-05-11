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



class Node{
    friend class List;
    Node(const Node& node_copy){
        obj=node_copy.obj->clone();
        if(node_copy.next!=nullptr){
            next= new Node(*(node_copy.next));
        }
        else{
            next=nullptr;
        }
    }
public:
    Object* obj;
    Node* next;
    Node(): obj(nullptr), next(nullptr) {}
    ~Node(){
        //   cout<<"\tTO JA DESTRUKTOR NODE"<<endl;
    }

};


class List{
    size_t number_of_elements;
    Node* head;

public:

    List(): number_of_elements(0), head(nullptr) {}

    List(const List& list_copy){
        cout<<endl<<"Konstruktor kopiujacy"<<endl;
        head= new Node(*(list_copy.head));
        number_of_elements=list_copy.number_of_elements;
    }

    List(List&& move){
        cout<<endl<<"Konstruktor przenoszacy"<<endl;
        number_of_elements=move.number_of_elements;
        head=move.head;
        move.head=nullptr;
        move.number_of_elements=0;
    }

    ~List(){
        //cout<<"DESTRUKTOR LIST:"<<endl;
        while(number_of_elements>0){
            pop_back();
        }
    }

    List& operator=(const List& list_copy){
        if(this->head!=list_copy.head){
            cout<<endl<<"Operator kopiujacy"<<endl;
            head= new Node(*(list_copy.head));
            number_of_elements=list_copy.number_of_elements;
        }
        return *this;
    }

    List& operator=(List&& move){
        if(this->head!=move.head){
            cout<<endl<<"Operator przenoszacy"<<endl;
            number_of_elements=move.number_of_elements;
            head=move.head;
            move.head=nullptr;
            move.number_of_elements=0;
        }
        return *this;
    }





    void push_back(Object* obj){
        number_of_elements++;
        Node* push_node= new Node;
        push_node->obj=obj;
        push_node->next=nullptr;
        if( head== nullptr){
            head=push_node;
        }
        else{
            Node* node_ptr=head;
            while(node_ptr->next!=nullptr){
                node_ptr=node_ptr->next;
            }
            node_ptr->next=push_node;
        }
    }

    List& operator+=(Object* obj){
        number_of_elements++;
        Node* push_node= new Node;
        push_node->obj=obj;
        push_node->next=nullptr;
        if( head== nullptr){
            head=push_node;
        }
        else{
            Node* node_ptr=head;
            while(node_ptr->next!=nullptr){
                node_ptr=node_ptr->next;
            }
            node_ptr->next=push_node;
        }
        return *this;
    }

    void pop_back(){
        if(number_of_elements!=0){
            if(number_of_elements==1){
                delete head;
                head=nullptr;
            }
            else{
                Node* node_ptr=head;
                while(node_ptr->next->next!=nullptr){
                    node_ptr=node_ptr->next;
                }
                delete (node_ptr->next);
                node_ptr->next=nullptr;
            }
            number_of_elements--;
        }
    }
    List& operator--(int){
        if(number_of_elements!=0){
            if(number_of_elements==1){
                delete head;
                head=nullptr;
            }
            else{
                Node* node_ptr=head;
                while(node_ptr->next->next!=nullptr){
                    node_ptr=node_ptr->next;
                }
                delete (node_ptr->next);
                node_ptr->next=nullptr;
            }
            number_of_elements--;
        }
        return *this;
    }



    Object& at(size_t index){
        if(index >= number_of_elements){
            cerr<<"INDEX OUT OF RANGE"<<endl;
            exit(EXIT_FAILURE);
        }
        else{
            Node* node_ptr=head;
            for (size_t i=0; i<index; i++){
                node_ptr=node_ptr->next;
            }
            return *(node_ptr->obj);
        }
    }

    Object& operator[](size_t index){
        if(index >= number_of_elements){
            cerr<<"INDEX OUT OF RANGE"<<endl;
            exit(EXIT_FAILURE);
        }
        else{
            Node* node_ptr=head;
            for (size_t i=0; i<index; i++){
                node_ptr=node_ptr->next;
            }
            return *(node_ptr->obj);
        }
    }


    size_t size(){
        return number_of_elements;
    }
    operator size_t(){
        return number_of_elements;
    }

};



int main(){

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


    List l;

    cout<<l.size()<<endl;
    l+=(&s1);
    l+=(&s2);
    l+=(&i1);
    l+=(&i2);
    l+=(&d1);
    l+=(&d2);
    l.pop_back();
    l.push_back(&d2);
    l--;


    List l1(l);
    cout<<l.size()<<endl;

    List l2(move(l1));
    cout<<l1.size()<<endl;


    cout<<endl<<"LISTA L2"<<endl;
    for( size_t i=0 ; i< l2.size();i++ ){
        cout<<l2.at(i).toString()<<endl;
    }
    cout<<endl<<"LISTA L"<<endl;
    for( size_t i=0 ; i< l.size();i++ ){
        cout<<l[i].toString()<<endl;
    }
    cout<<"L.size()"<<l.size()<<endl;


}
