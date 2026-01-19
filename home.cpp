#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Account
{
    int id;
    string name;
    int pin;
    double balance;
};

// Save accounts to file
void saveAccounts(const vector<Account> &accounts)
{
    ofstream file("accounts.txt");
    for (auto &acc : accounts)
    {
        file << acc.id << " " << acc.name << " " << acc.pin << " " << acc.balance << endl;
    }
    file.close();
}

// Load accounts from file
vector<Account> loadAccounts()
{
    vector<Account> accounts;
    ifstream file("accounts.txt");
    Account acc;
    while (file >> acc.id >> acc.name >> acc.pin >> acc.balance)
    {
        accounts.push_back(acc);
    }
    file.close();
    return accounts;
}

// Find account by ID
int findAccount(const vector<Account> &accounts, int id, int pin)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].id == id && accounts[i].pin == pin)
            return i;
    }
    return -1;
}

int main()
{
    vector<Account> accounts = loadAccounts();
    int choice;

    do
    {
        cout << "\n===== ATM Banking System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Account acc;
            cout << "Enter ID: ";
            cin >> acc.id;
            cout << "Enter Name: ";
            cin >> acc.name;
            cout << "Set PIN: ";
            cin >> acc.pin;
            acc.balance = 0;
            accounts.push_back(acc);
            saveAccounts(accounts);
            cout << "Account created successfully!\n";
        }
        else if (choice == 2)
        {
            int id, pin;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter PIN: ";
            cin >> pin;
            int index = findAccount(accounts, id, pin);

            if (index == -1)
            {
                cout << "Invalid login!\n";
            }
            else
            {
                int subChoice;
                do
                {
                    cout << "\nWelcome, " << accounts[index].name << "!\n";
                    cout << "1. Deposit\n";
                    cout << "2. Withdraw\n";
                    cout << "3. Check Balance\n";
                    cout << "4. Logout\n";
                    cout << "Enter choice: ";
                    cin >> subChoice;

                    if (subChoice == 1)
                    {
                        double amt;
                        cout << "Enter amount to deposit: ";
                        cin >> amt;
                        accounts[index].balance += amt;
                        saveAccounts(accounts);
                        cout << "Deposit successful!\n";
                    }
                    else if (subChoice == 2)
                    {
                        double amt;
                        cout << "Enter amount to withdraw: ";
                        cin >> amt;
                        if (amt > accounts[index].balance)
                        {
                            cout << "Insufficient balance!\n";
                        }
                        else
                        {
                            accounts[index].balance -= amt;
                            saveAccounts(accounts);
                            cout << "Withdrawal successful!\n";
                        }
                    }
                    else if (subChoice == 3)
                    {
                        cout << "Current Balance: " << accounts[index].balance << endl;
                    }
                } while (subChoice != 4);
            }
        }
    } while (choice != 3);

    cout << "Thank you for using ATM System!\n";
    return 0;
}