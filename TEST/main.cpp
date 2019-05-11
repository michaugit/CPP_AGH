#include <iostream>
using namespace std;

struct A
{
    A() { cout << "A::A()\n"; }
    ~A() { cout << "A::~A()\n"; }
    A(const A&) { cout << "A::A(const A&)\n"; }
    A& operator=(const A&) { cout << "A::operator=(const A&)\n"; return *this; }
};


struct B
{
    int i;
    B(): i(2) { cout << "B::B() i=" << i << "\n"; }

    ~B() { cout << "B::~B() i=" << i << "\n"; }

    B(int i): i(i) { cout << "B::B(int) i=" << i << "\n"; }

    B(const B& b): i(b.i) { cout << "B::B(const B&) i=" << i << "\n"; }

    B& operator=(const B& b) { i = b.i; cout << "B::operator=(const B&) i=" << i << "\n"; return *this; }

    B& operator=(int i) { this->i = i; cout << "B::operator=(int) i=" << i << "\n"; return *this; }
};
struct C // : A
{
    B b;

    C() { cout << "C::C()\n"; }
    C(int i): b(i) { cout << "C::C(int)\n"; }
    ~C() { cout << "C::~C()\n"; }
};



struct C1
{
    B b;

    C1(int i) {

cout << "C::C(int)\n";
b = i;
        cout << "C::C(int)\n";
    }
};
struct C2
{
    B b;

    C2(int i): b(i) {
        cout << "C::C(int)\n"; }
};

void f1(A a) {}
void f2(A& a) {}
void f3(const A& a) {}
void f4(A* a) {}



class Aklasa {
 public:
    Aklasa(){
        cout<<"konstruktor A"<<endl;
    }
};

class Bklasa: Aklasa{
  public:
    Bklasa(){
        cout<<"konstruktor B"<<endl;
    }
};





int main()
{
//Bklasa np;


//    {
//        cout << __LINE__ << ")Before:\n";
//        A a;
//        cout << __LINE__ << ")after:\n";
//    }

//    {
//        cout << __LINE__ << ")Before:\n";
//        A *aPtr = new A;
//        cout << __LINE__ << ")after:\n";
//    }

//    { /// konstruktor kopiujacy vs operator przypisania
//        cout << __LINE__ << ")Before:\n";
//        cout<<endl;
//        B b(__LINE__);
//         cout<<endl;
//        B b1 = b;
//         cout<<endl;
//        b = b1;
//        cout << __LINE__ << ")after:\n";
//    }

//    { /// kolejnosc wolania konstruktorow i destruktorow
//        cout << __LINE__ << ")Before:\n";
//        C c;
//        cout << __LINE__ << ")after:\n";
//    }

//    { /// inicjalizacja na liscie inicjalizacyjnej vs w ciele konstruktora
//        cout << __LINE__ << ")Before:\n";
//        C1 c1(3);
//        cout << " vs\n";
//        C2 c2(3);
//        cout << __LINE__ << ")after:\n";
//    }

//    {
//        cout << __LINE__ << ")Before:\n";
//        A a;
//        f1(a);
//        f1(A());
//        f2(a);
////        f2(A()); // czemu blad?
//        f3(a);
//        f3(A());
//        f4(&a);
//        cout << __LINE__ << ")after:\n";
//    }
}
