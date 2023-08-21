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

void _MEDfieldGeometryType41(int dummy, ...)

{
  int      _it                  =0;
  int      _itgeo               =0;
  int      _itent               =0;
  med_int  _ret			=-1;
  med_idt  _gid 		=0;
  med_idt  _gid0 		=0;
  med_int  _i			=0;
  uint32_t  _lgeometrytype1  	=0;
  uint32_t  _lgeometrytypetmp 	=0;
  uint32_t  _lglobalgeometrytypetmp=0;
  const char * _attname   	= NULL;
  const char * _attallname	= NULL;
  char         _gidname        [MED_FIELD_GRP_SIZE+MED_NAME_SIZE+1+2*MED_MAX_PARA+1]=MED_FIELD_GRP;
  med_int           _usedbyncs       = 0;
  med_int           _tmpusedbyncs    = 0;
  med_geometry_type _geolocaltype    = 0;
  int               _geoglobaltypeit = 0;
    
  MED_VARGS_DECL(const, med_idt      	      ,       , fid       	 );
  MED_VARGS_DECL(const, char * 		      , const , fieldname 	 );
  MED_VARGS_DECL(const, med_int               ,       , numdt     	 );
  MED_VARGS_DECL(const, med_int               ,       , numit     	 );
  MED_VARGS_DECL(const, med_entity_type       ,       , entitytype       );
  MED_VARGS_DECL(     , med_geometry_type *   , const , geometrytypes   );
  MED_VARGS_DECL(     , med_int *             ,	const , usedbyncs        );
  MED_VARGS_DECL(     , med_int *             ,	      , fret      	 );

  va_list params;
  va_start(params,dummy);

  MED_VARGS_DEF(const, med_idt      	     , 	     , fid       	);
  MED_VARGS_DEF(const, char * 		     , const , fieldname 	);
  MED_VARGS_DEF(const, med_int               , 	     , numdt     	);
  MED_VARGS_DEF(const, med_int               , 	     , numit     	);
  MED_VARGS_DEF(const, med_entity_type       ,       , entitytype       );
  MED_VARGS_DEF(     , med_geometry_type *   , const , geometrytypes   );
  MED_VARGS_DEF(     , med_int *             , const , usedbyncs        );
  MED_VARGS_DEF(     , med_int *             ,	     , fret      	);


  /*
   * On inhibe le gestionnaire d'erreur HDF 5
   */
  _MEDmodeErreurVerrouiller();

  NOFINALBLANK(fieldname,ERROR);

  /* TODO: Tester les multiples apparitions d'un même type géométrique */
  /* pour des types d'entités différents avant d'activer la gestion de MED_ALL_ENTITY_TYPE */
  if ( (entitytype == MED_UNDEF_ENTITY_TYPE) || ( entitytype ==  MED_ALL_ENTITY_TYPE )) {
    MED_ERR_(_ret,MED_ERR_INVALID,MED_ERR_ENTITY,MED_ERR_VALUE_MSG);
    ISCRUTE_int(entitytype);
    goto ERROR;
  }

  /*
   * Si le Data Group cha n'existe pas => erreur
   */
  strcat(_gidname,fieldname);
  if ((_gid0 = _MEDdatagroupOuvrir(fid,_gidname)) < 0) {
    MED_ERR_(_ret,MED_ERR_OPEN,MED_ERR_DATAGROUP,MED_ERR_FIELD_MSG);
    SSCRUTE(fieldname);SSCRUTE(_gidname); goto ERROR;
  }

  if ( (numdt != MED_ALL_DT) && (numit != MED_ALL_IT) ) {
    strcat(_gidname,"/");
    _MEDgetComputationStepName(MED_SORT_DTIT,numdt,numit,&_gidname[strlen(_gidname)]);
  
    if ((_gid = _MEDdatagroupOuvrir(fid,_gidname)) < 0) {
      MED_ERR_(_ret,MED_ERR_OPEN,MED_ERR_DATAGROUP,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_gidname); goto ERROR;
    }
  } else {
    _gid = _gid0;
  }
  
  /*Lecture de la liste des types d'entités utilisés soit :
   - au niveau global
   - au niveau d'une étape de calcul 
  */
  *usedbyncs=0;
  _usedbyncs=-1;
  _tmpusedbyncs=-1;

  /* MED_N_CELL_FIXED_GEO ne prend pas en compte (MED_NODE,MED_NO_GEOTYPE) car 
    les noeuds sont un autre type d'entité (le MED_N_NODE_FIXED_GEO ==1 n'est 
    pas comptabilisé dans MED_N_CELL_FIXED_GEO).
    Si c'était le cas, il faudrait ajouter un MED_NO_GEOTYPE supplémentaire avant POINT1.
   ???
   Pour le codage interne Nbits itératif des types géométrique de MED_ALL_ENTITY_TYPE ,
   il faut commencer à _it==0 contrairement aux autres type d'entités.
   Du coup on ne mutualise pas le traitement Nbits->typeGeo avec le cas !MED_ALL_ENTITY_TYPE
   ???
  */
  if ( entitytype ==  MED_ALL_ENTITY_TYPE ) {

    /* TODO: GERER LE ALL_ENTITY_TYPES et ELSTRUCT comme le cas !ALL_ENTITY_TYPES  ....*/
    _i=0;
    for (_itent=1; _itent <= MED_N_ENTITY_TYPES; _itent++) {

      _attname                = _MEDgetEntityListAttributeIName(MED_GET_ENTITY_TYPE[_itent]);
      _lglobalgeometrytypetmp = 0;
      _lgeometrytypetmp       = 0;
      /* SSCRUTE(_attname); */
      /* Lecture de la liste des types géo en numérotation locale au type d'entité   */
      _MEDattributeInt32Rd(_gid,_attname,&_lgeometrytypetmp);
      /* ISCRUTE_int32(_lgeometrytypetmp); */
      /* Renumérotation de la liste des types géo utilisés en numérotation globale  */
      for (_itgeo=1; _itgeo <= MED_GET_N_FIXED_GEO_FOR_ENTITY_TYPE_IT[_itent]; _itgeo++) {
	
	_geolocaltype    = (MED_GET_GEOMETRY_TYPE_IT_FROM_ENTITY_TYPE_IT[_itent])[_itgeo];
	_geoglobaltypeit =  MEDgetCellGeometryTypeIt(_geolocaltype);
	/* SSCRUTE(MED_GET_CELL_GEOMETRY_TYPENAME[_geoglobaltypeit]); */
	/* ISCRUTE(_MEDtest32bits(_lgeometrytypetmp,(_itgeo-1))); */
	if( _MEDtest32bits(_lgeometrytypetmp,(_itgeo-1)) ) {
	  /* ISCRUTE(_geoglobaltypeit); */
	  /* _MEDset32bits( &_lglobalgeometrytypetmp, _geoglobaltypeit ); /\*sans le _it-1*\/ */
	  geometrytypes[_i++]=_geolocaltype;
	  /* ISCRUTE_int32(_lglobalgeometrytypetmp); */
	}
      }
      /* _lgeometrytype1_without-1 |= _lglobalgeometrytypetmp; */
	
      _attallname = _MEDgetEntityListAttributeINameAll(MED_GET_ENTITY_TYPE[_itent]);
      if (_MEDattrEntierLire(_gid0,_attallname,&_tmpusedbyncs) >= 0) {
	if ( _usedbyncs == -1 )
	  _usedbyncs=_tmpusedbyncs;
	else {
	  _usedbyncs=MIN(_usedbyncs,_tmpusedbyncs);
	}
      }
  
    } /*Fin : MED_N_ENTITY_TYPES*/

    if ( _usedbyncs == -1 )
      *usedbyncs=0;
    else
      *usedbyncs=_usedbyncs;
    
  } else {
    
    _attname    = _MEDgetEntityListAttributeIName    (entitytype);

    if (_MEDattributeInt32Rd(_gid,_attname,&_lgeometrytype1) < 0) {
      MED_ERR_(_ret,MED_ERR_READ,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_gidname)SSCRUTE(_attname);goto ERROR;
    }

    _lgeometrytypetmp       = 0;
    _itent=MEDgetEntityTypeIt(entitytype);
    for (_itgeo=1; _itgeo <= MED_GET_N_FIXED_GEO_FOR_ENTITY_TYPE_IT[_itent]; _itgeo++) {
	
      _geolocaltype    = (MED_GET_GEOMETRY_TYPE_IT_FROM_ENTITY_TYPE_IT[_itent])[_itgeo];
      _geoglobaltypeit =  MEDgetCellGeometryTypeIt(_geolocaltype);
      /* SSCRUTE(MED_GET_CELL_GEOMETRY_TYPENAME[_geoglobaltypeit]); */
      /* ISCRUTE(_MEDtest32bits(_lgeometrytypetmp,(_itgeo-1))); */
      if( _MEDtest32bits(_lgeometrytype1,(_itgeo-1)) ) {
	/* ISCRUTE(_geoglobaltypeit); */
	/* _MEDset32bits( &_lglobalgeometrytypetmp, _geoglobaltypeit ); /\*sans le _it-1*\/ */
    	if (entitytype != MED_STRUCT_ELEMENT)  {
	  geometrytypes[_i++]=_geolocaltype;
	} else {
    	  geometrytypes[_i++]=MED_STRUCT_GEO_INTERNAL+_itgeo;/*ATTENTION*/
	}
	/* ISCRUTE_int32(_lglobalgeometrytypetmp); */
      }
    }

    
    /*TODO : VERIFIER NB MAX ELSTRUCT*/
    /* FAUX ! */
    /* _i=0; */
    /* for (_it=0; _it < MED_N_CELL_GEO; _it++) { */
    /*   if ( _MEDtest32bits(_lgeometrytype1,_it) ) */
    /* 	if (entitytype != MED_STRUCT_ELEMENT)  { */
    /* 	  /\* ISCRUTE(_it); *\/ */
    /* 	  /\* ISCRUTE(entitytype); *\/ */
    /* 	  /\* SSCRUTE(MEDgetGeometryTypeName(MED_GET_CELL_GEOMETRY_TYPE[_it+1])); *\/ */
    /* 	  geometrytypes[_i++]=MED_GET_CELL_GEOMETRY_TYPE[_it+1]; */
    /* 	} else { */
    /* 	  geometrytypes[_i++]=MED_STRUCT_GEO_INTERNAL+_it+1; */
    /* 	} */
    /* } */

    _attallname = _MEDgetEntityListAttributeINameAll (entitytype);
    *usedbyncs=0;
    if (_MEDattrEntierLire(_gid0,_attallname,&_usedbyncs) < 0) {
      MED_ERR_(_ret,MED_ERR_READ,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_attallname);goto ERROR;
    }
    *usedbyncs=_usedbyncs;
    
  }
  
  _ret = 0;
  
 ERROR:
  
  if ((_gid>0) && (_gid != _gid0))  if (_MEDdatagroupFermer(_gid) < 0) {
    MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_DATAGROUP,_gidname);
    ISCRUTE_id(_gid);
  }

  if (_gid0>0)                      if (_MEDdatagroupFermer(_gid0) < 0) {
    MED_ERR_(_ret,MED_ERR_CLOSE,MED_ERR_DATAGROUP,fieldname);
    ISCRUTE_id(_gid0);
  }

  va_end(params);
  *fret = _ret;

  return;
}

