@echo off
echo ========================================
echo   Preparing Hospital Management System
echo          for Submission
echo ========================================
echo.

set "SUBMIT_FOLDER=Hospital Management System Submission"

:: Create submission folder
if not exist "%SUBMIT_FOLDER%" mkdir "%SUBMIT_FOLDER%"
echo Created submission folder: %SUBMIT_FOLDER%
echo.

:: Copy source code files
echo Copying source code files...
copy /Y main.cpp "%SUBMIT_FOLDER%\" >nul
copy /Y User.h "%SUBMIT_FOLDER%\" >nul
copy /Y User.cpp "%SUBMIT_FOLDER%\" >nul
copy /Y Patient.h "%SUBMIT_FOLDER%\" >nul
copy /Y Patient.cpp "%SUBMIT_FOLDER%\" >nul
copy /Y Doctor.h "%SUBMIT_FOLDER%\" >nul
copy /Y Doctor.cpp "%SUBMIT_FOLDER%\" >nul
copy /Y Appointment.h "%SUBMIT_FOLDER%\" >nul
copy /Y Appointment.cpp "%SUBMIT_FOLDER%\" >nul
copy /Y Billing.h "%SUBMIT_FOLDER%\" >nul
copy /Y Billing.cpp "%SUBMIT_FOLDER%\" >nul
echo   [OK] Source code files copied
echo.

:: Copy documentation
echo Copying documentation...
copy /Y README.md "%SUBMIT_FOLDER%\" >nul
echo   [OK] Documentation copied
echo.

:: Copy sample data files
echo Copying sample data files...
copy /Y users.txt "%SUBMIT_FOLDER%\" >nul
copy /Y patients.txt "%SUBMIT_FOLDER%\" >nul
copy /Y doctors.txt "%SUBMIT_FOLDER%\" >nul
copy /Y appointments.txt "%SUBMIT_FOLDER%\" >nul
copy /Y bills.txt "%SUBMIT_FOLDER%\" >nul
echo   [OK] Sample data files copied
echo.

:: Copy optional documentation
echo Copying additional documentation...
copy /Y TESTING_GUIDE.md "%SUBMIT_FOLDER%\" >nul 2>&1
copy /Y PROJECT_SUMMARY.txt "%SUBMIT_FOLDER%\" >nul 2>&1
echo   [OK] Additional documentation copied
echo.

:: Create submission info file
echo Creating submission information file...
(
echo ========================================
echo   HOSPITAL MANAGEMENT SYSTEM
echo   Submission Package
echo ========================================
echo.
echo Files Included:
echo - Source Code: 11 files (.cpp and .h)
echo - Documentation: README.md
echo - Sample Data: 5 files (.txt)
echo.
echo COMPILATION INSTRUCTIONS:
echo -------------------------
echo g++ main.cpp User.cpp Patient.cpp Doctor.cpp Appointment.cpp Billing.cpp -o hms.exe
echo.
echo RUN THE PROGRAM:
echo ----------------
echo hms.exe
echo.
echo DEFAULT LOGIN:
echo --------------
echo Username: admin
echo Password: admin123
echo.
echo ========================================
) > "%SUBMIT_FOLDER%\SUBMISSION_INFO.txt"

echo   [OK] Submission info file created
echo.

echo ========================================
echo   SUBMISSION FOLDER READY!
echo ========================================
echo.
echo Folder location: %CD%\%SUBMIT_FOLDER%
echo.
echo Next steps:
echo 1. Check the folder: %SUBMIT_FOLDER%
echo 2. Right-click the folder
echo 3. Send to ^> Compressed (zipped) folder
echo 4. Name it: HospitalManagementSystem_YourName.zip
echo 5. Submit the zip file to your teacher
echo.
echo Press any key to open the submission folder...
pause >nul

:: Open the folder in explorer
explorer "%SUBMIT_FOLDER%"

