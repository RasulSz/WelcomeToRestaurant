#include<iostream>
#include<assert.h>
#include<string>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<windows.h>
#include<vector>
#include"ClassAndFunc.h"
#include"Admin.h"
#include"Client.h"
using namespace std;


void main() {
	Product p("Tomato", 0.4, 18);
	Product p1("Olive", 0.1, 115);
	Product p2("Mashroom", 0.8, 22);
	Product p3("Flour", 1, 364);
	Product p4("Cucumber", 1, 364);

	Stock stocksave;
	stocksave.AddProduct(p);
	stocksave.AddProduct(p1);
	stocksave.AddProduct(p2);
	stocksave.AddProduct(p3);
	stocksave.AddProduct(p4);
	Meal f(20, "Mozerella");
	f.AddProduct(p);
	f.AddProduct(p1);
	f.AddProduct(p2);
	f.AddProduct(p3);
	Meal f1(13, "Sezar");
	f1.AddProduct(p);
	f1.AddProduct(p1);
	Kitchen k;
	k.AddMeal(f);
	k.AddMeal(f1);
	Client c1;
	c1.AddMenu(k);
	//FileHelper::Save(stocksave);
	Stock stock = FileHelper::Read();

	Meal m;
	Table t;
	Notification n;

#pragma region START
	double totalPrice = 0;
	while (true)
	{
		system("cls");
		cout << "                                                                                                        CLIENT [1]                                                                                  " << endl << endl;
		cout << "                                                                                                        ADMIN  [2]                                                                                  " << endl << endl;
		cout << "                                                                                                    Enter select [1/2] : ";
		string select;
		cin >> select;
		cout << endl << endl;
		if (select == "1") {

			Client c(1);
			c.AddMenu(k);
			ClientMenu(totalPrice, c, k, stock, n, t);
		}
		else if (select == "2") {
			system("cls");
			while (true)
			{
				cin.ignore();
				cin.clear();
				system("cls");
				cout << endl;
				cout << "                                                  Enter username : ";
				string username;
				getline(cin, username);
				system("cls");
				cout << "                                                  Enter Password: ";
				string password, P;
				char p;
				p = _getch();
				while (p != 13)
				{
					if (p == 8)
					{
						P.resize(P.length() - 1);
						cout << P;
						password.resize(password.length() - 1);
					}
					else {
						P = P + "*";
						cout << P;
						password.push_back(p);
					}
					p = _getch();
					if (p != 13) {
						system("cls");
						cout << "                                                  Enter Password: ";
					}
				}
				cout << endl;
				if (username == "OneSec") {
					if (password == "Senior10Line") {
						AdminMenu(k, stock, c1, t);
						break;
					}
					else {
						cout << "                                                  Wrong password!" << endl;
					}
				}
				else {
					cout << "                                                  Wrong username!" << endl;
				}
			}
		}
		else {
			cout << "                                                  Your select is incorrect!!!\n";
			cout << "                                                  Please enter retry" << endl;
		}
		system("pause");
	}
#pragma endregion	
}



