/*
  This file is part of libkronos.

  Libkronos is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Libkronos is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with Libkronos.  If not, see <http://www.gnu.org/licenses/>.

  Contributors:
    - Johan Saji <innovatorjohan@gmail.com>

*/

#ifndef KRONOS_ERROR_H
#define KRONOS_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

  typedef enum{
    KRONOS_SUCCESS = 0,
    KRONOS_FAILED
  } KRONOS_RET;
  

#ifdef __cplusplus
}
#endif


#endif //KRONOS_ERROR_H
