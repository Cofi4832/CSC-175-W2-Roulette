#include <iostream>
#include <vector>
#include <array>
#include <ctime>
#include <fstream>
using namespace std;


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


    ifstream inFile("results.txt");
    if (inFile.is_open()) {
        int value;
        int i = 0;
        while (inFile >> value && i < 10) {
            lastResults[i++] = value;
        }
        inFile.close();
    }

    cout << "\nWELCOME TO ROULETTE!!! \n";

    while (again == 'y' || again == 'Y') {

        cout << "\nBalance: $" << money << endl;

        if (money <= 0) {
            cout << "You are out of money! GAME OVER!!!.\n";
            break;
        }

        double bet;
        while (true) {
            cout << "Enter bet amount: $";
            cin >> bet;

            if (cin.fail() || bet <= 0 || bet > money) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nInvalid bet. Try again.\n";
            } else break;
        }

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
                cout << "\nInvalid choice. Enter a number 1–9.\n";
            } else break;
        }

        int chosenDozen = -1;
        int chosenColumn = -1;
        int chosenNumber = -1;

        if (choice == 7) {
            while (true) {
                cout << "Choose dozen (1) 1–12, (2) 13–24, (3) 25–36: ";
                cin >> chosenDozen;
                if (cin.fail() || chosenDozen < 1 || chosenDozen > 3) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nInvalid dozen.\n";
                } else break;
            }
        }

        if (choice == 8) {
            while (true) {
                cout << "Choose column (1, 2, or 3): ";
                cin >> chosenColumn;
                if (cin.fail() || chosenColumn < 1 || chosenColumn > 3) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nInvalid column.\n";
                } else break;
            }
        }

        if (choice == 9) {
            while (true) {
                cout << "Choose a number (0–36): ";
                cin >> chosenNumber;
                if (cin.fail() || chosenNumber < 0 || chosenNumber > 36) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nInvalid number.\n";
                } else break;
            }
        }

        int spin = rand() % 37;
        cout << "\nThe ball landed on " << spin;
        if (spin == 0) cout << " GREEN\n";
        else if (isRed(spin)) cout << " RED\n";
        else cout << " BLACK\n";

        bool win = false;
        double payout = 0;
        string history = "Bet type " + to_string(choice) + ", landed " + to_string(spin);

        switch (choice) {
        case 1: win = (spin != 0 && isRed(spin)); payout = bet; break;
        case 2: win = (spin != 0 && !isRed(spin)); payout = bet; break;
        case 3: win = (spin != 0 && spin % 2 == 0); payout = bet; break;
        case 4: win = (spin % 2 == 1); payout = bet; break;
        case 5: win = (spin >= 19 && spin <= 36); payout = bet; break;
        case 6: win = (spin >= 1 && spin <= 18); payout = bet; break;

        case 7:
            win = (spin >= (chosenDozen - 1) * 12 + 1 && spin <= chosenDozen * 12);
            payout = bet * 2;
            break;

        case 8:
            win = (spin != 0 && ((spin - chosenColumn) % 3 == 0));
            payout = bet * 2;
            break;

        case 9:
            win = (spin == chosenNumber);
            payout = bet * 35;
            break;
        }

        if (win) {
            cout << "YOU WIN!!! +$" << payout << endl;
            money += payout;
        } else {
            cout << "YOU LOSE!!! -$" << bet << endl;
            money -= bet;
        }

        lastResults[resultIndex] = spin;
        resultIndex = (resultIndex + 1) % 10;

        betHistory.push_back(history);

        while (true) {
            cout << "Bet again? (y/n): ";
            cin >> again;
            if (again == 'y' || again == 'Y' || again == 'n' || again == 'N')
                break;
            cout << " Invalid input. Enter y or n.\n";
        }
    }

    ofstream outFile("results.txt");
    if (outFile.is_open()) {

        outFile << "=== Last 10 Spins ===\n";
        for (int r : lastResults) {
            outFile << r << "\n";
        }

        outFile << "\nFinal Balance: $" << money << "\n";
        outFile << "======================\n";

        outFile.close();
    }

    cout << "\nResults saved to results.txt\n";
    cout << "\nYou finished the game with: $" << money << endl;
    cout << "\nTHANKS FOR PLAYING!!!\n";

    return 0;
}