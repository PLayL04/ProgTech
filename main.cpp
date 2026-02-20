#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class RealEstate {
public:
    string owner;    // Владелец
    string date;     // Дата (гггг.мм.дд)
    int cost;        // Ориентировочная стоимость

    void printInfo() {
        cout << "--- Данные объекта ---" << endl;
        cout << "Владелец: " << owner << endl;
        cout << "Дата: " << date << endl;
        cout << "Стоимость: " << cost << " руб." << endl;
        cout << "----------------------" << endl;
    }

    RealEstate() {
        owner = "";
        date = "";
        cost = 0;
    }

    RealEstate(string p_owner, string p_date, int p_cost) {
        owner = p_owner;
        date = p_date;
        cost = p_cost;
    }
};

int func(vector<int>& list) {
    int counter = 0;
    for (int& item : list){
        if(item > 0) counter++;
    }
    return counter;
}

// string& - передача элемента по ссылке
RealEstate parseRealEstate(const string& textData) {
    RealEstate obj;

    stringstream ss(textData);

    char ch;
    // Крутим цикл, считывая по одному символу, пока не наткнемся на открывающую кавычку '"'
    while (ss.get(ch)) {
        if (ch == '"') {
            break; // Нашли начало имени владельца, выходим из цикла
        }
    }

    // Теперь читаем всё до следующей кавычки '"' и сохраняем в obj.owner
    getline(ss, obj.owner, '"');

    ss >> obj.date >> obj.cost;

    return obj;
}

vector<RealEstate> sortRealEstateByCost(vector<RealEstate>& objects) {
    /*
     * Внешний цикл отвечает за количество проходов по массиву
     * Если текущий объект стоит больше, чем следующий
     * Меняем их местами.
     */
    int n = objects.size();
    //
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (objects[j].cost > objects[j + 1].cost) {
                // Функция swap — стандартный инструмент C++ для обмена значений переменных.
                swap(objects[j], objects[j + 1]);
            }
        }
    }

    return objects; // Возвращаем измененный массив
}



int main() {
    // Поддержка русского языка в консоли (для Windows)
    // setlocale(LC_ALL, "Russian");

    RealEstate house1("Иванов Иван Иванович", "2026.02.20", 10);
    RealEstate house2("Гадя Петрович Хренова", "2025.02.21", 20);
    RealEstate house3("Федор Иванович Крузинштерн", "2020.02.02", 30);
    RealEstate house4("Илья Игоревич Рыжков", "2020.01.01", 1);
    RealEstate house5("Доминик C Торрента", "2020.04.04", 60);

    vector<RealEstate> list = { house1, house2, house3, house4, house5 };

    for (RealEstate& item : list) {
        cout << item.owner << ": " << item.cost << endl;
    }

    sortRealEstateByCost(list);

    for (int i = 0; i < 5 && i < list.size(); i++) {
        cout << i + 1 << ". " << list[i].owner << ": " << list[i].cost << endl;
    }

    return 0;
}
