#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

/**
 * UML Class Diagram - Patient
 * +------------------+
 * |     Patient      |
 * +------------------+
 * | - id             |
 * | - name           |
 * | - age            |
 * | - gender         |
 * | - address        |
 * | - phone          |
 * | - disease        |
 * | - admissionDate  |
 * +------------------+
 * | + addPatient()   |
 * | + updatePatient()|
 * | + deletePatient()|
 * | + searchPatient()|
 * | + display()      |
 * +------------------+
 */

class Patient {
private:
    int id;
    std::string name;
    int age;
    std::string gender;
    std::string address;
    std::string phone;
    std::string disease;
    std::string admissionDate;

public:
    Patient();
    Patient(int pid, const std::string& n, int a, const std::string& g, 
            const std::string& addr, const std::string& ph, 
            const std::string& dis, const std::string& date);
    
    // Getters
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getAddress() const;
    std::string getPhone() const;
    std::string getDisease() const;
    std::string getAdmissionDate() const;
    
    // Setters
    void setId(int pid);
    void setName(const std::string& n);
    void setAge(int a);
    void setGender(const std::string& g);
    void setAddress(const std::string& addr);
    void setPhone(const std::string& ph);
    void setDisease(const std::string& dis);
    void setAdmissionDate(const std::string& date);
    
    // CRUD operations
    static void addPatient();
    static void updatePatient();
    static void deletePatient();
    static void searchPatient();
    static void displayAllPatients();
    static Patient findPatientById(int id);
    static std::vector<Patient> loadAllPatients();
    static void saveAllPatients(const std::vector<Patient>& patients);
    
    // Display
    void display() const;
    void displaySummary() const;
    
    // File operations
    static const std::string PATIENT_FILE;
};

#endif

