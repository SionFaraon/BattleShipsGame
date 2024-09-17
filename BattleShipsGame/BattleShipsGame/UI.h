#pragma once
#include "Players.h"

class UI {
public:
	int mainMenu();
	void PlayerVSPlayer(Player&, Player&);
	void PlayerVSComputer(Player&, Player&, NOD*, int);
	void InGameBoard(Player&);
	bool Win(Player&, Player&);
	void updBoard(Player&, Player&, int, int);
	void Decision(Player&, Player&);
};

int UI::mainMenu() {
	cout << "\t BattleShips" << endl;
	cout << "1. Player vs. Player" << endl;
	cout << "2. Player vs. Computer" << endl;
	cout << "3. Leaderboard" << endl;
	cout << "4. Exit" << endl;
	int number;
	cin >> number;
	system("cls");
	return number % 5;
}

void UI::PlayerVSPlayer(Player& p1, Player& p2) {
	cout << "\t Player vs. Player" << endl;
	char* name1, * name2;
	cout << "Player 1 : ";
	name1 = new char[30];
	cin.get();
	cin.getline(name1, 30);
	cout << "Player 2 : ";
	name2 = new char[30];
	cin.getline(name2, 30);
	p1.setName(name1);
	p2.setName(name2);
	system("cls");
}

void UI::PlayerVSComputer(Player& p, Player &c, NOD* list, int total) {
	cout << "\t Player vs. Computer" << endl;
	char* name;
	cout << "Player : ";
	name = new char[30];
	cin.get();
	cin.getline(name, 30);
	p.setName(name);
	random_device rand;
	uniform_int_distribution<int> dist(0, total-1);
	c.operator=(list[dist(rand)].info);
	cout << "Computer :  " << c.getName() << endl;
	system("pause");
	system("cls");
}

void UI::InGameBoard(Player& player) {
	cout << "\t" << player.getName() << "'s turn" << endl;
	cout << "Hit map ---" << endl;
	cout << "  ";
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << " ";
	}
	cout << endl;
	for (int i = 0; i < 9; i++) {
		cout << char(65 + i) << " ";
		for (int j = 0; j < 9; j++) {
			if (player.cBoard[i][j] == 0)
				cout << "  ";
			else {
				cout << "X ";
			}
		}
		cout << endl;
	}
	cout << "Radar ---" << endl;
	cout << "  ";
	for (int i = 0; i < 9; i++) {
		cout << i + 1 << " ";
	}
	cout << endl;
	for (int i = 0; i < 9; i++) {
		cout << char(65 + i) << " ";
		for (int j = 0; j < 9; j++) {
			if (player.board[i][j] == 1)
				cout << "A ";
			else if (player.board[i][j] == 2)
				cout << "B ";
			else if (player.board[i][j] == 3)
				cout << "C ";
			else if (player.board[i][j] == 4)
				cout << "D ";
			else if (player.board[i][j] == 5)
				cout << "X ";
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << "5xA - Aircraft Carrier | 4xB - Battleship | 3XC - Cruiser | 2xD - Distroyer" << endl;
	cout <<"Score : " << player.getScore() << endl;
	cout << "Record : " << player.wins << "w - " << player.losses << "l - " << player.draws << "d" << endl;
	cout << "Your hit : ";
}

bool UI::Win(Player &player1, Player &player2) {
	bool p1win = true, p2win = true;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if(player1.board[i][j] >= 1 && player1.board[i][j] <= 4)
				p1win = false;
			if (player2.board[i][j] >= 1 && player2.board[i][j] <= 4)
				p2win = false;
		}
	}
	if (p1win == false && p2win == false)
		return false;
	return true;
}


void UI::updBoard(Player& p1, Player &p2, int gx, int gy) {
	if (p2.board[gx][gy] > 0 && p2.board[gx][gy] < 5)
		p1.score += 1;
	p2.board[gx][gy] = 5;
	p1.cBoard[gx][gy] = 1;
}

void UI::Decision(Player& p1, Player& p2) {
	if (p1.score > p2.score) {
		cout << "\t WINNER" << endl;
		p1.wins++;
		p2.losses++;
	}
	else if (p1.score < p2.score) {
		cout << "\t\t\t WINNER" << endl;
		p1.losses++;
		p2.wins++;
	}
	else {
		cout << "\t\t DRAW" << endl;
		p1.draws++;
		p2.draws++;
	}
	cout << "\t" << p1.getName() << "\t\t" << p2.getName() << endl;
	system("pause");
	system("cls");
}