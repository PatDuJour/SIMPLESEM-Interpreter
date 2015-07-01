//
//  SIMPLESEM_Interpreter.cpp
//  HW1
//
//  Created by Patrick Zhang on 6/30/15.
//  Copyright (c) 2015 Patrick Zhang. All rights reserved.
//

#include "SIMPLESEM.hpp"

template <typename T>
void read_values(const std::string& file_name, std::vector<T>& lines){
    std::fstream file(file_name);
    std::string line;
    
    if (file.is_open()) {
        while (std::getline(file,line)){
            lines.push_back(line);
        }
    }
    else{
        std::cout<<"Unable to Open File."<<std::endl;
    }
}

std::string get_token(std::string& line){
    std::string first;
    if (std::stringstream(line) >> first) {
        line.erase(line.begin(), line.begin()+first.size()+1);
    }
    return first;
}

void number(std::string token, std::string line){
    std::cout<< "Number" <<std::endl;
}
void factor(std::string token, std::string line){
    token.erase(0, token.find_first_not_of(" \n\r\t"));
    std::cout<< "Factor" <<std::endl;
    token.erase(token.find_last_not_of(" \n\r\t")+1);
    if (isdigit(token[0])) {
        number(token, line);
    }
    else if(token[0] == 'D'){
        expr((std::string)&token[2], line);
    }
    else{
        std::cout<<"Exception at Factor;" <<token<<std::endl;
    }
}
void term(std::string token, std::string line){
    std::cout<< "Term" <<std::endl;
    factor(token, line);
}
void expr(std::string token, std::string line){
    std::string left;
    std::string right;
    std::string delimiter;
    if (token.find("read")==std::string::npos && token.find("write")==std::string::npos) {
        std::cout << "Expr" <<std::endl;
        if (token[0] == 'D' && token.find("-")!=std::string::npos) {
            delimiter = "-";
            left = token.substr(0, token.find(delimiter));
            right = token.substr(token.find(delimiter)+1, std::string::npos);
            term(left, line);
            term(right, line);
        }
        
        else if (token[0] == 'D' && token.find("+")!=std::string::npos) {
            delimiter = "+";
            left = token.substr(0, token.find(delimiter));
            right = token.substr(token.find(delimiter)+1, std::string::npos);
            term(left, line);
            term(right, line);
        }
        
        else{
            term(token, line);
        }
        
    }
}
void set(std::string token, std::string line){
    std::cout<< "Set"<<std::endl;
    std::string first;
    std::string second;

    first = get_token(line);
    second = line;
    expr(first, line);
    expr(second, line);
}
void jumpt(std::string token, std::string line){
    std::cout<< "Jumpt" <<std::endl;
    token = get_token(line);
    expr(token, line);
    token = get_token(line);
    expr(token, line);
    token = get_token(line);
    token = get_token(line);
    expr(token, line);
    
}
void jump(std::string token, std::string line){
    std::cout<< "Jump"<<std::endl;
    token = get_token(line);
    expr(token, line);
}
void halt(){return;}


void statement(std::string line){
    std::string token;
    token = get_token(line);

    if (token == "set") {
        set(token, line);
    }
    else if (token == "jumpt") {
        jumpt(token, line);
    }
    else if (token == "jump") {
        jump(token, line);
    }
    else if (token == "halt") {
        halt();
    }
    else{
        std::cout<<"unexpected expression"<<std::endl;
    }
}


int main(int argc, const char * argv[]) {

    std::vector<std::string> lines;
    read_values(argv[1], lines);
    
    std::cout<<"Program"<<std::endl;
    for (auto i: lines){
        std::cout<<"Statement"<<std::endl;
        statement(i);
        std::cout<<std::endl;
    }
               
    return 0;
}
