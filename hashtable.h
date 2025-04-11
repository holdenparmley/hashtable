#include <cmath>
#include <vector>
#include <string>

class Record{
public:
  Record();  // Default constructor                                                                                             
  Record(std::string);  // Constructor from a string                                                                            
  int getID() const { return id; };
  std::string getValue() const { return value; };
  Record* clone();  // Invokes copy constructor                                                                                 
private:
  int id;
  std::string value;
};

class HashTable{
public:
  HashTable(int size=100);  // Default size is 100                                                                              
  ~HashTable();
  void insert(Record* rec);  // Insert a copy of a record                                                                       
  Record* del(int);  // Delete a record                                                                                         
  Record* search(int);  // Return the record if it is found, or nullptr                                                         
  void write(std::string);  // Write out to another file                                                                        
  void read(std::string);  // Read from another file                                                                            
  void clear(); // Clear the hashtable                                                                                          
private:
  int find(int);  // Finds the index of a value within its spot in the array                                                    
  int hash(Record* rec);  // Record hash value                                                                                  
  int hash(int);  // Key hash value                                                                                             
  const int m;  // Size of table                                                                                                
  const double c;
  std::vector<Record>* A;
};
