#include <fstream>
#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdio>
using namespace std;

class Book{
      int bookid;
      char title[30];
      float price; //4byte
public:
   Book(){ //This is a constructor. This is what runs first when object calls.
      bookid=0;
      strcpy(title,"No Title");
      price=0;
   }

   void getBookData();
   void Display();
   void insertData();
   void ViewAllData();
   void DeleteData(char *);


};
//This is for entering Data
void Book::getBookData(){
   cout <<"Enter Book ID: "<< endl;
   cin >> bookid;
   cin.ignore();
   cout <<"Enter Book Title: "<< endl;
   cin.getline(title,29);
   cout <<"Enter Book price: "<< endl;
   cin >> price;
   }
//This is for Displaying Data.
void Book::Display(){
   cout << bookid<<"\t\t"<<title<<"\t\t"<<price<<endl;
   }

//This is for inserting Data in a file.
void Book::insertData(){
   ofstream fout;
   fout.open("book.txt", ios::app); //app stands for append mode.
   fout.write((char*)this,sizeof(*this));
   cout<<"Data Inserted"<<endl;
   fout.close();
   getch();
   }

//This is for viewing Data.
void Book::ViewAllData(){
      ifstream fin;
      fin.open("book.txt",ios::in);
      if(!fin){
         cout <<"File Not Exits";
      }else{
         fin.read((char*)this,sizeof(*this));
         while(!fin.eof()){
            Display();
            fin.read((char*)this,sizeof(*this));

         }
         fin.close();

      }


   }

//This is for Deleting Data.
void Book::DeleteData(char *t){

    ifstream fin;
    ofstream fout;
    fin.open("book.txt",ios::in|ios::binary);
    if(!fin){
        cout <<"No Data Found";
    }else{
        fout.open("booknew.txt",ios::out|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(strcmp(title,t)){
                fout.write((char*)this,sizeof(*this));
                fin.read((char*)this,sizeof(*this));
            }
        }
        fin.close();
        fout.close();
        remove("book.txt");
        rename("booknew.txt","book.txt");
    }
}



int main()
{
    Book b1; //b1 is a caller object and has three values 36 bytes.
 b1.getBookData();
   b1.insertData();
   b1.DeleteData("Knights");
   b1.ViewAllData();

    return 0;
}
