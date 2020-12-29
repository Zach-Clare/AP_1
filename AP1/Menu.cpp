#include "Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Menu::Menu(std::string given_conf_file) {
	std::ifstream active_conf_file (given_conf_file); // Select and open the given file
	std::string line;
	std::vector<std::string> menu_item;

	if (active_conf_file.is_open()) { // Successfully opened
		while (std::getline(active_conf_file, line)) {
			Menu::parseLine(line) = menu_item; // Parse this line into a vector of tokens.
			////////////////////////////// Currently here - completed constructor for appetiser (and item).
			//  TODO: complete other constructors and then create objects with given letter code from the csv. Will have to cast the indexes as we pass them. We'll also need some sort of try-catch.
		}
		active_conf_file.close();
	}
	else {
		cout << ":("; // File wasn't successfully opened. Maybe exit gracefully?
	}
}

std::vector<std::string> Menu::parseLine(std::string line) {
	std::string token;
	std::vector<std::string> result;
	std::stringstream line_stream;
	
	line_stream.str(line);

	while (std::getline(line_stream, token, ',')) {
		result.push_back(token);  
	}
	return result;
}

std::string Menu::toString() {
	return ""; // Format menu here
}