/*
 * Copyright 2010 Sébastien Aupetit <sebastien.aupetit@univ-tours.fr>
 *
 * This source code is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this source code. If not, see <http://www.gnu.org/licenses/>.
 *
 * $Id: MyString.c 293 2011-10-02 15:05:44Z sebtic $
 */

#include <MyString.h>
#include <limits.h>

/** Like the tolower() function. It converts the letter c to lower case, if possible.
 * @param c the letter to convert
 * @return the lower case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toLowerChar)(char c)
{
    if((c >= 'A') && (c <= 'Z'))
	return (char)(c+'a'-'A');
	else
	return c;
	/*return provided_toLowerChar(c);*/
}

/** Like the toupper() function. It converts the letter c to upper case, if possible.
 * @param c the letter to convert
 * @return the upper case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toUpperChar)(char c)
{
    if((c >= 'a') && (c <= 'z'))
	return (char)(c-'a'+'A');
	else
	return c;
	/*return provided_toUpperChar(c);*/
}

/** Like the strcmp() function. It compares the two strings str1 and str2.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(compareString)(const char * str1, const char * str2)
{
    int i=0;
    if((*str1)=='\0' && (*str2)!='\0')
        {i=-1;}
    else if((*str1)!='\0' && (*str2)=='\0')
        {i=1;}
    else
    while(((*str1)!='\0')&&((*str2)!='\0'))
    {   if((*str1)==(*str2))
        {str1=str1 + 1;
         str2=str2 + 1;}
        else if((*str1)>(*str2))
               {i=1;
                break;}
        else if((*str1)<(*str2))
               {i=-1;
                break;}
    }
        if(/*(*str1)=='\0' && */(*str2)!='\0')
        {i=-1;}
    else if((*str1)!='\0' /*&&  (*str2)=='\0'*/)
        {i=1;}
    return i;
    /*return provided_compareString(str1, str2);*/
}

/** Like the strcasecmp() function. It compares the two strings str1 and str2, ignoring the case of the characters.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(icaseCompareString)(const char * str1, const char * str2)
{
    int i=0;
    if((*str1)=='\0' && (*str2)!='\0')
        {i=-1;}
    else if((*str1)!='\0' && (*str2)=='\0')
        {i=1;}
    else
    while(((*str1)!='\0')&&((*str2)!='\0'))
    {   if(IMPLEMENT(toLowerChar)(*str1) == IMPLEMENT(toLowerChar)(*str2))
        {str1=str1 + 1;
         str2=str2 + 1;}
        else if(IMPLEMENT(toLowerChar)(*str1)>IMPLEMENT(toLowerChar)(*str2))
               {i=1;
                break;}
        else if(IMPLEMENT(toLowerChar)(*str1)<IMPLEMENT(toLowerChar)(*str2))
               {i=-1;
                break;}
    }
        if(/*(*str1)=='\0' &&*/ (*str2)!='\0')
        {i=-1;}
    else if((*str1)!='\0' /*&& (*str2)=='\0'*/)
        {i=1;}
    return i;
    /*return provided_icaseCompareString(str1, str2);*/
}

/** Like the strlen() function. It calculates the length of the string str, not including the terminating '\\0' character.
 * @param str the string
 * @return the number of characters in str.
 */
size_t IMPLEMENT(stringLength)(const char * str)
{
    size_t length=0;
    while(*str != '\0')
    {
        length=length+1;
        str++;
    }
    return length;
    /*return provided_stringLength(str);*/
}

/** Copy the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 *
 * @param dest the destination string
 * @param src the source string
 */
void IMPLEMENT(copyString)(char * dest, const char * src)
{
    fprintf(stderr,
            "You should avoid strcpy and copyString. Use strncpy or copyStringWithLength instead\n");
    copyStringWithLength(dest, src, INT_MAX);
}

/** Copy the first destSize characters of the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 * @warning If src is longer than destSize characters, the string is truncated and the terminating null byte ('\\0') is added.
 *
 * @param dest the destination string
 * @param src the source string
 * @param destSize the maximal number of characters to copy
 */
void IMPLEMENT(copyStringWithLength)(char * dest, const char * src, size_t destSize)
{
   size_t i=0;
   size_t j=IMPLEMENT(stringLength)(src);
   if(destSize<=1)
    { *dest='\0';
      return;}
   else if ((destSize>1) && (destSize<j))
       {
           while(i < (destSize-1))
            {
                dest[i] = src[i];
                 i++;
            }
            dest[i]='\0';
            return;
       }
  else if(destSize>=j)
        {
            while(*src != '\0')
            {
                *dest=*src;
                dest++;
                src++;
                i++;
            }
            while(i<destSize)
            {
                *dest = '\0';
                dest++;
                i++;
            }
            return;
       }

    /*provided_copyStringWithLength(dest, src, destSize);*/
}


/** Like the strdup() function. It creates a copy of the string on the heap.
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str the string to duplicate
 */
char * IMPLEMENT(duplicateString)(const char * str)
{
    size_t length=IMPLEMENT(stringLength)(str);
    char *res;
    res=(char*)malloc((length+1)*sizeof(char));
    IMPLEMENT(copyStringWithLength)(res,str,length+1);
    return res;
    /*return provided_duplicateString(str);*/
}

/** Test if the string str begins by the string start, ignoring the case of the characters.
 * @param start the string which should be at the beginning of str
 * @param str the string to test
 * @return a non null number (true) if the str begins with the string start, false otherwise
 */
int IMPLEMENT(icaseStartWith)(const char * start, const char * str)
{
    int i=1;
    while (((*str) != '\0') && (toUpperChar(*start) != '\0') && (i==1))
        {
            if (IMPLEMENT(toUpperChar)(*str) == IMPLEMENT(toUpperChar)(*start))
           {
               str++;
               start++;
           }
            else
                {
                    i=0;
                }
        }
    return i;
    /*return provided_icaseStartWith(start, str);*/
}

/** Test if the string str ends by the string start, ignoring the case of the characters.
 * @param end the string which should be at the end of str
 * @param str the string to test
 * @return a non null number (true) if the str ends with the string end, false otherwise
 */
int IMPLEMENT(icaseEndWith)(const char * end, const char * str)
{
    int i=1;
    int k=0;
    size_t j=IMPLEMENT(stringLength)(str)-IMPLEMENT(stringLength)(end);
    while ((toUpperChar(*(end+k)) != '\0') && (toUpperChar(*(str+j+k)) != '\0') && (i==1))
    {
        if(IMPLEMENT(toUpperChar)(*(end+k)) == IMPLEMENT(toUpperChar)(*(str+j+k)))
            k++;
        else
            i=0;
    }
    return i;
    /*return provided_icaseEndWith(end, str);*/
}

/** Create a new string on the heap which is the result of the concatenation of the two strings.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str1 the first string
 * @param str2 the second string
 * @return the new string
 */
char * IMPLEMENT(concatenateString)(const char * str1, const char * str2)
{
    size_t lengtha=IMPLEMENT(stringLength)(str1);
    size_t lengthb=IMPLEMENT(stringLength)(str2);
    char *res;
    res=(char*)malloc((lengtha+lengthb+1)*sizeof(char));
    int n=0,i=0,j=0;
    while(*(str1+i) != '\0')
    {
        *(res+n) = *(str1+i);
        n++;
        i++;
    }
    while(*(str2+j) != '\0')
    {
       *(res+n) = *(str2+j);
        n++;
        j++;
    }
    *(res+n) = '\0';
    return res;
    /*return provided_concatenateString(str1, str2);*/
}

/** Like the index() function. It returns a pointer to the first occurrence of the character c in the string str.
 * @param str the string to search in
 * @param c the character to find
 * @return a pointer to the first occurrence of the character c in the string str if c is in str, NULL otherwise
 */
const char * IMPLEMENT(indexOfChar)(const char *str, char c)
{
    if(*str == '\0')
    {return NULL;}
    else
    {while(*str!='\0')
    {
        if(*str==c)
            return str;
        else
            str++;

    }
    }
    if(*str == '\0')
    {return NULL;}
    else
    {return str;}
    /*return provided_indexOfChar(str, c);*/
}

/** Create a copy on the heap of part of a string. The new string contains the characters pointed from start (inclusive) to end (exclusive).
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param start a pointer to the first character of the new string
 * @param end a pointer to the next character of the new string (the pointed character is not part of the new string)
 * @return the new string
 *
 * @code
 * char * str = "abcdef";
 * char * s1 = subString(str,str);
 * char * s2 = subString(str,str+strlen(str));
 * char * s3 = subString(str+1,str+2);
 *
 * We get:
 *    s1: "";
 *    s2: "abcdef";
 *    s3: "b";
 * @endcode
 */
char * IMPLEMENT(subString)(const char * start, const char * end)
{
     size_t a=IMPLEMENT(stringLength)(start);
     size_t b=IMPLEMENT(stringLength)(end);
     size_t i=0;
     char *res;
     res=(char*)malloc((a-b+1)*sizeof(char));
     if(*start == *end)
     {
        memset(res,'\0',(a-b+1)*sizeof(char));
        while(i<a-b)
        {
           res[i]='\0';
           i++;
        }
        return res;
     }
     else
     {
        memset(res,'\0',(a-b+1)*sizeof(char));
        while(start[i] != *end)
        {
           res[i]=start[i];
           i++;
        }
        return res;
     }
     /*return provided_subString(start, end);*/
}

/** Like the strstr() function. It returns a pointer to the first occurrence of the string aiguille in the string meule_de_foin.
 * @param meule_de_foin the string to search in
 * @param aiguille the string to find
 * @return a pointer to the first occurrence of the string aiguille in the string meule_de_foin if aiguille is in meule_de_foin, NULL otherwise
 */
const char * IMPLEMENT(indexOfString)(const char *meule_de_foin, const char *aiguille)
{
    size_t i=0;
    size_t j=0;
    while((*(meule_de_foin+i+j) != '\0') && (*(aiguille+j) != '\0'))
    {
       if (*(meule_de_foin+i+j) == *(aiguille+j))
       {  j++;
       }
       else
       {
          i++;
          j=0;
       }
    }
    if(j != 0)
    {return meule_de_foin+i;}
    else
    {return NULL;}
    /*return provided_indexOfString(meule_de_foin, aiguille);*/
}

/** Convert a string to upper case.
 * @param str the string to convert
 */
void IMPLEMENT(makeUpperCaseString)(char * str)
{
    while ((*str) != '\0')
        {*str = IMPLEMENT(toUpperChar)(*str);
         str++;}
    return;
    /*provided_makeUpperCaseString(str);*/
}

/** Convert a string to lower case.
 * @param str the string to convert
 */
void IMPLEMENT(makeLowerCaseString)(char * str)
{
    while ((*str) != '\0')
        {*str = IMPLEMENT(toLowerChar)(*str);
         str++;}
    return;
    /*provided_makeLowerCaseString(str);*/
}

/** Create a new string on the heap which contents is the result of the insertion in src of insertLength characters from  toBeInserted at position insertPosition.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param src the string in which the insertion is done
 * @param insertPosition the position where the insertion is done
 * @param toBeInserted a pointer on the first character to insert
 * @param insertLength the number of character to insert
 * @return the new string
 */
char * IMPLEMENT(insertString)(const char * src, int insertPosition, const char * toBeInserted,
        int insertLength)
{
    size_t srclength=IMPLEMENT(stringLength)(src);
    char *res;
    res=(char*)malloc((srclength+(size_t)(insertLength)+1)*sizeof(char));
    int i=0;/**pour src*/
    int n=0;/**pour res*/
    int j=0;/**pour toBeInserted*/
    while (n<insertPosition)
    {
        *(res+n) = *(src+i);
        n++;
        i++;
    }
    while (j<insertLength)
    {
        *(res+n) = *(toBeInserted+j);
        n++;
        j++;
    }
    while (*(src+i) != '\0')
    {
        *(res+n) = *(src+i);
        n++;
        i++;
    }
    *(res+n) = '\0';
    return res;
    /*return provided_insertString(src, insertPosition, toBeInserted, insertLength);*/
}
