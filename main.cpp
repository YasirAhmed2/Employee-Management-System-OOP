#include <iostream>
#include <sqlite3.h>
#include "Employee.h"
using namespace std;
// Simple user authentication function
bool authenticateUser()
{
    string username, password;
   cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    // Check for correct credentials (this is for demonstration; do not use in production)
    return (username == "admin" && password == "admin123");
}
int main()
{
    // Authenticate the user
    if (!authenticateUser())
    {
        cout << "Authentication failed!" <<endl;
        return 1;
    }
    sqlite3 *db;
    if (sqlite3_open("employee.db", &db))
    {
        cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    // Create the employee table if it doesn't exist
    Employee::createTable(db);
    int choice;
    do
    {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Modify Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Display All Employees\n";
        cout << "5. Search Employee\n";
        cout << "6. Export Data to CSV\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string name, position;
            float salary;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter position: ";
            cin >> position;
            cout << "Enter salary: ";
        cin >> salary;
            Employee emp(0, name, position, salary);
            if (emp.addEmployee(db))
            {
                cout << "Employee added successfully!" <<endl;
            }
            break;
        }
        case 2:
        {
            int id;
          string name, position;
            float salary;
            cout << "Enter employee ID to modify: ";
            cin >> id;
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter new position: ";
            cin >> position;
            cout << "Enter new salary: ";
            cin >> salary;
            Employee emp(id, name, position, salary);
            if (emp.modifyEmployee(db))
            {
                cout << "Employee modified successfully!" << std::endl;
            }
            break;
        }
        case 3:
        {
            int id;
            cout << "Enter employee ID to delete: ";
            cin >> id;
            Employee emp(id, "", "", 0);
            if (emp.deleteEmployee(db))
            {
                cout << "Employee deleted successfully!" << endl;
            }
            break;
        }
        case 4:
            Employee::displayEmployees(db);
            break;
        case 5:
        {
           string searchQuery;
            cout << "Enter name or position to search: ";
            cin >> searchQuery;
            Employee::searchEmployee(db, searchQuery);
            break;
        }
        case 6:
            Employee::exportToCSV(db);
            break;
        case 7:
            cout << "Exiting the system..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again!" << endl;
        }
    } while (choice != 7);
    sqlite3_close(db);
    return 0;
}