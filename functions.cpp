#include "header.h"

void scrolltext(const string &str) {
    for (char ch : str) {
        cout << ch << flush;
        #ifdef _WIN32
        Sleep(10);
        #else
        this_thread::sleep_for(chrono::milliseconds(10));
        #endif
    }
}
void pressAnyKey() {
    cout << "\n\tPress any key to continue...";
    #ifdef _WIN32
    _getch();  // Windows - waits for any key
    #else
    getchar(); // Linux/Mac - waits for Enter key
    #endif
}


void takeinput(string &input) {
    getline(cin, input);
}

void takepassword(string &pass) {
    char ch;
    pass.clear();
    while (true) {
        #ifdef _WIN32
        ch = _getch();
        #else
        ch = getchar();
        #endif
        if (ch == 13 || ch == '\n') {
            cout << "\n";
            break;
        } else if (ch == 8) {
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else if (ch == 32 || ch == 9 || ch == 27) {
            continue;
        } else {
            pass.push_back(ch);
            cout << "*";
        }
    }
}

int registration() {
    system("cls");
    system("color 70");

    int choice;
    cout << "\t\t\t--- Registration ---\n";
    cout << "\t\t1. Register as a student\n\t\t2. Register as a teacher\n";
    scrolltext("\n\t\tEnter your choice: ");
    cin >> choice;
    cin.ignore();

    fstream file;
    string name, email, phone, roll, password, pass2;

    switch (choice) {
        case 1: {
            file.open("stdinfo.txt", ios::app | ios::binary);
            system("cls");
            cout << "\t\t\t--- Student Registration ---\n";

            cout << "\t\tEnter your name: ";
            takeinput(name);
            s.setName(name);

            cout << "\t\tEnter your email: ";
            takeinput(email);
            s.setEmail(email);

            cout << "\t\tEnter your phone: ";
            takeinput(phone);
            s.setPhone(phone);

            cout << "\t\tEnter your roll: ";
            takeinput(roll);
            s.setRoll(roll);

            cout << "\t\tEnter your password: ";
            takepassword(password);
            s.setPassword(password);

            cout << "\t\tConfirm your password: ";
            takepassword(pass2);

            if (password != pass2) {
                cout << "\n\t\tPasswords do not match.\n";
                #ifdef _WIN32
                Beep(823, 500);
                Sleep(1000);
                #endif
                file.close();
                return registration();
            }

            file.write(reinterpret_cast<char*>(&s), sizeof(User));
            file.close();

            scrolltext("\n\n\t\tRegistering");
            for (int i = 0; i < 3; i++) {
                cout << ".";
                #ifdef _WIN32
                Sleep(500);
                #else
                this_thread::sleep_for(chrono::milliseconds(500));
                #endif
            }
            cout << "\n\t\tRegistration successful!\n";
            cout << "\t\tYour ID is your roll number: " << roll << "\n";
            pressAnyKey();
            return login();
        }

        case 2: {
            file.open("teacherinfo.txt", ios::app | ios::binary);
            system("cls");
            cout << "\t\t\t--- Teacher Registration ---\n";

            cout << "\t\tEnter your name: ";
            takeinput(name);
            t.setName(name);

            cout << "\t\tEnter your email: ";
            takeinput(email);
            t.setEmail(email);

            cout << "\t\tEnter your phone: ";
            takeinput(phone);
            t.setPhone(phone);

            cout << "\t\tEnter your password: ";
            takepassword(password);
            t.setPassword(password);

            cout << "\t\tConfirm your password: ";
            takepassword(pass2);

            if (password != pass2) {
                cout << "\n\t\tPasswords do not match.\n";
                #ifdef _WIN32
                Beep(523, 500);
                Sleep(1000);
                #endif
                file.close();
                return registration();
            }

            file.write(reinterpret_cast<char*>(&t), sizeof(User));
            file.close();

            scrolltext("\n\n\t\tRegistering");
            for (int i = 0; i < 3; i++) {
                cout << ".";
                #ifdef _WIN32
                Sleep(500);
                #else
                this_thread::sleep_for(chrono::milliseconds(500));
                #endif
            }
            cout << "\n\t\tRegistration successful!\n";
            pressAnyKey();
            return login();
        }

        default:
            cout << "\n\t\t\t--- Invalid choice ---\n";
            return registration();
    }
}

int login() {
    system("cls");
    system("color 70");

    int choice;
    cout << "\t\t\t--- Login ---\n";
    cout << "\t\t1. Login as student\n\t\t2. Login as teacher\n\t\t3. Go back\n";
    scrolltext("\n\t\tEnter your choice: ");
    cin >> choice;
    cin.ignore();

    string id, email, password;
    fstream file;
    User temp;

    switch (choice) {
        case 1: {
            system("cls");
            cout << "\t\t\t--- Student Login ---\n\n";
            cout << "\t\tEnter your ID: ";
            takeinput(id);
            cout << "\t\tEnter your password: ";
            takepassword(password);

            file.open("stdinfo.txt", ios::in | ios::binary);
            bool studentFound = false;
            while (file.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
                if (id == temp.getRoll()) {
                    studentFound = true;
                    if (password == temp.getPassword()) {
                        file.close();
                        scrolltext("\n\t\tLogging in");
                        for (int i = 0; i < 3; i++) {
                            cout << ".";
                            #ifdef _WIN32
                            Sleep(500);
                            #else
                            this_thread::sleep_for(chrono::milliseconds(500));
                            #endif
                        }
                        cout << "\n\t\tLogin successful!\n";
                                    pressAnyKey();

                        return options(id, password);
                    } else {
                        file.close();
                        scrolltext("\n\t\tWrong password.\n");
                        #ifdef _WIN32
                        Beep(823, 500);
                        Sleep(2000);
                        #endif
                        return login();
                    }
                }
            }
            file.close();
            if (!studentFound) {
                cout << "\n\t\tUser not found.\n";
                #ifdef _WIN32
                Beep(823, 500);
                #endif
            }
                        pressAnyKey();

            return login();
        }

        case 2: {
            system("cls");
            cout << "\t\t\t--- Teacher Login ---\n\n";
            cout << "\t\tEnter your email: ";
            takeinput(email);
            cout << "\t\tEnter your password: ";
            takepassword(password);

            file.open("teacherinfo.txt", ios::in | ios::binary);
            bool teacherFound = false;
            while (file.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
                if (email == temp.getEmail()) {
                    teacherFound = true;
                    if (password == temp.getPassword()) {
                        file.close();
                        scrolltext("\n\t\tLogging in");
                        for (int i = 0; i < 3; i++) {
                            cout << ".";
                            #ifdef _WIN32
                            Sleep(500);
                            #else
                            this_thread::sleep_for(chrono::milliseconds(500));
                            #endif
                        }
                        cout << "\n\t\tLogin successful!\n";
                                    pressAnyKey();

                        return optiont(email, password);
                    } else {
                        file.close();
                        scrolltext("\n\t\tWrong password.\n");
                        #ifdef _WIN32
                        Sleep(2000);
                        #endif
                        return login();
                    }
                }
            }
            file.close();
            if (!teacherFound) {
                scrolltext("\t\tUser not found.\n");
            }
            #ifdef _WIN32
            Sleep(1000);
            #endif
            return login();
        }

        case 3:
            showMainMenu();
            return 0;

        default:
            scrolltext("\t\t\t--- Invalid choice ---\n");
            #ifdef _WIN32
            Sleep(1000);
            #endif
            return login();
    }
}

