#pragma once

enum NType
{
    Null,
    False,
    True,
    Number,
    String,
    Object
};

struct NValue
{
    NType type;
};

enum NParseResult
{
    OK = 0,
    ExpectValue,
    InvalidValue,
    RootNotSingular
};

int NParse(NValue* v, const char* json);

NType NGetType(const NValue* v);
