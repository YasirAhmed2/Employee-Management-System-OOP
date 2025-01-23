#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <sqlite3.h>
#include <fstream>
using namespace std;
class Employee
{
private:
    int id;
    string name;
    string position;
    float salary;

public:
    Employee(int id, const string &name, const string &position, float salary);
    int getId() const;
    string getName() const;
    string getPosition() const;
    float getSalary() const;
    void setName(const string &name);
    void setPosition(const string &position);
    void setSalary(float salary);
    static bool createTable(sqlite3 *db);
    bool addEmployee(sqlite3 *db);
    bool modifyEmployee(sqlite3 *db);
    bool deleteEmployee(sqlite3 *db);
    static void displayEmployees(sqlite3 *db);
    static void exportToCSV(sqlite3 *db);
    static void searchEmployee(sqlite3 *db, const std::string &searchQuery);
};
#endif
