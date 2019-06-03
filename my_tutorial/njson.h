#pragma once

enum NJsonType
{
    Null,
    False,
    True,
    Number,
    String,
    Object
};

struct NJsonValue
{
    NJsonType type;
};

struct NJsonContext
{
    const char* json;
};

enum NJsonParseResult
{
    OK = 0,
    ExpectValue,
    InvalidValue,
    RootNotSingular
};

class NJson
{
public:
    NJsonParseResult Parse(NJsonValue* v, const char* json);
    NJsonType GetType(const NJsonValue* v);

private:
    void ParseWhitespace(NJsonContext* c);
    NJsonParseResult ParseNull(NJsonContext* c, NJsonValue* v);
    NJsonParseResult ParseValue(NJsonContext* c, NJsonValue* v);
};