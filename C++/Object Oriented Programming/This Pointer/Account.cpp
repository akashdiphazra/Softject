#include "Account.h"

void Account::set_balance(double bal) { this->balance = bal; }
double Account::get_balance() { return balance; }
void Account::set_name(std::string n) { name = n; }
std::string Account::get_name() { return name; }
bool Account::deposit(double amount) {
  balance += amount;
  return true;
}
bool Account::withdraw(double amount) {
  if ((balance - amount) >= 0) {
    balance -= amount;
    return true;
  }
  return false;
}
