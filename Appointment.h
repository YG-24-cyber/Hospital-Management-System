#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Patient.h"
#include "Doctor.h"

/**
 * UML Class Diagram - Appointment
 * +------------------+
 * |   Appointment    |
 * +------------------+
 * | - id             |
 * | - patientId      |
 * | - doctorId       |
 * | - date           |
 * | - time           |
 * | - status         |
 * | - description    |
 * +------------------+
 * | + schedule()     |
 * | + cancel()       |
 * | + update()       |
 * | + display()      |
 * +------------------+
 */

class Appointment {
private:
    int id;
    int patientId;
    int doctorId;
    std::string date;
    std::string time;
    std::string status; // "scheduled", "completed", "cancelled"
    std::string description;

public:
    Appointment();
    Appointment(int aid, int pid, int did, const std::string& d, 
                const std::string& t, const std::string& stat, 
                const std::string& desc);
    
    // Getters
    int getId() const;
    int getPatientId() const;
    int getDoctorId() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
    std::string getDescription() const;
    
    // Setters
    void setId(int aid);
    void setPatientId(int pid);
    void setDoctorId(int did);
    void setDate(const std::string& d);
    void setTime(const std::string& t);
    void setStatus(const std::string& stat);
    void setDescription(const std::string& desc);
    
    // Operations
    static void scheduleAppointment();
    static void cancelAppointment();
    static void updateAppointment();
    static void displayAllAppointments();
    static void searchAppointment();
    static Appointment findAppointmentById(int id);
    static std::vector<Appointment> loadAllAppointments();
    static void saveAllAppointments(const std::vector<Appointment>& appointments);
    
    // Display
    void display() const;
    void displayDetailed() const;
    
    // File operations
    static const std::string APPOINTMENT_FILE;
};

#endif

