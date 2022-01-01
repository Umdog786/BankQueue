#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "Login.h"

Login::Login() // Default constructor for assigning default values to all private variables
{
    loginAttempts = 3; // Number of login attempts the user has
    menuSelection = "";
    menuPass = false;
    menuSelectionPass = false;
    newUsername = "";
    newPassword = "";
    tempUsername = "";
    tempPassword = "";
}

void Login::LoadCredentials(ifstream &inputCredentialsFile) { // Passes 'Credentials.txt' as a reference
    inputCredentialsFile >> actualUsername >> actualPassword; // Extracts credentials and stores in variables
}

void Login::EnterUsername()
{
    cout << "Please enter your USERNAME: " << endl; // Asks user to enter username
    cin >> attemptUsername; // Stores user's username attempt entry
}

void Login::EnterPassword()
{
    cout << "Please enter your PASSWORD: " << endl; // Asks user to enter password
    cin >> attemptPassword; // Stores user's password attempt entry
}

int Login::GetLoginAttempts()
{
    int* getLoginAttempts = &loginAttempts; // Uses pointer to get current login attempts
    return *getLoginAttempts; // Dereference login attempts and return
}

bool Login::GetMenuPass() {
    return menuPass; // Return current status of menuPass
}

bool Login::SetMenuPass() {
    return menuPass = true; // Set menuPass to true (user selected 'Logout' at menu
}

bool Login::LoginSuccessful()
{
    if (loginAttempts == 0) // Check if the user has no login attempts left
    {
        cout << "You have been locked out!" << endl; // Informs user they have been locked out
        return true; // Returns to main, program then ends (login not successful)
    }
    else if ((attemptUsername != actualUsername) && (attemptPassword != actualPassword)) // Both credentials are incorrect
    {
        cout << "USERNAME and PASSWORD are incorrect!" << endl; // Inform user that both credentials are incorrect
        loginAttempts -= 1; // Decrement login attempts remaining
        cout << "You have " << loginAttempts + 1<< " attempts remaining!" << endl; // Informs user of login attempts remaining
        return false; // Return to main (login not successful)
    }
    else if ((attemptUsername == actualUsername) && (attemptPassword == actualPassword)) // Both credentials are correct
    {
        cout << "Login Successful!" << endl; // Informs user that both credentials are correct
        return true; // Returns to main (login successful)
    }
    else if (attemptUsername != actualUsername) // Only the username is incorrect
    {
        cout << "USERNAME is incorrect!" << endl; // Informs user that only the username is incorrect
        loginAttempts -= 1; // Decrement login attempts remaining
        cout << "You have " << loginAttempts + 1 << " attempts remaining!" << endl; // Informs user of login attempts remaining
        return false; // Return to main (login not successful)
    }
    else if (attemptPassword != actualPassword) // Only the password is incorrect
    {
        cout << "PASSWORD is incorrect!" << endl; // Informs user that only the password is incorrect
        loginAttempts -= 1; // Decrement login attempts remaining
        cout << "You have " << loginAttempts + 1 << " attempts remaining!" << endl; // Informs user of login attempts remaining
        return false; // Return to main (login not successful)
    }
    else
    {
        return false;  // Return to main (login not successful)
    }
}

void Login::SetMenuSelection() {
    menuSelection = ""; // Reset menu selection
    menuSelectionPass = false; // Reset menu validation pass
    while (!menuSelectionPass) { // Repeats until valid menu input
        cout << "Please select one of the following options (1-7) :" << endl << // Displaying main menu options
             "1. View Employee Timetables" << endl <<
             "2. Change Username" << endl <<
             "3. Change Password" << endl <<
             "4. Logout" << endl <<
             "5. View Customer Information" << endl <<
             "6. Advance Time" << endl <<
             "7. Cancel Appointment" << endl;
        cin >> menuSelection; // User enters menu selection

        if (menuSelection == "1") { // Informing user of their choice
            cout << "You have selected View Employee Timetables" << endl;
            menuSelectionPass = true;
        } else if (menuSelection == "2") {
            cout << "You have selected Change Username" << endl;
            menuSelectionPass = true;
        } else if (menuSelection == "3") {
            cout << "You have selected Change Password" << endl;
            menuSelectionPass = true;
        } else if (menuSelection == "4") {
            cout << "You have selected Logout. Goodbye!" << endl;
            exit(1); // Exits program if 'Logout' selected
            menuSelectionPass = true;
        } else if (menuSelection == "5") {
            cout << "You have selected View Customer Information" << endl;
            menuSelectionPass = true;
        } else if (menuSelection == "6") {
            cout << "You have selected Advance Time" << endl;
            menuSelectionPass = true;
        } else if (menuSelection == "7") {
            cout << "You have selected Cancel Appointment" << endl;
            menuSelectionPass = true;
        } else { // Invalid input entered
            cout << "Invalid Selection! Please try again" << endl; // Informs user of invalid input
        }
        cout << string(20, '-') << endl;
        }
}

string Login::GetMenuSelection() {
    return menuSelection; // Returns last menu selection
}

void Login::ChangePassword() // User chooses to change password
{
    while (actualPassword != newPassword) // Can't change password to current password
    {
        cout << "Please enter the password you'd like to change to: " << endl; // Prompt to enter new password
        cin >> newPassword; // Stores new password in a temporary variable
        cout << "Please confirm your new password: " << endl; // Re-enter new password to confirm
        cin >> tempPassword; // Stores re-entry in a temporary variable
        if (newPassword == tempPassword) // Check the two new passwords match
        {
            cout << "Password successfully changed!" << endl; // Inform user that the password was successfully changed
            actualPassword = newPassword; // Set the new password
            ofstream outputCredentialsFile; // New output file variable
            outputCredentialsFile.open("Credentials.txt", ofstream::out | ofstream::trunc); // Points to 'Credentials.txt' with truncate flag to clear file
            outputCredentialsFile << actualUsername << endl << actualPassword; // Write new password to file
        }
        else
        {
            cout << "Password confirmation failed, please try again." << endl; // If they don't match, try again
        }
    }
}

void Login::ChangeUsername() // User chooses to change username
{
    while (actualUsername != newUsername) // Can't change username to current username
    {
        cout << "Please enter the username you'd like to change to: " << endl; // Prompt to enter new username
        cin >> newUsername; // Stores new username in a temporary variable
        cout << "Please confirm your new username: " << endl; // Re-enter new username to confirm
        cin >> tempUsername; // Stores re-entry in a temporary variable
        if (newUsername == tempUsername) // Check the two new usernames match
        {
            cout << "Username successfully changed!" << endl; // Inform user that the username was successfully changed
            actualUsername = newUsername; // Set the new username
            ofstream outputCredentialsFile; // New output file variable
            outputCredentialsFile.open("Credentials.txt", ofstream::out | ofstream::trunc); // Points to 'Credentials.txt' with truncate flag to clear file
            outputCredentialsFile << actualUsername << endl << actualPassword; // Write new username to file
        }
        else
        {
            cout << "Username confirmation failed, please try again." << endl; // If they don't match, try again
        }
    }
}