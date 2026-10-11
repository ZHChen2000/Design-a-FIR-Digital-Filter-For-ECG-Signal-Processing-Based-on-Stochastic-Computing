module sc_and_stream #(
    parameter WIDTH = 4096
) (
    input  wire [WIDTH-1:0] a,
    input  wire [WIDTH-1:0] b,
    output wire [WIDTH-1:0] y
);
  assign y = a & b;
endmodule
