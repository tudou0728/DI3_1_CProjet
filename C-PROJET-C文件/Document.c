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
 * $Id: Document.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Document.h>
#include <DocumentUtil.h>
#include <DocumentRowList.h>

/** Initialize a document
 * @param document a pointer to a document
 * @warning An initialized document must be finalized by Document_finalize() to free all resources
 */
void IMPLEMENT(Document_init)(Document * document)
{
    IMPLEMENT(CustomerRecord_init)(&(document->customer));
    document->editDate=duplicateString("");
    document->expiryDate=duplicateString("");
    document->docNumber=duplicateString("");
    document->object=duplicateString("");
    document->operator=duplicateString("");
    document->rows=NULL;
    document->typeDocument=0;
    return;
    /*provided_Document_init(document);*/
}

/** Finalize a document
 * @param document the document to finalize
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_finalize)(Document * document)
{
    IMPLEMENT(CustomerRecord_finalize)(&(document->customer));
    free(document->editDate);
    free(document->expiryDate);
    free(document->docNumber);
    free(document->object);
    free(document->operator);
    IMPLEMENT(DocumentRow_finalize)(document->rows);
    return;
   /* provided_Document_finalize(document);*/
}

/** Save the content of a documentrowlist to a file
 * @param row the documentrow
 * @param file the file
 */
static void DocumentRow_writeRowList(DocumentRow *row,FILE* file)
{
    int a = DocumentRowList_getRowCount(row);
    if( fwrite(&a,sizeof(int),1,file)<1 )
    { fatalError("Write file error");}
    while( row!=NULL )
    {
        DocumentRow_writeRow(row,file);
        row = row->next;
    }
    return;
}

/** Save the content of a document to a file
 * @param document the document
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_saveToFile)(Document * document, const char * filename)
{
    FILE *fp;
    fp=fopen(filename,"wb");
    if(fp == NULL)
    { fatalError("open file error"); }

    IMPLEMENT(CustomerRecord_write)(&(document->customer), fp);
    IMPLEMENT(writeString)(document->editDate, fp);
    IMPLEMENT(writeString)(document->expiryDate, fp);
    IMPLEMENT(writeString)(document->docNumber, fp);
    IMPLEMENT(writeString)(document->object, fp);
    IMPLEMENT(writeString)(document->operator, fp);

    DocumentRow_writeRowList(document->rows,fp);

    if(fwrite(&(document->typeDocument),sizeof(int),1,fp)<1)
    { fatalError("write type error"); }

    fclose(fp);
    return;
    /*provided_Document_saveToFile(document,filename);*/
}

/** Load the content of a documentrowlist from a file
 * @param file the file
 * @return a documentrowlist
 */
static DocumentRow* DocumentRow_readRowList(FILE *file)
{
    DocumentRow *temp = NULL;
    int a;
    if( fread( &a,sizeof(int),1,file )<1 )
    { fatalError("read count error");}

    while( a!=0 )
    {
        DocumentRowList_pushBack(&temp,IMPLEMENT(DocumentRow_readRow)(file));
        a--;
    }
    return temp;
}

/** Load the content of a document from a file
 * @param document the document to fill
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_loadFromFile)(Document * document, const char * filename)
{
    FILE *fp;
    char *str;
    fp = fopen(filename,"rb");
    if( fp!=NULL )
    {
        IMPLEMENT(CustomerRecord_read)( &(document->customer),fp );

        str = readString(fp);
        if( str != NULL)
        {
            free(document->editDate);
            document->editDate = str ;
        }

        str = readString(fp);
        if( str != NULL)
        {
            free(document->expiryDate);
            document->expiryDate = str ;
        }

        str = readString(fp);
        if( str != NULL)
        {
            free(document->docNumber);
            document->docNumber = str ;
        }

        str = readString(fp);
        if( str != NULL)
        {
            free(document->object);
            document->object = str ;
        }

        str = readString(fp);
        if( str != NULL)
        {
            free(document->operator);
            document->operator = str ;
        }

        document->rows = DocumentRow_readRowList(fp);

        if( fread(&(document->typeDocument),sizeof(int),1,fp)<1 )
        { fatalError("read trye error"); }

        fclose(fp);

    }
    /* provided_Document_loadFromFile(document,filename);*/
}

