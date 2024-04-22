#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

//This was found on StackOverflow.com
template<typename charT, typename traits = std::char_traits<charT> >
class center_helper {
    std::basic_string<charT, traits> str_;
public:
    center_helper(std::basic_string<charT, traits> str) : str_(str) {}
    template<typename a, typename b>
    friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);
};

template<typename charT, typename traits = std::char_traits<charT> >
center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
    return center_helper<charT, traits>(str);
}

// redeclare for std::string directly so we can support anything that implicitly converts to std::string
center_helper<std::string::value_type, std::string::traits_type> centered(const std::string& str) {
    return center_helper<std::string::value_type, std::string::traits_type>(str);
}

template<typename charT, typename traits>
std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& s, const center_helper<charT, traits>& c) {
    std::streamsize w = s.width();
    if (w > c.str_.length()) {
        std::streamsize left = (w + c.str_.length()) / 2;
        s.width(left);
        s << c.str_;
        s.width(w - left);
        s << "";
    } else {
        s << c.str_;
    }
    return s;
}

void help();
void logo();
int isWin(int num1, int num2, int num3, int win1, int win2, int win3, int fbWin);
int earningsCalculator(int winType);
int readFile (std::string fileName, int in1, int in2, int in3, bool brute, int* cost, int* roi);
bool fileTest(std::string fileName);
void autoScan(std::string fileName, bool brute, int* cost, int* roi);

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
		std::cout << "Enter a year to read (YYYY):\n>";
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

//function to determine win and what type
/*
returns integer value to determine win type:

0 = none
1 = straight
3 = box
5 = fbStraight
11 = fbBox

4 = straight + box
6 = straight + fbStraight
8 = box + fbStraight
12 = straight + fbBox
14 = box + fbBox
16 = fbStraight + fbBox

9 = straight + box + fbStraight
15 = straight + box + fbBox
19 = box + fbStraight + fbBox

*/

void logo(){
	std::cout << std::setw(64) << std::setfill('*') << "*" << std::endl;
	std::cout << "*" << std::setw(63) << std::setfill(' ') << "*" << std::endl;
	std::cout << "*" << std::setw(62) << centered("NJ Pick 3 Lotto Tool") << "*" << std::endl;
	std::cout << "*" << std::setw(62) << centered("Version 0.2.1") << "*" << std::endl;
	std::cout << "*" << std::setw(63) << std::setfill(' ') << "*" << std::endl;
	std::cout << std::setw(64) << std::setfill('*') << "*" << std::endl << std::endl;
}

int isWin(int num1, int num2, int num3, int win1, int win2, int win3, int fbWin) {
	/*
	types of wins:
		straight
		box (6way)
		fbStraight
		fbBox (6way)
	*/
	
	int winType = 0;

    //verified
	//check if straight
	if ((num1 == win1 ) && (num2 == win2) && (num3 == win3)) {
		winType += 1;
	} // end of straight



	//check if box
    if ((num1 == win1) && (num2 == win3) && (num3 == win2)) {
	    winType += 3;
	}
	
	else if ((num1 == win2) || (num1 == win3)) {
		if (num1 == win2) {
			if ((num2 == win1) && (num3 == win3)) {
					winType += 3;
			}
			else if ((num2 == win3) && (num3 == win1)) {
			    winType += 3;
			}
		}
		else if ( num1 == win3){
		    if ((num2 == win1) && (num3 == win2)) {
		        winType +=3;
		    }
		    else if ((num2 == win2) && (num3 == win1)) {
		        winType += 3;
		    }
		}
	} // end of box check


    // check if fb straight
    if ((win1 == fbWin ) && (num2 == win2) && (num3 == win3)) {
		winType += 5;
	}
    else if ((num1 == win1 ) && (win2 == fbWin) && (num3 == win3)) {
		winType += 5;
	}
	else if ((num1 == win1 ) && (num2 == win2) && (win3 == fbWin)) {
		winType += 5;
	} // end of fb straight check
	
	
	// fb box check
	//fb == win1 series
	if ((win1 == fbWin) && (num3 == win2) && ((num1 == win3) || (num2 == win3)) ) {
	    winType += 11;
	}
	else if ((win1 == fbWin) && (num1 == win2) && ((num2 == win3) || (num3 == win3))) {
	    winType += 11;
	}
	else if ((win1 == fbWin) && (num2 == win2) && (num1 == win3)) {
	    winType += 11;
	}
	
	//fb == win2 series
	else if ((win2 == fbWin) && (num2 == win1) &&  ((num1 == win3) || (num3 == win3))) {
	    winType += 11;
	}
	else if ((win2 == fbWin) && (num3 == win1) && ((num1 == win3) || (num2 == win3))) {
	    winType += 11;
	}
	else if ((win2 == fbWin) && (num1 == win1) && (num2 == win3)) {
	    winType += 11;
	}
	
	
	//fb == win3 series
	else if ((win3 == fbWin) && (num2 == win1) && ((num1 == win2) || (num3 == win2))) {
	    winType += 11;
	}
	else if ((win3 == fbWin) && (num3 == win1) && ((num1 == win2) || (num2 == win2))) {
	    winType += 11;
	}
	else if ((win3 == fbWin) && (num1 == win1) && (num3 == win2)) {
	 winType += 11;
	} // end of fb box check
	
	
	//returns int value to input in another function 
	return winType;
	
} // end of isWin function


int earningsCalculator(int winType) {
	/*
	Earnings chart:
		straight -- $250
		box -- $40
		
		fbStraight -- $90
		fbBox -- $15
	*/
	
	//variable declaration
	int winTotal;

	//converts win value to monetary units
	switch (winType) {
		case 0:
			winTotal = 0;
			break;
		case 1:
			winTotal = 250;
			break;
		case 3:
			winTotal = 40;
			break;
		case 4:
			winTotal = 290;
			break;
		case 5:
			winTotal = 90;
			break;
		case 6:
			winTotal = 340;
			break;
		case 8:
			winTotal = 130;
			break;
		case 9: 
			winTotal = 380;
			break;
		case 11:
			winTotal = 15;
			break;
		case 12: 
			winTotal = 265;
			break;
		case 14:
			winTotal = 65;
			break;
		case 15: 
			winTotal = 305;
			break;
		case 16:
			winTotal = 105;
			break;
		case 19:
			winTotal = 155;
			break;
	}
	return winTotal;
} //returns running total of winnings


int readFile (std::string fileName, int in1, int in2, int in3, bool brute, int* cost, int* roi) {
std::ifstream inputFile(fileName);

    int i;
	int count = 0;
	int n = 0;
	std::string date;
//	int day, month, year;
    
    std::string streamString;
  //  char stream;
	char num0, num1, num2, num3;
	int w1, w2, w3, wf;
	
	int runningTotal = 0;
    
    // Check if the file is opened successfully
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
       	
    }

    std::string line;
    // Read and print each line from the file
    while (std::getline(inputFile, line)) {
		n++;
        i = 18;
		char ch = line[4];
		if (ch == '/') {
			count++;
			if (date != line.substr(0, 9)) {
			date = line.substr(0, 9);
			//outputfile << date << std::endl;
			}
		}
 
        while ( (48 > static_cast<int>(line[i])) && (57 < static_cast<int>(line[i])) ) {
            i++;
             //std::cout << line[i];
        }

		//midday drawings
		if (line[i - 2] == 'Y') {
			num0 = line[i];
			i++;
			num1 = line[i];
			i++;
			num2 = line[i];
			i += 2;
			num3 = line[i];
		}

		//evening drawings
		else {
			i++; 

			//handles str/back lines
			if (line[30] == 'S') {
// for testing  	std::cout << "STR/BACK!!!!\n";
				num0 = line[i];
				i++;
				num1 = line[i];
				i++;
				num2 = line[i];
				i += 23;
				num3 = line[i];
			}
			// non-str/back lines
			else if (('0' <= line[i])&&(line[i] <= '9')) { 
				num0 = line[i];
				i++;
				num1 = line[i];
				i++;
				num2 = line[i];
				i += 2;
				num3 = line[i];
			}
			inputFile.ignore();
		} //end of else
		
		
		w1 = static_cast<int>(num0) - 48;
		w2 = static_cast<int>(num1) - 48;
		w3 = static_cast<int>(num2) - 48;
		wf= static_cast<int>(num3) - 48;
		
		int winCheck = isWin(in1, in2, in3, w1, w2, w3, wf);
		
		runningTotal += earningsCalculator(winCheck);
    } // end of while loop

    *cost = (count * 2);
	*roi = (runningTotal * 100 / (count * 2));

if (brute == 0){
   std::cout << "total: $" << runningTotal << "\n";
   std::cout << "Cost: $" << *cost << "\n";
   std::cout << "Return: " << runningTotal * 100 / *cost << "%\n\n";

// Close the file
    inputFile.close();
}
else if (brute == 1){
    // Close the file
    inputFile.close();
}
return runningTotal;
}


bool fileTest (std::string fileName) {
	std::ifstream inputFile(fileName);

	// Check if the file is opened successfully
    if (!inputFile) {
        std::cerr << "Failed to open the file.\n\n";
       	return 1;
    }
	else {
		// Close the file
    	inputFile.close();
		return 0;
	}
}


void autoScan(std::string fileName, bool brute, int* cost, int* roi) {
	//intilization
	int num[3] = {0, 0, 0};
    std::ofstream outFile("temp.txt");
    int total, record;
    int win[3] = {0, 0, 0};
	*roi = 0;
	*cost = 0;
	total = 0;
    
	outFile << "Year: ";
	for (int i = 0; i < 4; i++){
		outFile << fileName[i];
	} 
	outFile << std::endl
			<< "Numbers\t\t"
			<< "Earnings\t\t\n";
    
	while (brute == true) {
		record = readFile(fileName, num[0], num[1], num[2], brute, cost, roi);
		
        if (record >= total){
            total = record;
            outFile << num[0] << "-" << num[1] << "-" << num[2] << std::setw(8);// "\t";
			outFile << "$" << total << "\t" << "\n";
            win[0] = num[0];
            win[1] = num[1];
            win[2] = num[2];
        }
        
        // if statements to increase and cycle scanning numbers
        if (num[2] < 9) {
            num[2]++;
        }
		//num2 = 9
        else {
            if (num[1] < 9) {
                num[1]++;
                num[2] = 0;
            }
			//num1 = 9
            else {
                if (num[0] < 9) {
                num[0]++;
                num[1] = 0;
                num[2] = 0;
                }
                else {
                    break;
                }
            }
        }
	} // end of loop

	std::cout << "Highest paying ticket: ";
	for (int i = 0; i < 3; i++){
	std::cout << win[i];
	}
	*roi = (total * 100) / *cost;
	std::cout << std::endl;
    std::cout << "$" << total << std::endl;
	std::cout << "cost: $" << *cost << std::endl;
	std::cout << "Return: " << *roi << "%" << std::endl << std::endl;
} // end of autoScan function

void help() {
	std::string pause;

	std::cout << "This program is designed to test ticket numbers for the New Jersey Pick 3 lottery.\n";
	std::cout << "Based on the assumption that one buys the same ticket every day for a year,\n";
	std::cout << "it will calculate the cost, payout, and return for that ticket.\n";
	std::cout << "As of this current version, it will only calculate the ticket as a Straight/Box of \n";
	std::cout << "$0.50 wager, with the fireball option, playing both daily drawings.\n";
	std::cout << "This program currently does not calculate 'Straight Back' bonus winnings.\n";
	std::cout << "Total ticket cost is $4 per day.\n\n";
	std::cout << "The automatic function will scan every possible ticket value, and determine the\n";
	std::cout << "highest paying ticket for that year. Starting with 0-0-0, it will also print \n";
	std::cout << "ticket numbers with higher payouts than the previously tested ticket. These values can be\n";
	std::cout << "found in the file \"temp.txt\". This file is overwritten for each automatic scan.\n\n";
	std::cout << "Enter any key to continue.\n";
	std::cin >> pause;
 	std::cout << std::endl << std::endl;
} // end of Help function
