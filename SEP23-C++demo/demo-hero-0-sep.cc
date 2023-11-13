#include <iostream>
#include "demo-hero-0-sep.h"

void Human::eat()
{
    weight += 1.0f;
}
void Human::walk()
{
    if (weight > 1.0f)
        weight -= 1.0f;
}
void Human::talk(const string &s) const
{
    cout << "I am a human" << endl;
}
Human::Human(float height, float weight)
{
    this->height = height;
    this->weight = weight;
}
Human::Human(const Human &h)
{
    this->height = h.height;
    this->weight = h.weight;
}

int main()
{
    Human passerby_a(185.0f, 74.0f);
    Human passerby_b(passerby_a);
    passerby_b.talk("Hi");
    return 0;
}