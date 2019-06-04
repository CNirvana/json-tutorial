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
    NJson json;
    NJsonValue v;
    v.type = NJsonType::False;

    EXPECT_EQ_INT(NJsonParseResult::OK, json.Parse(&v, "null"));
    EXPECT_EQ_INT(NJsonType::Null, json.GetType(&v));
}

static void test_parse_true()
{
    NJson json;
    NJsonValue v;
    v.type = NJsonType::False;

    EXPECT_EQ_INT(NJsonParseResult::OK, json.Parse(&v, "true"));
    EXPECT_EQ_INT(NJsonType::True, json.GetType(&v));
}

static void test_parse_false()
{
    NJson json;
    NJsonValue v;
    v.type = NJsonType::False;

    EXPECT_EQ_INT(NJsonParseResult::OK, json.Parse(&v, "false"));
    EXPECT_EQ_INT(NJsonType::False, json.GetType(&v));
}

static void test_parse_expect_value()
{
    NJson json;
    NJsonValue v;

    v.type = NJsonType::False;
    EXPECT_EQ_INT(NJsonParseResult::ExpectValue, json.Parse(&v, ""));
    EXPECT_EQ_INT(NJsonType::Null, json.GetType(&v));

    v.type = NJsonType::False;
    EXPECT_EQ_INT(NJsonParseResult::ExpectValue, json.Parse(&v, " "));
    EXPECT_EQ_INT(NJsonType::Null, json.GetType(&v));
}

static void test_parse_invalid_value()
{
    NJson json;
    NJsonValue v;
    v.type = NJsonType::False;
    EXPECT_EQ_INT(NJsonParseResult::InvalidValue, json.Parse(&v, "nul"));
    EXPECT_EQ_INT(NJsonType::Null, json.GetType(&v));

    v.type = NJsonType::False;
    EXPECT_EQ_INT(NJsonParseResult::InvalidValue, json.Parse(&v, "?"));
    EXPECT_EQ_INT(NJsonType::Null, json.GetType(&v));
}

static void test_parse_root_not_singular()
{
    NJson json;
    NJsonValue v;
    v.type = NJsonType::False;
    EXPECT_EQ_INT(NJsonParseResult::RootNotSingular, json.Parse(&v, "null x"));
    EXPECT_EQ_INT(NJsonType::Null, json.GetType(&v));
}

static void test_parse()
{
    test_parse_null();
    test_parse_true();
    test_parse_false();
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