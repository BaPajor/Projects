#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

const string FILE_NAME = "tasks.txt";

// Funkcja zapisująca wszystkie zadania do pliku
void saveTasks(const vector<string>& tasks) {
    ofstream file(FILE_NAME);
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    for (const auto& task : tasks)
        file << task << endl;
    file.close();
}

// Funkcja wczytująca zadania z pliku
vector<string> loadTasks() {
    vector<string> tasks;
    ifstream file(FILE_NAME);
    if (!file)
        return tasks;

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            tasks.push_back(line);
    }
    file.close();
    return tasks;
}

int main() {
    vector<string> tasks;
    bool fileLoaded = false;

    cout << "Welcome to Task List Tool!" << endl << endl;

    int choice;
    while (true) {
        cout << endl;
        cout << "====== MENU ======" << endl;
        cout << "1. Load Tasks from File" << endl;
        cout << "2. Add Task(s)" << endl;
        cout << "3. View Tasks" << endl;
        cout << "4. Remove Task(s)" << endl;
        cout << "5. Save Tasks" << endl;
        cout << "6. Quit" << endl;
        cout << "==================" << endl;

        if (!fileLoaded)
            cout << "Status: No file loaded." << endl;
        else
            cout << "Status: Loaded file \"" << FILE_NAME << "\" (" << tasks.size() << " tasks)" << endl;

        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            tasks = loadTasks();
            if (!tasks.empty()) {
                fileLoaded = true;
                cout << "Loaded " << tasks.size() << " tasks from \"" << FILE_NAME << "\" successfully." << endl;
            } else {
                cout << "No tasks loaded (file empty or not found)." << endl;
            }
        }
        else if (choice == 2) {
            int numTasks;
            cout << "How many tasks would you like to add? ";
            cin >> numTasks;
            cin.ignore();

            if (numTasks <= 0) {
                cout << "Invalid number of tasks. Returning to menu." << endl;
                continue;
            }

            for (int i = 1; i <= numTasks; i++) {
                string task;
                cout << "Enter task " << i << ": ";
                getline(cin, task);
                tasks.push_back(task);
                cout << "Task \"" << task << "\" added successfully!" << endl;
            }

            cout << "All tasks added successfully!" << endl;
            fileLoaded = true;
        }
        else if (choice == 3) {
            if (tasks.empty()) {
                cout << "No tasks available." << endl;
            } else {
                cout << "Your Tasks:" << endl;
                for (int i = 0; i < tasks.size(); i++) {
                    cout << (i + 1) << ". " << tasks[i] << endl;
                }
                cout << "Total tasks: " << tasks.size() << endl;
            }
        }
        else if (choice == 4) {
            if (tasks.empty()) {
                cout << "No tasks to remove." << endl;
                continue;
            }

            cout << "You have " << tasks.size() << " tasks." << endl;
            cout << "How many tasks do you want to remove? ";
            int count;
            cin >> count;

            if (count <= 0) {
                cout << "Invalid number of tasks to remove." << endl;
                continue;
            }

            if (count > tasks.size()) {
                cout << "You only have " << tasks.size() << " tasks! Cannot remove " << count << "." << endl;
                continue;
            }

            if (count == tasks.size()) {
                tasks.clear();
                cout << "All tasks removed successfully!" << endl;
            } else {
                vector<int> indices;
                cout << "Enter the task numbers to remove (separated by spaces): ";
                for (int i = 0; i < count; i++) {
                    int num;
                    cin >> num;
                    if (num >= 1 && num <= tasks.size()) {
                        indices.push_back(num);
                    } else {
                        cout << "Invalid task number: " << num << " (ignored)." << endl;
                    }
                }

                // Sortowanie malejące
                sort(indices.rbegin(), indices.rend());

                for (int i : indices) {
                    cout << "Removed: \"" << tasks[i - 1] << "\"" << endl;
                    tasks.erase(tasks.begin() + (i - 1));
                }

                cout << "Selected tasks removed successfully!" << endl;
            }

            saveTasks(tasks);

            if (tasks.empty())
                cout << "No tasks remaining." << endl;
            else {
                cout << "Remaining tasks:" << endl;
                for (int i = 0; i < tasks.size(); i++)
                    cout << (i + 1) << ". " << tasks[i] << endl;
            }
            cout << "Total tasks: " << tasks.size() << endl;
        }
        else if (choice == 5) {
            if (tasks.empty()) {
                cout << "No tasks to save." << endl;
            } else {
                saveTasks(tasks);
                cout << "Tasks saved successfully to \"" << FILE_NAME << "\"." << endl;
                fileLoaded = true;
            }
        }
        else if (choice == 6) {
            cout << "Saving and exiting..." << endl;
            if (!tasks.empty())
                saveTasks(tasks);
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
