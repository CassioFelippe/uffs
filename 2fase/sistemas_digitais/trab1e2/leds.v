module leds (
	// ENTRADA DE 8 BITS NOMEADA CLOCK
	input CLOCK_50,
  // SAÍDA DE 8 BITS NOMEADA S
  output [7:0] LEDG
);

// REGISTRADOR DE 8 BITS DA SAÍDA S
reg[7:0] blinkingLed = 0;
assign LEDG = blinkingLed;

always @(posedge CLOCK_50) begin
  // REGISTRADOR blinkingLed RECEBE SEU INVERSO
  blinkingLed <= ~blinkingLed;

end

endmodule

// MODULO DE TESTE (SAÍDA PARA GTKWAVE)
module test;

	reg clk = 0;
	wire [7:0] ls;

  leds leds1(clk, ls);

	initial begin
		$dumpvars;

		#2 clk = ~clk;
		#2 clk = ~clk;
		#2 clk = ~clk;
		#2 clk = ~clk;
		#2 clk = ~clk;
		#2 clk = ~clk;
		#2 clk = ~clk;
		#2 clk = ~clk;
		#2 clk = ~clk;

		$finish;
	end
endmodule

// PRIMEIRO TRABALHO: LEDS PISCANDO (NÃO VISÍVEL, TOO FAST)
