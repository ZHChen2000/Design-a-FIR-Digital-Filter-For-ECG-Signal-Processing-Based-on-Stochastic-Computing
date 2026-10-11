module d_function (
    input  wire [3:0] din,
    output wire [3:0] dout
);
  reg [3:0] lut [0:15];
  initial begin
    lut[0]  = 4'h4;
    lut[1]  = 4'h5;
    lut[2]  = 4'h6;
    lut[3]  = 4'hB;
    lut[4]  = 4'hE;
    lut[5]  = 4'h2;
    lut[6]  = 4'h7;
    lut[7]  = 4'hF;
    lut[8]  = 4'h9;
    lut[9]  = 4'hD;
    lut[10] = 4'h8;
    lut[11] = 4'h0;
    lut[12] = 4'h3;
    lut[13] = 4'h1;
    lut[14] = 4'hC;
    lut[15] = 4'hA;
  end
  assign dout = lut[din];
endmodule
