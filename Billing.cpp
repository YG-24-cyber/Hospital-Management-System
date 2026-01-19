#include "Billing.h"
#include "Appointment.h"
#include <algorithm>
#include <cmath>

const std::string Billing::BILLING_FILE = "bills.txt";

Billing::Billing()
    : id(0), patientId(0), appointmentId(0), consultationFee(0.0),
      medicineCost(0.0), testCost(0.0), totalAmount(0.0),
      paymentStatus("pending"), billingDate("") {}

Billing::Billing(int bid, int pid, int aid, double consult, double medicine,
                 double test, const std::string &status,
                 const std::string &date)
    : id(bid), patientId(pid), appointmentId(aid), consultationFee(consult),
      medicineCost(medicine), testCost(test), paymentStatus(status),
      billingDate(date) {
  calculateTotal();
}

int Billing::getId() const { return id; }
int Billing::getPatientId() const { return patientId; }
int Billing::getAppointmentId() const { return appointmentId; }
double Billing::getConsultationFee() const { return consultationFee; }
double Billing::getMedicineCost() const { return medicineCost; }
double Billing::getTestCost() const { return testCost; }
double Billing::getTotalAmount() const { return totalAmount; }
std::string Billing::getPaymentStatus() const { return paymentStatus; }
std::string Billing::getBillingDate() const { return billingDate; }

void Billing::setId(int bid) { id = bid; }
void Billing::setPatientId(int pid) { patientId = pid; }
void Billing::setAppointmentId(int aid) { appointmentId = aid; }
void Billing::setConsultationFee(double fee) {
  consultationFee = fee;
  calculateTotal();
}
void Billing::setMedicineCost(double cost) {
  medicineCost = cost;
  calculateTotal();
}
void Billing::setTestCost(double cost) {
  testCost = cost;
  calculateTotal();
}
void Billing::setPaymentStatus(const std::string &status) {
  paymentStatus = status;
}
void Billing::setBillingDate(const std::string &date) { billingDate = date; }

void Billing::calculateTotal() {
  totalAmount = consultationFee + medicineCost + testCost;
}

void Billing::generateBill() {
  Billing bill;
  std::vector<Billing> bills = loadAllBills();

  // Generate new ID
  int newId = 1;
  if (!bills.empty()) {
    int maxId = 0;
    for (const auto &b : bills) {
      if (b.getId() > maxId)
        maxId = b.getId();
    }
    newId = maxId + 1;
  }
  bill.setId(newId);

  std::cout << "\n=== GENERATE BILL ===\n";
  std::cout << "Bill ID: " << newId << "\n";

  // Display patients
  Patient::displayAllPatients();
  std::cout << "Enter Patient ID: ";
  std::cin >> bill.patientId;

  // Verify patient exists
  Patient patient = Patient::findPatientById(bill.patientId);
  if (patient.getId() == 0) {
    std::cout << "Invalid Patient ID!\n";
    return;
  }

  // Display appointments for this patient
  std::vector<Appointment> allAppointments = Appointment::loadAllAppointments();
  std::cout << "\nAppointments for this patient:\n";
  bool hasAppointments = false;
  for (const auto &apt : allAppointments) {
    if (apt.getPatientId() == bill.patientId) {
      apt.display();
      hasAppointments = true;
    }
  }

  if (hasAppointments) {
    std::cout << "Enter Appointment ID (or 0 if not applicable): ";
    std::cin >> bill.appointmentId;
  } else {
    bill.appointmentId = 0;
  }

  std::cout << "Enter Consultation Fee: $";
  std::cin >> bill.consultationFee;

  std::cout << "Enter Medicine Cost: $";
  std::cin >> bill.medicineCost;

  std::cout << "Enter Test Cost: $";
  std::cin >> bill.testCost;

  std::cin.ignore();
  std::cout << "Enter Billing Date (DD-MM-YYYY): ";
  std::getline(std::cin, bill.billingDate);

  bill.paymentStatus = "pending";
  bill.calculateTotal();

  bills.push_back(bill);
  saveAllBills(bills);

  std::cout << "\nBill generated successfully!\n";
  std::cout << "Total Amount: $" << std::fixed << std::setprecision(2)
            << bill.totalAmount << "\n";
}

void Billing::processPayment() {
  int id;
  std::cout << "\n=== PROCESS PAYMENT ===\n";
  std::cout << "Enter Bill ID: ";
  std::cin >> id;

  Billing bill = findBillById(id);
  if (bill.getId() == 0) {
    std::cout << "Bill not found!\n";
    return;
  }

  bill.displayInvoice();

  std::cout << "\nCurrent Payment Status: " << bill.getPaymentStatus() << "\n";
  std::cout << "Enter new Payment Status (paid/partial/pending): ";
  std::string status;
  std::cin.ignore();
  std::getline(std::cin, status);

  if (status == "paid" || status == "partial" || status == "pending") {
    std::vector<Billing> bills = loadAllBills();
    for (auto &b : bills) {
      if (b.getId() == id) {
        b.setPaymentStatus(status);
        break;
      }
    }
    saveAllBills(bills);
    std::cout << "\nPayment status updated successfully!\n";
  } else {
    std::cout << "Invalid status!\n";
  }
}

void Billing::displayAllBills() {
  std::vector<Billing> bills = loadAllBills();

  if (bills.empty()) {
    std::cout << "\nNo bills found.\n";
    return;
  }

  std::cout << "\n=== ALL BILLS ===\n";
  std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "PatientID"
            << std::setw(12) << "Total Amount" << std::setw(15)
            << "Payment Status" << std::setw(12) << "Date" << "\n";
  std::cout << std::string(54, '-') << "\n";

  for (const auto &b : bills) {
    std::cout << std::left << std::setw(5) << b.getId() << std::setw(10)
              << b.getPatientId() << std::fixed << std::setprecision(2)
              << std::setw(12) << b.getTotalAmount() << std::setw(15)
              << b.getPaymentStatus() << std::setw(12) << b.getBillingDate()
              << "\n";
  }
  std::cout << "\n";
}

void Billing::searchBill() {
  int id;
  std::cout << "\n=== SEARCH BILL ===\n";
  std::cout << "Enter Bill ID: ";
  std::cin >> id;

  Billing bill = findBillById(id);
  if (bill.getId() != 0) {
    std::cout << "\nBill Found:\n";
    bill.displayInvoice();
  } else {
    std::cout << "\nBill not found!\n";
  }
}

void Billing::generateInvoice(int billId) {
  Billing bill = findBillById(billId);
  if (bill.getId() != 0) {
    bill.displayInvoice();
  } else {
    std::cout << "Bill not found!\n";
  }
}

Billing Billing::findBillById(int id) {
  std::vector<Billing> bills = loadAllBills();
  for (const auto &b : bills) {
    if (b.getId() == id) {
      return b;
    }
  }
  return Billing();
}

std::vector<Billing> Billing::loadAllBills() {
  std::vector<Billing> bills;
  std::ifstream file(BILLING_FILE);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      if (line.empty())
        continue;

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
        int pid = std::stoi(tokens[1]);
        int aid = std::stoi(tokens[2]);
        double consult = std::stod(tokens[3]);
        double medicine = std::stod(tokens[4]);
        double test = std::stod(tokens[5]);
        std::string status = tokens[6];
        std::string date = tokens[7];

        Billing b(id, pid, aid, consult, medicine, test, status, date);
        bills.push_back(b);
      }
    }
    file.close();
  }
  return bills;
}

void Billing::saveAllBills(const std::vector<Billing> &bills) {
  std::ofstream file(BILLING_FILE);
  if (file.is_open()) {
    for (const auto &b : bills) {
      file << b.getId() << "|" << b.getPatientId() << "|"
           << b.getAppointmentId() << "|" << std::fixed << std::setprecision(2)
           << b.getConsultationFee() << "|" << b.getMedicineCost() << "|"
           << b.getTestCost() << "|" << b.getPaymentStatus() << "|"
           << b.getBillingDate() << "\n";
    }
    file.close();
  }
}

void Billing::display() const {
  std::cout << "Bill ID: " << id << " | PatientID: " << patientId
            << " | Total: $" << std::fixed << std::setprecision(2)
            << totalAmount << " | Status: " << paymentStatus << "\n";
}

void Billing::displayInvoice() const {
  Patient patient = Patient::findPatientById(patientId);

  std::cout << "\n";
  std::cout << "========================================\n";
  std::cout << "          HOSPITAL INVOICE\n";
  std::cout << "========================================\n";
  std::cout << "Bill ID: " << id << "\n";
  std::cout << "Billing Date: " << billingDate << "\n";
  std::cout << "----------------------------------------\n";
  std::cout << "Patient Information:\n";
  std::cout << "  Name: " << patient.getName() << "\n";
  std::cout << "  ID: " << patientId << "\n";
  std::cout << "  Phone: " << patient.getPhone() << "\n";
  std::cout << "----------------------------------------\n";
  std::cout << "Charges:\n";
  std::cout << "  Consultation Fee:     $" << std::fixed << std::setprecision(2)
            << std::setw(8) << consultationFee << "\n";
  std::cout << "  Medicine Cost:        $" << std::setw(8) << medicineCost
            << "\n";
  std::cout << "  Test Cost:            $" << std::setw(8) << testCost << "\n";
  std::cout << "----------------------------------------\n";
  std::cout << "  TOTAL AMOUNT:         $" << std::setw(8) << totalAmount
            << "\n";
  std::cout << "----------------------------------------\n";
  std::cout << "Payment Status: " << paymentStatus << "\n";
  std::cout << "========================================\n";
  std::cout << "\n";
}
