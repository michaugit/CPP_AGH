#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

enum class BonusType{attack, defend};


struct Item{
    int value;
    string description;
    BonusType bonusType;
};

void save_items_to_file(vector<Item> vector_of_items, string name_of_file );

void load_items_from_file(vector<Item>& vector_of_items, string name_of_file );




class Equipment{
    vector <Item> owned_items;
   /**
    assign      ->	Usuwa wszystkie istniejące elementy z kontenera, a następnie kopiuje wskazane elementy do kontenera. (metoda)
    at          ->  Zwraca referencję na element, który znajduje się na podanej pozycji w kontenerze » standard C++ ♦ vector. (metoda)
    back        ->	Zwraca referencję na ostatni element w kontenerze. (metoda)
    begin       ->	Zwraca iterator wskazujący na pierwszy element. (metoda)
    capacity    ->	Zwraca maksymalną liczbę elementów jaką może pomieścić kontener bez wykonywania realokacji pamięci. (metoda)
    clear       ->  Usuwa wszystkie elementy z kontenera vector. (metoda)
    empty       ->  Sprawdza czy kontener jest pusty. (metoda)
    end         ->  Zwraca iterator wskazujący na element będący za ostatnim elementem. (metoda)
    erase       ->  Usuwa jeden element lub wiele elementów z kontenera vector występujących na podanej pozycji lub w podanym zakresie. (metoda)
    front       ->  Zwraca referencję na pierwszy element w kontenerze. (metoda)
    get_allocator	->  Zwraca kopię alokatora używanego do tworzenia elementów kontenera » standard C++ ♦ vector. (metoda)
    insert  	->  Wstawia jeden element lub wiele elementów do kontenera vector na określonej pozycji. (metoda)
    max_size	->  Maksymalna możliwa długość tablicy kontenera » standard C++ ♦ vector, wyrażona w liczbie elementów. (metoda)
    operator[]	->  Zwraca referencję na element, który znajduje się na podanej pozycji w kontenerze » standard C++ ♦ vector. (operator - metoda)
    pop_back	->  Usuwa jeden element z kontenera vector, znajdujący się na jego końcu. (metoda)
    push_back	->  Dodaje nowy element na końcu kontenera vector. (metoda)
    rbegin      ->  Zwraca iterator odwrotny wskazujący na ostatni element. (metoda)
    rend        ->  Zwraca iterator odwrotny wskazujący na element występujący bezpośrednio przed pierwszym elementem. (metoda)
    reserve     ->  Rezerwuje tyle miejsca w kontenerze, żeby pomieściła się wskazana liczba elementów bez konieczności wykonywania dodatkowej realokacji pamięci przy ich dodawaniu. (metoda)
    resize      ->  Ustawia nowy rozmiar kontenera vector. (metoda)
    size        ->  Zwraca liczbę elementów znajdujących się aktualnie w kontenerze. (metoda)
    swap        ->  Kontenery » standard C++ ♦ vector zamieniają się posiadanymi danymi. (metoda)
    **/

    int attack;
    int defence;
    const string name;

    int find_item(Item item, vector<Item> item_vector){
        int index=-1;
        for(unsigned int i=0; i<item_vector.size(); i++){
            if(item_vector[i].description == item.description ){
                index=i;
                break;
            }
        }
        return index;
    }

    void print_item(Item item){
        cout<<"\t\t-Name of item: "<<item.description<<endl;
        switch(item.bonusType){
        case BonusType::attack:
            cout<<"\t\t-Attack bonus: "<<item.value<<endl<<endl;
        break;

        case BonusType::defend:
            cout<<"\t\t-Defence bonus: "<<item.value<<endl<<endl;
        break;

        default: exit(EXIT_FAILURE);
    }
    }

public:
    Equipment(string name_of_owner="default"): name(name_of_owner){
        attack=0;
        defence=0;
    }

    void collect_item(Item item){
        owned_items.push_back(item);
        switch(item.bonusType){
            case BonusType::attack: attack+=item.value; break;
            case BonusType::defend: defence+=item.value; break;
            default: exit(EXIT_FAILURE);
        }
    }

    int remove_item(Item item){
        int ret=0;
        int index=0;
        index=find_item(item, owned_items);
        if(index>=0){
            switch(item.bonusType){
                case BonusType::attack: attack-=item.value; break;
                case BonusType::defend: defence-=item.value; break;
                default: exit(EXIT_FAILURE);
            }
            owned_items.erase(owned_items.begin()+index);
            ret=1;
        }
        else ret=0;
        return ret;
    }

    void print_items(BonusType type_of_item){
       int show=0;
        switch(type_of_item){
        case BonusType::attack:
            for(unsigned int i=0; i<owned_items.size();i++){
                if(owned_items[i].bonusType==BonusType::attack){
                    cout<<"\t\t"<<show+1<<"."<<endl;
                    print_item(owned_items[i]);
                    show++;
                }
            }
            if (show==0)cout<<"\t\t none of attack items "<<endl;
            break;
        case BonusType::defend:
            for(unsigned int i=0; i<owned_items.size();i++){
                if(owned_items[i].bonusType==BonusType::defend){
                    cout<<"\t\t"<<show+1<<"."<<endl;
                    print_item(owned_items[i]);
                    show++;
                }
            }
            if(show==0) cout<<"\t\t none of deffence items "<<endl;
            break;
        }
    }

    void print_all_owned_items(){
        cout<<"OWNED ITEMS: "<<endl;
        cout<<"\t*Attack: "<<endl;
        print_items(BonusType::attack);
        cout<<"\t*Defence: "<<endl;
        print_items(BonusType::defend);
    }

    void save_to_file(){
         save_items_to_file(owned_items,this->name+".txt");
    }

    void load_from_file(){
        vector<Item> loaded_items;
        load_items_from_file(loaded_items,this->name+".txt");
        for(unsigned int i=0; i<loaded_items.size(); i++){
            collect_item(loaded_items[i]);
        }
    }

    void show_statistics_of_owned_items_type_of(BonusType type_of_item){
        switch(type_of_item){
        case BonusType::attack:
            cout<<"*Owned attack items: "<<endl;
            print_items(type_of_item);
            cout<<"\tSummary power of attack: "<<attack<<endl<<endl;
            break;
        case BonusType::defend:
            cout<<"*Owned defence items: "<<endl;
            print_items(type_of_item);
            cout<<"\tSummary power of defence: "<<defence<<endl<<endl;
            break;
        }
    }

    void sort_items(){
        struct {
            bool operator() (Item i1, Item i2){
                return (i1.bonusType<i2.bonusType);
            }
        }type_sort;
        sort(owned_items.begin(), owned_items.end(), type_sort);

        struct {
            bool operator() (Item i1, Item i2){
                return (((i1.bonusType==i2.bonusType)&&i1.value<i2.value));
            }
        }alph_sort;
        sort(owned_items.begin(), owned_items.end(), alph_sort);

        struct {
            bool operator() (Item i1, Item i2){
                return ((i1.bonusType==i2.bonusType)&&(i1.value==i2.value)&&(i1.description[0]<i2.description[0]));
            }
        }value_sort;
        sort(owned_items.begin(), owned_items.end(), value_sort);

   }

    void print(){
        for(unsigned int i=0; i<owned_items.size(); i++){
            print_item(owned_items[i]);
        }
    }

    friend void unite_two_equipments_in_one(Equipment& where, Equipment first_source, Equipment second_source);
};


void unite_two_equipments_in_one(Equipment& where, Equipment first_source, Equipment second_source){
    where.owned_items.clear();
    for(unsigned int i=0; i<first_source.owned_items.size(); i++){
        where.collect_item(first_source.owned_items[i]);
    }
    for(unsigned int i=0; i<second_source.owned_items.size(); i++){
        where.collect_item(second_source.owned_items[i]);
    }
   }

void save_items_to_file(vector<Item> vector_of_items, string name_of_file ){
    fstream items_file;
    int value;
    string description;
    char bonus;;
    items_file.open(name_of_file, ios::out);

    if(items_file.good()==0) cout<<"ERROR";
    for(unsigned int i=0; i< vector_of_items.size(); i++){
        value=vector_of_items[i].value;
        description=vector_of_items[i].description;
        switch(vector_of_items[i].bonusType){
            case BonusType::attack: bonus='a'; break;
            case BonusType::defend: bonus='d'; break;
        }
        items_file<<description<<endl<<value<<endl<<bonus<<endl;

    }

    items_file.close();

}

void load_items_from_file(vector<Item>& vector_of_items, string name_of_file ){
    fstream items_file;
    string line;
    int number_of_line=0;

    Item item;

    items_file.open(name_of_file, ios::in);
    if(items_file.good()==0) cout<<"ERROR";
    while(getline(items_file,line)){
        switch(number_of_line%3){
        case 0:
           item.description=line;
           break;

        case 1:
           item.value=atoi(line.c_str());
           break;

        case 2:
            switch(line[0]){ //bo to będzie wtedy znak a lub d
                case 'a':
                    item.bonusType=BonusType::attack;
                break;

                case 'd':
                    item.bonusType=BonusType::defend;
                break;
            }
            vector_of_items.push_back(item);
            break;
         }
        number_of_line++;
     }

    items_file.close();
}









int main(){


Equipment p1;

Item item1={50, "mlotek",   BonusType::attack };
Item item2={150,"dzida",    BonusType::attack };
Item item5={150,"mlotek2",  BonusType::attack };
Item item3={50, "tarcza",   BonusType::defend };
p1.collect_item(item3);
p1.collect_item(item1);
p1.collect_item(item2);
p1.collect_item(item5);


//sprawdzenie sortowania
cout<<endl<<endl<<endl<<endl;
p1.print();
cout<<endl<<endl<<endl<<endl;
p1.sort_items();
p1.print();
cout<<endl<<endl<<endl<<endl;

//sprawdzanie usuwania i statystyk
p1.print_all_owned_items();
p1.save_to_file();
p1.remove_item(item1);
p1.remove_item(item2);
p1.remove_item(item3);
p1.show_statistics_of_owned_items_type_of(BonusType::attack);
p1.show_statistics_of_owned_items_type_of(BonusType::defend);

//ladowanie z pliku
p1.load_from_file();

//laczenie dwoch equipmentow w jeden
Equipment p2;
Item item4={4000,"AK47",BonusType::attack};
p2.collect_item(item4);

unite_two_equipments_in_one(p1,p2,p1);
p1.show_statistics_of_owned_items_type_of(BonusType::attack);
p1.show_statistics_of_owned_items_type_of(BonusType::defend);


return 0;
}
