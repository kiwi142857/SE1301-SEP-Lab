#include <string>

using namespace std;

class Human {
private:
    float height;
    float weight;
    int age;
public:
    void eat();
    void walk();
    void talk(const string &s) const;
    Human(float height, float weight);
    Human(const Human &h);
};

