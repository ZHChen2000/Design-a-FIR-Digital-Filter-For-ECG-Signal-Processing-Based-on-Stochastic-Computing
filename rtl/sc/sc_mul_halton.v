`include "fir_coeffs.vh"

module sc_mul_halton #(
    parameter SN_LEN = 4096,
    parameter W      = 12
) (
    input  wire             clk,
    input  wire             rst,
    input  wire             start,
    input  wire [15:0]      bound_a,
    input  wire [15:0]      bound_b,
    input  wire [W-1:0]     seed_b,
    input  wire [3:0]       shift_b,
    output reg              done,
    output reg  [31:0]      product
);
  localparam S_IDLE = 2'd0;
  localparam S_RUN  = 2'd1;

  reg [1:0]   state;
  reg [11:0]  idx;
  reg [W-1:0] lfsr_b;
  reg [31:0]  acc;

  wire [W-1:0] halton_r;
  wire [W-1:0] next_b = {lfsr_b[W-2:0], lfsr_b[0] ^ lfsr_b[6] ^ lfsr_b[8] ^ lfsr_b[11]};
  wire [W-1:0] rot_b, rnd_b;
  wire         bit_a, bit_b;

  halton_sample #(.W(W)) u_h (.index(idx), .sample(halton_r));
  assign bit_a = (halton_r < bound_a[W-1:0]);

  lfsr12_rotate #(.W(W)) u_rb (.in_state(next_b), .shift_amt(shift_b), .out_state(rot_b));
  lfsr12_dec #(.W(W)) u_db (.bits(rot_b), .value(rnd_b));
  assign bit_b = (rnd_b < bound_b[W-1:0]);

  always @(posedge clk) begin
    if (rst) begin
      state <= S_IDLE;
      done <= 0;
      product <= 0;
      idx <= 0;
      acc <= 0;
      lfsr_b <= 0;
    end else
      case (state)
        S_IDLE: begin
          done <= 0;
          if (start) begin
            lfsr_b <= seed_b;
            idx <= 0;
            acc <= 0;
            state <= S_RUN;
          end
        end
        S_RUN: begin
          lfsr_b <= next_b;
          acc <= acc + (bit_a & bit_b);
          if (idx == SN_LEN - 1) begin
            product <= acc + (bit_a & bit_b);
            done <= 1;
            state <= S_IDLE;
          end else
            idx <= idx + 1;
        end
      endcase
  end
endmodule
