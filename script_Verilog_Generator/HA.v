module HA (a, cin, sum, cout);
	input a;
	input cin;
	output sum;
	output cout;
	reg sum,cout;
	always@(*)
	/*synopsys resource HA: map_to_module="DW01_add", implementation="apparch", ops="a0";*/
		{cout,sum} = a + cin; //synopsys label a0
endmodule
