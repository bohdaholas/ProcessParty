#include <iostream>
#include "validator.h"

using namespace std;

int main() {
    Validator val{1, 10};
    int num = 5;
    cout << boolalpha << val.insideInterval(num) << endl;
    return 0;
}