module wbg_sng_bit #(
    parameter W = 12
) (
    input  wire [W-1:0]     counter,
    input  wire [W-1:0]     bound,
    output wire             sn_bit
);
  wire [W-1:0] rn = counter;
  wire [W-1:0] bn = bound;

  wire w0  = rn[0];
  wire w1  = (~rn[0]) & rn[1];
  wire w2  = (~rn[0]) & (~rn[1]) & rn[2];
  wire w3  = (~rn[0]) & (~rn[1]) & (~rn[2]) & rn[3];
  wire w4  = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & rn[4];
  wire w5  = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & (~rn[4]) & rn[5];
  wire w6  = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & (~rn[4]) & (~rn[5]) & rn[6];
  wire w7  = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & (~rn[4]) & (~rn[5]) & (~rn[6]) & rn[7];
  wire w8  = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & (~rn[4]) & (~rn[5]) & (~rn[6]) & (~rn[7]) & rn[8];
  wire w9  = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & (~rn[4]) & (~rn[5]) & (~rn[6]) & (~rn[7]) & (~rn[8]) & rn[9];
  wire w10 = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & (~rn[4]) & (~rn[5]) & (~rn[6]) & (~rn[7]) & (~rn[8]) & (~rn[9]) & rn[10];
  wire w11 = (~rn[0]) & (~rn[1]) & (~rn[2]) & (~rn[3]) & (~rn[4]) & (~rn[5]) & (~rn[6]) & (~rn[7]) & (~rn[8]) & (~rn[9]) & (~rn[10]) & rn[11];

  assign sn_bit = (w0 & bn[11]) | (w1 & bn[10]) | (w2 & bn[9]) | (w3 & bn[8]) |
                  (w4 & bn[7]) | (w5 & bn[6]) | (w6 & bn[5]) | (w7 & bn[4]) |
                  (w8 & bn[3]) | (w9 & bn[2]) | (w10 & bn[1]) | (w11 & bn[0]);
endmodule
