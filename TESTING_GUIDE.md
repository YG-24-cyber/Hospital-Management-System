# Testing Guide - Hospital Management System

## Quick Start Testing

### Step 1: Compile the Program

**Option A: Using the batch file (Windows)**
```bash
compile.bat
```

**Option B: Manual compilation**
```bash
g++ main.cpp User.cpp Patient.cpp Doctor.cpp Appointment.cpp Billing.cpp -o hms.exe
```

### Step 2: Run the Program
```bash
hms.exe
```

---

## Test Scenarios

### Test 1: Login as Admin

1. **Start the program** - Run `hms.exe`
2. **Select option 1** - Login
3. **Enter credentials:**
   - Username: `admin`
   - Password: `admin123`
4. **Expected Result:** Login successful, Admin menu appears

### Test 2: Admin - Patient Management

**After logging in as admin:**

1. **Select option 1** - Patient Management
2. **Test Add Patient:**
   - Select option 1 (Add Patient)
   - Enter details:
     - Name: Test Patient
     - Age: 25
     - Gender: M
     - Address: Test Address
     - Phone: 123-456-7890
     - Disease: Test Disease
     - Date: 01-02-2024
   - **Expected:** Patient added successfully

3. **Test View All Patients:**
   - Select option 5 (View All Patients)
   - **Expected:** List of all patients displayed

4. **Test Search Patient:**
   - Select option 4 (Search Patient)
   - Enter Patient ID: 1
   - **Expected:** Patient details displayed

5. **Test Update Patient:**
   - Select option 2 (Update Patient)
   - Enter Patient ID: 1
   - Update any field
   - **Expected:** Patient updated successfully

6. **Test Delete Patient:**
   - Select option 3 (Delete Patient)
   - Enter Patient ID (use a test ID)
   - **Expected:** Patient deleted successfully

### Test 3: Admin - Doctor Management

1. **Select option 2** - Doctor Management
2. **Test Add Doctor:**
   - Select option 1 (Add Doctor)
   - Enter details:
     - Name: Dr. Test
     - Specialization: Cardiology
     - Qualification: MD
     - Phone: 555-0100
     - Email: test@hospital.com
     - Availability: available
   - **Expected:** Doctor added successfully

3. **Test View All Doctors:**
   - Select option 5 (View All Doctors)
   - **Expected:** List of all doctors displayed

4. **Test Search/Update/Delete** - Similar to patient management

### Test 4: Admin - Appointment Scheduling

1. **Select option 3** - Appointment Management
2. **Test Schedule Appointment:**
   - Select option 1 (Schedule Appointment)
   - Enter:
     - Patient ID: 1 (must exist)
     - Doctor ID: 1 (must exist)
     - Date: 15-02-2024
     - Time: 10:00
     - Description: Regular checkup
   - **Expected:** Appointment scheduled successfully

3. **Test View All Appointments:**
   - Select option 5 (View All Appointments)
   - **Expected:** List of all appointments displayed

4. **Test Update/Cancel Appointment:**
   - Select option 2 or 3
   - Enter Appointment ID
   - **Expected:** Appointment updated/cancelled

### Test 5: Admin - Billing Management

1. **Select option 4** - Billing Management
2. **Test Generate Bill:**
   - Select option 1 (Generate Bill)
   - Enter:
     - Patient ID: 1
     - Appointment ID: 1 (or 0)
     - Consultation Fee: 150.00
     - Medicine Cost: 50.00
     - Test Cost: 100.00
     - Date: 15-02-2024
   - **Expected:** Bill generated, total amount displayed

3. **Test Generate Invoice:**
   - Select option 5 (Generate Invoice)
   - Enter Bill ID: 1
   - **Expected:** Formatted invoice displayed

4. **Test Process Payment:**
   - Select option 2 (Process Payment)
   - Enter Bill ID: 1
   - Change status to "paid"
   - **Expected:** Payment status updated

5. **Test View All Bills:**
   - Select option 4 (View All Bills)
   - **Expected:** List of all bills displayed

### Test 6: Admin - Reports

1. **Select option 5** - Reports
2. **Test each report:**
   - Patient Report (option 1)
   - Doctor Report (option 2)
   - Appointment Report (option 3)
   - Billing Report (option 4)
   - **Expected:** Each report displays relevant data

### Test 7: Doctor Login

1. **Logout** from admin (option 6)
2. **Login** with:
   - Username: `doctor1`
   - Password: `doc123`
3. **Expected:** Doctor menu appears
4. **Test Doctor Features:**
   - View All Appointments (option 1)
   - View All Patients (option 2)
   - Update Appointment (option 3)

### Test 8: Patient Login

1. **Logout** from doctor
2. **Login** with:
   - Username: `patient1`
   - Password: `pat123`
3. **Expected:** Patient menu appears
4. **Test Patient Features:**
   - View My Appointments (option 1)
   - View My Bills (option 2)

### Test 9: User Registration

1. **Logout** (or start fresh)
2. **Select option 2** - Register
3. **Enter details:**
   - Username: newuser
   - Password: password123
   - Role: patient
4. **Expected:** Registration successful
5. **Test login** with new credentials

### Test 10: Error Handling

**Test Invalid Inputs:**
- Invalid login credentials → Should show "Login failed"
- Invalid Patient ID when searching → Should show "Patient not found"
- Invalid menu choice → Should show "Invalid choice"
- Empty fields → Should handle gracefully

**Test File Operations:**
- All data should persist after program restart
- Check text files are created/updated correctly

---

## Sample Test Data

The system comes with pre-loaded sample data:

**Users:**
- admin / admin123 (admin)
- doctor1 / doc123 (doctor)
- patient1 / pat123 (patient)

**Patients:**
- ID 1: John Doe, Hypertension
- ID 2: Jane Smith, Diabetes

**Doctors:**
- ID 1: Dr. Sarah Johnson, Cardiology
- ID 2: Dr. Michael Brown, General Medicine
- ID 3: Dr. Emily Davis, Pediatrics

**Appointments:**
- ID 1: Patient 1 with Doctor 1
- ID 2: Patient 2 with Doctor 2

**Bills:**
- ID 1: Bill for Patient 1
- ID 2: Bill for Patient 2

---

## Testing Checklist

- [ ] Program compiles without errors
- [ ] Program runs and shows welcome screen
- [ ] Login works with valid credentials
- [ ] Login fails with invalid credentials
- [ ] Registration creates new user
- [ ] Admin can manage patients (CRUD)
- [ ] Admin can manage doctors (CRUD)
- [ ] Admin can schedule appointments
- [ ] Admin can generate bills
- [ ] Admin can view reports
- [ ] Doctor can view appointments and patients
- [ ] Patient can view own appointments and bills
- [ ] Data persists in text files
- [ ] Menu navigation works correctly
- [ ] Error handling works for invalid inputs
- [ ] Logout works correctly

---

## Troubleshooting

**Problem: Compilation errors**
- Make sure g++ is installed
- Check all .cpp and .h files are in the same directory
- Verify all includes are correct

**Problem: Program crashes**
- Check if data files exist (users.txt, patients.txt, etc.)
- Verify file permissions
- Check for invalid input handling

**Problem: Data not saving**
- Check file permissions
- Verify file paths are correct
- Check disk space

**Problem: Menu not displaying correctly**
- This is a console application - ensure terminal supports ANSI codes
- Try running in a different terminal (Command Prompt, PowerShell, etc.)

---

## Expected Output Examples

### Login Screen:
```
========================================
   HOSPITAL MANAGEMENT SYSTEM
========================================
Welcome to the Hospital Management System

1. Login
2. Register
3. Exit
Enter your choice:
```

### Admin Menu:
```
=== ADMIN MENU ===
1. Patient Management
2. Doctor Management
3. Appointment Management
4. Billing Management
5. Reports
6. Logout
7. Exit
Enter your choice:
```

### Patient List:
```
=== ALL PATIENTS ===
ID   Name                 Age  Gender     Phone           Disease             Date       
---------------------------------------------------------------------------------------
1    John Doe             35   M          555-0101        Hypertension        15-01-2024
2    Jane Smith           28   F          555-0102        Diabetes            20-01-2024
```

---

## Tips for Testing

1. **Test systematically** - Go through each module one by one
2. **Test edge cases** - Try invalid inputs, empty fields, etc.
3. **Verify data persistence** - Close and reopen program to check data is saved
4. **Test all roles** - Test admin, doctor, and patient functionalities
5. **Check file contents** - Open text files to verify data is stored correctly
6. **Test navigation** - Ensure you can navigate back and forth between menus

Happy Testing! 🏥

