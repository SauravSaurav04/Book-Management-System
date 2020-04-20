#include<fstream>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
class Book{
	char name[20];
	int id;
	float price;
	public:
		Book(){
			strcpy(name, "No name");
			id = 0;
			price = 0;
		}
		void set(){
			
			cout<<"   Name : ";
			cin>>name;
			cout<<"   Id : ";
			cin>>id;
			cout<<"   Price : ";
			cin>>price;
		}
		void show(){
			cout<<"   Book Name is "<<name<<endl;
			cout<<"   Book Id is "<<id<<endl;
			cout<<"   Book Price is "<<price<<endl;
			cout<<endl;
		}
		int store_info_to_hard_disk(){
			system("cls");
			system("color 30");
			start:
			cout<<"\n\tEnter Book Details\n\n";
			set();
			if(id==0 && price==0){
				cout<<"Book Data not initialized";
				return 0;
			} else {
				ofstream fout;
				fout.open("Book_M_S_Data.txt", ios::app|ios::binary);
				fout.write((char*)this, sizeof(*this));
				fout.close();
				cout<<"\n   Book Record Inserted Successfully.\n\n";
				char c;
				cout<<"   Press i to Enter detail of another Book \n";
				cout<<"   Enter any Key for Next ";
				cin>>c;
				cout<<endl;
				if(c == 'i'){
					goto start;
				}
			}
			return 1;
		}
		void view_all_info(){
			system("cls");
			system("color 30");
			cout<<"\n\tAll Book Details are\n\n";
			ifstream fin;
			fin.open("Book_M_S_Data.txt", ios::in|ios::binary);
			if(!fin){
				cout<<"File not found";
			} else{
				fin.read((char*)this, sizeof(*this));
				while(!fin.eof()){
					show();
					fin.read((char*)this, sizeof(*this));
				}
				fin.close();
			}
			cout<<"   Enter any Key for Next ";
			getch();
		}
		void search(){
			system("cls");
			system("color 30");
			cout<<"\n\tSearch Book Here\n\n";
			cout<<"   Enter Book name to Search : ";
			char s[20];
			cin>>s;
			cout<<endl;
			ifstream fin;
			int x=0;
			fin.open("Book_M_S_Data.txt", ios::in);
			if(!fin){
				cout<<"File not found";
			} else{
				fin.read((char*)this, sizeof(*this));
				while(!fin.eof()){
					if(!strcmp(name,s)){
						show();
						x++;
						break;
					}
					fin.read((char*)this, sizeof(*this));
				}
				fin.close();
				if(x == 0){
					cout<<"   This Book is not present in this file\n\n";
				}
			}
			cout<<"   Enter any Key for Next ";
			getch();
		}
		void delete_info(){
			int x = 0;
			system("cls");
			system("color 30");
			cout<<"\n\tDelete Book here\n\n";
			char s[20];
			cout<<"   Enter Book Name to Delete : ";
			cin>>s;
			cout<<"\n";
			ifstream fin;
			ofstream fout;
			fin.open("Book_M_S_Data.txt", ios::in|ios::binary);
			if(!fin){
				cout<<"File doesn't open";
			} else{
				fin.read((char*)this, sizeof(*this));
				while(!fin.eof()){
					if(!strcmp(name,s)){
						x++;
						break;
					}
					fin.read((char*)this, sizeof(*this));
				}
				fin.close();
				if(x == 0){
					cout<<"   Sorry This Book is not Present in this file\n\n";
				} else {
					fin.open("Book_M_S_Data.txt", ios::in|ios::binary);
					fout.open("temp.txt",ios::out|ios::binary);
					fin.read((char*)this, sizeof(*this));
					while(!fin.eof()){
						if(strcmp(s, name)){
							fout.write((char*)this, sizeof(*this));
						}
						fin.read((char*)this, sizeof(*this));
					}
					fin.close();
					fout.close();
					remove("Book_M_S_Data.txt");
					rename("temp.txt", "Book_M_S_Data.txt");
					cout<<"   Book Successfully Deleted\n\n";
				}
			}
			cout<<"   Enter any Key for Next ";
			getch();
		}
		void update_info(){
			int x = 0;
			system("cls");
			system("color 30");
			cout<<"\n\tUpdate Book Here\n\n";
			cout<<"   Enter Book name to Update : ";
			char d[20];
			cin>>d;
			cout<<"\n";
			fstream file;
			file.open("Book_M_S_Data.txt", ios::in| ios::out|ios::ate|ios::binary);
			file.seekg(0);
			file.read((char*)this, sizeof(*this));
			while(!file.eof()){
				if(!strcmp(d, name)){
					set();
//					file.seekg(file.tellp()-sizeof(*this));
					file.seekg(-sizeof(*this),ios_base::cur);
					file.write((char*)this, sizeof(*this));
					x++;
				}
				file.read((char*)this, sizeof(*this));
			}
			file.close();
			if(x == 0){
				cout<<"   Sorry This Book is not present in this file\n";
			} else {
				cout<<"\n   Book Updated Successfully.\n";
			}
			cout<<"\n   Enter any Key for Next ";
			getch();
		}
};
int menu(){
	system("cls");
	system("color 90");
	int choice;
	cout<<"\n\t\t\xB2\xB1\xB2\xB1\xB2\xB1   WeLcOmE tO BooK Management System   \xB1\xB2\xB1\xB2\xB1\xB2";
	cout<<"\n\n\t\t\t\t1. Insert Book Records";
	cout<<"\n\t\t\t\t2. View all Book Records";
	cout<<"\n\t\t\t\t3. Search Book Records";
	cout<<"\n\t\t\t\t4. Delete Book Records";
	cout<<"\n\t\t\t\t5. Update Book Records";
	cout<<"\n\t\t\t\t6. Exit";
	cout<<"\n\n\t\t\t\tEnter Your Choice : ";
	cin>>choice;
	return(choice);
}
int main(){
	Book b1;
	system("cls");
	system("color 90");
	while(1){
		switch(menu()){
			system("color 90");
			case 1:
				b1.store_info_to_hard_disk();
				break;
			case 2:
				b1.view_all_info();
				break;
			case 3:
				b1.search();
				break;
			case 4:
				b1.delete_info();
				break;
			case 5:
				b1.update_info();
				break;
			case 6:
				cout<<"\n\t\t\t Thank you for using this application";
				cout<<"\n\n\t\t\t\tPress any key to exit ";
				getch();
				exit(0);
			default:
				cout<<"\n\n\t\t\t\tInvalid choice";
		}
	}
}
