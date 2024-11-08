#include <gtest/gtest.h>
#include "mytime.h"


TEST(TimeTest, DefaultConstructor) {
    Time t;
    EXPECT_EQ(t.GetHours(), 0);
    EXPECT_EQ(t.GetMinutes(), 0);
    EXPECT_EQ(t.GetSeconds(), 0);
}

TEST(TimeTest, ParametrizedConstructor) {
    Time t(5, 30, 45);
    EXPECT_EQ(t.GetHours(), 5);
    EXPECT_EQ(t.GetMinutes(), 30);
    EXPECT_EQ(t.GetSeconds(), 45);
}

TEST(TimeTest, CopyConstructor) {
    Time t1(1, 15, 30);
    Time t2(t1);
    EXPECT_EQ(t1.GetHours(), t2.GetHours());
    EXPECT_EQ(t1.GetMinutes(), t2.GetMinutes());
    EXPECT_EQ(t1.GetSeconds(), t2.GetSeconds());
}


TEST(TimeTest, AssignmentOperator) {
    Time t1(2, 20, 30);
    Time t2 = t1;
    EXPECT_EQ(t1, t2);
}

TEST(TimeTest, AdditionOperator) {
    Time t(5, 30, 30);
    Time result = t + 90;
    EXPECT_EQ(result.GetHours(), 5);
    EXPECT_EQ(result.GetMinutes(), 32);
    EXPECT_EQ(result.GetSeconds(), 0);
}

TEST(TimeTest, SubtractionOperator) {
    Time t(5, 30, 30);
    Time result = t - 90; // 05:29:00
    EXPECT_EQ(result.GetHours(), 5);
    EXPECT_EQ(result.GetMinutes(), 28);  // провален намеренно
    EXPECT_EQ(result.GetSeconds(), 0);
}

TEST(TimeTest, EqualityOperator) {
    Time t1(2, 20, 30);
    Time t2(2, 20, 30);
    EXPECT_TRUE(t1 == t2);

    Time t3(2, 20, 31);
    EXPECT_FALSE(t1 == t3);
}


TEST(TimeTest, SetHours) {
    Time t;
    t.SetHours(10);
    EXPECT_EQ(t.GetHours(), 10);
}

TEST(TimeTest, SetMinutes) {
    Time t;
    t.SetMinutes(45);
    EXPECT_EQ(t.GetMinutes(), 45);
}

TEST(TimeTest, SetSeconds) {
    Time t;
    t.SetSeconds(59);
    EXPECT_EQ(t.GetSeconds(), 59);
}

TEST(TimeTest, ToSeconds) {
    Time t(1, 1, 1);
    EXPECT_EQ(t.ToSeconds(), 3661); // 1 * 3600 + 1 * 60 + 1 = 3661
}

TEST(TimeTest, Normalize) {
    Time t(1, 61, 70); // 1 hour, 61 minutes, 70 seconds
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 2);
    EXPECT_EQ(t.GetMinutes(), 2);
    EXPECT_EQ(t.GetSeconds(), 10);
}

TEST(TimeTest, NormalizeFail) {
    Time t(2, 59, 61); // 2 hours, 59 minutes, 61 seconds
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 3);  // провален намеренно
    EXPECT_EQ(t.GetMinutes(), 0);
    EXPECT_EQ(t.GetSeconds(), 1);
}


TEST(TimeTest, OutputOperator) {
    Time t(10, 20, 30);
    std::stringstream ss;
    ss << t;
    EXPECT_EQ(ss.str(), "10:20:30");
}


TEST(TimeTest, InputOperator) {
    Time t;
    std::stringstream ss("12:34:56");
    ss >> t;
    EXPECT_EQ(t.GetHours(), 12);
    EXPECT_EQ(t.GetMinutes(), 34);
    EXPECT_EQ(t.GetSeconds(), 56);
}
