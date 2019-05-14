#include <iostream>
#include <memory>
#include <initializer_list>


#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;





template<typename T, size_t resize_of_tabStep=5>
class Vector{
  size_t size_of_tab;
  size_t capacity;
  unique_ptr<T[]> data;

public:
  Vector(): size_of_tab(0), capacity(0), data(nullptr){}

  Vector(const Vector& copy): size_of_tab(copy.size_of_tab), capacity(copy.size_of_tab), data(new T[copy.size_of_tab]){
      data.reset(new T[size_of_tab]);
      for(size_t i=0; i<size_of_tab; ++i){
          data[i]=copy.data[i];
      }
  }
  Vector(Vector&& mov): size_of_tab(mov.size_of_tab), capacity(mov.capacity), data(move(mov.data)){
      mov.capacity=0;
      mov.size_of_tab=0;
  }

  template<typename Container>
  Vector(const Container& container): size_of_tab(container.size()),capacity(container.size()), data(new T[container.size()]){
      size_t i=0;
      for(auto it: container){
          data[i]=it;
          ++i;
      }
  }

  template<size_t N>
  Vector(T(& staticArray) [N]): size_of_tab(N), capacity(N){
      data.reset(new T[size_of_tab]);
      for(size_t i=0; i<size_of_tab; ++i){
          data[i]=staticArray[i];
      }
  }

  Vector(initializer_list<T> in_list){
      for(auto it: in_list){
          push_back(it);
      }
  }

  ~Vector(){
      data.release();
     //????????????????????????????????????????????????????????????
  }

  void isEnough(){
      if(size_of_tab==capacity){
          unique_ptr<T[]> copy=move(data);
          capacity+=resize_of_tabStep;
          data.reset(new T[capacity]);
          for(size_t i=0; i<size_of_tab; ++i){
              data[i]=copy[i];
          }
      }
  }

  void push_back(T t){
      isEnough();
      size_of_tab++;
      data[size_of_tab-1]=t;
  }

  void pop_back(){
      if(size_of_tab>0){
          size_of_tab--;
          if(size_of_tab==capacity/2){
              unique_ptr<T[]> copy=move(data);
              capacity=size_of_tab;
              data.reset(new T[capacity]);
              for(size_t i=0; i<size_of_tab; ++i){
                  data[i]=copy[i];
              }
          }
      }
  }

  T& at(size_t index) const{
      if(index>=size_of_tab) throw "index out of range";
      return data[index];
  }

  size_t size() const{
      return size_of_tab;
  }

  class Iterator{
      T* obj;
      size_t size;
      size_t number_of_element;
  public:
      Iterator(T* ptr, size_t size): obj(ptr), size(size), number_of_element(0){}


      T& operator*() const {
          if(number_of_element==size) throw "not permision!";
          return *obj;
      }

      Iterator operator++(){
          if(number_of_element==size) throw "not permision!";
          ++obj;
          return *this;
      }

      bool operator!=(Iterator& itr) const {
          return obj!=itr.obj;
      }
  };

  Iterator begin(){
      return Iterator{data.get(), size_of_tab};
  }

  Iterator end(){
      T* ptr=data.get();
      return Iterator{ &(ptr[size_of_tab]), size_of_tab };
  }

  template<typename Predicate>
  size_t count_if(Predicate predicate){
      size_t count=0;
      for(auto it: *this){
          if(predicate(it)){
              count++;
          }
      }
      return count;
  }
};


bool isMoreThanZero(int number){
    return number>0;
}


int main()
{

    static int b[11];
    for(int i=0; i<11; i++){
        b[i]=i;
    }
//sfksndfksnk;
    Vector<int> a(b);
    Vector<int> c(move(a));


    for(auto it: c){
        cout<<it<<" ";
    }
    cout<<endl<<c.count_if(isMoreThanZero);

    Vector<int> d={1,5,356,76567456,345342,645654,43563,54677,45746,3,2342};

    cout<<endl<<endl<<d.size()<<endl;
    for(auto it: d){
        cout<<it<<" ";
    }
    cout<<endl;


}
