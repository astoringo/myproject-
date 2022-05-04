#include <iostream> 
#include <cstdio> 
#include <cstdint> 
#include <iomanip>
#include <fstream>

using namespace std;

//Структура, яка мiстить поля згiдно з iндивiдуальним завданням
struct vedomost
{

    char Pr[10]; // Назва продукції
    char Shr[10]; // Шифр
    int  k, // Обсяг поставок, шт
        c, // Вартість, грн  
        z; // Оптова ціна, грн. //Z=K*C

};

vedomost kl[10];
int s1 = 0,
s2 = 0,
s3 = 0;
extern "C" int     mas_func(int, int);
int zapolnenie();  // заповнення масиву даними з клавiатури
void show(int);    // виведення на екран
int zapis(int);    // запису даних у файл
int read();        // читання даних iз файлу
void edit(int);    // редагування 

int main() {

    setlocale(0, "rus");

    int k,//змiнна для вибору дiй користувача
        v = 0;//змiнна для зберiгання кiлькостi записiв у масивi вiдомостей

      //виведення вiдомостей  про розробника 
    cout << " КУРСОВА РОБОТА" << endl;
    cout << " Системне Програмування" << endl;
    cout << " Cтудента групи Е - 85" << endl;
    cout << " Кишковара Даниїла Ігоровича " << endl;
    cout << " Варiант № 47" << endl;

    do {
        //пояснення користувачу
        cout << "\n 1: Для заповнення масиву даними з клавiатури введiть '1'" << endl;
        cout << " 2: Для виведення на екран введiть '2'" << endl;
        cout << " 3: Для запису даних у файл введiть '3'" << endl;
        cout << " 4: Для читання даних iз файлу введiть '4'" << endl;
        cout << " 5: Для редагування введiть '5'" << endl;
        cout << "\n Введiть один з варiантiв (вiд 1 до 5): ";
        cin >> k;
        switch (k)
        {
        case 1:v = zapolnenie(); break;
        case 2:show(v); break;
        case 3:zapis(v); break;
        case 4:v = read(); break;
        case 5:edit(v); break;
        default:cout << " Неправильний вибiр!";
        }
        cout << "\n Для продовження введiть вiд 1 до 5. Для виходу iз програми введiть 0: ";   cin >> k;
    } 
    while (k != 0);

    return 0;
}

//функцiя заповнення масиву даними з клавiатури
int zapolnenie() {

    int n;//тимчасова змiнна для того, щоб повернути у голову програму введену кiлькiсть
    cout << "\n Введiть кiлькiсть продукції (< або = 10): ";  cin >> n;
    cout << "\n Данi для вiдомостi: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "\n Введення даних для продукції № " << i + 1;
        cout << "\n Назва продукції: "; cin >> kl[i].Pr;
        cout << " Введiть шифр Shr: "; cin >> kl[i].Shr;
        cout << " Введiть обсяг поставок k: "; cin >> kl[i].k;
        cout << " Введiть вартість однієї одиниці: "; cin >> kl[i].c;
        kl[i].z = kl[i].k * kl[i].c; //Z=K*C
    //    s1 = s1 + kl[i].k;//
        s1 = mas_func(s1, kl[i].k);
        s2 = mas_func(s2, kl[i].c);
        s3 = mas_func(s3, kl[i].z);
    }
    cout << "\n Данi введенi!" << endl;
    return n;
}

//виведення структури на екран
//для роботи оператора setw() потрiбна бiблiотека <iomanip>
void show(int v) {
    if (!v)
    {
        cout << "\n У масивi немає даних!" << endl;  return;
    }
    else
    {
        //виведення шапки таблицi
        cout << " ______________________________________________________ " << endl;
        cout << "|" << "№" << setw(22) << "Склад"
            << setw(7) << "k" << setw(7) << "c"
            << setw(7) << "z" << setw(4) << "|"
            << "    " << endl;
        cout << "|______________________________________________________|" << endl;
        //виведення рядкiв таблицi
        for (int i = 0; i < v; i++)
        {
            if (i >= 9) {

                cout << "|" << i + 1 << setw(21) << kl[i].Pr
                    << setw(7) << kl[i].k << setw(7) << kl[i].c
                    << setw(7) << kl[i].z << setw(4) << " |"
                    << "      " << endl;
                cout << "|______________________________________________________|" << endl;

            }
            else
            {
                cout << "|" << i + 1 << setw(22) << kl[i].Pr
                    << setw(7) << kl[i].k << setw(7) << kl[i].c
                    << setw(7) << kl[i].z << setw(4) << " |"
                    << "      " << endl;
                cout << "|______________________________________________________|" << endl;
            }
        }
    }
    //виведення рядку «Усього»
    cout << "|" << "Разом по    |" << setw(42) << "|" << endl;
    cout << "|" << "пiдприємству|" << setw(17) << s1 << setw(7) << s2 << setw(7) << s3 << setw(7) << "|" << endl;
    cout << "|____________|_________________________________________|" << endl;

}
//функцiя запису до файлу, q- кiлькiсть рядкiв масиву 
int zapis(int q) {
    ofstream f;//оголошення файлової змiнної
    setlocale(LC_ALL, "rus");//русифiкатор 
    char name[12];//масив символiв для iменi файлу
    cout << "\n Введiть iм’я файлу: ";     cin >> name;
    f.open(name);//вiдкрити файл для запису даних
    if (!f)//перевiрка на правильнiсть операцiї вiдкриття
    {
        cout << "\n Error"; getchar();
    }//дiй при помилцi вiдкриття
    for (int i = 0; i < q; i++)//дiї для записування даних до файлу
    {
        f << kl[i].Pr << " " << kl[i].k << " " << kl[i].c << " "
            << kl[i].z << endl;
    }
    f.close();//закрити файл
    cout << " Данi були записанi у файл. " << name << endl;

    return 0;
}

//функцiя читання iз файлу, повертає кiлькiсть прочитаних записiв
int read() {
    int i = 0;//номер поточного прочитаного запису
    int j;// тимчасова змiнна
    char name[12]; //масив символiв для iменi файлу
    cout << "\n Введiть iм'я файлу: ";    cin >> name;
    ifstream  readFile; //оголошення файлової змiнної
    readFile.open(name); //вiдкрити файл для читання даних
    if (!readFile) cout << "\n Помилка вiдкриття файлу!" << endl;
    else
    {
        while (1)//безкiнечний цикл
        {
            if (readFile.tellg() == -1) break;//якщо вказiвник вийшов за межi файлу – вийти з циклу
            //читання iз файлу
            readFile >> kl[i].Pr >> kl[i].k >> kl[i].c >> kl[i].z;
            i++;//збiльшення лiчильника номера рядка
        }
        cout << "\n Данi прочитанi iз файлу <" << name << "> успiшно!! " << endl;
        //обчислюються потрiбнi поля
        for (int j = 0; j < i; j++)
        {
            //s1 = s1 + kl[j].k;
            s1 = mas_func(s1, kl[i].k);
            s2 = mas_func(s2, kl[j].c);
            s3 = mas_func( s3, kl[j].z);
        }
        return i - 1;
    }
}

//редагування даних
void edit(int v) {
    int kol_strok = v;
    int num;// порядковий номер рядка для змiни даних
    int pole;// порядковий номер поля 
    if (kol_strok > 0)//якщомасив даних не пустий
    {
        cout << "\n Введiть порядковий номер рядка: "; cin >> num;
        num--;
        cout << "\n Введiть номер поля: ";
        cout << "\n Продукція - 1 ";
        cout << "\n Шифр - 2 ";
        cout << "\n Обсяг k - 3 ";
        cout << "\n Вартість одиниці c - 4  ";
        cin >> pole;
        cout << "\n Введiть нове значення для поля \n" << endl;
        switch (pole)
        {
        case 1: { cin >> kl[num].Pr;  } break;
        case 2: { cin >> kl[num].k;   } break;
        case 3: { cin >> kl[num].c;   } break;
        case 4: { cin >> kl[num].z;   } break;
        default: {cout << "\n Немає такого поля!\n"; pole = 0; }
        }
        if (pole != 0) cout << "\n Змiни внесенi!\n";
        kl[num].z = kl[num].k * kl[num].c;
        s1 = 0;  s2 = 0; s3 = 0;//пiсля змiни значень полiв очистити змiннi сум 
//перерахунок значень змiнних сум
        for (int i = 0; i < v; i++)
        {
            //s1 = s1 + kl[i].k;
            s1 = mas_func(s1, kl[i].k);
            s2 = mas_func(s2, kl[i].c);
            s3 =mas_func( s3, kl[i].z);
        }
    }
}
