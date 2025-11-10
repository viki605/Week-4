#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// Named constants to replace magic numbers
const int MIN_QUANTITY = 1;                // Minimum valid quantity
const double MIN_PRICE = 1.0;              // Minimum valid price
const int BEGINNER_QUANTITY = 5;           // Threshold for beginner collector
const double MAX_BEGINNER_SPENDING = 20.0; // Max spending for beginner collector
const int ADVANCED_QUANTITY = 10;          // Threshold for advanced collector
const double MAX_FILE_IGNORE = 1000;       // Used to ignore bad input in cin

int main() {
    // Introduction banner
    cout << "==================================================\n";
    cout << "     Welcome to Viktorija's Souvenir Tracker  \n";
    cout << "==================================================\n\n";

    string souvenirName;
    int quantity;
    double pricePerItem;
    double totalCost;

    int choice;
    char continueMenu;

    do { // Menu loop
        cout << "\nMenu:\n";
        cout << "1 - Add a souvenir\n";
        cout << "2 - View souvenir report\n";
        cout << "3 - Recommend collecting level\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1: { // Add souvenirs
            int numToAdd;
            cout << "How many souvenirs do you want to add? ";
            cin >> numToAdd;
            cin.ignore();

            for (int i = 1; i <= numToAdd; i++) {
                cout << "\nSouvenir " << i << ":\n";
                cout << "Enter the name of the souvenir: ";
                getline(cin, souvenirName);

                // While loop for input validation
                while (true) {
                    cout << "Enter the quantity you bought: ";
                    cin >> quantity;
                    if (!cin.fail() && quantity >= MIN_QUANTITY) break;
                    cout << "Invalid input. Quantity must be at least " << MIN_QUANTITY << ".\n";
                    cin.clear();
                    cin.ignore(MAX_FILE_IGNORE, '\n');
                }

                while (true) {
                    cout << "Enter the price per item (USD): ";
                    cin >> pricePerItem;
                    if (!cin.fail() && pricePerItem >= MIN_PRICE) break;
                    cout << "Invalid input. Price must be at least $" << MIN_PRICE << ".\n";
                    cin.clear();
                    cin.ignore(MAX_FILE_IGNORE, '\n');
                }
                cin.ignore();

                totalCost = quantity * pricePerItem;

                // Display formatted summary
                cout << "\n===================== Souvenir Summary =====================\n";
                cout << left << setw(20) << "Souvenir Name" << right << setw(15) << "Quantity"
                    << right << setw(20) << "Price Each ($)" << right << setw(20) << "Total ($)" << endl;
                cout << "------------------------------------------------------------\n";
                cout << left << setw(20) << souvenirName << right << setw(15) << quantity
                    << right << setw(20) << fixed << setprecision(2) << pricePerItem
                    << right << setw(20) << fixed << setprecision(2) << totalCost << endl;

                // Save to file
                ofstream report("report.txt", ios::app); // append mode
                if (report.is_open()) {
                    report << left << setw(20) << souvenirName << right << setw(15) << quantity
                        << right << setw(20) << fixed << setprecision(2) << pricePerItem
                        << right << setw(20) << fixed << setprecision(2) << totalCost << endl;
                    report.close();
                }
            }
            break;
        }

        case 2: { // View report
            cout << "\nOpening report.txt...\n";
            ifstream file("report.txt");
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
            }
            else {
                cout << "Report file not found.\n";
            }
            break;
        }

        case 3: { // Recommend collecting level
            cout << "Enter the total souvenirs collected today: ";
            cin >> quantity;
            cout << "Enter total money spent: ";
            cin >> pricePerItem;

            // Compound boolean if/else using constants
            if (quantity >= BEGINNER_QUANTITY && pricePerItem <= MAX_BEGINNER_SPENDING) {
                cout << "You are a beginner collector. Keep exploring!\n";
            }
            else if (quantity >= ADVANCED_QUANTITY || pricePerItem > MAX_BEGINNER_SPENDING * 2.5) {
                // Example: advanced if spending is high
                cout << "You are an advanced collector!\n";
            }
            else {
                cout << "You are an intermediate collector.\n";
            }
            break;
        }

        default:
            cout << "Invalid menu choice.\n";
            break;
        }

        cout << "\nReturn to menu? (y/n): ";
        cin >> continueMenu;
        cin.ignore();
    } while (continueMenu == 'y' || continueMenu == 'Y');

    cout << "\nThank you for using Viktorija's Souvenir Tracker!\n";
    return 0;
}
