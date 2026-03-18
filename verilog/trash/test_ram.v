`timescale 1ns/1ps

module ram_tb;

    reg clk;
    reg [15:0] a;      
    reg w;             
    reg [20:0] d;     
    wire [20:0] out;
    ram dut (
        .clk(clk),
        .a(a),
        .w(w),
        .d(d),
        .out(out)
    );


    // generator zegara (toggle)
    initial begin
        clk = 0;
        forever #5 clk = ~clk;   // okres 10 ns
    end

    // obserwacja + zakończenie symulacji
    initial begin
        $dumpfile("ram.vcd");
        $dumpvars(0, ram_tb);
        
        a = 0; w = 0; d = 0;

        #10;
        a = 15'd0; d = 63'd42; w = 1;
        #10;
        w = 0;
        a = 6'd0;
        #10;
        $display("Out = %d", out);

        // zapis do adresu 1
        a = 15'd1; d = 20'd99; w = 1;
        #10; w = 0;

        // odczyt z adresu 1
        a = 15'd1;
        #10;
        $display("Out = %d", out);

        $finish;
    end

endmodule
