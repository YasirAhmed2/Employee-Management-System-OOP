#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <sqlite3.h>
#include <fstream>
class Employee
{
private:
    int id;
    std::string name;
    std::string position;
    float salary;

public:
    // Constructor
    Employee(int id, const std::string &name, const std::string &position, float salary);
    // Getters and Setters
    int getId() const;
    std::string getName() const;
    std::string getPosition() const;
    float getSalary() const;
    void setName(const std::string &name);
    void setPosition(const std::string &position);
    void setSalary(float salary);
    // Database operations
    static bool createTable(sqlite3 *db);
    bool addEmployee(sqlite3 *db);
    bool modifyEmployee(sqlite3 *db);
    bool deleteEmployee(sqlite3 *db);
    static void displayEmployees(sqlite3 *db);
    static void exportToCSV(sqlite3 *db);
    static void searchEmployee(sqlite3 *db, const std::string &searchQuery);
};
#endif // EMPLOYEE_H
