#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int finish = 10;
int winner = -1;
bool END = false;
int pos[10] = { 0 };
int finishers = 0;

struct TurtleInfo
{
    int id;
};

void Draw()
{
    system("cls");

    cout << "гонка черепах" << endl;
    cout << "финиш: " << finish << endl << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << i + 1 << ": ";

        for (int way = 0; way < pos[i]; way++)
        {
            cout << "-";
        }

        if (pos[i] < finish)
        {
            cout << ">";
        }



        cout << "|" << pos[i];

        if (pos[i] >= finish)
        {
            cout << " фин";
        }
        cout << endl;
    }

    cout << endl;

    if (winner != -1)
    {
        cout << "победитель: " << winner + 1 << endl;
    }
}

DWORD WINAPI Turtle(LPVOID param)
{

    srand(time(NULL));
    TurtleInfo* info = (TurtleInfo*)param;
    int id = info->id;


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

        Draw();

        if (pos[id] >= finish)
        {
            if (winner == -1)
            {
                winner = id;
                Draw();
            }
            break;
        }
    }

    delete info;
    return 0;
}

int main()
{
    HANDLE GAME[10];
    setlocale(0, "rus");

    cout << "ГОНКА Черпах" << endl;
    Sleep(2000);


    cout << "Старт!" << endl;
    Sleep(1000);

    for (int i = 0; i < 10; i++)
    {
        TurtleInfo* info = new TurtleInfo;
        info->id = i;

        GAME[i] = CreateThread(NULL, 0, Turtle, (void*)info, 0, NULL);

        if (GAME[i] == NULL)
        {
            cout << "ошибка потока" << endl;
            return GetLastError();
        }
    }

    cout << "все черепашки стартовали" << endl;
    Sleep(1000);

    while (true)
    {

        int finished = 0;
        for (int i = 0; i < 10; i++) {
            if (pos[i] >= finish) {
                finished++;
            }
        }

        if (finished == 10) {
            break;
        }

        Sleep(300);  
    }

    WaitForMultipleObjects(10, GAME, TRUE, INFINITE);


    cout << "" << endl;
    cout << "игра закончена" << endl;
    cout << "победитель: " << winner + 1 << endl;

    for (int i = 0; i < 10; i++)
    {
        CloseHandle(GAME[i]);
    }

    cin.get();

    return 0;
}