/*  This file is part of MED.
 *
 *  COPYRIGHT (C) 1999 - 2023  EDF R&D, CEA/DEN
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


#include <med.h>
#include <med_config.h>
#include <med_outils.h>
#include <hdf5.h>


med_idt  _MEDfileOpenForImport(const char * const filename,const med_access_mode accessmode)
{

  med_idt _fid =-1;
  int     _hdf_mode=-1;
  hid_t   _fapl    = H5P_DEFAULT;

  /* H5AC_cache_config_t config; */

  switch(accessmode)
    {
    case MED_ACC_RDWR :
    case MED_ACC_RDEXT    :
      _hdf_mode = H5F_ACC_RDWR;
      break;

    case MED_ACC_RDONLY :
      _hdf_mode = H5F_ACC_RDONLY;
      break;

    default :
      MED_ERR_(_fid,MED_ERR_RANGE,MED_ERR_ACCESS,filename);
      goto ERROR;
    }

  if ( (_fapl = H5Pcreate (H5P_FILE_ACCESS)) < 0 ) {
    MED_ERR_(_fid,MED_ERR_CREATE,MED_ERR_PROPERTY,MED_ERR_FILEVERSION_MSG);
    goto ERROR;
  }


#if H5_VERS_MINOR > 12
#error "Don't forget to change the compatibility version of the library !"
#endif
/* L'avantage de bloquer le modèle interne HDF5
   est que l'on peut modifier des fichiers med de différentes versions majeures de fichiers.
   L'inconvénient est que l'on ne profite pas des évolutions de performances d'HDF.
*/
  if ( H5Pset_libver_bounds( _fapl, H5F_LIBVER_V112, H5F_LIBVER_V112 ) ) {
    MED_ERR_(_fid,MED_ERR_INIT,MED_ERR_PROPERTY,MED_ERR_FILEVERSION_MSG);
    goto ERROR;
  }

  if ((_fid = H5Fopen(filename,_hdf_mode,_fapl)) < 0) {
    /*La gestion de l'affichage des erreurs se fait dans la couche supérieure*/
    /*cela permet de tester l'ouverture du fichier (cf MEDfileExist, MEDfileCompatibility) sans provoquer 
     d'affichage intempestif.*/
    _fid = MED_ERR_OPEN MED_ERR_FILE;
    /* MED_ERR_(_fid,MED_ERR_OPEN,MED_ERR_FILE,""); */
    /* ISCRUTE_int(accessmode); */
    /* Ne pas activer la ligne suivante en production, car certains code 
       utlisent MEDfileOpen pour tester la présence d'un fichier */
    /*    H5Eprint1(stderr); */
    goto ERROR;
  }

  if ( H5Pclose(_fapl) < 0 ) {
    MED_ERR_(_fid,MED_ERR_CLOSE,MED_ERR_PROPERTY,"");
    _fid=-1;goto ERROR;
  }

  _MEDsetModeAcces(_fid,accessmode);
  /* Si le fichier _fid ne possède pas la structure MED_INFOS;
     le fichier est considéré en version 0.0.0 mais n'est pas inscrit
     en cache de version.
  */
  _MEDfileVersion(_fid);

 ERROR:

  return _fid;
}
