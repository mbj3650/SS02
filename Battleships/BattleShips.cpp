#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>


struct pointer {
	int posX = 0;//position coords
	int posY = 0;

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
			if (posX < 9) {
				posX++;
			}
			break;
		default://if not wasd do nothing
			break;
		}
	}
};

struct ship {
	int size; //size of the ship
	bool vertical = false; //whether ship is vertical or not
	bool destroyed = false; //whether the ship is still alive or not
};
void botmove(std::string(*playerboard)[10][10], pointer cursor, char& botinput, bool& hitgood);
void move_cursor_to(int column, int row);
bool checkwinner(std::string(*playerboard)[10][10]);
bool hitboat(std::string(*playerboard)[10][10], pointer cursor);
void game();
void drawboard(std::string playerboard[10][10], pointer cursor, int turn);
void generateboard(std::string (*playerboard)[10][10]);
void main() {
	srand(time(0));
	
	game();
}


void game() {
	int turn = 1;//player turn at start
	pointer cursor;//player cursor
	pointer botcursor;//bot cursor
	std::string playerboard[10][10] = { {" "} };//player board starts empty
	std::string botboard[10][10] = { {" "} };//same with bot
	char input;//player input
	bool hitgood = false;//this lets bot know if previous turn was a hit
	bool gamefinish = false;//if game is finished
	char botinput = 'x';//starts at x, meaning pick a random spot
	std::string(*pointerboard)[10][10] = &playerboard;//pointer to boards
	std::string(*pointerbotboard)[10][10] = &botboard;//^


	generateboard(pointerboard);//generate boards
	generateboard(pointerbotboard);//generate bot boards
	drawboard(playerboard, cursor, 1);//draw player board at start
	do {
		if (turn == 1) {//if player turn
			do {
				_kbhit();
				input = _getch();//get input
				cursor.move(input);//move cursor according to input
				drawboard(playerboard, cursor,turn);//drawboard
			} while (tolower(input) != 'e');//e means hit that spot

			if (!hitboat(pointerboard,cursor)) {//if miss
				turn = 1 - turn;//swap turn
				drawboard(botboard, cursor, turn);//draw bot board
			}	
			else {//if hit
				if (checkwinner(pointerboard)) {//check if all ships are down
					move_cursor_to(15, 15);//if so then output win message
					std::cout << "\n\n PLAYER WINS!";
					gamefinish = true;//finish game
				}
				else {//if game isnt finished
					drawboard(playerboard, cursor, turn);//get another turn
				}
				
			}
			
			
		}
		else {
			_kbhit();
			input = _getch();//same thing but with bot
			botmove(pointerbotboard, botcursor, botinput, hitgood);//we dont need to call hit move here because bot does it until it stops
			drawboard(botboard, cursor, turn);//detecting it has hit moves
			if (checkwinner(pointerbotboard)) {//after its finished detecting, check if its won
				move_cursor_to(15, 15);//if so, output message
				std::cout << "\n\n BOT WINS!";
				gamefinish = true;
			}
			else {//else wait for user input before swapping screen
				input = _getch();//so they can see bot progress
				turn = 1 - turn;//swap turn
				drawboard(playerboard, cursor, turn);
				hitgood = false; //bot missed
			}
			
		}
		
		
	} while (input != 'q' && gamefinish == false);//wait until input is either q or game is fnished to leave
	
}

void botmove(std::string(*playerboard)[10][10], pointer cursor,char &botinput,bool &hitgood) {
	bool nomoves = false;
	char choices[4] = { 'w','a','s','d' };
	//hitboat(playerboard, cursor)
	do{
		if (hitgood == true) {//if previous move was a hit
			if (botinput == 'x') {//if bot a good hit but got it randomly
				int randomchoice = rand() % 4;
				botinput = (choices[randomchoice]);//pick a random direction
			}
			switch (botinput) {
			case 'a':
				if (cursor.posX == 0) {
					botinput = 'd';//go other way if at boundary
				}
				else {
					botinput = 'a';
				}
				cursor.move(botinput);//try a again
				break;
			case 's':
				if (cursor.posY == 9) {
					botinput = 'w';//go other way if at boundary
				}
				else {
					botinput = 's';
				}
				cursor.move(botinput);//try s again
				break;
			case 'd':
				if (cursor.posX == 9) {
					botinput = 'a';//go other way if at boundary
				}
				else {
					botinput = 'd';
				}
				cursor.move(botinput);//try d again
				break;
			case 'w':
				if (cursor.posY == 0) {
					botinput = 's';//go other way if at boundary
				}
				else {
					botinput = 'w';
				}
				cursor.move(botinput);//try w again
				break;
			}
			if (hitboat(playerboard, cursor)) {//if player was hit
				hitgood = true;//let bot know its previous move was a good one
			}
			else {//else tell it the move was bad
				hitgood = false;
				nomoves = false;//and its out of moves
			}

		}
		else {
			cursor.posY = rand() % 10;//pick random spot if previous move was bad
			cursor.posX = rand() % 10;
			if (hitboat(playerboard, cursor)) {//if move hit something, tell it to do something more consistent
				hitgood = true;
			}
			else {//else end turn
				hitgood = false;
				nomoves = false;
			}
		}
	} while(nomoves = false);
	
	
}
bool hitboat(std::string(*playerboard)[10][10], pointer cursor) {//check if cursor is on a "#" aka a boat part
	if ((*playerboard)[cursor.posY][cursor.posX] == "#") {//if on boat
		(*playerboard)[cursor.posY][cursor.posX] = "H";//replace with H for hit
		return true;//return true to say its hit
	}
	else {//if not hit
		(*playerboard)[cursor.posY][cursor.posX] = "M";//replace with m for Miss
		return false;//return false to say its not hit
	}
	
}

bool checkwinner(std::string(*playerboard)[10][10]) {//check if someones won
	bool iswinner = true;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if ((*playerboard)[i][j] == "#") {//if theres a single # on the board, that means theres still an unhit boat
				iswinner = false;
			}
		}
	}
	return iswinner;
}

void drawboard(std::string playerboard[10][10], pointer cursor, int turn) {
	system("cls");//clear screen
	std::cout << "CURSOR BATTLESHIPS\n\n\n";//draw title
	if (turn == 1) {
		std::cout << "PLAYER TURN: \n";//draw corresponding turn
	}
	else {
		std::cout << "BOT TURN: \n";
	}
	std::cout << "  0 1 2 3 4 5 6 7 8 9  \n";//draw grid
	for (int i = 0; i < 10; i++) {
		std::cout << char('A' + i);
		for (int j = 0; j < 10; j++) {
			//playerboard[cursor.posY][cursor.posX] = 'X';
			std::cout << " ";
			if (playerboard[i][j].empty() || playerboard[i][j] == "#") {//we dont actually want to show the boats, so make all #s invisible
				std::cout << " ";
			}
			else {
				std::cout << (playerboard[i][j]);
			}
			
		}
		std::cout << " " << char('A' + i) << "\n";
	}
	std::cout << "  0 1 2 3 4 5 6 7 8 9  \n";
	std::cout << "CURSOR LOCATED AT: "<< char('A'+cursor.posY) << char('0' + cursor.posX) << "\n";//tell cursor pos
	move_cursor_to(cursor.posX*2 + 2, cursor.posY+5);//move cursor there
}

void move_cursor_to(int column, int row)
{
	HANDLE console_window = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = column;
	position.Y = row;
	SetConsoleCursorPosition(console_window, position);
}

void generateboard(std::string(*playerboard)[10][10]) {//generate boart
	//create 5 template ships
	ship mini;
	mini.size = 2;
	mini.vertical = false;

	ship regular;
	regular.size = 3;
	regular.vertical = false;

	ship large;
	large.size = 4;
	large.vertical = false;

	ship sub;
	sub.size = 3;
	sub.vertical = true;

	ship battleship;
	battleship.size = 5;
	battleship.vertical = true;
	bool taken = false;
	int posX, posY;
	ship placements[] = { mini, regular, large, sub, battleship };

	//randomly place them
	for (int i = 0; i < 5; i++) {
		if (placements[i].vertical == false) {
			//std::cout <<i <<" i\n";
			do {//keep rerolling until a ship doesnt spawn inside another
				taken = false;
				posX = (rand() % (10 - placements[i].size));
				posY = (rand() % 10);
				for (int z = 0; z < placements[i].size;z++) {
					if ((*playerboard)[posY][posX + z] == "#") {
						taken = true;
					}
				}
			} while (taken == true);
			
			//std::cout << i << " i2123\n";
			for (int p = 0; p < placements[i].size; p++) {
				//std::cout << p << " i999\n";
				(*playerboard)[posY][posX + p] = '#';
			}
		}
		else {
			do {
				taken = false;
				posY = (rand() % (10 - placements[i].size));
				posX = (rand() % 10);
				for (int z = 0; z < placements[i].size; z++) {
					if ((*playerboard)[posY+z][posX] == "#") {
						taken = true;
					}
				}
			} while (taken == true);


			for (int p = 0; p < placements[i].size; p++) {
				(*playerboard)[posY+p][posX] = '#';
			}
		}
	}
}