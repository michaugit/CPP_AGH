#include <iostream>

using namespace std;

template<class T>
class Klasa;

template<class T>
void fun(Klasa<T> x);

template<class T>

class Klasa{
public:
T tab[8];
friend void fun<T>(Klasa);
};

template<class T>
void fun(Klasa<T> x){
    cout<<endl<<typeid(x.tab).name()<<endl;
}


int main()
{
Klasa<int> a;
fun(a);

Klasa<float> b;
fun(b);

Klasa<char> c;
fun(c);

return 0;
}
