#include "header.h"
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <fstream>

int main() {
	//displays ASCII text on startup
	logo();

	//variable declaration
	char in1, in2, in3;
	int num1, num2, num3; //fbNum;
	std::string input, file;
	bool test, brute;
	int cost, roi;
	

	//while loop to repeat program
	while (input != "exit") {
		//main prompt
		std::cout << "Enter 'exit' to end program, or enter 'help' for more info.\n";
		std::cout << "Enter a year, 2020 - 2024, to read (YYYY):\n>";
		std::cin >> input;
		std::cout << std::endl;

		if (input == "exit") {
			break;
		}
		else if (input == "help") {
			help();
			continue;
		}

		test = fileTest(input + ".txt");
		if (test == 1) {
			continue;
		}
		
		file = input + ".txt";

		loop_return:
		std::cout << "Run automatic scan? (y/n):\n>";
		std::cin >> input;
		std::cout << std::endl;

		if (input == "y") {
			brute = true;
			autoScan(file, brute, &cost, &roi);
		}
		else if (input == "n") {
		    brute = false;
			
			while (0 == 0) {
				std::cout << "Enter ticket numbers, or 'q' to return to year selection:\n>";
				//std::cin >> in1;
				std::cin >> in1;

				if (in1 == 'q') {
					std::cin.clear();
					std::cin.ignore();
					std::cout << std::endl;
					break;
				}
				
				std::cin>> in2 >> in3;
				std::cin.clear();
				std::cin.ignore();
		//		std::cout << "\n";
				
				
				//convert char to ascii value integer
				num1 = static_cast<int>(in1);
				num2 = static_cast<int>(in2);
				num3 = static_cast<int>(in3);
				
				//convert ascii value to original integer value
				num1 -= 48;
				num2 -= 48;
				num3 -= 48;
				
				
				// ticket numbers must be 0 - 9
				if ((num1  > 9 ) || (num2 > 9) || (num3 > 9) || (num1 < 0 ) || (num2 < 0 ) || (num3 < 0)) {
					std::cout << "Invalid ticket numbers. Try again\n";
					continue;
				}

				readFile(file, num1, num2, num3, brute, &cost, &roi);
				
			} //end of while loop
		} //end of else if

		else {
			std::cout << "invalid input" << std::endl;
			goto loop_return;
		}


	} // end of while loop
	return 0;
}