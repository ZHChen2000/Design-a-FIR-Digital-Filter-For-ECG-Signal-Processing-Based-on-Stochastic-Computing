module lfsr12_rotate #(
    parameter W = 12
) (
    input  wire [W-1:0]     in_state,
    input  wire [3:0]       shift_amt,
    output reg  [W-1:0]     out_state
);
  function automatic [W-1:0] rot_n(input [W-1:0] v, input [3:0] n);
    integer j;
    begin
      rot_n = v;
      for (j = 0; j < n; j = j + 1)
        rot_n = {rot_n[W-2:0], rot_n[W-1]};
    end
  endfunction

  always @* out_state = rot_n(in_state, shift_amt);
endmodule
