#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <random>

using namespace std;

class Player {
public:
	char* name;
	int score;
	int** board, **cBoard;
	int wins, losses, draws;
public:
	Player();
	Player(const char*, int, int, int);
	Player(Player&);
	~Player();
	//functions
	char* getName();
	void setName(char*);
	int getScore();
	void setScore(int);
	int** getBoard();
	void setBoard(int**&);
	void compGuess(int &,int &);
	void playGuess(int &, int &);
	Player& operator=(const Player&);
	friend ostream& operator<<(ostream&, const Player&);
	bool operator<(const Player&);
	bool operator>=(const Player&);
};

struct NOD {
	Player info;
}*List;

Player::Player() {
	name = 0;
	score = 0;
	board = 0;
	cBoard = 0;
	wins = losses = 0;
}

Player::Player(const char* name, int wins,int losses, int draws) {
	this->name = new char [strlen(name)+1];
	strcpy_s(this->name,strlen(name) + 1, name);
	this->score = 0;
	this->wins = wins;
	this->losses = losses;
	this->draws = draws;
}

Player::Player(Player& player) {
	name = new char[strlen(player.name) + 1];
	strcpy_s(name, strlen(name) + 1, player.name);
	score = player.score;
	board = new int* [9];
	cBoard = new int* [9];
	for (int i = 0; i < 9; i++) {
		board[i] = new int[9];
		cBoard[i] = new int[9];
		for (int j = 0; j < 9; j++) {
			board[i][j] = player.board[i][j];
			cBoard[i][j] = player.cBoard[i][j];
		}
	}
}

Player::~Player() {
	if (name) delete[] name;
	if (board != nullptr) {
		for (int i = 0; i < 9; i++)
			delete[]board[i];
		delete[] board;
	}
	if (cBoard != nullptr) {
		for (int i = 0; i < 9; i++)
			delete[]cBoard[i];
		delete[] cBoard;
	}
}

char* Player::getName() {
	return name;
}

void Player::setName(char* name) {
	if (this->name) delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

int Player::getScore() {
	return score;
}

void Player::setScore(int score) {
	this->score = score;
}

int** Player::getBoard() {
	return board;
}

void Player::setBoard(int**& board) {
	if (board != nullptr) {
		for (int i = 0; i < 9; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
	if (cBoard != nullptr) {
		for (int i = 0; i < 9; i++) {
			delete[] cBoard[i];
		}
		delete[] cBoard;
	}
	board = new int* [9];
	for (int i = 0; i < 9; i++) {
		board[i] = new int[9];
	}
	cBoard = new int* [9];
	for (int i = 0; i < 9; i++) {
		cBoard[i] = new int[9];
		for (int j = 0; j < 9; j++) {
			cBoard[i][j] = 0;
		}
	}
	int rx, ry, k = 5, simbol = 1;
	bool ok = false;
	while (k >= 2) {
		do {
			ok = false;
			random_device rand;
			uniform_int_distribution<int> xdist(0, (8 - k + 1));
			uniform_int_distribution<int> ydist(0, 8);
			rx = xdist(rand);
			ry = ydist(rand);
			for (int i = rx; i < rx + k; i++) {
				if (board[i][ry] != 0) {
					ok = true;
					break;
				}
			}
		} while (ok == false);
		for (int i = rx; i < rx + k; i++) {
			board[i][ry] = simbol;
		}
		k--;
		simbol++;
	}
}

void Player::compGuess(int &rx, int &ry) {
	random_device rand;
	uniform_int_distribution<int>dist(0, 8);
	rx = dist(rand);
	ry = dist(rand);
}

void Player::playGuess(int &gx,int &gy) {
	char guess[3];
	bool ok = true;
	while (ok) {
		cin.getline(guess, 3);
		gx = ((int)guess[0] - 5) % 10;
		gy = int(guess[1]) - 48;
		if ((gx >= 0 && gx <= 9) && (gy >= 0 && gy <= 9)) {
			ok = false;
		}
	}
	system("cls");
}

Player& Player::operator=(const Player& p) {
	if (this != &p) {
		if (name) delete[] name;
		name = new char[strlen(p.name) + 1];
		strcpy_s(name,strlen(p.name)+1,p.name);
		wins = p.wins;
		losses = p.losses;
		draws = p.draws;
	}
	return *this;
}

bool Player::operator<(const Player& p) {
	return (wins + (draws * 0.5)) / losses < (p.wins + (p.draws * 0.5)) / p.losses;
}

bool Player::operator>=(const Player& p) {
	return (wins + (draws * 0.5)) / losses > (p.wins + (p.draws * 0.5)) / p.losses;
}

ostream& operator<<(ostream& out, const Player& p) {
	out << p.name << "," << p.wins <<","<< p.losses << "," << p.draws << endl;
	return out;
}