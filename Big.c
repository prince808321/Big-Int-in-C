#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 260

typedef struct BigInteger
{
    int *array;
    int sign;
    int length;
} BigInt;


void printBigInteger(BigInt *b)
{
    int i;
    if (b->sign == 1)
        printf("-");
    for (i = b->length - 1; i >= 0; i--)
        printf("%d", b->array[i]);
}

BigInt stringToInteger(char *s)
{
    BigInt b;
    int size = strlen(s);
    if (s[0] == '-')
    {
        b.sign = 1;
    }
    else
        b.sign = 0;
    b.length = size - b.sign;
    b.array = (int *)malloc(sizeof(int) * (b.length));
    int *i;
    i = b.array;
    size--;
    while (size >= b.sign)
    {
        *(i) = s[size] - '0';
        i++;
        size--;
    }
    return b;
}

BigInt *AdditionBigIntegers(BigInt *a, BigInt *b);
BigInt *SubtractionBigInteger(BigInt *a, BigInt *b);

int Compare(BigInt *a, BigInt *b)
{
    int i, retval;
    if (a->length == b->length)
    {
        i = (a->length) - 1;
        while (i >= 0 && a->array[i] == b->array[i])
        {
            i--;
        }
        if (i < 0)
        {
            retval = 0;
        }
        else
        {
            retval = (a->array[i]) - (b->array[i]);
        }
    }
    else
    {
        retval = (a->length) - (b->length);
    }
    return retval;
}
// adding two integres using passing pointers
BigInt *AdditionBigIntegers(BigInt *a, BigInt *b)
{
    int n1 = a->length;
    int n2 = b->length;
    int carry;
    BigInt *sum = (BigInt *)malloc(sizeof(BigInt));
    if (n2 > n1)
        sum->array = (int *)malloc(sizeof(int) * (n2 + 1));
    else
        sum->array = (int *)malloc(sizeof(int) * (n1 + 1));

    if (a->sign == b->sign)
    {
        sum->sign = a->sign;

        carry = 0;
        int i = 0, digit;
        while (i < n1 && i < n2)
        {
            digit = (a->array[i]) + (b->array[i]) + carry;
            carry = digit / 10;
            digit = digit % 10;
            sum->array[i] = digit;
            i++;
        }
        while (i < n1)
        {
            digit = (a->array[i]) + carry;
            carry = digit / 10;
            digit = digit % 10;
            sum->array[i] = digit;
            i++;
        }
        while (i < n2)
        {
            digit = (b->array[i]) + carry;
            carry = digit / 10;
            digit = digit % 10;
            sum->array[i] = digit;
            i++;
        }
        while (carry != 0)
        {
            sum->array[i] = (carry % 10);
            carry /= 10;
            i++;
        }
        sum->length = i;
    }
    else
    {
        if (a->sign == 1)
        {
            a->sign = 0;
            sum = SubtractionBigInteger(b, a);
            a->sign = 1;
        }
        else
        {
            b->sign = 0;
            sum = SubtractionBigInteger(a, b);
            b->sign = 1;
        }
    }
    return sum;
}
BigInt *subtraction(BigInt *a, BigInt *b)
{
    BigInt *diff = (BigInt *)malloc(sizeof(BigInt));
    diff->array = (int *)malloc(sizeof(int) * (a->length));
    int bor = 0;
    int i = 0, digit;
    while (i < b->length)
    {
        digit = (a->array[i]) - (b->array[i]) - bor;
        if (digit < 0)
        {
            bor = 1;
            digit += 10;
        }
        else
        {
            bor = 0;
        }
        diff->array[i] = digit;
        i++;
    }
    while (i < a->length)
    {
        digit = (a->array[i]) - bor;
        if (digit < 0)
        {
            bor = 1;
            digit += 10;
        }
        else
        {
            bor = 0;
        }
        diff->array[i] = digit;
        i++;
    }
    diff->length = i;
    return diff;
}

// subtraction of two big integers using paas by refrence
BigInt *SubtractionBigInteger(BigInt *a, BigInt *b)
{
    int n1 = a->length;
    int n2 = b->length;
    BigInt *diff = (BigInt *)malloc(sizeof(BigInt));
    if (n2 > n1)
        diff->array = (int *)malloc(sizeof(int) * n2);
    else
        diff->array = (int *)malloc(sizeof(int) * n1);

    if (a->sign != b->sign)
    {
        if (b->sign == 1)
        {
            b->sign = 0;
            diff = AdditionBigIntegers(a, b);
            b->sign = 1;
            diff->sign = 0;
        }
        else
        {
            b->sign = 1;
            diff = AdditionBigIntegers(a, b);
            b->sign = 0;
            diff->sign = 1;
        }
    }
    else
    {
        if (Compare(a, b) > 0)
        {
            diff = subtraction(a, b);
            diff->sign = a->sign;
        }
        else
        {
            diff = subtraction(b, a);
            if (a->sign == 0)
                diff->sign = 1;
            else
                diff->sign = 0;
        }
    }
    return diff;
}
// Multiplying two big integers using passing pointers
BigInt *MultiplicationBigIntegers(BigInt *a, BigInt *b)
{
    BigInt *mult = (BigInt *)malloc(sizeof(BigInt));
    mult->length = a->length + b->length;
    mult->array = (int *)malloc(sizeof(int) * (mult->length));
    int i, j, carry, prod;

    for (i = 0; i < mult->length; i++)
        mult->array[i] = 0;

    for (i = 0; i < a->length; i++)
    {
        carry = 0;
        for (j = 0; j < b->length; j++)
        {
            prod = (a->array[i] * b->array[j]) + carry;
            carry = prod / 10;
            mult->array[i + j] += (prod % 10);
            if (mult->array[i + j] > 9)
            {
                mult->array[i + j + 1] += 1;
                (mult->array[i + j]) %= 10;
            }
        }
        while (carry != 0)
        {
            mult->array[i + j] += (carry % 10);
            if (mult->array[i + j] > 9)
            {
                mult->array[i + j + 1] += 1;
                (mult->array[i + j]) %= 10;
            }
            carry /= 10;
            j++;
        }
    }

    if (a->sign == b->sign)
        mult->sign = 0;
    else
        mult->sign = 1;

    i = mult->length - 1;
    while (mult->array[i] == 0)
    {
        i--;
        (mult->length)--;
    }
    if (mult->length == 0)
    {
        mult->sign = 0;
        mult->length = 1;
    }
    return mult;
}

int main()
{
    BigInt first, second;
    char *n1, *n2;
    n1 = (char *)malloc(sizeof(char) * SIZE);
    n2 = (char *)malloc(sizeof(char) * SIZE);

    printf("Enter first Number : ");
    scanf("%s", n1);
    printf("Enter Second Number : ");
    scanf("%s", n2);
     printf("_____________\n");
    first = stringToInteger(n1); 
    second = stringToInteger(n2);

    BigInt *result = AdditionBigIntegers(&first, &second);
    printf("Sum OF two Big Integer Numbers : ");
    printBigInteger(result);

    result = SubtractionBigInteger(&first, &second);
    printf("\nDifference OF two  Big Integer Numbers : ");
    printBigInteger(result);

    result = MultiplicationBigIntegers(&first, &second);
    printf("\nMultiplication OF two Big Integer Numbers : ");
    printBigInteger(result);

    return 0;
}