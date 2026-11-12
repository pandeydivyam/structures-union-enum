// Unions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef union {
    int i;
    float f;
    char str[20];
} UnionData;

typedef struct {
    int i;
    float f;
    char str[20];
} StructData;

typedef enum { VALUE_INT, VALUE_FLOAT, VALUE_TEXT } ValueType;

typedef struct {
    UnionData data;
    ValueType type;
} ValueRecord;

int set_int(ValueRecord *r, int x) {
    r->data.i = x;
    r->type = VALUE_INT;
    return 1;
}

int set_float(ValueRecord *r, float x) {
    r->data.f = x;
    r->type = VALUE_FLOAT;
    return 1;
}

int set_text(ValueRecord *r, const char *s) {
    if (strlen(s) >= sizeof(r->data.str)) return 0;
    strcpy(r->data.str, s);
    r->type = VALUE_TEXT;
    return 1;
}

void display(ValueRecord *r) {
    switch (r->type) {
        case VALUE_INT: printf("%d\n", r->data.i); break;
        case VALUE_FLOAT: printf("%.2f\n", r->data.f); break;
        case VALUE_TEXT: printf("%s\n", r->data.str); break;
        default: printf("Invalid type\n");
    }
}

int main() {
    UnionData udata;
    StructData sdata;
    ValueRecord r[5] = {0};

    sdata.i = 10;
    sdata.f = 220.5;
    strcpy(sdata.str, "Struct Programming");

    udata.i = 10;
    printf("Union integer: %d\n", udata.i);
    strcpy(udata.str, "Union Programming");
    printf("Union text: %s\n", udata.str);
    udata.f = 220.5;
    printf("Union float: %.2f\n", udata.f);

    printf("\nUnion addresses:\n%p\n%p\n%p\n",
    (void *)&udata.i, (void *)&udata.str, (void *)&udata.f);

    printf("\nStructure addresses:\n%p\n%p\n%p\n",
    (void *)&sdata.i, (void *)&sdata.str, (void *)&sdata.f);

    printf("\nStructure offsets:\n");
    printf("i: %zu\nf: %zu\nstr: %zu\n",
    offsetof(StructData, i), offsetof(StructData, f),
    offsetof(StructData, str));

    printf("\nSize and alignment:\n");
    printf("Union: %zu Alignment: %zu\n",
    sizeof(UnionData), _Alignof(UnionData));
    printf("Structure: %zu Alignment: %zu\n",
    sizeof(StructData), _Alignof(StructData));

    printf("100 Unions: %zu bytes\n", 100 * sizeof(UnionData));
    printf("100 Structures: %zu bytes\n", 100 * sizeof(StructData));

    set_int(&r[0], 10);
    set_float(&r[1], 220.5);
    set_text(&r[2], "Union Programming");
    set_int(&r[3], 50);
    set_text(&r[4], "C Programming");

    set_int(&r[0], 10);
    set_text(&r[0], "Changed");
    set_float(&r[0], 45.5);

    printf("\nTagged records:\n");
    for (int i = 0; i < 5; i++) {
        printf("Record %d: ", i + 1);
        display(&r[i]);
    }

    printf("\nTagged record size: %zu\n", sizeof(ValueRecord));
    printf("Union size: %zu\n", sizeof(UnionData));
    printf("Structure size: %zu\n", sizeof(StructData));

    printf("\nMaximum string test: %s\n",
    set_text(&r[0], "1234567890123456789") ? "Valid" : "Invalid");

    printf("Long string test: %s\n",
    set_text(&r[0], "12345678901234567890") ? "Valid" : "Rejected");

    r[0].type = (ValueType)99;
    printf("Invalid tag test: ");
    display(&r[0]);

    return 0;
}
