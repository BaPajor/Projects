#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

const string FILE_NAME = "inventory.txt";

// Zapis do pliku
void saveInventory(const map<string, int>& inventory) {
    ofstream file(FILE_NAME);
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    for (const auto& [item, qty] : inventory)
        file << item << " " << qty << endl;

    cout << "Inventory saved successfully to \"" << FILE_NAME << "\"." << endl;
}

// Odczyt z pliku
map<string, int> loadInventory() {
    map<string, int> inventory;
    ifstream file(FILE_NAME);
    if (!file) {
        cerr << "Warning: No inventory file found. Starting with default data." << endl;
        return inventory;
    }

    string item;
    int qty;
    while (file >> item >> qty)
        inventory[item] = qty;

    cout << "Inventory loaded from \"" << FILE_NAME << "\" successfully." << endl;
    return inventory;
}

// Konwersja mapy do wektora
vector<pair<string, int>> mapToVector(const map<string, int>& inventory) {
    vector<pair<string, int>> data;
    for (const auto& [item, qty] : inventory)
        data.emplace_back(item, qty);
    return data;
}

// Raport
void displayReport(const vector<pair<string, int>>& data) {
    if (data.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }

    cout << "\n===== INVENTORY REPORT =====" << endl;

    int totalItems = 0;
    int totalQuantity = 0;

    string highestItem = data[0].first;
    int highestQuantity = data[0].second;
    string lowestItem = data[0].first;
    int lowestQuantity = data[0].second;

    for (const auto& [item, qty] : data) {
        cout << item << " - " << qty << endl;
        totalItems++;
        totalQuantity += qty;

        if (qty > highestQuantity) {
            highestQuantity = qty;
            highestItem = item;
        }
        if (qty < lowestQuantity) {
            lowestQuantity = qty;
            lowestItem = item;
        }
    }

    double avg;
    if (totalItems){
        avg = (double)totalQuantity / totalItems;
    }
    else{
        avg = 0.0;
    }

    cout << "\nTotal items: " << totalItems << endl;
    cout << "Total quantity: " << totalQuantity << endl;
    cout << "Average stock: " << avg << endl;
    cout << "Highest stock: " << highestItem << " (" << highestQuantity << ")" << endl;
    cout << "Lowest stock: " << lowestItem << " (" << lowestQuantity << ")" << endl;
    cout << "==============================" << endl;
}

// Dodawanie produktu
void addItem(map<string, int>& inventory) {
    string name;
    int qty;

    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter quantity: ";
    cin >> qty;

    if (qty < 0) {
        cout << "Error: Quantity cannot be negative." << endl;
        return;
    }

    inventory[name] += qty;
    cout << "Added " << qty << " of \"" << name << "\" to inventory." << endl;
}

// Aktualizacja
void updateItem(map<string, int>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }

    string name;
    cout << "Enter item name to update: ";
    cin >> name;

    if (inventory.find(name) == inventory.end()) {
        cout << "Item not found." << endl;
        return;
    }

    int newQty;
    cout << "Enter new quantity for " << name << ": ";
    cin >> newQty;

    if (newQty < 0) {
        cout << "Error: Quantity cannot be negative." << endl;
        return;
    }

    inventory[name] = newQty;
    cout << "Quantity for \"" << name << "\" updated to " << newQty << "." << endl;
}

// Usuwanie
void removeItem(map<string, int>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }

    string name;
    cout << "Enter item name to remove: ";
    cin >> name;

    if (inventory.erase(name))
        cout << "Item \"" << name << "\" removed successfully." << endl;
    else
        cout << "Item not found." << endl;
}

// Sortowanie alfabetyczne
void sortAlphabetically(const map<string, int>& inventory) {
    auto data = mapToVector(inventory);
    sort(data.begin(), data.end(), [](auto& a, auto& b) {
        return a.first < b.first;
    });

    cout << "\n--- Sorted Alphabetically ---" << endl;
    displayReport(data);
}

// Sortowanie po ilości
void sortByQuantity(const map<string, int>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }

    auto data = mapToVector(inventory);
    sort(data.begin(), data.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    cout << "\n--- Sorted by Quantity ---" << endl;
    displayReport(data);
}

// Wyszukiwanie produktu
void searchItem(const map<string, int>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }

    string keyword;
    cout << "Enter product name or fragment: ";
    cin >> keyword;

    vector<pair<string, int>> results;
    for (const auto& [item, qty] : inventory)
        if (item.find(keyword) != string::npos)
            results.push_back({item, qty});

    if (results.empty())
        cout << "No items found matching \"" << keyword << "\"." << endl;
    else
        displayReport(results);
}

// Main
int main() {
    map<string, int> inventory = {
        {"apples", 50},
        {"bananas", 30},
        {"oranges", 25},
        {"grapes", 40},
        {"strawberries", 15}
    };

    bool running = true;
    int choice;

    cout << "===== INVENTORY TOOL =====" << endl;

    while (running) {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Display inventory report" << endl;
        cout << "2. Add new item" << endl;
        cout << "3. Update item quantity" << endl;
        cout << "4. Remove item" << endl;
        cout << "5. Save inventory to file" << endl;
        cout << "6. Load inventory from file" << endl;
        cout << "7. Sort alphabetically" << endl;
        cout << "8. Sort by quantity (descending)" << endl;
        cout << "9. Search product by name" << endl;
        cout << "10. Quit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: displayReport(mapToVector(inventory));
                    break;
            case 2: addItem(inventory);
                    break;
            case 3: updateItem(inventory);
                    break;
            case 4: removeItem(inventory);
                    break;
            case 5: saveInventory(inventory);
                    break;
            case 6: inventory = loadInventory();
                    break;
            case 7: sortAlphabetically(inventory);
                    break;
            case 8: sortByQuantity(inventory);
                    break;
            case 9: searchItem(inventory);
                    break;
            case 10:
                cout << "Saving and exiting..." << endl;
                saveInventory(inventory);
                running = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }

    return 0;
}
