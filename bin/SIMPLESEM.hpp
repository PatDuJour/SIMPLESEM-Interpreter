//
//  SIMPLESEM.hpp
//  
//
//  Created by Patrick Zhang on 7/1/15.
//  Copyright (c) 2015 Patrick Zhang. All rights reserved.
//

#ifndef SIMPLESEM_hpp
#define SIMPLESEM_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
void read_values(const std::string& file_name, std::vector<T>& lines);
std::string get_token(std::string& line);
void set(std::string token, std::string line);
void jump(std::string token, std::string line);
void jumpt(std::string token, std::string line);
void expr(std::string token, std::string line);
void term(std::string token, std::string line);
void factor(std::string token, std::string line);
void number(std::string token, std::string line);

#endif
