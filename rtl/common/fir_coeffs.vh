`ifndef FIR_COEFFS_VH
`define FIR_COEFFS_VH

parameter FIR_TAPS_P = 31;
parameter SN_LEN_DEF = 4096;
parameter LFSR_W = 12;
parameter SN_SCALE = 4096;

function automatic integer fir_coe_8bit(input integer idx);
  integer c [0:30];
  begin
    c[0]=70; c[1]=68; c[2]=66; c[3]=64; c[4]=64; c[5]=67; c[6]=70; c[7]=64;
    c[8]=45; c[9]=18; c[10]=0; c[11]=14; c[12]=70; c[13]=152; c[14]=226; c[15]=256;
    c[16]=226; c[17]=152; c[18]=70; c[19]=14; c[20]=0; c[21]=18; c[22]=45; c[23]=64;
    c[24]=70; c[25]=67; c[26]=64; c[27]=64; c[28]=66; c[29]=68; c[30]=70;
    fir_coe_8bit = c[idx];
  end
endfunction

function automatic integer fir_coe_trad(input integer idx);
  integer c [0:30];
  begin
    c[0]=849; c[1]=-701; c[2]=-2758; c[3]=-3860; c[4]=-1168; c[5]=6350; c[6]=14087;
    c[7]=12595; c[8]=-4649; c[9]=-31377; c[10]=-46117; c[11]=-23101; c[12]=48447;
    c[13]=150680; c[14]=241671; c[15]=278103; c[16]=241671; c[17]=150680; c[18]=48447;
    c[19]=-23101; c[20]=-46117; c[21]=-31377; c[22]=-4649; c[23]=12595; c[24]=14087;
    c[25]=6350; c[26]=-1168; c[27]=-3860; c[28]=-2758; c[29]=-701; c[30]=849;
    fir_coe_trad = c[idx];
  end
endfunction

`endif
