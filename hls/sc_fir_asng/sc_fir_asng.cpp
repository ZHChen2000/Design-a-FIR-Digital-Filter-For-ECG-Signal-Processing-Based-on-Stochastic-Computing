#include "../common/fir_coeffs.h"
#include "../common/hls_types.h"

static ap_int<32> sc_mul_cape(ap_int<16> a, ap_int<16> b, int sn_len) {
  ap_int<32> k = ((ap_int<32>)b * sn_len) / 4096;
  if (k < 0)
    k = 0;
  if (k > sn_len)
    k = sn_len;
  ap_int<32> pa = (ap_int<32>)a * sn_len;
  return (pa / 4096) * k / sn_len;
}

extern "C" void sc_fir_asng(
    ap_int<16> x_in,
    ap_int<16> delay_line[FIR_TAPS],
    int sn_len,
    ap_int<32> *y_out) {
#pragma HLS INTERFACE s_axilite port=x_in bundle=CTRL
#pragma HLS INTERFACE s_axilite port=sn_len bundle=CTRL
#pragma HLS INTERFACE s_axilite port=y_out bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
#pragma HLS ARRAY_PARTITION variable=delay_line complete

  ap_int<48> acc = 0;
  for (int i = 0; i < FIR_TAPS; ++i)
    acc += sc_mul_cape(delay_line[i], (ap_int<16>)FIR_COE_8BIT[i], sn_len);

  for (int i = FIR_TAPS - 1; i > 0; --i)
    delay_line[i] = delay_line[i - 1];
  delay_line[0] = x_in;

  *y_out = (ap_int<32>)acc;
}
