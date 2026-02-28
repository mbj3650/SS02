#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
void colorrandomizer(HANDLE h);//randomizes text color
void resetcolor(HANDLE h);//resets text to white
void letterrandomizer(char& letter, char letters[]);
bool game();//sets up initial game stuff
bool gameround(int& right, int& wrong, HANDLE h);//the main meat and bones of the game
void main() {
	
	while(!game());
}
bool game() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//setup for colored text
	SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);//set text to be white background with black text
	std::cout << "       " << "+-----------------------+                   \n";//output intro
	std::cout << "       " << "| Keyboard Whack-Em-All |                   \n";
	std::cout << "       " << "+-----------------------+                   \n";
	std::cout << "Press the missing letter's key! (Press '~' to quit)\n\n";
	int right = 0;//tracks right guesses
	int wrong = 0;//tracks wrong ones
	srand(time(0));//set seed
	resetcolor(h);//reset text color to white
	while(gameround(right, wrong, h));//loop gamerounds
	return true;//return when game rounds is finished
}

bool gameround(int& right, int& wrong, HANDLE h) {

	char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',//list of choosable characters
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
	'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	
	colorrandomizer(h);//randomize characters
	char randomletter;//random letter storage
	bool canpass = false;//whether user passes the  round
	letterrandomizer(randomletter, letters);//randomize ,letter
	//std::cout << randomletter;
	for (int i = 0; i < 26; i++) {//prints out the message with one letter as underscore (the right one)
		if (letters[i] == randomletter) {//if sequence of letters' letter is the chosen one
			std::cout << '_' << " ";//underscore here
		}
		else {
			std::cout << letters[i] << " ";//else just print letter
		}
	}
	std::cout << "\n";//output newline
	do {
		char userinput;//char for input
		userinput = _getch();//getch puts input into storage
		if (userinput == randomletter) {//compare if its right
			right++;//then add to right count
			canpass = true;//let user pass
		}
		else if (userinput == '~' || userinput == '`') {//theyre on the same key so when that button in general is pressed stop the game
			canpass = true;//let user pass
			SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
			std::cout << "Correct count: " << right << "\n\n";//output stats
			std::cout << "Incorrect count: " << wrong;
			resetcolor(h); //reset color
			return false;//end game
		}
		else if (userinput != randomletter) {
			wrong++;//increment wrong
			canpass = false;//dont pass
		}
	} while (canpass == false);//do this while round hasnt passed

	return true;//return true to keep looping
}
void letterrandomizer(char &letter, char letters[]) {
	letter = letters[(rand() % 26)];//set it to a random letter
}
void colorrandomizer(HANDLE h) {
	SetConsoleTextAttribute(h, (rand() % 15)+1); //randomize color except for black because its impossible to see on the console
}

void resetcolor(HANDLE h) {
	SetConsoleTextAttribute(h, 15);//reset to white
}