`include "../common/fir_coeffs.vh"

module sc_fir_wbg #(
    parameter SN_LEN = 4096,
    parameter TAPS   = 31,
    parameter W      = 12
) (
    input  wire               clk,
    input  wire               rst,
    input  wire               start,
    input  wire signed [15:0] x_in,
    output reg                done,
    output reg signed [31:0]  y_out
);
  localparam SEED_COE  = 12'h001;
  localparam SEED_DATA = 12'h009;

  localparam ST_IDLE = 3'd0;
  localparam ST_BIT  = 3'd1;
  localparam ST_DONE = 3'd2;

  reg [2:0]             state;
  reg [4:0]             tap;
  reg [11:0]            idx;
  reg [W-1:0]           lfsr_c, lfsr_d;
  reg [SN_LEN-1:0]      acc_stream;
  reg [31:0]            pop_count;
  reg signed [15:0]     delay [0:TAPS-1];

  wire [W-1:0] next_c = {lfsr_c[W-2:0], lfsr_c[0] ^ lfsr_c[6] ^ lfsr_c[8] ^ lfsr_c[11]};
  wire [W-1:0] next_d = {lfsr_d[W-2:0], lfsr_d[0] ^ lfsr_d[6] ^ lfsr_d[8] ^ lfsr_d[11]};
  wire [W-1:0] rot_c, rot_d, rnd_c, rnd_d;
  wire         bit_c, bit_d, mul_bit, merged;
  wire         old_bit;

  lfsr12_rotate #(.W(W)) u_rc (.in_state(next_c), .shift_amt(4'd0), .out_state(rot_c));
  lfsr12_rotate #(.W(W)) u_rd (.in_state(next_d), .shift_amt(4'd0), .out_state(rot_d));
  lfsr12_dec #(.W(W)) u_dc (.bits(rot_c), .value(rnd_c));
  lfsr12_dec #(.W(W)) u_dd (.bits(rot_d), .value(rnd_d));

  assign bit_c = (rnd_c < fir_coe_8bit(tap));
  assign bit_d = (rnd_d < delay[tap]);
  assign mul_bit = bit_c & bit_d;
  assign old_bit = acc_stream[idx];

  sc_add_wbg_merge #(.W(W)) u_add (
      .stream_idx(idx),
      .bit_a(old_bit),
      .bit_b(mul_bit),
      .bit_out(merged)
  );

  integer j;

  always @(posedge clk) begin
    if (rst) begin
      state <= ST_IDLE;
      done <= 0;
      tap <= 0;
      idx <= 0;
      pop_count <= 0;
      acc_stream <= 0;
      lfsr_c <= SEED_COE;
      lfsr_d <= SEED_DATA;
      y_out <= 0;
      for (j = 0; j < TAPS; j = j + 1)
        delay[j] <= 0;
    end else
      case (state)
        ST_IDLE: begin
          done <= 0;
          if (start) begin
            tap <= 0;
            idx <= 0;
            pop_count <= 0;
            acc_stream <= 0;
            lfsr_c <= SEED_COE;
            lfsr_d <= SEED_DATA;
            state <= ST_BIT;
          end
        end
        ST_BIT: begin
          lfsr_c <= next_c;
          lfsr_d <= next_d;
          pop_count <= pop_count + merged - old_bit;
          acc_stream[idx] <= merged;
          if (idx == SN_LEN - 1) begin
            idx <= 0;
            lfsr_c <= SEED_COE;
            lfsr_d <= SEED_DATA;
            if (tap == TAPS - 1) begin
              for (j = TAPS - 1; j > 0; j = j - 1)
                delay[j] <= delay[j - 1];
              delay[0] <= x_in;
              y_out <= pop_count + merged - old_bit;
              done <= 1;
              state <= ST_IDLE;
            end else begin
              tap <= tap + 1;
              state <= ST_BIT;
            end
          end else
            idx <= idx + 1;
        end
        default: state <= ST_IDLE;
      endcase
  end
endmodule
