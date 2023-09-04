#include <iostream>
#include <functional>
using namespace std;

//---------------------------------------------------------
class MyClass { 
    std::function<void(int)> _f;   
public:
    void callCB(int i);
    void setCB(std::function<void(int)> f);
    void CBFunc(int i);
    void Func(int i);
};

void MyClass::setCB(std::function<void(int)> f)
{
    _f = f;   
}
void MyClass::callCB(int i)
{
    _f(i);
}
void MyClass::CBFunc(int i)
{
    std::cout << "Call back "<< i << endl;
}

void MyClass::Func(int i)
{
    std::cout << "Func ";
    this->callCB(i);
}
//---------------------------------------------------------
class MyClass2 { 
    std::function<void(int)> _f;   
public:
    void callCB(int i);
    void setCB(std::function<void(int)> f);
    void CBFunc(int i);
};

void MyClass2::setCB(std::function<void(int)> f)
{
    _f = f;   
}
void MyClass2::callCB(int i)
{
    _f(i);
}
void MyClass2::CBFunc(int i)
{
    std::cout << "Call back2 "<< i << endl;
}
//---------------------------------------------------------
int main(int, char**) {
    std::cout << "Hello call back!\n";
    MyClass* p = new MyClass();
    MyClass2* p2 = new MyClass2();


    p->setCB([&](int a){p2->CBFunc(a);});
    p2->setCB([&](int a){p->CBFunc(a);});

    p->callCB(5);
    p2->callCB(6);
    p->Func(7);
    return 0;
}
//---------------------------------------------------------
