#include <iostream>
#include <map>
#include <set>
using namespace std;


class vector{
    int* tab;
    int size;
    int capacity;

public:
    vector(): tab(nullptr), size(0), capacity(0){}
    vector(vector& copy): size(copy.size), capacity(copy.size){
        tab=new int[size];
        for(int i=0; i<size; i++){
            tab[i]=copy.tab[i];
        }
    }
    ~vector(){
        delete [] tab;
    }

    void isEnough(){
        if(size==capacity){
            int* temp=tab;
            ++capacity;
            tab= new int[capacity];
            for(int i=0; i<(capacity-1); ++i){
                tab[i]=temp[i];
            }
            delete [] temp;

        }
    }

    int& insert(int number){
        isEnough();
        tab[size]=number;
        size++;

       return tab[size-1];
    }

    int& get(int index){
        return tab[index];
    }

    void print(){
        for(int i=0; i<size; i++){
            cout<<get(i)<<" ";
        }
    }




    class Iterator{
        int number_of_element;
        int size;
        int* number;
    public:

        Iterator(int* number, int size): number(number), size(size), number_of_element(0){}

        int& operator*() const{
            if(number_of_element==size) throw "ERROR";
            return *number;
        }

        int& operator++(){
            if(number_of_element==size) throw "ERROR";
            number_of_element++;
            number++;
            return *number;
        }
        bool operator!=(Iterator itr){
            return number!=itr.number;
        }

    };

    Iterator begin() const{
        return Iterator{tab,size};
    }
    Iterator end() const{
        return Iterator{ &tab[size], size};
    }

};

class mylist;
class node{
int obj;
node* next;
friend class mylist;
node(): next(nullptr){}
node(node& copy): obj(copy.obj), next(copy.next){}
};
class mylist{
public:
int nel;
node* head;

mylist(): head(nullptr), nel(0){}

mylist(mylist& copy): nel(copy.nel){
    if(copy.head==nullptr){
        head=nullptr;
    }
    else{
        head= new node;
        head->obj=copy.head->obj;
        node* temp=copy.head;
        node* temp2=head;
        while(temp->next){
            temp=temp->next;
            temp2=temp2->next;
            temp2=new node(*temp);
        }
    }
}

~mylist(){
    while(nel!=0){
        pop_back();
    }
}

int& insert(int obj){
    nel++;
    node* ins= new node();
    ins->obj=obj;
    if(head==nullptr){
        head=ins;
    }
    else{
        node* tmp=head;
        while(tmp->next){
            tmp=tmp->next;
        }
        tmp->next=ins;
    }
    return ins->obj;
}

void print(){
    node* tmp=head;
    while(tmp){
        cout<<tmp->obj<<" ";
        tmp=tmp->next;
    }
}

void pop_back(){
    nel--;
    if(head){
        if(head->next==nullptr){
            delete head;
            head=nullptr;
        }
        else{
            node* tmp=head;
            while(tmp->next->next){
              //  cout<<tmp->obj<<" ";
                tmp=tmp->next;
            }
            cout<<endl<<"usuwam: "<<tmp->next->obj<<endl;
            delete tmp->next;
            tmp->next=nullptr;
        }
    }
}
class Iterator{
    node* itr;
public:
    Iterator(): itr(nullptr){}
    Iterator(node* ptr): itr(ptr){}

    int& operator*() const{
        return itr->obj;
    }

    Iterator& operator++(){
        if(!itr) throw "ERROR";
        itr=itr->next;
        return *this;
    }

    bool operator!=(const Iterator& itr) const{
        return this->itr!=itr.itr;
    }
};

Iterator begin()const{
    return {head};
}

Iterator end()const{
    return {};
}

};

class singleton{
    int i;
    singleton()=default;

public:
    static singleton& getsingl(){
        static singleton singleto;
        return singleto;
    }

    void set(int a){
        i=a;
    }
    void print(){
        cout<<endl<<i<<endl;
    }

};

int main()
{
    singleton::getsingl().set(5);
    singleton::getsingl().print();
    cout<<endl;

    vector v;
    for(int i=0;  i<=5; i++){
        v.insert(i);
    }
    v.print();

cout<<endl;

std::map<int, string> mp;
mp.insert({1,"Ala ma kota"});
mp.erase(mp.find(1));
cout<<mp.begin()->first<<endl<<mp.begin()->second;


    return 0;
}
