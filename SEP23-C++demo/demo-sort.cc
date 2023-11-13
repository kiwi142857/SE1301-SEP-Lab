#include <iostream>
#include <string>

using namespace std;

class SorterInt {
private:
    int min;
    int max;
    SorterInt() { }
public:
    SorterInt(int min, int max) {
        this->min = min;
        this->max = max;
    }
    void add(int newEle) {
        if (newEle < min) min = newEle;
        if (newEle > max) max = newEle;
    }
    int getMin() const { return min; }
    int getMax() const { return max; }
};

class SorterString {
private:
    string min;
    string max;
    SorterString() { }
public:
    SorterString(string min, string max) {
        this->min = min;
        this->max = max;
    }
    void add(string newEle) {
        if (newEle < min) min = newEle;
        if (newEle > max) max = newEle;
    }
    string getMin() const { return min; }
    string getMax() const { return max; }
};

// TODO: Add class Sorter using template

int main()
{
    SorterInt sorterInt(50, 50);
    sorterInt.add(13);
    sorterInt.add(94);
    sorterInt.add(12);
    sorterInt.add(430);
    sorterInt.add(59);
    cout << "sorterint     => min: " << sorterInt.getMin() << " max: " << sorterInt.getMax() << endl;

    SorterString sorterStr("50", "50");
    sorterStr.add("013");
    sorterStr.add("94");
    sorterStr.add("12");
    sorterStr.add("403");
    sorterStr.add("590");
    cout << "sorterstring  => min: " << sorterStr.getMin() << " max: " << sorterStr.getMax() << endl;

    Sorter<int> sorterTint(50, 50);
    sorterTint.add(13);
    sorterTint.add(94);
    sorterTint.add(12);
    sorterTint.add(430);
    sorterTint.add(59);
    cout << "sorter<int>   => min: " << sorterTint.getMin() << " max: " << sorterTint.getMax() << endl;

    Sorter<string> sorterTstr("50", "50");
    sorterTstr.add("013");
    sorterTstr.add("94");
    sorterTstr.add("12");
    sorterTstr.add("403");
    sorterTstr.add("590");
    cout << "sorter<string>=> min: " << sorterStr.getMin() << " max: " << sorterStr.getMax() << endl;

    return 0;
}