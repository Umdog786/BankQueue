#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#include "Employee.h"

Employee::Employee() { // Default constructor for assigning default values to all private variables
    employeeName = "";
    employeeJob = "";
    scheduleArrayPointer = 0;
    cancelTime = "";
}

void Employee::LoadEmployee(ifstream& inputEmployeeListFile) {
    inputEmployeeListFile >> employeeName >> employeeJob; // Extracts Employee Name & Job
    employeeName =  employeeName.substr(0, employeeName.find('-')) + " " + employeeName.substr(employeeName.find('-') + 1,employeeName.length() - 1 );
    employeeJob =  employeeJob.substr(0, employeeJob.find('-')) + " " + employeeJob.substr(employeeJob.find('-') + 1,employeeJob.length() - 1 );
    // Formatting of employeeName and employeeJob

}

string Employee::GetEmployeeName() {
    return employeeName; // Returns employeeName
}

string Employee::GetEmployeeJob() {
    return employeeJob; // Returns employeeJob
}

void Employee::PopulateScheduleArray() {
    for (int hour = 9; hour < 17; ++hour) { // Starting from 09:00, Ending at 17:00
        for (int minute = 0; minute < 60; minute += 20) { // 60 minutes in an hour, three 20-minute intervals
            if ((minute == 0) and (hour == 9)) {
                scheduleArray[scheduleArrayPointer] = "0" + to_string(hour) + ":" + to_string(minute) + "0"; // Populate scheduleArray with formatted time
                timeArray[scheduleArrayPointer] = "0" + to_string(hour) + ":" + to_string(minute) + "0"; // Populate timeArray with formatted time
            }
            else if (hour == 9){
                scheduleArray[scheduleArrayPointer] = "0" + to_string(hour) + ":" + to_string(minute); // Populate scheduleArray with formatted time
                timeArray[scheduleArrayPointer] = "0" + to_string(hour) + ":" + to_string(minute); // Populate timeArray with formatted time
            }
            else if (minute == 0){
                scheduleArray[scheduleArrayPointer] = to_string(hour) + ":" + to_string(minute) + "0"; // Populate scheduleArray with formatted time
                timeArray[scheduleArrayPointer] = to_string(hour) + ":" + to_string(minute) + "0"; // Populate timeArray with formatted time
            }
            else {
                scheduleArray[scheduleArrayPointer] = to_string(hour) + ":" + to_string(minute); // Populate scheduleArray with formatted time
                timeArray[scheduleArrayPointer] = to_string(hour) + ":" + to_string(minute); // Populate timeArray with formatted time
            }
            ++scheduleArrayPointer; // Increment array pointer

        }
    }
}

void Employee::GetScheduleArray() { // Displays full timetable for an employee
    for (int i = 0; i < 24 ; ++i) {
        cout << scheduleArray[i] << endl;
    }
    cout << endl;
}

void Employee::GetTimeElement(int currentTime) { // Returns a specific time
    cout << "Current Time: " << timeArray[currentTime] << endl;
}

void Employee::MakeAppointment(const string& customerUsername, // Takes customer's details as parameters
                               const string& customerFirstName,
                               const string& customerLastName,
                               int randomTime, ofstream &outputAppointmentLogFile) {

    cout << "New Appointment Requested with: " << employeeName << endl << // Display requested appointment details
            "Customer Name: " << customerFirstName << " " << customerLastName << endl <<
            "Customer Username: " << customerUsername << endl <<
            "Time: " << timeArray[randomTime] << endl;


    if (scheduleArray[randomTime] != timeArray[randomTime]) { // Check if there is already a meeting at the desired time
        cout << "Unfortunately the meeting you requested is unavailable at the selected time." << endl;
        for (int i = randomTime + 1; i < 24; ++i) { // Iterate over the next timeslots
            if (scheduleArray[i] == timeArray[i]) { // Looking for the next available timeslot
                cout << "A meeting at " << timeArray[i] << " has been created." << endl; // Create appointment at next available timeslot
                scheduleArray[i] = timeArray[i] + " Appointment with: " + customerFirstName + " " + customerLastName;

                outputAppointmentLogFile << timeArray[randomTime] << " " << // Outputs appointment to 'AppointmentLog.txt'
                                            customerUsername << " " <<
                                            customerFirstName << " " <<
                                            customerLastName << endl;
                break;
            }
        }
    }
    else // Desired timeslot is free
    {
        scheduleArray[randomTime] = timeArray[randomTime] + " Appointment with: " + customerFirstName + " " + customerLastName; // Create appointment
        outputAppointmentLogFile << timeArray[randomTime] << " " << // Outputs appointment to 'AppointmentLog.txt'
                                 customerUsername << " " <<
                                 customerFirstName << " " <<
                                 customerLastName << endl;    }
}

void Employee::CancelAppointment() { // User selects 'Cancel Appointment' from main menu
    for (int i = 0; i < 24; ++i) { // Iterate over scheduleArray
        if (scheduleArray[i] != timeArray[i]) // If not default value, appointment exists
        {
            cout << scheduleArray[i] << endl; // Display existing appointment details
        }
    }
    cout << "Please select the Time for the meeting you would like to cancel: (HH:MM) " << endl;
    cin >> cancelTime; // User inputs time of the appointment they want to cancel

    while (find(begin(timeArray), end(timeArray), cancelTime) == end(timeArray)) // Check if time exists within scheduleArray
    {
        cout << "Invalid Entry" << endl; // If it doesn't, inform user
        cout << "Please select the Time for the meeting you would like to cancel: (HH:MM) " << endl; // Re-enter time
        cin >> cancelTime;
    }

    for (int i = 0; i < 24; ++i) {
        if (cancelTime == scheduleArray[i].substr(0,5)) // Check if time exists within scheduleArray
        {
            if (scheduleArray[i] != timeArray[i]) // Check that appointment exists at time user wants to cancel
            {
                scheduleArray[i] = timeArray[i]; // If it does, reset that timeslot to default value
                cout << "Appointment at " << cancelTime << " has been cancelled." << endl; // Inform user that appointment has been cancelled
            }
            else
            {
                cout << "No Appointment was found at the selected time." << endl; // Inform user if no appointment exists at specified timeslot
            }

        }
    }
}