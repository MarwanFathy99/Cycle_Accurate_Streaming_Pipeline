module stream_pipeline #(
    parameter int DATA_WIDTH = 32,
    parameter int NUM_STAGES = 4
)(
    input  logic                  clk,
    input  logic                  rst,

    input  logic [DATA_WIDTH-1:0] in_data,
    input  logic                  in_valid,
    output logic                  in_ready,

    output logic [DATA_WIDTH-1:0] out_data,
    output logic                  out_valid,
    input  logic                  out_ready
);

    logic [NUM_STAGES:0]        valid;
    logic [NUM_STAGES:0]        ready;
    logic [NUM_STAGES:0][DATA_WIDTH-1:0] data;

    assign valid[0] = in_valid;
    assign in_ready = ready[0];
    assign out_data = data[NUM_STAGES];
    assign out_valid = valid[NUM_STAGES];
    assign ready[NUM_STAGES] = out_ready;
    assign data[0] = in_data;
    
    for(genvar i = 0; i < NUM_STAGES; i++) begin : gen_stages
        always_ff @(posedge clk) begin
            if (rst) begin
                valid[i+1] <= 0;
            end else begin
                if (ready[i] && valid[i]) begin  // Only update on valid transaction
                    data[i+1] <= data[i] + 1;
                    valid[i+1] <= 1;
                end else if (ready[i]) begin     // Or propagate empty slots
                    valid[i+1] <= 0;
                end
            end
        end

        assign ready[i] = !valid[i+1] || ready[i+1];
    end

endmodule
