module pref_elem1 (g1, p1, g2, p2, g_out, p_out);
	input g1;
	input p1;
	input g2;
	input p2;
	output g_out;
	output p_out;
	assign g_out = g1|(p1&g2);
	assign p_out = p1&p2;
endmodule
