#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <regex>
#include <map>
#include <cstdlib>
#include <list>
#include <set>
#include <iterator>



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
    virtual bool operator<(const Object&) const =0;
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

    bool operator<(const Object& right) const {
        bool ret;
        if(right.whatAmI()!=this->whatAmI()) ret=false;
        else{
            auto so=dynamic_cast<const StringObject*>(&right);
            ret= (this->toString()) < (so->toString());
        }
        return ret;
    }


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
    bool operator<(const Object& right) const {
        bool ret;
        if(right.whatAmI()==Object::obj_type::StringObject) ret=true;
        else if(right.whatAmI()==Object::obj_type::DoubleObject) ret=false;
        else{
            auto io=dynamic_cast<const IntObject*>(&right);
            ret= this->getInt() < io->getInt();
        }
        return ret;
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

    int getInt() const{
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

    bool operator<(const Object& right) const {
        bool ret;
        if(right.whatAmI()==Object::obj_type::StringObject) ret=true;
        else if(right.whatAmI()==Object::obj_type::IntObject) ret=true;
        else{
            auto double_o=dynamic_cast<const DoubleObject*>(&right);
            ret= this->getDouble() < double_o->getDouble();
        }
        return ret;
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
    double getDouble()const{
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

    List(): number_of_elements(0), head(nullptr) {
        srand(time(NULL));
    }

    List(const List& list_copy){
        srand(time(NULL));
        cout<<endl<<"Konstruktor kopiujacy"<<endl;
        head= new Node(*(list_copy.head));
        number_of_elements=list_copy.number_of_elements;
    }

    List(List&& move){
        srand(time(NULL));
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

    Object& operator[](size_t index) const{
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


    size_t size() const {
        return number_of_elements;
    }
    operator size_t(){
        return number_of_elements;
    }

    bool operator&&(const Object& obj){
        bool ret=0;
        for (size_t i=0; i<number_of_elements; i++){
            if((*this)[i].toString()==obj.toString()){
                ret=true;
            }
        }
        return  ret;
    }


    Object* operator->(){
        string empty_list="PUSTA LISTA!";
        if(number_of_elements==0) throw empty_list;
        size_t index=static_cast<size_t>((rand() % static_cast<int>(number_of_elements)));
        return &((*this)[index]);
    }



    class iterator{
        Node* itr;

    public:
        iterator(): itr(nullptr){}
        iterator(Node* copy): itr(copy){}

        Object*& operator*() const{
            if(!itr) throw "Invalid iteretor derference";
            return itr->obj;
        }

        const iterator& operator++(){ //preinkrementacja
            if(!itr) throw "Out-of-bounds iterator incerement";
            itr= itr->next;
            return *this;
        }

//        iterator operator++(int){ //postinkrementacja
//            if(!itr) throw "Out-of-bounds iterator incerement";
//            iterator tmp(*this);
//            itr= itr->next;
//            return tmp;
//        }

        bool operator!=(const iterator& it) const {
            return this->itr!=it.itr;
        }
    };

    iterator begin()const{
        //return iterator(head);
        //return head;
        return {head};
    }

    iterator end()const{
        //return iterator();
        return {}; //wolanie konstrukotra domyslnego
    }



};








bool isMail(const Object* obj){
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return obj->whatAmI()==Object::obj_type::StringObject? regex_match(obj->toString(),pattern): false;
}

List getElementsPassingPredicate(const List& myList, bool(*predicate)(const Object*)){
    List ret;
    for(size_t i=0; i< myList.size() ; i++){
        if(predicate(&(myList[i]))==true){
            ret+= &myList[i];
        }
    }
    return ret;
}

enum class Month{January,
                 February,
                 March,
                 April,
                 May,
                 June,
                 July,
                 August,
                 September,
                 October,
                 November,
                 December,
                };

const map<Month, string> months{{Month::January,"January"},
                                {Month::February,"February"},
                                {Month::March,"March"},
                                {Month::April,"April"},
                                {Month::May,"May"},
                                {Month::June,"June"},
                                {Month::July,"July"},
                                {Month::August,"August"},
                                {Month::September,"September"},
                                {Month::October,"October"},
                                {Month::November,"November"},
                                {Month::December,"December"}};

pair<IntObject, StringObject> getMonthNumberAndText(Month month){
    IntObject number;
    number=static_cast<int>(month)+1;
    StringObject name;
    name= months.at(month);
    return make_pair(number,name);
}

struct Predicate{
    virtual  bool operator()(Object*) const =0;
    virtual ~Predicate(){}
};

struct IsGreaterThan{
    int number;
    IsGreaterThan(int nmb):number(nmb){}
    bool operator()(Object* obj){
        bool ret=0;
        if(obj->whatAmI()== Object::obj_type::StringObject){
            ret=0;
        }
        else if(obj->whatAmI()== Object::obj_type::IntObject){
            IntObject* object= dynamic_cast<IntObject*>(obj);
            ret=(object->getInt()>number? true : false);
        }
        else if(obj->whatAmI()== Object::obj_type::DoubleObject){
            DoubleObject* object= dynamic_cast<DoubleObject*>(obj);
            ret=(object->getDouble()>number? true : false);
        }
        return ret;
    }
};

struct isMail: Predicate{
    bool operator()(Object* obj) const override{
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(obj->toString(),pattern);
    }
};

size_t countElementsPassingPredicate(const List& myList, const Predicate& predicate){
    size_t number=0;
    for(size_t i=0; i< myList.size() ; i++){
        if(predicate(&(myList[i]))==true){
            number++;
        }
    }
    return number;
}



class file_iter{
public:
    ifstream ifstream_file;

    file_iter(const char* filename, ios_base::openmode mode = ios_base::in): ifstream_file(filename, mode){}
    file_iter(ifstream& str): ifstream_file(move(str)){
        ifstream_file.clear();
        ifstream_file.seekg(0);
    }

    class iterator{
        ifstream* file;
        string line;
    public:
        iterator(): file(nullptr){
            line[0]=EOF;
        }
        iterator(ifstream* copy): file(copy){
            if(!(getline(*file,line))) line[0]=EOF;
        }


        string operator*(){
            if(line[0]==EOF) throw "Invalid iteretor derference";
            return line;
        }

        const iterator& operator++(){ //preinkrementacja
            if(line[0]==EOF) throw "Out-of-bounds iterator incerement";
            if(!(getline(*file, line))) line[0]=EOF;
            return *this;
        }

        bool operator!=(const iterator& it) const {
            return this->line[0]!= it.line[0];
        }
    };


    iterator begin(){
        ifstream_file.clear();
        ifstream_file.seekg(0);
        iterator itr(&ifstream_file);
        return itr;
    }

    iterator end()const{
        iterator end;
        return end;
    }

    ~file_iter(){
        ifstream_file.close();
    }
};

ifstream& File2File_copy(ifstream& from, string name_of_copy="default_copy"){
    file_iter iter(from);
    ofstream to(name_of_copy+".txt", ios::out);
    for(auto it: iter){
        to<<it<<endl;
    }
    to.close();
    return from;
}


int main(){

    StringObject s1;
    s1="xxx.xxx@xxx.xxx";
    StringObject s2;
    s2="Ala nie ma kota";
    IntObject i1;
    i1=0;
    IntObject i2;
    i2=29;

    DoubleObject d1;
    d1=25.52;
    DoubleObject d2;
    d2=29.92;

    List l1;
    try{
        cout<<l1->toString()<<endl;
    }
    catch (string x){
        cout<<"Wyjatek: "<<x<<endl;
    }

    l1.push_back(&s1);
    l1.push_back(&s2);
    l1.push_back(&i1);
    l1.push_back(&i2);
    l1.push_back(&d1);




    cout<<endl<<"#LIST ITERATOR operator: "<<endl;
    try {
        for(auto it=l1.begin(); it!=l1.end(); ++it){
            cout<<(*it)->toString()<<endl;
        }
        for(auto &wsk : l1){
            cout<<(*wsk).toString()<<endl;
        }

        file_iter f1("test.txt");

        for(auto it : f1){
            cout<<it<<endl;
        }
        File2File_copy(f1.ifstream_file);

    }
    catch (...) {
        cout<<"ITERAOR-WYJATEK";

    }





    cout<<endl<<"#Overload AND operator: "<<endl;
    cout<< (l1&&s1)<<endl;
    cout<< (l1&&s2)<<endl;
    cout<< (l1&&i1)<<endl;
    cout<< (l1&&i2)<<endl;
    cout<< (l1&&d1)<<endl;
    cout<< (l1&&d2)<<endl;




    cout<<endl<<"#getElementsPassingPredicate: "<<endl;
    List l2=getElementsPassingPredicate(l1, isMail);
    for(size_t i=0; i< l2.size(); i++){
        cout<<l2[i].toString()<<endl;
    }



    cout<<endl<<"#countElementsPassingPredicate: "<<endl;
    struct isMail im;
    cout<<countElementsPassingPredicate(l1,im)<<endl;




    cout<<endl<<"#getMonthNumberAndText: "<<endl;
    auto x=getMonthNumberAndText(Month::December);
    cout<<x.first<<" "<<x.second<<endl;




    cout<<endl<<"#IsGreaterThan: "<<endl;
    IsGreaterThan igt(1);
    cout<<igt(&s1)<<endl;
    cout<<igt(&i1)<<endl;
    cout<<igt(&i2)<<endl;
    cout<<igt(&d1)<<endl;



    cout<<endl<<"#LOSOWANIE: "<<endl;
    cout<<l1->toString()<<endl;
    cout<<l1->toString()<<endl;
    cout<<l1->toString()<<endl;
    cout<<l1->toString()<<endl;
    cout<<l1->toString()<<endl;
    cout<<l1->toString()<<endl<<endl<<endl<<endl;



    cout<<endl<<"#SET: "<<endl;
    std::set<Object*> std_set;
    std_set.insert(&i1);
    std_set.insert(&i2);
    std_set.insert(&s1);
    std_set.insert(&s2);
    std_set.insert(&d1);
    std_set.insert(&d2);

    for(auto it: std_set){
        cout<<(*it).toString()<<endl;
    }


    cout<<endl<<"#WYSWIETLANIE WEKTORA z wykorzystaniem std::copy i ostream_iterator: "<<endl;
    vector<int> vect;
    for(int i=0; i<11; i++){
        vect.push_back(i);
    }
    std::copy(vect.begin(), vect.end(), ostream_iterator<int>(std::cout," "));
    ostream_iterator<int> itr (std::cout, " ");
    std::copy(vect.begin(), vect.end(), itr);

    cout<<endl<<endl<<endl;









    std::map<int,string> mymap;
    mymap[1]="ala";
    mymap.insert({2,"ma"});

    for(auto it: mymap){
        cout<<it.first<<" "<<it.second<<endl;
    }







}
