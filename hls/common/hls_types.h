#ifndef HLS_TYPES_H
#define HLS_TYPES_H

#ifdef __SYNTHESIS__
#include <ap_int.h>
#else
#include <cstdint>
template <int W> using ap_int = int;
template <int W> using ap_uint = unsigned int;
#endif

#endif
