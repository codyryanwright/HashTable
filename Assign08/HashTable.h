#ifndef HASH_TABLE
#define HASH_TABLE

#include <cstdlib>  // for use of size_t
#include <iostream> // for use of ostream
#include <string>   // for use of string

class HashTable
{
public:
   typedef size_t size_type;
   static const size_type INIT_CAP = 101;
   // default | 1-argument constructor
   HashTable(size_type initial_capacity = INIT_CAP);
   ~HashTable();
   size_type cap() const;
   size_type size() const;
   bool exists(const std::string& sWord) const;
   bool search(const std::string& sWord) const;
   double load_factor() const;
   void scat_plot(std::ostream& out) const;
   void grading_helper_print(std::ostream& out) const;
   void insert(const std::string& sWord);
private:
   struct Item
   {
      std::string word;  // word as string
   };
   Item* data;
   size_type capacity; // hash table capacity
   size_type used;     // # of hash table elements used (non-vacant)
   size_type hash(const std::string& word) const;
   void rehash();

   // disable copy construction & copy assignment
   HashTable(const HashTable& src) { }
   void operator=(const HashTable& rhs) { }
};

// non-member utility functions
bool is_prime(HashTable::size_type num);
HashTable::size_type next_prime(HashTable::size_type x);

#endif
