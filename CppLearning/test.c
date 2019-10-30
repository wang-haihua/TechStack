#include<stdio.h>
#include<stdlib.h>

char * longestPalindrome(char * s){
    int start = 0;
    int end = 0;
    int i = 0;
    int len = 1;
    int maxlen = 1;
    int index = 0;
    while(s[end] != '\0')
    {
        for(i = start; i<=end; i++)
        {
            if(s[end+1] == s[i])
                break;
        }
        if(i <= end)
        {
            start = i + 1;
        }
        end++;
        len = end - start + 1;
        if(maxlen < len)
        {
            maxlen = len;
            index = start;
        }
    }
    char * res = (char *)malloc(maxlen*sizeof(char));
    for(int j = 0; j < maxlen; j++ )
    {
        res[j] = s[index-1];
        index++;
    }
    return res;
}

int main()
{
    char * res = (char *)malloc(4*sizeof(char));
    char * s = {'a','b','c','a','d','f','e'};
    res = longestPalindrome(s);
    int end = 0;
    while(res[end]!=0)
    {
        printf("%c",res[end++]);
    }
    return 0;
}
