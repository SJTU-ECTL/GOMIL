module Inf1 (a, b, p, g);
	input a;
	input b;
	output p;
	output g;
	assign p = a|b;
	assign g = a&b;
endmodule
