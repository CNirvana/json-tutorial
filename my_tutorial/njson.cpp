#include "njson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

struct NContext
{
    const char* json;
};

static void NParseWhitespace(NContext* c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static NParseResult NParseNull(NContext* c, NValue* v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return NParseResult::InvalidValue;
    c->json += 3;
    v->type = NType::Null;
    return NParseResult::OK;
}

static int NParseValue(NContext* c, NValue* v) {
    switch (*c->json)
    {
        case 'n':  return NParseNull(c, v);
        case '\0': return NParseResult::ExpectValue;
        default:   return NParseResult::InvalidValue;
    }
}

int NParse(NValue* v, const char* json)
{
    NContext c;
    assert(v != NULL);
    c.json = json;
    v->type = NType::Null;
    NParseWhitespace(&c);
    return NParseValue(&c, v);
}

NType NGetType(const NValue* v)
{
    assert(v != NULL);
    return v->type;
}
