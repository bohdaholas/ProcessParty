#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_

/**
 * Validator class works with number intervals.
 *
 * Example class which we use to learn how to create
 * tests and doxygen documentation.
 */
class Validator {
public:
    /**
     * Constructor which creates Validator with the interval
     * from x to y.
     *
     * @param x Number which marks the beginning of the interval
     * @param y Number which marks the end of the interval
     */
    Validator(int x, int y);

    /**
     * Check if input number is inside the interval of Validator.
     *
     * @param num Input number to be checked
     * @return True if number is inside the interval, False
     * otherwise
     */
    bool insideInterval(int num);

    /**
     * Set to Validator new interval from x to y.
     *
     * @param x Number which marks the beginning of the interval
     * @param y Number which marks the end of the interval
     */
    void setInterval(int x, int y);

private:
    int a, b;
};

#endif
