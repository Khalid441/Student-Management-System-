#include "header.h"

User s, t;

int main() {
    showMainMenu();
    return 0;
}

void showMainMenu() {
    system("cls");
    system("color 70");

    #ifdef _WIN32
    SetConsoleTitle(TEXT("STUDENT MANAGEMENT SYSTEM"));
    #endif

    int opt;
    cout << "\t\t\t--- Welcome to the Student Management System ---\n\n";
    cout << "\t\t1. Registration\n\t\t2. Login\n\t\t3. Exit\n";

    scrolltext("\n\t\tEnter your choice: ");
    cin >> opt;
    cin.ignore();

    switch (opt) {
        case 1:
            system("cls");
            registration();
            break;
        case 2:
            system("cls");
            login();
            break;
        case 3:
            scrolltext("\t\t\tExiting");
            for (int i = 0; i < 3; i++) {
                cout << ".";
                #ifdef _WIN32
                Sleep(500);
                #else
                this_thread::sleep_for(chrono::milliseconds(500));
                #endif
            }
            exit(0);
        default:
            scrolltext("\t\t\t--- Invalid choice ---\n");
            #ifdef _WIN32
            Beep(800, 500);
            Sleep(1000);
            #endif
            system("cls");
            showMainMenu();
    }
}

