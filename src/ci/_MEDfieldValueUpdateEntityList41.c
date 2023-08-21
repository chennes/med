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


#include <med.h>
#include <med_config.h>
#include <med_outils.h>
#include <string.h>
#include <stdlib.h>

/* Inclus par med.h.in */
/* #include <stdint.h> */

/* #define NDEBUG */
/* #include <assert.h> */

/* const char * const  _MEDgetEntityListAttributeIName(const med_entity_type entitytype) { */
/*   switch( entitytype ) { */
/*     case  MED_UNDEF_ENTITY_TYPE : return MED_NOM_LEN; break; */
/*     case  MED_CELL              : return MED_NOM_LGC; break; */
/*     case  MED_NODE              : return MED_NOM_LGN; break; */
/*     case  MED_DESCENDING_FACE   : return MED_NOM_LGF; break; */
/*     case  MED_DESCENDING_EDGE   : return MED_NOM_LGE; break; */
/*     case  MED_NODE_ELEMENT      : return MED_NOM_LGT; break; */
/*     case  MED_STRUCT_ELEMENT    : return MED_NOM_LGS; break; */
/*   } */
/* } */
/* /\*ALL : Toutes les étapes de calcul.*\/ */
/* const char * const  _MEDgetEntityListAttributeINameAll(const med_entity_type entitytype) { */
/*   switch( entitytype ) { */
/*     case  MED_UNDEF_ENTITY_TYPE : return MED_NOM_LAA; break; */
/*     case  MED_CELL              : return MED_NOM_LCA; break; */
/*     case  MED_NODE              : return MED_NOM_LNA; break; */
/*     case  MED_DESCENDING_FACE   : return MED_NOM_LFA; break; */
/*     case  MED_DESCENDING_EDGE   : return MED_NOM_LEA; break; */
/*     case  MED_NODE_ELEMENT      : return MED_NOM_LTA; break; */
/*     case  MED_STRUCT_ELEMENT    : return MED_NOM_LSA; break; */
/*   } */
/* } */


/*Mise à jour de la liste des types d'entités/géométriques utilisés globlalement au niveau du datagroup _gid0 et
  Mise à jour de la liste des types d'entités/géométriques utilisés localement   au niveau du datagroup _gid1    
  Les gidname sont utilisés pour générér des messages d'erreur avec des informations significatives (todo : retrouver le nom avec l'objid)
*/

static med_int  _MEDfieldValueUpdateEntityList(const char *            const gid0name    ,
					const char *            const gid1name    ,
					const med_idt                 gid0	  ,
					const med_idt                 gid1	  ,
					const med_entity_type         entitytype  ,
					const med_geometry_type       geotype     ,
					const med_bool                forentity   ) {

  med_bool _attexist                              = MED_FALSE;
  med_err  _ret                                   = -1;
  uint32_t  _lentitytype1  		    	  = 0;
  uint32_t  _lentitytype2   		    	  = 0;
  uint32_t  _lentitytype1sav   		    	  = 0;
  uint32_t  _lentitytype2sav   		    	  = 0;
  uint32_t _lgeotype	   		    	  = 0;
  med_int  _nsamelentitype    		    	  = 0;
  med_int  _nsamelentitypesav 		    	  = 0;
  med_idt  _gid				    	  = gid0;
  med_idt  _datagroup1			    	  = gid1;
  const char *    _attname   			  = NULL;
  const char *    _attallname			  = NULL;
  const char *    fieldname        		  = gid0name;
  const char *    _datagroupname1  		  = gid1name;
  med_entity_type _entytypeforattname 		  = MED_UNDEF_ENTITY_TYPE;
  int             _it                             = 0;

 
  /*Si l'on met à jour la liste des types géométriques (forentity==0), il faut récupérer :
    - le nom de l'attribut qui les stocke pour l'entitytype passé en paramètre
    - le nom de l'attribut qui stocke le nombre d'étapes de calcul qui ont la même liste 
    Sinon, on récupère, les noms d'attributs associés à la liste des type d'entités
  */
  if (! forentity) _entytypeforattname = entitytype;     
  _attname    = _MEDgetEntityListAttributeIName    (_entytypeforattname);
  _attallname = _MEDgetEntityListAttributeINameAll (_entytypeforattname);

  /* - La fonction MEDgetEntityGeometyTypeIt(entitytype,geotype) nous permet d'obtenir un numéro d'itération de type géométrique 
     (commence à 1 et est incrémental) que l'on associe à un numéro de bit d'un entier 32bits (1 entier pour chaque type d'entité)
     - Cet entier est stocké pour chaque étape de calcul et globalement au champ (si au moins un type géométrique existe pour ce type d'entité). 
     Cela permet de limiter la taille du stockage et d'accéder directement par type d'entité aux types géométriques présents.  
  */
  if (forentity)
    _it=entitytype;
  else 
    _it=MEDgetEntityGeometryTypeIt(entitytype, geotype)-1;

  /* ISCRUTE_int(entitytype);ISCRUTE_int(geotype); */
  /* SSCRUTE(MED_GET_ENTITY_TYPENAME[MEDgetEntityTypeIt(entitytype)]); */
  /*TODO : Etudier la possibilité de récupérer le nom avec l'id de l'objet */

  /* SSCRUTE(fieldname); */
  /* SSCRUTE(MEDgetEntityTypeName(entitytype)); SSCRUTE(MEDgetGeometryTypeName(geotype)); */
  /* SSCRUTE(_attname);                         SSCRUTE(_attallname); */
  
  /*Lire l'attribut _attname s'il exite, sinon la valeur lue est nulle */
  _MEDattributeExist(_gid,".",_attname,&_attexist);
  if (_attexist) {
/* if ( forentity) */
    if (_MEDattributeInt32Rd(_gid,_attname,&_lentitytype1sav) < 0) {
      MED_ERR_(_ret,MED_ERR_READ,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_attname);goto ERROR;
    }
  }
  _lentitytype1 = _lentitytype1sav;

  /* _MEDset32bits(&_lentitytype1, MEDgetEntityTypeIt(entitytype)); */ 
  /* On utilise directement la valeur de l'enum pour l'entitype, ainsi on utilise le décalage de 0 (on économise 1bit) */
  /* Mise à jour de la liste d'entités/types géométriques au niveau du champ */
  /* */
  /* ISCRUTE_int8(_lentitytype1sav); */
  /* _MEDset32bits(&_lentitytype1, MEDgetEntityTypeIt(entitytype)); */
  /* Utilise le numéro d'itération pour le type géométrique du type d'entité donné pour positionner le bit de même position (-1) */
  _MEDset32bits(&_lentitytype1, _it);
  /* ISCRUTE_int8(_lentitytype1); */

  /* Ecriture de la liste globale des types */
  /*REM : Si l'attribut n'existait pas _lentitytype1sav == 0 et il ne se peut pas que _lentitytype1 == 0 même si entitytype == 0 
   à cause du _MEDsetNbits() */
  if ( _lentitytype1sav != _lentitytype1 ) {
/* if ( forentity) */
    if ( _MEDattributeInt32Wr(_gid,_attname,&_lentitytype1) < 0) {
      MED_ERR_(_ret,MED_ERR_WRITE,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_attname);goto ERROR;
    }
  }
  
  /*
   * Il faut mettre à jour au niveau 2 (étape de calcul)
   * la liste des types d'entités ou des types géométriques d'entités utilisées
   */
  _MEDattributeExist(_datagroup1,".",_attname,&_attexist);
  if (_attexist) {
    if (_MEDattributeInt32Rd(_datagroup1,_attname,&_lentitytype2sav) < 0) {
      MED_ERR_(_ret,MED_ERR_READ,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_datagroupname1);SSCRUTE(_attname);goto ERROR;
    }
  }
  _lentitytype2 = _lentitytype2sav;

  /* Mise à jour de la liste d'entités*/
  /* ISCRUTE_int8(_lentitytype2sav); */
  _MEDset32bits(&_lentitytype2, _it);
  /* ISCRUTE_int8(_lentitytype2); */

  if ( _lentitytype2sav != _lentitytype2 )
    if ( _MEDattributeInt32Wr(_datagroup1,_attname,&_lentitytype2) < 0) {
      MED_ERR_(_ret,MED_ERR_WRITE,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_datagroupname1);SSCRUTE(_attname);goto ERROR;
    }

  /* GESTION DU NOMBRE D'ETAPES DE CALCUL */
  
  /* Il faut pouvoir indiquer à l'utilisateur qu'il n'a pas besoin d'interroger toutes les étapes de calcul
     pour connaître la liste des types d'entités utilisées si cette liste est la même pour toutes les étapes.
     On vérifie que la liste des types d'entités utilisées à cette étape de calcul est le même que celle au niveau du champ global :

    - Si  la liste des types d'entités ou des types géométriques d'entité utilisés globalement 
    avant l'appel à cette fonction était identique à la notre avant m.a.j. :
        _lentitytype1sav == _lentitytype2sav  =>
	* Si la nouvelle liste est toujours  identique : 
	     Ne rien faire, on le change pas le nbre d'étapes de calcul ayant la même liste
        * Si la nouvelle liste devient différente (ajout d'un nouveau type à la liste) : 
	     positionner le nombre d'étapes de calcul ayant la même liste de types d'entités à 1 (la notre)
    - Si  la liste des types d'entités utilisés avant l'appel à cette fonction était différente 
      entre celle de tous les autres étapes de calcul et celle de notre étape de calcul :
        _lentitytype1sav != _lentitytype2sav  =>
	* Si la nouvelle liste est identique incrémenter le nombre d'étapes de calcul ayant la même liste de types d'entités
        * Si la nouvelle liste est toujours différente : 
	Si notre type d'entité n'appartenait pas à la liste globale initiale => 0 sinon Ne rien faire, 
	on le change pas le nbre d'étapes de calcul ayant la même liste.
   */

  /* Cree l'attribut _attallname s'il n'exite pas déjà au niveau 0, sinon lit sa valeur */
  /* Nombre d'étapes de calcul partageant la même liste d'entités/types géométriques */
  _MEDattributeExist(_gid,".",_attallname,&_attexist);
  if (_attexist) {
    if (_MEDattrEntierLire(_gid,_attallname,&_nsamelentitype) < 0) {
      MED_ERR_(_ret,MED_ERR_READ,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_attallname);goto ERROR;
    }
  } else
    _nsamelentitype = 0;
  _nsamelentitypesav = _nsamelentitype;

  /** Il faut vérifier pour notre type d'entité indépendemment des autres déjà positionnées **/
  /*(VERIF:) En HDF//, le mécanisme fonctionne car l'écriture d'attribut n'est pas // */
  /* Si les listes de types d'entitées étaient identiques */
  if ( _lentitytype1sav == _lentitytype2sav ) {
    if ( (_lentitytype1sav != _lentitytype1 /*faux : idem _lentitytype2*/ ) || (!_lentitytype1sav) ) {
      /*Le fait que l'on en ajoute ou en supprime un modifie le nbre d'étape de calcul ayant la meme liste */
      /*Si on ajoute un nouveau type d'entite, il n'y a plus que notre étape en adéquation. */
      _nsamelentitype=1;
      /*La supression d'un type d'entité écrit en MED n'est pas possible*/
      /* ISCRUTE(_nsamelentitype); */
    } else {
      /*Il n'y a rien à faire car notre liste de type est toujours la même que la globale*/
      /* ISCRUTE(_nsamelentitype); */
    }
  } else {
  /* Si les listes de types d'entitées étaient déjà différentes */
    /*Si nos listes sont devenues les mêmes*/
    if (_lentitytype1 == _lentitytype2) {
      /*Les liste de types d'entités deviennent identiques, il faut alors incrémenter le nbre d'étapes utilisant
	la même liste.*/
      ++_nsamelentitype;
      /* ISCRUTE(_nsamelentitype); */
    }  else {
      /*Si nos listes ne sont pas devenues les mêmes*/
      /*Ds ce cas de figure l'étape de calcul concernée n'utilisait pas 
       * la liste de types d'entité du champ (il n'était pas comptabilisé dans le Nb. d'étapes de même liste d'entité).
       * La nouvelle liste d'entité utilisée par cette étape n'est toujours pas devenue la même que celle du champ.
       * Soit parcequ'il lui manque toujours certains type d'entités, soit parcequ'il utilise un nouveau type d'entité.
       */
      /* Si notre type d'entité n'appartenait pas à la liste globale initiale => 0 sinon on ne fait rien  */
      if (!_MEDtest32bits(_lentitytype1sav,_it) ) _nsamelentitype=0; 
       /* ISCRUTE(_nsamelentitype); */
   }
  }
  
  if ( _nsamelentitypesav != _nsamelentitype ) {
/* if ( forentity) */
    if ( _MEDattributeIntWr(_gid,_attallname,&_nsamelentitype) < 0) {
      MED_ERR_(_ret,MED_ERR_WRITE,MED_ERR_ATTRIBUTE,MED_ERR_FIELD_MSG);
      SSCRUTE(fieldname);SSCRUTE(_attallname);goto ERROR;
    }
  }

  _ret = 0;

 ERROR:
  return _ret;
}

