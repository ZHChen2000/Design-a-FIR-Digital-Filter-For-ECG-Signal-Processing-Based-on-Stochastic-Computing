# 基于随机计算的心电 FIR 滤波

31 阶 Hamming 窗 FIR，360 Hz 采样、50 Hz 低通，用于心电去噪。随机计算实现乘加，面向 FPGA 资源受限场景。

| 路径 | 内容 |
|------|------|
| `ref/behavior/main_legacy.cpp` | Legacy 行为模型 |
| `ref/matlab/design_fir_ecg.m` | FIR 系数设计 |
| `hls/common/` | 公共类型与 `fir_coeffs.h` |
| `hls/binary_fir/` | 常规二进制 MAC FIR 核 |
| `hls/sc_fir_indep/` | SC FIR，每抽头独立 SNG |
| `hls/sc_fir_shared/` | SC FIR，共享 D-SNG |
| `hls/sc_fir_asng/` | SC FIR，A-SNG |
| `rtl/common/fir_coeffs.vh` | 抽头系数（8 bit SC + 传统 MAC） |
| `rtl/sng/` | LFSR、D 函数 LUT、WBG-SNG、Halton |
| `rtl/sc/` | 串行 SC 乘法 / WBG 加法合并 |
| `rtl/fir/` | 二进制 FIR、各 SC FIR 顶层、`ecg_fir_top` |

### RTL `ecg_fir_top` 模式

| `mode` | 模块 | 变体 |
|--------|------|------|
| 0 | `fir_direct_bin` | 二进制直接型 MAC |
| 1 | `sc_fir_indep` | 双路独立 LFSR 比较式 SNG |
| 2 | `sc_fir_shared` | 共享 LFSR，系数按抽头移位 |
| 3 | `sc_fir_asng` | WBG-up 系数 SNG |
| 4 | `sc_fir_ld` | Halton 采样 + LFSR 比较式 SNG |
| 5 | `sc_fir_wbg` | WBG 选通流式加 |
| 6 | `sc_fir_d` | 系数路径 D 函数 SNG |

SC 顶层默认 `SN_LEN = 4096`。除 WBG 流式加法外，每个输出样本约需 `31 × SN_LEN` 个时钟（WBG 模式为 `31 × SN_LEN` 次比特合并）。

综合或仿真源文件见 `rtl/filelist.f`。
