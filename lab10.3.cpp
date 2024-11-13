#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;

struct Route
{
    string sname;  // початковий пункт
    string ename;  // кінцевий пункт
    int rnum{};    // номер маршруту
};

void Create(Route* p, const int N);
void Print(Route* p, const int N);
void Sort(Route* p, const int N);
void PrintAll(Route* p, const int N);
void SaveToFile(Route* p, const int N, const char* filename);
void LoadFromFile(Route*& p, int& N, const char* filename);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "Введіть кількість маршрутів N: "; cin >> N;
    Route* p = new Route[N];
    double proc = 0, avg = 0, Kurs = 0, average = 0;
    string prizv;
    int found = 0;
    char filename[100]{};
    int menuItem;
     
    do {
        cout << endl << endl;
        cout << "Оберіть дію:" << endl << endl;
        cout << " [1] - Введення даних з клавіатури" << endl;
        cout << " [2] - Вивід даних за номером маршруту" << endl;
        cout << " [3] - Сортування масиву" << endl; 
        cout << " [4] - Вивід усіх даних" << endl;
        cout << " [5] - Збереження даних у файл" << endl;
        cout << " [6] - Завантаження даних з файлу" << endl;
        cout << " [0] - Вихід із програми" << endl << endl;
        cout << "Введіть номер дії: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;

        case 2:
            Print(p, N);
            break;

        case 3:
            Sort(p, N);
            PrintAll(p, N);
            break;

        case 4: 
            PrintAll(p, N);
            break;

        case 5:
            cout << "Введіть ім'я файлу для збереження даних: "; cin >> filename;
            SaveToFile(p, N, filename);
            cout << "Дані збережено у файл." << endl;
            break;

        case 6:
            cout << "Введіть ім'я файлу для завантаження даних: "; cin >> filename;
            LoadFromFile(p, N, filename);
            cout << "Дані завантажено з файлу." << endl;
            break;

        case 0:
            break;

        default:
            cout << "Невірна дія! Будь ласка, введіть коректний номер дії." <<
                "Для виходу з програми введіть 0." << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}


void Create(Route* p, const int N)
{ 
    for (int i = 0; i < N; i++)
    {
        cin.get();
        cin.sync();
        cout << "Введіть початковий пункт: "; getline(cin, p[i].sname);
        cout << "Введіть кінцевий пункт: "; cin >> p[i].ename;
        cout << "Введіть номер маршруту: "; cin >> p[i].rnum;
        cout << endl;
    }
}

void Print(Route* p, const int N)
{
    int routenumber, count = 0;
    cout << "Введіть номер маршруту для виведення: "; cin >> routenumber;

    for (int i = 0; i < N; i++)
    {
        if (routenumber == p[i].rnum)
            count++;
    }

    if (count > 0) {
        cout << "============================================================"
            << endl;
        cout << "____________________________________________________________"
            << endl;
        cout << "|  Початковий Пункт  |  Кінцевий Пункт  |  Номер Маршруту  |"
            << endl;
        cout << "============================================================"
            << endl;
        for (int i = 0; i < N; i++)
        {
            if (routenumber == p[i].rnum) {
                cout << "| " << setw(19) << left << p[i].sname  
                    << "| " << setw(17) << left << p[i].ename  
                    << "| " << setw(17) << left << p[i].rnum << "|" << endl;
            }
        }
        cout << "============================================================"
            << endl;
        cout << endl;
    }
    else
        cout << "\nМаршрут із вказаним номером не знайдено!\n"
        "Перевірте правильність введеного номера серед існуючих у масиві." << endl;
}

void Sort(Route* p, const int N)
{
    Route tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            if (p[i1].rnum > p[i1 + 1].rnum)
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
}

void PrintAll(Route* p, const int N)
{
    cout << "============================================================" 
        << endl;
    cout << "____________________________________________________________"
        << endl;
    cout << "|  Початковий Пункт  |  Кінцевий Пункт  |  Номер Маршруту  |"
        << endl;
    cout << "============================================================"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(19) << left << p[i].sname
            << "| " << setw(17) << left << p[i].ename
            << "| " << setw(17) << left << p[i].rnum << "|" << endl;
    }
    cout << "============================================================"
        << endl;
    cout << endl;
}

void SaveToFile(Route* p, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary); 
    fout.write((char*)&N, sizeof(N)); 
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Route)); 
    fout.close(); 
}

void LoadFromFile(Route*& p, int& N, const char* filename)
{
    delete[] p; 
    ifstream fin(filename, ios::binary);
    fin.read((char*)&N, sizeof(N)); 
    p = new Route[N]; 
    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Route)); 
    fin.close(); 
}
