#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "njson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void test_parse_null()
{
    NValue v;
    v.type = NType::False;
    EXPECT_EQ_INT(NParseResult::OK, NParse(&v, "null"));
    EXPECT_EQ_INT(NType::Null, NGetType(&v));
}

static void test_parse_expect_value()
{
    NValue v;

    v.type = NType::False;
    EXPECT_EQ_INT(NParseResult::ExpectValue, NParse(&v, ""));
    EXPECT_EQ_INT(NType::Null, NGetType(&v));

    v.type = NType::False;
    EXPECT_EQ_INT(NParseResult::ExpectValue, NParse(&v, " "));
    EXPECT_EQ_INT(NType::Null, NGetType(&v));
}

static void test_parse_invalid_value()
{
    NValue v;
    v.type = NType::False;
    EXPECT_EQ_INT(NParseResult::InvalidValue, NParse(&v, "nul"));
    EXPECT_EQ_INT(NType::Null, NGetType(&v));

    v.type = NType::False;
    EXPECT_EQ_INT(NParseResult::InvalidValue, NParse(&v, "?"));
    EXPECT_EQ_INT(NType::Null, NGetType(&v));
}

static void test_parse_root_not_singular()
{
    NValue v;
    v.type = NType::False;
    EXPECT_EQ_INT(NParseResult::RootNotSingular, NParse(&v, "null x"));
    EXPECT_EQ_INT(NType::Null, NGetType(&v));
}

static void test_parse()
{
    test_parse_null();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
