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
#include <string.h>

/*L'itération sur les */

med_entity_type MED_GET_ENTITY_TYPE[MED_N_ENTITY_TYPES+2]={
  MED_UNDEF_ENTITY_TYPE,
  MED_CELL,
  MED_DESCENDING_FACE,
  MED_DESCENDING_EDGE,
  MED_NODE,
  MED_NODE_ELEMENT,
  MED_STRUCT_ELEMENT,
  MED_UNDEF_ENTITY_TYPE
};

const char * const MED_GET_ENTITY_TYPENAME[MED_N_ENTITY_TYPES+2]={
  "MED_UNDEF_ENTITY_TYPE",
  "MED_CELL",
  "MED_DESCENDING_FACE",
  "MED_DESCENDING_EDGE",
  "MED_NODE",
  "MED_NODE_ELEMENT",
  "MED_STRUCT_ELEMENT",
  "MED_UNDEF_ENTITY_TYPE"
};


/* MED_N_CELL_FIXED_GEO ne prend pas en compte (MED_NODE,MED_NO_GEOTYPE) 
   sinon il faudrait ajouter un MED_NO_GEOTYPE supplémentaire avant POINT1
   mais les NOEUDS ne sont pas des mailles et le MED_N_NODE_FIXED_GEO ==1 n'est 
   pas comptabilisé dans MED_N_CELL_FIXED_GEO.
   Pour le codage interne Nbits itératif des types géométrique de MED_ALL_ENTITY_TYPE ,
   il faut commencer à _it==0 contrairement aux autres type d'entités.
*/
med_geometry_type MED_GET_CELL_GEOMETRY_TYPE[MED_N_CELL_FIXED_GEO+2]={
  MED_NO_GEOTYPE,
  MED_POINT1,
  MED_SEG2,
  MED_SEG3,
  MED_SEG4,
  MED_TRIA3,
  MED_QUAD4,
  MED_TRIA6,
  MED_TRIA7,
  MED_QUAD8,
  MED_QUAD9,
  MED_TETRA4,
  MED_PYRA5,
  MED_PENTA6,
  MED_HEXA8,
  MED_TETRA10,
  MED_OCTA12,
  MED_PYRA13,
  MED_PENTA15,
  MED_PENTA18,
  MED_HEXA20,
  MED_HEXA27,
  MED_POLYGON,
  MED_POLYGON2,
  MED_POLYHEDRON,
  MED_NO_GEOTYPE
};

const char * const MED_GET_CELL_GEOMETRY_TYPENAME[MED_N_CELL_FIXED_GEO+2]={
  "MED_NO_GEOTYPE",
  "MED_POINT1",
  "MED_SEG2",
  "MED_SEG3",
  "MED_SEG4",
  "MED_TRIA3",
  "MED_QUAD4",
  "MED_TRIA6",
  "MED_TRIA7",
  "MED_QUAD8",
  "MED_QUAD9",
  "MED_TETRA4",
  "MED_PYRA5",
  "MED_PENTA6",
  "MED_HEXA8",
  "MED_TETRA10",
  "MED_OCTA12",
  "MED_PYRA13",
  "MED_PENTA15",
  "MED_PENTA18",
  "MED_HEXA20",
  "MED_HEXA27",
  "MED_POLYGON",
  "MED_POLYGON2",
  "MED_POLYHEDRON",
  "MED_NO_GEOTYPE"
};


med_geometry_type MED_GET_FACE_GEOMETRY_TYPE[MED_N_FACE_FIXED_GEO+2]={
  MED_NO_GEOTYPE,
  MED_TRIA3,
  MED_QUAD4,
  MED_TRIA6,
  MED_TRIA7,
  MED_QUAD8,
  MED_QUAD9,
  MED_POLYGON,
  MED_POLYGON2,
  MED_NO_GEOTYPE
};

const char * const MED_GET_FACE_GEOMETRY_TYPENAME[MED_N_FACE_FIXED_GEO+2]={
  "MED_NO_GEOTYPE",
  "MED_TRIA3",
  "MED_QUAD4",
  "MED_TRIA6",
  "MED_TRIA7",
  "MED_QUAD8",
  "MED_QUAD9",
  "MED_POLYGON",
  "MED_POLYGON2",
  "MED_NO_GEOTYPE"
};

med_geometry_type MED_GET_EDGE_GEOMETRY_TYPE[MED_N_EDGE_FIXED_GEO+2]={
  MED_NO_GEOTYPE,
  MED_SEG2,
  MED_SEG3,
  MED_SEG4,
  MED_NO_GEOTYPE
};

const char * MED_GET_EDGE_GEOMETRY_TYPENAME[MED_N_EDGE_FIXED_GEO+2]={
  "MED_NO_GEOTYPE",
  "MED_SEG2",
  "MED_SEG3",
  "MED_SEG4",
  "MED_NO_GEOTYPE"
};

med_geometry_type MED_GET_NODE_GEOMETRY_TYPE[MED_N_NODE_FIXED_GEO+2]={
  MED_NO_GEOTYPE,
  MED_NO_GEOTYPE,
  MED_NO_GEOTYPE
};

const char * MED_GET_NODE_GEOMETRY_TYPENAME[MED_N_NODE_FIXED_GEO+2]={
  "MED_NO_GEOTYPE",
  "MED_NO_GEOTYPE",
  "MED_NO_GEOTYPE"
};


/* A renommer en MED_GET_GEOMETRY_TYPE_FROM_ENTITY_TYPE */
/* cf. define dans med.h.in */
const med_geometry_type * const MED_GET_CELL_GEOMETRY_TYPE_FROM_ENTITY_TYPE[MED_N_ENTITY_TYPES+2]={
  MED_NULL,
  MED_GET_CELL_GEOMETRY_TYPE,
  MED_GET_FACE_GEOMETRY_TYPE,
  MED_GET_EDGE_GEOMETRY_TYPE,
  MED_GET_NODE_GEOMETRY_TYPE,
  MED_GET_CELL_GEOMETRY_TYPE, /*Les éléments aux noeuds ont les mêmes types géométriques que les CELL*/
  MED_NULL,                   /*pas de type géométrique prédéfini (statique) pour les éléments de structure */
  MED_NULL
};

const int MED_GET_N_FIXED_GEO_FOR_ENTITY_TYPE_IT[MED_N_ENTITY_TYPES+2]={
  0,
  MED_N_CELL_FIXED_GEO,
  MED_N_FACE_FIXED_GEO,
  MED_N_EDGE_FIXED_GEO,
  MED_N_NODE_FIXED_GEO,
  MED_N_CELL_FIXED_GEO, /*Les éléments aux noeuds ont les mêmes types géométriques que les CELL*/
  0,                    /*pas de type géométrique prédéfini (statique) pour les éléments de structure */
  0
};




int MEDgetEntityTypeIt(med_entity_type entitytype) {
  switch( entitytype ) {
  case  MED_UNDEF_ENTITY_TYPE : return 0; break;
  case  MED_CELL              : return 1; break;
  case  MED_DESCENDING_FACE   : return 2; break;
  case  MED_DESCENDING_EDGE   : return 3; break;
  case  MED_NODE              : return 4; break;
  case  MED_NODE_ELEMENT      : return 5; break;
  case  MED_STRUCT_ELEMENT    : return 6; break;
  /* case  MED_UNDEF_ENTITY_TYPE : return 7; break;  */
  }
};


int MEDgetCellGeometryTypeIt(med_geometry_type geotype) {
  switch( geotype ) {
  case MED_NO_GEOTYPE : return  0; break;
  case MED_POINT1     : return  1; break;
  case MED_SEG2       : return  2; break;
  case MED_SEG3       : return  3; break;
  case MED_SEG4       : return  4; break;
  case MED_TRIA3      : return  5; break;
  case MED_QUAD4      : return  6; break;
  case MED_TRIA6      : return  7; break;
  case MED_TRIA7      : return  8; break;
  case MED_QUAD8      : return  9; break;
  case MED_QUAD9      : return 10; break;
  case MED_TETRA4     : return 11; break;
  case MED_PYRA5      : return 12; break;
  case MED_PENTA6     : return 13; break;
  case MED_HEXA8      : return 14; break;
  case MED_TETRA10    : return 15; break;
  case MED_OCTA12     : return 16; break;
  case MED_PYRA13     : return 17; break;
  case MED_PENTA15    : return 18; break;
  case MED_PENTA18    : return 19; break;
  case MED_HEXA20     : return 20; break;
  case MED_HEXA27     : return 21; break;
  case MED_POLYGON    : return 22; break;
  case MED_POLYGON2   : return 23; break;
  case MED_POLYHEDRON : return 24; break;
  /* case MED_NO_GEOTYPE : return 25; break; */
  }
};


int MEDgetFaceGeometryTypeIt(med_geometry_type geotype) {
  switch( geotype ) {
  case MED_NO_GEOTYPE : return 0; break;
  case MED_TRIA3      : return 1; break;
  case MED_QUAD4      : return 2; break;
  case MED_TRIA6      : return 3; break;
  case MED_TRIA7      : return 4; break;
  case MED_QUAD8      : return 5; break;
  case MED_QUAD9      : return 6; break;
  case MED_POLYGON    : return 7; break;
  case MED_POLYGON2   : return 8; break;
  /* case MED_NO_GEOTYPE : return 9; break; */
  }
};

int MEDgetEdgeGeometryTypeIt(med_geometry_type geotype) {
  switch( geotype ) {
  case MED_NO_GEOTYPE : return 0; break;
  case MED_SEG2       : return 1; break;
  case MED_SEG3       : return 2; break;
  case MED_SEG4       : return 3; break;
  }
};

int MEDgetNodeGeometryTypeIt(med_geometry_type geotype) {
  switch( geotype ) {
  case MED_NO_GEOTYPE : return 1; break;
  }
};

int MEDgetEntityGeometryTypeIt(med_entity_type entitytype, med_geometry_type geotype) {
  switch( entitytype ) {
  case  MED_UNDEF_ENTITY_TYPE : return 0; break;
  case  MED_CELL              : return MEDgetCellGeometryTypeIt(geotype); break;
  case  MED_DESCENDING_FACE   : return MEDgetFaceGeometryTypeIt(geotype); break;
  case  MED_DESCENDING_EDGE   : return MEDgetEdgeGeometryTypeIt(geotype); break;
  case  MED_NODE              : return MEDgetNodeGeometryTypeIt(geotype); break;
  case  MED_NODE_ELEMENT      : return MEDgetCellGeometryTypeIt(geotype); break;
  case  MED_STRUCT_ELEMENT    : return geotype%MED_STRUCT_GEO_INTERNAL  ; break;
  }
};

const char * const  MEDgetEntityTypeName(med_entity_type entitytype) {
  switch( entitytype ) {
    case  MED_UNDEF_ENTITY_TYPE : return "MED_UNDEF_ENTITY_TYPE"; break;
    case  MED_CELL              : return "MED_CELL"             ; break;
    case  MED_DESCENDING_FACE   : return "MED_DESCENDING_FACE"  ; break;
    case  MED_DESCENDING_EDGE   : return "MED_DESCENDING_EDGE"  ; break;
    case  MED_NODE              : return "MED_NODE"             ; break;
    case  MED_NODE_ELEMENT      : return "MED_NODE_ELEMENT"     ; break;
    case  MED_STRUCT_ELEMENT    : return "MED_STRUCT_ELEMENT"   ; break;
  }
}

const char * const  MEDgetGeometryTypeName(med_geometry_type geotype) {
  switch( geotype ) {
     case  MED_NO_GEOTYPE   :  return "MED_NO_GEOTYPE"; break;
     case  MED_POINT1       :  return "MED_POINT1"    ; break;   
     case  MED_SEG2	    :  return "MED_SEG2"      ; break;     
     case  MED_SEG3	    :  return "MED_SEG3"      ; break;     
     case  MED_SEG4	    :  return "MED_SEG4"      ; break;     
     case  MED_TRIA3	    :  return "MED_TRIA3"     ; break;    
     case  MED_QUAD4	    :  return "MED_QUAD4"     ; break;    
     case  MED_TRIA6	    :  return "MED_TRIA6"     ; break;    
     case  MED_TRIA7	    :  return "MED_TRIA7"     ; break;    
     case  MED_QUAD8	    :  return "MED_QUAD8"     ; break;    
     case  MED_QUAD9	    :  return "MED_QUAD9"     ; break;    
     case  MED_TETRA4       :  return "MED_TETRA4"    ; break;   
     case  MED_PYRA5	    :  return "MED_PYRA5"     ; break;    
     case  MED_PENTA6       :  return "MED_PENTA6"    ; break;   
     case  MED_HEXA8	    :  return "MED_HEXA8"     ; break;    
     case  MED_TETRA10      :  return "MED_TETRA10"   ; break;  
     case  MED_OCTA12       :  return "MED_OCTA12"    ; break;   
     case  MED_PYRA13       :  return "MED_PYRA13"    ; break;   
     case  MED_PENTA15      :  return "MED_PENTA15"   ; break;  
     case  MED_PENTA18      :  return "MED_PENTA18"   ; break;  
     case  MED_HEXA20       :  return "MED_HEXA20"    ; break;   
     case  MED_HEXA27       :  return "MED_HEXA27"    ; break;   
     case  MED_POLYGON      :  return "MED_POLYGON"   ; break;  
     case  MED_POLYGON2     :  return "MED_POLYGON2"  ; break; 
     case  MED_POLYHEDRON   :  return "MED_POLYHEDRON"; break;
  default :
    return "MED_UNKNOWN_GEOTYPE";
    break;
  }
};
