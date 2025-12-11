#include <stdio.h>
#include <stdlib.h> // change this to <stdlib.h>
#include <ctype.h>

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
    
    exit(1);
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int parce_plus(char **s);
int parce_darb(char **s);
int parce_9aws(char **s);

int parce_9aws(char **s)
{
    if(isdigit(**s))
    {
        int val = **s - '0';
        (*s)++;
        return val;
    }
    if(accept(s, '('))
    {
        int r = parce_plus(s);
        if(!expect(s, ')'))
            exit(1);
        return r;
    }
    unexpected(**s);
    return 0;
}

int parce_darb(char **s)
{
    int l = parce_9aws(s);
    while(accept(s, '*'))
    {
        int r = parce_9aws(s);
        l *= r;
    }
    return l;
}


int parce_plus(char **s)
{
    int l = parce_darb(s);
    while(accept(s, '+'))
    {
        int r = parce_darb(s);
        l += r;
    }
    return l; 
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    char *s = argv[1];
    if (!*s)
        unexpected(0);
    int r = parce_plus(&s);
    if(*s)
        unexpected(*s);
    printf("%d\n",r);
}