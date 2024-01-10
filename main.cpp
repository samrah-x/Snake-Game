#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Declaring variables
bool GameOver;

// dimensions of game board
const int width = 50;
const int height = 20;

// snake head coords
int x, y;

// fruit coords;
int fruitX, fruitY;

// score variable
int score;

// tail array
int TailX[100] , TailY[100];

//tail length
int tail_length;

// direction
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};

eDirection dir;

// Function to initialize variables
void Setup (void)
{
    GameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// Function to draw
void GameBoard (void)
{
    system("cls"); 
    for (int i = 0; i < width + 2; i++)
        cout << "_";
    cout << endl;

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            if (j == 0)
            {
                cout << "|";
            }
            if (j == x && i == y)
            {
                cout << "O";
            }
            else if (j == fruitX && i == fruitY)
            {
                cout << "x";
            }
            else 
            {
                bool print = false;
                for (int k = 0 ; k < tail_length ; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    {
                        cout << " ";
                    }
            }
            if (j == width -1)
            {
                cout << "|";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
    {
        cout << "_";
    }
    cout << endl;
    cout << "Score: " <<score <<endl;
}

// Function to get input
void Input (void)
{
    if (_kbhit())
    {
        switch(_getch())
        {
        case 'a': 
            dir = LEFT;
            break;
        case 's': 
            dir = DOWN;
            break;
        case 'd': 
            dir = RIGHT;
            break;
        case 'w': 
            dir = UP;
            break;
        default:
            break;
        }
    }
}

// Function for logic
void Logic (void)
{
    int prevx = TailX[0];
    int prevy = TailY[0];
    int prev2x, prev2y;
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1 ; i < tail_length; i++)
    {
        prev2x = TailX[i];
        prev2y = TailY[i];
        TailX[i] = prevx;
        TailY[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case DOWN:
        y++;
        break;
    case UP:
        y--;
        break;
    default:
        break;
    }

    // redirect
        if (x >= width) x = 0; else if (x < 0) x = width - 1; 
        else if (y >= height) y = 0; else if (y < 0) y = height - 1; 

    // Game Over condition
    for (int i = 0; i < tail_length; i++)
    {
        if (TailX[i] == x && TailY[i] == y)
        {
            GameOver = true;
        }
    }
    
    if (x == fruitX && y == fruitY)
    {
        tail_length++;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score+= 10;
    }
}
// Function for difficulty

// Main Function
int main ()
{
    Setup();
    while (!GameOver)
    {
        GameBoard();
        Input();
        Logic();
        Sleep(10);
    }
    return 0;
}