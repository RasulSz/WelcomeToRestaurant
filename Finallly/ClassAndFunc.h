#pragma once
#include<iostream>
#include<assert.h>
#include<string>
#include<list>
#include<vector>
#include <Windows.h>

using namespace std;

template<class T>
class Stack {
	T* data;
	size_t size = 0;
public:
	Stack() :data(NULL), size(NULL) {}
	void Push(const T& newdata) {
		auto newarray = new T[size + 1]{};
		for (size_t i = 0; i < size; i++)
		{
			newarray[i] = data[i];
		}
		newarray[size] = newdata;
		data = newarray;
		newarray = nullptr;
		++size;
	}
	void Pop(int index = -1) {
		if (index != -1) {
			auto newitems = new T[size - 1]{};
			for (size_t i = 0; i < index; i++)
			{
				newitems[i] = data[i];
			}
			int index1 = index + 1;
			int index2 = index;
			for (size_t i = 0; i < size - (index + 1); i++)
			{
				newitems[index2] = data[index1];
				index1++;
				index2++;
			}
			data = newitems;
			newitems = nullptr;
			size -= 1;
		}
		else {
			auto newitems = new T[size - 1]{};
			for (size_t i = 0; i < size - 1; i++)
			{
				newitems[i] = data[i];
			}
			data = newitems;
			newitems = nullptr;
			size -= 1;
		}
	}
	int Peek()const {
		assert(size > 0 && "Empty Stack");
		return data[size - 1];
	}
	void Clear() {
		if (this->data == NULL || this->size == NULL) {
			return;
		}
		delete[]data;
		this->data = NULL;
		this->size = NULL;
	}
	void Show()const {
		for (size_t i = 0; i < size; i++)
		{
			cout << data[i] << endl;
		}
	}
	size_t GetSize()const {
		return size;
	}
	T& operator[](int index) {
		assert(index >= 0 && index <= size && "Invalid Index");
		return data[index];
	}
	~Stack()
	{
		//delete[]data;
	}
};

class ClientNotification {
	string content;
	int tableNo;
public:
	ClientNotification() = default;
	ClientNotification(const string& content, const int& tableNo) {
		SetContent(content);
		SetTableNo(tableNo);
	}

	void SetContent(const string& content) {
		if (!content.empty()) {
			this->content = content;
		}

	}
	void SetTableNo(const int& tableNo) {
		if (tableNo >= 0) {
			this->tableNo = tableNo;
		}

	}

	int GetTableNo()const noexcept {
		return tableNo;
	}
	string GetContent()const noexcept {
		return content;
	}

	friend ostream& operator<<(ostream& out, const ClientNotification& clientnotifications);
};
ostream& operator<<(ostream& out, const ClientNotification& clientnotifications) {
	out << "                                                  Content : " << clientnotifications.GetContent() << endl;
	out << "                                                  Table NO : " << clientnotifications.GetTableNo() << endl;
	return out;
}



class Product {
	string name;
	double price;
	int id;
	int count;
public:
	static int ID;
	Product() = default;
	Product(const string& name, const double& price, const int& count) {
		SetId(ID++);
		SetName(name);
		SetPrice(price);
		SetCount(count);
	}
	void SetId(const int& id) {
		this->id = id;
	}
	void SetCount(const int& count) {
		assert(count > 0 && "Product count will be more than 0");
		this->count = count;
	}
	void SetName(const string& name) {
		assert(!name.empty() && "Name of product is null");
		this->name = name;
	}
	void SetPrice(const double& price) {
		assert(price >= 0 && "Price of product is negative or equal to 0");
		this->price = price;
	}
	double GetPrice()const {
		return price;
	}
	int GetCount()const {
		return count;
	}
	int GetId()const {
		return id;
	}
	string GetName()const {
		return name;
	}
	friend ostream& operator<<(ostream& out, const Product& products);
};
int Product::ID = 1;
ostream& operator<<(ostream& out, const Product& products) {
	//out << "Id : " << products.GetId() << endl << endl;
	out << "Product name : " << products.GetName() << endl;
	//out << "Product price : " << products.price << endl;
	return out;
}


class Meal {
	int id;
	double price;
	Stack<Product>products;
	string name;
	double allCalories;
public:
	static int ID;
	Meal() = default;
	Meal(const double& price, const string& name) {
		SetId(ID++);
		SetName(name);
		SetPrice(price);
		//allCalories += GetCalories();
	}
	void SetName(const string& name) {
		assert(!name.empty() && "Name of Meal is null");
		this->name = name;
	}
	void SetPrice(const double& price) {
		assert(price > 0 && "Price of Meal is negative or equal to 0");
		this->price = price;
	}
	void SetId(const int& id) {
		this->id = id;
	}
	int GetId()const {
		return id;
	}
	double GetPrice()const {
		return price;
	}
	string GetName()const {
		return name;
	}
	void AddProduct(Product& product) {
		products.Push(product);
	}

	Product* GetProductById(int id) {
		for (size_t i = 0; i < products.GetSize(); i++)
		{
			if (products[i].GetId() == id) {
				return &products[i];
			}
		}
	}


	void UpdateProduct() {
		cout << "Enter id of product : ";
		int id;
		cin >> id;
		auto product = GetProductById(id);
		cout << "[1] Product name" << endl;
		cout << "[2] Product price" << endl;
		cout << "[3] Product count" << endl;
		cout << "Enter choice : ";
		int choice;
		cin >> choice;
		if (choice == 1) {
			cin.ignore();
			cin.clear();
			cout << "Enter name : ";
			string name;
			getline(cin, name);
			product->SetName(name);
		}
		else if (choice == 2) {
			cout << "Enter price : " << endl;
			double price;
			cin >> price;
			product->SetPrice(price);
		}
		else if (choice == 3) {
			cout << "Enter count : " << endl;
			int count;
			cin >> count;
			product->SetCount(count);
		}

	}

	void ShowProductOfMeal()
	{
		products.Show();
	}
	friend ostream& operator<<(ostream& out, Meal& meal) {
		out << "Id : " << meal.GetId() << endl << endl;
		out << "Name of Meal : " << meal.name << endl << endl;
		meal.products.Show();
		return out;
	}
};



class Notification {
	int quantity;
	int tableNo;
public:
	Stack<Meal>meals;
	Notification() = default;
	Notification(const int& quantity, const int& tableNo) {
		SetNotificationQuantity(quantity);
		SetTableNo(tableNo);
	}
	void SetNotificationQuantity(const int& quantity) {
		if (quantity > 0) {
			this->quantity = quantity;
		}
		//throw "Quantity of notification is null";
	}
	void SetTableNo(const int& tableNo) {
		if (tableNo >= 0) {
			this->tableNo = tableNo;
		}
		//throw "No of table is empty";
	}

	int GetQuantity()const noexcept {
		return quantity;
	}
	int GetTableNo()const noexcept {
		return tableNo;
	}

	void AddMealToNotification(Meal* meal) {
		meals.Push(*meal);
	}
	friend ostream& operator<<(ostream& out, const Notification& notifications);
};
ostream& operator<<(ostream& out, Notification& notifications) {
	for (size_t i = 0; i < notifications.meals.GetSize(); i++)
	{
		out << notifications.meals[i] << endl;
	}
	out << "Meal count : " << notifications.GetQuantity() << endl;
	out << "Table no : " << notifications.GetTableNo() << endl;
	return out;
}

class Table {
	string message;
	string name;
public:
	static int notificationcount;
	Stack<ClientNotification>clientnotification;
	Stack<Notification>notifications;
	Table() = default;
	Table(const int& notif) {
		SetCount(notificationcount);
	}

	void SetMessage(const string& message) {
		this->message = message;
	}
	void SetCount(const int& notificationcount) {
		this->notificationcount = notificationcount;
	}
	void SetName(const string& name) {
		this->name = name;
	}

	string GetMessage() const {
		return message;
	}
	int GetNotificationCount()const {
		return notificationcount;
	}
	string GetName()const {
		return name;
	}

	void AddNotification(const Notification& notification) {
		notifications.Push(notification);
	}
};
int Table::notificationcount = 0;

int Meal::ID = 1;

class Kitchen :public Meal {
public:
	Stack<Meal>meals;
	Stack<Notification>notification;
	static int notificationCount;
	Kitchen() = default;
	Kitchen(const int& notificationCount, const string& meal) {
		SetNotificationCount(notificationCount);
	}
	void SetNotificationCount(const int& notificationCount) {
		assert(notificationCount >= 0 && "Notification count is negative number");
		this->notificationCount = notificationCount;
	}
	int GetNotificationCount()const {
		return notificationCount;
	}

	void AddMeal(Meal& meal) {
		meals.Push(meal);
	}
	void Show()const {
		meals.Show();
	}
	void ShowName() {
		for (size_t i = 0; i < meals.GetSize(); i++)
		{
			cout << "                                                  " << meals[i].GetId() << ". " << meals[i].GetName() << " - " << meals[i].GetPrice() << " $" << endl << endl;
		}
	}
	void ShowMealById(int id) {
		for (size_t i = 0; i < meals.GetSize(); i++)
		{
			if (meals[i].GetId() == id) {
				cout << meals[i] << endl;
			}
		}
	}
	Meal* GetMealById(int id) {
		for (size_t i = 0; i < meals.GetSize(); i++)
		{
			if (meals[i].GetId() == id) {
				return &meals[i];
			}
		}
	}
	void MealsPop(int index) {
		meals.Pop(index);
	}
	int GetMealCount() {
		return meals.GetSize();
	}


	void AddMeal() {
		cin.ignore();
		cin.clear();
		cout << "Enter name : ";
		string name;
		getline(cin, name);
		cout << "Enter price : ";
		double price;
		cin >> price;
		cout << endl;
		Meal newMeal(price, name);
		cout << "PRODUCT COUNT : ";
		int count;
		cin >> count;
		for (size_t i = 1; i <= count; i++)//2
		{
			cin.ignore();
			cin.clear();
			cout << "Enter " << i << " product name : ";
			string pName;
			getline(cin, pName);
			cout << "Enter " << i << " product price : ";
			double price;
			cin >> price;
			cout << "Enter " << i << " product count : ";
			int count;
			cin >> count;
			Product p(name, price, count);
			newMeal.AddProduct(p);
		}
		meals.Push(newMeal);
		cout << "Meal added successfully" << endl;
	};
	void UptadeMeals(int id) {
		auto meal = GetMealById(id);
		cout << "[1] Name" << endl;
		cout << "[2] Price" << endl;
		cout << "[3] Products" << endl;
		cout << "Enter select : " << endl;
		int select;
		cin >> select;
		if (select == 1) {
			cin.ignore();
			cin.clear();
			cout << "Enter meal name : ";
			string name;
			getline(cin, name);
			meal->SetName(name);
		}
		else if (select == 2) {
			cout << "Enter meal price : ";
			double price;
			cin >> price;
			meal->SetPrice(price);
		}
		else if (select == 3) {
			meal->ShowProductOfMeal();
			meal->UpdateProduct();
		}
	}
};

int Kitchen::notificationCount = 0;

class Client {
	Stack<Kitchen>menu;
	int tableNo;
public:
	Client() = default;
	Client(const int& tableNo) {
		SetTable(tableNo);
	}
	void SetTable(const int& tableNo) {
		assert(tableNo > 0 && "Table no is empty");
		this->tableNo = tableNo;
	}
	int GetTableNo()const {
		return tableNo;
	}
	void AddMenu(Kitchen& kitchen) {
		menu.Push(kitchen);
	}
	void ShowMenu() {
		for (size_t i = 0; i < menu.GetSize(); i++)
		{
			cout << endl;
			menu[i].ShowName();
			cout << endl << endl;
		}
	}
};

class Stock {
public:
	vector<Product>products;
	Stock() = default;
	void AddProduct(Product& product) {
		products.push_back(product);
	}
	void Show() {
		int id = 1;
		cout << "------ALL PRODUCTS------" << endl << endl;
		for (size_t i = 0; i < products.size(); i++)
		{
			cout << "Id : " << id++ << endl << endl;
			cout << products[i];
			cout << "Product count : " << products[i].GetCount() << endl << endl;
		}
	}
	auto* GetProductById(int index) {
		for (size_t i = 0; i < products.size(); i++)
		{
			int id = products[i].GetId();
			if (products[i].GetId() == index) {
				return &products[i];
			}
		}
	}
	bool ProductCount(int index, int count) {
		auto product = GetProductById(index);
		int temp = product->GetCount() - count;
		if (temp >= 0) {
			products[index].SetCount(temp);
			return true;
		}
		return false;
	}
	void DeleteIngredientsByID(int index) {
		if (index == 1) {
			products.pop_back();
		}
		else {
			products.erase(products.begin() + index);
		}
	}

	void ShowProductCount() {
		for (size_t i = 0; i < products.size(); i++)
		{
			cout << products[i].GetId() << " - " << products[i].GetName() << " count " << products[i].GetCount() << endl << endl;
		}

	}

	int GetProductCount() {
		return products.size();
	}
};


class FileHelper {
public:
	static string filename;

	static void Save(Stock& stock) {
		ofstream fout(filename, ios::app);
		if (fout.is_open()) {
			int count1 = stock.GetProductCount();
			fout << count1 << endl;
			for (size_t i = 0; i < stock.products.size(); i++)
			{
				fout << stock.products[i].GetId() << " " << stock.products[i].GetName() << " " << stock.products[i].GetPrice() << " " << stock.products[i].GetCount() << endl;
			}
			fout.close();
		}

	}


	static Stock Read() {
		Stock stock;
		ifstream fin(filename);
		int count1;
		fin >> count1;
		if (fin.is_open()) {

			for (size_t i = 0; i < count1; i++)
			{
				Product p;
				int id;
				string name;
				double price;
				int count;

				fin >> id;
				fin >> name;
				fin >> price;
				fin >> count;

				p.SetId(id);
				p.SetName(name);
				p.SetPrice(price);
				p.SetCount(count);
				stock.AddProduct(p);
			}
			fin.close();

			return stock;
		}
	}
};

string FileHelper::filename = "products.txt";
