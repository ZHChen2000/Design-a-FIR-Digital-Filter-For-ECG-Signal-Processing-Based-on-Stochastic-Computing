module halton_sample #(
    parameter W = 12
) (
    input  wire [15:0]      index,
    output reg  [W-1:0]     sample
);
  integer t;
  reg [31:0] inv;
  reg [31:0] d;

  always @* begin
    inv = 0;
    d = 2048;
    t = index;
    while (t > 0) begin
      inv = inv + (t & 1) * d;
      t = t >> 1;
      d = d >> 1;
    end
    if (inv > 4095)
      sample = 4095;
    else
      sample = inv[W-1:0];
  end
endmodule
