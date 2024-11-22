#ifndef _File_Block_HPP_
#define _File_Block_HPP_

#include <iostream>

class FileBlock {
  public:
    // Constructor
    FileBlock(int ID, int slot);

    // Destructor
    ~FileBlock();

    //Public variables
    int fileID;
    int slotNum;
    char payload[500]; 
    int checksum;
    bool stored; //to check wether the file has been stored and truly exists

    //Public Functions
    int calc_checksum();
    void read_charstring(char str[]);
};
#endif 