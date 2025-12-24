# Cycle Accurate Streaming Pipeline

A SystemVerilog streaming pipeline which relies on a handshake mechanism to execute data transfers. Each pipeline stage increments data by 1 (used as a sanity check)

The module is expandable to multiple pipeline stages.
## Prerequisites

### Required
- **Verilator**: SystemVerilog simulator compiler
- **Make**: Build automation tool
- **C++ Compiler**: clang++ or g++ (comes with Xcode)

### Optional (for viewing waveforms)
- **Surfer**: Modern waveform viewer

## Installation

### 1. Install Verilator

**Using Homebrew** (recommended):
```bash
brew install verilator
```

**From Source** (if needed):
```bash
git clone https://github.com/verilator/verilator.git
cd verilator
git checkout stable
autoconf
./configure
make
sudo make install
```

### 2. Install Waveform Viewer (optional but recommended)

**Surfer** (modern, recommended):
```bash
brew install surfer
```

## Project Structure

```
.
├── rtl/                    # HDL source files
│   └── test_top.sv        # Top-level SystemVerilog module
├── sim/                    # Simulation files
│   └── test_tb.cpp        # C++ testbench
├── build/                 # Generated files (auto-created)
├── Makefile               # Build configuration
├── trace.vcd              # Generated waveform trace
└── README.md              # This file
```

## Files Overview

### `rtl/cycle_accurate_streaming_pipeline.sv`
SystemVerilog module demonstrating:
- Clock and reset signals
- Ready-Valid handshake
- Increment of in_data


### `sim/cycle_accurate_streaming_pipeline_tb.cpp`
C testbench that:
- Instantiates the compiled Verilog module
- Generates clock and reset signals
- Applies stimulus to inputs
- Sets 'Ready' signal based on run arguments
- Records waveforms to VCD file
- Uses C standard library (`stdio.h`) for macOS compatibility

## Building and Running

### Quick Start

Build and simulate:
```bash
make run 
```
```
make run always will keep in_ready always high
make run periodic sets in_ready high for 5 cycles and then low for 1 cycle
make run random randomly sets in_ready to high
```

This will:
1. Compile your SystemVerilog with Verilator
2. Build the C++ testbench
3. Execute the simulation
4. Generate `trace.vcd` with waveform data

### Build Only (without running)
```bash
make all
```

### Run Existing Build
```bash
make run
```

### View Waveforms

**Using Surfer** (modern viewer):
```bash
surfer
```

Then use the GUI

### Clean Build Artifacts
```bash
make clean
```

## Advanced Usage

### Enabling More Trace Depth
In `Makefile`, modify Verilator flags:
```makefile
VERILATOR_FLAGS = -Wall --trace --trace-fst --cc --exe -Mdir $(OUT)
```

### Using FST Format (faster waveform viewing)
Replace `--trace` with `--trace-fst` in `Makefile` for better performance with large designs.

### Adding Verilator Options
Examples in `Makefile` VERILATOR_FLAGS:
- `--trace`: Enable VCD tracing (included)
- `-Wall`: Show all warnings
- `--coverage`: Enable code coverage
- `--assertions`: Enable SystemVerilog assertions

## References

- [Verilator Documentation](https://verilator.org/guide/latest/)
- [SystemVerilog Reference](https://en.wikipedia.org/wiki/SystemVerilog)

## Notes

- This template uses C standard library (`stdio.h`) instead of C++ headers for reliable macOS compatibility
- Removes the deprecated `graph-sdk` dependency
- VCD trace format is standard and compatible with most waveform viewers (Surfer, GTKWave, Pulseview, etc.)
- For production designs, consider adding formal verification and coverage analysis
- The example `test_top.sv` demonstrates a simple 2-stage pipeline for reference
