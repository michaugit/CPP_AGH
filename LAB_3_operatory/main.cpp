#include <iostream>
#include <string>
#include <stdlib.h> // do konwersji inta

using namespace std;



class String{
    int size_of_tab;
    int size_of_text;
public:
    char *text;
    String(): size_of_tab(0), size_of_text(0), text(nullptr){}
    String(char* text){
        int size=0;
        while(text[size]!='\0') size++;
        size++;
        this->text= new char[size];
        this->size_of_text=size-1;
        this->size_of_tab=size;
        for(int i=0; i<size; i++){
            this->text[i]=text[i];
        }
    }
    String(const String& copy){

        this->size_of_text=copy.size_of_text;
        this->size_of_tab=copy.size_of_tab;
        this->text= new char[this->size_of_tab];

        for(int i=0; i<=this->size_of_text; i++){
            this->text[i]=copy.text[i];
        }
    }
    ~String(){
        delete [] text;
    }

    String& operator=(const String& string){
        delete [] this->text;
        this->text= new char[string.size_of_text];
        for(int i=0; i<=string.size_of_text; i++){
            this->text[i]=string.text[i];
        }
        this->size_of_text=string.size_of_text;
        this->size_of_tab=string.size_of_tab;
        return *this;
    }

    String operator+(const String& string){
        String tmp;
        int size=(this->size_of_text + string.size_of_text + 1);
        tmp.text= new char[size];
        tmp.size_of_text=size-1;
        tmp.size_of_tab=size;
        //        strcpy(gdzie, z czego);
        //        strncat(gdzie dodac, z czego, ile znakow);

        int i;
        for( i=0 ; i<this->size_of_text; i++){
            tmp.text[i]=this->text[i];
        }
        int j;
        for(j=0; j<string.size_of_text; j++){
            tmp.text[i+j]=string.text[j];
        }

        tmp.text[tmp.size_of_text]='\0';
        return tmp;
    }

    String operator+(const char *text){
        String tmp;
        int size=0;
        while(text[size]!='\0') size++;
        size++;

        size+=this->size_of_text;
        tmp.text= new char[size];
        tmp.size_of_text=size-1;
        tmp.size_of_tab=size;

        for(int i=0; i<this->size_of_text; i++){
            tmp.text[i]=this->text[i];
        }
        for(int i=this->size_of_text; i<=tmp.size_of_text; i++){
            tmp.text[i]=text[i-this->size_of_text];
        }
        return tmp;
    }


    bool operator==(const char *text) const{
        bool ret=0;
        int size=0;
        while(text[size]!='\0') size++;
        if(this->size_of_text==size) ret=true;
        if(ret==true){
            for(int i=0; i<this->size_of_text; i++){
                if(this->text[i]!=text[i]){
                    ret=false;
                    break;
                }
            }
        }
        return ret;   //strcmp(this->text, text)==0; zwracaa - jak sa rowne
    }

    bool operator==(const String& string){
        bool ret=0;
        if(this->size_of_text==string.size_of_text) ret=1;
        if(ret==1){
            for(int i=0; i<this->size_of_text; i++){
                if(this->text[i]!=string.text[i]){
                    ret=0;
                    break;
                }
            }
        }
        return ret;
    }


    bool operator>(const String& string){
        int size= ((this->size_of_text > string.size_of_text)? string.size_of_text : this->size_of_text);
        bool ret=1;
        for(int i=0; i<size; i++){
            if(this->text[i] < string.text[i]){
                ret=0;
                break;
            }
        }
        //jesli jest szansa ze beda takie same to ma zadecydowac dlugosc
        if(ret==1){
            bool same=1;
            for(int i=0; i<size; i++){
                if(this->text[i]!=string.text[i]){
                    same=0;
                    break;
                }
            }
            if(same==1) ret=((this->size_of_text > string.size_of_text) ? 1 : 0);
        }

        return ret;
    }

    bool operator<(const String& string){
        int size= ((this->size_of_text > string.size_of_text)? string.size_of_text : this->size_of_text);
        bool ret=1;
        for(int i=0; i<size; i++){
            if(this->text[i] > string.text[i]){
                ret=0;
                break;
            }
        }
        //jesli jest szansa ze beda takie same to ma zadecydowac dlugosc
        if(ret==1){
            bool same=1;
            for(int i=0; i<size; i++){
                if(this->text[i]!=string.text[i]){
                    same=0;
                    break;
                }
            }
            if(same==1) ret=((string.size_of_text > this->size_of_text) ? 1 : 0);
        }

        return ret;
    }


    char& operator[](size_t index){
        if( index > static_cast<size_t>(this->size_of_text)){
            cout<<endl<<"INDEX OUT OF RANGE!"<<endl;
            exit(EXIT_FAILURE);
        }
        return this->text[index];
    }

    const char& operator[](size_t index) const {
        if( index > static_cast<unsigned>(this->size_of_text) ){
            cout<<endl<<"INDEX OUT OF RANGE!"<<endl;
            exit(EXIT_FAILURE);
        }
        return this->text[index];
    }

    const int& operator()(){
        return this->size_of_text;
    }

    int operator()(const char* text){  //zwracajcy pozycje tekstu text ????????????
        int ret=-1;
        int size=0;
        while(text[size]!='\0') size++;
        int i;
        cout<<endl<<text[0]<<this->text[0]<<endl;
        for(i=0; i<this->size_of_text; i++){
            if(text[0]==this->text[i]){
                for(int j=0; j<size; j++){
                    if(text[j]!=this->text[i+j]  || (i+j)>this->size_of_text ){
                        ret=-1;
                        break;
                    }
                    ret=i;
                }
            }
            if(ret==i) break;
        }
        return ret;
    }
    //CHYBA CHODZILO O TO V V V V V V V V
    explicit operator const char*(){
        return this->text;
    }


    explicit operator bool(){
        return this->size_of_text==0? false : true;
    }
    //jawny operator konwersji do std::string

    explicit operator std::string() const {
        string tmp;
        for(int i=0; i<= this->size_of_text; i++){
            tmp+=this->text[i];
        }
        return tmp;
    }


    //preinkrementacja
    String& operator++(){
        this->size_of_text++;
        if(this->size_of_text+1>this->size_of_tab){
            char *copy= this->text;
            this->size_of_tab*=1.5;
            this->text= new char[this->size_of_tab];

            for(int i=0; i<this->size_of_text-1; i++){
                this->text[i]=copy[i];
            }
            delete [] copy;
        }
        this->text[this->size_of_text-1]= 32; // 32 to spacja w ASCII
        this->text[this->size_of_text]='\0';
        return *this;
    }
    //postinkrementacja
    String operator++(int){
        String before_incrementation(*this);
        ++(*this);
        return before_incrementation;
    }
    //predekrementacja
    String& operator--(){
        this->size_of_text--;
        char *copy= this->text;
        this->size_of_tab=this->size_of_text+1;
        this->text= new char[this->size_of_tab];

        for(int i=0; i<this->size_of_text; i++){
            this->text[i]=copy[i];
        }
        delete [] copy;

        this->text[this->size_of_text]='\0';
        return *this;
    }
    //postdekrementacja
    String operator--(int){
        String before_decrementation(*this);
        --(*this);
        return before_decrementation;
    }


    String& operator<<(double number){
        char text_number[25];
        sprintf(text_number, "%lf", number);
        int size=0;
        while(text_number[size]!='\0') size++;
        cout<<"ROZMIAR: "<<size<<endl;
        this->size_of_text+=size;
        if(this->size_of_text+1>this->size_of_tab){
            char *copy= this->text;
            while(this->size_of_text+1>this->size_of_tab) this->size_of_tab*=1.5;
            this->text= new char[this->size_of_tab];

            for(int i=0; i<this->size_of_text-size; i++){
                this->text[i]=copy[i];
            }
            delete [] copy;
        }
        for(int i=0; i<size; i++){
            this->text[this->size_of_text-size+i]= text_number[i];
        }
        this->text[this->size_of_text]='\0';
        return *this;
    }

    String& operator<<(int number){
        char text_number[20];
        itoa(number,text_number,10);
        int size=0;
        while(text_number[size]!='\0') size++;

        this->size_of_text+=size;
        if(this->size_of_text+1>this->size_of_tab){
            char *copy= this->text;
            while(this->size_of_text+1>this->size_of_tab) this->size_of_tab*=1.5;
            this->text= new char[this->size_of_tab];

            for(int i=0; i<this->size_of_text-size; i++){
                this->text[i]=copy[i];
            }
            delete [] copy;
        }
        for(int i=0; i<size; i++){
            this->text[this->size_of_text-size+i]= text_number[i];
        }
        this->text[this->size_of_text]='\0';
        return *this;
    }



    friend std::istream& operator>>(std::istream& is, String& string);
    friend std::ostream& operator<<(std::ostream& os,const String& string);

};


std::istream& operator>>(std::istream& is, String& string){
    char c;
    char *copy=nullptr;
    string.size_of_text=0;
    string.size_of_tab=2;
    delete [] string.text;
    string.text= new char[string.size_of_tab];

    while(is.get(c) && c!='\n'){
        string.size_of_text++;

        if(string.size_of_text+1>string.size_of_tab){
            copy=string.text;
            string.size_of_tab*=1.5;
            string.text= new char[string.size_of_tab];

            for(int i=0; i<string.size_of_text-1; i++){
                string.text[i]=copy[i];
            }
            delete [] copy;
        }

        string.text[string.size_of_text-1]=c;
        string.text[string.size_of_text]='\0';
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const String& string){
    return os<<string.text;
}



int main()
{

String a;
String* b= new String(a);

}

