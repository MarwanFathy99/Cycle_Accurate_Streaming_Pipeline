module stream_pipeline #(
    parameter int DATA_WIDTH = 32
    // parameter int NUM_STAGES = 1
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
    
    always_ff @(posedge clk) begin
        if (rst) begin
            out_valid <= 0;
            out_data <= 32'b0;
        end else begin
            if (in_valid && in_ready) begin
                out_data <= in_data + 1;
                out_valid <= 1;
            end else if (out_ready && out_valid) begin
                out_valid <= 0;
            end
        end
    end

    assign in_ready = !out_valid || (out_ready && out_valid);

endmodule
