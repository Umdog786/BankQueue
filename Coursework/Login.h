#pragma once
#include <iostream>
#include <string>
using namespace std;

class Login
{
public:
    Login();
    void LoadCredentials(ifstream& inputCredentialsFile); // Loads credentials via reference to 'Credentials.txt'
    void EnterUsername(); // Allows the user to enter their username
    void EnterPassword(); // Allows the user to enter their password
    int GetLoginAttempts(); // Returns the number of login attempts left before locked out
    bool LoginSuccessful(); // Events that are triggered when valid credentials are entered
    void ChangePassword(); // Allows the user to change their password when they have successfully logged in
    void ChangeUsername(); // Allows the user to change their username when they have successfully logged in
    bool GetMenuPass(); // Returns menuPass
    bool SetMenuPass(); // Sets menuPass to true (user selected 'Logout' at menu)
    void SetMenuSelection(); // Displays main menu and handles menu selection
    string GetMenuSelection(); // Returns last menu selection made
private:
    string actualUsername, actualPassword; // Actual credentials for the system
    string attemptUsername, attemptPassword; // Inputted credentials by the user
    int loginAttempts; // Number of login attempts the user has before they're locked out
    string menuSelection; // Stores the selection from the menu once user has logged-in
    bool menuSelectionPass; // Boolean value for validated whether an acceptable input has been during menu selection
    bool menuPass; // Boolean value for controlling menu while loop
    string newPassword, tempPassword, newUsername, tempUsername; // Variables for correct and user-attempted login credentials
};