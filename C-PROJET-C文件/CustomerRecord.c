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
 * $Id: CustomerRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */


#include <CustomerRecord.h>

void IMPLEMENT(CustomerRecord_setValue_name)(CustomerRecord * record, const char * value)
{
  copyStringWithLength(record->name,value,CUSTOMERRECORD_NAME_SIZE);
  /*provided_CustomerRecord_setValue_name(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_address)(CustomerRecord * record, const char * value)
{
  copyStringWithLength(record->address,value,CUSTOMERRECORD_ADDRESS_SIZE);
  /*provided_CustomerRecord_setValue_address(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_postalCode)(CustomerRecord * record, const char * value)
{
  copyStringWithLength(record->postalCode,value,CUSTOMERRECORD_POSTALCODE_SIZE);
  /*provided_CustomerRecord_setValue_postalCode(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_town)(CustomerRecord * record, const char * value)
{
  copyStringWithLength(record->town,value,CUSTOMERRECORD_TOWN_SIZE);
  /*provided_CustomerRecord_setValue_town(record, value);*/
}

char * IMPLEMENT(CustomerRecord_getValue_name)(CustomerRecord * record)
{
   char *a=duplicateString(record->name);
   return a;
   /*return provided_CustomerRecord_getValue_name(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_address)(CustomerRecord * record)
{
  char *a=duplicateString(record->address);
  return a;
  /*return provided_CustomerRecord_getValue_address(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_postalCode)(CustomerRecord * record)
{
  char *a=duplicateString(record->postalCode);
  return a;
  /*return provided_CustomerRecord_getValue_postalCode(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_town)(CustomerRecord * record)
{
  char *a=duplicateString(record->town);
  return a;
  /*return provided_CustomerRecord_getValue_town(record);*/
}

void IMPLEMENT(CustomerRecord_init)(CustomerRecord * record)
{
  unsigned int i;
  for(i=0;i<(CUSTOMERRECORD_NAME_SIZE);i++)
  {
      record->name[i]='\0';
  }
  for(i=0;i<(CUSTOMERRECORD_ADDRESS_SIZE);i++)
  {
      record->address[i]='\0';
  }
  for(i=0;i<(CUSTOMERRECORD_POSTALCODE_SIZE);i++)
  {
      record->postalCode[i]='\0';
  }
  for(i=0;i<(CUSTOMERRECORD_TOWN_SIZE);i++)
  {
      record->town[i]='\0';
  }
  return;
  /*provided_CustomerRecord_init(record);*/
}

void IMPLEMENT(CustomerRecord_finalize)(CustomerRecord * record)
{
   memset(&(record->name),0,CUSTOMERRECORD_NAME_SIZE);
   memset(&(record->address),0,CUSTOMERRECORD_ADDRESS_SIZE);
   memset(&(record->postalCode),0,CUSTOMERRECORD_POSTALCODE_SIZE);
   memset(&(record->town),0,CUSTOMERRECORD_TOWN_SIZE);
   return;
   /*provided_CustomerRecord_finalize(record);*/
}

void IMPLEMENT(CustomerRecord_read)(CustomerRecord * record, FILE * file)
{

   if(fread(record->name,CUSTOMERRECORD_NAME_SIZE,1,file) != 1)

      { fatalError("read name error");}

   if(fread(record->address,CUSTOMERRECORD_ADDRESS_SIZE,1,file) != 1)

       {fatalError("read address error");}

   if(fread(record->postalCode,CUSTOMERRECORD_POSTALCODE_SIZE,1,file) != 1)

    {   fatalError("read postalCode error");}

   if(fread(record->town,CUSTOMERRECORD_TOWN_SIZE,1,file) != 1)

    {   fatalError("read town error");}

   return;
   /*provided_CustomerRecord_read(record, file);*/
}

void IMPLEMENT(CustomerRecord_write)(CustomerRecord * record, FILE * file)
{
    char temp1[CUSTOMERRECORD_NAME_SIZE];
    char temp2[CUSTOMERRECORD_ADDRESS_SIZE];
    char temp3[CUSTOMERRECORD_POSTALCODE_SIZE];
    char temp4[CUSTOMERRECORD_TOWN_SIZE];

    copyStringWithLength(temp1,record->name,CUSTOMERRECORD_NAME_SIZE);
    copyStringWithLength(temp2,record->address,CUSTOMERRECORD_ADDRESS_SIZE);
    copyStringWithLength(temp3,record->postalCode,CUSTOMERRECORD_POSTALCODE_SIZE);
    copyStringWithLength(temp4,record->town,CUSTOMERRECORD_TOWN_SIZE);

    if(fwrite(temp1,CUSTOMERRECORD_NAME_SIZE,1,file)!=1)
    { fatalError("write error.\n"); }
	if(fwrite(temp2,CUSTOMERRECORD_ADDRESS_SIZE,1,file)!=1)
    { fatalError("write error.\n"); }
	if(fwrite(temp3,CUSTOMERRECORD_POSTALCODE_SIZE,1,file)!=1)
    { fatalError("write error.\n"); }
    if(fwrite(temp4,CUSTOMERRECORD_TOWN_SIZE,1,file)!=1)
    { fatalError("write error.\n"); }
    return;
  /*provided_CustomerRecord_write(record, file);*/
}

