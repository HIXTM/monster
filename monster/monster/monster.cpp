#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 30;
const int height = 15;
char playArea[height][width];

struct Player {
    int x, y;
};

struct Monster {
    int x, y;
};

Player player;
Monster monster;
vector<pair<int, int>> coins;

void setup() {
    player.x = 1;
    player.y = 1;
    monster.x = width - 2;
    monster.y = height - 2;

    srand(time(0));
    for (int i = 0; i < 7; i++) {
        coins.push_back({ rand() % (height - 2) + 1, rand() % (width - 2) + 1 });
    }

    // Установка стен
    for (int i = 0; i < width; i++) {
        playArea[0][i] = playArea[height - 1][i] = '#'; // Верх и низ
    }
    for (int i = 1; i < height - 1; i++) {
        playArea[i][0] = playArea[i][width - 1] = '#'; // Лево и право
    }
}

void draw() {
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == player.y && j == player.x) {
                cout << 'P'; 
            }
            else if (i == monster.y && j == monster.x) {
                cout << 'M'; 
            }
            else {
                bool coinFound = false;
                for (auto& coin : coins) {
                    if (coin.first == i && coin.second == j) {
                        cout << 'C';
                        coinFound = true;
                        break;
                    }
                }
                if (!coinFound) {
                    cout << (playArea[i][j] == '#' ? '#' : '.');
                }
            }
        }
        cout << endl;
    }
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w': if (playArea[player.y - 1][player.x] != '#') player.y--; break;
        case 's': if (playArea[player.y + 1][player.x] != '#') player.y++; break;
        case 'a': if (playArea[player.y][player.x - 1] != '#') player.x--; break;
        case 'd': if (playArea[player.y][player.x + 1] != '#') player.x++; break; 
        case 'x': exit(0); 
        }
    }
}

void logic() {
    if (player.x > monster.x) monster.x++;
    else if (player.x < monster.x) monster.x--;

    if (player.y > monster.y) monster.y++;
    else if (player.y < monster.y) monster.y--;


    if (player.x == monster.x && player.y == monster.y) {
        cout << "Game Over! The monster caught you!" << endl;
        exit(0);
    }

    for (auto it = coins.begin(); it != coins.end();) {
        if (it->first == player.y && it->second == player.x) {
            it = coins.erase(it);
        }
        else {
            ++it;
        }
    }

    if (coins.empty()) {
        cout << "Congratulations! You've collected all the coins!" << endl;
        exit(0);
    }
}

int main() {
    setup();
    while (true) {
        draw();
        input();
        logic();
        Sleep(300);
    }
    return 0;
}