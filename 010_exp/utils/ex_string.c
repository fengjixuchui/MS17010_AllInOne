#include "ex_string.h"

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>


/********************************************************************
*  Function��  my_strstr()
*  Description: ��һ���ַ����в���һ���Ӵ�;
*  Input��      ps: Դ;      pd���Ӵ�
*  Return :    0��Դ�ַ�����û���Ӵ�; 1��Դ�ַ��������Ӵ�;
*********************************************************************/
static char * my_strstr(char * ps, char *pd)
{
    char *pt = pd;
    int c = 0;
    while (*ps != '\0')
    {
        if (*ps == *pd)
        {
            while (*ps == *pd && *pd != '\0')
            {
                ps++;
                pd++;
                c++;
            }
        }
        else
        {
            ps++;
        }
        if (*pd == '\0')
        {
            return (ps - c);
        }
        c = 0;
        pd = pt;
    }
    return 0;
}

/********************************************************************
*  Function��  my_memcpy()
*  Description: ����һ���ڴ�������һ������;
*  Input��      src: Դ;
count: �����ֽ���.
*  Output��      dest: ����Ŀ�ĵ�;
*  Return :      dest;
*********************************************************************/
static void * my_memcpy(void * dest, const void *src, size_t count)
{
    char *tmp = (char *)dest, *s = (char *)src;
    while (count--)
        *tmp++ = *s++;
    return dest;
}

/********************************************************************
*  Function��  str_replace()
*  Description: ��һ���ַ����в���һ���Ӵ������Ұ����з��ϵ��Ӵ���
��һ���滻�ַ����滻��
*  Input��      p_source:Ҫ���ҵ�ĸ�ַ����� p_seachҪ���ҵ����ַ���;
p_repstr���滻���ַ���;
*  Output��      p_result:��Ž��;
*  Return :      �����滻�ɹ����Ӵ�����;
*  Others:      p_resultҪ�㹻��Ŀռ��Ž�����������������Ҫ��\0����;
*********************************************************************/
static int _str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr)
{
    int c = 0;
    int repstr_leng = 0;
    int searchstr_leng = 0;
    char *p1;
    char *presult = p_result;
    char *psource = p_source;
    char *prep = p_repstr;
    char *pseach = p_seach;
    int nLen = 0;
    repstr_leng = strlen(prep);
    searchstr_leng = strlen(pseach);

    do
    {
        p1 = strstr(psource, p_seach);
        if (p1 == 0)
        {
            strcpy(presult, psource);
            return c;
        }
        c++;  //ƥ���Ӵ�������1;
        //printf("���:%s\r\n", p_result);
        //printf("Դ�ַ�:%s\r\n", p_source);
        // ������һ���滻�����һ���滻���м���ַ���
        nLen = p1 - psource;
        memcpy(presult, psource, nLen);
        // ������Ҫ�滻���ַ���
        memcpy(presult + nLen, p_repstr, repstr_leng);
        psource = p1 + searchstr_leng;
        presult = presult + nLen + repstr_leng;
    }
    while (p1);

    return c;
}

int replace_str(char *pStrBuf, char *pOld, char *pNew)
{
    int newLen = 0;
    char *pTmpBuf = NULL;

    newLen = strlen(pStrBuf) + 1000;
    pTmpBuf = (char *)malloc(newLen);
    if(pTmpBuf == NULL)
        return -1;
    memset(pTmpBuf, 0x00, newLen);

    if(_str_replace(pTmpBuf, pStrBuf, pOld, pNew) <= 0)
    {
        free(pTmpBuf);
        return -2;
    }
    memset(pStrBuf, 0x00, strlen(pStrBuf));
    strcat(pStrBuf, pTmpBuf);
    free(pTmpBuf);

    return 0;
}

char *upper_str(char *pStr)
{
    static char upStrBuf[65536];
    int idx;

    memset(upStrBuf, 0x00, sizeof(upStrBuf));

    for(idx = 0; pStr[idx] != NULL; ++idx)
    {
        if(pStr[idx] >= 'a' && pStr[idx] <= 'z')
        {
            upStrBuf[idx] = pStr[idx] - 32;
        }
        else
        {
            upStrBuf[idx] = pStr[idx];
        }
    }

    return upStrBuf;
}

char *lower_str(char *pStr)
{
    int idx;
    char *pNewBuf = NULL;

    pNewBuf = (char *)malloc(65536);
    if(pNewBuf == NULL)
        return NULL;

    memset(pNewBuf, 0x00, 65536);

    for(idx = 0; pStr[idx] != NULL; ++idx)
    {
        if(pStr[idx] >= 'A' && pStr[idx] <= 'Z')
        {
            pNewBuf[idx] = pStr[idx] + 32;
        }
        else
        {
            pNewBuf[idx] = pStr[idx];
        }
    }

    return pNewBuf;
}

char* strtok_r(
    char *str,
    const char *delim,
    char **nextp)
{
    char *ret;

    if (str == NULL)
    {
        str = *nextp;
    }

    str += strspn(str, delim);

    if (*str == '\0')
    {
        return NULL;
    }

    ret = str;

    str += strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}

//��������Ϊlength������ַ���
char* gen_random_string(int length)
{
    int flag, i;
    char* string;

    srand((unsigned)time(NULL));
    if ((string = (char *)malloc(length + 1)) == NULL )
    {
        return NULL ;
    }

    memset(string, 0x00, length + 1);

    for (i = 0; i < length; i++)
    {
        flag = rand() % 3;
        switch (flag)
        {
        case 0:
            string[i] = 'A' + rand() % 26;
            break;
        case 1:
            string[i] = 'a' + rand() % 26;
            break;
        case 2:
            string[i] = '0' + rand() % 10;
            break;
        default:
            string[i] = 'x';
            break;
        }
    }

    return string;
}

