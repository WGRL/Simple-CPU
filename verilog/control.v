module control(input reg [12:0]arg, input reg set_ir, output [7:0]arg_value, output [4:0]instruction);
    always@(posedge set_ir)begin
        arg_value   <= arg[12:5]; 
        instruction <= arg[4:0];
    end

    //case 5'b00000, 5'b00001, 5'b10000, 5'b10001, 5'b10010, 5'b10011 : begin


endmodule