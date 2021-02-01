#include <conio.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
using namespace std;
int x = 0;
int y = 0;
int enemy = 5;
int self = 5;

void cls(HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE))
{
    COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}

string spaces(int a) {
    string res;
    for (int i = 0; i < a; i++) {
        res += ' ';
    }
    return res;
}

void scoreboard(int enemy, int self) {
    cout << "Enemy HP: " << enemy << endl;
    cout << "Your HP: " << self << endl;
}

void nextLine(int a) {
    for (int i = 0; i < a; i++) {
        cout << endl;
    }
}
void showPlayer(int x, int y) {
    scoreboard(enemy, self);
    nextLine(y+1);
    string margin = spaces(x);
    cout << margin << " o   o" << endl;
    cout << margin << "/|\\ /|\\" << endl;
    cout << margin << "/ \\ / \\" << endl;
}

#include <random>

typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 7);

rng_type rng;

int isHit()
{
    // seed rng first:
    rng_type::result_type const seedval = time(NULL); // get this from somewhere
    rng.seed(seedval);

    rng_type::result_type random_number = udist(rng);

    return (random_number) % 3;
}

void hit(int x, int y) {
    if (isHit() == 1) {
        enemy--;
    } else if (isHit() == 2) {
        self--;
    }
    scoreboard(enemy, self);
    nextLine(y);
    string margin = spaces(x);
    cout << margin << " Ha!" << endl;
    cout << margin << " o_  o" << endl;
    cout << margin << "/|  /|\\" << endl;
    cout << margin << "/ \\  |\\" << endl;
    cout << "+---------------+" << endl;
    cout << "| You used hit! |" << endl;
    cout << "+---------------+" << endl;
}

void bomb(int x, int y) {
    if (isHit() == 1) {
        enemy-=2;
    } else if (isHit() == 2) {
        self-=2;
    }
    scoreboard(enemy, self);
    nextLine(y);
    string margin = spaces(x);
    cout << margin << " Ha!~o" << endl;
    cout << margin << " o_  o" << endl;
    cout << margin << "/|  /|\\" << endl;
    cout << margin << "/ \\  |\\" << endl;
    cout << "+----------------+" << endl;
    cout << "| You used bomb! |" << endl;
    cout << "+----------------+" << endl;
}

int main() {
    while (true) {
        cls();
        cout << "KONG-FU ARENA" << endl;
        cout << "You are fighting against the strongest man - Pixel." << endl;
        cout << "He is substantially strong, so your attacks might be reflected." << endl;
        cout << "Attacks:" << endl;
        cout << "Bomb: B" << endl;
        cout << "Hit: H" << endl;
        if (enemy <= 0) {
            cout << "You won!" << endl;
            return 0;
        }
        if (self <= 0) {
            cout << "You lost..." << endl;
            return 0;
        }
        showPlayer(x, y);
        char key = getch();
        cls();
        if ((int)key == LEFT) {
            if (x > 0) {
                x -= 1;
            }
            showPlayer(x, y);
        } else if ((int)key == RIGHT) {
            x += 1;
            showPlayer(x, y);
        } else if ((int)key == UP) {
            if (y > 0) {
                y -= 1;
            }
            showPlayer(x, y);
        } else if ((int)key == DOWN) {
            y += 1;
            showPlayer(x, y);
        } else if (key == 'h') {
            cout << "KONG-FU ARENA" << endl;
            cout << "You are fighting against the strongest man - Pixel." << endl;
            cout << "He is substantially strong, so your attacks might be reflected." << endl;
            cout << "Attacks:" << endl;
            cout << "Bomb: B" << endl;
            cout << "Hit: H" << endl;
            hit(x, y);
            system("PING localhost -n 4 >NUL");
        } else if (key == 'b') {
            cout << "KONG-FU ARENA" << endl;
            cout << "You are fighting against the strongest man - Pixel." << endl;
            cout << "He is substantially strong, so your attacks might be reflected." << endl;
            cout << "Attacks:" << endl;
            cout << "Bomb: B" << endl;
            cout << "Hit: H" << endl;
            bomb(x, y);
            system("PING localhost -n 4 >NUL");
        }
    }
}