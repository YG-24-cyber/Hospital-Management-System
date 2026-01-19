#ifndef BILLING_H
#define BILLING_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Patient.h"

/**
 * UML Class Diagram - Billing
 * +------------------+
 * |     Billing      |
 * +------------------+
 * | - id             |
 * | - patientId      |
 * | - appointmentId  |
 * | - consultationFee|
 * | - medicineCost   |
 * | - testCost       |
 * | - totalAmount    |
 * | - paymentStatus  |
 * | - billingDate    |
 * +------------------+
 * | + calculateBill()|
 * | + generateInvoice()|
 * | + processPayment()|
 * | + displayBill()  |
 * +------------------+
 */

class Billing {
private:
    int id;
    int patientId;
    int appointmentId;
    double consultationFee;
    double medicineCost;
    double testCost;
    double totalAmount;
    std::string paymentStatus; // "pending", "paid", "partial"
    std::string billingDate;

public:
    Billing();
    Billing(int bid, int pid, int aid, double consult, double medicine, 
            double test, const std::string& status, const std::string& date);
    
    // Getters
    int getId() const;
    int getPatientId() const;
    int getAppointmentId() const;
    double getConsultationFee() const;
    double getMedicineCost() const;
    double getTestCost() const;
    double getTotalAmount() const;
    std::string getPaymentStatus() const;
    std::string getBillingDate() const;
    
    // Setters
    void setId(int bid);
    void setPatientId(int pid);
    void setAppointmentId(int aid);
    void setConsultationFee(double fee);
    void setMedicineCost(double cost);
    void setTestCost(double cost);
    void setPaymentStatus(const std::string& status);
    void setBillingDate(const std::string& date);
    
    // Operations
    void calculateTotal();
    static void generateBill();
    static void processPayment();
    static void displayAllBills();
    static void searchBill();
    static void generateInvoice(int billId);
    static Billing findBillById(int id);
    static std::vector<Billing> loadAllBills();
    static void saveAllBills(const std::vector<Billing>& bills);
    
    // Display
    void display() const;
    void displayInvoice() const;
    
    // File operations
    static const std::string BILLING_FILE;
};

#endif

