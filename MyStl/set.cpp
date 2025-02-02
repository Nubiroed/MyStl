#include<iostream>
#include<vector>
#include<algorithm>

namespace MyStl {
    class Set {
    private:
        std::vector<int> elements;

    public:
        // ���������� ��������
        void add(int element) {
            if (!contains(element)) {
                elements.push_back(element);
            }
        }

        // �������� ��������
        void remove(int element) {
            auto it = std::remove(elements.begin(), elements.end(), element);
            if (it != elements.end()) {
                elements.erase(it, elements.end());
            }
        }

        // �������� ������� ��������
        bool contains(int element) const {
            return std::find(elements.begin(), elements.end(), element) != elements.end();
        }

        // ����� ���� ���������
        void display() const {
            for (int element : elements) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    };
}
