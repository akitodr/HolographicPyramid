#pragma once
#include <iostream>
#include <string>
#include <fstream>

static int readFile(std::string fileName, std::string type) {

	std::ifstream file;
	file.open(fileName);
	std::string line;
	std::string number;

	while (std::getline(file, line))
	{
		//std::cout << "line:" << line << std::endl;
		if (line.find(type) != std::string::npos) {
			number = line.substr(line.find(":") + 1);
			//std::cout << number << std::endl;
			return std::stoi(number);
		}
	}
}