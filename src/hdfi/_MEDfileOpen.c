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


med_idt _MEDfileOpen(const char * const filename,const med_access_mode accessmode)
{

  med_idt _ret          =  0;
  med_idt _fid		=  0;
  int     _hdf_mode	= -1;
  hid_t   _fapl		=  H5P_DEFAULT;
  med_int _fmajor	=  0;
  med_int _fminor	=  0;
  med_int _frelease	=  0;
  med_int _fversionMM	=  0;

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
      MED_ERR_(_ret,MED_ERR_RANGE,MED_ERR_ACCESS,filename);
      goto ERROR;
    }

  if ( (_fapl = H5Pcreate (H5P_FILE_ACCESS)) < 0 ) {
    MED_ERR_(_ret,MED_ERR_CREATE,MED_ERR_PROPERTY,MED_ERR_FILEVERSION_MSG);
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
    goto ERROR;
  }


  if ( MEDfileNumVersionRd(_fid,&_fmajor,&_fminor,&_frelease) < 0) {
    /* Si le fichier _fid ne possède pas la structure MED_INFOS 
       (mountById, cf test20-0.med.hdf où la struct MED est dans un ss-groupe)
       le fichier est considéré en version 0.0.0 et ne sera pas inscrit
       en cache de version. cf. plus bas
    */
    /* MED_ERR_(_ret,MED_ERR_CALL,MED_ERR_API,"MEDfileNumVersionRd"); */
    /* goto ERROR; */
  }

  _fversionMM = 100*_fmajor+10*_fminor;

  /* OLD: EN MED4/HDF5-1.10 -> transposer en MED5/HDF5-1.12
    Cette ligne, présente depuis la 3.0, impose l'utilisation du modèle de données HDF 1.8 pour :
     - Utiliser les nouvelles représentations HDF plus efficaces que dans les versions précédentes
     - Empêcher l'utilisation de nvlles représentations d'une future bibliothèque HDF 1.10
       qui poseait d'eventuels problèmes de relecture aux bibliothèques med
       utilisant encore la 1.8 (ce choix doit être manuel) :
    Les fichiers HDF 1.8 utilisent la nouvelle représentation des liens au sein des groupes :
    compact (header) ou dense (hors header)
  */

  /* HDF-5 : UG
    Groups will be initially created in the compact‐or‐indexed format only when one or more of the following
    conditions is met:
   •    The low version bound value of the library version bounds property has been set to Release 1.8.0
        or later in the file access property list (see H5Pset_libver_bounds). Currently, that would
        require an H5Pset_libver_bounds call with the low parameter set to H5F_LIBVER_LATEST.
        When this property is set for an HDF5 file, all objects in the file will be created using the latest
        available format; no effort will be made to create a file that can be read by older libraries.

   •   The creation order tracking property, H5P_CRT_ORDER_TRACKED,
       has been set in the group creation property list (see H5Pset_link_creation_order).
  */

#if H5_VERS_MINOR > 12
#error "Don't forget to change the compatibility version of the library !"
#endif
/* L'avantage de bloquer le modèle interne HDF5
   est que l'on peut modifier des fichiers med de différentes versions majeures de fichiers.
   L'inconvénient est que l'on ne profite pas des évolutions de performances d'HDF (ou des bugs ;).
*/

  if ( _fversionMM < 500 ) /*100*MED_NUM_MAJEUR+10*MED_NUM_MINEUR*/ {
    if (H5Fset_libver_bounds(_fid, H5F_LIBVER_V18, H5F_LIBVER_V18) < 0) {
      MED_ERR_(_ret,MED_ERR_INIT,MED_ERR_PROPERTY,MED_ERR_FILEVERSION_MSG);
      goto ERROR;
    }
  } else {
    if ( H5Fset_libver_bounds(_fid, H5F_LIBVER_V112, H5F_LIBVER_V112) < 0) {
      MED_ERR_(_ret,MED_ERR_INIT,MED_ERR_PROPERTY,MED_ERR_FILEVERSION_MSG);
      goto ERROR;
    }
  }

/* Adjust the size of metadata cache */
/* config.version = H5AC__CURR_CACHE_CONFIG_VERSION; */
/* H5Fget_mdc_config(_fid, &config); */
/* config.set_initial_size = 1; */
/* config.initial_size = 8*1024*1024; */
/* config.max_size = 16*1024*1024; */
/* H5Fset_mdc_config(_fid, &config); */

  _MEDsetModeAcces(_fid,accessmode);
  /* Si le fichier _fid ne possède pas la structure MED_INFOS;
     le fichier est considéré en version 0.0.0 mais n'est pas inscrit
     en cache de version.
  */
  _MEDfileVersion(_fid);

 ERROR:

  if (_fid > 0 ) {
    if ( _ret < 0 ) {
      MEDfileClose(_fid);
      return _ret;
    }
    return _fid;
  } else {
    if (_fid == 0 ) {
      return _ret;
    }
    return _fid;
  }

  /* if ( (_fid > 0 ) && ( _ret < 0 ) ) { */
  /*   MEDfileClose(_fid); */
  /*   return _ret; */
  /* } */
  /* if (_fid == 0 ) { */
  /*   return _ret; */
  /* } */
  /* return _fid; */
  
}
