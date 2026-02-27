/* #include required headers here */


#include <iostream>
struct Player
{
	int pos[2];
	int Health;
	bool Alive;
	/* Insert your code here */
};
/* Insert Prototypes here */
void SetupPlayer(Player* Player);
void PrintPlayerDetails(const Player* Playerinfo);
int main()
{
	Player player1,player2; //Setup player1 and 2
	PrintPlayerDetails(&player1);//at this time, all values are uninitialized, with all int details being -858993460
	PrintPlayerDetails(&player2);//and alive will be false

	SetupPlayer(&player1);//sets up the players
	SetupPlayer(&player2);

	PrintPlayerDetails(&player1);//now position will be 0 and health with be 100
	PrintPlayerDetails(&player2);//and alive will be true
	return 0;
}
/* Insert function definitions here */
void SetupPlayer(Player* Player) {//sets up all info
	Player->pos[0] = 0;//pos setup
	Player->pos[1] = 0;
	Player->Health = 100;//health 
	Player->Alive = true;//alive state
}

void PrintPlayerDetails(const Player* Playerinfo) {
	//prints out info
	std::cout << "Player's Current State:\n";
	std::cout << "- Position: (" << Playerinfo->pos[0] << ", " << Playerinfo->pos[1] << ")\n";
	std::cout << "- Health: "<< Playerinfo->Health<< "\n";
	std::cout << "- Alive: "; 
	if (Playerinfo->Alive == true) {
		std::cout << "yes";
	}
	else {
		std::cout << "false";
	}
	std::cout << "\n";
}
