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
#ifndef MED_LOGICAL_OP_HXX
#define MED_LOGICAL_OP_HXX

/* Pour tester la présence d'une entité */
template <typename T> inline int MEDtestBits(const T & int_type, const int offset) {
  T mask = 1 << offset;
  return(int_type & mask);
}

/* Counting bits set, Brian Kernighan's way */
template <typename T> inline T MEDnSetBits(const T & int_type) {

  /*unsigned*/
  T v=int_type;   // count the number of bits set in v
  /*unsigned*/
  T c;            // c accumulates the total bits set in v
  for (c = 0; v; c++)
    {
      v &= v - 1; // clear the least significant bit set
    }
  return(c);
}

/* setBit() returns an integer with the bit at 'offset' set to 1. */
 template <typename T> inline T& MEDsetBits(T& int_type, const int offset) {
  T mask = 1 << offset;
  int_type = int_type | mask;
  return(int_type);
}

#endif
