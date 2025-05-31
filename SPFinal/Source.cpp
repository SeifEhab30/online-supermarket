#include<iostream>
#include<fstream>
#include<string>
#include <conio.h>
#include<stdio.h>
#include <windows.h> 
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#define categsize 5
#define psize 25
#define cart_size 100
int cnt = 0;
int iD;
struct customer {
	int ID;
	string username;
	long long phone_number;
	string location;
	string password;
};
customer users[100];

string Categories[categsize] = { "Meat","Snacks","Beverages","Baking","Dairy" };

struct product {
	string name, category, pDate, eDate;
	float price;
	int code;
	int quantity;
}products[psize];

struct cart {
	string name;
	float price, quantity_price;
	int code;
	int quantity;
}purchased_p[cart_size] = {};
void store() {
	ifstream in_file{ "Customer.txt" };
	if (!in_file) {
		cerr << "Error";

	}
	else {
		string line;
		int i = 0;

		while (in_file) {
			in_file >> users[i].ID >> users[i].username >> users[i].phone_number >> users[i].location >> users[i].password;
			i++;
			cnt++;
		}

		in_file.close();
	}
}

void intfile(product products[]) {
	int i = 0;
	ifstream thefile{ "data.txt" };

	if (!thefile) {
		cout << "Error";
	}
	for (i; i < 25; i++) {// read product data from the file
		thefile >> products[i].name
			>> products[i].category
			>> products[i].pDate
			>> products[i].eDate
			>> products[i].price
			>> products[i].code;
	}
	thefile.close();
}

void outfile(product products[]) {
	ofstream write("data.txt");//write to file
	for (int i = 0; i < psize; i++) {
		write << products[i].name << " "
			<< products[i].category << " "
			<< products[i].pDate << " "
			<< products[i].eDate << " "
			<< products[i].price << " "
			<< products[i].code << "" << endl;
	}
	write.close();
}
void Intro() {
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Welcome To The Online Supermarket!                       \n";
}
bool login() {
	string name, pass;
	char x = '\0', y = '\0';
	bool isUser = false;
	int i = 0;
	int j, temp;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Enter your username : ";
	cin >> name;
	for (j = 0; j < cnt; j++) {
		if (name == users[j].username) {
			pass = users[j].password;
			iD = users[j].ID;
			isUser = true;
			break;
		} //to confirm user is registered
		else pass = { "00000000000000000000000000" };
	}
	cout << "Enter your password : ";

	while (x != '\r' && i < 26) {
		x = _getch();
		if ((x != '\r') && (x != '\b')) {
			cout << '*';
			if (x != pass[i]) {
				isUser = false;
			}
			temp = y; //to use incase of backspace
			y = x;
			i++;
		}
		else if (x == '\b') {
			cout << "\b \b";
			i--;
			isUser = true;
			y = temp;
		}
	}
	if (y != pass.back()) {
		isUser = false;
	} //password loop stops at the second to last digit 
	cout << endl;
	SetConsoleTextAttribute(hConsole, 12);
	if (isUser) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Login successful!" << '\n';
	}
	else cerr << "Invalid username or password. Please try again.";
	return isUser;
}
void isUser() {
	while (!login()) {
		cout << endl;

	}
}
float  TOTAL_price() {
	float  total_price = 0;
	for (int i = 0; i < cart_size; i++) {
		total_price += purchased_p[i].quantity_price;
	}
	return total_price;
}

void view_order(cart purchased_p[]) {
	int x = 1;
	cout << "-------------------------------------Your Cart Contain-------------------------------------\n\n";
	SetConsoleTextAttribute(hConsole, 5);
	cout << "number\tCode\tName\tQuantity\tPrice for one\t Quantity Price\n";
	for (int i = 0; i < cart_size; i++) {
		SetConsoleTextAttribute(hConsole, 13);
		if (purchased_p[i].code != 0) {
			cout << x << ")\t" << purchased_p[i].code << "\t"
				<< purchased_p[i].name << "\t"
				<< purchased_p[i].quantity << "\t\t"
				<< purchased_p[i].price << "\t\t  "
				<< purchased_p[i].quantity_price << "\n";
			x++;
		}
		else
			continue;
	}
	SetConsoleTextAttribute(hConsole, 11);
	cout << "The total price is " << TOTAL_price() << "  Egypt Pound\n";
}
void buyFromCategory(string category) {
	string answer;
	do {
		SetConsoleTextAttribute(hConsole, 14);
		cout << "Would you like to buy anything from the " << category << " category? (Y/N) ";
		cin >> answer;
		if (answer == "Y" || answer == "y") {
			// User wants to buy something from this category
			int code, quantity;
			cout << "Please enter the code of the product you would like to buy: ";
			while (!(cin >> code)) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Invaild input please try again.   " << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cin.clear();
				cin.ignore(100, '\n');
			}
			bool found = false;
			for (int i = 0; i < psize; i++) {
				if (products[i].code == code && products[i].category == category) {
					found = true;
					cout << "How many " << products[i].name << " would you like to buy? ";
					while (!(cin >> quantity)) {
						SetConsoleTextAttribute(hConsole, 12);
						cout << "Invaild input please try again. " << endl;
						SetConsoleTextAttribute(hConsole, 7);
						cin.clear();
						cin.ignore(100, '\n');
					}
					//save info into cart arr
					for (int j = 0; j < cart_size; j++) {
						if (purchased_p[j].code == 0) {
							purchased_p[j].code = code;
							purchased_p[j].name = products[i].name;
							purchased_p[j].price = products[i].price;
							purchased_p[j].quantity = quantity;
							purchased_p[j].quantity_price = purchased_p[j].price * quantity;
							break;
						}
					}
					cout << "You have purchased " << quantity
						<< " " << products[i].name << " from the "
						<< category << " category." << endl;
				}
			}

			if (!found) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Product not found in the " << category << " category." << endl;
			}
		}
		else if (answer == "N" || answer == "n") {
			// User does not want to buy anything from this category
			cout << "No problem." << endl;
			break;
		}
		else {
			// Invalid input
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid input. Please try again." << endl;
			SetConsoleTextAttribute(hConsole, 7);
			answer = "y";
			continue;
		}
	} while (answer == "Y" || answer == "y");
}

void viewMenu() {  // view category menu
	char choose = 'A';
	SetConsoleTextAttribute(hConsole, 14);
	cout << "\n------------------------  Categories  ------------------------ \n";
	for (int i = 0; i < categsize; i++) {
		cout << choose << ")" << Categories[i] << "\t";
		choose++;
	}
	cout << endl;
}

void viewproducts(product products[]) {// view product of a specific category
	char categ;
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Please enter the character of one category to see products:  ";
	cin >> categ;
	do {
		SetConsoleTextAttribute(hConsole, 6);
		switch (categ) {
		case 'A':
		case 'a':
			cout << "\n------------------------  Meat Category  ------------------------ \n";
			cout << "Code\t" << "Name\t\t\t" << "Price\t\t\t" << "Production Date\t\t\t" << "Expired Date\n" << endl;
			for (int i = 0; i < psize; i++) {
				if (products[i].category == "meat") {
					cout << products[i].code << "\t"
						<< products[i].name << "\t\t\t"
						<< products[i].price << "\t\t\t"
						<< products[i].pDate << "\t\t\t"
						<< products[i].eDate << endl;
				}
			}
			buyFromCategory("meat");//previous buyFromCategory("Meat category")
			break;
		case'B':
		case'b':
			cout << "\n------------------------  Snacks Category  ------------------------ \n";
			cout << "Code\t" << "Name\t\t\t" << "Price\t\t\t" << "Production Date\t" << "Expired Date" << endl << endl;
			for (int i = 0; i < psize; i++) {
				if (products[i].category == "snacks") {
					cout << products[i].code << "\t"
						<< products[i].name << "\t\t\t"
						<< products[i].price << "\t\t\t"
						<< products[i].pDate << "\t"
						<< products[i].eDate << endl;
				}
			}buyFromCategory("snacks");//previous buyFromCategory("snacks category")
			break;
		case'C':
		case'c':
			cout << "\n------------------------  Beverages Category  ------------------------ \n";
			cout << "Code\t" << "Name\t\t\t" << "Price\t\t\t" << "Production Date\t" << "Expired Date" << endl << endl;
			for (int i = 0; i < psize; i++) {
				if (products[i].category == "beverages") {
					cout << products[i].code << "\t"
						<< products[i].name << "\t\t\t"
						<< products[i].price << "\t\t\t"
						<< products[i].pDate << "\t"
						<< products[i].eDate << endl;
				}
			}buyFromCategory("beverages");//previous buyFromCategory("beverages category")
			break;
		case'D':
		case'd':
			cout << "\n------------------------ Baking Category  ------------------------ \n";
			cout << "Code\t" << "Name\t\t\t" << "Price\t\t\t" << "Production Date\t" << "Expired Date" << endl << endl;
			for (int i = 0; i < psize; i++) {
				if (products[i].category == "baking") {
					cout << products[i].code << "\t"
						<< products[i].name << "\t\t\t"
						<< products[i].price << "\t\t\t"
						<< products[i].pDate << "\t"
						<< products[i].eDate << endl;
				}
			}buyFromCategory("baking");//previous buyFromCategory("Baking category")
			break;
		case'E':
		case'e':
			cout << "\n------------------------ Dairy Category  ------------------------ \n";
			cout << "Code\t" << "Name\t\t\t" << "Price\t\t\t" << "Production Date\t" << "Expired Date" << endl << endl;
			for (int i = 0; i < psize; i++) {
				if (products[i].category == "dairy") {
					cout << products[i].code << "\t"
						<< products[i].name << "\t\t\t"
						<< products[i].price << "\t\t\t"
						<< products[i].pDate << "\t"
						<< products[i].eDate << endl;
				}
			}buyFromCategory("dairy");//previous buyFromCategory("Dairy category")
			break;
		default:
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid input. Please try again." << endl;
			SetConsoleTextAttribute(hConsole, 7);
			cin >> categ;
			continue;
		}
		SetConsoleTextAttribute(hConsole, 14);
		cout << "would you like to see another product? (Y/N)";
		while (categ != 'y' || categ != 'Y' || categ != 'n' || categ != 'N') {
			cin >> categ;
			if (categ == 'n' || categ == 'N')break;
			else if (categ == 'Y' || categ == 'y') {
				viewMenu();
				cout << "Please enter the character of one category to see products:  ";
				cin >> categ;
				break;
			}
			else {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Invalid input. Please try again." << endl;
				SetConsoleTextAttribute(hConsole, 7);
				continue;
			}
		}
		if (categ == 'Y' || categ == 'y') continue;
		else if (categ == 'n' || categ == 'N')break;
	} while (true);
}

void modifytheorder()
{
	string answer2;
	int code1, code2;
	view_order(purchased_p);
	do {
		SetConsoleTextAttribute(hConsole, 11);
		cout << "( D ) Delete an item \n( C ) Change quantity \n( E ) Delete ALL items \n( Y ) Confirm your order\n( G ) Go back to the main menu \n ";
		cin >> answer2;
		if (answer2 == "d" || answer2 == "D") {
			SetConsoleTextAttribute(hConsole, 13);
			cout << "Enter the code of the item you want to delete \n";
			while (!(cin >> code1)) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Invaild input please try again." << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cin.clear();
				cin.ignore(100, '\n');
			}
			bool flag1 = false;
			for (int i = 0; i < cart_size; i++) {
				if (code1 == purchased_p[i].code) {
					flag1 = true;
					SetConsoleTextAttribute(hConsole, 12);
					cout << "you have deleted:" << purchased_p[i].name << endl;
					purchased_p[i].code = 0;
					purchased_p[i].quantity_price = 0;
				}
			}
			if (flag1 == false) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Invalid code please enter correct code\n";
				SetConsoleTextAttribute(hConsole, 7);
				continue;
			}
			else if (flag1 == true) {
				SetConsoleTextAttribute(hConsole, 13);
				cout << "ORDER after modefication\n";
				view_order(purchased_p);
				continue;
			}
		}
		else if (answer2 == "c" || answer2 == "C") {
			SetConsoleTextAttribute(hConsole, 13);
			cout << "Enter the code of the item you want to change it's quantity \n";
			while (!(cin >> code2)) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Invaild input please try again." << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cin.clear();
				cin.ignore(100, '\n');
			}
			bool flag2 = false;
			int N_quantity;
			for (int i = 0; i < cart_size; i++) {
				if (code2 == purchased_p[i].code) {
					flag2 = true;
					SetConsoleTextAttribute(hConsole, 13);
					cout << "Enter new quantity\n";
					while (!(cin >> N_quantity)) {
						SetConsoleTextAttribute(hConsole, 12);
						cout << "Invaild input please try again." << endl;
						SetConsoleTextAttribute(hConsole, 7);
						cin.clear();
						cin.ignore(100, '\n');
					}
					purchased_p[i].quantity = N_quantity;
					purchased_p[i].quantity_price = N_quantity * purchased_p[i].price;
					break;
				}
			}

			if (flag2 == false) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Invalid code please enter correct code\n";
				continue;
			}
			else if (flag2 == true) {
				SetConsoleTextAttribute(hConsole, 11);
				cout << "ORDER after modefication\n";
				view_order(purchased_p);
				continue;
			}
		}

		else if (answer2 == "E" || answer2 == "e") {
			string answer1;
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Are you sure you want to delete ALL the items in your cart ( Y / N ) ?\n";
			cin >> answer1;
			if (answer1 == "y" || answer1 == "Y") {
				for (int i = 0; i < cart_size; i++) {
					purchased_p[i].code = 0;
					purchased_p[i].quantity = 0;
					purchased_p[i].price = 0;
					purchased_p[i].quantity_price = 0;
				}
			}
			SetConsoleTextAttribute(hConsole, 11);
			cout << "ORDER after modefication\n";
			view_order(purchased_p);
			continue;
		}
		else if (answer2 == "G" || answer2 == "g") {
			break;

		}
		else if (answer2 == "y" || answer2 == "Y") {
			bool flag = false;
			for (int i = 0; i < cart_size; i++) {
				if (purchased_p[i].code != 0) {
					flag = true;
					break;
				}
			}
			if (flag == false) {
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Your cart is empty.\n";
			}
			else if (flag == true) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << "Your order has been processed and will be shipped in 3 days.\n";
			}
			for (int i = 0; i < cart_size; i++)
			{
				purchased_p[i].code = 0;
				purchased_p[i].quantity = 0;
				purchased_p[i].price = 0;
				purchased_p[i].quantity_price = 0;
			}
			break;
		}
		else {
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Please enter a valid character \n";
			SetConsoleTextAttribute(hConsole, 11);

		}
	} while (answer2 != "g" || answer2 != "G");

}
void editInfo(int ID) {
	ofstream out_file{ "customer.txt" };
	if (!out_file) {
		cerr << "Error 2";
	}
	int x;
	SetConsoleTextAttribute(hConsole, 11);
	cout << "What would you like to edit?" << endl;
	cout << "1-Username" << endl << "2-Password" << endl << "3-location" << endl << "4-phone number" << endl << "5-to exit" << endl;
	while (!(cin >> x)) {
		SetConsoleTextAttribute(hConsole, 12);
		cout << "Invaild input please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		cin.clear();
		cin.ignore(100, '\n');
	}
	SetConsoleTextAttribute(hConsole, 13);
	switch (x) {
	case 1:cout << "Enter your new username : ";
		cin >> users[iD - 1].username;
		cout << "Your username has been changed.";
		break;
	case 2:cout << "Enter your new password : ";
		cin >> users[iD - 1].password;
		cout << "Your password has been changed.";
		break;
	case 3:cout << "Enter your new location : ";
		cin >> users[iD - 1].location;
		cout << "Your location has been changed.";
		break;
	case 4:cout << "Enter your new phone number : ";
		cin >> users[iD - 1].phone_number;
		cout << "Your phone number has been changed.";
		break;
	case 5:break;
		SetConsoleTextAttribute(hConsole, 12);
	default:SetConsoleTextAttribute(hConsole, 12);
		cout << "Invalid input please try again." << endl;
		SetConsoleTextAttribute(hConsole, 7);

	}
	cout << endl;
	for (int i = 0; i < cnt; i++) {
		out_file << users[i].ID << '\t' << users[i].username << '\t' << users[i].phone_number << '\t' << users[i].location << '\t' << users[i].password << '\n';
	}
	out_file.close();
}
void viewInfo(int ID) {
	char ans;
	SetConsoleTextAttribute(hConsole, 8);
	cout << "Your Username : " << users[ID - 1].username << endl;
	cout << "Your Password : " << users[ID - 1].password << endl;
	cout << "Your ID : " << users[ID - 1].ID << endl;
	cout << "Your Phone Number : " << users[ID - 1].phone_number << endl;
	cout << "Your Location : " << users[ID - 1].location << endl;
	do {
		SetConsoleTextAttribute(hConsole, 9);
		cout << "would you like to edit your info? (Y/N)" << endl;
		cin >> ans;
		SetConsoleTextAttribute(hConsole, 12);
		if (ans == 'y' || ans == 'Y') editInfo(iD);
		else if (ans == 'n' || ans == 'N') {
			cout << "No data changed." << endl;
			break;
		}

		else {
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid input please try again." << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	} while (ans != 'y' || ans != 'Y');
}
void logout();
void action();
void main() {
	intfile(products);
	store();
	Intro();
	isUser();
	action();
}

void logout() {
	{
		int logout, a = 1;
		SetConsoleTextAttribute(hConsole, 10);
		printf("\npress 1 to logout and login with a different account\n");
		SetConsoleTextAttribute(hConsole, 12);
		printf("\npress any other key to logout and close the program\n");
		SetConsoleTextAttribute(hConsole, 7);
		scanf_s("%d", &logout);
		for (int i = 0; i < cart_size; i++)
		{
			purchased_p[i].code = 0;
			purchased_p[i].quantity = 0;
			purchased_p[i].price = 0;
			purchased_p[i].quantity_price = 0;
		}
		if (logout == a)
		{
			main();
		}
	}
}
void action() {
	int ans;
	char x;

	do {
		SetConsoleTextAttribute(hConsole, 11);
		cout << "\n------------------------ Main menu ------------------------ \n";
		cout << "1-View your information." << endl << "2-View products menu." << endl << "3-View your cart." << endl << "4-Logout" << endl;
		cout << "What would you like to do?" << endl;
		while (!(cin >> ans)) {
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invaild input please try again.   " << endl;
			SetConsoleTextAttribute(hConsole, 7);
			cin.clear();
			cin.ignore(100, '\n');
		}
		switch (ans) {
		case 1:viewInfo(iD);
			break;
		case 2:viewMenu();
			cout << "Would you like to see a specific category?(Y/N)";
			do {
				cin >> x;
				if (x == 'y' || x == 'Y')viewproducts(products);
				else if (x == 'n' || x == 'N') {
					break;
				}
				else {
					SetConsoleTextAttribute(hConsole, 12);
					cout << "Invalid input please try again." << endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			} while (x != 'y' && x != 'Y');
			break;
		case 3:modifytheorder();
			break;
		case 4:break;
		default:SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid input please try again. " << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}

	} while (ans != 4);
	if (ans == 4) {
		logout();
	}
}

