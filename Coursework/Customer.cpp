#include <iostream>
#include <string>
#include <random>
#include <fstream>
using namespace std;
#include "Customer.h"

Customer::Customer() // Default constructor for assigning default values to all private variables
{
    customerUsername = "";
    customerFirstName = "";
    customerLastName = "";
}

void Customer::LoadCustomers(ifstream& inputCustomerListFile) {  // Passes 'CustomerList.txt' as a reference
    inputCustomerListFile >> customerUsername >> customerFirstName >> customerLastName; // Extracts customer information and stores in variables
}

string Customer::GetCustomerUsername()
{
    return customerUsername; // Returns specified customer's username
}

string Customer::GetCustomerFirstName() {
    return customerFirstName; // Returns specified customer's first name
}

string Customer::GetCustomerLastName() {
    return customerLastName; // Returns specified customer's last name
}

void Customer::DisplayCustomer() { // Display customer information
    cout << "Username: " << customerUsername << endl <<
            "First Name: " << customerFirstName << endl <<
            "Last Name: " << customerLastName << endl;
}



