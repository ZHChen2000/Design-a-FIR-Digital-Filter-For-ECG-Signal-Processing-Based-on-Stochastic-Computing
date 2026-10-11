`include "../common/fir_coeffs.vh"

module sc_fir_shared #(
    parameter SN_LEN = 4096,
    parameter TAPS   = 31,
    parameter W      = 12
) (
    input  wire               clk,
    input  wire               rst,
    input  wire               start,
    input  wire [3:0]         base_shift,
    input  wire signed [15:0] x_in,
    output reg                done,
    output reg signed [31:0]  y_out
);
  localparam SEED_COE  = 12'h55D;
  localparam SEED_DATA = 12'd32;

  localparam ST_IDLE = 2'd0;
  localparam ST_MUL  = 2'd1;

  reg [1:0]             state;
  reg [4:0]             tap;
  reg signed [31:0]     acc_fir;
  reg signed [15:0]     delay [0:TAPS-1];
  reg                   mul_start;
  wire                  mul_done;
  wire [31:0]           mul_product;
  wire [3:0]            coe_shift = base_shift + tap[3:0];

  sc_mul_comp #(.SN_LEN(SN_LEN), .W(W)) u_mul (
      .clk(clk),
      .rst(rst),
      .start(mul_start),
      .bound_a(fir_coe_8bit(tap)),
      .shift_a(coe_shift),
      .seed_a(SEED_COE),
      .bound_b(delay[tap]),
      .shift_b(4'd0),
      .seed_b(SEED_DATA),
      .done(mul_done),
      .product(mul_product)
  );

  integer j;

  always @(posedge clk) begin
    if (rst) begin
      state <= ST_IDLE;
      done <= 0;
      tap <= 0;
      acc_fir <= 0;
      mul_start <= 0;
      y_out <= 0;
      for (j = 0; j < TAPS; j = j + 1)
        delay[j] <= 0;
    end else
      case (state)
        ST_IDLE: begin
          done <= 0;
          if (start) begin
            acc_fir <= 0;
            tap <= 0;
            mul_start <= 1;
            state <= ST_MUL;
          end
        end
        ST_MUL: begin
          mul_start <= 0;
          if (mul_done) begin
            acc_fir <= acc_fir + mul_product;
            if (tap == TAPS - 1) begin
              for (j = TAPS - 1; j > 0; j = j - 1)
                delay[j] <= delay[j - 1];
              delay[0] <= x_in;
              y_out <= acc_fir + mul_product;
              done <= 1;
              state <= ST_IDLE;
            end else begin
              tap <= tap + 1;
              mul_start <= 1;
            end
          end
        end
        default: state <= ST_IDLE;
      endcase
  end
endmodule
