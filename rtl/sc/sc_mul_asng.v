`include "fir_coeffs.vh"

module sc_mul_asng #(
    parameter SN_LEN = 4096,
    parameter W      = 12
) (
    input  wire             clk,
    input  wire             rst,
    input  wire             start,
    input  wire [15:0]      bound_coe,
    input  wire [15:0]      bound_data,
    input  wire [W-1:0]     seed_data,
    input  wire [3:0]       shift_data,
    output reg              done,
    output reg  [31:0]      product
);
  localparam S_IDLE = 2'd0;
  localparam S_RUN  = 2'd1;

  reg [1:0]   state;
  reg [11:0]  idx;
  reg [W-1:0] up_cnt;
  reg [W-1:0] lfsr_d;
  reg [31:0]  acc;

  wire [W-1:0] next_d = {lfsr_d[W-2:0], lfsr_d[0] ^ lfsr_d[6] ^ lfsr_d[8] ^ lfsr_d[11]};
  wire [W-1:0] rot_d;
  wire [W-1:0] rnd_d;
  wire         bit_coe, bit_data;

  wbg_sng_bit #(.W(W)) u_wbg (.counter(up_cnt), .bound(bound_coe[W-1:0]), .sn_bit(bit_coe));

  lfsr12_rotate #(.W(W)) u_rd (.in_state(next_d), .shift_amt(shift_data), .out_state(rot_d));
  lfsr12_dec #(.W(W)) u_dd (.bits(rot_d), .value(rnd_d));
  assign bit_data = (rnd_d < bound_data[W-1:0]);

  always @(posedge clk) begin
    if (rst) begin
      state <= S_IDLE;
      done <= 0;
      product <= 0;
      idx <= 0;
      acc <= 0;
      up_cnt <= 0;
      lfsr_d <= 0;
    end else
      case (state)
        S_IDLE: begin
          done <= 0;
          if (start) begin
            up_cnt <= 0;
            lfsr_d <= seed_data;
            idx <= 0;
            acc <= 0;
            state <= S_RUN;
          end
        end
        S_RUN: begin
          up_cnt <= up_cnt + 1;
          lfsr_d <= next_d;
          acc <= acc + (bit_coe & bit_data);
          if (idx == SN_LEN - 1) begin
            product <= acc + (bit_coe & bit_data);
            done <= 1;
            state <= S_IDLE;
          end else
            idx <= idx + 1;
        end
      endcase
  end
endmodule
