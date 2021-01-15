#include "Order.h"
#include "Menu.h"
#include "Appetiser.h"
#include "Helper.h"
#include "stdio.h""
#include <iostream>
#include <fstream>
#include <map>

// Write the checkout confirmation screen, reusing Menu's toString() method.

int Order::getIndex(Menu menu, int menu_number) { // Get index of item in menu object's itemlist from the number shown on the menu

	Item* menu_item_pointer = menu.items[menu_number-1]; // Access menu's itemList, get pointer for given menu number

	for (std::size_t i = 0; i != this->items.size(); ++i) { // Iterate over order.items...
		if (menu_item_pointer == this->items.at(i)) { // until pointers match
			return i; // If found, return index
		}
	}

	return -1; // If not found, return -1 (as an error code!)
}

void Order::checkout() {
	std::cout << this->toString("cl");
	std::cout << "\n";
	this->confirmOrder();
	return;
}

std::string Order::toString(std::string env) {
	std::string output = "";

	// We need to print out the order items in the same way as we did with the menu
	output.append("========== Checkout ==========\n");

	for (std::size_t i = 0; i != this->items.size(); ++i) {

		auto(*current_item) = this->items[i]; // can be used to interact with object
		output.append(current_item->toString(env));
		output.append("\n");

	}

	output.append("------------------------------\n");

	output.append(this->calculateTotal(env));

	return output;
}

std::string Order::calculateTotal(std::string env) {
	std::string output = "";
	Appetiser* appetiser_handle;
	int twoForOne_clock = 0;
	double discount = 0;
	double total = 0;

	// We need to output a string of stuff
	for (std::size_t i = 0; i != this->items.size(); ++i) {

		auto(*current_item) = this->items[i]; // can be used to interact with object

		// Check for any savings?
		if (current_item->item_code() == "a") {
			Appetiser * appetiser_handle = dynamic_cast<Appetiser*>(current_item); // Use pointer of parent (Item) as pointer to child (Appetiser)
			if (appetiser_handle->twoForOne()) {
				// appetiser is two for one!
				twoForOne_clock++; // Another two for one!

				if (twoForOne_clock % 2 == 0) { // If there has been another two for one, let this one have a discount
					discount = discount + appetiser_handle->price(); // Add the price to discount to be removed at the end
				}
			}
		}

		total = total + current_item->price();

	}

	if (discount > 0) {
        total = total - discount;
		output.append("2-4-1 discount applied! Savings: " + std::string(env == "cl" ? "\x9C" : "\u00A3") + Helper::FormatDoubleToString(discount) + "\n");
	}

	output.append("Total: " + std::string(env == "cl" ? "\x9C" : "\u00A3") + Helper::FormatDoubleToString(total));
	

	// Get total for order

	return output;
}

void Order::confirmOrder() {

	std::string command;

	// Ask if they want to confirm
	std::cout << "Type 'y' to confirm, or 'n' to go back and modify it.\n";
	std::cin >> command;
	if (command == "n") { // if no, return
		std::cin.ignore();
		return;
	}
	else if (command == "y") {// if yes...
		// write to receipt.txt
		ofstream receipt;
		receipt.open("receipt.txt");
		receipt << this->toString("file"); // Output order object as string
		receipt.close();

		// delete all objects (do we need to?)

		// then exit program
		exit(0);
	}
	
}