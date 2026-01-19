# Hospital Management System

A complete console-based Hospital Management System developed in C++ using Object-Oriented Programming principles.

## Features

### 1. User Authentication
- Login/Logout functionality
- User registration with role-based access (admin, doctor, patient)
- Secure password-based authentication
- User data stored in text files

### 2. Patient Management
- Add new patient records
- Update existing patient information
- Delete patient records
- Search patients by ID
- View all patients

### 3. Doctor/Staff Management
- Add new doctor records
- Update doctor information
- Delete doctor records
- Search doctors by ID
- View all doctors with their specializations

### 4. Appointment Scheduling
- Schedule appointments between patients and doctors
- Update appointment details
- Cancel appointments
- Search appointments
- View all appointments

### 5. Billing and Payment
- Generate bills for patients
- Calculate total charges (consultation, medicine, tests)
- Process payments
- Generate invoices
- Track payment status

### 6. Reporting
- Generate patient reports
- Generate doctor reports
- Generate appointment reports
- Generate billing reports

## Project Structure

```
Hospital Management System/
│
├── main.cpp              # Main entry point with menu system
├── User.h                # User class header file
├── User.cpp              # User class implementation
├── Patient.h             # Patient class header file
├── Patient.cpp           # Patient class implementation
├── Doctor.h              # Doctor class header file
├── Doctor.cpp            # Doctor class implementation
├── Appointment.h         # Appointment class header file
├── Appointment.cpp       # Appointment class implementation
├── Billing.h             # Billing class header file
├── Billing.cpp           # Billing class implementation
├── users.txt             # User data storage
├── patients.txt          # Patient data storage
├── doctors.txt           # Doctor data storage
├── appointments.txt      # Appointment data storage
├── bills.txt             # Billing data storage
└── README.md             # This file
```

## Compilation Instructions

### Using g++ (GCC Compiler)

**For Windows (using MinGW or similar):**
```bash
g++ main.cpp User.cpp Patient.cpp Doctor.cpp Appointment.cpp Billing.cpp -o hms.exe
```

**For Linux/Mac:**
```bash
g++ main.cpp User.cpp Patient.cpp Doctor.cpp Appointment.cpp Billing.cpp -o hms
```

### Using Visual Studio Code (VS Code)

1. **Install C++ Extension:**
   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X)
   - Search for "C/C++" by Microsoft and install it

2. **Install C++ Compiler:**
   - **Windows:** Install MinGW-w64 or use MSVC
   - **Linux:** `sudo apt-get install build-essential` (Ubuntu/Debian)
   - **Mac:** Install Xcode Command Line Tools: `xcode-select --install`

3. **Compile the Project:**
   - Open Terminal in VS Code (Ctrl+` or View → Terminal)
   - Navigate to project directory
   - Run the compilation command above

4. **Run the Program:**
   - **Windows:** `hms.exe`
   - **Linux/Mac:** `./hms`

## Usage

### Default Login Credentials

The system comes with sample users:

- **Admin:**
  - Username: `admin`
  - Password: `admin123`
  - Role: `admin`

- **Doctor:**
  - Username: `doctor1`
  - Password: `doc123`
  - Role: `doctor`

- **Patient:**
  - Username: `patient1`
  - Password: `pat123`
  - Role: `patient`

### Menu Navigation

1. **Login/Register:** Start by logging in or registering a new account
2. **Role-Based Menus:** Different menus appear based on your role
3. **Navigate:** Use numbers to select menu options
4. **Exit:** Choose Exit option or press Ctrl+C to quit

### Admin Menu Options

1. Patient Management (Add, Update, Delete, Search, View All)
2. Doctor Management (Add, Update, Delete, Search, View All)
3. Appointment Management (Schedule, Update, Cancel, Search, View All)
4. Billing Management (Generate Bill, Process Payment, Search, View All, Generate Invoice)
5. Reports (Patient, Doctor, Appointment, Billing Reports)
6. Logout
7. Exit

### Doctor Menu Options

1. View All Appointments
2. View All Patients
3. Update Appointment
4. Logout
5. Exit

### Patient Menu Options

1. View My Appointments
2. View My Bills
3. Logout
4. Exit

## Data Storage Format

All data is stored in text files using pipe (`|`) as delimiter:

- **users.txt:** `username|password|role`
- **patients.txt:** `id|name|age|gender|address|phone|disease|admissionDate`
- **doctors.txt:** `id|name|specialization|qualification|phone|email|availability`
- **appointments.txt:** `id|patientId|doctorId|date|time|status|description`
- **bills.txt:** `id|patientId|appointmentId|consultationFee|medicineCost|testCost|paymentStatus|billingDate`

## System Design

### UML Class Diagram

```
+------------------+        +------------------+
|     Patient      |        |      Doctor      |
+------------------+        +------------------+
| - id             |        | - id             |
| - name           |        | - name           |
| - age            |        | - specialization |
| - gender         |        | - qualification  |
| - address        |        | - phone          |
| - phone          |        | - email          |
| - disease        |        | - availability   |
| - admissionDate  |        +------------------+
+------------------+        | + addDoctor()    |
| + addPatient()   |        | + updateDoctor() |
| + updatePatient()|        | + deleteDoctor() |
| + deletePatient()|        | + searchDoctor() |
| + searchPatient()|        | + display()      |
| + display()      |        +------------------+
+------------------+                 |
        |                            |
        |                            |
        +--------+         +---------+
                 |         |
        +--------v---------v--------+
        |     Appointment           |
        +---------------------------+
        | - id                      |
        | - patientId               |
        | - doctorId                |
        | - date                    |
        | - time                    |
        | - status                  |
        | - description             |
        +---------------------------+
        | + schedule()              |
        | + cancel()                |
        | + update()                |
        | + display()               |
        +---------------------------+
                 |
                 |
        +--------v--------+
        |     Billing     |
        +-----------------+
        | - id            |
        | - patientId     |
        | - appointmentId |
        | - consultationFee|
        | - medicineCost  |
        | - testCost      |
        | - totalAmount   |
        | - paymentStatus|
        | - billingDate   |
        +-----------------+
        | + calculateBill()|
        | + generateInvoice()|
        | + processPayment()|
        | + displayBill() |
        +-----------------+
                 |
                 |
        +--------v--------+
        |      User       |
        +-----------------+
        | - username      |
        | - password      |
        | - role          |
        +-----------------+
        | + login()       |
        | + logout()      |
        | + register()    |
        | + authenticate()|
        +-----------------+
```

### Use Case Diagram

**Actors:** Admin, Doctor, Patient

**Use Cases:**
- Login/Logout
- Register User
- Manage Patients (Admin only)
- Manage Doctors (Admin only)
- Manage Appointments
- Manage Billing (Admin only)
- View Reports
- Generate Invoice

### Data Flow Diagram (Level 0)

```
                    +-------------------+
                    |  User (Actor)     |
                    +-------------------+
                           | |
                           | |
                    +------v-v------+
                    |   Hospital    |
                    |  Management   |
                    |    System     |
                    +---------------+
                           | |
                           | |
                    +------v-v------+
                    |  Data Files   |
                    | (Text Files)  |
                    +---------------+
```

### Sequence Diagram - Patient Registration & Appointment Scheduling

See comments in `main.cpp` for detailed sequence diagram representation.

## Error Handling

The system includes:
- Input validation for all user inputs
- File existence checking
- Invalid ID handling
- Duplicate user prevention
- Error messages for invalid operations

## Technical Requirements

- **Language:** C++ (C++11 or later)
- **Compiler:** g++ (GCC) or any standard C++ compiler
- **Platform:** Windows, Linux, or macOS
- **Dependencies:** Standard C++ Library only (no external dependencies)
- **Storage:** Text file-based (no database required)

## Coding Standards

- Object-Oriented Programming principles
- Modular design with separate header and source files
- Clear naming conventions
- Comprehensive comments
- Input validation and error handling
- Consistent code formatting

## Limitations

- Console-based interface only (no GUI)
- Text file storage (not suitable for large-scale production)
- No data encryption
- Basic authentication (no password hashing)
- Single-user file access (not thread-safe)

## Future Enhancements

Possible improvements:
- Database integration (SQLite, MySQL)
- Password hashing for security
- GUI implementation (Qt, wxWidgets)
- Multi-user concurrent access
- Data encryption
- Email notifications
- Appointment reminders
- Advanced reporting with charts
- Export to PDF/Excel

## License

This project is provided as-is for educational purposes.

## Author

Hospital Management System - Console-Based Application

## Version

1.0.0

## Contact

For questions or issues, please refer to the code documentation or create an issue in the repository.

---

**Note:** This is a console-based application. All interactions are through text menus and command-line input/output.

