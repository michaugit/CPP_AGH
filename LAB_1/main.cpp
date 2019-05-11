#include <iostream>
#include <cstring> //memset
#include <sstream>
#include <cstdlib>


using namespace std;


class Array{
    int* tab;
    const int size_of_tab;

public:
    Array(int size_tab=20): size_of_tab(size_tab){
        tab=new int[size_of_tab];
        memset(tab,0,(sizeof(int)*size_of_tab));
    }
    ~Array(){
        delete [] tab;
    }

    int get(int index){
        if((index>size_of_tab)||(index<0)){
            cout<<"Faulty index!";
            exit(EXIT_FAILURE);
        }
        else return tab[index];
    }

    void set(int index, int newValue){
    tab[index]=newValue;
    }

    int* front(){
        return tab;
    }
    int* back(){
        return &tab[size_of_tab-1];
    }
    int size(){
        return size_of_tab;
    }
    void fill(int value)
    {// fill_n(tab,size_of_tab, value);
        for(int i=0; i<size_of_tab;i++){
            tab[i]=value;
        }
    }

    void assign(const int tab_source[], int tabSize){
        if(tabSize>size_of_tab) tabSize=size_of_tab;
        for(int i=0; i<tabSize; i++){
                tab[i]=tab_source[i];
        }

    }

    Array* clone(){
        Array* copy= new Array(this->size());
        copy->assign(this->tab, this->size());
        return copy;
    }
    void reverse(){
        for(int i=0;i<(size_of_tab/2);i++){
            int copy;
            copy=tab[i];
            tab[i]=tab[(size_of_tab-1)-i];
            tab[(size_of_tab-1)-i]=copy;
        }
    }

    int count(int value){
        int sum=0;
        for(int i=0; i<size_of_tab; i++){
            sum+=(tab[i]==value);
        }
        return sum;
    }
    string toText() const {
        string text;
        ostringstream stream;
        for(int i=0; i<size_of_tab; i++){
                stream<<tab[i]<<" ";
        }
        text=stream.str();
    return text;
    }



    void print(){
        for(int i=0; i<size_of_tab;i++){
            cout<<tab[i]<<endl;
        }
    }
    void swap(Array& anotherArray){
        Array copy(size_of_tab);
        copy.assign(anotherArray.tab, size_of_tab);
        anotherArray.assign(this->tab, size_of_tab);
        this->assign(copy.tab, size_of_tab);
    }

    int find(int value){
        int index;
        for(int i=0; i<size_of_tab; i++){
            if(this->tab[i]==value){
                index=i;
                break;
            }
            else index=-1;
        }
        return index;
    }

    friend std::ostream& operator<<(std::ostream& os, const Array& array);

    friend std::istream& operator>>(std::istream& is, Array& array);


};




    std::ostream& operator<<(std::ostream& os, const Array& array){
        return os << array.toText() << std::endl;
    }

    std::istream& operator>>(std::istream& is, Array& array){
        std:: cout<<"Enter index and value: ";
        int index, value;
        is >> index >> value;
        if(index>=array.size()){
            cout<<"Faulty index!";
            exit(EXIT_FAILURE);
        }
        else array.set(index, value);
        return is;

    }


int main()
{

Array array(10);
array.fill(5);
cout<<array;
cin>>array;
cout<<array<<endl;

return 0;
}
