#include "../common/fir_coeffs.h"
#include "../common/hls_types.h"

static ap_int<32> sc_mul_shift(ap_int<16> a, ap_int<16> b, int shift, int sn_len) {
  ap_int<32> pa = (ap_int<32>)a * sn_len;
  ap_int<32> pb = (ap_int<32>)b * sn_len;
  ap_int<32> corr = (pa / 4096) * (pb / 4096);
  return corr / sn_len;
}

extern "C" void sc_fir_shared(
    ap_int<16> x_in,
    ap_int<16> delay_line[FIR_TAPS],
    int base_shift,
    int sn_len,
    ap_int<32> *y_out) {
#pragma HLS INTERFACE s_axilite port=x_in bundle=CTRL
#pragma HLS INTERFACE s_axilite port=base_shift bundle=CTRL
#pragma HLS INTERFACE s_axilite port=sn_len bundle=CTRL
#pragma HLS INTERFACE s_axilite port=y_out bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
#pragma HLS ARRAY_PARTITION variable=delay_line complete

  ap_int<48> acc = 0;
  for (int i = 0; i < FIR_TAPS; ++i)
    acc += sc_mul_shift(delay_line[i], (ap_int<16>)FIR_COE_8BIT[i], base_shift + i, sn_len);

  for (int i = FIR_TAPS - 1; i > 0; --i)
    delay_line[i] = delay_line[i - 1];
  delay_line[0] = x_in;

  *y_out = (ap_int<32>)acc;
}
