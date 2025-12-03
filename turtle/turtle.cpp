#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int finish = 50;
int winner = -1;
bool END = false;
int pos[10] = { 0 };    
int finishers = 0;

char pole[finish] = {0};

void Green()
{
    int number;
    
    for (int i = 0; i < finish; i++)
    {
        pole[i] = '_';
        if (i == finish-1)
        {
            pole[i] = ';';
        }
    }

    for (int i = 0; i < 10; i++)
    {
        char tt;
        tt = '0' + i;

        if (pole[pos[i]] == '_')
        {
            pole[pos[i]] = tt;
        }
    }


}

struct TurtleInfo
{
    int id;
    int smh;
};

void Draw()
{
    system("cls");

    Green();

    cout << "гонка черепах" << endl;
    cout << "финиш: " << finish << endl << endl;
    cout << "" << endl;

    for (int i = 0; i < finish; i++)
    {
        cout << pole[i];
    }
    cout << "" << endl;

    for (int turt = 0; turt < 10; turt++)
    {
        cout << "гонщик: " << turt << " сейчас на " << pos[turt] << " позиции";
        cout << "" << endl;

        if (pos[turt] >= finish)
        {
            cout << " победа";
            cout << "" << endl;
            
        }
    }

    //for (int i = 0; i < 10; i++)
    //{
    //    cout << i + 1 << ": ";

    //    for (int way = 0; way < pos[i]; way++)
    //    {
    //        cout << "-";
    //    }

    //    if (pos[i] < finish)
    //    {
    //        cout << ">";
    //    }

    //    cout << "|" << pos[i];

    //    if (pos[i] >= finish)
    //    {
    //        cout << " фин";
    //    }
    //    cout << endl;
    //}

    //cout << endl;

    //if (winner != -1)
    //{
    //    cout << "победитель: " << winner + 1 << endl;
    //}

}


DWORD WINAPI Turtle(LPVOID param)
{

    TurtleInfo* info = (TurtleInfo*)param;

    int id = info->id;
    int smh = info->smh;

    srand(smh);

    Sleep(rand() % 3000);


    int my_speed = 1000 + rand() % 2000;  

    while (pos[id] < finish)
    {
        Sleep(my_speed + rand() % 500);

        int step = rand() % 3;
        pos[id] += step;

        if (pos[id] > finish)
        {
            pos[id] = finish;
        }

        if (pos[id] >= finish  && winner==-1)
        {
            winner = id;
        }
        if (pos[id] >= finish)
        {
            break;
        }
    }

    return 0;
}

int main()
{
    srand(time(NULL));


    HANDLE GAME[10];

    setlocale(0, "rus");

    cout << "черепашная гонак" << endl;
    Sleep(2000);


    cout << "Старт!!!" << endl;
    Sleep(1000);

    for (int i = 0; i < 10; i++)
    {
        TurtleInfo* info = new TurtleInfo;
        info->id = i;
        info->smh = rand();

        GAME[i] = CreateThread(NULL, 0, Turtle, (void*)info, 0, NULL);

        if (GAME[i] == NULL)
        {
            cout << "ошибка потока" << endl;
            return GetLastError();
        }
    }


    while (true)
    {
        Draw();

        bool checker = true;
        for (int i = 0; i < 10; i++) {
            if (pos[i] < finish) {
                checker = false;
                break;
            }
        }

        if (checker) {
            break;
        }
        Sleep(300);  
    }

    WaitForMultipleObjects(10, GAME, TRUE, INFINITE);

    Draw();

    cout << "" << endl;
    cout << "игра закончена" << endl;
    cout << "победитель:! " << winner + 1 << endl;

    for (int i = 0; i < 10; i++)
    {
        CloseHandle(GAME[i]);
    }

    cin.get();

    return 0;
}