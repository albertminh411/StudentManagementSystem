#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string major;
    float gpa;
};
int inputInt(string prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            return value;
        }

        cout << "Invalid input! Please enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int inputAge() {
    int age;

    while (true) {
        age = inputInt("Enter age: ");

        if (age > 0 && age <= 120) {
            return age;
        }

        cout << "Age must be between 1 and 120!\n";
    }
}

float inputGPA() {
    float gpa;

    while (true) {
        cout << "Enter GPA: ";

        if (cin >> gpa) {
            if (gpa >= 0.0f && gpa <= 4.0f) {
                return gpa;
            }

            cout << "GPA must be between 0.0 and 4.0!\n";
        } else {
            cout << "Invalid input! Please enter a number.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


bool saveStudents(Student students[], int studentCount) {
    ofstream file("students.txt");

    if (!file.is_open()) {
        cout << "Error: Cannot open students.txt!\n";
        return false;
    }

    for (int i = 0; i < studentCount; i++) {
        file << students[i].id << '\n';
        file << students[i].name << '\n';
        file << students[i].age << '\n';
        file << students[i].major << '\n';
        file << students[i].gpa << '\n';
    }

    file.close();

    if (file.fail()) {
        cout << "Error: Failed to save student data!\n";
        return false;
    }

    return true;
}

void loadStudents(Student students[], int &studentCount) {
    ifstream file("students.txt");

    if (!file.is_open()) {
        return;
    }

    studentCount = 0;

    while (studentCount < 100) {
        Student s;

        if (!(file >> s.id)) {
            break;
        }

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(file, s.name)) break;
        if (!(file >> s.age)) break;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(file, s.major)) break;
        if (!(file >> s.gpa)) break;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        students[studentCount] = s;
        studentCount++;
    }

    file.close();
}

int findStudentById(Student students[], int studentCount, int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return i;
        }
    }

    return -1;
}

void displayStudents(Student students[], int studentCount) {
    if (studentCount == 0) {
        cout << "\nThe student list is empty.\n";
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        cout << "\nStudent " << i + 1 << endl;
        cout << "ID: " << students[i].id << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Age: " << students[i].age << endl;
        cout << "Major: " << students[i].major << endl;
        cout << "GPA: " << students[i].gpa << endl;
    }
}

void addStudent(Student students[], int &studentCount) {
    if (studentCount >= 100) {
        cout << "Student list is full!\n";
        return;
    }

    int newId = inputInt("Enter ID: ");

    while (findStudentById(students, studentCount, newId) != -1) {
        cout << "This ID already exists! Please enter another ID.\n";
        newId = inputInt("Enter ID: ");
    }

    students[studentCount].id = newId;

    cout << "Enter name: ";
    getline(cin >> ws, students[studentCount].name);

    students[studentCount].age = inputAge();

    cout << "Enter major: ";
    getline(cin >> ws, students[studentCount].major);

    students[studentCount].gpa = inputGPA();

    studentCount++;

if (saveStudents(students, studentCount)) {
    cout << "Student added successfully!\n";
} else {
    cout << "Student was added in memory, but could not be saved to file.\n";
}
}


void searchStudent(Student students[], int studentCount) {
    if (studentCount == 0) {
        cout << "\nThe student list is empty. Nothing to search.\n";
        return;
    }

    int searchId = inputInt("Enter ID to search: ");
    int index = findStudentById(students, studentCount, searchId);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    cout << "\nStudent found!\n";
    cout << "ID: " << students[index].id << endl;
    cout << "Name: " << students[index].name << endl;
    cout << "Age: " << students[index].age << endl;
    cout << "Major: " << students[index].major << endl;
    cout << "GPA: " << students[index].gpa << endl;
}

void deleteStudent(Student students[], int &studentCount) {
    if (studentCount == 0) {
        cout << "\nThe student list is empty. Nothing to delete.\n";
        return;
    }

    int deleteId = inputInt("Enter ID to delete: ");
    int index = findStudentById(students, studentCount, deleteId);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;

if (saveStudents(students, studentCount)) {
    cout << "Student deleted successfully!\n";
} else {
    cout << "Student was deleted in memory, but could not be saved to file.\n";
}
}

void updateStudent(Student students[], int studentCount) {
    if (studentCount == 0) {
        cout << "\nThe student list is empty. Nothing to update.\n";
        return;
    }

    int updateId = inputInt("Enter ID to update: ");
    int index = findStudentById(students, studentCount, updateId);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    int updateChoice;

    do {
        cout << "\n========== UPDATE STUDENT ==========\n";
        cout << "1. Update name\n";
        cout << "2. Update age\n";
        cout << "3. Update major\n";
        cout << "4. Update GPA\n";
        cout << "0. Back to main menu\n";

        updateChoice = inputInt("Choose: ");

        switch (updateChoice) {
            case 1:
    cout << "Enter new name: ";
    getline(cin >> ws, students[index].name);

    if (saveStudents(students, studentCount)) {
        cout << "Name updated successfully!\n";
    } else {
        cout << "Name updated in memory, but could not be saved to file.\n";
    }
    break;

            case 2:
    students[index].age = inputAge();

    if (saveStudents(students, studentCount)) {
        cout << "Age updated successfully!\n";
    } else {
        cout << "Age updated in memory, but could not be saved to file.\n";
    }
    break;

            case 3:
    cout << "Enter new major: ";
    getline(cin >> ws, students[index].major);

    if (saveStudents(students, studentCount)) {
        cout << "Major updated successfully!\n";
    } else {
        cout << "Major updated in memory, but could not be saved to file.\n";
    }
    break;

            case 4:
    students[index].gpa = inputGPA();

    if (saveStudents(students, studentCount)) {
        cout << "GPA updated successfully!\n";
    } else {
        cout << "GPA updated in memory, but could not be saved to file.\n";
    }
    break;

            case 0:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (updateChoice != 0);
}

void sortStudents(Student students[], int studentCount) {
    if (studentCount == 0) {
        cout << "\nThe student list is empty. Nothing to sort.\n";
        return;
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    if (saveStudents(students, studentCount)) {
    cout << "Students sorted by GPA in descending order!\n";
} else {
    cout << "Students were sorted in memory, but could not be saved to file.\n";
}
}

int main() {
    int choice;
    Student students[100];
    int studentCount = 0;
    loadStudents(students, studentCount);

    do {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add student\n";
        cout << "2. Display students\n";
        cout << "3. Search student\n";
        cout << "4. Update student\n";
        cout << "5. Delete student\n";
        cout << "6. Sort students\n";
        cout << "0. Exit\n";
        choice = inputInt("Choose: ");

        switch (choice) {

case 1:
    addStudent(students, studentCount);
    break;

case 2:
    displayStudents(students, studentCount);
    break;
    
case 3:
    searchStudent(students, studentCount);
    break;

case 4:
    updateStudent(students, studentCount);
    break;

case 5:
    deleteStudent(students, studentCount);
    break;


case 6:
    sortStudents(students, studentCount);
    break;



            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}