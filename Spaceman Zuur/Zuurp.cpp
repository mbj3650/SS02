#include <iostream>
#include <conio.h>
#include <cassert>
#include <Windows.h>
struct zuurp {
	int wrongletter = 0;//zuurp is the tracker because its thematically accurate and also its
	int rightletter = 0;//easy to refer to 
	int loseround = 0;
	int winround = 0;
	bool leaving = false;
};
struct WordHider {
	std::string theword;//the word stored
	bool revealed = false; //when true, it means theres no more underscores
};

enum WORDS
{
	SPACEMAN = 0,//word enums
	ALIEN = 1,
	EXTRATERRESTRIAL = 2,
	GALAXY = 3,
	UNIVERSE = 4,
};
bool checkword(zuurp* tracker, std::string word, WordHider*hiddenword, char input, std::string* incorrectchars, char* letters);//checks the word
//increments incorrect chars, updates the hidden word display, updates the letter array and updates the zuurp tracker


std::string generatewordstring(std::string word);
void printzuurp();//we're gonna need to print him a lot, but not all the time, so turn it into a function
void printship(int wrongletter);//print ship
void game();
void drawgame(zuurp* tracker, WordHider worddisplay, std::string incorrectchars);
std::string getword(int word);//gets enum turns returns string form

void main() {
	//intro
	std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
	std::cout << "          Welcome to SPACEMAN, a word-guessing game!\n";
	std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";

	std::cout << "Zuurp, an alien, has crashed on planet Earth! Zuurp mistakes you\n";
	std::cout << "               for Earth's leader and demands you\n";
	std::cout << "guess their secret word, one letter at a time. Zuurp's people have\n";
	std::cout << "   been monitoring Earth for years, and hence know the English\n";
	std::cout << "                        language quite well!\n\n";
	std::cout << "     If you don't guess the word quickly enough, Zuurp will\n";
	std::cout << "   rebuild their spaceship and leave, but if you do manage to\n";
	std::cout << "   guess Zuurp's secret word then they will stay to play again!\n";
	std::cout << "             Beware, Zuurp likes numbers, and will be\n";
	std::cout << "                recording your data as you guess!\n";
	_getch();//wait for user to press any key before starting game
	game();
}

void game() {
	zuurp tracker;//tracker (zuurp)
	srand(time(0));//set seed
	bool gamefinished = false; //is game finished?
	WordHider worddisplay; //word display, displays progress of player such as underscores or correct letters

	assert(tracker.wrongletter == 0);//check if most important value is 0
	do {
		
		WORDS wordtoguess = static_cast <WORDS>(rand() % 5);//set random word from enums
		worddisplay.theword = generatewordstring(getword(wordtoguess));//hidden word starts as all underscores and will be
		//filled in and displayed on the screen as the game progresses

		std::string incorrectchars = "";
		worddisplay.revealed = false;
		char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',//list of choosable characters
		'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		do {
			drawgame(&tracker, worddisplay, incorrectchars);//draw game

			char input = _getch();//wait for input
			checkword(&tracker, getword(wordtoguess), &worddisplay, input, &incorrectchars, letters);//check word

		} while (incorrectchars.length() != 9 && worddisplay.revealed == false);

		//when game is complete:

		drawgame(&tracker, worddisplay, incorrectchars);//draw game with filled word

		std::cout << "Zuurp says, \"My secret word was...\"\n\n";
		for (int i = 0; i < getword(wordtoguess).length(); i++) {//print each letter
			std::cout << getword(wordtoguess)[i] << " ";
		}
		std::cout << "\n";
		if (worddisplay.revealed == true) {//if player won
			std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
			std::cout << "       Xzoopz!! That means 'well done' on Zuurp's world!\n\n";
			std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
			printzuurp();
			tracker.winround++;//increment
		}
		else {
			std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
			std::cout << "                   Zuurp is ready to go home!\n\n";
			std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
			tracker.loseround++;//else increment rounds lost
		}
		std::cout << "Want to play again? y/n\n";
		char playagain;
		do {
			playagain = _getch();
		} while (playagain != 'y' && playagain != 'n');
		if (playagain == 'n') {//if user doesnt want to play
			//output messages and stats
			std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
			std::cout << "          Zuurp left planet Earth for good this time!\n\n";
			std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n";
			if (tracker.winround == 1) {//plural checking
				std::cout << tracker.winround << " word fully revealed.\n";
			}
			else {
				std::cout << tracker.winround << " words fully revealed.\n";
			}

			if (tracker.loseround == 1) {
				std::cout << tracker.loseround << " word not fully revealed.\n";
			}
			else {
				std::cout << tracker.loseround << " words not fully revealed.\n";
			}

			if (tracker.rightletter == 1) {
				std::cout << tracker.rightletter << " letter correctly guessed.\n";
			}
			else {
				std::cout << tracker.rightletter << " letters correctly guessed.\n";
			}
			
			if (tracker.wrongletter == 1) {
				std::cout << tracker.wrongletter << " letter incorrectly guessed.\n";
			}
			else {
				std::cout << tracker.wrongletter << " letters incorrectly guessed.\n";
			}

			gamefinished = true;//finish game
		}
		else if(worddisplay.revealed == false){
			tracker.leaving = true; //zuurp wants to leave, tells display he was meant to leave but crashed

		}

	} while (gamefinished == false);//while game isnt complete
	
}

void printship(int wrongletter) {
	switch (wrongletter) {//calls a switch on the wrongletter amuont
		case 1://prints each state based on the amount
			std::cout <<  "____________________\n";
			std::cout << "\\__________________/\n";
			break;
		case 2:
			std::cout << " ________________________\n";
			std::cout << "/________________________\\\n";
			std::cout << "  \\___________________/\n";
			break;
		case 3:
			std::cout << " ________________________\n\n";
			std::cout << "/___________O____________\\\n";
			std::cout << "  \\___________________/\n";
			break;
		case 4:
			std::cout << " ________________________\n\n";
			std::cout << "/_____O__O__O____________\\\n";
			std::cout << "  \\___________________/\n";
			break;
		case 5:
			std::cout << " ________________________\n\n";
			std::cout << "/____O__O__O__O__O____\\\n";
			std::cout << " \\___________________/\n";
			break;
		case 6:
			std::cout << "_____/_______________\\_____\n";
			std::cout << "  /____O__O__O__O__O____\\\n";
			std::cout << "   \\___________________/\n";
			break;
		case 7:
			std::cout << "_____/_______________\\_____\n";
			std::cout << "  /____O__O__O__O__O____\\\n";
			std::cout << "       \\__|__|__|__/\n";
			break;
		case 8:
			std::cout << "          ........\n";
			std::cout << "       ..          ..\n";
			std::cout << "_____/_______________\\_____\n";
			std::cout << "  /____O__O__O__O__O____\\\n";
			std::cout << "       \\__|__|__|__/\n";
			break;
		case 9:
			std::cout << "          ........\n";
			std::cout << "       ..    \\_/    ..\n";
			std::cout << "_____/_______(\")_____\\_____\n";
			std::cout << "  /____O__O__O__O__O____\\\n";
			std::cout << "       \\__|__|__|__/\n";
			break;
	}
}


void drawgame(zuurp* tracker, WordHider worddisplay, std::string incorrectchars) {
	system("cls");
	if (tracker->leaving == true) {
		tracker->leaving = false;
		std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n"; 
		std::cout << "     Something went wrong with Zuurp's spaceship... Zuurp\n\n";
		std::cout << "           returns to planet Earth to rebuild again...\n\n";
		std::cout << "        -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
	}
	std::cout << "+----------------------------------------------------------------------------------------------+\n\n";
	std::cout << worddisplay.theword << "\n";//display user's progress so far

	printship(incorrectchars.length());//print the ship
	if (incorrectchars.length() != 9) {
		printzuurp();//print him as long as 9 characters arent wrong, otherwise hed be in theship
	}


	std::cout << "+----------------------------------------------------------------------------------------------+\n\n";

	std::cout << "Zuurp counts " << incorrectchars.length() << " incorrect guesses... [";
	if (incorrectchars.length() <= 1) {//if only one or less incorrect
		for (int i = 0; i < incorrectchars.length(); i++) {
			std::cout << incorrectchars[i];//output only 1
		}
	}
	else {
		std::cout << incorrectchars[0];//if wrong letters is greater than 1 we can start
		if (tracker->wrongletter > 1) {//outputting it with commas
			for (int i = 1; i < incorrectchars.length(); i++) {

				std::cout << ", " << incorrectchars[i];
			}
		}
	}

	std::cout << "]\n";
	std::cout << "Earth leader: ";//earth leader input

}

bool checkword(zuurp* tracker, std::string word, WordHider *hiddenword, char input, std::string* incorrectchars, char *letters) {
	bool foundword = false; //if the input was a new unguessed letter in the word
	char tocheck = tolower(input);
	bool guessed = true;
	if (isalpha(tocheck)) {
		for (int i = 0; i < 26; i++) {//make sure we havent guessed it yet by scanning the array
			if (letters[i] == tocheck) {//if letter equals the input char
				letters[i] = -12;//make letter gone
				guessed = false;//since we had to remove the letter, it means that it wasnt guessed yet
			}
		}
		if (guessed == false) {//if we hadnt guessed it yet
			for (int i = 0; i < word.length(); i++) {
				if (tolower(tocheck) == tolower(word[i])) {
					//std::cout << tocheck << word[i];
					hiddenword->theword.replace(i, 1, 1, tocheck);
					foundword = true;
				}
			}
		}
		if (!guessed) {//if not guessed, allow it to go forward
			if (foundword) {
				hiddenword->revealed = true;
				for (int i = 0; i < hiddenword->theword.length(); i++) {//check if theres still underscores
					if (hiddenword->theword[i] == '_') {
						hiddenword->revealed = false;
					}
				}
				tracker->rightletter++;//increment right letter guesses
			}
			else {
				incorrectchars->append(1, tocheck);//add to incorrect chars list
				tracker->wrongletter++;//increment wrong letter guesses
			}
		}
	}
	else{
		std::cout << "Zuurp says: \"Qzwopp! " << tocheck << " is not a letter!\"\n";//if not alphabetical, output message insteaed
	}
	return foundword;
}

void printzuurp() {//print the fellow
	std::cout << "                                       \\_/\n";
	std::cout << "                                       (\")\n";
	std::cout << "                                     ---+---\n";
	std::cout << "                                      _/ \\_\n";
}

std::string generatewordstring(std::string word) {
	std::string toreturn = "";//gets the length and creates a string of underscores from it
	for (int i = 0; i < word.length(); i++) {
		toreturn.append("_");
	}
	return toreturn;
}

std::string getword(int word) {//gets word from given enum
	std::string words[5] = { "spaceman", "alien","EXTRATERRESTRIAL" ,"GALAXY" ,"UNIVERSE" };
	return(words[word]);
}