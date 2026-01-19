#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * UML Class Diagram - User
 * +------------------+
 * |      User        |
 * +------------------+
 * | - username       |
 * | - password       |
 * | - role           |
 * +------------------+
 * | + login()        |
 * | + logout()       |
 * | + register()     |
 * | + authenticate() |
 * +------------------+
 */

class User {
private:
  std::string username;
  std::string password;
  std::string role; // "admin", "doctor", "patient"

public:
  User();
  User(const std::string &uname, const std::string &pwd, const std::string &r);

  // Getters
  std::string getUsername() const;
  std::string getPassword() const;
  std::string getRole() const;

  // Setters
  void setUsername(const std::string &uname);
  void setPassword(const std::string &pwd);
  void setRole(const std::string &r);

  // Authentication methods
  static bool login(const std::string &username, const std::string &password);
  static bool registerUser(const std::string &username,
                           const std::string &password,
                           const std::string &role);
  static void saveUserToFile(const User &user);
  static User loadUserFromFile(const std::string &username);
  static std::vector<User> loadAllUsers();
  static std::string getCurrentUserRole();
  static void setCurrentUser(const std::string &username);
  static void logout();

  // File operations
  static const std::string USER_FILE;
  static std::string currentLoggedInUser;
};

#endif
