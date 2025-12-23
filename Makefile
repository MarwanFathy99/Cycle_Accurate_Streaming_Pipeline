TOP=stream_pipeline
VERILATOR=verilator
SRC=rtl/stream_pipeline.sv
TB=sim/stream_pipeline_tb.cpp
OUT=build
EXECUTABLE=$(OUT)/sim

# Verilator options
VERILATOR_FLAGS = -Wall --trace --cc --exe -Mdir $(OUT)

# Extract output mode from command line arguments
# Usage: make run always/periodic/random
VALID_MODES := always periodic random
MODE := $(filter $(VALID_MODES), $(MAKECMDGOALS))
OUTPUT_MODE := $(if $(MODE), $(MODE), always)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC) $(TB)
	mkdir -p $(OUT)
	$(VERILATOR) $(VERILATOR_FLAGS) $(SRC) $(TB) -o sim
	make -C $(OUT) -f V$(TOP).mk

run: all
	./$(EXECUTABLE) $(OUTPUT_MODE)

# Define mode targets so they don't cause errors
always periodic random:
	@:

view-trace: run
	@echo "VCD file generated: trace.vcd"
	@echo "Open with Surfer: surfer trace.vcd"

clean:
	rm -rf $(OUT) trace.vcd

.PHONY: all run view-trace clean help always periodic random

help:
	@echo "Usage: make run [OUTPUT_MODE]"
	@echo "Available OUTPUT_MODE options:"
	@echo "  always    - Output always ready"
	@echo "  periodic  - Periodic stall on output"
	@echo "  random    - Random stall on output (default)"
	@echo ""
	@echo "Examples:"
	@echo "  make run always"
	@echo "  make run periodic"
	@echo "  make run random"
