module fir_direct_bin #(
    parameter TAPS = 31,
    parameter DATA_W = 16,
    parameter COE_W = 32,
    parameter ACC_W = 48
) (
    input  wire                   clk,
    input  wire                   rst,
    input  wire signed [DATA_W-1:0] x_in,
    input  wire                   valid_in,
    output reg  signed [DATA_W-1:0] y_out,
    output reg                    valid_out
);
  reg signed [DATA_W-1:0] delay [0:TAPS-1];
  reg signed [COE_W-1:0] coe [0:TAPS-1];

  initial begin
    coe[0]  = 849;   coe[1]  = -701;  coe[2]  = -2758; coe[3]  = -3860;
    coe[4]  = -1168; coe[5]  = 6350;  coe[6]  = 14087; coe[7]  = 12595;
    coe[8]  = -4649; coe[9]  = -31377; coe[10] = -46117; coe[11] = -23101;
    coe[12] = 48447; coe[13] = 150680; coe[14] = 241671; coe[15] = 278103;
    coe[16] = 241671; coe[17] = 150680; coe[18] = 48447; coe[19] = -23101;
    coe[20] = -46117; coe[21] = -31377; coe[22] = -4649; coe[23] = 12595;
    coe[24] = 14087; coe[25] = 6350;  coe[26] = -1168; coe[27] = -3860;
    coe[28] = -2758; coe[29] = -701;  coe[30] = 849;
  end

  integer i;
  reg signed [ACC_W-1:0] acc;

  always @(posedge clk) begin
    valid_out <= valid_in;
    if (rst) begin
      y_out <= 0;
      for (i = 0; i < TAPS; i = i + 1)
        delay[i] <= 0;
    end else if (valid_in) begin
      for (i = TAPS - 1; i > 0; i = i - 1)
        delay[i] <= delay[i - 1];
      delay[0] <= x_in;
      acc = 0;
      for (i = 0; i < TAPS; i = i + 1)
        acc = acc + delay[i] * coe[i];
      y_out <= acc >>> 8;
    end
  end
endmodule
