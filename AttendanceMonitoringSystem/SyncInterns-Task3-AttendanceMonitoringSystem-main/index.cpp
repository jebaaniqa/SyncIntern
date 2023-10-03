#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_STUDENTS = 100;

struct Student
{
    string name;
    int id;
    bool present;
};


void saveData(Student students[], int size)
{
    ofstream file("index.txt");
    for (int i = 0; i < size; i++)
    {
        file << students[i].name << " " << students[i].id << " " << students[i].present << endl;
    }
    file.close();
}

void loadData(Student students[], int &size)
{
    ifstream file("index.txt");
    if (file)
    {
        size = 0;
        while (!file.eof())
        {
            file >> students[size].name >> students[size].id >> students[size].present;
            size++;
        }
        size--;
    }
    file.close();
}

void printData(Student students[], int size)
{
    cout << setw(10) << left << "Name" << setw(10) << left << "ID" << setw(10) << left << "Present" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << setw(10) << left << students[i].name << setw(10) << left << students[i].id << setw(10) << left << (students[i].present ? "Yes" : "No") << endl;
    }
}

void searchStudent(Student students[], int size)
{
    string searchName;
    int searchID;
    bool found = false;
    cout << "Enter name or ID of student to search: ";
    cin.ignore();
    getline(cin, searchName);
    cin.clear();
    cin >> searchID;
    for (int i = 0; i < size; i++)
    {
        if (students[i].name == searchName && students[i].id == searchID)
        {
            found = true;
            cout << "Attendance record for " << students[i].name << " (" << students[i].id << "): " << (students[i].present ? "Present" : "Absent") << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Student not found." << endl;
    }
}

void editAttendance(Student students[], int size)
{
    string searchName;
    int searchID;
    bool found = false;
    cout << "Enter name or ID of student to edit attendance: ";
    cin.ignore();
    getline(cin, searchName);
    cin.clear();
    cin >> searchID;
    for (int i = 0; i < size; i++)
    {
        if (students[i].name == searchName && students[i].id == searchID)
        {
            found = true;
            cout << "Current attendance record for " << students[i].name << " (" << students[i].id << "): " << (students[i].present ? "Present" : "Absent") << endl;
            cout << "Enter 1 for present, 0 for absent: ";
            cin >> students[i].present;
            cout << "Attendance record updated." << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Student not found." << endl;
    }
}

void attendanceHistory(Student students[], int size)
{
    string searchName;
    int searchID;
    bool found = false;
    cout << "Enter name or ID of student to view attendance history: ";
    cin.ignore();
    getline(cin, searchName);
    cin.clear();
    cin >> searchID;
    for (int i = 0; i < size; i++)
    {
        if (students[i].name == searchName && students[i].id == searchID)
        {
            found = true;
            cout << "Attendance history for " << students[i].name << " (" << students[i].id << "):" << endl;
            cout << setw(10) << left << "Date" << setw(10) << left << "Present" << endl;
            for (int j = 0; j < size; j++)
            {
                if (students[i].id == students[j].id)
                {
                    cout << setw(10) << left << j + 1 << setw(10) << left << (students[j].present ? "Yes" : "No") << endl;
                }
            }
            break;
        }
    }
    if (!found)
    {
        cout << "Student not found." << endl;
    }
}

void exportData(Student students[], int size)
{
    ofstream file("attendance.csv");
    file << "Name,ID,Present" << endl;
    for (int i = 0; i < size; i++)
    {
        file << students[i].name << "," << students[i].id << "," << (students[i].present ? "Yes" : "No") << endl;
    }
    file.close();
    cout << "Attendance data exported to attendance.csv." << endl;
}

void addStudent(Student students[], int &size)
{
    if (size < MAX_STUDENTS)
    {
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, students[size].name);
        cout << "Enter student ID: ";
        cin >> students[size].id;
        cout << "Is the student present (1 for present, 0 for absent): ";
        cin >> students[size].present;
        size++;
        cout << "Student added successfully." << endl;
    }
    else
    {
        cout << "Maximum number of students reached." << endl;
    }
}


int main()
{
    Student students[MAX_STUDENTS];
    int size = 0;
    loadData(students, size);

    int choice = -1;
    while (choice != 0)
    {
        cout << "Attendance Monitoring System" << endl;
        cout << "1. View attendance data" << endl;
        cout << "2. Search for a student" << endl;
        cout << "3. Edit attendance data for a student" << endl;
        cout << "4. View attendance history for a student" << endl;
        cout << "5. Export attendance data" << endl;
        cout << "6. Add Student" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            printData(students, size);
            break;
        case 2:
            searchStudent(students, size);
            break;
        case 3:
            editAttendance(students, size);
            saveData(students, size);
            break;
        case 4:
            attendanceHistory(students, size);
            break;
        case 5:
            exportData(students, size);
            break;
        case 6:
            addStudent(students, size);
            saveData(students, size);
            break;
        case 0:
            saveData(students, size);
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        cout << endl;
    }
    return 0;}