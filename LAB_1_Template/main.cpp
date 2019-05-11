#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class Array {
public:
  T *tab;
  const int size_of_tab;

  Array(int size_tab = 20) : size_of_tab(size_tab) {
    tab = new T[size_of_tab];
    memset(tab, 3, (sizeof(T) * size_of_tab));
  }
  ~Array() { delete[] tab; }

  T get(T index) {
    if ((index > size_of_tab) || (index < 0)) {
      cout << "Faulty index!";
      exit(EXIT_FAILURE);
    } else
      return tab[index];
  }

  void set(size_t index, T newValue) { tab[index] = newValue; }

  T *front() { return tab; }
  T *back() { return &tab[size_of_tab - 1]; }
  int size() { return size_of_tab; }
  void fill(T value) {
    for (int i = 0; i < size_of_tab; i++) {
      tab[i] = value;
    }
  }

  void assign(const T tab_source[], int tabSize) {
    if (tabSize > size_of_tab)
      tabSize = size_of_tab;
    // min(tabSize, size_of_tab) zwroci mniejsza wartosc;
    for (int i = 0; i < tabSize; i++) {
      tab[i] = tab_source[i];
    }
  }

  Array *clone() {
    Array *copy = new Array(this->size());
    copy->assign(this->tab, this->size());
    return copy;
  }
  void reverse() {
    for (int i = 0; i < (size_of_tab / 2); i++) {
      T copy;
      copy = tab[i];
      tab[i] = tab[(size_of_tab - 1) - i];
      tab[(size_of_tab - 1) - i] = copy;
    }
  }

  T count(T value) {
    int sum = 0;
    for (int i = 0; i < size_of_tab; i++) {
      sum += (tab[i] == value);
    }
    return sum;
  }
  string toText() const {
    string text;
    ostringstream stream;
    for (int i = 0; i < size_of_tab; i++) {
      stream << tab[i] << " ";
    }
    text = stream.str();
    return text;
  }

  void print() {
    for (int i = 0; i < size_of_tab; i++) {
      cout << tab[i] << endl;
    }
  }
  void swap(Array &anotherArray) {
    Array copy(size_of_tab);
    copy.assign(anotherArray.tab, size_of_tab);
    anotherArray.assign(this->tab, size_of_tab);
    this->assign(copy.tab, size_of_tab);
  }

  T find(T value) {
    int index;
    for (int i = 0; i < size_of_tab; i++) {
      if (this->tab[i] == value) {
        index = i;
        break;
      } else
        index = -1;
    }
    return index;
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Array<U> &array);
  template <typename U>
  friend std::istream &operator>>(std::istream &is, Array<U> &array);
};

template <class T>
std::ostream &operator<<(std::ostream &os, const Array<T> &array) {
  return os << array.toText() << std::endl;
}
template <class T> std::istream &operator>>(std::istream &is, Array<T> &array) {
  std::cout << "Enter index and value: ";
  int index;
  T value;
  is >> index >> value;
  if (index >= array.size()) {
    cout << "Faulty index!";
    exit(EXIT_FAILURE);
  } else {
    array.set(index, value);
  }
  return is;
}

int main() {
  Array<float> array(10);
  array.fill(6);
  string text = array.toText();
  cout << text << endl << typeid(array.tab[1]).name() << endl;

  cout << array;
  cin >> array;
  cout << array << endl;
  return 0;
}
