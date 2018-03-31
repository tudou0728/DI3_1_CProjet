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
 * $Id: DocumentUtil.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentUtil.h>

/** Create a new string on the heap which represents the parameter as a number in basis 36.
 * @param id the number to convert
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(computeDocumentNumber)(long id)
{
    char *res;
    res=(char*)malloc(50*sizeof(char));
    memset(res,0,50);
    long i=0;
    while(id != 0)
    {
       if(id%36 <=9)
       {
         res[i]=(char)(id%36 + 48);
         i++;
         id=id/36;
       }
       else
       {
         res[i]=(char)(id%36 + 55);
         i++;
         id=id/36;
       }
    }
    char a;
    long j=0;
    while (i != j)
    {
      a=res[j];
      res[j]=res[i-1];
      res[i-1]=a;
      i--;
      j++;
    }
    return res;
    /*return provided_computeDocumentNumber(id);*/
}
/** Create a new string on the heap which represents the date in the format DD/MM/YYYY.
 * @param day the day
 * @param month the month
 * @param year the year
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(formatDate)(int day, int month, int year)
{
    char *res;
    res=(char*)malloc(11* sizeof(char));
    memset(res,0,11);
    res[0]=(char)((day - day%10)/10 + 48);
    res[1]=(char)(day%10 +48);
    res[2]='/';
    res[3]=(char)(month - month%10 +48);
    res[4]=(char)(month%10 +48);
    res[5]='/';
    res[6]=(char)(year/1000 +48);
    res[7]=(char)((year - (year/1000) *1000 )/100 +48);
    res[8]=(char)((year%100)/10 +48);
    res[9]=(char)(year%10 +48);
    res[10]='\0';
    return res;
    /*return provided_formatDate(day, month, year);*/
}


/** Write a string in a binary file
 * @param str the string
 * @param file the file
 */
void IMPLEMENT(writeString)(const char * str, FILE * file)
{
    size_t length;
    if(file == NULL)
    { fatalError("open file error"); }
    length=IMPLEMENT(stringLength)(str);
    if(fwrite(&(length),sizeof(size_t),1,file)<1)
    {
      fatalError("write count error");
    }
    if(length>0)
    {
      if(fwrite(str,sizeof(char),(length),file) != length)
          { fatalError("write str error");  }
    }
    return;
  /* provided_writeString(str,file);*/
}

/** Read a string from a binary file
 * @param file the file
 * @return a new string created on the heap which contains the read string
 * @see writeString()
 */
char * IMPLEMENT(readString)(FILE * file)
{
    char *str;
    size_t length;
    if(file == NULL)
    { fatalError("open file error"); }

    if(fread(&length,sizeof(size_t),1,file)<1)
    { fatalError("read length error"); }

    str=(char*)malloc(sizeof(char)*(length+1));
    if(str==NULL)
    { fatalError("malloc error");}

    if(length>0)
    {  if(fread(str,sizeof(char)*length,1,file) != 1)
      { fatalError("read str error"); }
      *(str+length)='\0';
    }

    return str;
   /*return provided_readString(file);*/
}
