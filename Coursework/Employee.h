#pragma once
#include <iostream>
#include <string>
using namespace std;

class Employee
{
public:
    Employee();
    void LoadEmployee(ifstream& inputEmployeeListFile); // Loads employee info from 'EmployeeList.txt'
                                                        // extracts key data and stores in variables
    string GetEmployeeName(); // Returns specified employee's full name
    string GetEmployeeJob(); // Returns specified employee's Job
    void PopulateScheduleArray(); // Sets default values for scheduleArray aka employee timetable
    void GetScheduleArray(); // Displays full employee timetable
    void GetTimeElement(int currentTime); // Returns a specified time
    void MakeAppointment(const string& customerUsername,
                         const string& customerFirstName,
                         const string& customerLastName,
                         int randomTime,
                         ofstream &outputAppointmentLogFile);
                         // Makes a new appointment based in inputted customer information and a time
    void CancelAppointment(); // Cancels a specified, existing appointment

private:
    string employeeName, employeeJob; // Stores employee name and employee job respectively
    string scheduleArray[24]; // Three 20-min timeslots per hour, holds up-to-date timetable
    string timeArray[24]; // Holds 'blank' timetable of default values
    int scheduleArrayPointer; // Pointer for iterating through the timetable
    string cancelTime; // Holds the time for the appointment that is being canelled
};