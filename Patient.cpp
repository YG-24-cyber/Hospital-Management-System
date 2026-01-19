#include "Patient.h"
#include <algorithm>
#include <limits>

const std::string Patient::PATIENT_FILE = "patients.txt";

Patient::Patient() : id(0), name(""), age(0), gender(""), address(""), phone(""), disease(""), admissionDate("") {}

Patient::Patient(int pid, const std::string& n, int a, const std::string& g, 
                 const std::string& addr, const std::string& ph, 
                 const std::string& dis, const std::string& date)
    : id(pid), name(n), age(a), gender(g), address(addr), phone(ph), disease(dis), admissionDate(date) {}

int Patient::getId() const { return id; }
std::string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
std::string Patient::getGender() const { return gender; }
std::string Patient::getAddress() const { return address; }
std::string Patient::getPhone() const { return phone; }
std::string Patient::getDisease() const { return disease; }
std::string Patient::getAdmissionDate() const { return admissionDate; }

void Patient::setId(int pid) { id = pid; }
void Patient::setName(const std::string& n) { name = n; }
void Patient::setAge(int a) { age = a; }
void Patient::setGender(const std::string& g) { gender = g; }
void Patient::setAddress(const std::string& addr) { address = addr; }
void Patient::setPhone(const std::string& ph) { phone = ph; }
void Patient::setDisease(const std::string& dis) { disease = dis; }
void Patient::setAdmissionDate(const std::string& date) { admissionDate = date; }

void Patient::addPatient() {
    Patient patient;
    std::vector<Patient> patients = loadAllPatients();
    
    // Generate new ID
    int newId = 1;
    if (!patients.empty()) {
        int maxId = 0;
        for (const auto& p : patients) {
            if (p.getId() > maxId) maxId = p.getId();
        }
        newId = maxId + 1;
    }
    patient.setId(newId);
    
    std::cout << "\n=== ADD NEW PATIENT ===\n";
    std::cout << "Patient ID: " << newId << "\n";
    
    std::cin.ignore();
    std::cout << "Enter Name: ";
    std::getline(std::cin, patient.name);
    
    std::cout << "Enter Age: ";
    std::cin >> patient.age;
    std::cin.ignore();
    
    std::cout << "Enter Gender (M/F/Other): ";
    std::getline(std::cin, patient.gender);
    
    std::cout << "Enter Address: ";
    std::getline(std::cin, patient.address);
    
    std::cout << "Enter Phone: ";
    std::getline(std::cin, patient.phone);
    
    std::cout << "Enter Disease/Diagnosis: ";
    std::getline(std::cin, patient.disease);
    
    std::cout << "Enter Admission Date (DD-MM-YYYY): ";
    std::getline(std::cin, patient.admissionDate);
    
    patients.push_back(patient);
    saveAllPatients(patients);
    std::cout << "\nPatient added successfully!\n";
}

void Patient::updatePatient() {
    int id;
    std::cout << "\n=== UPDATE PATIENT ===\n";
    std::cout << "Enter Patient ID to update: ";
    std::cin >> id;
    
    std::vector<Patient> patients = loadAllPatients();
    bool found = false;
    
    for (auto& p : patients) {
        if (p.getId() == id) {
            found = true;
            std::cout << "\nCurrent Patient Information:\n";
            p.display();
            
            std::cin.ignore();
            std::cout << "\nEnter new Name (or press Enter to keep current): ";
            std::string name;
            std::getline(std::cin, name);
            if (!name.empty()) p.setName(name);
            
            std::cout << "Enter new Age (or 0 to keep current): ";
            int age;
            std::cin >> age;
            if (age > 0) p.setAge(age);
            std::cin.ignore();
            
            std::cout << "Enter new Gender (or press Enter to keep current): ";
            std::string gender;
            std::getline(std::cin, gender);
            if (!gender.empty()) p.setGender(gender);
            
            std::cout << "Enter new Address (or press Enter to keep current): ";
            std::string addr;
            std::getline(std::cin, addr);
            if (!addr.empty()) p.setAddress(addr);
            
            std::cout << "Enter new Phone (or press Enter to keep current): ";
            std::string phone;
            std::getline(std::cin, phone);
            if (!phone.empty()) p.setPhone(phone);
            
            std::cout << "Enter new Disease/Diagnosis (or press Enter to keep current): ";
            std::string disease;
            std::getline(std::cin, disease);
            if (!disease.empty()) p.setDisease(disease);
            
            break;
        }
    }
    
    if (found) {
        saveAllPatients(patients);
        std::cout << "\nPatient updated successfully!\n";
    } else {
        std::cout << "\nPatient not found!\n";
    }
}

void Patient::deletePatient() {
    int id;
    std::cout << "\n=== DELETE PATIENT ===\n";
    std::cout << "Enter Patient ID to delete: ";
    std::cin >> id;
    
    std::vector<Patient> patients = loadAllPatients();
    auto it = std::remove_if(patients.begin(), patients.end(),
                             [id](const Patient& p) { return p.getId() == id; });
    
    if (it != patients.end()) {
        patients.erase(it, patients.end());
        saveAllPatients(patients);
        std::cout << "\nPatient deleted successfully!\n";
    } else {
        std::cout << "\nPatient not found!\n";
    }
}

void Patient::searchPatient() {
    int id;
    std::cout << "\n=== SEARCH PATIENT ===\n";
    std::cout << "Enter Patient ID: ";
    std::cin >> id;
    
    Patient patient = findPatientById(id);
    if (patient.getId() != 0) {
        std::cout << "\nPatient Found:\n";
        patient.display();
    } else {
        std::cout << "\nPatient not found!\n";
    }
}

void Patient::displayAllPatients() {
    std::vector<Patient> patients = loadAllPatients();
    
    if (patients.empty()) {
        std::cout << "\nNo patients found.\n";
        return;
    }
    
    std::cout << "\n=== ALL PATIENTS ===\n";
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(5) << "Age" 
              << std::setw(10) << "Gender" 
              << std::setw(15) << "Phone" 
              << std::setw(20) << "Disease" 
              << std::setw(12) << "Date" << "\n";
    std::cout << std::string(87, '-') << "\n";
    
    for (const auto& p : patients) {
        std::cout << std::left << std::setw(5) << p.getId()
                  << std::setw(20) << p.getName()
                  << std::setw(5) << p.getAge()
                  << std::setw(10) << p.getGender()
                  << std::setw(15) << p.getPhone()
                  << std::setw(20) << p.getDisease()
                  << std::setw(12) << p.getAdmissionDate() << "\n";
    }
    std::cout << "\n";
}

Patient Patient::findPatientById(int id) {
    std::vector<Patient> patients = loadAllPatients();
    for (const auto& p : patients) {
        if (p.getId() == id) {
            return p;
        }
    }
    return Patient();
}

std::vector<Patient> Patient::loadAllPatients() {
    std::vector<Patient> patients;
    std::ifstream file(PATIENT_FILE);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;
            
            while (std::getline(iss, token, '|')) {
                token.erase(0, token.find_first_not_of(" \t"));
                token.erase(token.find_last_not_of(" \t") + 1);
                tokens.push_back(token);
            }
            
            if (tokens.size() >= 8) {
                int id = std::stoi(tokens[0]);
                int age = std::stoi(tokens[2]);
                Patient p(id, tokens[1], age, tokens[3], tokens[4], tokens[5], tokens[6], tokens[7]);
                patients.push_back(p);
            }
        }
        file.close();
    }
    return patients;
}

void Patient::saveAllPatients(const std::vector<Patient>& patients) {
    std::ofstream file(PATIENT_FILE);
    if (file.is_open()) {
        for (const auto& p : patients) {
            file << p.getId() << "|" << p.getName() << "|" << p.getAge() << "|"
                 << p.getGender() << "|" << p.getAddress() << "|" << p.getPhone() << "|"
                 << p.getDisease() << "|" << p.getAdmissionDate() << "\n";
        }
        file.close();
    }
}

void Patient::display() const {
    std::cout << "\n=== PATIENT DETAILS ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Gender: " << gender << "\n";
    std::cout << "Address: " << address << "\n";
    std::cout << "Phone: " << phone << "\n";
    std::cout << "Disease/Diagnosis: " << disease << "\n";
    std::cout << "Admission Date: " << admissionDate << "\n";
}

void Patient::displaySummary() const {
    std::cout << "ID: " << id << " | Name: " << name << " | Disease: " << disease << "\n";
}

