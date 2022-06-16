module fast_mult (a, b, clock, out);
	input clock;
	input[9:0] a;
	input[9:0] b;
	output[19:0] out;


	wire[1:0] out0_C;
	wire[1:0] out1_C;
	wire[1:0] out2_C;
	wire[1:0] out3_C;
	wire[1:0] out4_C;
	wire[1:0] out5_C;
	wire[1:0] out6_C;
	wire[1:0] out7_C;
	wire[1:0] out8_C;
	wire[1:0] out9_C;
	wire[1:0] out10_C;
	wire[0:0] out11_C;
	wire[0:0] out12_C;
	wire[1:0] out13_C;
	wire[0:0] out14_C;
	wire[0:0] out15_C;
	wire[0:0] out16_C;
	wire[0:0] out17_C;
	wire[0:0] out18_C;
	Compress_Tree C0(.a(a),.b(b),.data0_s5(out0_C),.data1_s5(out1_C),.data2_s5(out2_C),.data3_s5(out3_C),.data4_s5(out4_C),.data5_s5(out5_C),.data6_s5(out6_C),.data7_s5(out7_C),.data8_s5(out8_C),.data9_s5(out9_C),.data10_s5(out10_C),.data11_s5(out11_C),.data12_s5(out12_C),.data13_s5(out13_C),.data14_s5(out14_C),.data15_s5(out15_C),.data16_s5(out16_C),.data17_s5(out17_C),.data18_s5(out18_C));

	wire out0_g_P;
	wire out0_p_P;
	wire out1_g_P;
	wire out1_p_P;
	wire out2_g_P;
	wire out2_p_P;
	wire out3_g_P;
	wire out3_p_P;
	Prefex_Tree P0(.in0(out0_C),.in1(out1_C),.in2(out2_C),.in3(out3_C),.in4(out4_C),.in5(out5_C),.in6(out6_C),.in7(out7_C),.in8(out8_C),.in9(out9_C),.in10(out10_C),.in11(out11_C),.in12(out12_C),.in13(out13_C),.in14(out14_C),.in15(out15_C),.in16(out16_C),.in17(out17_C),.in18(out18_C),.out0_g(out0_g_P),.out0_p(out0_p_P),.out1_g(out1_g_P),.out1_p(out1_p_P),.out2_g(out2_g_P),.out2_p(out2_p_P),.out3_g(out3_g_P),.out3_p(out3_p_P));

	CSL CSL0(.in0(out0_C),.in1(out1_C),.in2(out2_C),.in3(out3_C),.in4(out4_C),.in5(out5_C),.in6(out6_C),.in7(out7_C),.in8(out8_C),.in9(out9_C),.in10(out10_C),.in11(out11_C),.in12(out12_C),.in13(out13_C),.in14(out14_C),.in15(out15_C),.in16(out16_C),.in17(out17_C),.in18(out18_C),.out0_g(out0_g_P),.out1_g(out1_g_P),.out2_g(out2_g_P),.out3_g(out3_g_P),.out0(out[0]),.out1(out[1]),.out2(out[2]),.out3(out[3]),.out4(out[4]),.out5(out[5]),.out6(out[6]),.out7(out[7]),.out8(out[8]),.out9(out[9]),.out10(out[10]),.out11(out[11]),.out12(out[12]),.out13(out[13]),.out14(out[14]),.out15(out[15]),.out16(out[16]),.out17(out[17]),.out18(out[18]),.out19(out[19]));
endmodule
