module CSL (in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15, in16, in17, in18, out0_g, out1_g, out2_g, out3_g, out0, out1, out2, out3, out4, out5, out6, out7, out8, out9, out10, out11, out12, out13, out14, out15, out16, out17, out18, out19);
	input[1:0] in0;
	input[1:0] in1;
	input[1:0] in2;
	input[1:0] in3;
	input[1:0] in4;
	input[1:0] in5;
	input[1:0] in6;
	input[1:0] in7;
	input[1:0] in8;
	input[1:0] in9;
	input[1:0] in10;
	input[0:0] in11;
	input[0:0] in12;
	input[1:0] in13;
	input[0:0] in14;
	input[0:0] in15;
	input[0:0] in16;
	input[0:0] in17;
	input[0:0] in18;
	input out0_g;
	input out1_g;
	input out2_g;
	input out3_g;
	output out0;
	output out1;
	output out2;
	output out3;
	output out4;
	output out5;
	output out6;
	output out7;
	output out8;
	output out9;
	output out10;
	output out11;
	output out12;
	output out13;
	output out14;
	output out15;
	output out16;
	output out17;
	output out18;
	output out19;


	wire out18_s1, out18_s0;
	wire out18_c1;
	wire out17_s1, out17_s0;
	wire out17_c1;
	wire out16_s1, out16_s0;
	wire out16_c1;
	assign out18_s0 = in18;
	HA H7(.a(in18),.cin(1'b1),.sum(out18_s1),.cout(out18_c1));
	MUX M0(.a(out18_s1),.b(out18_s0),.sel(1'b0),.z(out19));
	assign out17_s0 = in17;
	HA H8(.a(in17),.cin(out18_c1),.sum(out17_s1),.cout(out17_c1));
	MUX M1(.a(out17_s1),.b(out17_s0),.sel(1'b0),.z(out18));
	assign out16_s0 = in16;
	HA H9(.a(in16),.cin(out17_c1),.sum(out16_s1),.cout(out16_c1));
	MUX M2(.a(out16_s1),.b(out16_s0),.sel(1'b0),.z(out17));

	wire out15_s1, out15_s0;
	wire out15_c1;
	wire out14_s1, out14_s0;
	wire out14_c1;
	wire out13_s1, out13_s0;
	wire out13_c1, out13_c0;
	assign out15_s0 = in15;
	HA H10(.a(in15),.cin(1'b1),.sum(out15_s1),.cout(out15_c1));
	MUX M3(.a(out15_s1),.b(out15_s0),.sel(out0_g),.z(out16));
	assign out14_s0 = in14;
	HA H11(.a(in14),.cin(out15_c1),.sum(out14_s1),.cout(out14_c1));
	MUX M4(.a(out14_s1),.b(out14_s0),.sel(out0_g),.z(out15));
	HA H12(.a(in13[0]),.cin(in13[1]),.sum(out13_s0),.cout(out13_c0));
	FA F69(.a(in13[0]),.b(in13[1]),.cin(out14_c1),.sum(out13_s1),.cout(out13_c1));
	MUX M5(.a(out13_s1),.b(out13_s0),.sel(out0_g),.z(out14));

	wire out12_s1, out12_s0;
	wire out12_c1;
	wire out11_s1, out11_s0;
	wire out11_c1;
	wire out10_s1, out10_s0;
	wire out10_c1, out10_c0;
	wire out9_s1, out9_s0;
	wire out9_c1, out9_c0;
	wire out8_s1, out8_s0;
	wire out8_c1, out8_c0;
	assign out12_s0 = in12;
	HA H13(.a(in12),.cin(1'b1),.sum(out12_s1),.cout(out12_c1));
	MUX M6(.a(out12_s1),.b(out12_s0),.sel(out1_g),.z(out13));
	assign out11_s0 = in11;
	HA H14(.a(in11),.cin(out12_c1),.sum(out11_s1),.cout(out11_c1));
	MUX M7(.a(out11_s1),.b(out11_s0),.sel(out1_g),.z(out12));
	HA H15(.a(in10[0]),.cin(in10[1]),.sum(out10_s0),.cout(out10_c0));
	FA F70(.a(in10[0]),.b(in10[1]),.cin(out11_c1),.sum(out10_s1),.cout(out10_c1));
	MUX M8(.a(out10_s1),.b(out10_s0),.sel(out1_g),.z(out11));
	FA F71(.a(in9[0]),.b(in9[1]),.cin(out10_c0),.sum(out9_s0),.cout(out9_c0));
	FA F72(.a(in9[0]),.b(in9[1]),.cin(out10_c1),.sum(out9_s1),.cout(out9_c1));
	MUX M9(.a(out9_s1),.b(out9_s0),.sel(out1_g),.z(out10));
	FA F73(.a(in8[0]),.b(in8[1]),.cin(out9_c0),.sum(out8_s0),.cout(out8_c0));
	FA F74(.a(in8[0]),.b(in8[1]),.cin(out9_c1),.sum(out8_s1),.cout(out8_c1));
	MUX M10(.a(out8_s1),.b(out8_s0),.sel(out1_g),.z(out9));

	wire out7_s1, out7_s0;
	wire out7_c1, out7_c0;
	wire out6_s1, out6_s0;
	wire out6_c1, out6_c0;
	wire out5_s1, out5_s0;
	wire out5_c1, out5_c0;
	wire out4_s1, out4_s0;
	wire out4_c1, out4_c0;
	HA H16(.a(in7[0]),.cin(in7[1]),.sum(out7_s0),.cout(out7_c0));
	FA F75(.a(in7[0]),.b(in7[1]),.cin(1'b1),.sum(out7_s1),.cout(out7_c1));
	MUX M11(.a(out7_s1),.b(out7_s0),.sel(out2_g),.z(out8));
	FA F76(.a(in6[0]),.b(in6[1]),.cin(out7_c0),.sum(out6_s0),.cout(out6_c0));
	FA F77(.a(in6[0]),.b(in6[1]),.cin(out7_c1),.sum(out6_s1),.cout(out6_c1));
	MUX M12(.a(out6_s1),.b(out6_s0),.sel(out2_g),.z(out7));
	FA F78(.a(in5[0]),.b(in5[1]),.cin(out6_c0),.sum(out5_s0),.cout(out5_c0));
	FA F79(.a(in5[0]),.b(in5[1]),.cin(out6_c1),.sum(out5_s1),.cout(out5_c1));
	MUX M13(.a(out5_s1),.b(out5_s0),.sel(out2_g),.z(out6));
	FA F80(.a(in4[0]),.b(in4[1]),.cin(out5_c0),.sum(out4_s0),.cout(out4_c0));
	FA F81(.a(in4[0]),.b(in4[1]),.cin(out5_c1),.sum(out4_s1),.cout(out4_c1));
	MUX M14(.a(out4_s1),.b(out4_s0),.sel(out2_g),.z(out5));

	wire out3_s1, out3_s0;
	wire out3_c1, out3_c0;
	wire out2_s1, out2_s0;
	wire out2_c1, out2_c0;
	wire out1_s1, out1_s0;
	wire out1_c1, out1_c0;
	wire out0_s1, out0_s0;
	wire out0_c1, out0_c0;
	HA H17(.a(in3[0]),.cin(in3[1]),.sum(out3_s0),.cout(out3_c0));
	FA F82(.a(in3[0]),.b(in3[1]),.cin(1'b1),.sum(out3_s1),.cout(out3_c1));
	MUX M15(.a(out3_s1),.b(out3_s0),.sel(out3_g),.z(out4));
	FA F83(.a(in2[0]),.b(in2[1]),.cin(out3_c0),.sum(out2_s0),.cout(out2_c0));
	FA F84(.a(in2[0]),.b(in2[1]),.cin(out3_c1),.sum(out2_s1),.cout(out2_c1));
	MUX M16(.a(out2_s1),.b(out2_s0),.sel(out3_g),.z(out3));
	FA F85(.a(in1[0]),.b(in1[1]),.cin(out2_c0),.sum(out1_s0),.cout(out1_c0));
	FA F86(.a(in1[0]),.b(in1[1]),.cin(out2_c1),.sum(out1_s1),.cout(out1_c1));
	MUX M17(.a(out1_s1),.b(out1_s0),.sel(out3_g),.z(out2));
	FA F87(.a(in0[0]),.b(in0[1]),.cin(out1_c0),.sum(out0_s0),.cout(out0_c0));
	FA F88(.a(in0[0]),.b(in0[1]),.cin(out1_c1),.sum(out0_s1),.cout(out0_c1));
	MUX M18(.a(out0_s1),.b(out0_s0),.sel(out3_g),.z(out1));
	MUX M19(.a(out0_c1),.b(out0_c0),.sel(out3_g),.z(out0));
endmodule
