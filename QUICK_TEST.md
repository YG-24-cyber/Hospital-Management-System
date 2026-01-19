# Quick Testing Guide

## ✅ Your program is compiled and ready!

The executable `hms.exe` has been created successfully.

## How to Run:

1. **Double-click** `hms.exe` in File Explorer, OR
2. **Run in terminal:**
   ```
   hms.exe
   ```

## Quick Test Steps:

### 1️⃣ Test Login (Start Here!)

When the program starts:
- Choose option **1** (Login)
- Username: `admin`
- Password: `admin123`
- You should see the Admin Menu!

### 2️⃣ Test Viewing Data

In Admin Menu, try:
- Option **1** → Patient Management → Option **5** (View All Patients)
- Option **2** → Doctor Management → Option **5** (View All Doctors)  
- Option **3** → Appointment Management → Option **5** (View All Appointments)
- Option **4** → Billing Management → Option **4** (View All Bills)

You should see sample data already loaded!

### 3️⃣ Test Adding New Data

Try adding a new patient:
- Admin Menu → Option **1** (Patient Management) → Option **1** (Add Patient)
- Fill in the details
- You'll see "Patient added successfully!"

### 4️⃣ Test Different User Roles

**Test as Doctor:**
- Logout (Option 6)
- Login with: `doctor1` / `doc123`
- You'll see a different menu (Doctor Menu)

**Test as Patient:**
- Logout
- Login with: `patient1` / `pat123`
- You'll see Patient Menu

### 5️⃣ Test Features

**Admin Features:**
- ✅ Add/Update/Delete Patients
- ✅ Add/Update/Delete Doctors
- ✅ Schedule/Update/Cancel Appointments
- ✅ Generate Bills and Process Payments
- ✅ View Reports

**Doctor Features:**
- ✅ View Appointments
- ✅ View Patients
- ✅ Update Appointments

**Patient Features:**
- ✅ View Own Appointments
- ✅ View Own Bills

## Tips:

- **Press Enter** after each input
- Use numbers to select menu options
- Type **6** or **7** to go back/exit
- All data is saved automatically to text files

## Default Test Accounts:

| Role   | Username  | Password  |
|--------|-----------|-----------|
| Admin  | admin     | admin123  |
| Doctor | doctor1   | doc123    |
| Patient| patient1  | pat123    |

## Sample Data Already Loaded:

- **2 Patients** (John Doe, Jane Smith)
- **3 Doctors** (Dr. Sarah Johnson, Dr. Michael Brown, Dr. Emily Davis)
- **2 Appointments**
- **2 Bills**

Try viewing them first, then add your own data!

---

**Need more details?** See `TESTING_GUIDE.md` for comprehensive testing scenarios.

