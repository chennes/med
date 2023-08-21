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


#include <med_config.h>
#include <med.h>
#include <med_outils.h>

#include <string.h>
#include <stdlib.h>

void _MEDfieldnEntityType41(int dummy, ...)

{
  med_int  _ret=-1;
  med_idt  _gid=0;
  char     _gidname                [MED_FIELD_GRP_SIZE+MED_NAME_SIZE+1+2*MED_MAX_PARA+1]=MED_FIELD_GRP;
  /* med_int  _numdt=0, _numit=0; */
  med_int  _n=0;
  uint32_t  _lentitytype1  		    	  =0;

  MED_VARGS_DECL(const, med_idt      	      ,       , fid       );
  MED_VARGS_DECL(const, char * 		      , const , fieldname );
  MED_VARGS_DECL(const, med_int               ,       , numdt     );
  MED_VARGS_DECL(const, med_int               ,       , numit     );
  MED_VARGS_DECL(     , med_int *             ,	      , fret      );

  va_list params;
  va_start(params,dummy);

  MED_VARGS_DEF(const, med_idt      	     , 	     , fid       );
  MED_VARGS_DEF(const, char * 		     , const , fieldname );
  MED_VARGS_DEF(const, med_int               , 	     , numdt     );
  MED_VARGS_DEF(const, med_int               , 	     , numit     );
  MED_VARGS_DEF(     , med_int *             ,	     , fret      );


  /*
   * On inhibe le gestionnaire d'erreur HDF 5
   */
  _MEDmodeErreurVerrouiller();

  NOFINALBLANK(fieldname,ERROR);

  /*
   * Si le Data Group cha n'existe pas => erreur
   */
  strcat(_gidname,fieldname);
  if ( (numdt != MED_ALL_DT) && (numit != MED_ALL_IT) ) {
    strcat(_gidname,"/");
    _MEDgetComputationStepName(MED_SORT_DTIT,numdt,numit,&_gidname[strlen(_gidname)]);
  }
  
  if ((_gid = _MEDdatagroupOuvrir(fid,_gidname)) < 0) {
    MED_ERR_(_ret,MED_ERR_OPEN,MED_ERR_DATAGROUP,MED_ERR_FIELD_MSG);
    SSCRUTE(fieldname);SSCRUTE(_gidname); goto ERROR;
  }

  /*Lecture de la liste des types d'entités utilisés soit :
   - au niveau global
   - au niveau d'une étape de calcul 
  */
  if (_MEDattributeInt32Rd(_gid,MED_NOM_LEN,&_lentitytype1) < 0) {
    MED_ERR_(_ret,MED_ERR_READ,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
    SSCRUTE(fieldname);SSCRUTE(_gidname)SSCRUTE(MED_NOM_LEN);goto ERROR;
  }

  _n=_MEDnSet32bits(_lentitytype1);

  /* ISCRUTE(_n); */

 SORTIE:
  
  _ret =  _n;
  
 ERROR:
  
  if (_gid>0)            if (_MEDdatagroupFermer(_gid) < 0) {
    MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_DATAGROUP,_gidname);
    ISCRUTE_id(_gid);
  }

  va_end(params);
  *fret = _ret;

  return;
}

