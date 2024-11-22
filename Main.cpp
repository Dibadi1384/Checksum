#include <iostream>
#include <string>
#include "File_Block.hpp"
#include "Disk.hpp"

int main(){
    Disk *D = new Disk();
    
    std::string  input;
    while (std::cin>>input){
        if (input == "NEW"){
            int N;
            int T;
            std::cin >> N >> T ;
            D->NEW(N,T);
        } 
        else if (input == "STORE"){
            int ID;
            char str[501];
            std::cin >> ID; 
            std::cin.ignore(); 
            std::cin.getline(str, 501); 
            D->STORE(ID, str);
        }
        else if (input == "SEARCH"){
            int ID;
            std::cin >> ID;
            D->SEARCH(ID);
        }
        else if (input == "DELETE"){
            int ID;
            std::cin >> ID;
            D->DELETE(ID);
        }
        else if (input == "CORRUPT"){
            int ID;
            char str[501];
            std::cin >> ID; 
            std::cin.ignore(); 
            std::cin.getline(str, 501); 
            D->CORRUPT(ID, str);
        }
        else if (input == "VALIDATE"){
            int ID;
            std::cin >> ID;
            D->VALIDATE(ID);
        }
        else if (input == "PRINT"){
            int i;
            std::cin >> i;
            D->PRINT(i);
        }
        else if (input == "EXIT"){
            D->EXIT();
        }
    }

    delete D;

    return 0;
}

