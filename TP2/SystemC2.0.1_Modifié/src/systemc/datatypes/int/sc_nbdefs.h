/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  sc_nbdefs.h -- Top level header file for arbitrary precision signed/unsigned
                 arithmetic. This file defines all the constants needed.

  Original Author: Ali Dasdan, Synopsys, Inc.
  
 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#ifndef SC_NBDEFS_H
#define SC_NBDEFS_H


#include "systemc/kernel/sc_cmnhdr.h"

#include <limits.h>

#include "systemc/utils/sc_iostream.h"
#include "systemc/kernel/sc_constants.h"   // For SC_MAX_NBITS
#include "systemc/utils/sc_string.h"      // For sc_numrep


#if defined( __SUNPRO_CC ) || defined( _MSC_VER ) || 1
#define SC_DT_MIXED_COMMA_OPERATORS
#endif


namespace sc_dt
{

// Sign of a number:
#define SC_NEG       -1     // Negative number
#define SC_ZERO      0      // Zero
#define SC_POS       1      // Positive number
#define SC_NOSIGN    2      // Uninitialized sc_signed number

typedef unsigned char uchar;

// A small_type number is at least a char. Defining an int is probably
// better for alignment.
typedef int small_type;

// Attributes of a byte.
#define BITS_PER_BYTE   8
#define BYTE_RADIX      256
#define BYTE_MASK       255

// LOG2_BITS_PER_BYTE = log2(BITS_PER_BYTE), assuming that
// BITS_PER_BYTE is a power of 2.
#define LOG2_BITS_PER_BYTE 3

// Attributes of the unsigned long. These definitions are used mainly in
// the functions that are aware of the internal representation of
// digits, e.g., get/set_packed_rep().
#define BYTES_PER_DIGIT_TYPE  4
#define BITS_PER_DIGIT_TYPE   32

// Attributes of a digit, i.e., unsigned long less the overflow bits.
#define BYTES_PER_DIGIT 4
#define BITS_PER_DIGIT  30
#define DIGIT_RADIX     (1ul << BITS_PER_DIGIT)
#define DIGIT_MASK      (DIGIT_RADIX - 1)
// Make sure that BYTES_PER_DIGIT = ceil(BITS_PER_DIGIT / BITS_PER_BYTE).

// Similar attributes for the half of a digit. Note that
// HALF_DIGIT_RADIX is equal to the square root of DIGIT_RADIX. These
// definitions are used mainly in the multiplication routines.
#define BITS_PER_HALF_DIGIT (BITS_PER_DIGIT / 2)
#define HALF_DIGIT_RADIX    (1ul << BITS_PER_HALF_DIGIT)
#define HALF_DIGIT_MASK     (HALF_DIGIT_RADIX - 1)

// DIV_CEIL2(x, y) = ceil(x / y). x and y are positive numbers.
#define DIV_CEIL2(x, y) (((x) - 1) / (y) + 1)

// DIV_CEIL(x) = ceil(x / BITS_PER_DIGIT) = the number of digits to
// store x bits. x is a positive number.
#define DIV_CEIL(x) DIV_CEIL2(x, BITS_PER_DIGIT)

#ifdef SC_MAX_NBITS
extern const int MAX_NDIGITS;
// Consider a number with x bits another with y bits. The maximum
// number of bits happens when we multiply them. The result will have
// (x + y) bits. Assume that x + y <= SC_MAX_NBITS. Then, DIV_CEIL(x) +
// DIV_CEIL(y) <= DIV_CEIL(SC_MAX_NBITS) + 2. This is the reason for +2
// above. With this change, MAX_NDIGITS must be enough to hold the
// result of any operation.
#endif

// Support for the long long type. This type is not in the standard
// but is usually supported by compilers.
#ifndef WIN32
typedef long long          int64;
typedef unsigned long long uint64;
extern const uint64        UINT64_ZERO;
extern const uint64        UINT64_ONE;
extern const uint64        UINT64_32ONES;
#else
typedef __int64            int64;
typedef unsigned __int64   uint64;
extern const uint64        UINT64_ZERO;
extern const uint64        UINT64_ONE;
extern const uint64        UINT64_32ONES;
#endif

// Bits per ...
// will be deleted in the future. Use numeric_limits instead
#define BITS_PER_CHAR    8
#define BITS_PER_INT    32
#define BITS_PER_LONG   32
#define BITS_PER_INT64  64
#define BITS_PER_UINT   32
#define BITS_PER_ULONG  32
#define BITS_PER_UINT64 64

// Digits per ...
#define DIGITS_PER_CHAR   1
#define DIGITS_PER_INT    2
#define DIGITS_PER_LONG   2
#define DIGITS_PER_INT64  3
#define DIGITS_PER_UINT   2
#define DIGITS_PER_ULONG  2
#define DIGITS_PER_UINT64 3

// Above, BITS_PER_X is mainly used for sc_signed, and BITS_PER_UX is
// mainly used for sc_unsigned.

#if defined( WIN32 ) || defined( __SUNPRO_CC ) || defined( __HP_aCC )
typedef unsigned long fmtflags;
#else
typedef ios::fmtflags fmtflags;
#endif

extern const small_type NB_DEFAULT_BASE ;

// For sc_int code:
#define LLWIDTH  BITS_PER_INT64
#define INTWIDTH BITS_PER_INT

#ifndef _32BIT_

typedef int64 int_type;
typedef uint64 uint_type;
#define SC_INTWIDTH 64
extern const uint64 UINT_ZERO;
extern const uint64 UINT_ONE;

#else

typedef int int_type;
typedef unsigned int uint_type;
#define SC_INTWIDTH 32
extern const unsigned int UINT_ZERO;
extern const unsigned int UINT_ONE;

#endif


#if defined( _MSC_VER )
// VC++6 bug
ostream& operator << ( ostream&, int64 );
ostream& operator << ( ostream&, uint64 );
#endif

} // namespace sc_dt


#if defined( _MSC_VER )

inline
ostream&
operator << ( ostream& os, sc_dt::int64 a )
{
    sc_dt::operator << ( os, a );
    return os;
}

inline
ostream&
operator << ( ostream& os, sc_dt::uint64 a )
{
    sc_dt::operator << ( os, a );
    return os;
}

#endif


#endif
