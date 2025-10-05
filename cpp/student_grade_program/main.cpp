#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

const string DEFAULT_FILE = "gradebook.txt";

// Klasa Student

class Student {
private:
    int id;
    string name;
    vector<double> grades;

public:
    Student(int id, const string& name) : id(id), name(name) {}

    int getId() const { return id; }
    string getName() const { return name; }

    void addGrade(double grade) {
        if (grade >= 0 && grade <= 100) {
            grades.push_back(grade);
            cout << "Grade added successfully." << endl;
        }
        else
            cout << "Invalid grade. Must be between 0 and 100." << endl;
    }

    double average() const {
        if (grades.empty()) return 0.0;
        double sum = 0;
        for (double g : grades) sum += g;
        return sum / grades.size();
    }

    void printReport() const {
        cout << "ID: " << id << ", Name: " << name << ", Grades: ";
        if (grades.empty()) cout << "None";
        else {
            for (double g : grades) cout << fixed << setprecision(2) << g << " ";
        }
        cout << ", Average: " << fixed << setprecision(2) << average() << endl;
    }

    vector<double> getGrades() const { return grades; }
};

// Klasa Gradebook

class Gradebook {
private:
    vector<Student> students;

public:
    void addStudent(int id, const string& name) {
        for (const auto& s : students)
            if (s.getId() == id) {
                cout << "Student with ID " << id << " already exists." << endl;
                return;
            }
        students.emplace_back(id, name);
        cout << "Student added successfully." << endl;
    }

    vector<Student*> searchStudent(const string& keyword) {
        vector<Student*> results;
        for (auto& s : students) {
            if (to_string(s.getId()).find(keyword) != string::npos ||
                s.getName().find(keyword) != string::npos) {
                results.push_back(&s);
            }
        }
        return results;
    }

    void addGradeInteractive() {
        if (students.empty()) {
            cout << "No students in gradebook." << endl;
            return;
        }

        string keyword;
        cout << "Enter student ID or name fragment: ";
        cin.ignore();
        getline(cin, keyword);

        vector<Student*> matches = searchStudent(keyword);

        if (matches.empty()) {
            cout << "No matching student found." << endl;
            return;
        }

        cout << "Found " << matches.size() << " student(s):" << endl;
        for (size_t i = 0; i < matches.size(); ++i) {
            cout << i + 1 << ". ";
            matches[i]->printReport();
        }

        size_t choice = 1;
        if (matches.size() > 1) {
            cout << "Select student number to add grade: ";
            cin >> choice;
            if (choice < 1 || choice > matches.size()) {
                cout << "Invalid choice." << endl;
                return;
            }
        }

        double grade;
        cout << "Enter grade (0-100): ";
        cin >> grade;
        matches[choice - 1]->addGrade(grade);

    }

    void printReport() const {
        if (students.empty()) {
            cout << "No students in gradebook." << endl;
            return;
        }

        vector<Student> sorted = students;
        sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) {
            return a.average() > b.average();
        });

        cout << "\n===== GRADEBOOK REPORT =====" << endl;
        for (const auto& s : sorted)
            s.printReport();
        cout << "Class average: " << fixed << setprecision(2) << classAverage() << endl;
        cout << "============================" << endl;
    }

    double classAverage() const {
        if (students.empty()) return 0.0;
        double sum = 0;
        int count = 0;
        for (const auto& s : students) {
            if (!s.getGrades().empty()) {
                sum += s.average();
                count++;
            }
        }
        return count ? sum / count : 0.0;
    }

    void saveToFile(const string& filename = DEFAULT_FILE) const {
        ofstream file(filename);
        if (!file) {
            cout << "Error: Cannot open file for writing." << endl;
            return;
        }
        for (const auto& s : students) {
            file << s.getId() << " " << s.getName() << " ";
            for (double g : s.getGrades()) file << g << " ";
            file << endl;
        }
        cout << "Gradebook saved to \"" << filename << "\" successfully." << endl;
    }

    void loadFromFile(const string& filename = DEFAULT_FILE) {
        ifstream file(filename);
        if (!file) {
            cout << "No gradebook file found. Starting with empty gradebook." << endl;
            return;
        }

        students.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            int id;
            string name;
            ss >> id >> name;

            Student s(id, name);
            double grade;
            while (ss >> grade) {
                s.addGrade(grade);
            }
            students.push_back(s);
        }

        cout << "Gradebook loaded from \"" << filename << "\" successfully." << endl;
    }
};

// Main

int main() {
    Gradebook gb;
    gb.loadFromFile();

    int choice;

    while (true) {
        cout << "\n--- STUDENT GRADE MANAGER ---" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Add grade" << endl;
        cout << "3. Print gradebook report" << endl;
        cout << "4. Print class average" << endl;
        cout << "5. Save gradebook to file" << endl;
        cout << "6. Quit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            cout << "Enter student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter student name: ";
            getline(cin, name);
            gb.addStudent(id, name);
        } else if (choice == 2) {
            gb.addGradeInteractive();
        } else if (choice == 3) {
            gb.printReport();
        } else if (choice == 4) {
            cout << "Class average: " << fixed << setprecision(2) << gb.classAverage() << endl;
        } else if (choice == 5) {
            string filename;
            cout << "Enter filename (or press Enter for default): ";
            cin.ignore();
            getline(cin, filename);
            if (filename.empty()) filename = DEFAULT_FILE;
            gb.saveToFile(filename);
        } else if (choice == 6) {
            gb.saveToFile();
            cout << "Exiting program. Gradebook saved." << endl;
            break;
        } else {
            cout << "Invalid option. Try again." << endl;
        }
    }

    return 0;
}
