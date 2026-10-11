module lfsr12_dec #(
    parameter W = 12
) (
    input  wire [W-1:0] bits,
    output wire [W-1:0] value
);
  wire [W-1:0] w0  = bits[0];
  wire [W-1:0] w1  = bits[1] << 1;
  wire [W-1:0] w2  = bits[2] << 2;
  wire [W-1:0] w3  = bits[3] << 3;
  wire [W-1:0] w4  = bits[4] << 4;
  wire [W-1:0] w5  = bits[5] << 5;
  wire [W-1:0] w6  = bits[6] << 6;
  wire [W-1:0] w7  = bits[7] << 7;
  wire [W-1:0] w8  = bits[8] << 8;
  wire [W-1:0] w9  = bits[9] << 9;
  wire [W-1:0] w10 = bits[10] << 10;
  wire [W-1:0] w11 = bits[11] << 11;
  assign value = w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7 + w8 + w9 + w10 + w11;
endmodule
