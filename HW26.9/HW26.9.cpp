#include <string>
#include <iostream>
#include <cstdlib>                                     // для получения рандомных чисел
#include <ctime>
#include <chrono>                                      // для получения времени
#include <fstream>
#include <thread>
using namespace std;

void calc_sum_arrpart(int l_bor, int r_bor, int arr[], int& summ)
{
    int s = 0;
    while (l_bor < r_bor)
    {
        s += arr[l_bor++];
    }
    summ += s;
};


int main()
{
    int N;                                             // длинна массива
    int M = 10000000;                                  // число частей массива
    int a = 0;                                         // переменная определяющая начало части
    int b;                                             // переменная определяющая конец части
    int c;                                             // временная переменная определяющая конец части
    int sum = 0;                                       // сумма элементов массива
    cout << "Enter array leght" << endl;
    cin >> N;
    while (M > N)
    {
        cout << "Enter number of array parts" << endl;
        cin >> M;
    }
    b = N / M;
    cout << "leght of array part = " << b << endl;
    int* rand_arr = new int[N];

    srand(time(nullptr));                              // используем текущее время, чтобы сгенерировать рандомные значения
    int lef_border = 0;                                // левая граница 
    int range_len = 99;                                // правая граница = range_len + left_border
    for (int i = 0; i < N; i++)
        rand_arr[i] = lef_border + rand() % range_len; // генерируем число в указанном диапазоне и записываем в массив
//Вычисляем без деления на потоки с функцией
    auto start = chrono::high_resolution_clock::now(); // сохраняем время начала работы алгоритма
    while (a != N)
    {
        if (a == b * M)
            c = N;
        else c = a + b;

        calc_sum_arrpart(a, c, rand_arr, sum);

        if (a == b * M)
            a = a + (N - a);
        else a = (a + b);
    }
    cout << "Total main = " << sum << endl;
    auto finish = chrono::high_resolution_clock::now(); // сохраняем время конца работы алгоритма
    chrono::duration<double> elapsed = finish - start;  // вычисляем продолжительность работы в сек. и выводим
    cout << "Elapsed time whith function: " << elapsed.count() << " sec" << endl; 
    sum = 0;
    a = 0;
    //Вычисляем без деления на потоки без функции
    start = chrono::high_resolution_clock::now(); // сохраняем время начала работы алгоритма
    while (a != N)
    {
        if (a == b * M)
            c = N;
        else c = a + b;
        for (int i = a; i < c; i++)
            sum = sum + rand_arr[i];
        if (a == b * M)
            a = a + (N - a);
        else a = (a + b);
    }
    cout << "Total main = " << sum << endl;
    finish = chrono::high_resolution_clock::now(); // сохраняем время конца работы алгоритма
    elapsed = finish - start;  // вычисляем продолжительность работы в сек. и выводим
    cout << "Elapsed time whithout function: " << elapsed.count() << " sec" << endl;
    sum = 0;
    a = 0;
    //Вычисляем с делением на потоки и функцией
    start = chrono::high_resolution_clock::now(); // сохраняем время начала работы алгоритма
    while (a != N)
    {
        if (a == b * M)
            c = N;
        else c = a + b;

        thread t(calc_sum_arrpart, a, c, rand_arr, ref(sum));
        if (t.joinable())
            t.join();
        if (a == b * M)
            a = a + (N - a);
        else a = (a + b);
    }
    cout << "Total main = " << sum << endl;
    finish = chrono::high_resolution_clock::now(); // сохраняем время конца работы алгоритма
    elapsed = finish - start;  // вычисляем продолжительность работы в сек. и выводим
    cout << "Elapsed time using threads: " << elapsed.count() << " sec" << endl;
  
    delete[] rand_arr;                                  // Чистим за собой
    return 0;
}