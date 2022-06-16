#include "basic_block.h"

void verilog_template(string module_name, vector<string> ports, int input_ports_num, ofstream& f2)
{
	string tmp;
	//module ***(ports);
	tmp = "module " + module_name + " (";
	for (auto port : ports)
	{
		tmp += port + ", ";
	}
	tmp.erase(tmp.size() - 2, tmp.size());
	tmp += ");";
	f2 << tmp << endl;
	//declare input and output ports;
	for (int i = 0; i < ports.size(); i++)
	{
		if (i < input_ports_num)
		{
			f2 << "\t" << ("input " + ports[i]) << ";" << endl;
		}
		else
		{
			f2 << "\t" << ("output " + ports[i]) << ";" << endl;
		}
	}
}

void function_A(vector<string> ports, int input_ports_num, ofstream& f2)
{
	f2 << "\treg " << ports[input_ports_num] << "," << ports[input_ports_num + 1] << ";" << endl;
	f2 << "\talways@(*)" << endl;
	/*if (input_ports_num == 3)
	{
		f2 << "\t/*synopsys resource FA:";
		f2 << " map_to_module=" << "\"DW01_add\",";
		f2 << " implementation=" << "\"apparch\",";*/
		//f2 << " ops=" << "\"a0\";" << "*/" << endl;
	//}
	/*else
	{
		f2 << "\t/*synopsys resource HA:";
		f2 << " map_to_module=" << "\"DW01_add\",";
		f2 << " implementation=" << "\"apparch\",";*/
		//f2 << " ops=" << "\"a0\";" << "*/" << endl;
	//}
	
	f2 << "\t\t" << ("{" + ports[input_ports_num + 1] + "," + ports[input_ports_num] + "} = ");
	for (int i = 0; i < input_ports_num; i++)
	{
		f2 << ports[i];
		if (i != input_ports_num - 1)
		{
			f2 << " + ";
		}
		else
		{
			f2 << ";" << endl;
		}
	}
	f2 << "endmodule" << endl;
}

void function_mux(vector<string> ports, int input_ports_num, ofstream& f2)
{
	//attribute "reg"
	f2 << "\t" << "reg " << ports[input_ports_num] << ";" << endl;
	//always block
	f2 << "\t" << "always @(*)" << endl;
	f2 << "\t\t" << "begin" << endl;
	f2 << "\t\t" << "if(" << ports[input_ports_num - 1] << " == 1'b1)" << endl;
	f2 << "\t\t\t" << ports[input_ports_num] << " = " << ports[0] << ";" << endl;
	f2 << "\t\t" << "else" << endl;
	f2 << "\t\t\t" << ports[input_ports_num] << " = " << ports[1] << ";" << endl;
	f2 << "\t\t" << "end" << endl;
	f2 << "endmodule" << endl;
}

void function_inf1(vector<string> ports, int input_ports_num, ofstream& f2)
{
	//assign p=a|b; assign g=a&b;
	f2 << "\t" << "assign " << ports[input_ports_num] << " = " << ports[0] << "|" << ports[1] << ";" << endl;
	f2 << "\t" << "assign " << ports[input_ports_num + 1] << " = " << ports[0] << "&" << ports[1] << ";" << endl;
	f2 << "endmodule" << endl;
}

void function_inf2(vector<string> ports, int input_ports_num, ofstream& f2)
{
	//assign p=a; assign g=0;
	f2 << "\t" << "assign " << ports[input_ports_num] << " = " << ports[0] << ";" << endl;
	f2 << "\t" << "assign " << ports[input_ports_num + 1] << " = " << 0 << ";" << endl;
	f2 << "endmodule" << endl;
}

void function_pref_elem1(vector<string> ports, int input_ports_num, ofstream& f2)
{
	//assign g_out=g1|(p1&g2); assign p_out=p1&p2;
	f2 << "\t" << "assign " << ports[input_ports_num] << " = " << ports[0] << "|(" << ports[1] << "&" << ports[2] << ");" << endl;
	f2 << "\t" << "assign " << ports[input_ports_num + 1] << " = " << ports[1] << "&" << ports[3] << ";" << endl;
	f2 << "endmodule" << endl;
}

void function_pref_elem2(vector<string> ports, int input_ports_num, ofstream& f2)
{
	//assign g_out=g1|(p1&g2); assign p_out=p1&p2;
	f2 << "\t" << "assign " << ports[input_ports_num] << " = " << ports[0] << ";" << endl;
	f2 << "\t" << "assign " << ports[input_ports_num + 1] << " = " << ports[1] << "&" << ports[3] << ";" << endl;
	f2 << "endmodule" << endl;
}

void function_pref_elem3(vector<string> ports, int input_ports_num, ofstream& f2)
{
	//assign g_out=p1&g2; assign p_out=p1&p2;
	f2 << "\t" << "assign " << ports[input_ports_num] << " = " << ports[1] << "&" << ports[2] << ";" << endl;
	f2 << "\t" << "assign " << ports[input_ports_num + 1] << " = " << ports[1] << "&" << ports[3] << ";" << endl;
	f2 << "endmodule" << endl;
}


void FA_V()
{
	ofstream f_FA;
	string module_name = "FA";
	vector<string> ports = { "a","b","cin","sum","cout" };
	int input_ports_num = 3;
	f_FA.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_FA);
	function_A(ports, input_ports_num, f_FA);
	f_FA.close();
}

void HA_V()
{
	ofstream f_HA;
	string module_name = "HA"; 
	vector<string> ports = { "a","cin","sum","cout" };
	int input_ports_num = 2;
	f_HA.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_HA);
	function_A(ports, input_ports_num, f_HA);
	f_HA.close();
}

void MUX_V()
{
	ofstream f_MUX;
	string module_name = "MUX";
	vector<string> ports = { "a","b","sel","z" };
	int input_ports_num = 3;
	f_MUX.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_MUX);
	function_mux(ports, input_ports_num, f_MUX);
	f_MUX.close();
}

void INF1_V()
{
	ofstream f_INF1;
	string module_name = "Inf1";
	vector<string> ports = { "a","b","p","g" };
	int input_ports_num = 2;
	f_INF1.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_INF1);
	function_inf1(ports, input_ports_num, f_INF1);
	f_INF1.close();
}

void INF2_V()
{
	ofstream f_INF2;
	string module_name = "Inf2";
	vector<string> ports = { "a","p","g" };
	int input_ports_num = 1;
	f_INF2.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_INF2);
	function_inf2(ports, input_ports_num, f_INF2);
	f_INF2.close();
}

void PREF_ELEM1_V()
{
	ofstream f_PREF_ELEM1;
	string module_name = "pref_elem1";
	vector<string> ports = { "g1","p1","g2","p2","g_out","p_out" };
	int input_ports_num = 4;
	f_PREF_ELEM1.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_PREF_ELEM1);
	function_pref_elem1(ports, input_ports_num, f_PREF_ELEM1);
	f_PREF_ELEM1.close();
}

void PREF_ELEM2_V()
{
	ofstream f_PREF_ELEM2;
	string module_name = "pref_elem2";
	vector<string> ports = { "g1","p1","g2","p2","g_out","p_out" };
	int input_ports_num = 4;
	f_PREF_ELEM2.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_PREF_ELEM2);
	function_pref_elem2(ports, input_ports_num, f_PREF_ELEM2);
	f_PREF_ELEM2.close();
}

void PREF_ELEM3_V()
{
	ofstream f_PREF_ELEM3;
	string module_name = "pref_elem3";
	vector<string> ports = { "g1","p1","g2","p2","g_out","p_out" };
	int input_ports_num = 4;
	f_PREF_ELEM3.open((module_name + ".v").c_str());
	verilog_template(module_name, ports, input_ports_num, f_PREF_ELEM3);
	function_pref_elem3(ports, input_ports_num, f_PREF_ELEM3);
	f_PREF_ELEM3.close();
}


