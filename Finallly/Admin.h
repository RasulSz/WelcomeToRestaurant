#pragma once
#include<iostream>;
#include<string>;
#include<string.h>;
#include"ClassAndFunc.h";


using namespace std;

void SendNotificationToClient(ClientNotification& n, Table& t) {
	t.clientnotification.Push(n);
	t.notificationcount++;
}
void SendNotification(Notification& n1, Kitchen& k) {
	k.notification.Push(n1);
	k.notificationCount++;
}

void AdminMenu(Kitchen& k, Stock& s, Client& c, Table& t) {
	system("cls");
	cout << endl;
	cout << "                                                  [1] KITCHEN " << endl;
	cout << "                                                  [2] STOCK   " << endl;
	cout << "                                                  [3] BACK   " << endl;
	cout << "                                                  Enter select : ";
	int adminselect = 0;
	cin >> adminselect;
	if (adminselect == 1) {
		system("cls");
		cout << "                                               ---------KITCHEN---------                                               " << endl << endl;
		k.ShowName();
		cout << "                                                  [1] Delete meal " << endl;
		cout << "                                                  [2] Update meal" << endl;
		cout << "                                                  [3] Add meal" << endl;
		cout << "                                                  [4] Notifications";
		cout << "(" << k.notificationCount << ")" << endl;
		cout << "                                                  [5] Back" << endl << endl;
		cout << "                                                  Enter your select : ";
		int select;
		cin >> select;
		if (select == 1) {
			while (true)
			{
				cout << "                                                  Enter ID of meal : ";
				int id;
				cin >> id;
				if (k.GetMealCount() >= id) {
					--id;
					k.MealsPop(id);
					system("cls");
					k.ShowName();
					cout << endl << "                                                  Food deleted!" << endl;
					system("pause");
					break;
				}
				else {
					cout << "                                                  Meal not found!" << endl;
				}
			}
			AdminMenu(k, s, c, t);
		}
		else if (select == 2) {
			cout << "                                                  Select meal id : ";
			int id;
			cin >> id;
			k.UptadeMeals(id);
			cout << "                                                  Meal updated succesfully" << endl;
			system("pause");
			AdminMenu(k, s, c, t);
		}
		else if (select == 3) {
			k.ShowName();
			k.AddMeal();
			AdminMenu(k, s, c, t);
		}
		else if (select == 4) {
			for (size_t i = 0; i < k.notificationCount; i++)
			{
				k.notification.Show();
			}
			k.notificationCount--;
			cout << "                                                  Accept [1]\nReject [2]" << endl;
			cout << "                                                  Enter your answer : ";
			int answer;
			cin >> answer;
			int count;
			if (answer == 2) {
				int tableNo = c.GetTableNo();
				int count;
				static string content = "                                                  We can't preparing your order. Because we are very busy now";
				ClientNotification n(content, tableNo);
				SendNotificationToClient(n, t);
			}
			else if (answer == 1) {
				int tableNo = c.GetTableNo();
				static string content = "                                                  We preparing your order. Please wait 10 minutes";
				ClientNotification n(content, tableNo);
				SendNotificationToClient(n, t);
			}
			else if (answer == 4) {
				AdminMenu(k, s, c, t);
			}
		}
	}
	else if (adminselect == 2) {
		while (true) {
			system("cls");
			cout << "\n                                                  <><><><><><>STOCK<><><><><><>" << endl << endl;
			cout << "                                                  [1] Show Ingredients" << endl;
			cout << "                                                  [2] Add Ingredients" << endl;
			cout << "                                                  [3] Delete Ingredients" << endl;
			cout << "                                                  [4] Update ingredients count" << endl;
			cout << "                                                  [5] BACK" << endl;
			cout << "                                                  Select : ";
			int select;
			cin >> select;
			if (select == 1) {
				s.Show();
				system("pause");
			}
			else if (select == 2) {
				cin.ignore();
				cin.clear();
				cout << "                                                  Enter ingredients name : ";
				string name;
				getline(cin, name);

				cout << "                                                  Enter ingredients price : ";
				double price;
				cin >> price;

				cout << "                                                  Enter ingredient count : ";
				int count;
				cin >> count;

				Product p(name, price, count);
				s.AddProduct(p);
				remove("products.txt");
				FileHelper::Save(s);
				cout << "                                                  Ingredient added successfully" << endl;
				system("pause");
			}
			else if (select == 3) {
				s.Show();
				cout << "                                                  Enter id of ingredients : ";
				int id;
				cin >> id;
				--id;
				s.DeleteIngredientsByID(id);
				remove("products.txt");
				FileHelper::Save(s);
				cout << "                                                  Ingredient deleted successfully" << endl;
				system("pause");
			}
			else if (select == 4) {
				s.ShowProductCount();
				cout << "                                                  Enter id of ingredient : ";
				int id1;
				cin >> id1;
				Product* p = s.GetProductById(id1);
				cout << "                                                  Enter new count : ";
				int count;
				cin >> count;
				p->SetCount(count);
				remove("products.txt");
				FileHelper::Save(s);
				cout << "                                                  Count uptaded successfully" << endl;

			}
			else if (select == 5) {
				break;
			}
			else {
				cout << "                                                  Invalid select !!" << endl;
				system("pause");
			}
		}


	}
	else if (adminselect == 3) {
		return;
	}

}
