module processor_top;
    reg clk;
    wire [12:0]ram_out; 
    wire [7:0]arg_value;
    wire [4:0]instruction;
    wire ram_write;
    reg [7:0]ram_addr;
    wire [12:0]ram_value;
    reg [12:0] data_bus;
    reg ir_clk;
    wire init;
    reg [3:0]stage;
    reg [7:0]pc;
    reg reg_num;
    reg reg_write_val;
    wire reg_out;
    reg reg_write;
    reg [7:0]help_reg;
    reg [7:0]program_output;

    reg [1:0]phase;

    initial begin
        pc          <= 8'b0;
        ir_clk      <= 0;
        init        <= 1;
        ram_write   <= 0;
        ram_addr    <= 8'b0;
        reg_write   <= 0;
        stage       <= 0;
    end

    ram ram_unit(
        .clk(clk), 
        .a(ram_addr), 
        .w(ram_write), 
        .d(ram_value), 
        .out(ram_out)
    );

    control control_unit(
        .arg(data_bus), 
        .set_ir(ir_clk),
        .arg_value(arg_value), 
        .instruction(instruction)
    );

    regs registers(
        .clk(clk),
        .reg_num(reg_num),
        .write(reg_write),
        .write_val(reg_write_val),
        .out_val(reg_out)
    );

    always @(posedge clk) begin
        case(instruction)
            5'b00000 : begin// lda
                    reg_write <= 0;
                    ir_clk    <= 0;

                    case (stage)

                        4'd0: begin
                            ram_addr <= arg_value;
                            pc       <= pc + 1;
                            stage    <= 4'd1;
                        end

                        4'd1: begin
                            data_bus <= ram_out;
                            stage    <= 4'd2;
                        end

                        4'd2: begin
                            reg_num       <= 2'b00;
                            reg_write     <= 1;
                            reg_write_val <= data_bus[12:5];
                            stage         <= 4'd3;
                        end

                        4'd3: begin
                            ram_addr <= pc;
                            stage    <= 4'd4;
                        end

                        4'd4: begin
                            ir_clk <= 1;
                            stage  <= 4'd0;
                        end

                        default: begin
                            stage <= 4'd0;
                        end

                    endcase
                end
            5'b00001 : begin // sta
                reg_write <= 0;
                ir_clk    <= 0;

                case(stage)
                    4'd0: begin
                        ram_addr <= arg_value;
                        pc       <= pc + 1;
                        ram_write<= 1;
                        stage    <= 4'd1;
                    end

                    4'd1: begin
                        ram_value <= reg_out;
                        stage     <= 4'd2;
                    end

                    4'd2: begin
                        ram_addr <= pc;
                        ir_clk   <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end
                endcase
            end

            5'd2 : begin // add
                ir_clk    <= 0;

                case(stage)
                    4'd0: begin
                        reg_num  <= 2'b01;
                        pc       <= pc + 1;
                        stage    <= 4'd1;
                    end

                    4'd1: begin
                        help_reg <= reg_out;
                        stage     <= 4'd2;
                    end

                    4'd2: begin
                        reg_num  <= 2'b00;
                        stage    <= 4'd3;
                    end

                    4'd3: begin
                        help_reg <= help_reg + reg_out;
                        stage    <= 4'd4;
                    end

                    4'd4: begin
                        reg_num       <= 2'b00;
                        reg_write     <= 1;
                        reg_write_val <= help_reg; 
                        stage         <= 4'd5;
                    end

                    4'd5: begin
                        ram_addr <= pc;
                        ir_clk   <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end
                endcase
            end

            5'd3 : begin // sub
                ir_clk    <= 0;

                case(stage)
                    4'd0: begin
                        reg_num  <= 2'b01;
                        pc       <= pc + 1;
                        stage    <= 4'd1;
                    end

                    4'd1: begin
                        help_reg <= reg_out;
                        stage     <= 4'd2;
                    end

                    4'd2: begin
                        reg_num  <= 2'b00;
                        stage    <= 4'd3;
                    end

                    4'd3: begin
                        help_reg <= help_reg - reg_out;
                        stage    <= 4'd4;
                    end

                    4'd4: begin
                        reg_num       <= 2'b00;
                        reg_write     <= 1;
                        reg_write_val <= help_reg; 
                        stage         <= 4'd5;
                    end

                    4'd5: begin
                        ram_addr <= pc;
                        ir_clk   <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end
                endcase
            end

            5'd4 : begin // and
                ir_clk    <= 0;

                case(stage)
                    4'd0: begin
                        reg_num  <= 2'b01;
                        pc       <= pc + 1;
                        stage    <= 4'd1;
                    end

                    4'd1: begin
                        help_reg <= reg_out;
                        stage     <= 4'd2;
                    end

                    4'd2: begin
                        reg_num  <= 2'b00;
                        stage    <= 4'd3;
                    end

                    4'd3: begin
                        help_reg <= help_reg & reg_out;
                        stage    <= 4'd4;
                    end

                    4'd4: begin
                        reg_num       <= 2'b00;
                        reg_write     <= 1;
                        reg_write_val <= help_reg; 
                        stage         <= 4'd5;
                    end

                    4'd5: begin
                        ram_addr <= pc;
                        ir_clk   <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end
                endcase
            end

            5'd5 : begin // or
                ir_clk    <= 0;

                case(stage)
                    4'd0: begin
                        reg_num  <= 2'b01;
                        pc       <= pc + 1;
                        stage    <= 4'd1;
                    end

                    4'd1: begin
                        help_reg <= reg_out;
                        stage     <= 4'd2;
                    end

                    4'd2: begin
                        reg_num  <= 2'b00;
                        stage    <= 4'd3;
                    end

                    4'd3: begin
                        help_reg <= help_reg | reg_out;
                        stage    <= 4'd4;
                    end

                    4'd4: begin
                        reg_num       <= 2'b00;
                        reg_write     <= 1;
                        reg_write_val <= help_reg; 
                        stage         <= 4'd5;
                    end

                    4'd5: begin
                        ram_addr <= pc;
                        ir_clk   <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end
                endcase
            end

            5'd6 : begin // xor
                ir_clk    <= 0;

                case(stage)
                    4'd0: begin
                        reg_num  <= 2'b01;
                        pc       <= pc + 1;
                        stage    <= 4'd1;
                    end

                    4'd1: begin
                        help_reg <= reg_out;
                        stage     <= 4'd2;
                    end

                    4'd2: begin
                        reg_num  <= 2'b00;
                        stage    <= 4'd3;
                    end

                    4'd3: begin
                        help_reg <= (~help_reg & reg_out) | (help_reg & ~reg_out);
                        stage    <= 4'd4;
                    end

                    4'd4: begin
                        reg_num       <= 2'b00;
                        reg_write     <= 1;
                        reg_write_val <= help_reg; 
                        stage         <= 4'd5;
                    end

                    4'd5: begin
                        ram_addr <= pc;
                        ir_clk   <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end
                endcase
            end
            
            5'd7 : begin // not
                ir_clk    <= 0;
                reg_write <= 0;

                case (stage)
                    4'd0: begin

                        reg_num   <= 2'b00;
                        pc    <= pc + 1;
                        stage <= 4'd1;
                    end

                    4'd1: begin
                        help_reg <= ~reg_out;
                        stage    <= 4'd2;
                    end

                    4'd2: begin
                        reg_write     <= 1;
                        reg_write_val <= help_reg;
                        stage         <= 4'd3;
                    end

                    4'd3: begin
                        ram_addr <= pc;
                        ir_clk   <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end
                endcase
            end

            5'd8 : begin// lla
                    reg_write <= 0;
                    ir_clk    <= 0;
                    reg_num       <= 2'b00;

                    case (stage)

                        4'd0: begin
                            pc            <= pc + 1;
                            data_bus      <= reg_out;
                            stage         <= 4'd1;
                        end

                        4'd1: begin
                            reg_write     <= 1;
                            reg_write_val <= data_bus[12:5];
                            stage    <= 4'd2;
                        end

                        4'd2: begin
                            reg_write     <= 0;
                            ram_addr <= pc;
                            ir_clk <= 1;
                            stage    <= 4'd0;
                        end

                        default: begin
                            stage <= 4'd0;
                        end

                    endcase
                end

            5'd9 : begin // nop - definitely not the brightest design choice 
                reg_write <= 0;
                ir_clk    <= 0;
                reg_num       <= 2'b00;

                case (stage)

                    4'd0: begin
                        pc            <= pc + 1;
                        stage         <= 4'd1;
                    end

                    4'd1: begin
                        ram_addr <= pc;
                        ir_clk <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end

                endcase
            end

            5'd10 : begin // jmp
                    reg_write <= 0;
                    ir_clk    <= 0;

                    case (stage)

                        4'd0: begin
                            data_bus      <= reg_out;
                            stage         <= 4'd1;
                        end

                        4'd1: begin
                            pc <= data_bus[12:5];
                            stage    <= 4'd2;
                        end

                        4'd2: begin
                            ram_addr <= pc;
                            ir_clk <= 1;
                            stage    <= 4'd0;
                        end

                        default: begin
                            stage <= 4'd0;
                        end

                    endcase
                end

            5'd11 : begin // jz
                    reg_write <= 0;
                    ir_clk    <= 0;
                    reg_num       <= 2'b00;

                    case (stage)

                        4'd0: begin
                            data_bus      <= reg_out;
                            stage         <= 4'd1;
                        end

                        4'd1: begin
                            if (reg_num == 8'b0)
                                pc <= data_bus[12:5];
                            stage    <= 4'd2;
                        end

                        4'd2: begin
                            ram_addr <= pc;
                            ir_clk <= 1;
                            stage    <= 4'd0;
                        end

                        default: begin
                            stage <= 4'd0;
                        end

                    endcase
                end
            5'd12 : begin // rxa gets data from input register
                reg_write <= 0;
                ir_clk    <= 0;
                reg_num       <= 2'b00;

                case (stage)

                    4'd0: begin
                        pc            <= pc + 1;
                        stage         <= 4'd1;
                    end

                    4'd1: begin
                        ram_addr <= pc;
                        ir_clk <= 1;
                        stage    <= 4'd0;
                    end

                    default: begin
                        stage <= 4'd0;
                    end

                endcase
            end
                    
        endcase
    end


endmodule