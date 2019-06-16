#ifndef __MYTIME_H__
#define __MYTIME_H__
#include <time.h>
char * GetTime(void)
{
    time_t timep;
    time(&timep);
    char * p1 = ctime(&timep);
    char * p2 = p1;
    while(*p1 != '\0')
    {
        if(*p1 == '\n')
        {
            *p1 = ' ';
        }
        p1++;
    }
    return p2;
}
#endif
