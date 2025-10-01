#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

using namespace std;

class User {
private:
    string name;
    string email;
    string password;
    string phone;
    string roll;

public:
    User() {}
    User(string n, string e, string p, string ph, string r)
        : name(n), email(e), password(p), phone(ph), roll(r) {}

    void setName(const string& n) { name = n; }
    void setEmail(const string& e) { email = e; }
    void setPassword(const string& p) { password = p; }
    void setPhone(const string& ph) { phone = ph; }
    void setRoll(const string& r) { roll = r; }

    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    string getPhone() const { return phone; }
    string getRoll() const { return roll; }

    void display() const {
        cout << "Name: " << name << "\n"
             << "Email: " << email << "\n"
             << "Phone: " << phone << "\n"
             << "Roll: " << roll << "\n";
    }
};

extern User s, t;

void scrolltext(const string &str);
void takeinput(string &input);
void takepassword(string &pass);
int registration();
int login();
void showMainMenu();
int options(const string& fid, const string& password);
int optiont(const string& femail, const string& password);
int stdresult(const string& fid);
int gpcal();
int course_reg(const string& fid);
int view_registered_courses(const string& fid);  // ADD THIS LINE
int editstdinfo(const string& fid, const string& password);
int edittcrinfo(const string& femail, const string& password);
int dlt(const string& fid, const string& password);

#endif
