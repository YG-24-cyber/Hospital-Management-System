#include "User.h"
#include <algorithm>
#include <sstream>

const std::string User::USER_FILE = "users.txt";
std::string User::currentLoggedInUser = "";

User::User() : username(""), password(""), role("") {}

User::User(const std::string& uname, const std::string& pwd, const std::string& r) 
    : username(uname), password(pwd), role(r) {}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getRole() const { return role; }

void User::setUsername(const std::string& uname) { username = uname; }
void User::setPassword(const std::string& pwd) { password = pwd; }
void User::setRole(const std::string& r) { role = r; }

bool User::login(const std::string& username, const std::string& password) {
    std::ifstream file(USER_FILE);
    if (!file.is_open()) {
        std::cout << "User file not found. Please register first.\n";
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string uname, pwd, role;
        
        if (std::getline(iss, uname, '|') && 
            std::getline(iss, pwd, '|') && 
            std::getline(iss, role, '|')) {
            
            // Remove leading/trailing whitespace
            uname.erase(0, uname.find_first_not_of(" \t"));
            uname.erase(uname.find_last_not_of(" \t") + 1);
            pwd.erase(0, pwd.find_first_not_of(" \t"));
            pwd.erase(pwd.find_last_not_of(" \t") + 1);
            
            if (uname == username && pwd == password) {
                currentLoggedInUser = username;
                file.close();
                return true;
            }
        }
    }
    
    file.close();
    return false;
}

bool User::registerUser(const std::string& username, const std::string& password, const std::string& role) {
    // Check if user already exists
    std::ifstream file(USER_FILE);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string uname;
            if (std::getline(iss, uname, '|')) {
                uname.erase(0, uname.find_first_not_of(" \t"));
                uname.erase(uname.find_last_not_of(" \t") + 1);
                if (uname == username) {
                    file.close();
                    return false; // User already exists
                }
            }
        }
        file.close();
    }
    
    // Add new user
    std::ofstream outfile(USER_FILE, std::ios::app);
    if (!outfile.is_open()) {
        std::cout << "Error: Cannot open user file for writing.\n";
        return false;
    }
    
    outfile << username << "|" << password << "|" << role << "\n";
    outfile.close();
    return true;
}

void User::saveUserToFile(const User& user) {
    std::ofstream file(USER_FILE, std::ios::app);
    if (file.is_open()) {
        file << user.username << "|" << user.password << "|" << user.role << "\n";
        file.close();
    }
}

User User::loadUserFromFile(const std::string& username) {
    std::ifstream file(USER_FILE);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string uname, pwd, role;
            
            if (std::getline(iss, uname, '|') && 
                std::getline(iss, pwd, '|') && 
                std::getline(iss, role, '|')) {
                
                uname.erase(0, uname.find_first_not_of(" \t"));
                uname.erase(uname.find_last_not_of(" \t") + 1);
                
                if (uname == username) {
                    pwd.erase(0, pwd.find_first_not_of(" \t"));
                    pwd.erase(pwd.find_last_not_of(" \t") + 1);
                    role.erase(0, role.find_first_not_of(" \t"));
                    role.erase(role.find_last_not_of(" \t") + 1);
                    
                    file.close();
                    return User(uname, pwd, role);
                }
            }
        }
        file.close();
    }
    return User();
}

std::vector<User> User::loadAllUsers() {
    std::vector<User> users;
    std::ifstream file(USER_FILE);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string uname, pwd, role;
            
            if (std::getline(iss, uname, '|') && 
                std::getline(iss, pwd, '|') && 
                std::getline(iss, role, '|')) {
                
                uname.erase(0, uname.find_first_not_of(" \t"));
                uname.erase(uname.find_last_not_of(" \t") + 1);
                pwd.erase(0, pwd.find_first_not_of(" \t"));
                pwd.erase(pwd.find_last_not_of(" \t") + 1);
                role.erase(0, role.find_first_not_of(" \t"));
                role.erase(role.find_last_not_of(" \t") + 1);
                
                users.push_back(User(uname, pwd, role));
            }
        }
        file.close();
    }
    return users;
}

std::string User::getCurrentUserRole() {
    if (currentLoggedInUser.empty()) {
        return "";
    }
    
    User user = loadUserFromFile(currentLoggedInUser);
    return user.getRole();
}

void User::setCurrentUser(const std::string& username) {
    currentLoggedInUser = username;
}

void User::logout() {
    currentLoggedInUser = "";
}

