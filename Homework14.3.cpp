// Homework14.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <mutex>


class Data {
private:
    int data1;
    int data2;
    int data3;
    std::mutex m;
    friend void swaplock(Data& d1, Data& d2);
    friend void swapscopedlock(Data& d1, Data& d2);
    friend void swapuniquelock(Data& d1, Data& d2);
public:
    Data(int a, int b, int c) : data1{ a }, data2{ b }, data3{ c } {}
    void printdata() {
        std::cout << "Data: " << data1 << " " << data2 << " " << data3 << std::endl;
    }
    
};
void swaplock(Data& d1, Data& d2) {
    d1.m.lock();
    d2.m.lock();
    int da = d1.data1;
    int db = d1.data2;
    int dc = d1.data3;
    d1.data1 = d2.data1;
    d1.data2 = d2.data2;
    d1.data3 = d2.data3;
    d2.data1 = da;
    d2.data2 = db;
    d2.data3 = dc;

    d1.m.unlock();
    d2.m.unlock();
}
void swapscopedlock(Data& d1, Data& d2) {
    std::scoped_lock lm1(d1.m, d2.m);
    int da = d1.data1;
    int db = d1.data2;
    int dc = d1.data3;
    d1.data1 = d2.data1;
    d1.data2 = d2.data2;
    d1.data3 = d2.data3;
    d2.data1 = da;
    d2.data2 = db;
    d2.data3 = dc;
}
void swapuniquelock(Data& d1, Data& d2) {
    std::unique_lock<std::mutex> lm1(d1.m, std::defer_lock);
    std::unique_lock<std::mutex> lm2(d2.m, std::defer_lock);
    std::lock(lm1, lm2);
    int da = d1.data1;
    int db = d1.data2;
    int dc = d1.data3;
    d1.data1 = d2.data1;
    d1.data2 = d2.data2;
    d1.data3 = d2.data3;
    d2.data1 = da;
    d2.data2 = db;
    d2.data3 = dc;

}

int main()
{
    Data d1(3, 5, 7);
    Data d2(4, 6, 8);
    d1.printdata();
    swaplock(d1, d2);
    d1.printdata();

    d1.printdata();
    swapscopedlock(d1, d2);
    d1.printdata();

    d1.printdata();
    swapuniquelock(d1, d2);
    d1.printdata();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
