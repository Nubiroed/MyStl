#include<iostream>
#include<vector>
#include<algorithm>

namespace MyStl {
    class Set {
    private:
        std::vector<int> elements;

    public:
        // Добавление элемента
        void add(int element) {
            if (!contains(element)) {
                elements.push_back(element);
            }
        }

        // Удаление элемента
        void remove(int element) {
            auto it = std::remove(elements.begin(), elements.end(), element);
            if (it != elements.end()) {
                elements.erase(it, elements.end());
            }
        }

        // Проверка наличия элемента
        bool contains(int element) const {
            return std::find(elements.begin(), elements.end(), element) != elements.end();
        }

        // Вывод всех элементов
        void display() const {
            for (int element : elements) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    };
}
