#pragma once

#include <iostream>
#include "ClassAndFunc.h"
#include "Admin.h"
using namespace std;


void ClientMenu(double totalPrice, Client& c, Kitchen& k, Stock& stock, Notification& n, Table& t) {
	system("cls");
	c.ShowMenu();
	cout << "                                                  [1] Select meal" << endl;
	cout << "                                                  [2] Back" << endl;
	cout << "                                                  Enter your select : ";
	int choice;
	cin >> choice;
	if (choice == 1) {
		cout << "                                                  Enter your choice to view : ";
		int select;
		cin >> select;
		cout << endl;
		k.ShowMealById(select);
		cout << "                                                  [1] Order" << endl;
		cout << "                                                  [2] Add ingredients" << endl;
		cout << "                                                  Enter select : ";
		int select1;
		cin >> select1;
		if (select1 == 1) {
			cout << "                                                  Enter meal count : ";
			int count;
			cin >> count;
			if (count > 0) {
				auto meal = k.GetMealById(select);
				int tableNo = c.GetTableNo();
				totalPrice += count * meal->GetPrice();
				cout << "                                                  Total price : " << totalPrice << " $" << endl;
				cout << "                                                  [1] Continue" << endl;
				cout << "                                                  [2] Finish" << endl;
				cout << "                                                  Select : ";
				int select;
				cin >> select;
				if (select == 1) {
					Notification n(count, tableNo);
					n.AddMealToNotification(meal);
					SendNotification(n, k);
					ClientMenu(totalPrice, c, k, stock, n, t);
				}
				else if (select == 2) {
					Notification n(count, tableNo);
					n.AddMealToNotification(meal);
					SendNotification(n, k);
				}
			}
		}
		else if (select1 == 2) {
			cout << endl;
			stock.Show();
			cout << "                                                  Enter ingredients id : ";
			int id;
			cin >> id;
			Product* product = stock.GetProductById(id);
			cout << *product << endl;
			cout << "                                                  Enter " << product->GetName() << " count : ";
			double count;
			cin >> count;
			if (stock.ProductCount(id, count)) {
				auto meal = k.GetMealById(select);
				meal->AddProduct(*product);
				totalPrice += meal->GetPrice();
				double a = product->GetPrice();
				totalPrice += product->GetPrice() * count;
				cout << "\n                                                  " << *meal << endl;
				cout << "                                                  Ingredients added successfully" << endl << endl;
				cout << "                                                  Total price : " << totalPrice << " $" << endl;
			}
			else {
				auto meal = k.GetMealById(select);
				totalPrice += meal->GetPrice();
				cout << "                                                  Ingredients out of stock" << endl;
			}
		}
	}
	
	if (choice == 2) {
		for (size_t i = 0; i < t.notificationcount; i++)
		{
			t.clientnotification.Show();
		}
		t.notificationcount--;
		system("pause");
	}
	else if (choice == 4) {
		return;
	}
};