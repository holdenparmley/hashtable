#include "hashtable.h"
#include <iostream>
#include <iomanip>

void readFile(HashTable& hashtable) {
  std::cout << "read hash table - filename? ";
  std::string fileName;
  std::getline(std::cin, fileName);
  hashtable.read(fileName);
}

void insertRecord(HashTable& hashtable) {
  std::cout << "input new record:" << std::endl;
  std::string newEntry;
  std::getline(std::cin, newEntry);
  Record* newRecord = new Record(newEntry);
  hashtable.insert(newRecord);
  delete newRecord;
}

void deleteRecord(HashTable& hashtable) {
  std::cout << "delete record - key? ";
  std::string keyStr;
  std::getline(std::cin, keyStr);
  int key = std::stoi(keyStr);
  Record* deletedRec = hashtable.del(key);
  if (deletedRec == nullptr) {
    std::cout << "Delete not found: ";
    std::cout << std::setw(9) << std::setfill('0') << keyStr << std::endl;
  } else {
    std::cout << "Delete: ";
    std::cout << std::setw(9) << std::setfill('0') << deletedRec->getID();
    std::cout << " " << deletedRec->getValue() << std::endl;
    delete deletedRec;
  }
}

void searchForRecord(HashTable& hashtable) {
  std::cout << "search for record - key? ";
  std::string keyStr;
  std::getline(std::cin, keyStr);
  int key = std::stoi(keyStr);
  Record* foundRec = hashtable.search(key);
  if (foundRec == nullptr) {
    std::cout << "Search not found: ";
    std::cout << std::setw(9) << std::setfill('0') << keyStr << std::endl;
  } else {
    std::cout << "Found: ";
    std::cout << std::setw(9) << std::setfill('0') << foundRec->getID();
    std::cout << " " << foundRec->getValue() << std::endl;
  }
}

void writeFile(HashTable& hashtable) {
  std::cout << "write hash table - filename? ";
  std::string fileName;
  std::getline(std::cin, fileName);
  hashtable.write(fileName);
}

int main() {
  HashTable hashtable(178000);
  std::string line;
  while (std::cin) {
    std::cout << "(1)load (2)insert (3)delete (4)search (5)clear (6)save "
              << "(7)quit -- Your choice? ";
    std::getline(std::cin, line);
    if (line == "1") readFile(hashtable);
    if (line == "2") insertRecord(hashtable);
    if (line == "3") deleteRecord(hashtable);
    if (line == "4") searchForRecord(hashtable);
    if (line == "5") {
      std::cout << "clearing hash table." << std::endl;
      hashtable.clear();
    }
    if (line == "6") writeFile(hashtable);
    if (line == "7") return 0;
  }
}
