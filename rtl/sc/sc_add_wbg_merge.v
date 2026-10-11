module sc_add_wbg_merge #(
    parameter W = 12
) (
    input  wire [W-1:0]     stream_idx,
    input  wire             bit_a,
    input  wire             bit_b,
    output wire             bit_out
);
  wire [W-1:0] down_cnt = (4095 - stream_idx[W-1:0]);
  wire         ctrl;
  wbg_sng_bit #(.W(W)) u_ctrl (
      .counter(down_cnt),
      .bound(12'd2048),
      .sn_bit(ctrl)
  );
  assign bit_out = ctrl ? bit_b : bit_a;
endmodule
