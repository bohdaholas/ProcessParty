#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_

class Validator {
public:
    Validator(int x, int y);
    bool insideInterval(int num);
    void setInterval(int x, int y);
private:
    int a, b;
};

#endif