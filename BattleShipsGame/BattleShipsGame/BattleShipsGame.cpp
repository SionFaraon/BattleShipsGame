#include "UI.h"

void Create(NOD *&list, int &i) {
	ifstream in("Leaderboard.txt");
	list = new (nothrow) NOD[30];
	if (list == nullptr) {
		cout << "Alocare esuata" << endl;
		exit(1);
	}
	char line[30];
	i = 0;
	while (in.getline(line, 30)) {
		char* name, * nxt;
		int w, l, d;
		char* p = strtok_s(line, ",", &nxt);
		name = p;
		p = strtok_s(nullptr, ",", &nxt);
		w = atoi(p);
		p = strtok_s(nullptr, ",", &nxt);
		l = atoi(p);
		p = strtok_s(nullptr, ",", &nxt);
		d = atoi(p);
		Player player(name, w, l, d);
		list[i].info.operator=(player);
		i++;
	}
	in.close();
}

void Sort(NOD* &list, int total) {
	int s = 0; 
	while (s == 0) {
		s = 1;
		for (int i = 0; i < total - 1; i++) {
			if (list[i].info.operator<(list[i + 1].info)) {
				Player aux;
				aux.operator=(list[i].info);
				list[i].info.operator=(list[i + 1].info);
				list[i + 1].info.operator=(aux);
				s = 0;
			}
		}
	}
}

void InFile(NOD* list, int total) {
	ofstream out("Leaderboard.txt");
	for (int i = 0; i < total; i++) {
		out << list[i].info;
	}
	out.close();
}

void Search(NOD* list, int total, Player& player, int &index) {
	for (int i = 0; i < total; i++) {
		char* l, * p;
		bool ok = true;
		l = list[i].info.getName();
		p = player.getName();
		while (*l == *p) {
			if (*l == '\0')
				ok = false;
			l++;
			p++;
		}
		if (ok == false) {
			player.operator=(list[i].info);
			index = i;
			break;
		}
	}
}

int main() {
	NOD* list;
	int total;
	Create(list, total);
	UI game;
	int gamemode;
	do {
		gamemode = game.mainMenu();
		if (gamemode == 1) {
			Player player1, player2;
			int p1index = -1, p2index = -1;
			game.PlayerVSPlayer(player1, player2);
			Search(list, total, player1, p1index);
			Search(list, total, player2, p2index);
			player1.setBoard(player1.board);
			system("pause");
			system("cls");
			player2.setBoard(player2.board);
			while (game.Win(player1, player2) == false) {
				int x, y;
				cout << "Waiting for " << player1.getName() << endl;
				system("pause");
				system("cls");
				game.InGameBoard(player1);
				player1.playGuess(x, y);
				game.updBoard(player1, player2, x, y - 1);
				cout << "Waiting for " << player2.getName() << endl;
				system("pause");
				system("cls");
				game.InGameBoard(player2);
				player2.playGuess(x, y);
				game.updBoard(player2, player1, x, y - 1);
			}
			game.Decision(player1, player2);
			if (p1index != -1)
				list[p1index].info.operator=(player1);
			else {
				total++;
				list[total - 1].info.operator=(player1);
			}
			if (p2index != -1)
				list[p2index].info.operator=(player2);
			else {
				total++;
				list[total - 1].info.operator=(player2);
			}
		}
		if (gamemode == 2) {
			Player player, computer;
			int pindex = -1, comindex = -1;
			game.PlayerVSComputer(player, computer, list, total);
			Search(list, total, player, pindex);
			Search(list, total, computer, comindex);
			computer.setBoard(computer.board);
			cout << "Waiting for " << player.getName() << endl;
			system("pause");
			system("cls");
			player.setBoard(player.board);
			while (game.Win(player, computer) == false) {
				int x, y;
				game.InGameBoard(player);
				player.playGuess(x, y);
				game.updBoard(player, computer, x, y - 1);
				system("pause");
				system("cls");
				computer.compGuess(x, y);
				game.updBoard(computer, player, x, y - 1);
			}
			game.Decision(player, computer);
			if (pindex != -1)
				list[pindex].info.operator=(player);
			else {
				total++;
				list[total - 1].info.operator=(player);
			}
			list[comindex].info.operator=(computer);
		}
		if (gamemode == 3) {
			Sort(list, total);
			cout << "\tLeaderboard" << endl;
			for (int i = 0; i < total; i++) {
				cout << i + 1 << ". " << list[i].info.getName() << "\t" << list[i].info.wins << "w - " << list[i].info.losses << "l - " << list[i].info.draws << "d" << endl;
			}
			system("pause");
			system("cls");
		}
		InFile(list, total);
		system("cls");
	} while (gamemode != 4);
	return 0;
}