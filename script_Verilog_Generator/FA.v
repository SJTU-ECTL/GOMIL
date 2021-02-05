module FA (a, b, cin, sum, cout);
	input a;
	input b;
	input cin;
	output sum;
	output cout;
	reg sum,cout;
	always@(*)
	/*synopsys resource FA: map_to_module="DW01_add", implementation="apparch", ops="a0";*/
		{cout,sum} = a + b + cin; //synopsys label a0
endmodule
