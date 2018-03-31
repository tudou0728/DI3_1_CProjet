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
 * $Id: EncryptDecrypt.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <EncryptDecrypt.h>

void IMPLEMENT(encrypt)(const char * key, char * str)
{
    size_t a=IMPLEMENT(stringLength)(str);
    size_t b=IMPLEMENT(stringLength)(key);
    size_t i=0;
    while(i<a)
    {
       str[i]=(char)(IMPLEMENT(toLowerChar)(str[i])+IMPLEMENT(toLowerChar)(key[i%b])-'a');
       i++;
    }
    return;
    /*provided_encrypt(key,str);*/
}
void IMPLEMENT(decrypt)(const char * key, char * str)
{
   size_t a=IMPLEMENT(stringLength)(str);
   size_t b=IMPLEMENT(stringLength)(key);
   size_t i=0;
   while(i<a)
   {
       str[i]=(char)(IMPLEMENT(toLowerChar)(str[i])-IMPLEMENT(toLowerChar)(key[i%b])+'a');
       i++;
   }
   return;
   /*provided_decrypt(key,str);*/
}
