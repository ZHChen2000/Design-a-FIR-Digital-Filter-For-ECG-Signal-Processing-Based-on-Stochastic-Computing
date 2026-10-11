#include "../common/fir_coeffs.h"
#include "../common/hls_types.h"

extern "C" void binary_fir(
    ap_int<16> x_in,
    ap_int<16> delay_line[FIR_TAPS],
    ap_int<32> *y_out) {
#pragma HLS INTERFACE s_axilite port=x_in bundle=CTRL
#pragma HLS INTERFACE s_axilite port=y_out bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
#pragma HLS ARRAY_PARTITION variable=delay_line complete

  for (int i = FIR_TAPS - 1; i > 0; --i)
    delay_line[i] = delay_line[i - 1];
  delay_line[0] = x_in;

  ap_int<48> acc = 0;
  for (int i = 0; i < FIR_TAPS; ++i)
    acc += delay_line[i] * FIR_COE_TRAD[i];
  *y_out = acc;
}
