#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ctime>
using namespace std;

// Vector: all RED numbers
vector<int> redNumbers = {
    1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36
};

bool isRed(int num) {
    for (int r : redNumbers)
        if (r == num)
            return true;
    return false;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    double money = 100.0;
    char again = 'y';

    array<int, 10> lastResults{};
    int resultIndex = 0;

    vector<string> betHistory;

    cout << " WELCOME TO ROULETTE \n";

    while (again == 'y' || again == 'Y') {

        cout << "\nBalance: $" << money << endl;

        if (money <= 0) {
            cout << "You are out of money! GAME OVER.\n";
            break;
        }

        // --------------------------
        // VALIDATE BET AMOUNT
        // --------------------------
        double bet;
        while (true) {
            cout << "Enter bet amount: $";
            cin >> bet;

            if (cin.fail() || bet <= 0 || bet > money) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << " Invalid bet. Try again.\n";
            } else break;
        }

        // --------------------------
        // VALIDATE BET TYPE
        // --------------------------
        int choice;
        while (true) {
            cout << "\n--- BET OPTIONS ---\n";
            cout << "1 - Red (1:1)\n";
            cout << "2 - Black (1:1)\n";
            cout << "3 - Even (1:1)\n";
            cout << "4 - Odd (1:1)\n";
            cout << "5 - High (19–36) (1:1)\n";
            cout << "6 - Low (1–18) (1:1)\n";
            cout << "7 - Dozen (2:1)\n";
            cout << "8 - Column (2:1)\n";
            cout << "9 - Single Number (35:1)\n";
            cout << "Choose bet type: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 9) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << " Invalid choice. Enter a number 1–9.\n";
            } else break;
        }

        int chosenDozen = -1;
        int chosenColumn = -1;
        int chosenNumber = -1;

        // --------------------------
        // VALIDATE EXTRA INPUTS
        // --------------------------
        if (choice == 7) {
            while (true) {
                cout << "Pick a dozen: (1) 1–12, (2) 13–24, (3) 25–36: ";
                cin >> chosenDozen;
                if (cin.fail() || chosenDozen < 1 || chosenDozen > 3) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " Invalid dozen. Choose 1–3.\n";
                } else break;
            }
        }
        else if (choice == 8) {
            while (true) {
                cout << "Pick column: (1) 1st, (2) 2nd, (3) 3rd: ";
                cin >> chosenColumn;
                if (cin.fail() || chosenColumn < 1 || chosenColumn > 3) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " Invalid column. Choose 1–3.\n";
                } else break;
            }
        }
        else if (choice == 9) {
            while (true) {
                cout << "Pick a number (0–36): ";
                cin >> chosenNumber;
                if (cin.fail() || chosenNumber < 0 || chosenNumber > 36) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " Invalid number. Choose 0–36.\n";
                } else break;
            }
        }

        // --------------------------
        // SPIN AFTER VALID INPUT
        // --------------------------
        int spin = rand() % 37;

        cout << "\nSpinning...\n";
        cout << "Ball lands on " << spin;
        if (spin == 0) cout << " (Green)\n";
        else if (isRed(spin)) cout << " (Red)\n";
        else cout << " (Black)\n";

        bool win = false;
        double payout = 0;
        string history = "Bet type " + to_string(choice) + ", landed on " + to_string(spin);

        // --------------------------
        // BET LOGIC
        // --------------------------
        switch (choice) {
        case 1: win = (spin != 0 && isRed(spin)); payout = bet; break;
        case 2: win = (spin != 0 && !isRed(spin)); payout = bet; break;
        case 3: win = (spin != 0 && spin % 2 == 0); payout = bet; break;
        case 4: win = (spin != 0 && spin % 2 == 1); payout = bet; break;
        case 5: win = (spin >= 19 && spin <= 36); payout = bet; break;
        case 6: win = (spin >= 1 && spin <= 18); payout = bet; break;

        case 7: // Dozens
            win = (spin >= (chosenDozen - 1) * 12 + 1 && spin <= chosenDozen * 12);
            payout = bet * 2;
            break;

        case 8: // Columns
            win = (spin != 0 && ((spin - chosenColumn) % 3 == 0));
            payout = bet * 2;
            break;

        case 9: // Single number
            win = (spin == chosenNumber);
            payout = bet * 35;
            break;
        }

        // --------------------------
        // PAYOUT
        // --------------------------
        if (win) {
            cout << " YOU WIN! +" << payout << endl;
            money += payout;
        } else {
            cout << " YOU lOSE. -" << bet << endl;
            money -= bet;
        }

        // Store results
        lastResults[resultIndex] = spin;
        resultIndex = (resultIndex + 1) % 10;

        // --------------------------
        // VALIDATE "BET AGAIN?"
        // --------------------------
        while (true) {
            cout << "Bet again? (y/n): ";
            cin >> again;

            if (again == 'y' || again == 'Y' || again == 'n' || again == 'N')
                break;

            cout << " Invalid response. Enter 'y' or 'n'.\n";
        }
    }

    cout << "\nTHANKS FOR PLAYING ROULETTE!\n";
    return 0;
}