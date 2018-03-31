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
 * $Id: OperatorTable.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <OperatorTable.h>
#include <EncryptDecrypt.h>

/**
 * Create an empty table of operators.
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_create)(void)
{
    OperatorTable*operatable;
    operatable=(OperatorTable*)malloc(sizeof(OperatorTable));
    if(operatable==NULL)
    {
        printf("malloc error");
        exit(1);
    }
    else
    {
        operatable->recordCount=0;
        operatable->records=NULL;
    }
    return operatable;
    /*return provided_OperatorTable_create();*/
}

/** Free a table of operators.
 * @param table a pointer to the table to free
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_destroy)(OperatorTable * table)
{
    free(table->records);
    free(table);
    /*provided_OperatorTable_destroy(table);*/
}

/** Load a table of operators from a file.
 * @param filename the file name
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_loadFromFile)(const char * filename)
{
    FILE*fp;
    fp=fopen(filename,"r+");
    if(fp == NULL)
    { fatalError("open file error"); }

    OperatorTable*table;
    table=IMPLEMENT(OperatorTable_create)();
    char temp1[OPERATORTABLE_MAXNAMESIZE];
    char temp2[OPERATORTABLE_MAXPASSWORDSIZE];
    while(fgets(temp1,OPERATORTABLE_MAXNAMESIZE,fp) != NULL)
    {
       if(fgets(temp2,OPERATORTABLE_MAXPASSWORDSIZE,fp) != NULL)
       {
           temp1[IMPLEMENT(stringLength)(temp1)-1]='\0';
           temp2[IMPLEMENT(stringLength)(temp2)-1]='\0';
           IMPLEMENT(decrypt)(OperatorCryptKey, temp1);
           IMPLEMENT(decrypt)(OperatorCryptKey, temp2);
           IMPLEMENT(OperatorTable_setOperator)(table, temp1, temp2);
           memset(temp1,0,OPERATORTABLE_MAXNAMESIZE);
           memset(temp2,0,OPERATORTABLE_MAXPASSWORDSIZE);
       }
    }
    fclose(fp);
    return table;
   /* return provided_OperatorTable_loadFromFile(filename);*/
}

/** Save a table of operators to a file.
 * @param table the table of operators
 * @param filename the file name
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_saveToFile)(OperatorTable * table, const char * filename)
{
    FILE*fp;
    fp=fopen(filename,"w+");
    if(fp == NULL)
    { fatalError("open file error"); }

    char *temp1,*temp2;
    int i=0;
    while(i<(table->recordCount))
    {
       temp1=IMPLEMENT(duplicateString)(table->records[i][0]);
       temp2=IMPLEMENT(duplicateString)(table->records[i][1]);
       IMPLEMENT(encrypt)(OperatorCryptKey, temp1);
       IMPLEMENT(encrypt)(OperatorCryptKey, temp2);
       fputs(temp1,fp);
       fputc('\n',fp);
       fputs(temp2,fp);
       fputc('\n',fp);
       i++;
    }
    fclose(fp);
   /* provided_OperatorTable_saveToFile(table, filename);*/
}

/** Get the number of records of a table of operators
 * @param table the table of operators
 * @return the number of records
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_getRecordCount)(OperatorTable * table)
{
    return table->recordCount;
    /*return provided_OperatorTable_getRecordCount(table);*/
}

/** Get the name of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record number
 * @return the name of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getName)(OperatorTable * table, int recordIndex)
{
    return table->records[recordIndex][0];
    /*return provided_OperatorTable_getName(table, recordIndex);*/
}

/** Get the password of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record index
 * @return the paswword of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getPassword)(OperatorTable * table, int recordIndex)
{
     return table->records[recordIndex][1];
     /*return provided_OperatorTable_getPassword(table, recordIndex);*/
}

/** Get the record index associated with an operator name.
 * @param table the table of operators
 * @param name the name of the operator
 * @return the index of the operator or -1 if the operator is not in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_findOperator)(OperatorTable * table, const char * name)
{
    int i;
    int a = OperatorTable_getRecordCount(table);
    for(i= 0; i< a; i++)
    {
        if(icaseCompareString(name, table->records[i][0]) == 0)
            return i;
    }
    return  -1;
    /*return provided_OperatorTable_findOperator(table, name);*/
}

/** Define or change the password of an operator
 * @param table the table of operators
 * @param name the name of the operator
 * @param password the password of the operator
 * @return the index of the operator in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_setOperator)(OperatorTable * table, const char * name, const char * password)
{
   long unsigned int count=(long unsigned int)(table->recordCount);
   int find=IMPLEMENT(OperatorTable_findOperator)(table,name);
   if(find != -1)
   {
     free(table->records[find][1]);
     /*table->records[find][1]=IMPLEMENT(duplicateString)(password);*/
     char*temp1;
     temp1=(char*)malloc(sizeof(char)*OPERATORTABLE_MAXPASSWORDSIZE);
     IMPLEMENT(copyStringWithLength)(temp1, password,stringLength(password));
     temp1[stringLength(password)]='\0';
     table->records[find][1]=temp1;

     return find;
   }
   else
   {
       table->records=(char***)realloc(table->records,sizeof(char**)*(count+1));
       if(table->records==NULL)
       {
           fatalError("realloc error");
       }
       else
       {
         table->records[count]=(char**)malloc(sizeof(char*)*2);
         if(table->records[count] == NULL)
         {
            fatalError("malloc error");
         }
         else
         {
        /* table->records[count][0]=IMPLEMENT(duplicateString)(name);*/
         char*temp;
         temp=(char*)malloc(sizeof(char)*OPERATORTABLE_MAXNAMESIZE);
         IMPLEMENT(copyStringWithLength)(temp, name,stringLength(name));
         temp[stringLength(name)]='\0';
         table->records[count][0]=temp;
         /*table->records[count][1]=IMPLEMENT(duplicateString)(password);*/
         char*temp2;
         temp2=(char*)malloc(sizeof(char)*OPERATORTABLE_MAXPASSWORDSIZE);
         IMPLEMENT(copyStringWithLength)(temp2, password,stringLength(password));
         temp2[stringLength(password)]='\0';
         table->records[count][1]=temp2;

         table->recordCount++;
         }
         return (int)(count);
       }
   }
  /*return provided_OperatorTable_setOperator(table, name, password);*/
}

/** Remove an operator from the table.
 * @param table the table of operators
 * @param recordIndex the index of the record to remove
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_removeRecord)(OperatorTable * table, int recordIndex)
{
   int count=table->recordCount;
   int i=0;
   while(i < recordIndex)
   {
      IMPLEMENT(copyStringWithLength)(table->records[i][0],table->records[i][0],IMPLEMENT(stringLength)(table->records[i][0]) /*OPERATORTABLE_MAXNAMESIZE*/);
      IMPLEMENT(copyStringWithLength)(table->records[i][1],table->records[i][1],IMPLEMENT(stringLength)(table->records[i][1]) /*OPERATORTABLE_MAXPASSWORDSIZE*/);
      i++;
   }
   while(i<count-1)
   {
      IMPLEMENT(copyStringWithLength)(table->records[i][0],table->records[i+1][0], OPERATORTABLE_MAXNAMESIZE);
      IMPLEMENT(copyStringWithLength)(table->records[i][1],table->records[i+1][1], OPERATORTABLE_MAXPASSWORDSIZE);
      i++;
   }
   table->recordCount--;
   return;
   /*provided_OperatorTable_removeRecord(table, recordIndex);*/
}

