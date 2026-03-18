// general use registers
module regs(input clk, input [1:0]reg_num, input write, input write_val output out_val);
    // regs : 0 rxa, 1 rxb, 2 rxc
    reg [7:0]rxa;
    reg [7:0]rxb;
    reg [7:0]rxc;

    always @(posedge clk) begin
        if (write) begin
            case(reg_num)
                2'b00 : rxa <= write_val;
                2'b01 : rxb <= write_val;
                2'b10 : rxc <= write_val;
            endcase
        end
    end
    
    case (reg_num)
        2'b00   : assign out_val = rxa;
        2'b01   : assign out_val = rxb;
        2'b10   : assign out_val = rxc;
        default : assign out_val = rxa;
    endcase
endmodule