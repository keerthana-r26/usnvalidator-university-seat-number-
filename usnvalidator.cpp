#include <iostream>
#include <regex>
#include <vector>

// Admin credentials
const std::string ADMIN_USERNAME = "admin";
const std::string ADMIN_PASSWORD = "password";

struct Student {
    std::string usn;
    char name[50];
    int semester;
    std::string email;
};

std::vector<Student> studentRecords;

bool validateUSN(const std::string& usn) {
    std::regex pattern("^[1-9][A-Za-z]{2}\\d{2}[A-Za-z]{2}\\d{3}$");
    return std::regex_match(usn, pattern);
}

bool validateEmail(const std::string& email) {
    std::regex pattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    return std::regex_match(email, pattern);
}

void validateFormat() {
    std::string usnToValidate;
    std::cout << "Enter USN to validate format: ";
    std::cin >> usnToValidate;

    if (validateUSN(usnToValidate)) {
        std::cout << "USN format is valid." << std::endl;
    } else {
        std::cout << "USN format is invalid." << std::endl;
    }
}

void addUSN() {
    Student newStudent;

    std::cout << "Enter USN: ";
    std::cin >> newStudent.usn;

    if (!validateUSN(newStudent.usn)) {
        std::cout << "Invalid USN." << std::endl;
        return;
    }

    std::cout << "Enter Name: ";
    std::cin.ignore();
    std::cin.getline(newStudent.name, sizeof(newStudent.name));

    std::regex namePattern("^[A-Za-z ]+$");
    if (!std::regex_match(newStudent.name, namePattern)) {
        std::cout << "Invalid name. Name should only contain alphabetic characters." << std::endl;
        return;
    }

    std::cout << "Enter Semester: ";
    std::string semesterStr;
    std::cin >> semesterStr;

    if (semesterStr.length() != 1 || !std::isdigit(semesterStr[0])) {
        std::cout << "Invalid semester. Semester should be a single digit." << std::endl;
        return;
    }

    newStudent.semester = semesterStr[0] - '0';

    std::cout << "Enter Email: ";
    std::cin >> newStudent.email;

    if (!validateEmail(newStudent.email)) {
        std::cout << "Invalid email." << std::endl;
        return;
    }

    studentRecords.push_back(newStudent);
    std::cout << "USN added successfully." << std::endl;
}

void deleteUSN() {
    std::string usnToDelete;
    std::cout << "Enter USN to delete: ";
    std::cin >> usnToDelete;

    for (auto it = studentRecords.begin(); it != studentRecords.end(); ++it) {
        if (it->usn == usnToDelete) {
            studentRecords.erase(it);
            std::cout << "USN deleted successfully." << std::endl;
            return;
        }
    }

    std::cout << "USN not found." << std::endl;
}

void modifyUSN() {
    std::string usnToModify;
    std::cout << "Enter USN to modify: ";
    std::cin >> usnToModify;

    for (auto& student : studentRecords) {
        if (student.usn == usnToModify) {
            std::cout << "Enter new Name: ";
            std::cin.ignore();
            std::cin.getline(student.name, sizeof(student.name));

            std::regex namePattern("^[A-Za-z ]+$");
            if (!std::regex_match(student.name, namePattern)) {
                std::cout << "Invalid name. Name should only contain alphabetic characters." << std::endl;
                return;
            }

            std::cout << "Enter new Semester: ";
            std::string semesterStr;
            std::cin >> semesterStr;

            if (semesterStr.length() != 1 || !std::isdigit(semesterStr[0])) {
                std::cout << "Invalid semester. Semester should be a single digit." << std::endl;
                return;
            }

            student.semester = semesterStr[0] - '0';

            std::cout << "Enter new Email: ";
            std::cin >> student.email;

            if (!validateEmail(student.email)) {
                std::cout << "Invalid email." << std::endl;
                return;
            }

            std::cout << "USN modified successfully." << std::endl;
            return;
        }
    }

    std::cout << "USN not found." << std::endl;
}

void searchUSN() {
    std::string usnToSearch;
    std::cout << "Enter USN to search: ";
    std::cin >> usnToSearch;

    for (const auto& student : studentRecords) {
        if (student.usn == usnToSearch) {
            std::cout << "USN: " << student.usn << std::endl;
            std::cout << "Name: " << student.name << std::endl;
            std::cout << "Semester: " << student.semester << std::endl;
            std::cout << "Email: " << student.email << std::endl;
            return;
        }
    }

    std::cout << "USN not found." << std::endl;
}

void displayAllUSN() {
    if (studentRecords.empty()) {
        std::cout << "No USN records found." << std::endl;
        return;
    }

    std::cout << "----- All USN Records -----" << std::endl;
    std::cout << "USN\t\tName\t\tSemester\tEmail" << std::endl;
    for (const auto& student : studentRecords) {
        std::cout << student.usn << "\t" << student.name << "\t\t" << student.semester << "\t\t" << student.email << std::endl;
    }
}

bool adminLogin() {
    std::string username, password;
    std::cout << "----- Admin Login -----" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        std::cout << "Login successful." << std::endl;
        return true;
    } else {
        std::cout << "Invalid credentials. Access denied." << std::endl;
        return false;
    }
}

int main() {
    if (!adminLogin()) {
        std::cout << "Exiting program." << std::endl;
        return 0;
    }

    int choice;

    while (true) {
        std::cout << "\n----- USN Validator -----" << std::endl;
        std::cout << "1. Validate USN Format" << std::endl;
        std::cout << "2. Add USN" << std::endl;
        std::cout << "3. Delete USN" << std::endl;
        std::cout << "4. Modify USN" << std::endl;
        std::cout << "5. Search USN" << std::endl;
        std::cout << "6. Display All USN Records" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                validateFormat();
                break;
            case 2:
                addUSN();
                break;
            case 3:
                deleteUSN();
                break;
            case 4:
                modifyUSN();
                break;
            case 5:
                searchUSN();
                break;
            case 6:
                displayAllUSN();
                break;
            case 7:
                std::cout << "Exiting program." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}

