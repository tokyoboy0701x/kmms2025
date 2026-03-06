#include <gtest/gtest.h>
#include "long_number.hpp"

TEST(LongNumberArithmeticTest, Addition) {
    {
        ordo::LongNumber a("123");
        ordo::LongNumber b("456");
        ordo::LongNumber c = a + b;
        ordo::LongNumber expected("579");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a1("-123");
        ordo::LongNumber b1("456");
        ordo::LongNumber c1 = a1 + b1;
        ordo::LongNumber expected("333");
        EXPECT_TRUE(c1 == expected);
    }
    
    {
        ordo::LongNumber a2("123");
        ordo::LongNumber b2("-456");
        ordo::LongNumber c2 = a2 + b2;
        ordo::LongNumber expected("-333");
        EXPECT_TRUE(c2 == expected);
    }
    {
        ordo::LongNumber a3("-123");
        ordo::LongNumber b3("-456");
        ordo::LongNumber c3 = a3 + b3;
        ordo::LongNumber expected("-579");
        EXPECT_TRUE(c3 == expected);
    }
    {
        ordo::LongNumber a("999999999999999999");
        ordo::LongNumber b("1");
        ordo::LongNumber c = a + b;
        ordo::LongNumber expected("1000000000000000000");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a("999999999999999999");
        ordo::LongNumber b("999999999999999999");
        ordo::LongNumber c = a + b;
        ordo::LongNumber expected("1999999999999999998");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a("0");
        ordo::LongNumber b("12345");
        ordo::LongNumber c = a + b;
        ordo::LongNumber expected("12345");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a("-123");
        ordo::LongNumber b("123");
        ordo::LongNumber c = a + b;
        ordo::LongNumber expected("0");
        EXPECT_TRUE(c == expected);
    }
}

TEST(LongNumberArithmeticTest, Subtraction) {
    {
        ordo::LongNumber a("123");
        ordo::LongNumber b("456");
        ordo::LongNumber c = a - b;
        ordo::LongNumber expected("-333");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a1("-123");
        ordo::LongNumber b1("456");
        ordo::LongNumber c = a1 - b1;
        ordo::LongNumber expected("-579");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    
    {
        ordo::LongNumber a2("123");
        ordo::LongNumber b2("-456");
        ordo::LongNumber c = a2 - b2;
        ordo::LongNumber expected("579");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a3("-123");
        ordo::LongNumber b3("-456");
        ordo::LongNumber c = a3 - b3;
        ordo::LongNumber expected("333");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("999999999999999999");
        ordo::LongNumber b("1");
        ordo::LongNumber c = b - a;
        ordo::LongNumber expected("-999999999999999998");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("12345");
        ordo::LongNumber b("12345");
        ordo::LongNumber c = a - b;
        ordo::LongNumber expected("0");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a("1000000000000000");
        ordo::LongNumber b("1");
        ordo::LongNumber c = a - b;
        ordo::LongNumber expected("999999999999999");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a("-50");
        ordo::LongNumber b("30");
        ordo::LongNumber c = a - b;
        ordo::LongNumber expected("-80");
        EXPECT_TRUE(c == expected);
    }
}

TEST(LongNumberArithmeticTest, Multiplication) {
    {
        ordo::LongNumber a("123");
        ordo::LongNumber b("456");
        ordo::LongNumber c = a * b;
        ordo::LongNumber expected("56088");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a1("-123");
        ordo::LongNumber b1("456");
        ordo::LongNumber c = a1 * b1;
        ordo::LongNumber expected("-56088");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    
    {
        ordo::LongNumber a2("123");
        ordo::LongNumber b2("-456");
        ordo::LongNumber c = a2 * b2;
        ordo::LongNumber expected("-56088");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a3("-123");
        ordo::LongNumber b3("-456");
        ordo::LongNumber c = a3 * b3;
        ordo::LongNumber expected("56088");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("1000000000000000");
        ordo::LongNumber b("2");
        ordo::LongNumber c = b * a;
        ordo::LongNumber expected("2000000000000000");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("1000000000000000");
        ordo::LongNumber b("0");
        ordo::LongNumber c = b * a;
        ordo::LongNumber expected("0");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("123456789");
        ordo::LongNumber b("1");
        ordo::LongNumber c = a * b;
        ordo::LongNumber expected("123456789");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a("999999999");
        ordo::LongNumber b("999999999");
        ordo::LongNumber c = a * b;
        ordo::LongNumber expected("999999998000000001");
        EXPECT_TRUE(c == expected);
    }
}

TEST(LongNumberArithmeticTest, Division) {
    {
        ordo::LongNumber a("5");
        ordo::LongNumber b("2");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("2");
        EXPECT_TRUE(c == expected);
    }
    {
        ordo::LongNumber a("2");
        ordo::LongNumber b("5");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("0");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    
    {
        ordo::LongNumber a("-5");
        ordo::LongNumber b("2");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("-2");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("5");
        ordo::LongNumber b("-2");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("-2");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("-5");
        ordo::LongNumber b("-2");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("2");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("12345");
        ordo::LongNumber b("1");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("12345");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("12345");
        ordo::LongNumber b("12345");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("1");
        EXPECT_TRUE(c == expected) << "должно быть" << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("100");
        ordo::LongNumber b("2");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("50");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("1000");
        ordo::LongNumber b("2");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("500");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("-10000");
        ordo::LongNumber b("2");
        ordo::LongNumber c = a / b;
        ordo::LongNumber expected("-5000");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("123");
        ordo::LongNumber zero("0");
        EXPECT_THROW({
            ordo::LongNumber c = a / zero;
        }, std::runtime_error);
    }

}

TEST(LongNumberArithmeticTest, Modulus) {
    {
        ordo::LongNumber a("123");
        ordo::LongNumber b("5");
        ordo::LongNumber c = a % b;
        ordo::LongNumber expected("3");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("100");
        ordo::LongNumber b("3");
        ordo::LongNumber c = a % b;
        ordo::LongNumber expected("1");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("-123");
        ordo::LongNumber b("5");
        ordo::LongNumber c = a % b;
        ordo::LongNumber expected("-3");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("123");
        ordo::LongNumber b("-5");
        ordo::LongNumber c = a % b;
        ordo::LongNumber expected("3");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("7");
        ordo::LongNumber b("10");
        ordo::LongNumber c = a % b;
        ordo::LongNumber expected("7");
        EXPECT_TRUE(c == expected) << "должно быть " << expected << " получилось " << c;
    }
    {
        ordo::LongNumber a("123");
        ordo::LongNumber zero("0");
        EXPECT_THROW({
            ordo::LongNumber c = a % zero;
        }, std::runtime_error);
    }
}

TEST(LongNumberArithmeticTest, Comparison) {
    {
        ordo::LongNumber a("123");
        ordo::LongNumber b("123");
        EXPECT_TRUE(a == b);
    }
    {
        ordo::LongNumber a("-123");
        ordo::LongNumber b("-123");
        EXPECT_TRUE(a == b);
    }
    {
        ordo::LongNumber a("123");
        ordo::LongNumber b("456");
        EXPECT_TRUE(a != b);
    }
    {
        ordo::LongNumber a("456");
        ordo::LongNumber b("123");
        EXPECT_TRUE(a > b);
        EXPECT_TRUE(b < a);
    }
    {
        ordo::LongNumber a("-123");
        ordo::LongNumber b("-456");
        EXPECT_TRUE(a > b);
        EXPECT_TRUE(b < a);
    }
    {
        ordo::LongNumber a("0");
        ordo::LongNumber b("123");
        EXPECT_TRUE(a < b);
        EXPECT_TRUE(b > a);
    }
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}