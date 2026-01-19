#include "Doctor.h"
#include <algorithm>
#include <limits>

const std::string Doctor::DOCTOR_FILE = "doctors.txt";

Doctor::Doctor() : id(0), name(""), specialization(""), qualification(""), phone(""), email(""), availability("available") {}

Doctor::Doctor(int did, const std::string& n, const std::string& spec, 
               const std::string& qual, const std::string& ph, 
               const std::string& em, const std::string& avail)
    : id(did), name(n), specialization(spec), qualification(qual), phone(ph), email(em), availability(avail) {}

int Doctor::getId() const { return id; }
std::string Doctor::getName() const { return name; }
std::string Doctor::getSpecialization() const { return specialization; }
std::string Doctor::getQualification() const { return qualification; }
std::string Doctor::getPhone() const { return phone; }
std::string Doctor::getEmail() const { return email; }
std::string Doctor::getAvailability() const { return availability; }

void Doctor::setId(int did) { id = did; }
void Doctor::setName(const std::string& n) { name = n; }
void Doctor::setSpecialization(const std::string& spec) { specialization = spec; }
void Doctor::setQualification(const std::string& qual) { qualification = qual; }
void Doctor::setPhone(const std::string& ph) { phone = ph; }
void Doctor::setEmail(const std::string& em) { email = em; }
void Doctor::setAvailability(const std::string& avail) { availability = avail; }

void Doctor::addDoctor() {
    Doctor doctor;
    std::vector<Doctor> doctors = loadAllDoctors();
    
    // Generate new ID
    int newId = 1;
    if (!doctors.empty()) {
        int maxId = 0;
        for (const auto& d : doctors) {
            if (d.getId() > maxId) maxId = d.getId();
        }
        newId = maxId + 1;
    }
    doctor.setId(newId);
    
    std::cout << "\n=== ADD NEW DOCTOR ===\n";
    std::cout << "Doctor ID: " << newId << "\n";
    
    std::cin.ignore();
    std::cout << "Enter Name: ";
    std::getline(std::cin, doctor.name);
    
    std::cout << "Enter Specialization: ";
    std::getline(std::cin, doctor.specialization);
    
    std::cout << "Enter Qualification: ";
    std::getline(std::cin, doctor.qualification);
    
    std::cout << "Enter Phone: ";
    std::getline(std::cin, doctor.phone);
    
    std::cout << "Enter Email: ";
    std::getline(std::cin, doctor.email);
    
    std::cout << "Enter Availability (available/busy/on_leave): ";
    std::getline(std::cin, doctor.availability);
    
    doctors.push_back(doctor);
    saveAllDoctors(doctors);
    std::cout << "\nDoctor added successfully!\n";
}

void Doctor::updateDoctor() {
    int id;
    std::cout << "\n=== UPDATE DOCTOR ===\n";
    std::cout << "Enter Doctor ID to update: ";
    std::cin >> id;
    
    std::vector<Doctor> doctors = loadAllDoctors();
    bool found = false;
    
    for (auto& d : doctors) {
        if (d.getId() == id) {
            found = true;
            std::cout << "\nCurrent Doctor Information:\n";
            d.display();
            
            std::cin.ignore();
            std::cout << "\nEnter new Name (or press Enter to keep current): ";
            std::string name;
            std::getline(std::cin, name);
            if (!name.empty()) d.setName(name);
            
            std::cout << "Enter new Specialization (or press Enter to keep current): ";
            std::string spec;
            std::getline(std::cin, spec);
            if (!spec.empty()) d.setSpecialization(spec);
            
            std::cout << "Enter new Qualification (or press Enter to keep current): ";
            std::string qual;
            std::getline(std::cin, qual);
            if (!qual.empty()) d.setQualification(qual);
            
            std::cout << "Enter new Phone (or press Enter to keep current): ";
            std::string phone;
            std::getline(std::cin, phone);
            if (!phone.empty()) d.setPhone(phone);
            
            std::cout << "Enter new Email (or press Enter to keep current): ";
            std::string email;
            std::getline(std::cin, email);
            if (!email.empty()) d.setEmail(email);
            
            std::cout << "Enter new Availability (or press Enter to keep current): ";
            std::string avail;
            std::getline(std::cin, avail);
            if (!avail.empty()) d.setAvailability(avail);
            
            break;
        }
    }
    
    if (found) {
        saveAllDoctors(doctors);
        std::cout << "\nDoctor updated successfully!\n";
    } else {
        std::cout << "\nDoctor not found!\n";
    }
}

void Doctor::deleteDoctor() {
    int id;
    std::cout << "\n=== DELETE DOCTOR ===\n";
    std::cout << "Enter Doctor ID to delete: ";
    std::cin >> id;
    
    std::vector<Doctor> doctors = loadAllDoctors();
    auto it = std::remove_if(doctors.begin(), doctors.end(),
                             [id](const Doctor& d) { return d.getId() == id; });
    
    if (it != doctors.end()) {
        doctors.erase(it, doctors.end());
        saveAllDoctors(doctors);
        std::cout << "\nDoctor deleted successfully!\n";
    } else {
        std::cout << "\nDoctor not found!\n";
    }
}

void Doctor::searchDoctor() {
    int id;
    std::cout << "\n=== SEARCH DOCTOR ===\n";
    std::cout << "Enter Doctor ID: ";
    std::cin >> id;
    
    Doctor doctor = findDoctorById(id);
    if (doctor.getId() != 0) {
        std::cout << "\nDoctor Found:\n";
        doctor.display();
    } else {
        std::cout << "\nDoctor not found!\n";
    }
}

void Doctor::displayAllDoctors() {
    std::vector<Doctor> doctors = loadAllDoctors();
    
    if (doctors.empty()) {
        std::cout << "\nNo doctors found.\n";
        return;
    }
    
    std::cout << "\n=== ALL DOCTORS ===\n";
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(20) << "Specialization" 
              << std::setw(15) << "Qualification" 
              << std::setw(15) << "Phone" 
              << std::setw(15) << "Availability" << "\n";
    std::cout << std::string(90, '-') << "\n";
    
    for (const auto& d : doctors) {
        std::cout << std::left << std::setw(5) << d.getId()
                  << std::setw(20) << d.getName()
                  << std::setw(20) << d.getSpecialization()
                  << std::setw(15) << d.getQualification()
                  << std::setw(15) << d.getPhone()
                  << std::setw(15) << d.getAvailability() << "\n";
    }
    std::cout << "\n";
}

Doctor Doctor::findDoctorById(int id) {
    std::vector<Doctor> doctors = loadAllDoctors();
    for (const auto& d : doctors) {
        if (d.getId() == id) {
            return d;
        }
    }
    return Doctor();
}

std::vector<Doctor> Doctor::loadAllDoctors() {
    std::vector<Doctor> doctors;
    std::ifstream file(DOCTOR_FILE);
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
            
            if (tokens.size() >= 7) {
                int id = std::stoi(tokens[0]);
                Doctor d(id, tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6]);
                doctors.push_back(d);
            }
        }
        file.close();
    }
    return doctors;
}

void Doctor::saveAllDoctors(const std::vector<Doctor>& doctors) {
    std::ofstream file(DOCTOR_FILE);
    if (file.is_open()) {
        for (const auto& d : doctors) {
            file << d.getId() << "|" << d.getName() << "|" << d.getSpecialization() << "|"
                 << d.getQualification() << "|" << d.getPhone() << "|" << d.getEmail() << "|"
                 << d.getAvailability() << "\n";
        }
        file.close();
    }
}

void Doctor::display() const {
    std::cout << "\n=== DOCTOR DETAILS ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Specialization: " << specialization << "\n";
    std::cout << "Qualification: " << qualification << "\n";
    std::cout << "Phone: " << phone << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Availability: " << availability << "\n";
}

void Doctor::displaySummary() const {
    std::cout << "ID: " << id << " | Name: " << name << " | Specialization: " << specialization << "\n";
}

