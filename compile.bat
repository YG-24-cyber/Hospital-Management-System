@echo off
echo Compiling Hospital Management System...
g++ main.cpp User.cpp Patient.cpp Doctor.cpp Appointment.cpp Billing.cpp -o hms.exe
if %errorlevel% == 0 (
    echo Compilation successful!
    echo Run hms.exe to start the program.
) else (
    echo Compilation failed!
    pause
)

