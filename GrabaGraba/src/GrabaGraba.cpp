//============================================================================
// Name        : GrabaGraba.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
using namespace std;

////Graba-Graba! You are Minion Jerry! You and your Weapons Team buddies Kevin & Carl are
////playing a game of Graba-Graba. On a 15 x 15 factory floor, Dr. Nefario’s wacky weapons
////machine spits out weapons on the floor at random! The firepower and weapons it spits out are:
////1C FartGun, 9 ShrinkRay, 8, FreezeRay, 7 RocketLauncher, 6 Dynamite, 5 FireExtinguisher, 4 Axe,
////3 Scythe, 2 Cleaver, and 1 EggBeater. For each move you make, the probability each weapon
////will be spit out is inversely proportional to the firepower, meaning an EggBeater will appear
////every move, but a FartGun only every 1C moves! Also, for each move you make, Kevin & Carl
////also move. Kevin moves toward the strongest weapon nearby. Carl is not very smart, and
////simply moves at random. When you move into a sJuare with a weapon, it is added to your
////collection. Each round lasts 1C-2C seconds. Go for the gusto! Grab like an octopus!
////Make it simple & fun. Use structs Minion and Weapon. Minion contains the name and a
////Weapon pointer. The struct Weapon contains the weapon name, firepower, and another
////Weapon pointer. Link weapons from one to another in a chain (Optionally: from highest-tolowest).
////When the game is over, list the weapons and their total firepower.

struct weapon{
	string name;
	int firepower;
	weapon * next;
	int x;
	int y;
};

struct minion{
	string name;
	weapon *collected;
	int x;
	int y;
	char initial;
};

void board (const char Field[15][15]){
	for (int i=0; i<15; i++){
		for (int j=0; j<15; j++){
			cout<<" "<<Field[i][j]<<" ";
		}
		cout<<endl;
	}
}
char weaponCharacter(int firePower){
	switch(firePower){
		case 1:
		return '1';break;
		case 2:
		return '2';break;
		case 3:
		return '3';break;
		case 4:
		return '4';break;
		case 5:
		return '5';break;
		case 6:
		return '6';break;
		case 7:
		return '7';break;
		case 8:
		return '8';break;
		case 9:
		return '9';break;
		case 10:
		return '0';break;
		default:
		return ' ';break;
	}
}
//void spawnWeapon(char Field[][15], int& turn){
//	int weaponX = 0, weaponY = 0;
//	int filled=0;
//	for (int y=0; y<15; y++){
//		for (int x=0; x<15; x++){
//			if (Field[y][x] != ' ')
//				filled++;
//		}
//	}
//	if (filled<225){
//		for (int i=1; i<=turn; i++){
//			if (turn % i == 0){
//				do {
//					weaponX = rand()% 15; weaponY = rand()% 15;
//				}
//				while (Field[weaponY][weaponX] != ' ');
//				Field[weaponY][weaponX] = weaponCharacter(i);
//			}
//		}
//	}
//}
void collectWeapon (minion& NAME, weapon* found){
	if(NAME.collected == NULL){
		NAME.collected = found;
	}else{
		weapon* i = NAME.collected;
		for(; i->next != NULL; i = i->next){
		}
		i->next = found;
	}
}
void printCollectedWeapon (minion& NAME){
	if(NAME.collected == NULL){
		cout << "No weapon collected";
	}else{
		for(weapon * i = NAME.collected;i != NULL; i = i->next){
			if(i->next == NULL){
				cout << i->name;
			}else{
				cout << i->name << ", ";
			}
		}
	}
}
int calcWeaponCollection(minion& NAME){
	int total = 0;
	if(NAME.collected == NULL){
		return 0;
	}else{
		for(weapon * i = NAME.collected;i != NULL; i = i->next){
			total += i->firepower;
		}
		return total;
	}
}
void move(minion& JERRY, char Field[][15], char movePlayer, weapon WEAPON[10]){
	int pastX = JERRY.x, pastY = JERRY.y;
	int newX = pastX, newY = pastY;
	switch (movePlayer){
		case 'a':
			if (pastX != 0 && pastX-1 != 'K' && pastX-1 != 'C')
				newX = pastX-1;
			else if (pastX == 0)
				newX = pastX;
			break;
		case 'd':
			if (pastX != 14 && pastX+1 != 'K' && pastX+1 != 'C')
				newX = pastX+1;
			else if (pastX == 14)
				newX = pastX;
			break;
		case 'w':
			if (pastY != 0 && pastY-1 != 'K' && pastY-1 != 'C')
				newY = pastY-1;
			else if (pastY == 0)
				newY = pastY;
			break;
		case 's':
			if (pastY != 14 && pastY+1 != 'K' && pastY+1 != 'C')
				newY = pastY+1;
			else if (pastY == 14)
				newY = pastY;
			break;
	}
	if (Field[newY][newX] == ' '){
		Field[newY][newX] = JERRY.initial;
		Field[pastY][pastX] = ' ';
	}
	else {
		Field[pastY][pastX]= ' ';
		Field[newY][newX] = JERRY.initial;
		//copy weapon in map as a new object
		weapon* found = new weapon;
		found->name = WEAPON->name;
		found->firepower = WEAPON->firepower;
		found->next = NULL;
		//collect weapon
		collectWeapon(JERRY, found);
	}
	JERRY.x = newX; JERRY.y = newY;
}
void spawnCarl (minion& CARL, char Field[][15]){
	do{
		CARL.x = rand()% 15; CARL.y = rand()% 15;
	}
	while (Field[CARL.y][CARL.x] != ' ');
}
void spawnKevin (minion& KEVIN, char Field[][15]){
	do{
		KEVIN.x = rand()% 15; KEVIN.y = rand()% 15;
	}
	while (Field[KEVIN.y][KEVIN.x] != ' ');
}
void spawnJerry (minion& JERRY, char Field[][15]){
	do{
		JERRY.x = rand()% 15; JERRY.y = rand()% 15;
	}
	while (Field[JERRY.y][JERRY.x] != ' ');
}
void moveCarl (minion& CARL, char Field[][15], weapon WEAPON[10]){
	int pastX = CARL.x, pastY = CARL.y;
	int newX = pastX, newY = pastY;
	do{
		int random = rand()% 4;
		if (random==0 && pastX!=0){ //a
			newX = pastX-1;
		}
		else if (random==1 && pastX!=14){ //d
			newX = pastX+1;
		}
		else if (random==2 && pastY!=0){ //w
			newY = pastY-1;
		}
		else if (random==3 && pastY!=14){ //s
			newY = pastY+1;
		}
	}
	while (Field[newY][newX] == 'K' && Field[newY][newX] == 'J');
	if (Field[newY][newX] == ' '){
		Field[newY][newX] = CARL.initial;
		Field[pastY][pastX] = ' ';
	}
	else {
		Field[pastY][pastX]= ' ';
		Field[newY][newX] = CARL.initial;
		//copy weapon in map as a new object
		weapon* found = new weapon;
		found->name = WEAPON->name;
		found->firepower = WEAPON->firepower;
		found->next = NULL;
		//collect weapon
		collectWeapon(CARL, found);
	}

	CARL.x = newX; CARL.y = newY;
}
void moveKevin (minion& KEVIN, char Field[][15], weapon WEAPON[10]){
	int pastX = KEVIN.x, pastY = KEVIN.y;
	int newX = pastX, newY = pastY;
	//Find weapon with biggest score in Field
	int weaponX = 0, weaponY = 0;
	int power=0;
	for (int i=0; i<15; i++){
		for (int j=0; j<15; j++){
			for (int k=0; k<15; k++){
				if (WEAPON[k].firepower > power){
					power = WEAPON[k].firepower;
					weaponX = j;
					weaponY = i;
				}
			}
		}
	}
		// decide kevin movement
		if (KEVIN.x>weaponX ){
			//left
			newX = pastX - 1;
			if (Field[newY][newX] == 'C' || Field[newY][newX] == 'K'){
				if (KEVIN.y<weaponY && (Field[pastY+1][pastX] != 'C' || Field[pastY+1][pastX] != 'J')){
					//down
					newY = pastY + 1;
					newX = pastX;
				}else if (KEVIN.y>weaponY && (Field[pastY-1][pastX] != 'C' || Field[pastY-1][pastX] != 'J')){
					//up
					newY = pastY - 1;
					newX = pastX;
				}
				// else condition it wont move
				else {
					newX = pastY;
					newY = pastX;
				}
			}
		}
		else if (KEVIN.x<weaponX){
			//right
			newX = pastX + 1;
			newY = pastY;
			if (Field[newY][newX] == 'C' || Field[newY][newX] == 'J' ){
				if (KEVIN.y<weaponY && (Field[pastY+1][pastX] != 'C' || Field[pastY+1][pastX] != 'J')){
					//down
					newY = pastY + 1;
					newX = pastX;
				}else if (KEVIN.y>weaponY && (Field[pastY-1][pastX] != 'C' || Field[pastY-1][pastX] != 'J')){
					//up
					newY = pastY - 1;
					newX = pastX;
				}
				// else condition it wont move
				else{
					newX = pastX;
					newY = pastY;
				}
			}
		}
		else{
			if (KEVIN.y<weaponY){
				//down
				newY = pastY + 1;
				newX = pastX;
				if (Field[newY][newX] == 'C' || Field[newY][newX] == 'J' ){
					//right
					if (Field[pastY][pastX+1] != 'C' || Field[pastY][pastX+1] != 'J'){
						newX = pastX + 1;
						newY = pastY;
					}
					//left
					else {
						newX = pastX - 1;
						newY = pastY;
					}
				}
			}
			else if (KEVIN.y>weaponY){
				//up
				newY = pastY - 1;
				newX = pastX;
				if (Field[newY][newX] == 'C' || Field[newY][newX] == 'J' ){
					if (Field[pastY][pastX+1] != 'C' || Field[pastY][pastX+1] != 'J'){
						//right
						newX = pastX + 1;
						newY = pastY;
					}
					//left
					else {
						newX = pastX - 1;
						newY = pastY;
					}
				}
			}
		}
	if (Field[newY][newX] == ' '){
		Field[newY][newX] = KEVIN.initial;
		Field[pastY][pastX] = ' ';
	}
	else {
		Field[pastY][pastX]= ' ';
		Field[newY][newX] = KEVIN.initial;
		//copy weapon in map as a new object
		weapon* found = new weapon;
		found->name = WEAPON->name;
		found->firepower = WEAPON->firepower;
		found->next = NULL;
		//collect weapon
		collectWeapon(KEVIN, found);
	}
	KEVIN.x = newX; KEVIN.y = newY;
}
void compare(minion& KEVIN, minion& JERRY, minion& CARL){
	int jerryScore = calcWeaponCollection(JERRY);
	int kevinScore = calcWeaponCollection(KEVIN);
	int carlScore = calcWeaponCollection(CARL);

	int scoreArray[3] = {jerryScore, kevinScore, carlScore};
	int bestScore = 0;
	int winner =0;
	//find best score
	for(int i = 0; i < 3; i++){
		if(scoreArray[i] > bestScore){
			bestScore = scoreArray[i];
		}
	}

	//find number of winner
	if(bestScore == jerryScore){
		winner++;
	}
	if(bestScore == kevinScore){
		winner++;
	}
	if(bestScore == carlScore){
		winner++;
	}

	cout << endl << endl << endl;
	//print message
	if(winner == 1){
		if(bestScore == jerryScore){
			cout << "              CONGRATULATION JERRY, YOU ARE THE WINNER! with a score of "<<bestScore;
		}else if(bestScore == kevinScore){
			cout << "              CONGRATULATION KEVIN, YOU ARE THE WINNER!"<<bestScore;
		}else{
			cout << "              CONGRATULATION CARL, YOU ARE THE WINNER!"<<bestScore;
		}
	}else if(winner == 3){
		cout << "              IT'S A TIE!"<<bestScore;
	}else{
		if(bestScore == jerryScore && bestScore == kevinScore){
			cout << "              CONGRATULATION JERRY AND KEVIN, YOU ARE THE WINNER!"<<bestScore;
		}else if(bestScore == jerryScore && bestScore == carlScore){
			cout << "              CONGRATULATION JERRY AND CARL, YOU ARE THE WINNER!"<<bestScore;
		}else if(bestScore == kevinScore && bestScore == carlScore){
			cout << "              CONGRATULATION KEVIN AND CARL, YOU ARE THE WINNER!"<<bestScore;
		}
	}
}

int main() {
	srand (time(NULL));
	// Assigning the Field
	char Field[15][15];
	for (int i=0; i<15; i++){
		for (int j=0; j<15; j++){
			Field[i][j]=' ';
		}
	}
	int turn = 0;
	int jerryScore =0, kevinScore = 0, carlScore =0;
	char movePlayer;

	//create minions
	minion JERRY ={"JERRY", NULL, 8, 8,'J'};
	spawnJerry (JERRY, Field);
	Field[JERRY.y][JERRY.x] = JERRY.initial;

	minion KEVIN ={"KEVIN", NULL, 14, 14, 'K'};
	spawnKevin (KEVIN, Field);
	Field[KEVIN.y][KEVIN.x] = KEVIN.initial;

	minion CARL = {"CARL", NULL, 0, 0, 'C'};
	spawnCarl (CARL, Field);
	Field[CARL.y][CARL.x] = CARL.initial;

	//weapon declaration
	weapon WEAPON[10];
	WEAPON[0].name = "EggBeater";
	WEAPON[1].name = "Cleaver";
	WEAPON[2].name = "Scythe";
	WEAPON[3].name = "Axe";
	WEAPON[4].name = "FireExtinguisher";
	WEAPON[5].name = "Dynamite";
	WEAPON[6].name = "RocketLauncher";
	WEAPON[7].name = "FreezeRay";
	WEAPON[8].name = "ShrinkRay";
	WEAPON[9].name = "FartGun";
	for (int i=1; i<10; i++){
		WEAPON[i].firepower = i+1;
		WEAPON[i].next = NULL;
	}
    int seconds;

    cout << "Enter the number of seconds: ";
    cin >> seconds;
    cout << "Start ... " << endl << flush;

    time_t start_time = time(nullptr);
    while ( (time(nullptr) - start_time) < seconds){
    	int weaponX=0, weaponY=0;
    	jerryScore = calcWeaponCollection(JERRY);
    	kevinScore = calcWeaponCollection(KEVIN);
    	carlScore = calcWeaponCollection(CARL);
    	board(Field);
    	cout<<"JerryScore is : "; printCollectedWeapon(JERRY); cout<<endl;
    	cout<<"CarlScore is : "; printCollectedWeapon(CARL); cout<<endl;
    	cout<<"KevinScore is : "; printCollectedWeapon(KEVIN); cout<<endl;
    					do {
    						weaponX = rand()% 15; weaponY = rand()% 15;
    					}
    					while (Field[weaponY][weaponX] != ' ');
    					Field[weaponY][weaponX] = '1';
//    	spawnWeapon(Field, turn);
    	cout<<endl<<"Pick your choice of move"; cin>>movePlayer; cout<<endl;
    	move (JERRY, Field, movePlayer, WEAPON);
    	moveCarl (CARL, Field, WEAPON);
    	moveKevin (KEVIN, Field, WEAPON);
    }
    board (Field);
	cout<<"JerryScore is : "; printCollectedWeapon(JERRY); cout<<endl;
	cout<<"CarlScore is : "; printCollectedWeapon(CARL); cout<<endl;
	cout<<"KevinScore is : "; printCollectedWeapon(KEVIN); cout<<endl;
    compare (KEVIN, JERRY, CARL);

	return 0;
}


