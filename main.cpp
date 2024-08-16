#include <iostream>
using namespace std;

bool checkWinner(char *spaces, char marker);
void placeMarker(char *spaces, int spot, char marker);
void board(char *spaces, int size);

int main()
{
    char symbol;
    char player;
    char machine;
    char spaces[9] = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};
    int size = sizeof(spaces) / sizeof(spaces[0]);
    int playerSpot;
    int machineSpot;
    bool isPlay = true;

    do
    {
        cout << "Choose the symbol (X/O): ";
        cin >> symbol;
    } while (tolower(symbol) != 'x' && tolower(symbol) != 'o');

    if (tolower(symbol) == 'x')
    {
        player = 'x';
        machine = 'o';
    }
    else
    {
        player = 'o';
        machine = 'x';
    }

    // Inside your game loop
    do
    {
        // Player's turn
        do
        {
            cout << "Enter spot to place marker (1-9): ";
            cin >> playerSpot;
            if (spaces[playerSpot - 1] != '.')
            {
                cout << "Spot already taken. Choose another spot.\n";
            }
        } while (playerSpot < 1 || playerSpot > 9 || spaces[playerSpot - 1] != '.');

        placeMarker(spaces, playerSpot, player);

        if (checkWinner(spaces, player))
        {
            cout << endl;
            board(spaces, size);
            cout << endl;

            cout << "You won!" << endl;
            isPlay = false;
            break;
        }

        // Machine's turn
        srand(time(0));
        do
        {
            machineSpot = rand() % 9 + 1;
        } while (spaces[machineSpot - 1] != '.');

        placeMarker(spaces, machineSpot, machine);

        if (checkWinner(spaces, machine))
        {
            cout << endl;
            board(spaces, size);
            cout << endl;

            cout << "You lose!" << endl;
            isPlay = false;
            break;
        }

        cout << endl;
        board(spaces, size);
        cout << endl;

    } while (isPlay);

    return 0;
}

void placeMarker(char *spaces, int spot, char marker)
{
    spaces[spot - 1] = toupper(marker);
}

void board(char *spaces, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i != 0 && i % 3 == 0)
        {
            cout << endl;
            for (int i = 0; i < size + (3 * 2); i++)
            {
                cout << "—";
            }
            cout << endl;
        }

        cout << ' ' << spaces[i] << ' ';
        if (i % 3 != 2)
            cout << " | ";
    }
    cout << endl;
}

bool checkWinner(char *spaces, char marker)
{
    marker = toupper(marker);
    // Check rows
    for (int i = 0; i < 9; i += 3)
    {

        if ((spaces[i] == marker && spaces[i + 1] == marker && spaces[i + 2] == marker))
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {

        if (spaces[i] == marker && spaces[i + 3] == marker && spaces[i + 6] == marker)
        {
            return true;
        }
    }

    // Check diagonals
    if ((spaces[0] == marker && spaces[4] == marker && spaces[8] == marker) ||
        (spaces[2] == marker && spaces[4] == marker && spaces[6] == marker))
    {
        return true;
    }

    return false;
}