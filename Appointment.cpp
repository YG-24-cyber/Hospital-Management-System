#include "Appointment.h"
#include <algorithm>

const std::string Appointment::APPOINTMENT_FILE = "appointments.txt";

Appointment::Appointment() : id(0), patientId(0), doctorId(0), date(""), time(""), status("scheduled"), description("") {}

Appointment::Appointment(int aid, int pid, int did, const std::string& d, 
                         const std::string& t, const std::string& stat, 
                         const std::string& desc)
    : id(aid), patientId(pid), doctorId(did), date(d), time(t), status(stat), description(desc) {}

int Appointment::getId() const { return id; }
int Appointment::getPatientId() const { return patientId; }
int Appointment::getDoctorId() const { return doctorId; }
std::string Appointment::getDate() const { return date; }
std::string Appointment::getTime() const { return time; }
std::string Appointment::getStatus() const { return status; }
std::string Appointment::getDescription() const { return description; }

void Appointment::setId(int aid) { id = aid; }
void Appointment::setPatientId(int pid) { patientId = pid; }
void Appointment::setDoctorId(int did) { doctorId = did; }
void Appointment::setDate(const std::string& d) { date = d; }
void Appointment::setTime(const std::string& t) { time = t; }
void Appointment::setStatus(const std::string& stat) { status = stat; }
void Appointment::setDescription(const std::string& desc) { description = desc; }

void Appointment::scheduleAppointment() {
    Appointment appointment;
    std::vector<Appointment> appointments = loadAllAppointments();
    
    // Generate new ID
    int newId = 1;
    if (!appointments.empty()) {
        int maxId = 0;
        for (const auto& a : appointments) {
            if (a.getId() > maxId) maxId = a.getId();
        }
        newId = maxId + 1;
    }
    appointment.setId(newId);
    
    std::cout << "\n=== SCHEDULE APPOINTMENT ===\n";
    std::cout << "Appointment ID: " << newId << "\n";
    
    // Display available patients
    Patient::displayAllPatients();
    std::cout << "Enter Patient ID: ";
    std::cin >> appointment.patientId;
    
    // Verify patient exists
    Patient patient = Patient::findPatientById(appointment.patientId);
    if (patient.getId() == 0) {
        std::cout << "Invalid Patient ID!\n";
        return;
    }
    
    // Display available doctors
    Doctor::displayAllDoctors();
    std::cout << "Enter Doctor ID: ";
    std::cin >> appointment.doctorId;
    
    // Verify doctor exists
    Doctor doctor = Doctor::findDoctorById(appointment.doctorId);
    if (doctor.getId() == 0) {
        std::cout << "Invalid Doctor ID!\n";
        return;
    }
    
    std::cin.ignore();
    std::cout << "Enter Date (DD-MM-YYYY): ";
    std::getline(std::cin, appointment.date);
    
    std::cout << "Enter Time (HH:MM): ";
    std::getline(std::cin, appointment.time);
    
    std::cout << "Enter Description: ";
    std::getline(std::cin, appointment.description);
    
    appointment.status = "scheduled";
    
    appointments.push_back(appointment);
    saveAllAppointments(appointments);
    
    std::cout << "\nAppointment scheduled successfully!\n";
    std::cout << "Patient: " << patient.getName() << "\n";
    std::cout << "Doctor: " << doctor.getName() << "\n";
    std::cout << "Date: " << appointment.date << " at " << appointment.time << "\n";
}

void Appointment::cancelAppointment() {
    int id;
    std::cout << "\n=== CANCEL APPOINTMENT ===\n";
    std::cout << "Enter Appointment ID to cancel: ";
    std::cin >> id;
    
    std::vector<Appointment> appointments = loadAllAppointments();
    bool found = false;
    
    for (auto& a : appointments) {
        if (a.getId() == id) {
            found = true;
            if (a.getStatus() == "cancelled") {
                std::cout << "Appointment is already cancelled.\n";
                return;
            }
            a.setStatus("cancelled");
            std::cout << "Appointment cancelled successfully!\n";
            break;
        }
    }
    
    if (found) {
        saveAllAppointments(appointments);
    } else {
        std::cout << "Appointment not found!\n";
    }
}

void Appointment::updateAppointment() {
    int id;
    std::cout << "\n=== UPDATE APPOINTMENT ===\n";
    std::cout << "Enter Appointment ID to update: ";
    std::cin >> id;
    
    std::vector<Appointment> appointments = loadAllAppointments();
    bool found = false;
    
    for (auto& a : appointments) {
        if (a.getId() == id) {
            found = true;
            std::cout << "\nCurrent Appointment Information:\n";
            a.displayDetailed();
            
            std::cin.ignore();
            std::cout << "\nEnter new Date (or press Enter to keep current): ";
            std::string date;
            std::getline(std::cin, date);
            if (!date.empty()) a.setDate(date);
            
            std::cout << "Enter new Time (or press Enter to keep current): ";
            std::string time;
            std::getline(std::cin, time);
            if (!time.empty()) a.setTime(time);
            
            std::cout << "Enter new Status (scheduled/completed/cancelled): ";
            std::string status;
            std::getline(std::cin, status);
            if (!status.empty()) a.setStatus(status);
            
            std::cout << "Enter new Description (or press Enter to keep current): ";
            std::string desc;
            std::getline(std::cin, desc);
            if (!desc.empty()) a.setDescription(desc);
            
            break;
        }
    }
    
    if (found) {
        saveAllAppointments(appointments);
        std::cout << "\nAppointment updated successfully!\n";
    } else {
        std::cout << "\nAppointment not found!\n";
    }
}

void Appointment::displayAllAppointments() {
    std::vector<Appointment> appointments = loadAllAppointments();
    
    if (appointments.empty()) {
        std::cout << "\nNo appointments found.\n";
        return;
    }
    
    std::cout << "\n=== ALL APPOINTMENTS ===\n";
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(10) << "PatientID" 
              << std::setw(10) << "DoctorID" 
              << std::setw(12) << "Date" 
              << std::setw(10) << "Time" 
              << std::setw(15) << "Status" << "\n";
    std::cout << std::string(62, '-') << "\n";
    
    for (const auto& a : appointments) {
        std::cout << std::left << std::setw(5) << a.getId()
                  << std::setw(10) << a.getPatientId()
                  << std::setw(10) << a.getDoctorId()
                  << std::setw(12) << a.getDate()
                  << std::setw(10) << a.getTime()
                  << std::setw(15) << a.getStatus() << "\n";
    }
    std::cout << "\n";
}

void Appointment::searchAppointment() {
    int id;
    std::cout << "\n=== SEARCH APPOINTMENT ===\n";
    std::cout << "Enter Appointment ID: ";
    std::cin >> id;
    
    Appointment appointment = findAppointmentById(id);
    if (appointment.getId() != 0) {
        std::cout << "\nAppointment Found:\n";
        appointment.displayDetailed();
    } else {
        std::cout << "\nAppointment not found!\n";
    }
}

Appointment Appointment::findAppointmentById(int id) {
    std::vector<Appointment> appointments = loadAllAppointments();
    for (const auto& a : appointments) {
        if (a.getId() == id) {
            return a;
        }
    }
    return Appointment();
}

std::vector<Appointment> Appointment::loadAllAppointments() {
    std::vector<Appointment> appointments;
    std::ifstream file(APPOINTMENT_FILE);
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
                int pid = std::stoi(tokens[1]);
                int did = std::stoi(tokens[2]);
                Appointment a(id, pid, did, tokens[3], tokens[4], tokens[5], tokens[6]);
                appointments.push_back(a);
            }
        }
        file.close();
    }
    return appointments;
}

void Appointment::saveAllAppointments(const std::vector<Appointment>& appointments) {
    std::ofstream file(APPOINTMENT_FILE);
    if (file.is_open()) {
        for (const auto& a : appointments) {
            file << a.getId() << "|" << a.getPatientId() << "|" << a.getDoctorId() << "|"
                 << a.getDate() << "|" << a.getTime() << "|" << a.getStatus() << "|"
                 << a.getDescription() << "\n";
        }
        file.close();
    }
}

void Appointment::display() const {
    std::cout << "ID: " << id << " | PatientID: " << patientId 
              << " | DoctorID: " << doctorId << " | Date: " << date 
              << " | Time: " << time << " | Status: " << status << "\n";
}

void Appointment::displayDetailed() const {
    Patient patient = Patient::findPatientById(patientId);
    Doctor doctor = Doctor::findDoctorById(doctorId);
    
    std::cout << "\n=== APPOINTMENT DETAILS ===\n";
    std::cout << "Appointment ID: " << id << "\n";
    std::cout << "Patient: " << patient.getName() << " (ID: " << patientId << ")\n";
    std::cout << "Doctor: " << doctor.getName() << " (ID: " << doctorId << ")\n";
    std::cout << "Date: " << date << "\n";
    std::cout << "Time: " << time << "\n";
    std::cout << "Status: " << status << "\n";
    std::cout << "Description: " << description << "\n";
}

