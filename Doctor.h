#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

/**
 * UML Class Diagram - Doctor
 * +------------------+
 * |      Doctor      |
 * +------------------+
 * | - id             |
 * | - name           |
 * | - specialization |
 * | - qualification  |
 * | - phone          |
 * | - email          |
 * | - availability   |
 * +------------------+
 * | + addDoctor()    |
 * | + updateDoctor() |
 * | + deleteDoctor() |
 * | + searchDoctor() |
 * | + display()      |
 * +------------------+
 */

class Doctor {
private:
    int id;
    std::string name;
    std::string specialization;
    std::string qualification;
    std::string phone;
    std::string email;
    std::string availability; // "available", "busy", "on_leave"

public:
    Doctor();
    Doctor(int did, const std::string& n, const std::string& spec, 
           const std::string& qual, const std::string& ph, 
           const std::string& em, const std::string& avail);
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getSpecialization() const;
    std::string getQualification() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getAvailability() const;
    
    // Setters
    void setId(int did);
    void setName(const std::string& n);
    void setSpecialization(const std::string& spec);
    void setQualification(const std::string& qual);
    void setPhone(const std::string& ph);
    void setEmail(const std::string& em);
    void setAvailability(const std::string& avail);
    
    // CRUD operations
    static void addDoctor();
    static void updateDoctor();
    static void deleteDoctor();
    static void searchDoctor();
    static void displayAllDoctors();
    static Doctor findDoctorById(int id);
    static std::vector<Doctor> loadAllDoctors();
    static void saveAllDoctors(const std::vector<Doctor>& doctors);
    
    // Display
    void display() const;
    void displaySummary() const;
    
    // File operations
    static const std::string DOCTOR_FILE;
};

#endif

