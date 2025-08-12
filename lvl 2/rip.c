#include <stdio.h>
#include <string.h>
#include <unistd.h>

int val(char *s)
{
    int open = 0;
    int close = 0;
    for (size_t i = 0; s[i]; i++)
    {
        if(s[i] == '(')
            open++;
        else if(s[i] == ')')
        {
            if(open > 0)
                open--;
            else 
                close++;
        }
    }
    return open + close;
}

void solve(char *s, int m_fix, int to_fix, int pos)
{
    if(m_fix == to_fix && val(s) == 0)
    {
        puts(s);
        return ;
    }
    for (size_t i = 0; s[i]; i++)
    {
        if(s[i] == '(' || s[i] == ')')
        {
            char c = s[i];
            s[i] = ' ';
            solve(s, m_fix, to_fix, i+1);
            s[i] = c;
        }
    }
    
}


int main(int ac, char **av)
{
    if(ac != 2)
     return 1;
    int m_fix = val(av[1]);
    solve(av[1], m_fix, 0, 0);
}