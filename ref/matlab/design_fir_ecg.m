Fs = 360;
Fpass = 50;
N = 30;
w = hamming(N + 1);
b = fir1(N, Fpass / (Fs / 2), 'low', w);
bq = round(b * 256);
bq = max(min(bq, 255), 0);
fid = fopen('fir_coe_8bit.hex', 'w');
for k = 1:numel(bq)
    fprintf(fid, '%04X\n', bq(k));
end
fclose(fid);
figure;
freqz(b, 1, 1024, Fs);
title('FIR frequency response');
disp('Wrote fir_coe_8bit.hex (compare with hls/common/fir_coeffs.h)');
