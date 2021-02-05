module MUX (a, b, sel, z);
	input a;
	input b;
	input sel;
	output z;
	reg z;
	always @(*)
		begin
		if(sel == 1'b1)
			z = a;
		else
			z = b;
		end
endmodule
