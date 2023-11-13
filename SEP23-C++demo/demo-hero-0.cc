#include <iostream>

using namespace std;

class Human {
private:
    float height;
    float weight;
    int age;
public:
    void eat() { weight += 1.0f; }
    void walk() { if (weight > 1.0f) weight -= 1.0f; }
    void talk(const string &s) const { cout << "I am a human" << endl; }
    Human(float height, float weight) {
        this->height = height;
        this->weight = weight;
    }
    Human(const Human &h) {
        this->height = h.height;
        this->weight = h.weight;
    }
};

int main()
{
    Human passerby_a(185.0f, 74.0f);
    Human passerby_b(passerby_a);
    passerby_b.talk("Hi");
    return 0;
}