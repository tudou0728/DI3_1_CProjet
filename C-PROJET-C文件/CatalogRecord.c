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
 * $Id: CatalogRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogRecord.h>

/** Static function which test if a code only contains numbers and letters
 * @param  value the value to test
 * @return true if the code is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_code)(const char * value)
{
   size_t a=IMPLEMENT(stringLength)(value);
   size_t i=0;
   int find=1;
   while((i<a) && (find == 1))
   {
      if(((value[i] >= 'A') && (value[i] <= 'Z')) ||((value[i] >= (char)(48)) && (value[i] <= (char)(57))) || ((value[i] >= 'a') && (value[i] <= 'z')))
      {
        i++;
      }
      else
      {
        find=0;
      }
   }
   return find;
  /*return provided_CatalogRecord_isValueValid_code(value);*/
}

/** Static function which test if the value is a positive number
 * @param  value the value to test
 * @return true if the valie is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_positiveNumber)(const char * value)
{
  size_t a=IMPLEMENT(stringLength)(value);
   size_t i=0;
   int find=1;
   if((value[i] <= (char)(47)) || (value[i] >= (char)(58)))
   {
      find=0;
   }
   else
   {
     while((i<a) && (find == 1))
     {
       if(value[i] == (char)(100))
       {
          find=0;
          break;
       }
       else
       {
         i++;
       }
     }
   }
   return find;
  /*return provided_CatalogRecord_isValueValid_positiveNumber(value);*/
}

/** Static function to set the code field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_code)(CatalogRecord * record, const char * value)
{
  if(CatalogRecord_isValueValid_code(value))
  {
      free(record->code);
      record->code=duplicateString(value);
  }
  else
  {
      printf("error");
      exit(1);
  }
  return;
  /*provided_CatalogRecord_setValue_code(record, value);*/
}

/** Static function to set the designation field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_designation)(CatalogRecord * record, const char * value)
{
  if(CatalogRecord_isValueValid_code(value))
  {
      free(record->designation);
      record->designation=duplicateString(value);
  }
  else
  {
      printf("error");
      exit(1);
  }
  return;
  /*provided_CatalogRecord_setValue_designation(record, value);*/
}

/** Static function to set the unity field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_unity)(CatalogRecord * record, const char * value)
{
  if(CatalogRecord_isValueValid_code(value))
  {
      free(record->unity);
      record->unity=duplicateString(value);
  }
  else
  {
      printf("error");
      exit(1);
  }
  return;
  /*provided_CatalogRecord_setValue_unity(record, value);*/
}

/** Static function to set the basePrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_basePrice)(CatalogRecord * record, const char * value)
{
  char *ptr;
  record->basePrice=strtod(value,&(ptr));
  ptr=NULL;
  return;
  /*provided_CatalogRecord_setValue_basePrice(record, value);*/
}

/** Static function to set the sellingPrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_sellingPrice)(CatalogRecord * record, const char * value)
{
  char *ptr;
  record->sellingPrice=strtod(value,&(ptr));
  ptr=NULL;
  return;
  /*provided_CatalogRecord_setValue_sellingPrice(record, value);*/
}

/** Static function to set the rateOfVAT field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_rateOfVAT)(CatalogRecord * record, const char * value)
{
  char *ptr;
  record->rateOfVAT=strtod(value,&(ptr));
  ptr=NULL;
  return;
  /*provided_CatalogRecord_setValue_rateOfVAT(record, value);*/
}

/** Static function which create a copy string on the head of the code field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_code)(CatalogRecord * record)
{
  char *res;
  res=IMPLEMENT(duplicateString)(record->code);
  return res;
  /*return provided_CatalogRecord_getValue_code(record);*/
}

/** Static function which create a copy string on the head of the designation field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_designation)(CatalogRecord * record)
{
  char *res;
  res=IMPLEMENT(duplicateString)(record->designation);
  return res;
  /*return provided_CatalogRecord_getValue_designation(record);*/
}

/** Static function which create a copy string on the head of the unity field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_unity)(CatalogRecord * record)
{
  char *res;
  res=IMPLEMENT(duplicateString)(record->unity);
  return res;
  /*return provided_CatalogRecord_getValue_unity(record);*/
}

/** Static function which create a copy string on the head of the basePrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_basePrice)(CatalogRecord * record)
{
   char *res;
   res=(char*)malloc(sizeof(char)*CATALOGRECORD_BASEPRICE_SIZE);
   sprintf(res,"%.2f",record->basePrice);
   return res;
   /*return provided_CatalogRecord_getValue_basePrice(record);*/
}

/** Static function which create a copy string on the head of the sellingPrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_sellingPrice)(CatalogRecord * record)
{
   char *res;
   res=(char*)malloc(sizeof(char)*CATALOGRECORD_SELLINGPRICE_SIZE);
   sprintf(res,"%.2f",record->sellingPrice);
   return res;
   /*return provided_CatalogRecord_getValue_sellingPrice(record);*/
}

/** Static function which create a copy string on the head of the rateOfVAT field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_rateOfVAT)(CatalogRecord * record)
{
   char *res;
   res=(char*)malloc(sizeof(char)*CATALOGRECORD_RATEOFVAT_SIZE);
   sprintf(res,"%.2f",record->rateOfVAT);
   return res;
   /*return provided_CatalogRecord_getValue_rateOfVAT(record);*/
}

/** Initialize a record
 * @param[in] record a pointer to a record to initialize
 * @warning every initialized record must be finalized with CatalogRecord_finalize()
 */
void IMPLEMENT(CatalogRecord_init)(CatalogRecord * record)
{
    record->code=duplicateString("");
    record->designation=duplicateString("");
    record->unity=duplicateString("");
    record->basePrice=0;
    record->sellingPrice=0;
    record->rateOfVAT=0;
    return;
    /*provided_CatalogRecord_init(record);*/
}

/** Finalize a record.
 * @param[in] record a pointer to a record to finalize
 */
void IMPLEMENT(CatalogRecord_finalize)(CatalogRecord * record)
{
    free(record->code);
    free(record->designation);
    free(record->unity);
    /*provided_CatalogRecord_finalize(record);*/
}

/** Read a record from a file
 * @param record a pointer to an initialized record on which to store data
 * @param file the file from which the data are read
 */
void IMPLEMENT(CatalogRecord_read)(CatalogRecord * record, FILE * file)
{
    char temp1[CATALOGRECORD_CODE_SIZE];
    char temp2[CATALOGRECORD_DESIGNATION_SIZE];
    char temp3[CATALOGRECORD_UNITY_SIZE];

    memset(temp1,0,CATALOGRECORD_CODE_SIZE);
    memset(temp2,0,CATALOGRECORD_DESIGNATION_SIZE);
    memset(temp3,0,CATALOGRECORD_UNITY_SIZE);

    if(fread(temp1,CATALOGRECORD_CODE_SIZE,1,file) == 1)
    {
        IMPLEMENT(CatalogRecord_setValue_code)(record, temp1);
    }
    if(fread(temp2,CATALOGRECORD_DESIGNATION_SIZE,1,file) == 1)
    {
        IMPLEMENT(CatalogRecord_setValue_designation)(record, temp2);
    }
    if(fread(temp3,CATALOGRECORD_UNITY_SIZE,1,file) == 1)
    {
        IMPLEMENT(CatalogRecord_setValue_unity)(record, temp3);
    }
    if(fread(&(record->basePrice),CATALOGRECORD_BASEPRICE_SIZE,1,file) != 1)
    {
        fatalError("error");
    }
    if(fread(&(record->sellingPrice),CATALOGRECORD_SELLINGPRICE_SIZE,1,file) != 1)
    {
        fatalError("error");
    }
   if(fread(&(record->rateOfVAT),CATALOGRECORD_RATEOFVAT_SIZE,1,file) != 1)
    {
        fatalError("error");
    }
    return;
  /* provided_CatalogRecord_read(record, file);*/
}

/** Write a record to a file
 * @param record a pointer to a record
 * @param file the file to which the data are written
 */
void IMPLEMENT(CatalogRecord_write)(CatalogRecord * record, FILE * file)
{
    char temp1[CATALOGRECORD_CODE_SIZE];
    char temp2[CATALOGRECORD_DESIGNATION_SIZE];
    char temp3[CATALOGRECORD_UNITY_SIZE];

    memset(temp1,0,CATALOGRECORD_CODE_SIZE);
    memset(temp2,0,CATALOGRECORD_DESIGNATION_SIZE);
    memset(temp3,0,CATALOGRECORD_UNITY_SIZE);

    copyStringWithLength(temp1,record->code,CATALOGRECORD_CODE_SIZE);
    copyStringWithLength(temp2,record->designation,CATALOGRECORD_DESIGNATION_SIZE);
    copyStringWithLength(temp3,record->unity,CATALOGRECORD_UNITY_SIZE);

    if(fwrite(temp1,CATALOGRECORD_CODE_SIZE,1,file)!=1)
    { fatalError("error.\n"); }
	if(fwrite(temp2,CATALOGRECORD_DESIGNATION_SIZE,1,file)!=1)
    { fatalError("error.\n"); }
	if(fwrite(temp3,CATALOGRECORD_UNITY_SIZE,1,file)!=1)
    { fatalError("error.\n"); }
    if(fwrite(&record->basePrice,CATALOGRECORD_BASEPRICE_SIZE,1,file)!=1)
    { fatalError("error.\n"); }
	if(fwrite(&record->sellingPrice,CATALOGRECORD_SELLINGPRICE_SIZE,1,file)!=1)
    { fatalError("error.\n"); }
	if(fwrite(&record->rateOfVAT,CATALOGRECORD_RATEOFVAT_SIZE,1,file)!=1)
    { fatalError("error.\n"); }
    return;
   /*provided_CatalogRecord_write(record, file);*/
}

