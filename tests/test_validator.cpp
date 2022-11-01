#include <iostream>
#include <gtest/gtest.h>
#include "validator.h"

using namespace std;

// simple tests

TEST(ValidatorTest, InRange)
{

    Validator val(1, 10);
    bool res = val.insideInterval(2);
    ASSERT_EQ(true, res);
}

TEST(ValidatorTest, OutOfRange)
{

    Validator val(1, 10);
    bool res = val.insideInterval(-10);
    ASSERT_EQ(false, res);
}

// test for exception

TEST(ValidatorTest, Point)
{
    ASSERT_THROW(Validator val(1, 1), std::runtime_error);
}

TEST(ValidatorTest, Interval)
{
    ASSERT_NO_THROW(Validator val(1, 2));
}

// fixtures

class ValidatorFixture : public testing::TestWithParam<pair<int, bool>> {
public:
    ValidatorFixture();
    virtual ~ValidatorFixture();

    static void SetUpTestCase(); // runs before all tests
    static void TearDownTestCase(); // runs after all tests
    void SetUp() override; // runs before each test
    void TearDown() override; // runs after each test
protected:
    Validator *p_val;
};

void ValidatorFixture::SetUp()
{
    p_val = new Validator{1, 10};
    cout << "Hi from set up" << endl;
}

void ValidatorFixture::TearDown()
{
    delete p_val;
    cout << "Hi from tear down up" << endl;
}

void ValidatorFixture::SetUpTestCase()
{
    cout << "Hi from set up test case" << endl;
}

void ValidatorFixture::TearDownTestCase()
{
    cout << "Hi from tear down test case" << endl;
}

ValidatorFixture::ValidatorFixture()
{
    cout << "\nConstructure called" << endl;
}

ValidatorFixture::~ValidatorFixture()
{
    cout << "Destructor called\n" << endl;
}

// TEST_F is used for running tests with body that differs

TEST_F(ValidatorFixture, OutOfRange) {
    bool res = p_val->insideInterval(-1);
    ASSERT_EQ(false, res);
}

TEST_F(ValidatorFixture, InRange) {
    bool res = p_val->insideInterval(7);
    ASSERT_EQ(true, res);
}

// TEST_P is used for running several tests with the same body

TEST_P(ValidatorFixture, TestInRange)
{
    auto [arg, expected] = GetParam();
    bool res = p_val->insideInterval(arg);
    ASSERT_EQ(expected, res);
}

INSTANTIATE_TEST_SUITE_P(InRange, ValidatorFixture, testing::Values(
        make_pair(-1, false),
        make_pair(1, true),
        make_pair(5, true),
        make_pair(10, true),
        make_pair(12, false)
));

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}