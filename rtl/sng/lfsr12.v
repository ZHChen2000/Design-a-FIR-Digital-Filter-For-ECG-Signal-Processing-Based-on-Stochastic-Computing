module lfsr12 #(
    parameter W = 12
) (
    input  wire             clk,
    input  wire             rst,
    input  wire             en,
    input  wire [W-1:0]     seed_load,
    input  wire             load,
    output wire [W-1:0]     state
);
  reg [W-1:0] s;
  wire fb = s[0] ^ s[6] ^ s[8] ^ s[11];

  always @(posedge clk) begin
    if (rst)
      s <= {12{1'b0}};
    else if (load)
      s <= seed_load;
    else if (en)
      s <= {s[10:0], fb};
  end

  assign state = s;
endmodule
