#include <iostream>

using namespace std;

class Human {
protected:
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
    Human(){};
    virtual void work()=0;
};


// TODO: Add class Speaker and Soldier
class Speaker:public Human {
public:
    Speaker() { };
    void work(){weight--;};

};

class Soldier:public Human {
public:
    Soldier() { };
    void work(){weight--; };
};

int main()
{
    Speaker speaker;
    Soldier soldier;

    cout << ">> Speaker:" << endl;
    speaker.talk("freeze");
    speaker.work();

    cout << ">> Solder:" << endl;
    soldier.talk("freeze");
    soldier.work();

    cout << ">> Together as humans:" << endl;
    Human *humans[] = {&speaker, &soldier};
    for (int i = 0; i < 2; ++i) {
        humans[i]->talk("freeze");
        humans[i]->work();
    }

    return 0;
}
