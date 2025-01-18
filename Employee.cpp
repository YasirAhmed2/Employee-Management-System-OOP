#include "Employee.h"
using namespace std;
Employee::Employee(int id, const std::string &name, const std::string &position, float salary)
    : id(id), name(name), position(position), salary(salary) {}
int Employee::getId() const
{
    return id;
}
string Employee::getName() const
{
    return name;
}
string Employee::getPosition() const
{
    return position;
}
float Employee::getSalary() const
{
    return salary;
}
void Employee::setName(const std::string &name)
{
    this->name = name;
}
void Employee::setPosition(const std::string &position)
{
    this->position = position;
}
void Employee::setSalary(float salary)
{
    this->salary = salary;
}
bool Employee::createTable(sqlite3 *db)
{
    const char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS Employee ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "name TEXT NOT NULL, "
                                 "position TEXT NOT NULL, "
                                 "salary REAL NOT NULL);";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
bool Employee::addEmployee(sqlite3 *db)
{
    std::string sql = "INSERT INTO Employee (name, position, salary) VALUES ('" +
                      name + "', '" + position + "', " + std::to_string(salary) + ");";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
      cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
bool Employee::modifyEmployee(sqlite3 *db)
{
    std::string sql = "UPDATE Employee SET name = '" + name + "', position = '" + position +
                      "', salary = " + std::to_string(salary) + " WHERE id = " + std::to_string(id) + ";";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
bool Employee::deleteEmployee(sqlite3 *db)
{
    std::string sql = "DELETE FROM Employee WHERE id = " + std::to_string(id) + ";";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
void Employee::displayEmployees(sqlite3 *db)
{
    const char *sql = "SELECT * FROM Employee;";
    char *errMsg = 0;
    auto callback = [](void *, int argc, char **argv, char **azColName) -> int
    {
        for (int i = 0; i < argc; i++)
        {
         cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\t";
        }
       cout << endl;
        return 0;
    };
    int rc = sqlite3_exec(db, sql, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
      cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}
void Employee::exportToCSV(sqlite3 *db)
{
    ofstream file("employees.csv");
    file << "id,name,position,salary\n";
    const char *sql = "SELECT * FROM Employee;";
    char *errMsg = 0;
    auto callback = [&file](void *, int argc, char **argv, char **azColName) -> int
    {
        for (int i = 0; i < argc; i++)
        {
            file << (argv[i] ? argv[i] : "NULL");
            if (i < argc - 1)
            {
                file << ",";
            }
        }
        file << "\n";
        return 0;
    };
    int rc = sqlite3_exec(db, sql, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    file.close();
    cout << "Data exported to employees.csv successfully!" << std::endl;
}
void Employee::searchEmployee(sqlite3 *db, const std::string &searchQuery)
{
    string sql = "SELECT * FROM Employee WHERE name LIKE '%" + searchQuery +
                      "%' OR position LIKE '%" + searchQuery + "%';";
    char *errMsg = 0;
    auto callback = [](void *, int argc, char **argv, char **azColName) -> int
    {
        for (int i = 0; i < argc; i++)
        {
            cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\t";
        }
        cout << endl;
        return 0;
    };
    int rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}