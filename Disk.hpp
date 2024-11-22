#ifndef _Disk_HPP_
#define _Disk_HPP_

#include <iostream>
#include <vector>
#include "File_Block.hpp"

class Disk {
  public:
    // Constructor
    Disk();

    // Destructor
    ~Disk();


    //public member functions
    void NEW(int N, int T);
    void STORE(int ID, char str[]);
    void SEARCH(int ID);
    void DELETE(int ID);
    void CORRUPT(int ID, char str[]);
    void VALIDATE(int ID);
    void PRINT(int i);
    void EXIT();



  private:
    //Private variables
    bool alrExists=false;
    int hash_type;
    int num;//total number of the slots in the hashtable
    int filledSlots;//for double hash only
    FileBlock** hashtable=nullptr; //table for double hash
    std::vector<std::vector<FileBlock*>> chaintable; //table for chaining
    //private functions
    int doublehash(int ID);
    int chaining(int ID);
};
#endif 

