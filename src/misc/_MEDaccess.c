/*  This file is part of MED.
 *
 *  COPYRIGHT (C) 1999 - 2021  EDF R&D, CEA/DEN
 *  MED is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MED is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with MED.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

/******************************************************************************
 *
 * - Nom de la fonction : _MEDaccess
 * - Description : 
 * - Parametres :
 *     - file       (IN) : nom du fichier.
 *     - mode       (IN) : 
 *
 ******************************************************************************/
int _MEDaccess(const char * const file, int mode) {
  int ret;
#if defined(WIN32) && defined(UNICODE)
  int size_needed;
  wchar_t* afilename = NULL;
  size_needed = MultiByteToWideChar(CP_UTF8, 0, file, strlen(file), NULL, 0);
  afilename = malloc((size_needed+1)*sizeof(wchar_t));
  MultiByteToWideChar(CP_UTF8, 0, file, strlen(file), afilename, size_needed);
  afilename[size_needed] = '\0';
  ret = _waccess(afilename, mode);
  free(afilename);
#else
  ret = access(file, mode);
#endif 
  return ret;
}
