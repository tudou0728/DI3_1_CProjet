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
 * $Id: DocumentRowList.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentRowList.h>
#include <DocumentUtil.h>

/** Initialize a row
 * @param row the row
 * @warning an initialized row must be finalized by DocumentRow_finalize() to free all resources
 */
void IMPLEMENT(DocumentRow_init)(DocumentRow * row)
{
    row->code=duplicateString("");
    row->designation=duplicateString("");
    row->quantity=0;
    row->unity=duplicateString("");
    row->basePrice=0;
    row->sellingPrice=0;
    row->discount=0;
    row->rateOfVAT=0;
    row->next=NULL;
    return;
    /*provided_DocumentRow_init(row);*/
}

/** Finalize a row
 * @param row the row
 * @warning document must have been initialized
 */
void IMPLEMENT(DocumentRow_finalize)(DocumentRow * row)
{
    free(row->code);
    free(row->designation);
    free(row->unity);
    row->next=NULL;
    /*provided_DocumentRow_finalize(row);*/
}

/** Create a new row on the heap and initialize it
 * @return the new row
 */
DocumentRow * IMPLEMENT(DocumentRow_create)(void)
{
    DocumentRow*row;
    row=(DocumentRow*)malloc(sizeof(DocumentRow));
    if(row==NULL)
    {
        printf("malloc row error");
        exit(1);
    }
    else
    {
        IMPLEMENT(DocumentRow_init)(row);
    }
    return row;
   /*return provided_DocumentRow_create();*/
}

/** Finalize and destroy a row previously created on the heap
 * @param row the row
 */
void IMPLEMENT(DocumentRow_destroy)(DocumentRow * row)
{
  IMPLEMENT(DocumentRow_finalize)(row);
  free(row);
  return;
  /*provided_DocumentRow_destroy(row);*/
}

/** Initialize a list of rows
 * @param list the address of the pointer on the first cell of the list
 */
void IMPLEMENT(DocumentRowList_init)(DocumentRow ** list)
{
    *list=NULL;
  /*provided_DocumentRowList_init(list);*/
}

/** Finalize a list of rows
 * @param list the address of the pointer on the first cell of the list
 * @note Each row of the list are destroyer using DocumentRow_destroy()
 */

void IMPLEMENT(DocumentRowList_finalize)(DocumentRow ** list)
{
   DocumentRow*a=*list;
   DocumentRow*b=*list;
   while(b->next != NULL)
   {
     a=b->next;
     b->next=NULL;
     IMPLEMENT(DocumentRow_destroy)(b);
     b=a;
   }
   IMPLEMENT(DocumentRow_destroy)(a);
   return;
   /*while(IMPLEMENT(DocumentRowList_getRowCount)(* list)>0)
    {
        IMPLEMENT(DocumentRow_destroy(*(list)));
        (*list)=(*list)->next;
    }
    free(*list);*/
    return;
   /*provided_DocumentRowList_finalize(list);*/
}

/** Get a pointer on the rowIndex-th row of the list
 * @param list the pointer on the first cell of the list
 * @param rowIndex the index of the requested row
 * @return a pointer on the rowIndex-th row of the list or NULL if the list contains less rows than the requested one
 */
DocumentRow * IMPLEMENT(DocumentRowList_get)(DocumentRow * list, int rowIndex) {
    int i=0;
    if(rowIndex<0)
    {
        return NULL;
    }
    else
    {
        while((i<rowIndex) && (list != NULL))
        {
            list=list->next;
            i++;
        }
        return list;
    }
  /*return provided_DocumentRowList_get(list, rowIndex);*/
}

/**
 * Get the number of rows in the list
 * @param list the pointer on the first cell of the list
 */
int IMPLEMENT(DocumentRowList_getRowCount)(DocumentRow * list)
{
    int rowcount=0;
    while(list != NULL)
    {
        list=list->next;
        rowcount++;
    }
    return rowcount;
    /*return provided_DocumentRowList_getRowCount(list);*/
}

/** Add a row at the end of the list
 * @param list the address of the pointer on the first cell of the list
 * @param row the row to add
 */
void IMPLEMENT(DocumentRowList_pushBack)(DocumentRow ** list, DocumentRow * row)
{
    if(*list == NULL)
    {
       (*list)=row;
       row->next=NULL;
    }
    else
    {
      DocumentRow*temp;
      temp=*list;
      while(temp->next != NULL)
      {
          temp=temp->next;
      }
      temp->next=row;
      row->next=NULL;
    }
    return;
   /*provided_DocumentRowList_pushBack(list, row);*/
}

/** Insert a row before a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertBefore)(DocumentRow ** list, DocumentRow * position, DocumentRow * row)
{
   int a=IMPLEMENT(DocumentRowList_getRowCount)(position);
   int b=IMPLEMENT(DocumentRowList_getRowCount)(*list);
   DocumentRow *temp;
   temp=*list;
   int i=0;
   if(a-b ==0)
   {
      row->next=*list;
      *list=row;
   }
   else
   {
     while(i < b-a-1)
    {
       temp=temp->next;
       i++;
    }
    row->next=temp->next;
    temp->next=row;
   }
   return;
   /*provided_DocumentRowList_insertBefore(list, position, row);*/
}

/** Insert a row after a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertAfter)(DocumentRow ** list, DocumentRow * position, DocumentRow * row)
{
   int a=IMPLEMENT(DocumentRowList_getRowCount)(position);
   int b=IMPLEMENT(DocumentRowList_getRowCount)(*list);
   DocumentRow *temp;
   temp=*list;
   int i=0;
   if(b<=1)
   {
     IMPLEMENT(DocumentRowList_pushBack)(list,row);
   }
   else
   {
      while(i<b-a)
    {
       temp=temp->next;
       i++;
    }
    row->next=temp->next;
    temp->next=row;
   }
   return;
    /*provided_DocumentRowList_insertAfter(list, position, row);*/
}

/** Remove a row from the list
 * @param list the address of the pointer on the first cell of the list
 * @param position the row to remove
 */
void IMPLEMENT(DocumentRowList_removeRow)(DocumentRow ** list, DocumentRow * position)
{
   int a=IMPLEMENT(DocumentRowList_getRowCount)(position);
   int b=IMPLEMENT(DocumentRowList_getRowCount)(*list);
   DocumentRow *temp;
   temp=*list;
   int i=0;
   if(a==b)
   {
      *list=temp->next;
   }
   else if(a==1)
   {
      while(i<b-2)
      {
         temp=temp->next;
         i++;
      }
      temp->next=NULL;
   }
   else
   {
      while(i<b-a-1)
      {
         temp=temp->next;
         i++;
      }
      temp->next=position->next;
   }
   return;
    /*provided_DocumentRowList_removeRow(list, position);*/
}

/** Write a row in a binary file
 * @param row the row
 * @param file the opened file
 */
void IMPLEMENT(DocumentRow_writeRow)(DocumentRow * row, FILE * file)
{
   IMPLEMENT(writeString)(row->code,file);
   IMPLEMENT(writeString)(row->designation, file);
   if(fwrite(&(row->quantity),sizeof(double),1,file)<1)
    { fatalError("read quantity error"); }
    IMPLEMENT(writeString)(row->unity,file);
    if(fwrite(&(row->basePrice),sizeof(double),1,file)<1)
    { fatalError("read basePrice error"); }
    if(fwrite(&(row->sellingPrice),sizeof(double),1,file)<1)
    { fatalError("read sellingPrice error"); }
    if(fwrite(&(row->discount),sizeof(double),1,file)<1)
    { fatalError("read discount error"); }
    if(fwrite(&(row->rateOfVAT),sizeof(double),1,file)<1)
    { fatalError("read rateOfVAT error"); }
    if(row->next != NULL)
    {IMPLEMENT(DocumentRow_writeRow)(row->next,file);}
    return;
   /*provided_DocumentRow_writeRow(row, file);*/
}

/** Read a row from a file
 * @param file the opened file
 * @return a new row created on the heap filled with the data
 */
DocumentRow * IMPLEMENT(DocumentRow_readRow)(FILE * file)
{
    DocumentRow *row;
    row=(DocumentRow*)malloc(sizeof(DocumentRow));
    if(row==NULL)
    { fatalError("malloc error"); }
    (row->code)=IMPLEMENT(readString)(file);
    (row->designation)=IMPLEMENT(readString)(file);
    if(fread(&(row->quantity),sizeof(double),1,file)<1)
    { fatalError("read quantity error"); }
    (row->unity)=IMPLEMENT(readString)(file);
    if(fread(&(row->basePrice),sizeof(double),1,file)<1)
    { fatalError("read basePrice error"); }
    if(fread(&(row->sellingPrice),sizeof(double),1,file)<1)
    { fatalError("read sellingPrice error"); }
    if(fread(&(row->discount),sizeof(double),1,file)<1)
    { fatalError("read discount error"); }
    if(fread(&(row->rateOfVAT),sizeof(double),1,file)<1)
    { fatalError("read rateOfVAT error"); }
    if(!EOF)
    { row->next=IMPLEMENT(DocumentRow_readRow)(file);}
    return row;
    /*return provided_DocumentRow_readRow(file);*/
}
