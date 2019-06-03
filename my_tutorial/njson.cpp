#include "njson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

void NJson::ParseWhitespace(NJsonContext* c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

NJsonParseResult NJson::ParseNull(NJsonContext* c, NJsonValue* v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return NJsonParseResult::InvalidValue;
    c->json += 3;
    v->type = NJsonType::Null;
    return NJsonParseResult::OK;
}

NJsonParseResult NJson::ParseValue(NJsonContext* c, NJsonValue* v)
{
    switch (*c->json)
    {
        case 'n':  return ParseNull(c, v);
        case '\0': return NJsonParseResult::ExpectValue;
        default:   return NJsonParseResult::InvalidValue;
    }
}

NJsonParseResult NJson::Parse(NJsonValue* v, const char* json)
{
    NJsonParseResult ret;

    NJsonContext c;
    assert(v != NULL);
    c.json = json;
    v->type = NJsonType::Null;
    ParseWhitespace(&c);

    if ((ret = ParseValue(&c, v)) == NJsonParseResult::OK)
    {
        ParseWhitespace(&c);
        if (*c.json != '\0')
        {
            ret = NJsonParseResult::RootNotSingular;
        }
    }

    return ret;
}

NJsonType NJson::GetType(const NJsonValue* v)
{
    assert(v != NULL);
    return v->type;
}