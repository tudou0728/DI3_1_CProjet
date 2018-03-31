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
 * $Id: PrintFormat.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <PrintFormat.h>
#include <Dictionary.h>

/** Initialize a print format
 * @param format a print format
 * @warning initialized print format should be finalized with PrintFormat_finalize()
 */
void IMPLEMENT(PrintFormat_init)(PrintFormat * format)
{
   char temp1[1];
   temp1[0]='\0';
   char temp2[1];
   temp2[0]='\0';
   char temp3[1];
   temp3[0]='\0';
   char temp4[1];
   temp4[0]='\0';

   format->name=temp1;
   format->header=temp2;
   format->row=temp3;
   format->footer=temp4;
   /*provided_PrintFormat_init(format);*/
}

/** Finalize a print format
 * @param format the print format
 */
void IMPLEMENT(PrintFormat_finalize)(PrintFormat * format)
{
  free(format->name);
  free(format->header);
  free(format->row);
  free(format->footer);
  /*provided_PrintFormat_finalize(format);*/
}

/** Load a print format from a file
 * @param format an initialized print format to fill
 * @param filename the file name
 */
static char *readLine(FILE*file);
void IMPLEMENT(PrintFormat_loadFromFile)(PrintFormat * format, const char * filename)
{
  FILE*fp;
  fp=fopen(filename,"rb+");
  if(fp==NULL)
  {fatalError("open file error");}

  fseek(fp,0,SEEK_SET);
  char *temp,*t;

  temp=readLine(fp)+6;
  (temp)[IMPLEMENT(stringLength)(temp)-1]='\0';
  format->name=IMPLEMENT(duplicateString)(temp);

  temp=readLine(fp);
  t=readLine(fp);
  while(((*t) != '.') && ((*(t+1)) != 'R') && ((*(t+2)) != 'O') && ((*(t+3)) != 'W'))
  {
     temp=IMPLEMENT(concatenateString)(temp, t);
     t=readLine(fp);
  }
  temp=(temp)+8;
  (temp)[IMPLEMENT(stringLength)(temp)-1]='\0';
  format->header=IMPLEMENT(duplicateString)(temp);

  temp=t;
  t=readLine(fp);
  while(((*t) != '.') && ((*(t+1)) != 'F') && ((*(t+2)) != 'O') && ((*(t+3)) != 'O') && ((*(t+4)) != 'T') && ((*(t+5)) != 'E') && ((*(t+6)) != 'R'))
  {
     temp=IMPLEMENT(concatenateString)(temp, t);
     t=readLine(fp);
  }
  temp=(temp)+5;
  (temp)[IMPLEMENT(stringLength)(temp)-1]='\0';
  format->row=IMPLEMENT(duplicateString)(temp);

  temp=t;
  t=readLine(fp);
  while(((*t) != '.') && ((*(t+1)) != 'E') && ((*(t+2)) != 'N') && ((*(t+3)) != 'D'))
  {
     temp=IMPLEMENT(concatenateString)(temp, t);
     t=readLine(fp);
  }
  temp=(temp)+8;
  (temp)[IMPLEMENT(stringLength)(temp)-1]='\0';
  format->footer=IMPLEMENT(duplicateString)(temp);

  return;
 /*provided_PrintFormat_loadFromFile(format, filename);*/
}

/**lire un ligne par un text*/
static char *readLine(FILE*file)
{
    char *res,*temp,buf[100];
    res=duplicateString("");
    memset(buf,'\0',100);
    while(feof(file)!=1)
    {
        if(fgets(buf,100,file) != NULL)
            {
                temp=concatenateString(res,buf);
                free(res);
                res=temp;
            }
        if(buf[stringLength(buf)-1] == '\n')
        {
            break;
        }
    }
    return res;
}
	
