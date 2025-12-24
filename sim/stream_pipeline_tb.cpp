#include <stdio.h>
#include <cstring>
#include "Vstream_pipeline.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

enum class InputMode {
    CONTINUOUS,
    BURSTY,
    RANDOM
};

enum class OutputMode {
    ALWAYS_READY,
    PERIODIC_STALL,
    RANDOM_STALL
};

uint8_t decide_out_ready(OutputMode Output);

uint64_t cycle = 0;

OutputMode parse_output_mode(const char* mode_str) {
    if (strcmp(mode_str, "always") == 0) {
        return OutputMode::ALWAYS_READY;
    } else if (strcmp(mode_str, "periodic") == 0) {
        return OutputMode::PERIODIC_STALL;
    } else if (strcmp(mode_str, "random") == 0) {
        return OutputMode::RANDOM_STALL;
    } else {
        printf("Unknown output mode: %s. Using random_stall by default.\n", mode_str);
        return OutputMode::RANDOM_STALL;
    }
}

struct PendingTransaction {
    uint32_t data;
    uint32_t expected_output;
};
std::queue<PendingTransaction> pending_queue;

int main(int argc, char **argv) {
    // Parse custom arguments BEFORE Verilated::commandArgs consumes them
    OutputMode output_mode = OutputMode::ALWAYS_READY;
    if (argc > 1) {
        output_mode = parse_output_mode(argv[1]);
    }
    
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    // Create model and trace objects
    Vstream_pipeline* top = new Vstream_pipeline;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    // trace depth = 99 levels
    top->trace(tfp, 99);  
    tfp->open("trace.vcd");

    // Run simulation
    printf("Starting simulation...\n");

    const uint32_t reset_cycles = 1;
    const uint8_t stages = 4;
    const uint32_t num_transactions = 1000;
    const uint64_t max_cycles = reset_cycles + 5 * num_transactions + 10 * stages + 1000;

    uint8_t in_valid = 0;
    uint8_t in_ready = 0;
    uint8_t out_valid = 0;
    uint8_t out_ready = 0;

    uint32_t in_data = 0;
    uint32_t out_data = 0;
    
    bool pending_input = false;
    uint32_t pending_value;
    uint32_t next_input_value;

    std::unordered_map<uint32_t, uint64_t> input_accept_cycle;
    std::unordered_map<uint32_t, uint64_t> output_accept_cycle;

    std::vector<uint64_t> latency_samples;

    InputMode  input_mode =  InputMode::CONTINUOUS;

    uint32_t burst_length = 0;
    uint32_t burst_period = 0;

    uint32_t stall_length = 0;
    uint32_t stall_period = 0;

    uint32_t idle_cycle_count = 0;
    const uint32_t deadlock_threshold = 11;

    for (int i = 0; i < reset_cycles; i++) {
        // Clock LOW
        top->clk = 0;
        top->rst = 1;
        top->eval();
        tfp->dump(i * 10);
        // Clock HIGH
        top->clk = 1;
        top->eval();
        tfp->dump(i * 10 + 5);
    }

    if(top->out_valid != 0) {
        printf("Error: Output valid high during reset!\n");
        return -1;
    }
    top->rst = 0;
    while (cycle < max_cycles) {
        // Clock LOW
        top->clk = 0;
        
        out_ready = decide_out_ready(output_mode);
    
        top->eval();
        tfp->dump(cycle * 10);

        idle_cycle_count++;

        if(!pending_input) {
            pending_input = true;
            in_valid = 1;
            in_data = cycle;
            PendingTransaction tx = {cycle, cycle + 4};  // stages=4
            pending_queue.push(tx);
        }
        
        top->in_data = in_data;
        top->in_valid = in_valid;
        top->out_ready = out_ready;

        top->eval();
        tfp->dump(cycle * 10 + 2.5);

        // Clock HIGH
        top->clk = 1;
        
        top->eval();
        tfp->dump(cycle * 10 + 5);

        // Check if input was accepted this cycle
        if(top->in_ready && in_valid) {
            pending_input = false;
            in_valid = 0;
        }

        if(out_ready && top->out_valid && !pending_queue.empty()) {
            auto tx = pending_queue.front();
            pending_queue.pop();
            assert(top->out_data == tx.expected_output && "Data mismatch detected!");
        }

        cycle++;

    }

    tfp->close();
    delete top;
    delete tfp;
    
    printf("Simulation complete! Trace saved to trace.vcd\n");
    return 0;
}  


uint8_t decide_out_ready(OutputMode Output){

    uint8_t stall = (Output == OutputMode::PERIODIC_STALL) ? 10 : rand() % 5;
    switch (Output) {
        case OutputMode::ALWAYS_READY:
            return 1;
        case OutputMode::PERIODIC_STALL:
            // Implement periodic stall logic
            return (cycle % (stall + 1) >= 5) ? 0 : 1;
        case OutputMode::RANDOM_STALL:
            // Implement random stall logic
            return (cycle % (stall + 1) == 0) ? 0 : 1;
        default:
            return 1;
    }
}