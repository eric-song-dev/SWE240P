/* ************************************************************************
> File Name:     Bank.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Tue Oct 21 16:19:39 2025
> Description:   
 ************************************************************************/

#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <unordered_set>
#include <vector>

struct Account {
    int id;
    std::string name;
    std::string address;
    std::string ssn;
    double balance;
    Account* next;

    Account(int id, std::string name, std::string address, std::string ssn, double balance, Account* next = nullptr)
        : id(id), name(name), address(address), ssn(ssn), balance(balance), next(next) {}
};

class Bank {
public:
    Bank();

    ~Bank();

    Account* addUser(std::string name, std::string address, std::string ssn, double initialDeposit);

    bool deleteUser(int id);

    bool payUserToUser(int payerID, int payeeID, double amount);

    double getMedianID() const;

    bool mergeAccounts(int id1, int id2);

    Account* findUser(int id) const;
    
    void printList() const;
    
    static Bank mergeBanks(Bank& bank1, Bank& bank2);


private:
    Account* dummyHead;
    std::stack<int> freeIDs;
    int nextAvailableID;

    int generateID();
    void recycleID(int id);

    void insertNode(Account* node);
};
