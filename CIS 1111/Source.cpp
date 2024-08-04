// Name: Andrii Malakhovtsev
// Date: 08/03/2024
// Program Name: Space Restaurant 2.0
// Program Description: Final project using all the learnt material to build a restaurant console app

#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<fstream>
#include<vector>

using namespace std;

const string FIRST_ITEM_NAME = "Saturn Sushi",
SECOND_ITEM_NAME = "Meteorite Pizza",
THIRD_ITEM_NAME = "Sun Shake",
FOURTH_ITEM_NAME = "\"Milky Way\" Toast";

const double FISRT_ITEM_PRICE = 33.39,
SECOND_ITEM_PRICE = 145.45,
THIRD_ITEM_PRICE = 19.99,
FOURTH_ITEM_PRICE = 28.00;

void showMenu();
vector<int> getCustomerMenuChoices(int customerIndex, int customerNumber);
int getMenuOption(bool lastCustomer);
void showBill(vector<vector<int>> customersMenuChoices);
double getPerCustomerBillPreview(vector<int> customerMenuChoices);
double getMenuItemPrice(int itemNumber);
string getMenuItemName(int itemNumber);
void getMenuItemInfo(int itemNumber, double& pickedItemPrice, string& pickedItemName);
string getCustomerFileName(int customerNumber);
void writeCustomerInfoToFile(vector<int> customerMenuChoices, int customerNumber);
vector<int> readCustomerMenuItemsFromFile(int customerNumber);
void removeAllCreatedFiles(vector<string> files);
vector<vector<int>> readCustomersMenuChoicesFromFiles(int customerNumber);

int main()
{
	cout << "Welcome to the Space Restaurant!" << endl;

	cout << "How many people are going to eat today? ";
	int customerNumber;
	cin >> customerNumber;

	vector<string> filesCreated;

	for (int customerIndex = 0; customerIndex < customerNumber; customerIndex++)
	{
		vector<int> customerMenuChoices = getCustomerMenuChoices(customerIndex, customerNumber);
		writeCustomerInfoToFile(customerMenuChoices, customerIndex);
		filesCreated.push_back(getCustomerFileName(customerIndex));
	}

	showBill(readCustomersMenuChoicesFromFiles(customerNumber));

	// END
	removeAllCreatedFiles(filesCreated);
	cout << endl << endl;
	system("pause");
	return 0;
}

vector<int> getCustomerMenuChoices(int customerIndex, int customerNumber)
{
	vector<int> customerMenuChoices;
	bool lastCustomer = customerIndex == customerNumber - 1;

	cout << "\nWhat does customer #" << customerIndex + 1 << " wants to get today?" << endl;

	int menuOption;
	showMenu();
	do
	{
		menuOption = getMenuOption(lastCustomer);
		if (menuOption != 0) customerMenuChoices.push_back(menuOption);
	} while (menuOption != 0);
	return customerMenuChoices;
}

void showMenu()
{
	cout << endl;
	cout << fixed << setprecision(2);
	cout << setw(30) << right << "MENU:" << endl;
	cout << setw(25) << left << "1. " + FIRST_ITEM_NAME + ": " << setw(10) << right << '$' << FISRT_ITEM_PRICE << endl;
	cout << setw(25) << left << "2. " + SECOND_ITEM_NAME + ": " << setw(10) << right << '$' << SECOND_ITEM_PRICE << endl;
	cout << setw(25) << left << "3. " + THIRD_ITEM_NAME + ": " << setw(10) << right << '$' << THIRD_ITEM_PRICE << endl;
	cout << setw(25) << left << "4. " + FOURTH_ITEM_NAME + ": " << setw(10) << right << '$' << FOURTH_ITEM_PRICE << endl;
	cout << endl;
}

int getMenuOption(bool lastCustomer)
{
	string continueText = lastCustomer ? "checkout or " : "continue to the next person";
	cout << "Enter the number of menu item or 0 to " << continueText << ": ";
	int itemNumber;
	cin >> itemNumber;
	return itemNumber;
}

void writeCustomerInfoToFile(vector<int> customerMenuChoices, int customerIndex)
{
	ofstream outFile(getCustomerFileName(customerIndex));

	for (int customerMenuChoice = 0; customerMenuChoice < customerMenuChoices.size(); customerMenuChoice++)
	{
		outFile << customerMenuChoices[customerMenuChoice] << "\n";
	}

	outFile.close();
}

vector<vector<int>> readCustomersMenuChoicesFromFiles(int customerNumber) 
{
	vector<vector<int>> customersMenuChoices;

	for (int customerIndex = 0; customerIndex < customerNumber; customerIndex++)
	{
		customersMenuChoices.push_back(readCustomerMenuItemsFromFile(customerIndex));
	}

	return customersMenuChoices;
}

vector<int> readCustomerMenuItemsFromFile(int customerIndex)
{
	ifstream inFile(getCustomerFileName(customerIndex));
	vector<int> customerInfoFromFile;

	int value;
	while (inFile >> value) 
	{
		customerInfoFromFile.push_back(value);
	}

	inFile.close();
	return customerInfoFromFile;
}

string getCustomerFileName(int customerIndex)
{
	return "Customer-" + to_string(customerIndex) + ".txt";
}

void showBill(vector<vector<int>> customersMenuChoices)
{
	cout << endl;
	cout << fixed << setprecision(2);
	cout << setw(30) << right << "BILL:" << endl;
	
	double totalPreTax = 0.0;

	for (int customerNumber = 0; customerNumber < customersMenuChoices.size(); customerNumber++)
	{
		vector<int> currentCustomerMenu = customersMenuChoices[customerNumber];

		cout << "Customer #" << customerNumber + 1 << " chose: ";
		for (int customerMenuChoice = 0; customerMenuChoice < currentCustomerMenu.size(); customerMenuChoice++)
		{
			bool lastLoop = customerMenuChoice == currentCustomerMenu.size() - 1;
			int menuItem = currentCustomerMenu[customerMenuChoice];

			cout << getMenuItemName(menuItem);

			string divider = lastLoop ? " " : ", ";
			cout << divider;
		}
		cout << "($" << getPerCustomerBillPreview(currentCustomerMenu) << ")";
		totalPreTax += getPerCustomerBillPreview(currentCustomerMenu);
		cout << endl;
	}

	cout << endl;
	cout << "Your total (pre-tax) is: $" << totalPreTax << endl;
	cout << "Your total is (tax 20%): $" << totalPreTax + (totalPreTax * 0.2);
}

double getPerCustomerBillPreview(vector<int> customerMenuChoices) 
{
	double perCustomerBill = 0.0;
	for (int chosenMenuItem = 0; chosenMenuItem < customerMenuChoices.size(); chosenMenuItem++)
	{
		perCustomerBill += getMenuItemPrice(customerMenuChoices[chosenMenuItem]);
	}
	return perCustomerBill;
}

double getMenuItemPrice(int itemNumber) 
{
	double pickedItemPrice;
	string fictionalName;
	getMenuItemInfo(itemNumber, pickedItemPrice, fictionalName);
	return pickedItemPrice;
}

string getMenuItemName(int itemNumber)
{
	string pickedItemName;
	double fictionalPrice;
	getMenuItemInfo(itemNumber, fictionalPrice, pickedItemName);
	return pickedItemName;
}

void getMenuItemInfo(int itemNumber, double& pickedItemPrice, string& pickedItemName)
{
	switch (itemNumber)
	{
		case 1:
			pickedItemPrice = FISRT_ITEM_PRICE;
			pickedItemName = FIRST_ITEM_NAME;
			break;
		case 2:
			pickedItemPrice = SECOND_ITEM_PRICE;
			pickedItemName = SECOND_ITEM_NAME;
			break;
		case 3:
			pickedItemPrice = THIRD_ITEM_PRICE;
			pickedItemName = THIRD_ITEM_NAME;
			break;
		case 4:
			pickedItemPrice = FOURTH_ITEM_PRICE;
			pickedItemName = FOURTH_ITEM_NAME;
			break;
	}
}

void removeAllCreatedFiles(vector<string> files)
{
	for (int index = 0; index < files.size(); index++)
	{
		remove(files[index].c_str());
	}
}