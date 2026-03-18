module ram(input clk, input [7:0]a, input w, input [12:0]d, output [12:0]out);
    reg [7:0] mem [12:0];
    always @(posedge clk)begin
        if (w == 1'b1)begin
            mem[a] <= d;
        end
    end

    assign out = mem[a];
endmodule