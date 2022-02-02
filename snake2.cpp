#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#define LENGTH 30
#define HEIGHT 20
#define SNAKE_LENGTH_INIT 3
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
using namespace std;

class snake
{
private:
    class cordinats
    {
    public:
        int X;
        int Y;
    };
    char a[LENGTH + 2][HEIGHT + 2];
    cordinats body[LENGTH * HEIGHT];
    cordinats apple;
    cordinats fil[LENGTH * HEIGHT];
    int direction;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int length;
    int flag;
    int k;
    int b;
    int count;
    int t;
    char head;
    char tail;
    char Wall;
    char Nothing;
    char ap;
    void change();
    bool check(int I);
    void turn(int I);
    void pop();
    void InitFil();

public:
    snake();
    void field();
    void initSnake();
    void fruit();
    void show();
    void dvij(int I);
    bool game();
    void Drow();
    int GetLength() { return length; }
    void result();
};

snake::snake()
{
    count = 0;
    direction = RIGHT;
    length = 0;
    flag = 0;
    k = 0;
    head = 'O';
    tail = '+';
    Wall = '#';
    Nothing = ' ';
    ap = '$';
    body[0].X = LENGTH / 2;
    body[0].Y = HEIGHT / 2;
    apple.X = 0;
    apple.Y = 0;
    this->initSnake();
    this->InitFil();
}

void snake::field()
{
    int i, j;
    for (j = 0; j < HEIGHT + 2; j++)
    {
        for (i = 0; i < LENGTH + 2; i++)
        {
            if ((i == 0 || i == LENGTH + 1) || (j == 0 || j == HEIGHT + 1))
                a[i][j] = Wall;
            else
                a[i][j] = Nothing;
        }
    }
}

void snake::initSnake()
{
    for (int i = 1; i < SNAKE_LENGTH_INIT; i++)
    {
        body[i].X = body[i - 1].X - dx[direction];
        body[i].Y = body[i - 1].Y + dy[direction];
    }

    /* for(int i=0; i<SNAKE_LENGTH_INIT; i++)
        cout<<body[i].X<<" "<<body[i].Y<<endl;  */
}
void snake::change()
{
    //apple.X=1+rand()%LENGTH;
    //apple.Y=1+rand()%HEIGHT;
    do
    {
        b = rand() % count;
    } while (a[fil[b].X][fil[b].Y] != Nothing);
    apple.X = fil[b].X;
    apple.Y = fil[b].Y;
    this->pop();
    flag = 1;
    //cout<<apple.X<<" "<<apple.Y<<endl;
    //}
}

void snake::pop()
{
    for (int i = b + 1; i < count; i++)
    {
        fil[i - 1].X = fil[i].X;
        fil[i - 1].Y = fil[i].Y;
    }
    fil[count - 1].X = 0;
    fil[count - 1].Y = 0;
    count--;
}

void snake::fruit()
{
    if (a[body[0].X][body[0].Y] == ap)
    {
        flag = 0;
        length++;
    }
    if (flag == 0)
        this->change();

    // cout<<apple.X<<" "<<apple.Y<<endl;
}

void snake::show()
{
    for (int j = 0; j < HEIGHT + 2; j++)
    {
        for (int i = 0; i < LENGTH + 2; i++)
            cout << a[i][j];
        cout << endl;
    }
    cout << "Total:" << length << endl;
}

void snake::dvij(int I)
{
    if (k == 0)
        a[body[SNAKE_LENGTH_INIT + length - 1].X][body[SNAKE_LENGTH_INIT + length - 1].Y] = Nothing;
    for (int i = SNAKE_LENGTH_INIT + length - 1; i > 0; i--)
    {
        body[i].X = body[i - 1].X;
        body[i].Y = body[i - 1].Y;
    }

    if (I >= 0 && this->check(I))
        this->turn(I);
    else
    {
        body[0].X = body[0].X + dx[direction];
        body[0].Y = body[0].Y - dy[direction];
    }
    if (a[body[0].X][body[0].Y] == ap)
    {
        k = 1;
        body[SNAKE_LENGTH_INIT + length].X = body[SNAKE_LENGTH_INIT + length - 1].X;
        body[SNAKE_LENGTH_INIT + length].Y = body[SNAKE_LENGTH_INIT + length - 1].Y;
    }
    else
        k = 0;

    /* for(int i=0; i<SNAKE_LENGTH_INIT; i++)
        cout<<body[i].X<<" "<<body[i].Y<<endl;   */
}

bool snake::check(int I)
{
    if ((direction == RIGHT && I == LEFT) || (direction == LEFT && I == RIGHT) || (direction == UP && I == DOWN) || (direction == DOWN && I == UP) || I < 0)
        return false;
    else
        return true;
}

bool snake::game()
{
    bool game = true;
    if (a[body[0].X][body[0].Y] == Wall || a[body[0].X][body[0].Y] == tail)
    {
        game = false;
        t = 0;
    }
    if (count == 0)
    {
        game = false;
        t = 1;
    }
    return game;
}

void snake::Drow()
{
    a[body[0].X][body[0].Y] = head;
    a[apple.X][apple.Y] = ap;
    for (int i = 1; i < SNAKE_LENGTH_INIT + length; i++)
        a[body[i].X][body[i].Y] = tail;
}

void snake::turn(int I)
{
    if (I == LEFT || I == RIGHT)
        body[0].X += dx[I];
    if (I == UP || I == DOWN)
        body[0].Y -= dy[I];
    direction = I;
}

void snake::InitFil()
{
    for (int j = 1; j < HEIGHT + 1; j++)
    {
        for (int i = 1; i < LENGTH + 1; i++)
        {
            fil[count].X = i;
            fil[count].Y = j;
            count++;
        }
    }
}

void snake::result()
{
    if (t)
        cout << "Are you wining, son?" << endl;
    else
        cout << "GAME OVER:<" << endl;
}

void ClearConsole();
int Input();
int main()
{
    snake a;
    bool ingame;
    system("cls");
    srand(time(NULL));
    cout << "Press space to start..." << endl;
    switch (_getch())
    {
    case ' ':
        ingame = true;
        break;
    default:
        return -2;
        break;
    }
    system("cls");
    a.field();
    while (ingame)
    //for (int i = 0; i < 200; i++)
    {
        a.fruit();
        a.Drow();
        a.show();
        Sleep(200);
        a.dvij(Input());
        ingame = a.game();
        ClearConsole();
    }
    a.result();
    cout << "Your score is: " << a.GetLength() << endl;
    return 0;
}

int Input()
{
    int input = -1;
    if (_kbhit())
    {
        switch (_getch())
        {
        case VK_UP:
        case 'w':
            input = UP;
            break;
        case VK_LEFT:
        case 'a':
            input = LEFT;
            break;
        case VK_DOWN:
        case 's':
            input = DOWN;
            break;
        case VK_RIGHT:
        case 'd':
            input = RIGHT;
            break;
        default:
            input = -1;
            break;
        }
    }
    return input;
}

void ClearConsole()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD homeCoords = {0, 0};
    DWORD count;
    DWORD cellCount;
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &info);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return;
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
        return;
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
