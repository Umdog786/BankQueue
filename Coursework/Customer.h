#pragma once
#include <iostream>
#include <string>
#include <random>
using namespace std;

class Customer
{
public:
    Customer();
    void LoadCustomers(ifstream& inputCustomerListFile); // Loads customer info from 'CustomerList.txt'
                                                         // extracts key data and stores in variables
    string GetCustomerUsername(); // Returns specified customer's username
    string GetCustomerFirstName(); // Returns specified customer's first name
    string GetCustomerLastName(); // Returns specified customer's last name
    void DisplayCustomer(); // Displays specified customer's details

private:
    string customerUsername; // Stores customer's username
    string customerFirstName; // Stores customer's first name
    string customerLastName; // Stores customer's last name
};