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

/**\ingroup MEDfield
  \brief \MEDfieldnGeometryTypeBrief
  \param fid \fid
  \param fieldname \fieldname
  \param numdt \numdt
  \param numit \numit
  \param entitytype \entitytype
  \retval med_int \ngeotype \n \error
  \details \MEDfieldnGeometryTypeDetails
  \remarks
  \MEDfieldnGeometryTypeRem1
  \see MEDfieldGeometryType
  \see MEDfieldnEntityType
  \see MEDfileNumVersionRd
  \see MEDfieldnValue
  \see MEDfieldnValueWithProfile
  \see MEDfieldnValueWithProfileByName
 */
med_int MEDfieldnGeometryType(const med_idt         fid,
			       const char * const    fieldname,
			       const med_int         numdt,
			       const med_int         numit,
			       const med_entity_type entitytype)

{
  char *  name = "_MEDfieldnGeometryType";
  int     dummy=0;
  med_int fret=-1;
  med_int majeur=0, mineur=0, release=0;
  med_int fileversionMM=0;
  MedFuncType func;


  MEDfileNumVersionRd(fid, &majeur, &mineur, &release);
  fileversionMM  = 10*majeur+mineur;

  /*
    Les modèles de données internes < 41 n'ont pas les meta datas
    pour répondre à cette API.
   */
  if (fileversionMM < 41) {
    MED_ERR_(fret,MED_ERR_RANGE,MED_ERR_PROPERTY,MED_ERR_FILEVERSION_MSG);
    ISCRUTE(majeur);ISCRUTE(mineur);ISCRUTE(release);
    goto ERROR;
  }
  
  func = _MEDversionedApi3(name,majeur,mineur,release);
  if ( func != (MedFuncType) NULL )
    func (dummy,
	  fid,
	  fieldname,
	  numdt,
	  numit,
	  entitytype,
	  &fret);
  
 ERROR:
  return fret;
}
