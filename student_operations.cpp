#include "header.h"
#include <algorithm>
#include <cctype>

using namespace std;

int options(const string& fid, const string& password) {
    system("cls");
    system("color 70");

    int opt;
    cout << "\t\t\t---Student Dashboard---\n\n";
    cout << "\t\t1. View your information\n";
    cout << "\t\t2. Edit your information\n";
    cout << "\t\t3. Delete your account\n";
    cout << "\t\t4. Course Registration\n";
    cout << "\t\t5. View your result\n";
    cout << "\t\t6. GPA Calculator\n";
    cout << "\t\t7. Logout\n";
    cout << "\n\t\tEnter your choice: ";
    cin >> opt;
    cin.ignore();

    switch (opt) {
        case 1: {
            cout << "\t\t\t---Your information---\n";
            ifstream fin("stdinfo.txt", ios::binary);
            User u;
            bool found = false;
            while (fin.read(reinterpret_cast<char*>(&u), sizeof(User))) {
                if (fid == u.getRoll()) {
                    found = true;
                    fin.close();
                    u.display();
                                pressAnyKey();

                    return options(fid, password);
                }
            }
            fin.close();
            if (!found) {
                cout << "\t\tUser not found!\n";
            }
                        pressAnyKey();

            return options(fid, password);
        }

        case 2:
            editstdinfo(fid, password);
            return options(fid, password);

        case 3:
            dlt(fid, password);
            showMainMenu();
            return 0;

        case 4: {
            int subchoice;
            system("cls");
            cout << "\t\tCourse Registration System\n\n";
            cout << "\t1. Register for New Courses\n";
            cout << "\t2. View My Registered Courses\n";
            cout << "\t3. Back to Main Menu\n";
            cout << "\n\tEnter your choice: ";
            cin >> subchoice;
            cin.ignore();

            switch (subchoice) {
                case 1:
                    course_reg(fid);
                    break;
                case 2:
                    view_registered_courses(fid);
                    break;
                case 3:
                    break;
                default:
                    cout << "\tInvalid choice!\n";
                                pressAnyKey();

            }
            return options(fid, password);
        }

        case 5:
            stdresult(fid);
            return options(fid, password);

        case 6:
            gpcal();
            return options(fid, password);

        case 7:
            cout << "\n\t\tLogging out";
            for (int i = 0; i < 3; i++) {
                cout << ".";
                cout.flush();
                #ifdef _WIN32
                Sleep(500);
                #else
                this_thread::sleep_for(chrono::milliseconds(500));
                #endif
            }
            login();
            break;

        default:
            cout << "\t\t---Invalid choice---\n";
            #ifdef _WIN32
            Sleep(1000);
            #endif
            return options(fid, password);
    }
    return 0;
}

int stdresult(const string& fid) {
    system("cls");
    cout << "\t\tYour Result for 1-1\n";

    ifstream fp("gpa.txt");
    if (!fp) {
        cerr << "Error opening file" << endl;
                    pressAnyKey();

        return 1;
    }

    string id;
    vector<float> gp(9);
    float gpa;
    bool found = false;

    while (fp >> id >> gp[0] >> gp[1] >> gp[2] >> gp[3]
              >> gp[4] >> gp[5] >> gp[6] >> gp[7] >> gp[8] >> gpa) {
        if (fid == id) {
            found = true;
            cout << fixed << setprecision(2);
            cout << "\tCSE  1203 : " << gp[0] << "\n";
            cout << "\tCSE  1204 : " << gp[1] << "\n";
            cout << "\tCSE  1205 : " << gp[2] << "\n";
            cout << "\tCSE  1206 : " << gp[3] << "\n";
            cout << "\tEEE  1207 : " << gp[4] << "\n";
            cout << "\tEEE  1208 : " << gp[5] << "\n";
            cout << "\tMATH 1207 : " << gp[6] << "\n";
            cout << "\tCHEM 1207 : " << gp[7] << "\n";
            cout << "\tCHEM 1208 : " << gp[8] << "\n\n";
            cout << "\tGPA       : " << gpa << "\n";
            break;
        }
    }

    fp.close();

    if (!found) {
        cout << "\tNo result found for ID: " << fid << "\n";
    }
            pressAnyKey();

    return 0;
}

int gpcal() {
    system("cls");
    cout << "\t\tGPA Calculator\n\n";

    string id;
    cout << "Enter the ID of student: ";
    cin >> id;

    vector<float> credits = {3, 1.5, 3, 1.5, 3, 1.5, 3, 3, 0.75};
    vector<string> courseCodes = {
        "CSE  1203", "CSE  1204", "CSE  1205", "CSE  1206",
        "EEE  1207", "EEE  1208", "MATH 1207",
        "CHEM 1207", "CHEM 1208"
    };

    vector<float> gp(9);
    float sum = 0.0;

    cout << fixed << setprecision(2);

    for (int i = 0; i < 9; i++) {
        cout << "\t" << courseCodes[i] << " : ";
        cin >> gp[i];
        sum += credits[i] * gp[i];
    }

    float totalCredits = 0;
    for (float c : credits) totalCredits += c;

    float gpa = sum / totalCredits;

    cout << "\n\tGPA is: " << gpa << "\n";

    ofstream fp("gpa.txt", ios::app);
    if (!fp) {
        cerr << "Error opening file" << endl;
                    pressAnyKey();

        return 1;
    }

    fp << id;
    for (float g : gp) fp << " " << g;
    fp << " " << gpa << "\n";

    fp.close();
                pressAnyKey();

    return 0;
}

// REMOVE THE DUPLICATE course_reg FUNCTION - KEEP ONLY THIS ONE:
int course_reg(const string& fid) {
    system("cls");
    cout << "\t\tCourse Registration System\n\n";
    cout << "\t\tStudent ID: " << fid << "\n\n";

    // Available courses for registration
    vector<string> courses = {
        "CSE 1201 - Programming Language I",
        "CSE 1202 - Discrete Mathematics",
        "CSE 1203 - Structured Programming",
        "CSE 1204 - Structured Programming Lab",
        "EEE 1207 - Electrical Circuits",
        "EEE 1208 - Electrical Circuits Lab",
        "MATH 1207 - Differential Calculus",
        "CHEM 1207 - Engineering Chemistry",
        "CHEM 1208 - Engineering Chemistry Lab",
        "HUM 1207 - English Language"
    };

    vector<string> registeredCourses;
    vector<bool> selected(courses.size(), false);

    int choice;
    bool registering = true;

    while (registering) {
        system("cls");
        cout << "\t\tCourse Registration - " << fid << "\n\n";
        cout << "\tAvailable Courses:\n";
        cout << "\t" << string(50, '-') << "\n";

        for (int i = 0; i < (int)courses.size(); i++) {
            cout << "\t" << (i + 1) << ". " << courses[i];
            if (selected[i]) {
                cout << " [SELECTED]";
            }
            cout << "\n";
        }

        cout << "\n\tSelected Courses: " << registeredCourses.size() << " courses\n";
        for (int i = 0; i < (int)registeredCourses.size(); i++) {
            cout << "\t  " << (i + 1) << ". " << registeredCourses[i] << "\n";
        }

        cout << "\n\tOptions:\n";
        cout << "\t" << ((int)courses.size() + 1) << ". Register Selected Courses\n";
        cout << "\t" << ((int)courses.size() + 2) << ". Clear Selection\n";
        cout << "\t" << ((int)courses.size() + 3) << ". Exit Registration\n";
        cout << "\n\tEnter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= (int)courses.size()) {
            int courseIndex = choice - 1;
            if (!selected[courseIndex]) {
                selected[courseIndex] = true;
                registeredCourses.push_back(courses[courseIndex]);
                cout << "\n\t✓ " << courses[courseIndex] << " added to selection.\n";
            } else {
                // Remove from selection
                selected[courseIndex] = false;
                // Remove from registered courses list
                for (auto it = registeredCourses.begin(); it != registeredCourses.end(); ++it) {
                    if (*it == courses[courseIndex]) {
                        registeredCourses.erase(it);
                        break;
                    }
                }
                cout << "\n\t✗ " << courses[courseIndex] << " removed from selection.\n";
            }
                        pressAnyKey();

        }
        else if (choice == (int)courses.size() + 1) {
            // Register selected courses
            if (registeredCourses.empty()) {
                cout << "\n\tNo courses selected! Please select courses first.\n";
            } else {
                // Save to file
                ofstream file("course_registration.txt", ios::app);
                if (file) {
                    file << "Student ID: " << fid << "\n";
                    file << "Registered Courses:\n";
                    for (const auto& course : registeredCourses) {
                        file << "  - " << course << "\n";
                    }
                    file << "Registration Date: " << __DATE__ << " " << __TIME__ << "\n";
                    file << string(30, '-') << "\n";
                    file.close();

                    cout << "\n\t🎉 Registration Successful!\n";
                    cout << "\tYou have registered for " << registeredCourses.size() << " courses:\n";
                    for (const auto& course : registeredCourses) {
                        cout << "\t  ✓ " << course << "\n";
                    }
                    cout << "\n\tRegistration details saved to file.\n";
                } else {
                    cout << "\n\tError saving registration details.\n";
                }
                registering = false;
            }
                        pressAnyKey();

        }
        else if (choice == (int)courses.size() + 2) {
            // Clear selection
            registeredCourses.clear();
            fill(selected.begin(), selected.end(), false);
            cout << "\n\tAll course selections cleared.\n";
                        pressAnyKey();

        }
        else if (choice == (int)courses.size() + 3) {
            // Exit
            if (!registeredCourses.empty()) {
                cout << "\n\t⚠  You have unsaved selections. Are you sure you want to exit? (y/n): ";
                char confirm;
                cin >> confirm;
                if (tolower(confirm) == 'y') {
                    registering = false;
                    cout << "\n\tRegistration cancelled.\n";
                } else {
                    continue;
                }
            } else {
                registering = false;
                cout << "\n\tRegistration cancelled.\n";
            }
            system("pause");
        }
        else {
            cout << "\n\tInvalid choice! Please try again.\n";
                        pressAnyKey();

        }
    }

    return 0;
}

int view_registered_courses(const string& fid) {
    system("cls");
    cout << "\t\tYour Registered Courses\n\n";
    cout << "\tStudent ID: " << fid << "\n\n";

    ifstream file("course_registration.txt");
    if (!file) {
        cout << "\tNo course registration found.\n";
        cout << "\tPlease register for courses first.\n";
                    pressAnyKey();

        return 0;
    }

    string line;
    bool found = false;
    bool printing = false;

    cout << "\t" << string(50, '-') << "\n";
    while (getline(file, line)) {
        if (line.find("Student ID: " + fid) != string::npos) {
            found = true;
            printing = true;
            cout << "\t" << line << "\n";
        } else if (printing && line.find("---") != string::npos) {
            cout << "\t" << line << "\n\n";
            printing = false;
        } else if (printing) {
            cout << "\t" << line << "\n";
        }
    }
    file.close();

    if (!found) {
        cout << "\tNo course registration found for your ID.\n";
        cout << "\tPlease register for courses first.\n";
    }
            pressAnyKey();

    return 0;
}

// Stub implementations for other functions
int editstdinfo(const string& fid, const string& password) {
    system("cls");
    cout << "\t\tEdit Student Information\n\n";
    cout << "\t\tFeature coming soon for ID: " << fid << "\n";
                pressAnyKey();

    return 0;
}

int dlt(const string& fid, const string& password) {
    system("cls");
    cout << "\t\tDelete Account\n\n";
    cout << "\t\tFeature coming soon for ID: " << fid << "\n";
                pressAnyKey();

    return 0;
}

int optiont(const string& femail, const string& password) {
    system("cls");
    cout << "\t\tTeacher Dashboard\n\n";
    cout << "\t\tWelcome Teacher: " << femail << "\n";
    cout << "\t\tTeacher features coming soon!\n";
                pressAnyKey();

    return 0;
}

int edittcrinfo(const string& femail, const string& password) {
    system("cls");
    cout << "\t\tEdit Teacher Information\n\n";
    cout << "\t\tFeature coming soon for email: " << femail << "\n";
                pressAnyKey();

    return 0;
}

