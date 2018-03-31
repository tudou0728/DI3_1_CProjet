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
 * $Id: CatalogDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogDB.h>
#include <CatalogRecord.h>
#include <CatalogRecordEditor.h>

/** The catalog file name */
const char * CATALOGDB_FILENAME = BASEPATH "/data/Catalog.db";

/** Create a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_create)(const char * filename)
{
     CatalogDB *catalogDB;
     catalogDB=(CatalogDB*)malloc(sizeof(CatalogDB));
     FILE*fp;
     fp=fopen(filename,"wb+");
     if(fp==NULL)
     {
         printf("open file error");
         exit(1);
     }
     catalogDB->file=fp;
     catalogDB->recordCount=0;
     if(fwrite(&(catalogDB->recordCount),sizeof(int),1,catalogDB->file) != 1)
     {
         printf("write file error");
         exit(1);
     }
     return catalogDB;
    /*return provided_CatalogDB_create(filename);*/
}

/** Open an existing database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_open)(const char * filename)
{
     CatalogDB *catalogDB;
     catalogDB=(CatalogDB*)malloc(sizeof(CatalogDB));
     FILE*fp;
     fp=fopen(filename,"rb+");
     if(fp==NULL)
     {
         printf("open file error");
         return NULL;
     }
     catalogDB->file=fp;
    if(fread(&(catalogDB->recordCount),sizeof(int),1,fp) != 1)
    {
        fatalError("error");
    }
    return catalogDB;
   /* return provided_CatalogDB_open(filename);*/
}

/** Open if exists or create otherwise a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_openOrCreate)(const char * filename)
{
    if(IMPLEMENT(CatalogDB_open)(filename)==NULL)
     { return IMPLEMENT(CatalogDB_create)(filename);}
    else
    { return IMPLEMENT(CatalogDB_open)(filename);}
    /*return provided_CatalogDB_openOrCreate(filename);*/
}

/** Flush cached data, close a database and free the structure representing the opened database
 * @param catalogDB a pointer on a CatalogDB representing the opened database
 */
void IMPLEMENT(CatalogDB_close)(CatalogDB * catalogDB)
{
    fseek(catalogDB->file,0,SEEK_SET);
    if(fwrite(&(catalogDB->recordCount),sizeof(int),1,catalogDB->file) != 1)
    {
        printf("fread error");
        exit(1);
    }
    fclose(catalogDB->file);
    free(catalogDB);
    return;
    /*provided_CatalogDB_close(catalogDB);*/
}

/** Get the number of records of the database
 * @param catalogDB the database
 * @return the number of records
 */
int IMPLEMENT(CatalogDB_getRecordCount)(CatalogDB * catalogDB)
{
    return catalogDB->recordCount;
    /*return provided_CatalogDB_getRecordCount(catalogDB);*/
}

/** Create a new string on the heap containing the value of the specified field for the specified record of a database
 * @param catalogDB the database
 * @param recordIndex the record index
 * @param field the field to query
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogDB_getFieldValueAsString(CatalogDB * catalogDB, int recordIndex, int field) {
    char * content = NULL;
    if (catalogDB != NULL) {
        CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(field);
        CatalogRecord record;
        CatalogRecord_init(&record);
        CatalogDB_readRecord(catalogDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CatalogRecord_finalize(&record);
    }
    return content;
}

/** Append the specified record at the end of the database
 * @param catalogDB the database
 * @param record the record
 */

void IMPLEMENT(CatalogDB_appendRecord)(CatalogDB * catalogDB, CatalogRecord *record)
{
    int a=catalogDB->recordCount;
    fseek(catalogDB->file,  (a)* (long) CATALOGRECORD_SIZE + (long) sizeof(int), SEEK_SET);
    IMPLEMENT(CatalogRecord_write)(record, catalogDB->file);

    catalogDB->recordCount++;
    fseek(catalogDB->file,0,SEEK_SET);
    if(fwrite(&(catalogDB->recordCount),sizeof(int),1,catalogDB->file)<1)
    { fatalError("write count error"); }
    return;

   /*provided_CatalogDB_appendRecord(catalogDB, record);*/
}

/** Insert the specified record at the given position in the database
 * @param catalogDB the database
 * @param recordIndex the insertion position
 * @param record the record
 */
void IMPLEMENT(CatalogDB_insertRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record)
{
    int i=0;
    CatalogRecord *temp;
    temp=(CatalogRecord *)malloc(sizeof(CatalogRecord));
    if(temp==NULL)
    {fatalError("malloc error !");}
    CatalogRecord_init(temp);

    if(recordIndex>=0 && recordIndex<=(catalogDB->recordCount))
    {
        for(i=catalogDB->recordCount;i>=recordIndex;i--)
        {
            CatalogDB_readRecord(catalogDB,i,temp);
            CatalogDB_writeRecord(catalogDB,i+1,temp);
        }
        CatalogRecord_finalize(temp);
        free(temp);
        catalogDB->recordCount++;
        CatalogDB_writeRecord(catalogDB,recordIndex,record);
        rewind(catalogDB->file);
        if(fwrite(&(catalogDB->recordCount),sizeof(int),1,catalogDB->file)!=1)
            { fatalError("write error"); }
        }
    else
    { fatalError("error"); }
  /*  provided_CatalogDB_insertRecord(catalogDB, recordIndex, record);*/
}

/** Remove a record at a given position from the database
 * @param catalogDB the database
 * @param recordIndex the removal position
 */
void IMPLEMENT(CatalogDB_removeRecord)(CatalogDB * catalogDB, int recordIndex)
{
    int i=0;
    CatalogRecord *temp;
    temp=(CatalogRecord *)malloc(sizeof(CatalogRecord));
    if(temp==NULL)
    {fatalError("malloc error");}
    CatalogRecord_init(temp);
    if(recordIndex>=0 && recordIndex<=(catalogDB->recordCount))
    {
        for(i=recordIndex+1;i<(catalogDB->recordCount);i++)
        {
            CatalogDB_readRecord(catalogDB,i,temp);
            CatalogDB_writeRecord(catalogDB,i-1,temp);
        }
            CatalogRecord_finalize(temp);
            free(temp);
            catalogDB->recordCount--;
            rewind(catalogDB->file);
            if(fwrite(&(catalogDB->recordCount),sizeof(int),1,catalogDB->file)!=1)
                { fatalError("write error !"); }
        }
    else
    { fatalError("error !");}
   /* provided_CatalogDB_removeRecord(catalogDB, recordIndex);*/
}

/** Read a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 */
void IMPLEMENT(CatalogDB_readRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record)
{
     if(recordIndex>(catalogDB->recordCount))
    {
        fatalError("input error!");
        exit(1);
    }
    else
    {
        fseek(catalogDB->file,  (recordIndex)* (long) CATALOGRECORD_SIZE + (long) sizeof(int), SEEK_SET);
        IMPLEMENT(CatalogRecord_read)(record,catalogDB->file);
    }
    return;
    /*provided_CatalogDB_readRecord(catalogDB, recordIndex, record);*/
}

/** Write a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 */
void IMPLEMENT(CatalogDB_writeRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record)
{
    if(recordIndex>(catalogDB->recordCount)+1)
    {
        fatalError("input error!");
        exit(1);
    }
    else
    {
        fseek(catalogDB->file,  (recordIndex)* (long) CATALOGRECORD_SIZE + (long) sizeof(int), SEEK_SET);
        IMPLEMENT(CatalogRecord_write)(record,catalogDB->file);
    }
    if (recordIndex == catalogDB->recordCount)
    {
        catalogDB->recordCount++;
        rewind(catalogDB->file);
    }
    return;
   /* provided_CatalogDB_writeRecord(catalogDB, recordIndex, record);*/
}

