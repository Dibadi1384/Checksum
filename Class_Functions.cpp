#include <iostream>
#include <string>
#include "File_Block.hpp"
#include "Disk.hpp"
#include <vector>



// ///////////////DISK
// Disk::Disk(){}


// // Destructor
// Disk::~Disk(){


//     //deleting items from doublehashing table
//     if(hash_type==0){
//         for(int i=0; i<num; i++){
//         delete hashtable[i];  
//         hashtable[i] = nullptr;
//         }
//         delete[] hashtable;
//         hashtable = nullptr;
//     }


//     //deleting items from chained list
//     else if(hash_type==1){
//       for (int i = 0; i < num; i++) {
//             // Delete each FileBlock in the chain
//             for (FileBlock* block : chaintable[i]) {
//                 delete block; // Free each allocated FileBlock
//             }
//             chaintable[i].clear(); // Clear the vector to remove all pointers
//         }
//     }
 
// }

// void Disk::NEW(int N, int T){
//     hash_type=T;
//     num=N;
   
//     //table for doublehashing
//     if(hash_type==0){
//         hashtable= new FileBlock*[N];
//         for (int i = 0; i < N; ++i) {
//             hashtable[i] = nullptr;
//         }
//         filledSlots=0;//set the table to be empty
//         std::cout<<"success"<<std::endl;
//     }
 
//     //table for chaining
//     if(hash_type==1){    
//         chaintable.resize(N);
//         std::cout<<"success"<<std::endl;
//     }
// }


// //runtime has to be o(1)
// void Disk::STORE(int ID, char str[]){  
//     //doublehashing
//     if(hash_type==0){
//         int slot=doublehash(ID);
       
//         //first check if the table was full or not
//         if(filledSlots==num){
//             std::cout<<"failure"<<std::endl;
//         }

//         //insert if table not full and key is not already there, or the key before was deleted
//         else if((slot<num && alrExists==false) || (alrExists==true && empty==true )){//empty==true incase another function was called before store
//             //store file in the free slot in table using index found by double hashing
//             hashtable[slot]->read_charstring(str);
//             hashtable[slot]->checksum=hashtable[slot]->calc_checksum();//update checksum
//             filledSlots+=1; //update size
//             empty=false;
//             std::cout<<"success"<<std::endl;
//         }

//         //if table is full and file could not be inserted OR key alr exists
//         else{
//             empty=true;
//             std::cout<<"failure"<<std::endl;
//         }
//     }


//     //chaining
//     else if(hash_type==1){
//         int chainindex=chaining(ID);
//         int h=ID%num;
       
//         //store file in the free slot in table using index found by double hashing
//         if(alrExists==false ||  (alrExists==true && empty==true)){//empty==true incase another function was called before store
//             chaintable[h][chainindex]->read_charstring(str);
//             chaintable[h][chainindex]->checksum=chaintable[h][chainindex]->calc_checksum();//update checksum
//             empty=false;
//             std::cout<<"success"<<std::endl;
//         }

//         //if file already existed
//         else{
//             empty=true;
//             std::cout<<"failure"<<std::endl;
//         }


//     }
       
// }


// void Disk::SEARCH(int ID){
//     //doublehashing
//     if(hash_type==0){
//         int slot=doublehash(ID);
       
//         //return the slot number if key exists
//         if(alrExists==true){
//             std::cout<<"found "<<ID<<" in "<<slot<<std::endl;
//         }
//         //if key doesnt exist
//         else{
//             empty=true;
//             std::cout<<"not found"<<std::endl;
//         }
//     }


//     //chaining
//     else if(hash_type==1){
//         int chainindex=chaining(ID);
//         int h=ID%num;


//         //return the index of the chain that key is in
//         if(alrExists==true){
//             std::cout<<"found "<<ID<<" in "<<h<<std::endl;
//         }
//         //if key doesnt exist
//         else{
//             empty=true;
//             std::cout<<"not found"<<std::endl;
//         }
//     }
// }


// //o(1)
// void Disk::DELETE(int ID){
//     //doublehashing
//     if(hash_type==0){
//         int slot=doublehash(ID);
       
//         //if key exists
//         if(alrExists==true && empty==false){
//             hashtable[slot]=NULL;
//             filledSlots-=1;//update size
//             std::cout<<"success"<<std::endl;
//         }
       
//         //if key doesnt exist
//         else{
//             std::cout<<"failure"<<std::endl;
//         }
//     }


//     //chaining
//     else if(hash_type==1){
//         int chainindex=chaining(ID);
//         int h=ID%num;


//         //if key exists
//         if(alrExists==true && empty==false){
//             chaintable[h].erase(chaintable[h].begin()+chainindex);
//             std::cout<<"success"<<std::endl;
//         }


//         //if key doesnt exist
//         else{
//             std::cout<<"failure"<<std::endl;
//         }
//     }
//     empty=true;//can be called here since it applies to all cases
// }


// void Disk::CORRUPT(int ID, char str[]){
//     //doublehashing
//     if(hash_type==0){
//         int slot=doublehash(ID);
       
//         //rewrite the payload if file exists
//         if(alrExists==true){
//             hashtable[slot]->read_charstring(str);
//             std::cout<<"success"<<std::endl;
//         }
//         //if key doesnt exist
//         else{
//             empty=true;
//             std::cout<<"failure"<<std::endl;
//         }
//     }


//     //chaining
//     else if(hash_type==1){
//         int chainindex=chaining(ID);
//         int h=ID%num;


//         //rewrite the payload if file exists
//         if(alrExists==true){
//             chaintable[h][chainindex]->read_charstring(str);
//             std::cout<<"success"<<std::endl;
//         }


//         //if key doesnt exist
//         else{
//             empty=true;
//             std::cout<<"failure"<<std::endl;
//         }    
//     }
// }


// void Disk::VALIDATE(int ID){
//     if(hash_type==0){
//         int slot=doublehash(ID);
       
//         //validate if key exists
//         if(alrExists==true){
//             //if new checksum matches old one
//             int newchecksum=hashtable[slot]->calc_checksum();
//             if(hashtable[slot]->checksum==newchecksum){
//                 std::cout<<"valid"<<std::endl;
//                 return;
//             }

//             //if file was corrupted
//             std::cout<<"invalid"<<std::endl;
//         }
//         //if key doesnt exist
//         else{
//             empty=true;
//             std::cout<<"failure"<<std::endl;
//         }
//     }


//     //chaining
//     else if(hash_type==1){
//         int chainindex=chaining(ID);
//         int h=ID%num;


//          //validate if key exists
//         if(alrExists==true){
//             //if new checksum matches old one
//             int newchecksum=chaintable[h][chainindex]->calc_checksum();
//             if(chaintable[h][chainindex]->checksum==newchecksum){
//                 std::cout<<"valid"<<std::endl;
//                 return;
//             }
//             //if file was corrupted
//             std::cout<<"invalid"<<std::endl;
//         }
//         //if key doesnt exist
//         else{
//             empty=true;
//             std::cout<<"failure"<<std::endl;
//         }   
//     }
// }


// void Disk::PRINT(int i){
//     if(chaintable[i].size()==0){
//         std::cout<<"chain is empty"<<std::endl;
//         return;
//     }


//     int j=0;
//     while(j<chaintable[i].size()){
//         std::cout<<chaintable[i][j]->fileID<<" ";
//         j++;
//     }
//     std::cout<<std::endl;
// }


// void Disk::EXIT(){}

// int Disk::doublehash(int ID){
//     //primarly hash funtion
//     int h1=ID%num;


//     //secondary hash funtion
//     int h2=(int(ID/num))%num;


//     if (h2%2==0){
//         h2+=1;
//     }


//     //hashfunction - linear probe starts w 0
//     int i=0;
//     int h=(h1+h2*i)%num;


//     //while the hashnumeber is within the bound, double hash to find empty slot
//     while(h<num && hashtable[h]!=NULL){
//         //check if key already exists
//         if(hashtable[h]->fileID==ID && empty==false){
//             alrExists=true;
//             return h;
//         }    


//         //check if table is full
//         if(filledSlots==num){
//             alrExists=false;
//             return h;
//         }
       
//         i++;
//         h=(h1+h2*i)%num;
//     }


//     alrExists=false;
//     hashtable[h]=new FileBlock(ID, h);
//     return h;
// }


// int Disk::chaining(int ID){
//     int h=ID%num;
//     int i=0;


//     //insert first file
//     if(chaintable[h].size() == 0){
//         chaintable[h].push_back(new FileBlock(ID, h));
//     }
 
//     //instert other files
//     else{
//         while(i < chaintable[h].size() && chaintable[h][i]->fileID<ID){
//             i++;
//         }
       
//         if(i < chaintable[h].size() && chaintable[h][i]->fileID == ID && empty==false){
//             alrExists=true;
//             return i; //index of key is i
//         }
       
//         chaintable[h].insert(chaintable[h].begin() + i, new FileBlock(ID, h));
//     }
    
//     alrExists=false;
//     return i;
// }

// ///////////////FILEBLOCK
// FileBlock::FileBlock(int ID, int slot){
//     fileID=ID;
//     slotNum=slot;
//     std::fill(std::begin(payload), std::end(payload), 0);
// }


// FileBlock::~FileBlock(){}


// int  FileBlock::calc_checksum(){
//     int sum=0;
//     for(int i=0; i<500; i++){
//         sum+= payload[i];
//     }
//     return sum%256;
// }


// void FileBlock::read_charstring(char str[]){
//     int i=0;
//     std::fill(std::begin(payload), std::end(payload), 0);
//     while (str[i]!='!' && i < 500){
//         payload[i]=str[i];
//         i++;
//     }
// }

