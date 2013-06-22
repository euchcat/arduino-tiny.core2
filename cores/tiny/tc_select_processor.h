/*==============================================================================

  Copyright 2012 Rowdy Dog Software.

  This file is part of Arduino-Tiny.

  Arduino-Tiny is free software: you can redistribute it and/or modify it 
  under the terms of the GNU Lesser General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.

  Arduino-Tiny is distributed in the hope that it will be useful, but 
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License 
  along with Arduino-Tiny.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/

#ifndef tc_select_processor_h
#define tc_select_processor_h


/*=============================================================================
  Build options specific to the ATtiny13 processor
=============================================================================*/

#if defined( __AVR_ATtiny13__ ) || defined( __AVR_ATtiny13A__ )
#define __AVR_ATtiny13X__
#endif


/*=============================================================================
  Build options specific to the ATtiny84 family of processors
=============================================================================*/

#if defined( __AVR_ATtiny24__ ) || defined( __AVR_ATtiny44__ ) || defined( __AVR_ATtiny84__ )
#define __AVR_ATtinyX4__
#endif


/*=============================================================================
  Build options specific to the ATtiny85 processor
=============================================================================*/

#if defined( __AVR_ATtiny25__ ) || defined( __AVR_ATtiny45__ ) || defined( __AVR_ATtiny85__ )
#define __AVR_ATtinyX5__
#endif


/*=============================================================================
  Build options specific to the ATtiny861 processor
=============================================================================*/

#if defined( __AVR_ATtiny261__ ) || defined( __AVR_ATtiny461__ ) || defined( __AVR_ATtiny861__ )
#define __AVR_ATtinyX61__
#endif


#endif // tc_select_processor_h
