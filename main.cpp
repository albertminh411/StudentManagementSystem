#include <iostream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string major;
    float gpa;
};

int main() {
    int choice;
    Student students[100];
    int studentCount = 0;

    do {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add student\n";
        cout << "2. Display students\n";
        cout << "3. Search student\n";
        cout << "4. Update student\n";
        cout << "5. Delete student\n";
        cout << "6. Sort students\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
case 1:
    cout << "Enter ID: ";
    cin >> students[studentCount].id;

    cout << "Enter name: ";
    cin >> students[studentCount].name;

    cout << "Enter age: ";
    cin >> students[studentCount].age;

    cout << "Enter major: ";
    cin >> students[studentCount].major;

    cout << "Enter GPA: ";
    cin >> students[studentCount].gpa;

    studentCount++;

    cout << "Student added successfully!\n";
    break;
case 2:
    for (int i = 0; i < studentCount; i++) {
        cout << "ID: " << students[i].id << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Age: " << students[i].age << endl;
        cout << "Major: " << students[i].major << endl;
        cout << "GPA: " << students[i].gpa << endl;
        cout << "--------------------" << endl;
    }
    break;

case 3: 
    {
    int searchId;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> searchId;

    for (int i = 0; i < studentCount; i++) {
        if (searchId == students[i].id) {
            cout << "ID: " << students[i].id << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "Major: " << students[i].major << endl;
            cout << "GPA: " << students[i].gpa << endl;

            found = true;
        }
    }

    if (found == false) {
        cout << "Student not found!\n";
    }

    break;
    }
case 4: {
    int updateId;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> updateId;
    for (int i = 0; i < studentCount; i++) {
    if (updateId == students[i].id) {
    	found = true;
    	cout << "Enter new name: ";
        cin >> students[i].name;

        cout << "Enter new age: ";
        cin >> students[i].age;

        cout << "Enter new major: ";
        cin >> students[i].major;

        cout << "Enter new GPA: ";
        cin >> students[i].gpa;

        cout << "Student updated successfully!\n";
        break;

    }
    }
    if (found == false) {
        cout << "Student not found!\n";
    }

    break;
    }

case 5: {
    int deleteId;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> deleteId;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == deleteId) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            studentCount--;
            found = true;

            cout << "Student deleted successfully!\n";
            break;
        }
    }

    if (found == false) {
        cout << "Student not found!\n";
    }

    break;
}
                

case 6: {
    if (studentCount == 0) {
        cout << "No students to sort!\n";
        break;
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

    cout << "Students sorted by GPA (highest to lowest)!\n";
    break;
}

            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}