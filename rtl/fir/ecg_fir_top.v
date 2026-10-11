`include "../common/fir_coeffs.vh"

module ecg_fir_top #(
    parameter SN_LEN = 4096,
    parameter TAPS   = 31
) (
    input  wire               clk,
    input  wire               rst,
    input  wire [2:0]         mode,
    input  wire               start,
    input  wire [3:0]         base_shift,
    input  wire signed [15:0] x_in,
    input  wire               valid_in,
    output reg                done,
    output reg signed [31:0]  y_out,
    output wire               valid_out
);
  localparam MODE_BIN    = 3'd0;
  localparam MODE_INDEP  = 3'd1;
  localparam MODE_SHARED = 3'd2;
  localparam MODE_ASNG   = 3'd3;
  localparam MODE_LD     = 3'd4;
  localparam MODE_WBG    = 3'd5;
  localparam MODE_D      = 3'd6;

  wire signed [15:0] bin_y16;
  wire               bin_valid;

  wire done_i, done_s, done_a, done_l, done_w, done_d;
  wire signed [31:0] y_i, y_s, y_a, y_l, y_w, y_d;

  fir_direct_bin #(.TAPS(TAPS)) u_bin (
      .clk(clk),
      .rst(rst),
      .x_in(x_in),
      .valid_in(valid_in && (mode == MODE_BIN)),
      .y_out(bin_y16),
      .valid_out(bin_valid)
  );

  sc_fir_indep #(.SN_LEN(SN_LEN), .TAPS(TAPS)) u_indep (
      .clk(clk), .rst(rst), .start(start && (mode == MODE_INDEP)),
      .x_in(x_in), .done(done_i), .y_out(y_i)
  );

  sc_fir_shared #(.SN_LEN(SN_LEN), .TAPS(TAPS)) u_shared (
      .clk(clk), .rst(rst), .start(start && (mode == MODE_SHARED)),
      .base_shift(base_shift), .x_in(x_in), .done(done_s), .y_out(y_s)
  );

  sc_fir_asng #(.SN_LEN(SN_LEN), .TAPS(TAPS)) u_asng (
      .clk(clk), .rst(rst), .start(start && (mode == MODE_ASNG)),
      .x_in(x_in), .done(done_a), .y_out(y_a)
  );

  sc_fir_ld #(.SN_LEN(SN_LEN), .TAPS(TAPS)) u_ld (
      .clk(clk), .rst(rst), .start(start && (mode == MODE_LD)),
      .x_in(x_in), .done(done_l), .y_out(y_l)
  );

  sc_fir_wbg #(.SN_LEN(SN_LEN), .TAPS(TAPS)) u_wbg (
      .clk(clk), .rst(rst), .start(start && (mode == MODE_WBG)),
      .x_in(x_in), .done(done_w), .y_out(y_w)
  );

  sc_fir_d #(.SN_LEN(SN_LEN), .TAPS(TAPS)) u_d (
      .clk(clk), .rst(rst), .start(start && (mode == MODE_D)),
      .base_shift(base_shift), .x_in(x_in), .done(done_d), .y_out(y_d)
  );

  assign valid_out = bin_valid;

  always @* begin
    case (mode)
      MODE_BIN: begin
        done = bin_valid;
        y_out = {{16{bin_y16[15]}}, bin_y16};
      end
      MODE_INDEP: begin done = done_i; y_out = y_i; end
      MODE_SHARED: begin done = done_s; y_out = y_s; end
      MODE_ASNG: begin done = done_a; y_out = y_a; end
      MODE_LD: begin done = done_l; y_out = y_l; end
      MODE_WBG: begin done = done_w; y_out = y_w; end
      MODE_D: begin done = done_d; y_out = y_d; end
      default: begin done = 0; y_out = 0; end
    endcase
  end
endmodule
