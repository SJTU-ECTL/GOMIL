module Prefex_Tree (in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15, in16, in17, in18, out0_g, out0_p, out1_g, out1_p, out2_g, out2_p, out3_g, out3_p);
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
	output out0_g;
	output out0_p;
	output out1_g;
	output out1_p;
	output out2_g;
	output out2_p;
	output out3_g;
	output out3_p;


	//The first stage --pre-processing
	wire[18:0] P_s1;
	wire[18:0] G_s1;
	Inf1 I0(.a(in4[0]),.b(in4[1]),.p(P_s1[4]),.g(G_s1[4]));
	Inf1 I1(.a(in5[0]),.b(in5[1]),.p(P_s1[5]),.g(G_s1[5]));
	Inf1 I2(.a(in6[0]),.b(in6[1]),.p(P_s1[6]),.g(G_s1[6]));
	Inf1 I3(.a(in7[0]),.b(in7[1]),.p(P_s1[7]),.g(G_s1[7]));
	Inf1 I4(.a(in8[0]),.b(in8[1]),.p(P_s1[8]),.g(G_s1[8]));
	Inf1 I5(.a(in9[0]),.b(in9[1]),.p(P_s1[9]),.g(G_s1[9]));
	Inf1 I6(.a(in10[0]),.b(in10[1]),.p(P_s1[10]),.g(G_s1[10]));
	Inf2 U0(.a(in11[0]),.p(P_s1[11]),.g(G_s1[11]));
	Inf2 U1(.a(in12[0]),.p(P_s1[12]),.g(G_s1[12]));
	Inf1 I7(.a(in13[0]),.b(in13[1]),.p(P_s1[13]),.g(G_s1[13]));
	Inf2 U2(.a(in14[0]),.p(P_s1[14]),.g(G_s1[14]));
	Inf2 U3(.a(in15[0]),.p(P_s1[15]),.g(G_s1[15]));
	Inf2 U4(.a(in16[0]),.p(P_s1[16]),.g(G_s1[16]));
	Inf2 U5(.a(in17[0]),.p(P_s1[17]),.g(G_s1[17]));
	Inf2 U6(.a(in18[0]),.p(P_s1[18]),.g(G_s1[18]));

	//The 2-th stage
	wire[11:0] P_s2;
	wire[11:0] G_s2;
	assign G_s2[0] = G_s1[4];
	assign P_s2[0] = P_s1[4];
	assign G_s2[1] = G_s1[5];
	assign P_s2[1] = P_s1[5];
	assign G_s2[2] = G_s1[6];
	assign P_s2[2] = P_s1[6];
	assign G_s2[3] = G_s1[7];
	assign P_s2[3] = P_s1[7];
	assign G_s2[4] = G_s1[8];
	assign P_s2[4] = P_s1[8];
	assign G_s2[5] = G_s1[9];
	assign P_s2[5] = P_s1[9];
	pref_elem2 PF2_0(.g1(G_s1[10]),.p1(P_s1[10]),.g2(G_s1[11]),.p2(P_s1[11]),.g_out(G_s2[6]),.p_out(P_s2[6]));
	assign G_s2[7] = G_s1[12];
	assign P_s2[7] = P_s1[12];
	assign G_s2[8] = G_s1[13];
	assign P_s2[8] = P_s1[13];
	pref_elem2 PF2_1(.g1(G_s1[14]),.p1(P_s1[14]),.g2(G_s1[15]),.p2(P_s1[15]),.g_out(G_s2[9]),.p_out(P_s2[9]));
	pref_elem2 PF2_2(.g1(G_s1[16]),.p1(P_s1[16]),.g2(G_s1[17]),.p2(P_s1[17]),.g_out(G_s2[10]),.p_out(P_s2[10]));
	assign G_s2[11] = G_s1[18];
	assign P_s2[11] = P_s1[18];

	//The 3-th stage
	wire[5:0] P_s3;
	wire[5:0] G_s3;
	pref_elem1 PF1_0(.g1(G_s2[0]),.p1(P_s2[0]),.g2(G_s2[1]),.p2(P_s2[1]),.g_out(G_s3[0]),.p_out(P_s3[0]));
	pref_elem1 PF1_1(.g1(G_s2[2]),.p1(P_s2[2]),.g2(G_s2[3]),.p2(P_s2[3]),.g_out(G_s3[1]),.p_out(P_s3[1]));
	pref_elem1 PF1_2(.g1(G_s2[4]),.p1(P_s2[4]),.g2(G_s2[5]),.p2(P_s2[5]),.g_out(G_s3[2]),.p_out(P_s3[2]));
	pref_elem2 PF2_3(.g1(G_s2[6]),.p1(P_s2[6]),.g2(G_s2[7]),.p2(P_s2[7]),.g_out(G_s3[3]),.p_out(P_s3[3]));
	pref_elem2 PF2_4(.g1(G_s2[8]),.p1(P_s2[8]),.g2(G_s2[9]),.p2(P_s2[9]),.g_out(G_s3[4]),.p_out(P_s3[4]));
	pref_elem2 PF2_5(.g1(G_s2[10]),.p1(P_s2[10]),.g2(G_s2[11]),.p2(P_s2[11]),.g_out(G_s3[5]),.p_out(P_s3[5]));

	//The 4-th stage
	wire[2:0] P_s4;
	wire[2:0] G_s4;
	pref_elem1 PF1_3(.g1(G_s3[0]),.p1(P_s3[0]),.g2(G_s3[1]),.p2(P_s3[1]),.g_out(G_s4[0]),.p_out(P_s4[0]));
	pref_elem1 PF1_4(.g1(G_s3[2]),.p1(P_s3[2]),.g2(G_s3[3]),.p2(P_s3[3]),.g_out(G_s4[1]),.p_out(P_s4[1]));
	pref_elem2 PF2_6(.g1(G_s3[4]),.p1(P_s3[4]),.g2(G_s3[5]),.p2(P_s3[5]),.g_out(G_s4[2]),.p_out(P_s4[2]));

	//The 5-th stage
	wire[1:0] P_s5;
	wire[1:0] G_s5;
	assign G_s5[0] = G_s4[0];
	assign P_s5[0] = P_s4[0];
	pref_elem1 PF1_5(.g1(G_s4[1]),.p1(P_s4[1]),.g2(G_s4[2]),.p2(P_s4[2]),.g_out(G_s5[1]),.p_out(P_s5[1]));

	//The 6-th stage
	wire[0:0] P_s6;
	wire[0:0] G_s6;
	pref_elem1 PF1_6(.g1(G_s5[0]),.p1(P_s5[0]),.g2(G_s5[1]),.p2(P_s5[1]),.g_out(G_s6[0]),.p_out(P_s6[0]));

	//compensated ports!!!
	assign out0_g = G_s3[5];
	assign out0_p = P_s3[5];
	assign out1_g = G_s4[2];
	assign out1_p = P_s4[2];
	assign out2_g = G_s5[1];
	assign out2_p = P_s5[1];
	assign out3_g = G_s6[0];
	assign out3_p = P_s6[0];
endmodule
