#include "hashtable.h"
#include <fstream>
#include <iomanip>

Record::Record() : id(0), value("") {
  // Default constructor has an id of 0 and an empty string for value                                                                                                                                                                                                                                       
}

Record::Record(std::string line) {
  size_t posOfSpace = line.find(' ');
  if (posOfSpace != std::string::npos) {
    id = std::stoi(line.substr(0, posOfSpace));
    value = line.substr(posOfSpace + 1);
  } else {
    id = std::stoi(line);
    value = "";
  }
}

Record* Record::clone() {
  Record* clone = new Record;
  clone->id = id;
  clone->value = value;
  return clone;
}

HashTable::HashTable(int size) : m(size), c((std::sqrt(5) - 1) / 2) {
  A = new std::vector<Record>[m];
}

void HashTable::insert(Record *rec) {
  int index = hash(rec);
  A[index].push_back(*rec);
}

Record* HashTable::del(int key) {
  if (find(key) == -1) return nullptr;
  int i = find(key);
  int index = hash(key);
  Record* deletedRec = A[index][i].clone();
  A[index].erase(A[index].begin() + i);
  return deletedRec;
}

Record* HashTable::search(int key) {
  int i = find(key);
  if (i == -1) return nullptr;
  int index = hash(key);
  return &A[index][i];  // Return the record at the found position                                                                                                                                                                                                                                          
}

int HashTable::find(int key) {
  int index = hash(key);
  for (int i = 0; i < A[index].size(); i++) {
    if (A[index][i].getID() == key) {
      return i;
    }
  }
  return -1;
}

int HashTable::hash(Record *rec) {
  int id = rec->getID();
  return hash(id);
}

int HashTable::hash(int k) {
  return static_cast<int>(m * (k * c - static_cast<int>(k * c)));
}

void HashTable::write(std::string filename) {
  std::ofstream newFile;
  newFile.open(filename);
  for (int i = 0; i < m; i++) {
    for (const Record &rec : A[i]) {
      newFile << std::setw(9) << std::setfill('0') << rec.getID();
      newFile << " " << rec.getValue() << std::endl;
    }
  }
  newFile.close();
}

void HashTable::read(std::string filename) {
  std::ifstream oldFile;
  oldFile.open(filename);
  if (oldFile.fail()) return;  // There was no file with the given name                                                                                                                                                                                                                                     
  std::string nextLine;
  while (std::getline(oldFile, nextLine)) {
    Record* rec = new Record(nextLine);
    insert(rec);
    delete rec;
  }
}

void HashTable::clear() {
  delete[] A;  // Delete the array completely, and...                                                                                                                                                                                                                                                       
  A =  new std::vector<Record>[m];  // Create a new one of the same size                                                                                                                                                                                                                                    
}

HashTable::~HashTable() {
  delete[] A;
}
