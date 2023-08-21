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

const char * const  _MEDgetEntityListAttributeIName(const med_entity_type entitytype) {
  switch( entitytype ) {
    case  MED_UNDEF_ENTITY_TYPE : return MED_NOM_LEN; break;
    case  MED_CELL              : return MED_NOM_LGC; break;
    case  MED_NODE              : return MED_NOM_LGN; break;
    case  MED_DESCENDING_FACE   : return MED_NOM_LGF; break;
    case  MED_DESCENDING_EDGE   : return MED_NOM_LGE; break;
    case  MED_NODE_ELEMENT      : return MED_NOM_LGT; break;
    case  MED_STRUCT_ELEMENT    : return MED_NOM_LGS; break;
  }
}
/*ALL : Nombre d'étapes partageant la liste globale des types utilisés dans ttes les étapes .*/
const char * const  _MEDgetEntityListAttributeINameAll(const med_entity_type entitytype) {
  switch( entitytype ) {
    case  MED_UNDEF_ENTITY_TYPE : return MED_NOM_LAA; break;
    case  MED_CELL              : return MED_NOM_LCA; break;
    case  MED_NODE              : return MED_NOM_LNA; break;
    case  MED_DESCENDING_FACE   : return MED_NOM_LFA; break;
    case  MED_DESCENDING_EDGE   : return MED_NOM_LEA; break;
    case  MED_NODE_ELEMENT      : return MED_NOM_LTA; break;
    case  MED_STRUCT_ELEMENT    : return MED_NOM_LSA; break;
  }
}
