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
 * $Id: CustomerDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerDB.h>
#include <CustomerRecord.h>
#include <CustomerRecordEditor.h>

const char * CUSTOMERDB_FILENAME = BASEPATH "/data/Customer.db";

CustomerDB * IMPLEMENT(CustomerDB_create)(const char * filename)
{
    CustomerDB*customerDB;
    FILE*fp;
    customerDB=(CustomerDB*)malloc(sizeof(CustomerDB));
    fp=fopen(filename,"wb+");
    if(fp==NULL)
    {
        printf("open file error");
        exit(1);
    }
    customerDB->recordCount=0;
    customerDB->file=fp;
    if(fwrite(&(customerDB->recordCount),sizeof(int),1,fp) != 1)
    {
       fatalError("write error");
       free(fp);
    }
    return customerDB;
    /*return provided_CustomerDB_create(filename);*/
}

CustomerDB * IMPLEMENT(CustomerDB_open)(const char * filename)
{
    CustomerDB*customerDB;
    FILE*fp;
    customerDB=(CustomerDB*)malloc(sizeof(CustomerDB));
    fp=fopen(filename,"rb+");
    if(fp==NULL)
    {
        printf("open file error");
        return NULL;
    }
    else
    {
      customerDB->recordCount=0;
      customerDB->file=fp;
      if(fread(&(customerDB->recordCount),sizeof(int),1,fp) != 1)
      {
        fatalError("error");
      }
      return customerDB;
    }
    /*return provided_CustomerDB_open(filename);*/
}

CustomerDB * IMPLEMENT(CustomerDB_openOrCreate)(const char * filename)
{
    if(IMPLEMENT(CustomerDB_open)(filename)==NULL)
     { return IMPLEMENT(CustomerDB_create)(filename);}
    else
    { return IMPLEMENT(CustomerDB_open)(filename);}
   /* return provided_CustomerDB_openOrCreate(filename);*/
}

void IMPLEMENT(CustomerDB_close)(CustomerDB * customerDB)
{
    fseek(customerDB->file,0,SEEK_SET);
    if(fwrite(&(customerDB->recordCount),sizeof(int),1,customerDB->file) != 1)
    {
        printf("fread error");
        exit(1);
    }
    fclose(customerDB->file);
    free(customerDB);
    return;
    /*provided_CustomerDB_close(customerDB);*/
}

int IMPLEMENT(CustomerDB_getRecordCount)(CustomerDB * customerDB)
{
    return customerDB->recordCount;
    /*return provided_CustomerDB_getRecordCount(customerDB);*/
}

char * CustomerDB_getFieldValueAsString(CustomerDB * customerDB, int recordIndex, int field) {
    char * content = NULL;
    if (customerDB != NULL) {
        CustomerRecord_FieldProperties properties = CustomerRecord_getFieldProperties(field);
        CustomerRecord record;
        CustomerRecord_init(&record);
        CustomerDB_readRecord(customerDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CustomerRecord_finalize(&record);
    }
    return content;
}


void IMPLEMENT(CustomerDB_appendRecord)(CustomerDB * customerDB, CustomerRecord *record)
{
    int a=customerDB->recordCount;
    fseek(customerDB->file,(long)sizeof(int)+(long)sizeof(CustomerRecord)*a,SEEK_SET);
    IMPLEMENT(CustomerRecord_write)(record, customerDB->file);

    customerDB->recordCount++;
    fseek(customerDB->file,0,SEEK_SET);
    if(fwrite(&(customerDB->recordCount),sizeof(int),1,customerDB->file)<1)
    { fatalError("write count error"); }
    return;
   /*provided_CustomerDB_appendRecord(customerDB, record);*/
}

void IMPLEMENT(CustomerDB_insertRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record)
{
    int i=0;
    CustomerRecord *temp;
    temp=(CustomerRecord *)malloc(sizeof(CustomerRecord));
    if(temp==NULL)
    {fatalError("malloc error !");}
    CustomerRecord_init(temp);
    if(recordIndex>=0 && recordIndex<=(customerDB->recordCount))
    {
        for(i=customerDB->recordCount;i>=recordIndex;i--)
        {
            CustomerDB_readRecord(customerDB,i,temp);
            CustomerDB_writeRecord(customerDB,i+1,temp);
        }
        CustomerRecord_finalize(temp);
        free(temp);
        customerDB->recordCount++;
        CustomerDB_writeRecord(customerDB,recordIndex,record);
        rewind(customerDB->file);
        if(fwrite(&(customerDB->recordCount),sizeof(int),1,customerDB->file)!=1)
            { fatalError("write error"); }
        }
    else
    { fatalError("error"); }
  /*provided_CustomerDB_insertRecord(customerDB, recordIndex, record);*/
}

void IMPLEMENT(CustomerDB_removeRecord)(CustomerDB * customerDB, int recordIndex)
{
    int i=0;
    CustomerRecord *temp;
    temp=(CustomerRecord *)malloc(sizeof(CustomerRecord));
    if(temp==NULL)
    {fatalError("malloc error");}
    CustomerRecord_init(temp);
    if(recordIndex>=0 && recordIndex<=(customerDB->recordCount))
    {
        for(i=recordIndex+1;i<(customerDB->recordCount);i++)
        {
            CustomerDB_readRecord(customerDB,i,temp);
            CustomerDB_writeRecord(customerDB,i-1,temp);
        }
            CustomerRecord_finalize(temp);
            free(temp);
            customerDB->recordCount--;
            rewind(customerDB->file);
            if(fwrite(&(customerDB->recordCount),sizeof(int),1,customerDB->file)!=1)
                { fatalError("write error !"); }
        }
    else
    { fatalError("error !");}
   /*provided_CustomerDB_removeRecord(customerDB, recordIndex);*/
}

void IMPLEMENT(CustomerDB_readRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record)
{
    fseek(customerDB->file,(long)(sizeof(CustomerRecord))*recordIndex +(int)sizeof(int),SEEK_SET);
    IMPLEMENT(CustomerRecord_read)(record, customerDB->file);
    return;
    /*provided_CustomerDB_readRecord(customerDB, recordIndex, record);*/
}

void IMPLEMENT(CustomerDB_writeRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record)
{
    fseek(customerDB->file,(long)(sizeof(CustomerRecord))*recordIndex +(long)sizeof(int),SEEK_SET);
    IMPLEMENT(CustomerRecord_write)(record, customerDB->file);
    if(recordIndex >= customerDB->recordCount)
    { customerDB->recordCount++;}
    return;
    /*provided_CustomerDB_writeRecord(customerDB, recordIndex, record);*/
}
