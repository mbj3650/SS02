#include <conio.h>
#include <cstdlib>

#include <Windows.h>
#include <iostream>
#include <time.h>
struct Player
{
	int JewelsCollected = 0; //jewels the player has collected
	int posX = 0;//position coords
	int posY = 0;
	int moves = 0;//player moves
	/* Insert your code here */
	void move(char movement) {
		switch (tolower(movement)) {
			case 'w'://wasd movements
				if (posY != 0) {//cant go off map
					posY--;
				}
				
				break;
			case 's':
				if (posY < 9) {
					posY++;
				}
				
				break;
			case 'a':
				if (posX != 0) {
					posX--;
				}
				break;
			case 'd':
				if (posX < 49) {
					posX++;
				}
				break;
			default://if not wasd do nothing
				break;
		}
	}
};

struct Jewels
{
	int posX = 0; //coords
	int posY = 0;
	bool Collected = false; //check to see if collected
	char name;//name for when initializing
	/* Insert your code here */
	
};

void drawgame(Player p, Jewels Jewelarray[], HANDLE h); //draw game screen and clear console to do so
bool game();//run the game
void generateJewels(Jewels* J); //generate the jewel pos and names
void checkpos(Jewels* J, Player& p);//check positon of player to jewels
void resetcolor(HANDLE h);//reset color to black and white
void gameoverscreen(Player p,HANDLE h);//when game is finish print corresponding screen
void main() {
	game();
}

bool game() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//setup for colored text
	srand(time(0)); //set seed
	bool quit = false;//whether the player has quit or not 
	Jewels JewelArray[4]; //stores jewels structs
	generateJewels(JewelArray);//generate jewel stuff
	/*std::cout << "A Gem X =" << JewelArray[0].posX << " Y =" << JewelArray[0].posY<<"\n";
	std::cout << "B Gem X =" << JewelArray[1].posX << " Y =" << JewelArray[1].posY << "\n";
	std::cout << "C Gem X =" << JewelArray[2].posX << " Y =" << JewelArray[2].posY << "\n";
	std::cout << "D Gem X =" << JewelArray[3].posX << " Y =" << JewelArray[3].posY << "\n";
	std::cout << "\n\n\n";*/
	Player newp;//player
	Player& playerpointer = newp;//pointer to player for the checckpos
	drawgame(newp, JewelArray, h);//draw the game
	do {
		char userinput = _getch();//get input
		if (tolower(userinput) == 'q') {//if input is q then quit game
			quit = true;
			break;
		}
		else {
			newp.move(userinput);//else move normally
		}
		checkpos(JewelArray, playerpointer);//check the player position on jewel positions and update accordingly

		drawgame(newp, JewelArray,h);//draw game
		
		newp.moves++;//increase player moves
	} while (quit == false);//while player hasnt quit
	gameoverscreen(newp, h);//when player quits, create gameover screen

	return false;
}

void generateJewels(Jewels* J) {
	for (int i = 0; i < 4; i++) {
		bool canpass = true;
		do {
			(J + i)->posX = rand() % 50;//randomize pos, wont spawn outside
			(J + i)->posY = rand() % 9+1;//randomize pos, wont spawn outside, and wont spawn on 0
			for (int j = 0;j < i; j++) {//make sure that gem doesnt spawn on other gems
				if ((J + i)->posX == (J + j)->posX && (J + i)->posY == (J + j)->posY) {//compare
					canpass = false;//if theyre the same, dont let it pass
				}
			}
		} while (canpass = false);
		(J+i)->name = 'a'+i;//set the name to a+whatever the index before
	}
}

void drawgame(Player p, Jewels Jewelarray[], HANDLE h) {
	system("cls");
	SetConsoleTextAttribute(h, 15 | BACKGROUND_GREEN);//set text to be green background with white text
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 50; x++) {//for each coordinate
			if (y == p.posY && x == p.posX) {//if player position, draw player there
				SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
				std::cout << "P";
				
			}
			//draw each of the jewels if they arent colelcted
			else if (Jewelarray[0].Collected == false && y == Jewelarray[0].posY && x == Jewelarray[0].posX) {
						SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE);
						std::cout << Jewelarray[0].name;
			}
			else if (Jewelarray[1].Collected == false && y == Jewelarray[1].posY && x == Jewelarray[1].posX) {
				SetConsoleTextAttribute(h, 0 | BACKGROUND_GREEN);
				std::cout << Jewelarray[1].name;
			}
			else if (Jewelarray[2].Collected == false && y == Jewelarray[2].posY && x == Jewelarray[2].posX) {
				SetConsoleTextAttribute(h, 0 | BACKGROUND_GREEN | BACKGROUND_BLUE);
				std::cout << Jewelarray[2].name;
			}
			else if (Jewelarray[3].Collected == false && y == Jewelarray[3].posY && x == Jewelarray[3].posX) {
				SetConsoleTextAttribute(h, 0 | BACKGROUND_RED);
				std::cout << Jewelarray[3].name;
			}
			
			else {//else just do a dash in the blank spot
				SetConsoleTextAttribute(h, 15 | BACKGROUND_GREEN);//set text to be green background with white text
				std::cout << "-";
			}
			
		}
		std::cout << "\n";
	}
	resetcolor(h);//reset the color
}

void checkpos(Jewels* J, Player &p) {
	for (int i = 0; i < 4; i++) {//for each gem
		if ((p.posX == (J + i)->posX) && (p.posY == (J + i)->posY) && (J+i)->Collected==false) {//check if player matches a gems coords
			//and that its collected
			(J + i)->Collected = true;//if not collected, set collected to true
			p.JewelsCollected++;//increase amount of jewels player has collected
		}
	}
}

void resetcolor(HANDLE h) {
	SetConsoleTextAttribute(h, 15);//reset to white
}

void gameoverscreen(Player p, HANDLE h){
	system("cls");//clear screen
	resetcolor(h);
	if (p.JewelsCollected == 4) {//draw the gameover screen
		SetConsoleTextAttribute(h, 5);
		std::cout << "[] ";
		SetConsoleTextAttribute(h, 13);
		std::cout << "[] ";
		SetConsoleTextAttribute(h, 4);
		std::cout << "[] ";
		SetConsoleTextAttribute(h, 14);
		std::cout << "[] ";
		resetcolor(h);
		std::cout << "Well done!";
		SetConsoleTextAttribute(h, 14);
		std::cout << " [] ";
		SetConsoleTextAttribute(h, 4);
		std::cout << "[] ";
		SetConsoleTextAttribute(h, 13);
		std::cout << "[] ";
		SetConsoleTextAttribute(h, 5);
		std::cout << "[]";

		resetcolor(h);
		std::cout << "\n\nYou collected all four jewels!\n\n";
		std::cout << "     It took you " << p.moves << " moves!\n\n";
	}
	else {
		std::cout << "         Oh no! You quit!!\n\n";
	}

	SetConsoleTextAttribute(h, 5);
	std::cout << "[] ";
	SetConsoleTextAttribute(h, 13);
	std::cout << "[] ";
	SetConsoleTextAttribute(h, 4);
	std::cout << "[] ";
	SetConsoleTextAttribute(h, 14);
	std::cout << "[] ";
	resetcolor(h);
	std::cout << "Game Over!";
	SetConsoleTextAttribute(h, 14);
	std::cout << " [] ";
	SetConsoleTextAttribute(h, 4);
	std::cout << "[] ";
	SetConsoleTextAttribute(h, 13);
	std::cout << "[] ";
	SetConsoleTextAttribute(h, 5);
	std::cout << "[]";
	resetcolor(h);
}