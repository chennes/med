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


#include "med_config.h"
#include "med_outils.h"
#include "med.h"

#include <string.h>

#include "MAJ_400_410.h"
#include "MAJ_version.h"

#define USER_MODE MED_COMPACT_STMODE

#include "_MEDfieldValueUpdateEntityList41.c"

med_err getFieldsOn40(med_idt                  fid,
		    const char * const       nommaa,
		    med_int                  nmodels,
		    const med_geometry_type* geotype_elst,
		    const char *             geotypename_elst,
		    const char * const       nomcha,
		    const char * const       dtunit,
		    const med_field_type     typcha,
		    const med_int            ncomp,
		    const char * const       comp,
		    const char * const       unit, 
		    const med_entity_type    entite,
		    const med_switch_mode    stockage,
		    const med_int            ncstp) {

  int       i,j,k,l,m,n,nb_geo=0;
  med_int   nbpdtnor=0,pflsize,*pflval,ngauss=0,ngroup,nval;
  med_int   numdt=0,numo=0,nprofile=0;
  med_int   meshnumdt=0, meshnumit=0 ;
  med_size  medtype_size=0;
  med_size  _sizei=0,_sizef=0,_sizeNbr=0;
  med_float dt=0.0;
  unsigned char *val = NULL; 
  med_err  ret=0;
  char     pflname      [MED_NAME_SIZE+1]="";
  char     _profilename [MED_NAME_SIZE+1]="";
  char     locname [MED_NAME_SIZE+1]="";
  char     _pathi[(MED_FIELD_GRP_SIZE  +MED_NAME_SIZE+1)+2*MED_MAX_PARA+1] = MED_FIELD_GRP;
  char     _pathf[(MED_FIELD_GRP_SIZE+1+MED_NAME_SIZE+1)+2*MED_MAX_PARA+1] = "/CHA_/";
  char     _pathtmp[MED_FIELD_GRP_SIZE+3]="/CHA__/";
  char     _getNBR[(MED_FIELD_GRP_SIZE+1+MED_NAME_SIZE+1)+(2*MED_MAX_PARA+1)+(2*MED_TAILLE_NOM_ENTITE+2)+(MED_NAME_SIZE+1)+MED_TAILLE_NOM_ENTITE+1] = MED_FIELD_GRP;
  char     _entitygeotypename[2*MED_TAILLE_NOM_ENTITE+2]="";
  char     * lien = NULL;
  med_bool            _fieldexist = MED_FALSE;
  med_bool            _meshexist  = MED_FALSE;
  med_int             _nentFromMesh   = 0;
  med_int             _nentFromField  = 0;
  med_int             _nent           = 0;
  med_geometry_type   *type_geo;
  med_data_type       meddatatype    = MED_CONNECTIVITY;
  med_bool            changement     = MED_FALSE;
  med_bool            transformation = MED_FALSE;
  htri_t              _datasetexist;

  char _gidname                [MED_FIELD_GRP_SIZE+MED_NAME_SIZE+1]=MED_FIELD_GRP;
  char _datagroupname1         [2*MED_MAX_PARA+1]="";
  med_idt _gid=0,_datagroup1 =0;
  
  const char * const * AFF;
  const char * const * AFF_ENT=MED_GET_ENTITY_TYPENAME+1;
  const char * * AFF_STRUCT = NULL;

  switch (entite) {
  case MED_NODE :
    type_geo = MED_GET_NODE_GEOMETRY_TYPE;
    nb_geo   = MED_N_NODE_FIXED_GEO;
    AFF      = MED_GET_NODE_GEOMETRY_TYPENAME;
    meddatatype = MED_COORDINATE;
    break;
  case  MED_CELL :
  case  MED_NODE_ELEMENT :
    type_geo = MED_GET_CELL_GEOMETRY_TYPE;
    nb_geo   = MED_N_CELL_FIXED_GEO;
    AFF      = MED_GET_CELL_GEOMETRY_TYPENAME;
    break;
  case  MED_DESCENDING_FACE :
    type_geo = MED_GET_FACE_GEOMETRY_TYPE;
    nb_geo   = MED_N_FACE_FIXED_GEO;
    AFF      = MED_GET_FACE_GEOMETRY_TYPENAME;
    break;
  case  MED_DESCENDING_EDGE :
    type_geo = MED_GET_EDGE_GEOMETRY_TYPE;
    nb_geo   = MED_N_EDGE_FIXED_GEO;
    AFF      = MED_GET_EDGE_GEOMETRY_TYPENAME;
    break;
  case  MED_STRUCT_ELEMENT :
    AFF_STRUCT = (const char * *) calloc(sizeof(const char * ),nmodels+1);
    for(i=0;i<nmodels;++i) AFF_STRUCT[i+1]= &geotypename_elst[(MED_NAME_SIZE+1)*i];
    type_geo = (med_geometry_type*)(geotype_elst)-1;
    nb_geo   = nmodels;
    AFF      = AFF_STRUCT;
    break;

  }

  strcat(_gidname,nomcha);
  MED_ERR_EXIT_IF((_gid = _MEDdatagroupOuvrir(fid,_gidname)) < 0, MED_ERR_OPEN, MED_ERR_DATAGROUP,nomcha);
  
  for (k=1;k<=nb_geo;k++) {

    /* Combien de séquences (PDT,NOR) a lire */
    nbpdtnor = ncstp;
    if (nbpdtnor < 1 ) continue;
    
    for (j=0;j<nbpdtnor;j++) {
	
      if ( MEDfieldComputingStepMeshInfo(fid, nomcha, j+1, &numdt, &numo,
					 &dt, &meshnumdt, &meshnumit) < 0 ) {
	MESSAGE("Erreur a l'appel de MEDfieldComputingStepMeshInfo : ");
	EXIT_IF(NULL == NULL,NULL,NULL);
      }

      _datagroup1 = 0;
      _MEDgetComputationStepName(MED_SORT_DTIT,numdt,numo,_datagroupname1);
      MED_ERR_EXIT_IF(( _datagroup1 = _MEDdatagroupOuvrir(_gid,_datagroupname1)) < 0, MED_ERR_OPEN,MED_ERR_DATAGROUP,_datagroupname1);


      /* 	printf("\n  +Pas de Temps n."IFORMAT" (%f) [%s], n. d'ordre "IFORMAT", avec "IFORMAT" valeur(s) par entité.\n",numdt,dt,dtunit,numo,ngauss); */
      /* 	printf("\t- Il y a "IFORMAT" entités qui portent des valeurs en mode %i. Chaque entite %s\ */
      /* de type geometrique %s associes au profile |%s| a "IFORMAT" valeurs associées \n", */
      /* 	       nval,USER_MODE,AFF_ENT[(int)entite],AFF[k],pflname,ngauss); */

      /*Ajout des méta-data au champ */

      /*Mise à jour de la liste des types d'entités au niveau des deux groupes _gid et _datagroup1 */
      MED_ERR_EXIT_IF(( _MEDfieldValueUpdateEntityList(nomcha,_datagroupname1,_gid,_datagroup1,entite,type_geo[k]  ,1)) < 0 ,
		       MED_ERR_WRITE,MED_ERR_FIELD,nomcha);
      /*Mise à jour de la liste des types géométriques pour le type d'entité <entitype> au niveau _gid et _datagroup1 */
      MED_ERR_EXIT_IF(( _MEDfieldValueUpdateEntityList(nomcha,_datagroupname1,_gid,_datagroup1,entite,type_geo[k]  ,0)) < 0 ,
		       MED_ERR_WRITE,MED_ERR_FIELD,nomcha);

      /* fprintf(stdout,"  ... Ajout des meta-données du champ effectuée...\n"); */

      if (_datagroup1>0) ret= (_MEDdatagroupFermer(_datagroup1) < 0);
      MED_ERR_EXIT_IF(ret,MED_ERR_CLOSE,MED_ERR_DATAGROUP,_datagroupname1);


    } /* fin for sur les étapes de calcul */


  } /* fin for sur les types géométriques de maille */

  if (_gid>0) ret= (_MEDdatagroupFermer(_gid) < 0);
  MED_ERR_EXIT_IF(ret,MED_ERR_CLOSE,MED_ERR_DATAGROUP,_gidname);


  free(AFF_STRUCT);
  return ret;
}


  
void MAJ_400_410_champs(med_idt fid)
{
  med_err         ret=0,lret=0;
  med_field_type  typcha;
  char            nomcha   [MED_NAME_SIZE+1]="";
  char            meshname [MED_NAME_SIZE+1]="";
  char            dtunit   [MED_SNAME_SIZE+1]="";
  char            *comp= NULL, *unit= NULL;
  med_int         ncomp,ncha;
  med_int         ncstp=0;
  med_bool        local=MED_FALSE;
  htri_t          _datasetexist;
  char _pathi[(MED_FIELD_GRP_SIZE  +MED_NAME_SIZE+1)+2*MED_MAX_PARA+1] = MED_FIELD_GRP;
  char _pathf[(MED_FIELD_GRP_SIZE+1+MED_NAME_SIZE+1)+2*MED_MAX_PARA+1] = "/CHA_/";
  char _pathtmp[MED_FIELD_GRP_SIZE+3]="/CHA__/";
  int              i=0,_num=0;
  /* char            _cstpname[2*MED_MAX_PARA+1]=""; */
  med_int             _nmodels=0;
  med_switch_mode     mode_coo = MED_NO_INTERLACE;
  
  med_geometry_type * geotype_elst;
  char              * geotypename_elst;

  med_geometry_type _geotype=MED_NONE;
  char              _elementname[MED_NAME_SIZE+1]="";
  med_int           _elementdim=0;
  char              _supportmeshname[MED_NAME_SIZE+1]="";
  med_entity_type   _entitytype=MED_UNDEF_ENTITY_TYPE;
  med_int           _nnode=0;
  med_int           _ncell=0;
  med_geometry_type _geocelltype=MED_NONE;
  char              _geocelltypename[MED_SNAME_SIZE+1]="";
  med_int           _nconstantattribute=0;
  med_bool          _anyprofile=MED_FALSE;
  med_int           _nvariableattribute=0;

  MAJ_version_num(fid,4,0,0);

  _nmodels = MEDnStructElement(fid);
  EXIT_IF(_nmodels < 0,"lors de la lecture du nombre d'éléments de structure",NULL);

  /* nmailles_elst     = (med_int *)           malloc(_nmodels*sizeof(med_int)); */
  geotype_elst      = (med_geometry_type *) malloc(_nmodels*sizeof(med_geometry_type));
  geotypename_elst  = (char *)              malloc(_nmodels*sizeof(char)*(MED_NAME_SIZE+1));

  for (i=0; i < _nmodels; i++) {
    ret= MEDstructElementInfo(fid, i+1, &geotypename_elst[i*(MED_NAME_SIZE+1)], &geotype_elst[i],
			       &_elementdim, _supportmeshname,
			       &_entitytype, &_nnode, &_ncell, &_geocelltype,
			       &_nconstantattribute, &_anyprofile, &_nvariableattribute );
    EXIT_IF(ret < 0,"lors de la demande d'information sur les éléments de structure",NULL);

  }

  /* combien de champs dans le fichier */
  ncha = MEDnField(fid);
  EXIT_IF(ncha < 0,"lors de la lecture du nombre de champs",NULL);

  /* MAJ des champs */
  for (i=0;i<ncha;i++) {

    /* Lecture du nombre de composantes */
    ncomp = MEDfieldnComponent(fid,i+1);
    if (ncomp < 0) {
      MESSAGE("Erreur à la lecture du nombre de composantes : "); ISCRUTE(ncomp);
      exit(1);
    }

    /* Lecture du type du champ, des noms des composantes et du nom de l'unité*/
    comp = (char*) malloc(ncomp*MED_SNAME_SIZE+1);
    EXIT_IF(comp == NULL,NULL,NULL);
    unit = (char*) malloc(ncomp*MED_SNAME_SIZE+1);
    EXIT_IF(unit == NULL,NULL,NULL);

    ret = MEDfieldInfo(fid,i+1,nomcha,meshname,&local,&typcha,comp,unit,dtunit,&ncstp);
    MED_ERR_EXIT_IF(ret,MED_ERR_ACCESS,MED_ERR_FIELD,nomcha);

    fprintf(stdout,"  >>> Normalisation du champ [%s] \n",nomcha);

    /* champs aux noeuds */
    lret = getFieldsOn40(fid, meshname, _nmodels, geotype_elst,geotypename_elst,
		       nomcha, dtunit, typcha, ncomp, comp, unit, MED_NODE, mode_coo, ncstp);

    /* champs sur les elements et aux points de Gauss */
    if (lret == 0) lret = getFieldsOn40(fid,  meshname, _nmodels, geotype_elst, geotypename_elst,
				      nomcha, dtunit, typcha, ncomp, comp, unit, MED_CELL, mode_coo, ncstp);
    else { MESSAGE("Erreur à la lecture des champs aux noeuds "); ret = -1; continue;}
   
    if (lret == 0) lret = getFieldsOn40(fid,  meshname, _nmodels, geotype_elst, geotypename_elst,
				      nomcha, dtunit, typcha, ncomp, comp, unit, MED_DESCENDING_FACE, mode_coo, ncstp);
    else { MESSAGE("Erreur à la lecture des champs aux mailles "); ret = -1; continue;}
   
    if (lret == 0) lret = getFieldsOn40(fid,  meshname, _nmodels, geotype_elst, geotypename_elst,
				      nomcha, dtunit, typcha, ncomp, comp, unit, MED_DESCENDING_EDGE, mode_coo, ncstp);
    else {MESSAGE("Erreur à la lecture des champs aux faces "); ret = -1; continue;}
    
    if (lret == 0) lret = getFieldsOn40(fid,  meshname, _nmodels, geotype_elst, geotypename_elst,
				      nomcha, dtunit, typcha, ncomp, comp, unit, MED_NODE_ELEMENT,mode_coo, ncstp);
    else {MESSAGE("Erreur a la lecture des champs aux aretes "); ret = -1; continue;}

    if  (lret != 0) {MESSAGE("Erreur a la lecture des champs aux noeuds des mailles "); ret = -1;};

    if (_nmodels)
      lret = getFieldsOn40(fid,  meshname, _nmodels, geotype_elst,geotypename_elst,
			 nomcha, dtunit, typcha, ncomp, comp, unit, MED_STRUCT_ELEMENT,mode_coo, ncstp);
    if  (lret != 0) {MESSAGE("Erreur a la lecture des champs aux éléments de sructure "); ret = -1;};


    fprintf(stdout,"  >>> Normalisation du champ [%s] : ... OK ... \n",nomcha);


  CONT:

    free(comp);
    free(unit);
    /* MAJ_version_num(fid,4,0,0); */
  }
  
  free(geotype_elst);
  free(geotypename_elst);

  /* _MEDobjetsOuverts(fid);  */

}

