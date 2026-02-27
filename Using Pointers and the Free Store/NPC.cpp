/* #include required headers here */
#include <stdlib.h>
#include <time.h>
#include <iostream>
struct NPC
{
	int Strength;
	int Health;
	int Tiredness;
	int Position_X;
	int Position_Y;

	bool Alive;
	/* Insert your code here */
};
void PrintNPCDetails(NPC* NPC);
void CreateNPC(NPC* NPC);
/* Insert Prototypes here */
int main()
{
	srand(time(0));
	// Declare NPC pointer array.
	NPC NPCArray[10];
	
	NPC* NPCPointer[10];
	for (int i = 0; i < sizeof(NPCArray) / sizeof(NPCArray[0]); i++) {
		NPCPointer[i] = &NPCArray[i];
	}
	// Call CreateNPC ten times, store the results.
	for (int i = 0; i < sizeof(NPCPointer) / sizeof(NPCPointer[0]); i++) {
		CreateNPC(NPCPointer[i]);
	}
	// Call PrintNPCDetails for each NPC in the array.
	for (int i = 0; i < sizeof(NPCPointer) / sizeof(NPCPointer[0]); i++) {
		PrintNPCDetails(NPCPointer[i]);
	}
	delete NPCPointer;
	for (int i = 0; i < sizeof(NPCArray) / sizeof(NPCArray[0]); i++) {
		NPCPointer[i] = 0;
	}
	//deallocate pointers
	return 0;
}
/* Insert function definitions here */
void PrintNPCDetails(NPC* NPC) {
	std::cout << "NPC's Current State:\n";
	std::cout << "- Position: (" << NPC->Position_X << ", " << NPC->Position_Y << ")\n";
	std::cout << "- Health: " << NPC->Health << "\n";
	std::cout << "- Strength: " << NPC->Strength << "\n";
	std::cout << "- Tiredness: " << NPC->Tiredness << "\n";
	std::cout << "- Alive: ";
	if (NPC->Alive == true) {
		std::cout << "yes";
	}
	else {
		std::cout << "false";
	}
	std::cout << "\n";
}
void CreateNPC(NPC* NPC) {
	
	NPC->Position_X = rand() % 101;//pos setup, goes up to 100
	NPC->Position_Y = rand() % 101;
	NPC->Strength = rand() % 18 + 3;//goes up to 20, minimum of 3
	NPC->Tiredness = rand() % 15 + 1;//goes up to 15, minimum of 1
	NPC->Health = rand() % 151 + 50;//goes up to 200, minimum of 50
	NPC->Alive = true;//alive state
}