/**
 * HOSPITAL MANAGEMENT SYSTEM
 * Console-Based Application in C++
 * 
 * Main Entry Point
 * 
 * Compilation: g++ main.cpp User.cpp Patient.cpp Doctor.cpp Appointment.cpp Billing.cpp -o hms
 * Execution: ./hms (Linux/Mac) or hms.exe (Windows)
 */

#include <iostream>
#include <cstdlib>
#include <limits>
#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Billing.h"

using namespace std;

// Function Prototypes
void displayMainMenu();
void displayAdminMenu();
void displayDoctorMenu();
void displayPatientMenu();
void handleLogin();
void handleRegistration();
void handlePatientManagement();
void handleDoctorManagement();
void handleAppointmentManagement();
void handleBillingManagement();
void handleReporting();
void clearScreen();
void pauseScreen();

/**
 * USE CASE DIAGRAM (Textual Representation)
 * 
 * Actors: Admin, Doctor, Patient
 * 
 * Use Cases:
 * 1. Admin:
 *    - Login/Logout
 *    - Manage Patients (Add, Update, Delete, Search, View All)
 *    - Manage Doctors (Add, Update, Delete, Search, View All)
 *    - Manage Appointments (Schedule, Update, Cancel, View All)
 *    - Manage Billing (Generate Bill, Process Payment, View All)
 *    - Generate Reports (Patients, Doctors, Appointments, Billing)
 * 
 * 2. Doctor:
 *    - Login/Logout
 *    - View Appointments
 *    - View Patient Information
 *    - Update Appointment Status
 * 
 * 3. Patient:
 *    - Login/Logout
 *    - View Own Appointments
 *    - View Own Bills
 *    - View Own Information
 */

/**
 * DATA FLOW DIAGRAM - Level 0 (Context Diagram)
 * 
 *                    +-------------------+
 *                    |  User (Actor)     |
 *                    +-------------------+
 *                           | |
 *                           | |
 *                    +------v-v------+
 *                    |   Hospital    |
 *                    |  Management   |
 *                    |    System     |
 *                    +---------------+
 *                           | |
 *                           | |
 *                    +------v-v------+
 *                    |  Data Files   |
 *                    | (Text Files)  |
 *                    +---------------+
 * 
 * DFD Level 1 - Process Decomposition
 * 
 * User Input --> Login Process --> Authentication
 *                              --> Patient Management
 *                              --> Doctor Management
 *                              --> Appointment Management
 *                              --> Billing Management
 *                              --> Reporting
 * 
 * Each Process --> File I/O Operations --> Data Storage
 */

/**
 * SEQUENCE DIAGRAM - Patient Registration and Appointment Scheduling
 * 
 * Actor        System       Patient     Doctor      File
 *   |            |             |           |          |
 *   |--Login---->|             |           |          |
 *   |<--Auth-----|             |           |          |
 *   |            |             |           |          |
 *   |--Register->|             |           |          |
 *   |            |--Add------->|           |          |
 *   |            |             |--Save---->|          |
 *   |            |<--Success---|           |          |
 *   |<--Confirm--|             |           |          |
 *   |            |             |           |          |
 *   |--Schedule->|             |           |          |
 *   |            |--Load------>|           |          |
 *   |            |<--List------|           |          |
 *   |            |--Select---->|           |          |
 *   |            |             |--Load---->|          |
 *   |            |             |<--List----|          |
 *   |            |--Select---->|           |          |
 *   |            |             |           |--Save--->|
 *   |            |<--Success---|           |          |
 *   |<--Confirm--|             |           |          |
 */

int main() {
    int choice;
    bool loggedIn = false;
    string userRole = "";
    
    // Welcome Screen
    clearScreen();
    cout << "========================================\n";
    cout << "   HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "Welcome to the Hospital Management System\n\n";
    
    // Authentication Loop
    while (!loggedIn) {
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                handleLogin();
                if (!User::currentLoggedInUser.empty()) {
                    loggedIn = true;
                    userRole = User::getCurrentUserRole();
                }
                break;
            case 2:
                handleRegistration();
                break;
            case 3:
                cout << "Thank you for using Hospital Management System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n\n";
        }
    }
    
    // Main Menu Loop
    while (loggedIn) {
        clearScreen();
        cout << "========================================\n";
        cout << "   HOSPITAL MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "Logged in as: " << User::currentLoggedInUser 
             << " (" << userRole << ")\n\n";
        
        if (userRole == "admin") {
            displayAdminMenu();
            cin >> choice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                pauseScreen();
                continue;
            }
            
            switch (choice) {
                case 1:
                    handlePatientManagement();
                    break;
                case 2:
                    handleDoctorManagement();
                    break;
                case 3:
                    handleAppointmentManagement();
                    break;
                case 4:
                    handleBillingManagement();
                    break;
                case 5:
                    handleReporting();
                    break;
                case 6:
                    User::logout();
                    loggedIn = false;
                    cout << "Logged out successfully!\n";
                    pauseScreen();
                    break;
                case 7:
                    cout << "Thank you for using Hospital Management System. Goodbye!\n";
                    User::logout();
                    return 0;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    pauseScreen();
            }
        } else if (userRole == "doctor") {
            displayDoctorMenu();
            cin >> choice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                pauseScreen();
                continue;
            }
            
            switch (choice) {
                case 1:
                    Appointment::displayAllAppointments();
                    pauseScreen();
                    break;
                case 2:
                    Patient::displayAllPatients();
                    pauseScreen();
                    break;
                case 3:
                    Appointment::updateAppointment();
                    pauseScreen();
                    break;
                case 4:
                    User::logout();
                    loggedIn = false;
                    cout << "Logged out successfully!\n";
                    pauseScreen();
                    break;
                case 5:
                    cout << "Thank you for using Hospital Management System. Goodbye!\n";
                    User::logout();
                    return 0;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    pauseScreen();
            }
        } else if (userRole == "patient") {
            displayPatientMenu();
            cin >> choice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                pauseScreen();
                continue;
            }
            
            switch (choice) {
                case 1:
                    Appointment::displayAllAppointments();
                    pauseScreen();
                    break;
                case 2:
                    Billing::displayAllBills();
                    pauseScreen();
                    break;
                case 3:
                    User::logout();
                    loggedIn = false;
                    cout << "Logged out successfully!\n";
                    pauseScreen();
                    break;
                case 4:
                    cout << "Thank you for using Hospital Management System. Goodbye!\n";
                    User::logout();
                    return 0;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    pauseScreen();
            }
        } else {
            cout << "Unknown user role. Logging out...\n";
            User::logout();
            loggedIn = false;
        }
    }
    
    return 0;
}

void displayMainMenu() {
    cout << "=== MAIN MENU ===\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
}

void displayAdminMenu() {
    cout << "=== ADMIN MENU ===\n";
    cout << "1. Patient Management\n";
    cout << "2. Doctor Management\n";
    cout << "3. Appointment Management\n";
    cout << "4. Billing Management\n";
    cout << "5. Reports\n";
    cout << "6. Logout\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

void displayDoctorMenu() {
    cout << "=== DOCTOR MENU ===\n";
    cout << "1. View All Appointments\n";
    cout << "2. View All Patients\n";
    cout << "3. Update Appointment\n";
    cout << "4. Logout\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void displayPatientMenu() {
    cout << "=== PATIENT MENU ===\n";
    cout << "1. View My Appointments\n";
    cout << "2. View My Bills\n";
    cout << "3. Logout\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void handleLogin() {
    string username, password;
    clearScreen();
    cout << "=== LOGIN ===\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    
    if (User::login(username, password)) {
        cout << "\nLogin successful! Welcome, " << username << "!\n";
        pauseScreen();
    } else {
        cout << "\nLogin failed! Invalid username or password.\n";
        pauseScreen();
    }
}

void handleRegistration() {
    string username, password, role;
    clearScreen();
    cout << "=== REGISTRATION ===\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Role (admin/doctor/patient): ";
    cin >> role;
    
    // Validate role
    if (role != "admin" && role != "doctor" && role != "patient") {
        cout << "Invalid role! Must be admin, doctor, or patient.\n";
        pauseScreen();
        return;
    }
    
    if (User::registerUser(username, password, role)) {
        cout << "\nRegistration successful! You can now login.\n";
        pauseScreen();
    } else {
        cout << "\nRegistration failed! Username may already exist.\n";
        pauseScreen();
    }
}

void handlePatientManagement() {
    int choice;
    do {
        clearScreen();
        cout << "=== PATIENT MANAGEMENT ===\n";
        cout << "1. Add Patient\n";
        cout << "2. Update Patient\n";
        cout << "3. Delete Patient\n";
        cout << "4. Search Patient\n";
        cout << "5. View All Patients\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        switch (choice) {
            case 1:
                Patient::addPatient();
                pauseScreen();
                break;
            case 2:
                Patient::updatePatient();
                pauseScreen();
                break;
            case 3:
                Patient::deletePatient();
                pauseScreen();
                break;
            case 4:
                Patient::searchPatient();
                pauseScreen();
                break;
            case 5:
                Patient::displayAllPatients();
                pauseScreen();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 6);
}

void handleDoctorManagement() {
    int choice;
    do {
        clearScreen();
        cout << "=== DOCTOR MANAGEMENT ===\n";
        cout << "1. Add Doctor\n";
        cout << "2. Update Doctor\n";
        cout << "3. Delete Doctor\n";
        cout << "4. Search Doctor\n";
        cout << "5. View All Doctors\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        switch (choice) {
            case 1:
                Doctor::addDoctor();
                pauseScreen();
                break;
            case 2:
                Doctor::updateDoctor();
                pauseScreen();
                break;
            case 3:
                Doctor::deleteDoctor();
                pauseScreen();
                break;
            case 4:
                Doctor::searchDoctor();
                pauseScreen();
                break;
            case 5:
                Doctor::displayAllDoctors();
                pauseScreen();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 6);
}

void handleAppointmentManagement() {
    int choice;
    do {
        clearScreen();
        cout << "=== APPOINTMENT MANAGEMENT ===\n";
        cout << "1. Schedule Appointment\n";
        cout << "2. Update Appointment\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. Search Appointment\n";
        cout << "5. View All Appointments\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        switch (choice) {
            case 1:
                Appointment::scheduleAppointment();
                pauseScreen();
                break;
            case 2:
                Appointment::updateAppointment();
                pauseScreen();
                break;
            case 3:
                Appointment::cancelAppointment();
                pauseScreen();
                break;
            case 4:
                Appointment::searchAppointment();
                pauseScreen();
                break;
            case 5:
                Appointment::displayAllAppointments();
                pauseScreen();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 6);
}

void handleBillingManagement() {
    int choice;
    do {
        clearScreen();
        cout << "=== BILLING MANAGEMENT ===\n";
        cout << "1. Generate Bill\n";
        cout << "2. Process Payment\n";
        cout << "3. Search Bill\n";
        cout << "4. View All Bills\n";
        cout << "5. Generate Invoice\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        switch (choice) {
            case 1:
                Billing::generateBill();
                pauseScreen();
                break;
            case 2:
                Billing::processPayment();
                pauseScreen();
                break;
            case 3:
                Billing::searchBill();
                pauseScreen();
                break;
            case 4:
                Billing::displayAllBills();
                pauseScreen();
                break;
            case 5:
                {
                    int billId;
                    cout << "Enter Bill ID: ";
                    cin >> billId;
                    Billing::generateInvoice(billId);
                    pauseScreen();
                }
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 6);
}

void handleReporting() {
    int choice;
    do {
        clearScreen();
        cout << "=== REPORTS ===\n";
        cout << "1. Patient Report\n";
        cout << "2. Doctor Report\n";
        cout << "3. Appointment Report\n";
        cout << "4. Billing Report\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        switch (choice) {
            case 1:
                cout << "\n=== PATIENT REPORT ===\n";
                Patient::displayAllPatients();
                pauseScreen();
                break;
            case 2:
                cout << "\n=== DOCTOR REPORT ===\n";
                Doctor::displayAllDoctors();
                pauseScreen();
                break;
            case 3:
                cout << "\n=== APPOINTMENT REPORT ===\n";
                Appointment::displayAllAppointments();
                pauseScreen();
                break;
            case 4:
                cout << "\n=== BILLING REPORT ===\n";
                Billing::displayAllBills();
                pauseScreen();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
                pauseScreen();
        }
    } while (choice != 5);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

