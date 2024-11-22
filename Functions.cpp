#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Node.hpp"
#include "Functions.hpp"
#include "Illegal_exception.hpp"
#include "ece250_socket.h"


//Global Variables
Node *root=new Node("root"); //the root node yummyyy
int numClassifications=0;//for o(1) size yummyyyy 

void LOAD(const std::string& filename) {

    //read each line from the texfile
    std::ifstream file(filename);
    std::string classification;

    while (std::getline(file, classification)) {

        //read each class in the line
        std::stringstream ss(classification);
        std::string Class;
        Node* currentNode = root; //assign the current node to root

        while (std::getline(ss, Class, ',')) {

            bool classFound = false;
            for (auto& child : currentNode->Children) { //check if class already exists as a child of current node
                if (child.first == Class) {
                    currentNode = child.second; //update current node, traverse to next level of trie
                    classFound = true; 
                    break;
                }
            }

            //if class was not in trie, insert it at the currect level, traverse to the next level of trie
            if (!classFound) {
                Node* newNode = new Node(Class);
                currentNode->Children.push_back({Class, newNode});
                currentNode = newNode;
            }            
        }

        numClassifications+=1;   //update num classifications
    }

    std::cout<<"success"<<std::endl;
}

void INSERT(const std::string& classification) {
    try {
        std::stringstream ss(classification);
        std::string Class;

        Node* currentNode = root;
        int pathlen = 0; //number of the classes that already exists in classification path
        int numclasses = 0; //total number of classes in given classfifcation

        //parse through each class in the classification path
        while (std::getline(ss, Class, ',')) {
            //check for illegal_exceptions
            for (char c : Class) {
                if (std::isupper(c)) {
                    throw illegal_exception();  //throw an exception if uppercase is found
                }
            }

            //if no expetions, continue with the trie traversal 
            bool classFound = false;
            numclasses += 1; //increment the number of classes in given classification

            for (auto& child : currentNode->Children) { //check if class already exists as a child of current node
                if (child.first == Class) { 
                    currentNode = child.second; //update current node, traverse to next level of trie
                    classFound = true;
                    pathlen += 1; //increment the number of classes already existing in the path
                }
            }


            //if class was not in trie, insert it at the currect level, traverse to the next level of trie
            if (!classFound) {
                Node* newNode = new Node(Class);
                currentNode->Children.push_back({Class, newNode});
                currentNode = newNode;
            }         
        }

        //if classification already existed, number of existing classes==number of given classes
        if (pathlen == numclasses) {
            std::cout << "failure" << std::endl;
            return;
        }

        //otherwise, the classification was inserted
        //overally, the total number of classification is the total number of leaves(terminal )
      
        numClassifications+=1;    //update num classifications
        std::cout << "success" << std::endl;
    }
    
    //if an illegal_excpetion was found
    catch (const illegal_exception& e) {
        std::cout <<"illegal argument"<< std::endl; 
    }
}

void CLASSIFY(const std::string& input){
    std::string path;
    try {
        //check for illegal_exceptions
        for (char c : input) {
            if (std::isupper(c)) {
                throw illegal_exception();  //throw an exception if uppercase is found
            }
        }

        //traversing the trie
        Node* currentNode = root;

        //if tree is empty
        if(currentNode->Children.empty()){
            std::cout<<"failure"<<std::endl;
            return;
        }

       //else
        while (!currentNode->Children.empty()) {
            std::string candidate_labels;

            //make a string of all candidate classes in that level
            for (auto& child : currentNode->Children) { 
                if(!candidate_labels.empty()){
                    candidate_labels += "," + child.first;
                }
                else{
                    candidate_labels += child.first;
                }
                std::cout<<candidate_labels <<std::endl;
            }

            //call classify for that level
            std::string classNode = labelText(input, candidate_labels);

            //update current node based on the returned classification
            for (auto& child : currentNode->Children) {
                if (child.first == classNode) {
                    if(!path.empty()){
                        path+=","+child.first; 
                    }
                    else{
                        path+=child.first;
                    }
                    currentNode = child.second; //updates current node
                    break;
                }
                else{
                    std::cout<<path<<std::endl;      
                    return;
                }
            }
            
        }
        std::cout<<path<<std::endl;      
    }

    //if an illegal_excpetion was found
    catch (const illegal_exception& e) {
        std::cout <<"illegal argument" << std::endl;
    }
}

void ERASE(const std::string& classification){
     try {
        std::stringstream ss(classification);
        std::string Class;
        Node* currentNode = root;

        //parse through each class in the classification path
        while (std::getline(ss, Class, ',')) {
            //check for illegal_exceptions
            for (char c : Class) {
                if (std::isupper(c)) {
                    throw illegal_exception();  //throw an exception if uppercase is found
                }
            }

            //if no expetions, continue with the trie traversal 
            for (auto child = currentNode->Children.begin(); child != currentNode->Children.end(); ++child) { //check if class already exists as a child of current node
                if (child->first == Class) { 

                    //if child is the terminal node, delete the last node therfore erasing the classification
                    if(child->second->Children.empty()==true){
                       delete child->second;
                       currentNode->Children.erase(child);
                                                  
                            numClassifications-=1;   //update num classifications

                        std::cout << "success" << std::endl;
                        return; 
                    }
                    
                    //else, travers the tree farther
                    currentNode = child->second; 
                    break;
                } 
            } 
        }

        //if classification did not exists or trie is empty
        std::cout << "failure" << std::endl;
        return;
    }
     
    //if an illegal_excpetion was found
    catch (const illegal_exception& e) {
        std::cout <<"illegal argument"<< std::endl; 
    }
}

void PRINT() {
    std::vector<std::string> classifications;
    printClassifications(root, "", classifications);

    if (classifications.empty()) {
        std::cout << "trie is empty" << std::endl;
    } 
    
    else {
        for (int i = 0; i < classifications.size(); i++) {
            std::cout<< classifications[i]<<"_"; //only has problem when i add "_"
        }
        std::cout<< std::endl;
    }
}


void EMPTY(){
    if(root->Children.empty()==true){
        std::cout << "empty 1" << std::endl;
    }

    else{
        std::cout << "empty 0" << std::endl;
    }
}

void CLEAR(){
    // Clear all nodes from the root
    clearNode(root);

    // Reset root node to empty state
    root->Children.clear();

    numClassifications=0;
    std::cout << "success" << std::endl;
}

void SIZE(){
    std::cout << "number of classifications is "<<numClassifications<< std::endl;
}

void EXIT(){
    clearNode(root);

    delete root;
    root = nullptr;
}

/////helper functions
void printClassifications(Node* currentNode, std::string path, std::vector<std::string>& classifications) {
    // If the node has no children, it is a terminal node (end of a classification path)
    if (currentNode->Children.empty()) {
        if (!path.empty()) {
            classifications.push_back(path);  // Add the full classification path to the vector
        }
        return;
    }

    // Traverse each child node
    for (const auto& child : currentNode->Children) {
        std::string newPath;

        //if node is root
        if(path.empty()){
            newPath = child.first; 
        }

        else{
           newPath = path + "," + child.first; 
        }
        //std::cout << newPath << std::endl;
        printClassifications(child.second, newPath, classifications);
    }
}

void clearNode(Node* currentNode) {
    // Recursively delete all children of the current node
    for (auto& child : currentNode->Children) {
        clearNode(child.second);
        delete child.second;
    }
    currentNode->Children.clear(); // Clear the children vector
}

///Class
Node::Node(std::string name){
    className=name;
}

Node::~Node(){}



