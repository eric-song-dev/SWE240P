/* ************************************************************************
> File Name:     Bank.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Tue Oct 21 16:19:59 2025
> Description:   
 ************************************************************************/

#include "../include/Bank.h"

Bank::Bank() : nextAvailableID(1) {
    dummyHead = new Account(-1, "DUMMY_HEAD", "", "", 0.0);
}

// Time: O(N), where N is the number of accounts
// Space: O(1)
Bank::~Bank() {
    Account* current = dummyHead->next;
    while (current != nullptr) {
        Account* temp = current;
        current = current->next;
        delete temp;
    }
    delete dummyHead;
}

// Time: O(1)
// Space: O(1)
int Bank::generateID() {
    if (!freeIDs.empty()) {
        int id = freeIDs.top();
        freeIDs.pop();
        return id;
    } else {
        return nextAvailableID++;
    }
}

// Time: O(1)
// Space: O(1)
void Bank::recycleID(int id) {
    freeIDs.push(id);
}

// Time: O(N), where N is the number of accounts (worst-case insertion at the end)
// Space: O(1)
void Bank::insertNode(Account* node) {
    Account* curr = dummyHead;
    
    while (curr->next != nullptr && curr->next->id < node->id) {
        curr = curr->next;
    }
    
    node->next = curr->next;
    curr->next = node;

    nextAvailableID = std::max(nextAvailableID, node->id + 1);
}

// Time: O(N) (dominated by insertNode)
// Space: O(1)
Account* Bank::addUser(std::string name, std::string address, std::string ssn, double initialDeposit) {
    int id = generateID();
    Account* newUser = new Account(id, name, address, ssn, initialDeposit);
    insertNode(newUser);
    return newUser;
}

// Time: O(N), where N is the number of accounts (worst-case finding the user)
// Space: O(1)
bool Bank::deleteUser(int id) {
    Account* prev = dummyHead;
    Account* curr = dummyHead->next;

    while (curr != nullptr && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        // user not found
        return false;
    }

    prev->next = curr->next;

    recycleID(curr->id);
    delete curr;
    return true;
}

// Time: O(N) (dominated by two findUser calls)
// Space: O(1)
bool Bank::payUserToUser(int payerID, int payeeID, double amount) {
    if (amount <= 0) {
        // invalid transfer amount
        return false;
    }
    
    Account* payer = findUser(payerID);
    Account* payee = findUser(payeeID);

    if (payer == nullptr || payee == nullptr) {
        // payer or payee not found
        return false;
    }

    if (payer->balance < amount) {
        // insufficient funds
        return false;
    }

    payer->balance -= amount;
    payee->balance += amount;
    return true;
}

// Time: O(N)
// Space: O(1)
double Bank::getMedianID() const {
    if (dummyHead->next == nullptr) {
        // bank is empty
        throw std::runtime_error("Bank is empty, cannot calculate median.");
    }

    Account *prevSlow = dummyHead;
    Account *slow = dummyHead->next;
    Account *fast = dummyHead->next;

    while (fast != nullptr && fast->next != nullptr) {
        prevSlow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast != nullptr) {
        // odd number of elements
        return static_cast<double>(slow->id);
    } else {
        // even number of elements
        return (static_cast<double>(prevSlow->id) + static_cast<double>(slow->id)) / 2.0;
    }
}

// Time: O(N) (dominated by two findUser and one deleteUser)
// Space: O(1)
bool Bank::mergeAccounts(int id1, int id2) {
    Account* acc1 = findUser(id1);
    Account* acc2 = findUser(id2);

    if (acc1 == nullptr || acc2 == nullptr) {
        // one or both accounts not found
        return false;
    }

    if (acc1->name == acc2->name &&
        acc1->address == acc2->address &&
        acc1->ssn == acc2->ssn) {
        
        Account* keepAcc = (acc1->id < acc2->id) ? acc1 : acc2;
        Account* delAcc = (acc1->id > acc2->id) ? acc1 : acc2;

        keepAcc->balance += delAcc->balance;
        
        return deleteUser(delAcc->id);
    }
    
    // account details do not match
    return false;
}

// Time: O(N) (worst-case linear scan)
// Space: O(1)
Account* Bank::findUser(int id) const {
    Account* current = dummyHead->next;
    while (current != nullptr) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    // user not found
    return nullptr;
}

void Bank::printList() const {
    std::cout << "--- Bank Account List ---" << std::endl;
    if (dummyHead->next == nullptr) {
        std::cout << "[Empty]" << std::endl;
        return;
    }
    std::cout << std::left;
    std::cout << std::setw(5) << "ID"
              << std::setw(15) << "Name"
              << std::setw(20) << "Address"
              << std::setw(15) << "SSN"
              << "Balance" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    
    Account* current = dummyHead->next; // start from the first real node
    while (current != nullptr) {
        std::cout << std::setw(5) << current->id
                  << std::setw(15) << current->name
                  << std::setw(20) << current->address
                  << std::setw(15) << current->ssn
                  << "$" << current->balance << std::endl;
        current = current->next;
    }
    std::cout << "---------------------------------------------------------------" << std::endl;
}

// Time: O((N+M)^2), where N is size of bank1, M is size of bank2
//       (due to O(k) insertion time of insertNode for k=1..N+M)
// Space: O(N+M) (for the new list, the unordered_set, and the vector)
Bank Bank::mergeBanks(Bank& bank1, Bank& bank2) {
    Bank newBank;
    
    std::unordered_set<int> existingIDs;

    // O(N^2) because each insertNode takes O(k)
    for (Account* account = bank1.dummyHead->next; account != nullptr; account = account->next) {
        auto newNode = new Account(account->id, account->name, account->address, account->ssn, account->balance);
        newBank.insertNode(newNode);
        existingIDs.insert(account->id);
    }

    std::vector<Account*> conflictAccounts;

    // O(M * (N+M)) because each insertNode takes O(N+k)
    for (Account* account = bank2.dummyHead->next; account != nullptr; account = account->next) {
        if (existingIDs.count(account->id) == 0) {
            auto newNode = new Account(account->id, account->name, account->address, account->ssn, account->balance);
            newBank.insertNode(newNode);
            existingIDs.insert(account->id);
        } else {
            conflictAccounts.push_back(account);
        }
    }

    // O(M * (N+M)) in worst case (all accounts conflict)
    for (Account* originalAccount : conflictAccounts) {
        int newID = newBank.generateID();
        auto newNode = new Account(newID, originalAccount->name, originalAccount->address, originalAccount->ssn, originalAccount->balance);
        newBank.insertNode(newNode);
        existingIDs.insert(newID);
    }

    return newBank;
}
