#!/bin/bash
echo "Compiling Hospital Management System..."
g++ main.cpp User.cpp Patient.cpp Doctor.cpp Appointment.cpp Billing.cpp -o hms
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Run ./hms to start the program."
else
    echo "Compilation failed!"
fi

