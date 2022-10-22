#include "iostream"
#include "vector"
#include <stdint.h>
#include <intrin.h>
#include <chrono>
#include <thread>

class ExampleObject {

};
class T {
public:
    int m_Number1;

    void localTest() {
        int number = 0;
        number++;
        number++;
        number = 5;
    }
    
    void memberTest() {
        m_Number1 = 0;
        m_Number1++;
        m_Number1++;
        m_Number1 = 5;
    }

    void fun() {
        unsigned int ui;
        unsigned __int64 i;

        i = __rdtscp(&ui);
        localTest();
        i = __rdtscp(&ui) - i;
        std::cout << "Calling localTest() function took " << i << " cycles.\n";

        i = __rdtscp(&ui);
        memberTest();
        i = __rdtscp(&ui) - i;
        std::cout << "Calling memberTest() function took " << i << " cycles.\n";

        i = __rdtscp(&ui);
        ExampleObject* heapobject = new ExampleObject();
        i = __rdtscp(&ui) - i;
        std::cout << "Creating object in heap took " << i << " cycles.\n";

        i = __rdtscp(&ui);
        ExampleObject stackobject;
        i = __rdtscp(&ui) - i;
        std::cout << "Creating object in stack took " << i << " cycles.\n";

        i = __rdtscp(&ui);
        int* ih = new int;
        *ih = 5;
        i = __rdtscp(&ui) - i;
        std::cout << "Creating integer in heap took " << i << " cycles.\n";

        i = __rdtscp(&ui);
        int is = 5;
        i = __rdtscp(&ui) - i;
        std::cout << "Creating integer in stack took " << i << " cycles.\n";

        delete heapobject;
        delete ih;
        std::cout << "\n";
    }
};

int main() {
    while (true) {
        T* t = new T();
        std::cout << "Calling fun() first.\n";
        t->fun();
        std::cout << "Calling fun() second.\n";
        t->fun();
        delete t;
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}