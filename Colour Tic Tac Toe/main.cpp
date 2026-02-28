#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>

#include "gpcolourconsole.h"


void drawboard(char placements[], bool gamefinished, char winner, int currentturn);
void tictactoe();
void checkboard(char *placements,bool &gamefin, char& winner);
void main() {
	tictactoe();
}

void checkboard(char *placements, bool& gamefin,char& winner) {
	for (int i = 0; i < 3;i++) {
		int row = i * 3;
		if (tolower(placements[row]) == tolower(placements[row+1])
			&& tolower(placements[row]) == tolower(placements[row+2])){//three horiz winner
			placements[row] = toupper(placements[row]);//dont really need to change row on the right
			placements[row+1] = toupper(placements[row]);//because symbols will be the same anyway
			placements[row+2] = toupper(placements[row]);
			gamefin = true;
			winner = toupper(placements[row]);
		}
	}

	//check vertical ones
	for (int v = 0; v < 3; v++) {
		int col = v;
		if (tolower(placements[col]) == tolower(placements[col + 3])
			&& tolower(placements[col]) == tolower(placements[col + 6])) {//three column winner
			placements[col] = toupper(placements[col]);//dont really need to change row on the right
			placements[col+3] = toupper(placements[col]);//because symbols will be the same anyway
			placements[col + 6] = toupper(placements[col]);
			gamefin = true;
			winner = toupper(placements[col]);
		}
	}
	
	//check diagonal ones
	//since theres just two ill just hardcode it
	if (tolower(placements[0]) == tolower(placements[4])
		&& tolower(placements[0]) == tolower(placements[8])) {//three column winner
		placements[0] = toupper(placements[0]);//dont really need to change row on the right
		placements[4] = toupper(placements[0]);//because symbols will be the same anyway
		placements[8] = toupper(placements[0]);
		winner = toupper(placements[0]);
		gamefin = true;
	}

	if (tolower(placements[6]) == tolower(placements[4])
		&& tolower(placements[6]) == tolower(placements[2])) {//three column winner
		placements[6] = toupper(placements[6]);//dont really need to change row on the right
		placements[4] = toupper(placements[6]);//because symbols will be the same anyway
		placements[2] = toupper(placements[6]);
		winner = toupper(placements[6]);
		gamefin = true;
	}

}

void tictactoe() {
	bool gamefinished = false;//is game finished
	char playerinput;//store player input
	char winner; //the character of the winner will be stored here
	char placements[9] = { 'A','B','C','D','E','F','G','H','I' }; //initial placements, will be replaced with Os and Xs later
	char symbols[2] = { 'o','x' };//the two symbols
	int currentturn = 0;//start on 0
	drawboard(placements, gamefinished,' ', currentturn);
	do {
		playerinput = _getch();//get input
		switch (tolower(playerinput)) {//switch statements for each part of the grid
		case 'a':
			if (placements[0] != 'o' && placements[0] != 'x') {//if something isnt placed here yet
				placements[0] = symbols[currentturn];//then replace it
				currentturn = 1- currentturn;//and then swap the turn, otherwise do nothing and keep the turn the same
			}
			break;

		case 'b':
			if (placements[1] != 'o' && placements[1] != 'x') {
				placements[1] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		case 'c':
			if (placements[2] != 'o' && placements[2] != 'x') {
				placements[2] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		case 'd':
			if (placements[3] != 'o' && placements[3] != 'x') {
				placements[3] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		case 'e':
			if (placements[4] != 'o' && placements[4] != 'x') {
				placements[4] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		case 'f':
			if (placements[5] != 'o' && placements[5] != 'x') {
				placements[5] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		case 'g':
			if (placements[6] != 'o' && placements[6] != 'x') {
				placements[6] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		case 'h':
			if (placements[7] != 'o' && placements[7] != 'x') {
				placements[7] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		case 'i':
			if (placements[8] != 'o' && placements[8] != 'x') {
				placements[8] = symbols[currentturn];
				currentturn = 1 - currentturn;
			}
			break;

		}
		system("cls");//clear screen
		checkboard(placements, gamefinished, winner);//check if someones won
		drawboard(placements, gamefinished, winner,currentturn);//draw the board
	} while (gamefinished == false);
}

void drawboard(char placements[], bool gamefinished,char winner,int currentturn) {
	std::cout << "-----+-----+-----\n";
	for (int i = 0; i < 3; i++) {
		int row = i * 3;

		//the for prints things like so:
		//1) "     |"
		//2) "     |     |"
		//3) "     |     |     |"

		//filling in the color for each row until a full 3x3 grid is made making 3 squares

		//repeat 2 more times to have 9 squares total


		//empty row 1
		if (placements[row] == 'o') {//if o, then make red
			set_text_colour(15, 4);
		}
		else if (placements[row] == 'x') {//otherwise, x is blue
			set_text_colour(15, 1);
		}
		else if (placements[row] == 'X' || placements[row] == 'O') {//capital o or x means winner, so make it golden
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);//otherwise, make it regular colored
		}
		std::cout << "     "; //add spaces
		set_text_colour(15, 0);//dont color in the seperator
		std::cout << "|";//make the seperator regular colored

		//repeat for all next columns, making a 3 wide 1 tall row

		if (placements[row + 1] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row + 1] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row+1] == 'X' || placements[row+1] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "     ";
		set_text_colour(15, 0);
		std::cout << "|";

		if (placements[row + 2] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row + 2] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row+2] == 'X' || placements[row+2] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "     ";
		set_text_colour(15, 0);
		std::cout << "\n";




		//symbol row 2


		if (placements[row] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row] == 'X' || placements[row] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "  " << placements[row] << "  "; //place symbol here for column 1
		set_text_colour(15, 0);
		std::cout << "|";

		if (placements[row + 1] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row + 1] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row+1] == 'X' || placements[row+1] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "  " << placements[row + 1] << "  "; //place symbol here for column 2
		set_text_colour(15, 0);
		std::cout << "|";

		if (placements[row + 2] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row + 2] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row+2] == 'X' || placements[row+2] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "  " << placements[row + 2] << "  "; //place symbol here for column 2
		set_text_colour(15, 0);
		std::cout << "\n";


		//empty row 3

		//refer to row 1 comments


		if (placements[row] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row] == 'X' || placements[row] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "     ";
		set_text_colour(15, 0);
		std::cout << "|";

		if (placements[row + 1] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row + 1] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row + 1] == 'X' || placements[row + 1] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "     ";
		set_text_colour(15, 0);
		std::cout << "|";

		if (placements[row + 2] == 'o') {
			set_text_colour(15, 4);
		}
		else if (placements[row + 2] == 'x') {
			set_text_colour(15, 1);
		}
		else if (placements[row + 2] == 'X' || placements[row + 2] == 'O') {
			set_text_colour(0, 14);
		}
		else {
			set_text_colour(15, 0);
		}
		std::cout << "     ";
		set_text_colour(15, 0);
		std::cout << "\n";

		std::cout << "-----+-----+-----\n";

	
		

	}
	std::cout << "\n\n";//output current turn
	if (gamefinished == false) {//if  game is not finished
		std::cout << " Current turn: ";//output who the curren turn is
		if (currentturn == 0) {
			set_text_colour(15, 4);//red for o
			std::cout << "O";
		}
		else {
			set_text_colour(15, 1);//blue for x
			std::cout << "X";
		}
	}
	else {
		
		std::cout << "     ";//if game is finished
		set_text_colour(0, 14);
		std::cout << winner << " wins!";//print out whos the winner
	}
	set_text_colour(15, 0);
}

void set_text_colour(int foreground, int background)
{
	HANDLE console_window = GetStdHandle(STD_OUTPUT_HANDLE);
	int colour = ((background & 0x0F) << 4) |
		(foreground & 0x0F);
	SetConsoleTextAttribute(console_window, colour);
}
void move_cursor_to(int column, int row)
{
	HANDLE console_window = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = column;
	position.Y = row;
	SetConsoleCursorPosition(console_window, position);
}