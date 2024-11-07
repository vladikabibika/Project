#include <iostream>
#include <windows.h>

using namespace std;

struct Student {
    char name[20];
    int age;
    int mark;
    int course;
};

void showStudent(Student* student) {
    cout << "Name: " << student->name << endl;
    cout << "Age: " << student->age << endl;
    cout << "Mark: " << student->mark << endl;
    cout << "Course: " << student->course << endl;
}

void fillStudent(Student& student) {
    cout << "Enter name: ";
    cin >> student.name; 
    cout << "Enter age: ";
    cin >> student.age;
    cout << "Enter mark: ";
    cin >> student.mark;
    cout << "Enter course: ";
    cin >> student.course;
}

void changeMark(Student* student) {
    int newmark;
    cout << "Enter new mark: ";
    cin >> newmark;
    student->mark = newmark;
}

void changeAge(Student* student) {
    int newage;
    cout << "Enter new age: ";
    cin >> newage;
    student->age = newage;
}

void changeCourse(Student* student) {
    int newcourse;
    cout << "Enter new course: ";
    cin >> newcourse;
    student->course = newcourse;
}

void sortStudents(Student* students, int N) {
    Student temp;
    for (int id = 0; id < N - 1; id++) {
        for (int i = 0; i < N - id - 1; i++) {
            if (students[i].mark < students[i + 1].mark) {
                temp = students[i];
                students[i] = students[i + 1];
                students[i + 1] = temp;
            }
        }
    }
}
void saveStudentsToFile(const char* pathToFile, Student* cars, int count) {
    FILE* file;
    if (fopen_s(&file, pathToFile, "w") == 0) {
        fwrite(cars, sizeof(Student), count, file);
        fclose(file);
        cout << "Successfully\n";
    }
    else {
        cout << "Error\n";
    }
}
void loadStudentsFromFile(const char* pathToFile, Student* cars, int count) {
    FILE* file;
    if (fopen_s(&file, pathToFile, "r") == 0) {
        fread(cars, sizeof(Student), count, file);
        fclose(file);
        cout << "Successfully\n";
    }
    else {
        cout << "Error\n";
    }
}
int main() {
    int countStudent;
    cout << "Enter count of students: ";
    cin >> countStudent;

    Student* students = new Student[countStudent];

    int choice, choice2;
    bool run = true;

    while (run) {
        cout << "\nMenu:\n";
        cout << "1. Add students\n";
        cout << "2. Change student data\n";
        cout << "3. Show all students\n";
        cout << "4. Sort students by marks\n";
        cout << "5. Save students to file\n";
        cout << "6. Load students from file\n";
        cout << "7. Exit\n";
        cout << "Choose an action: ";
        cin >> choice;

        switch (choice) {
        case 1:
            for (int i = 0; i < countStudent; i++) {
                cout << "Student #" << i + 1 << endl;
                fillStudent(students[i]);
            }
            break;

        case 2:
            cout << "\nChoose an option to change:\n";
            cout << "1. Change student age\n";
            cout << "2. Change student mark\n";
            cout << "3. Change student course\n";
            cout << "4. Exit\n";
            cout << "Choose an action: ";
            cin >> choice2;

            if (choice2 >= 1 && choice2 <= 3) {
                int studentIndex;
                cout << "Enter the student number (1-" << countStudent << "): ";
                cin >> studentIndex;

                if (studentIndex >= 1 && studentIndex <= countStudent) {
                    Student* student = &students[studentIndex - 1];

                    switch (choice2) {
                    case 1:
                        changeAge(student);
                        break;
                    case 2:
                        changeMark(student);
                        break;
                    case 3:
                        changeCourse(student);
                        break;
                    }
                }
                else {
                    cout << "Invalid student number." << endl;
                }
            }
            break;

        case 3:
            for (int i = 0; i < countStudent; i++) {
                cout << "==========================" << endl;
                cout << "Student #" << i + 1 << endl;
                showStudent(&students[i]);
            }
            break;

        case 4:
            sortStudents(students, countStudent);
            cout << "Students sorted by marks." << endl;
            break;
        case 5: {
            const char* pathToFile = "students.bin";
            saveStudentsToFile(pathToFile, students, countStudent);
            break;
        }

        case 6: {
            const char* pathToFile = "students.bin";
            loadStudentsFromFile(pathToFile, students, countStudent);
            break;
        }
        case 7:
            run = false;
            cout << "Exit..." << endl;
            break;

        default:
            cout << "Error" << endl;
            break;
        }
    }

    delete[] students; 
    return 0;
}
