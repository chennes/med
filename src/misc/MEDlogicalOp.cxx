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
#include "MEDlogicalOp.hxx"

#include <med_config.h>
#include <med_outils.h>

// using namespace std;
extern "C" {
  /*misc not proto*/
#include <stdint.h>
#include "med.h"
}

// #include <cstdint>

using namespace std;

extern "C"  int        _MEDtest8bits(uint8_t int_type,int offset) {
  return MEDtestBits(int_type,offset);
};

extern "C"  void      _MEDset8bits(uint8_t * const int_type,int offset) {
  MEDsetBits(*int_type,offset);
};

extern "C"  uint8_t    _MEDnSet8bits(uint8_t int_type) {
  return MEDnSetBits(int_type);
};


extern "C"  int        _MEDtest32bits(uint32_t int_type,int offset) {
  return MEDtestBits(int_type,offset);
};

extern "C"  void      _MEDset32bits(uint32_t * const int_type,int offset) {
  MEDsetBits(*int_type,offset);
};

extern "C"  uint32_t    _MEDnSet32bits(uint32_t int_type) {
  return MEDnSetBits(int_type);
};
