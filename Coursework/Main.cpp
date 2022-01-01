// BankQueueClientSide.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Login.h"
#include "Employee.h"
#include "Customer.h"
const int employeeNumber = 3; // Number of Employees
const int customerNumber = 105; // Number of Customers

int main()
{
    Login login; // Initializes a new instance of the Login object called login
    Employee employeeList[employeeNumber]; // Initializes a list where each element is a new instance of the Employee object
    Customer customerList[customerNumber]; // Initializes a list where each element is a new instance of the Customer object
                                            // Size of both employeeList and customerList is dependant on the constants employeeNumber and customerNumber respectively
    ifstream inputCustomerListFile("CustomerList.txt"); // Initializes a new ifstream variable and points to the Customer List file
    ifstream inputEmployeeListFile("EmployeeList.txt"); // Initializes a new ifstream variable and points to the Employee List file
    ifstream inputCredentialsFile("Credentials.txt"); // Initializes a new ifstream variable and points to the Credentials file
    ofstream outputAppointmentLogFile("AppointmentLog.txt", ofstream::out | ofstream::trunc); // Initializes a new ofstream variable and points to the Appointment Log file
                                                                                                 // Opens with 'truncate' flag so the file is cleared everytime the program runs
    int randomCustomer = 0; // Variable to select a random customer when making an appointment
    int randomTime = 0; // Variable to select a random time interval when making an appointment
    int currentTime = 0; // Variable for holding the current time, alters when 'Advance Time' is selected
    string selectEmployeeCancelAppointment; // Variable for selecting which employee holds the appointment you wish to cancel

    login.LoadCredentials(inputCredentialsFile); // Calls method for loading the login credentials from the 'Credentials.txt' file

    for (int i=0; i<customerNumber;i++) // Iterates over every customer in 'CustomerList.txt'
    {
        customerList[i].LoadCustomers(inputCustomerListFile); // Loads each customer into a separate element of customerList[]
    }
    inputCustomerListFile.close(); // Closes 'CustomerList.txt' as it won't be needed again

    for (int i=0;i<employeeNumber;i++) // Iterates over every employee in 'EmployeeList.txt'
    {
        employeeList[i].LoadEmployee(inputEmployeeListFile); // Loads each employee into a separate element of employeeList[]
        employeeList[i].PopulateScheduleArray(); // Populates each employee's timetable with default values
    }
    inputEmployeeListFile.close(); // Closes 'EmployeeList.txt' as it won't be needed again

    do
    {
        cout << string(20, '-') << endl;
        login.EnterUsername(); // Calls a method to allow the user to enter a username
        login.EnterPassword(); // Calls a method to allow the user to enter a password
        cout << string(20, '-') << endl;
    } while (!login.LoginSuccessful()); // Repeats until either the login is successful or they run out of attempts

    if (login.GetLoginAttempts() == 0)
    {
        exit(1); // If they run out of attempts, the program ends
    }

    while (!login.GetMenuPass()) // While the user has not selected 'Logout' from the menu, menu is repeatedly displayed
    {

        if (currentTime != 24){ // Program ends when the current time reaches 17:00
            cout << string(20, '-') << endl;
            employeeList[0].GetTimeElement(currentTime); // Displays the current time
            cout << string(20, '-') << endl;
        }

        login.SetMenuSelection(); // Calls the function to display the main menu

        if (login.GetMenuSelection() == "1") // If the user selects 'View Employee Timetables'
        {
            for (int i = 0; i < employeeNumber; i++) { // Iterates over each employee
                cout << string(5, '-') << "Employee " << i + 1 << string(5, '-') << endl;
                cout << "Name: " << employeeList[i].GetEmployeeName() << endl; // Displays each employee's Name
                cout << "Job:  " << employeeList[i].GetEmployeeJob() << endl; // Displays each employee's Job
                employeeList[i].GetScheduleArray(); // Displays each employee's full timetable
            }
            cout << string(20, '-') << endl;
        }
        else if (login.GetMenuSelection() == "2") // If the user selects 'Change Username'
        {
            login.ChangeUsername(); // Calls the 'ChangeUsername' method
        }
        else if (login.GetMenuSelection() == "3") // If the user selects 'Change Password'
        {
            login.ChangePassword(); // Calls the 'ChangePassword' method
        }
        else if (login.GetMenuSelection() == "4") // If the user selects 'Logout'
        {
            login.SetMenuPass(); // Sets menuPass to true to escape the while loop and end the program
        }
        else if (login.GetMenuSelection() == "5") // If the user selects 'View Customer Information'
        {
            for (int i = 0; i < customerNumber; i++) { // Iterates over each customer
                cout << string(5, '-') << "Customer " << i + 1 << string(5, '-') << endl;
                cout << "Username: " << customerList[i].GetCustomerUsername() << endl; // Displays each customer's Username
                cout << "First Name:  " << customerList[i].GetCustomerFirstName() << endl; // Displays each customer's First Name
                cout << "Last Name:  " << customerList[i].GetCustomerLastName() << endl; // Displays each customer's Last Name
            }
            cout << string(20, '-') << endl;

        }
        else if (login.GetMenuSelection() == "6") // If the user selects 'Advance Time'
        {
            if (currentTime == 23){
                employeeList[0].GetTimeElement(currentTime);
                cout << "The day has ended, Goodbye."; // If so, display goodbye message
                exit(1);
            }
            else {
                srand (time(NULL)); // Seeds random number generation based on time
                cout << "These are the events that have occurred: " << endl;
                cout << string(20, '-') << endl;
                for (int i = 0; i < rand() % 5 + 1; ++i) { // Randomly selects how many appointments will be made
                    randomCustomer = rand() % 105; // Randomly selects a customer
                    while ((randomTime = rand() % 24) <= currentTime) // Randomly selects a timeslot
                    {
                    }
                    employeeList[rand() % employeeNumber].MakeAppointment(customerList[randomCustomer].GetCustomerUsername(),
                                                                          customerList[randomCustomer].GetCustomerFirstName(),
                                                                          customerList[randomCustomer].GetCustomerLastName(),
                                                                          randomTime,
                                                                          outputAppointmentLogFile);
                    // Calls MakeAppointment() method with randomly selected data
                    cout << string(20, '-') << endl;

                }
            }


            ++currentTime;
        }

        else if (login.GetMenuSelection() == "7") // If the user selects 'Cancel Appointment'
        {
            cout << "Please the employee that the meeting you desire to cancel is with: (1-3)" << endl <<
                 "1. Max Smith" << endl <<
                 "2. Eren Karakus" << endl <<
                 "3. Will Marchant" << endl;
            cin >> selectEmployeeCancelAppointment; // Select an employee who's appointment you wish to cancel
            if (selectEmployeeCancelAppointment == "1")
            {
                employeeList[0].CancelAppointment(); // Call CancelAppointment() method for Employee 1
            }
            else if (selectEmployeeCancelAppointment == "2")
            {
                employeeList[1].CancelAppointment(); // Call CancelAppointment() method for Employee 2
            }
            else if (selectEmployeeCancelAppointment == "3")
            {
                employeeList[2].CancelAppointment(); // Call CancelAppointment() method for Employee 3
            }
            else
            {
                cout << "Invalid Entry" << endl; // Validation for selecting an employee
            }

        }
    }

}



