#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    std::initializer_list<int> init = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Инициализация map значениями : {{1, 2}, {3, 4}, {5, 6}}" << endl;
    auto map = std::map<int, int> {{1, 2}, {3, 4}, {5, 6}};
    cout << "Итерирование по map:"  << endl;
    cout << "Map: ";
    for (auto & it : map) {
        std::cout << "(" << it.first << ":" << it.second << "}, ";
    }
    cout << endl;

    cout << "Изменение map по ключу" << endl;
    cout << "Call map[1]\n"; map[1] = 99;
    cout << "Call map[3]\n"; map[3] = 99;
    cout << "Map: ";

    for (auto & it : map) {
        std::cout << "(" << it.first << ":" << it.second << "}, ";
    }

    std::cout << "\n\n\nИнициализация контейнеров vector, list, deque значениями: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}\n";
    auto vector = std::vector<int>(init);
    auto list = std::list<int>(init);
    auto deque = std::deque<int>(init);

    cout << "Контейнеры vector, deque имеет предоставляют досуп к любому элементу по индексу, список - нет." << endl;
    cout << "vector[2] = " << vector[2] << endl;
    cout << "deque[2] = " << deque[2] << endl;
    cout << "list[2] = error\n\n";

    cout << "Доступ к первому и последнему элементу за константное время:"  << endl;
    cout << "vector[0]: " << vector.front() << "; vector[size-1]: " << vector.back() << endl;
    cout << "deque[0]: " << deque.front() << "; deque[size-1]: " << deque.back() << endl;
    cout << "list[0]: " << list.front() << "; list[size-1]: " << list.back() << endl << endl;

    cout << "Все три контейнера обладают операциями push_back, push_front"  << endl;
    cout << "Call deque.push_back(99)\n"; deque.push_back(99);
    cout << "Call deque.push_front(99)\n"; deque.push_front(99);
    cout << "Call list.push_back(99)\n"; list.push_back(99);
    cout << "Call list.push_front(99)\n\n"; list.push_front(99);
    cout << "Vector не позволяет добавлять элементы в начало"  << endl;
    cout << "Call vector.push_back(99) - error\n\n";
    
    cout << "Итерирование идентично для всех контейнеров:"  << endl;
    cout << "Deque: ";
    for (auto & it : deque) {
        cout << it << " ";
    }
    cout << endl;

    cout << "List: ";
    for (auto & it : list) {
        cout << it << " ";
    }
    cout << endl;

    cout << "Vector: ";
    for (auto & it : vector) {
        cout << it << " ";
    }
    cout << endl;
}