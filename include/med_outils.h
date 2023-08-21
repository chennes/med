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

#ifndef MED_OUTILS_H
#define MED_OUTILS_H
#include <med.h>
#include "med_vargs.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

#define MED_MAJOR_NAME "MAJ"
#define MED_MINOR_NAME "MIN"
#define MED_RELEASE_NAME "REL"

#define MED_NOM_MAJEUR "MAJ"
#define MED_NOM_MINEUR "MIN"
#define MED_NOM_RELEASE "REL"

#define MED_NOM_DESCRIPTEUR "descripteur de fichier"
#define MED_COMMENT_NAME MED_NOM_DESCRIPTEUR

/* Noms des data sets ou attributs correspondant a des entites MED */
#define MED_TAILLE_NOM_ENTITE MED_NAME_SIZE
#define MED_NOM_NUM "NUM" /**< Nom du dataset contenant les numéros optionnels des entités                                                                                                                                                           */
#define MED_NOM_NBR "NBR" /**< Généralement le nombre d'entités référencées                                                                                                                                                                          */
#define MED_NOM_NOM "NOM" /**< Nom du dataset contenant les noms optionnels des entités                                                                                                                                                              */
#define MED_NOM_UNV "UNV" /**< Nom du dataset contenant le nom universel du fichier                                                                                                                                                                  */
#define MED_NOM_NNS "NNS" /**< Nombre de noeuds sommets                                                                                                                                                                                              */
#define MED_NOM_NNM "NNM" /**< Nombre de noeuds maximum par maille                                                                                                                                                                                   */
#define MED_NOM_NNI "NNI" /**< Nombre de noeuds isolés                                                                                                                                                                                               */
#define MED_NOM_GRO "GRO" /**< Nom du dataset contenant les noms des groupes associés à une famille                                                                                                                                                  */
#define MED_NOM_ATT "ATT" /**< Type des valeurs des attributs cst/var.                                                                                                                                                                               */
#define MED_NOM_NCO "NCO" /**< Nombre de composantes/constituants par valeur                                                                                                                                                                         */
#define MED_NOM_DIM "DIM" /**< Dimension d'un maillage                                                                                                                                                                                               */
#define MED_NOM_ESP "ESP" /**< Dimension de l'espace utilisé                                                                                                                                                                                         */
#define MED_NOM_FAM "FAM" /**< Nom du dataset contenant les numéros de familles des entitées                                                                                                                                                         */
#define MED_NOM_IDE "IDE" /**< Identificateur d'attribut de famille (med 2.x)                                                                                                                                                                        */
#define MED_NOM_VAL "VAL" /**< Valeur d'un attribut de famille (med 2.x) /Poids de points d'intégrations/Valeur d'un paramètre scalaire                                                                                                                                              */
#define MED_NOM_DES "DES" /**< Dataset contenant une connectivité descendante de mailles/polyèdres | Descripteur d'attribut de famille (med 2.x) / de paramètre scalaire / d'équivalence / de maillage                                                                               */
#define MED_NOM_COR "COR" /**< Nom du dataset contenant : les correspondances d'une équivalence / valeurs d'un attribut constant (elstruct)                                                                                                                                          */
#define MED_NOM_COO "COO" /**< Nom du dataset contenant des coordonnées                                                                                                                                                                                                              */
#define MED_NOM_TRF "TRF" /**< Nom du dataset contenant des paramètres de translation/rotation                                                                                                                                                                                       */
#define MED_NOM_IN1 "IN1" /**< Nom du dataset contenant les indices de grilles sur l'axe1                                                                                                                                                                                            */
#define MED_NOM_IN2 "IN2" /**< Nom du dataset contenant les indices de grilles sur l'axe2                                                                                                                                                                                            */
#define MED_NOM_IN3 "IN3" /**< Nom du dataset contenant les indices de grilles sur l'axe3                                                                                                                                                                                            */
#define MED_NOM_REP "REP" /**< Type de repère utilisé                                                                                                                                                                                                                                */
#define MED_NOM_UNI "UNI" /**< Nom(s) de(s) (l') unité(s) des composantes (field)/ou des axes (mesh)                                                                                                                                                                                 */
#define MED_NOM_UNT "UNT" /**< Unité du pas de temps                                                                                                                                                                                                 */
#define MED_NOM_NOD "NOD" /**< Dataset contenant une connectivité nodale de mailles                                                                                                                                                                  */
#define MED_NOM_TYP "TYP" /**< Type de maillage (structuré, non st,)/champ (entier, float,...)/paramètre scalaire                                                                                                                                    */
#define MED_NOM_GTY "GTY" /**< Type de grille                                                                                                                                                                                                        */
#define MED_NOM_CO  "CO"  /**< Valeur d'un champ à une étape de calcul                                                                                                                                                                               */

#define MED_NOM_NXT "NXT" /**< Numéro de pas de temps suivant                                                                                                                                                                                        */
#define MED_NOM_NXI "NXI" /**< Numéro d'itération suivant                                                                                                                                                                                            */
#define MED_NOM_PVT "PVT" /**< Numéro de pas de temps précédent                                                                                                                                                                                      */
#define MED_NOM_PVI "PVI" /**< Numéro d'itération précédent                                                                                                                                                                                          */
#define MED_NOM_CGT "CGT" /**< Un changement a eu lieu entre deux étapes                                                                                                                                                                             */
#define MED_NOM_CGS "CGS" /**< Un changement a eu lieu ds au moins un dataset concernant un même élément.                                                                                                                                            */
#define MED_NOM_SRT "SRT" /**< Ordre de tri des étapes de calcul                                                                                                                                                                                     */

/*Noms internes des types d'entités    */
#define MED_NOM_MAI "MAI"
#define MED_NOM_FAC "FAC"
#define MED_NOM_ARE "ARE"
#define MED_NOM_NOE "NOE"
#define MED_NOM_STR "STR"

/*Noms internes des types géométriques */
#define MED_NOM_PO1 "PO1" /**< Nom interne pour le type géométrique MED_POINT1          */
#define MED_NOM_SE2 "SE2" /**< Nom interne pour le type géométrique MED_SEG2            */
#define MED_NOM_SE3 "SE3" /**< Nom interne pour le type géométrique MED_SEG3            */
#define MED_NOM_SE4 "SE4" /**< Nom interne pour le type géométrique MED_SEG4            */
#define MED_NOM_TR3 "TR3" /**< Nom interne pour le type géométrique MED_TRIA3           */
#define MED_NOM_QU4 "QU4" /**< Nom interne pour le type géométrique MED_QUAD4           */
#define MED_NOM_TR6 "TR6" /**< Nom interne pour le type géométrique MED_TRIA6           */
#define MED_NOM_TR7 "TR7" /**< Nom interne pour le type géométrique MED_TRIA7           */
#define MED_NOM_QU8 "QU8" /**< Nom interne pour le type géométrique MED_QUAD8           */
#define MED_NOM_QU9 "QU9" /**< Nom interne pour le type géométrique MED_QUAD9           */
#define MED_NOM_TE4 "TE4" /**< Nom interne pour le type géométrique MED_TETRA4          */
#define MED_NOM_PY5 "PY5" /**< Nom interne pour le type géométrique MED_PYRA5           */
#define MED_NOM_PE6 "PE6" /**< Nom interne pour le type géométrique MED_PENTA6          */
#define MED_NOM_HE8 "HE8" /**< Nom interne pour le type géométrique MED_HEXA8           */
#define MED_NOM_T10 "T10" /**< Nom interne pour le type géométrique MED_TETRA10         */
#define MED_NOM_O12 "O12" /**< Nom interne pour le type géométrique MED_OCTA12          */
#define MED_NOM_P13 "P13" /**< Nom interne pour le type géométrique MED_PYRA13          */
#define MED_NOM_P15 "P15" /**< Nom interne pour le type géométrique MED_PENTA15         */
#define MED_NOM_P18 "P18" /**< Nom interne pour le type géométrique MED_PENTA18         */
#define MED_NOM_H20 "H20" /**< Nom interne pour le type géométrique MED_HEXA20          */
#define MED_NOM_H27 "H27" /**< Nom interne pour le type géométrique MED_HEXA27          */

#define MED_NOM_POG "POG" /**< Nom interne pour le type géométrique polygone            */
#define MED_NOM_PO2 "PO2" /**< Nom interne pour le type géométrique polygone de degré 2 */
#define MED_NOM_POE "POE" /**< Nom interne pour le type géométrique polyèdres           */

#define MED_NOM_TAI "TAI" /**< Taille du tableau de connectivité pour les polyèdres/gones (med 2.x)*/
#define MED_NOM_TTI "TTI" /**< Taille du tableau d'index de faces pour les polyèdres (med 2.x) */
#define MED_NOM_IFN "IFN" /**< Nom du dataset contenant les indexes de faces en conn. nodale pour les polyèdres (med 2.x) */
#define MED_NOM_IFD "IFD" /**< Nom du dataset contenant les indexes de faces en conn. descendante pour les polyèdres (med 2.x) */
#define MED_NOM_INN "INN" /**< Nom du dataset contenant les indexes de poly{èdres/gones} en conn. descendante pour les polyèdres (med 2.x) */
#define MED_NOM_IND "IND" /**< Nom du dataset contenant les indexes de poly{èdres/gones} en conn. descendante pour les polyèdres (med 2.x) */

#define MED_NOM_LEN "LEN" /**< Liste des entités utilisées                                                                                                       */
#define MED_NOM_LAA "LAA" /**< Nombre d'étapes de calcul pour lesquelles les listes d'entités utilisées sont identiques (Toutes ou 1)                            */
#define MED_NOM_LGC "LGC" /**< Liste des types géométriques utilisés par les entités MED_CELL                                                                    */
#define MED_NOM_LCA "LCA" /**< Nombre d'étapes de calcul pour lesquelles les listes de types géométriques sont identiques pour les entités MED_CELL              */
#define MED_NOM_LGF "LGF" /**< Liste des types géométriques utilisés par les entités MED_DESCENDING_FACE                                                         */
#define MED_NOM_LFA "LFA" /**< Nombre d'étapes de calcul pour lesquelles les listes de types géométriques sont identiques pour les entités MED_DESCENDING_FACE   */
#define MED_NOM_LGE "LGE" /**< Liste des types géométriques utilisés par les entités MED_DESCENDING_EDGE                                                         */
#define MED_NOM_LEA "LEA" /**< Nombre d'étapes de calcul pour lesquelles les listes de types géométriques sont identiques pour les entités MED_DESCENDING_EDGE   */
#define MED_NOM_LGN "LGN" /**< Liste des types géométriques utilisés par les entités MED_NODE                                                                    */
#define MED_NOM_LNA "LNA" /**< Nombre d'étapes de calcul pour lesquelles les listes de types géométriques sont identiques pour les entités MED_NODE              */
#define MED_NOM_LGT "LGT" /**< Liste des types géométriques utilisés par les entités MED_NODE_ELEMENT                                                            */
#define MED_NOM_LTA "LTA" /**< Nombre d'étapes de calcul pour lesquelles les listes de types géométriques sont identiques pour les entités MED_NODE_ELEMENT      */
#define MED_NOM_LGS "LGS" /**< Liste des types géométriques utilisés par les entités MED_STRUCT_ELEMENT                                                          */
#define MED_NOM_LSA "LSA" /**< Nombre d'étapes de calcul pour lesquelles les listes de types géométriques sont identiques pour les entités MED_STRUCT_ELEMENT    */

#define MED_NOM_GEO "GEO" /**< Numéro du type géométrique                                                                                  */
#define MED_NOM_NEO "NEO" /**< Numéro du type géométrique d'un élément de structure                                                        */
#define MED_NOM_ENT "ENT" /**< Numéro du type d'entité                                                                                     */
#define MED_NOM_GED "GED" /**< Numéro du type géométrique distant (équivalences)                                                           */
#define MED_NOM_END "END" /**< Numéro du type d'entité  distant (équivalences)                                                             */
#define MED_NOM_GAU "GAU" /**< Nom d'une localisation de points d'intégration                                                              */
#define MED_NOM_NGA "NGA" /**< Nombre de points d'intégration                                                                              */
#define MED_NOM_PFL "PFL" /**< Nom d'un profil                                                                                             */
#define MED_NOM_PFU "PFU" /**< Indique si un profil est utilisé ds la définition d'un élément de structure                                 */
#define MED_NOM_NDT "NDT" /**< Numéro de date                                                                                              */
#define MED_NOM_RDT "RDT" /**< Numéro de date distant                                                                                      */
#define MED_NOM_PDT "PDT" /**< Valeur de la date                                                                                           */
#define MED_NOM_NOR "NOR" /**< Numéro d'ordre                                                                                              */
#define MED_NOM_ROR "ROR" /**< Numéro d'ordre distant                                                                                      */
#define MED_NOM_LIE "LIE" /**< Nom d'un lien                                                                                               */
#define MED_NOM_DOM "DOM" /**< Numéro de domaine (joints)                                                                                  */
#define MED_NOM_GLB "GLB" /**< Numérotation globale                                                                                        */
#define MED_NOM_INM "INM" /**< Nom de l'interpolation géométrique                                                                          */
#define MED_NOM_NBV "NBV" /**< Nombre de variables utilisées ds une interpolation                                                          */
#define MED_NOM_MDG "MDG" /**< Degré maximum de l'ensemble des polynômes d'une interpolation                                               */
#define MED_NOM_MCF "NCF" /**< Nombre maximum de coefficients des polynômes d'une interpolation                                            */
#define MED_NOM_FCN "FCN" /**< Indique si les points de construction de l'interpolation sont aux noeuds de la maille de référence          */
#define MED_NOM_COE "COE" /**< Nom du dataset contenant les coefficients d'un polynôme                                                     */
#define MED_NOM_POW "POW" /**< Nom du dataset contenant les puissances d'un polynôme                                                       */

/* Nom du DATA GROUP CONTENANT TOUS LES MAILLAGES DU FICHIER HDF */
#define MED_MESH_NAME "ENS_MAA"
#define MED_MESH_GRP "/" MED_MESH_NAME "/"
#define MED_MESH_GRP_SIZE  9

/* Nom du DATA GROUP CONTENANT TOUS LES MAILLAGES SUPPORTS DU FICHIER HDF */
#define MED_MESH_SUPPORT_GRP "/ENS_SUP_MAA/"
#define MED_MESH_SUPPORT_GRP_SIZE 13

/* Nom du DATA GROUP CONTENANT TOUS LES CHAMPS RESULTATS */
#define MED_FIELD_NAME "CHA"
#define MED_FIELD_GRP "/" MED_FIELD_NAME "/"
#define MED_FIELD_GRP_SIZE 5

/* Nom du DATA GROUP CONTENANT TOUS LES MODELES D'ELEMENTS DE STRUCTURE */
#define MED_ELSTRUCT_NAME "STRUCT"
#define MED_ELSTRUCT_GRP "/" MED_ELSTRUCT_NAME "/"
#define MED_ELSTRUCT_GRP_SIZE 8

/* Nom du DATA GROUP CONTENANT TOUTES LES FONCTIONS D'INTERPOLATIONS */
#define MED_INTERPOLATION_NAME "INTERP"
#define MED_INTERPOLATION_GRP "/" MED_INTERPOLATION_NAME "/"
#define MED_INTERPOLATION_GRP_SIZE 8


/* Nom du DATA GROUP CONTENANT LES FONCTIONS D'INTERPOLATIONS UTILISEES PAR LES CHAMPS */
#define MED_CHA_INTERP "/CHA_INTERP/"
#define MED_TAILLE_CHA_INTERP 12

/* Nom du DATA GROUP CONTENANT LES ENTITES ET LES TYPES GEOMETRIQUES ASSOCIES UTILISES */
#define MED_ENTITYTYPE_NAME "ENTITYP"
#define MED_ENTITYTYPE_GRP "/" MED_ENTITYTYPE_NAME "/"
#define MED_ENTITYTYPE_GRP_SIZE 9

/* Nom du DATA GROUP CONTENANT TOUS LES ATTRIBUTS CONSTANTS D'ELEMENTS DE STRUCTURE */
#define MED_CSTATR "/CSTATR/"
#define MED_CSTATR_NOM "CSTATR"
#define MED_TAILLE_CSTATR 8

/* Nom du DATA GROUP CONTENANT TOUS LES ATTRIBUTS VARAIBLES D'ELEMENTS DE STRUCTURE */
#define MED_VARATR "/VARATR/"
#define MED_VARATR_NOM "VARATR"
#define MED_TAILLE_VARATR 8

/* Nom du DATA GROUP CONTENANT LES TRANSFORMATIONS GEOMETRIQUES APPLIQUEES AUX COORDONNEES */
#define MED_COOTRF "/COOTRF/"
#define MED_COOTRF_NOM "COOTRF"
#define MED_TAILLE_COOTRF 8

/* Nom du data group point de montage */
#define MED_MNT "/MNT/"
#define MED_TAILLE_MNT 5

/* Nom du data group ou ranger les familles */
#define MED_FAMILY_NAME "FAS"
#define MED_FAMILY_GRP "/" MED_FAMILY_NAME "/"
#define MED_FAMILY_GRP_SIZE 5

#define FAMILLE_ZERO "FAMILLE_ZERO"
#define MED_FAS_ZERO "/FAMILLE_ZERO/"
#define MED_FAS_ZERO_NOM "FAMILLE_ZERO"
#define MED_TAILLE_FAS_ZERO 14
#define MED_FAS_NOEUD "/NOEUD/"
#define MED_FAS_NOEUD_NOM "NOEUD"
#define MED_FAS_ELEME "/ELEME/"
#define MED_FAS_ELEME_NOM "ELEME"
#define MED_TAILLE_FAS_ENTITE 7

/* Nom du data group ou ranger les equivalences */
#define MED_EQUIVALENCE_NAME "EQS"
#define MED_EQUIVALENCE_GRP "/" MED_EQUIVALENCE_NAME "/"
#define MED_EQUIVALENCE_GRP_SIZE 5

/* Nom du data group contenant les profils */
#define MED_PROFILE_NAME "PROFILS"
#define MED_PROFILE_GRP "/" MED_PROFILE_NAME "/"
#define MED_PROFILE_GRP_SIZE 9

/* Nom du data group contenant la localisation des points de GAUSS */
#define MED_LOCALIZATION_NAME "GAUSS"
#define MED_LOCALIZATION_GRP "/" MED_LOCALIZATION_NAME "/"
#define MED_LOCALIZATION_GRP_SIZE 7

/*  Nom du data group contenant  les valeurs numeriques scalaires */
#define MED_NUMERICAL_DATA_NAME  "NUM_DATA"
#define MED_NUMERICAL_DATA_GRP "/" MED_NUMERICAL_DATA_NAME "/"
#define MED_NUMERICAL_DATA_GRP_SIZE 10

/* Nom du data group contenant les liens */
#define MED_LIENS "/LIENS/"
#define MED_TAILLE_LIENS 7

/* Nom du data group contenant les joints */
#define MED_JOINT_NAME "JNT"
#define MED_JOINT_GRP "/" MED_JOINT_NAME "/"
#define MED_JOINT_GRP_SIZE 5

/* Nom du data group contenant la version du fichier */
#define MED_INFOS "/INFOS_GENERALES/"

/*Pour eviter le bug solaris*/
#ifndef __APPLE__
#include <malloc.h>
#endif

/* Interface des routines du composant tools */
#include <med_misc.h>
#include <med_hdfi.h>
#include <med_utils.h>

#endif /* MED_OUTILS_H */
