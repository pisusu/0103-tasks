#include "partiya_checked.h"

// ====== TESTS FOR TASK 1 ======
void test1(Partiya& p) {
    cout << "\n--- TEST 1 (Task 1) ---\n";
    p.sell();
    p.sell(3);
    p.writeOff(2);
    p.sell();
}
void test2(Partiya& p) {
    cout << "\n--- TEST 2 (Task 1) ---\n";
    p.writeOff(5);
    p.sell(10);
    p.writeOff();
}
void test3(Partiya& p) {
    cout << "\n--- TEST 3 (Task 1) ---\n";
    p.sell(2);
    p.writeOff(2);
    p.sell(1);
    p.writeOff(1);
}

// ====== TESTS FOR TASK 2 ======
void testA(TovarSrok& t) {
    cout << "\n--- TEST A (Task 2) ---\n";
    t.sell(2);
    t.newDay();
    t.sell(1);
    t.newDay();
    t.writeOff(3);
}
void testB(TovarSrok& t) {
    cout << "\n--- TEST B (Task 2, shelf life expires) ---\n";
    t.newDay();
    t.newDay();
    t.sell(1);   // should trigger error
    t.writeOff(2);
}
void testC(TovarSrok& t) {
    cout << "\n--- TEST C (Task 2, mixed) ---\n";
    t.sell(10);
    t.newDay();
    t.writeOff(5);
    t.newDay();
    t.sell(5);
}

// ====== MENU ======
void showMenu() {
    cout << "\n===== MENU =====\n"
        << "1. Sell 1 pc.\n"
        << "2. Sell N pcs.\n"
        << "3. Write off 1 pc.\n"
        << "4. Write off N pcs.\n"
        << "5. New day\n"
        << "6. Show remaining\n"
        << "7. Full report\n"
        << "0. Exit\n"
        << "Your choice: ";
}

int main() {
    int mode;
    cout << "Select mode:\n"
        << "1 - Task 1 (base class tests)\n"
        << "2 - Task 2 (derived class tests)\n"
        << "3 - Interactive menu (Task 2/3)\n"
        << "Your choice: ";
    cin >> mode;

    if (mode == 1) {
        Partiya p;
        int q, d, m, y; string n;
        cout << "Quantity: ";     cin >> q;
        cout << "Name: ";         cin >> n;
        cout << "Date (d m y): "; cin >> d >> m >> y;
        p.init(q, n, d, m, y);

        int testNum;
        cout << "Test number (1-3): "; cin >> testNum;
        switch (testNum) {
        case 1: test1(p); break;
        case 2: test2(p); break;
        case 3: test3(p); break;
        default: cout << "No such test\n"; return 0;
        }
        p.printRemaining();
        p.printReport();
    }
    else if (mode == 2) {
        TovarSrok t;
        int q, d, m, y, shelfLife; string n;
        cout << "Quantity: ";     cin >> q;
        cout << "Name: ";         cin >> n;
        cout << "Date (d m y): "; cin >> d >> m >> y;
        cout << "Shelf life (days): "; cin >> shelfLife;
        t.initExpiring(q, n, d, m, y, shelfLife);

        char variant;
        cout << "Test (A/B/C): "; cin >> variant;
        switch (variant) {
        case 'A': case 'a': testA(t); break;
        case 'B': case 'b': testB(t); break;
        case 'C': case 'c': testC(t); break;
        default: cout << "No such test\n"; return 0;
        }
        t.printRemaining();
        t.printReport();
    }
    else if (mode == 3) {
        PartiyaChecked t;
        int q, d, m, y, shelfLife; string n;
        cout << "Quantity: ";     cin >> q;
        cout << "Name: ";         cin >> n;
        cout << "Date (d m y): "; cin >> d >> m >> y;
        cout << "Shelf life (days): "; cin >> shelfLife;
        t.initChecked(q, n, d, m, y, shelfLife);

        int choice;
        do {
            showMenu();
            cin >> choice;
            switch (choice) {
            case 1: t.sell(); break;
            case 2: { int a; cout << "How many? "; cin >> a; t.sell(a); break; }
            case 3: t.writeOff(); break;
            case 4: { int a; cout << "How many? "; cin >> a; t.writeOff(a); break; }
            case 5: t.newDay(); break;
            case 6: t.printRemaining(); break;
            case 7: t.printReport(); break;
            case 0: cout << "Exit.\n"; break;
            default: cout << "Invalid option\n";
            }
        } while (choice != 0);
    }
    else {
        cout << "Invalid mode\n";
    }

    return 0;
}