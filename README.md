# ECG FIR with stochastic computing

31-tap Hamming-window FIR at 360 Hz sampling and 50 Hz low-pass cutoff for ECG denoising. Multiplies and adds use stochastic computing for FPGA-friendly area.

| Path | Contents |
|------|----------|
| `ref/behavior/main_legacy.cpp` | Legacy behavioral model |
| `ref/matlab/design_fir_ecg.m` | FIR coefficient design |
| `hls/common/` | Shared types and `fir_coeffs.h` |
| `hls/binary_fir/` | Conventional binary MAC FIR kernel |
| `hls/sc_fir_indep/` | SC FIR, independent SNG per tap |
| `hls/sc_fir_shared/` | SC FIR, shared D-SNG |
| `hls/sc_fir_asng/` | SC FIR, A-SNG |
| `rtl/common/fir_coeffs.vh` | Tap coefficients (8-bit SC + traditional) |
| `rtl/sng/` | LFSR, D-function LUT, WBG-SNG bit, Halton sample |
| `rtl/sc/` | Serial SC multiply / WBG add merge |
| `rtl/fir/` | Binary FIR, SC FIR variants, `ecg_fir_top` |

### RTL `ecg_fir_top` modes

| `mode` | Module | Variant |
|--------|--------|---------|
| 0 | `fir_direct_bin` | Binary direct-form MAC |
| 1 | `sc_fir_indep` | Dual independent LFSR comparison SNG |
| 2 | `sc_fir_shared` | Shared LFSR, per-tap coefficient shift |
| 3 | `sc_fir_asng` | WBG-up coefficient SNG |
| 4 | `sc_fir_ld` | Halton sample + LFSR comparison SNG |
| 5 | `sc_fir_wbg` | WBG mux stream add |
| 6 | `sc_fir_d` | D-function on coefficient SNG |

Default stochastic length parameter `SN_LEN = 4096` on SC tops. One output sample takes `31 × SN_LEN` clock cycles per SC multiply path (WBG stream mode: `31 × SN_LEN` merge cycles).

List sources with `rtl/filelist.f` for simulation or synthesis.
