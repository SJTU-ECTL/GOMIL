#include "fast_mult.h"
#include "Compress_Tree.h"
//int wordlength = 8;
//int stage_number = 4;
int Compress_Tree_num = 0;
int Prefex_Tree_num = 0;
int CSL_num = 0;
int splits_num = 5;
int cssa_skip_points_num = 0;
void verilog_template_FM(string module_name, vector<string> ports, ofstream& f2)
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
	f2 << "\tinput clock;" << endl;
	f2 << "\tinput[" << wordlength - 1 << ":" << 0 << "] " << ports[0] << ";" << endl;
	f2 << "\tinput[" << wordlength - 1 << ":" << 0 << "] " << ports[1] << ";" << endl;
	f2 << "\toutput[" << 2 * wordlength - 1 << ":" << 0 << "] " << ports[3] << ";" << endl;
	f2 << endl;
}

void Instantiate_Compress_Tree(vector<string> ports, ofstream& f2)
{
	vector<string> real_ports;
	stringstream ss;
	real_ports.push_back(ports[0]);
	real_ports.push_back(ports[1]);
	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		string tmp;
		ss << "data" << i << "_s" << stage_number;
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	f2 << "\tCompress_Tree C" << Compress_Tree_num << "(";
	for (int i = 0; i < real_ports.size(); i++)
	{
		f2 << "." << real_ports[i] << "(" << ports[i] << ")";
		if (i != real_ports.size() - 1)
		{
			f2 << ",";
		}
	}
	f2 << ");" << endl;
	Compress_Tree_num++;
}

void Instantiate_Prefex_Tree(vector<string> ports, ofstream& f2)
{
	vector<string> real_ports;
	stringstream ss;
	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		string tmp;
		ss << "in" << i;
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	for (int i = 0; i < splits_num - 1; i++)
	{
		string tmp;
		ss << "out" << i << "_g";
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
		ss << "out" << i << "_p";
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	for (int i = 0; i < cssa_skip_points_num; i++)
	{
		string tmp;
		ss << "out_cssa" << i << "_g";
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
		ss << "out_cssa" << i << "_p";
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	f2 << "\tPrefex_Tree P" << Prefex_Tree_num << "(";
	for (int i = 0; i < real_ports.size(); i++)
	{
		f2 << "." << real_ports[i] << "(" << ports[i] << ")";
		if (i != real_ports.size() - 1)
		{
			f2 << ",";
		}
	}
	f2 << ");" << endl;
	Prefex_Tree_num++;
}

void Instantiate_CSL(vector<string> ports, ofstream& f2)
{
	vector<string> real_ports;
	stringstream ss;
	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		string tmp;
		ss << "in" << i;
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	for (int i = 0; i < splits_num - 1; i++)
	{
		string tmp;
		ss << "out" << i << "_g";
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	for (int i = 0; i < cssa_skip_points_num; i++)
	{
		string tmp;
		ss << "out_cssa" << i << "_g";
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
		ss << "out_cssa" << i << "_p";
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	for (int i = 0; i < 2 * wordlength; i++)
	{
		string tmp;
		ss << "out" << i;
		ss >> tmp;
		ss.clear();   ss.str("");
		real_ports.push_back(tmp);
	}
	f2 << "\tCSL CSL" << CSL_num << "(";
	for (int i = 0; i < real_ports.size(); i++)
	{
		f2 << "." << real_ports[i] << "(" << ports[i] << ")";
		if (i != real_ports.size() - 1)
		{
			f2 << ",";
		}
	}
	f2 << ");" << endl;
	CSL_num++;
}


void function_fast_multiplier(vector<string> ports, ofstream& f2)
{
	//Instantiate a Compress Tree
	vector<int> output_ports_size;
	get_output_ports_size(output_ports_size);
	vector<string> ins_ports_C;
	ins_ports_C.push_back(ports[0]);
	ins_ports_C.push_back(ports[1]);
	stringstream ss;
	//declare ports
	f2 << endl;
	for (int i = 0; i < output_ports_size.size(); i++)
	{
		string tmp;
		ss << "out" << i << "_C";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_C.push_back(tmp);
		f2 << "\twire[" << output_ports_size[i] - 1 << ":" << 0 << "] " << *(ins_ports_C.end() - 1) << ";" << endl;
	}
	Instantiate_Compress_Tree(ins_ports_C, f2);

	//Instantiate a Prefex Tree
	vector<string> ins_ports_P;
	ins_ports_C.erase(ins_ports_C.begin());
	ins_ports_C.erase(ins_ports_C.begin());
	ins_ports_P = ins_ports_C;
	//declare ports
	f2 << endl;
	for (int i = 0; i < splits_num - 1; i++)
	{
		string tmp;
		ss << "out" << i << "_g_P";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_P.push_back(tmp);
		f2 << "\twire " << *(ins_ports_P.end() - 1) << ";" << endl;
		ss << "out" << i << "_p_P";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_P.push_back(tmp);
		f2 << "\twire " << *(ins_ports_P.end() - 1) << ";" << endl;
		
		//f2 << "\twire out" << i << "_g_P;" << endl;

	}
	for (int i = 0; i < cssa_skip_points_num; i++)
	{
		string tmp;
		ss << "out_cssa" << i << "_g_P";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_P.push_back(tmp);
		f2 << "\twire " << *(ins_ports_P.end() - 1) << ";" << endl;
		ss << "out_cssa" << i << "_p_P";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_P.push_back(tmp);
		f2 << "\twire " << *(ins_ports_P.end() - 1) << ";" << endl;

		//f2 << "\twire out" << i << "_g_P;" << endl;

	}
	Instantiate_Prefex_Tree(ins_ports_P, f2);

	//Instantiate a CSL
	f2 << endl;
	vector<string> ins_ports_CSL;
	ins_ports_CSL = ins_ports_C;
	for (int i = 0; i < splits_num - 1; i++)
	{
		string tmp;
		ss << "out" << i << "_g_P";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_CSL.push_back(tmp);
	}
	for (int i = 0; i < cssa_skip_points_num; i++)
	{
		string tmp;
		ss << "out_cssa" << i << "_g_P";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_CSL.push_back(tmp);
		ss << "out_cssa" << i << "_p_P";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_CSL.push_back(tmp);
	}
	for (int i = 0; i < 2 * wordlength; i++)
	{
		string tmp;
		ss << "out" << "[" << i << "]";
		ss >> tmp;
		ss.clear();   ss.str("");
		ins_ports_CSL.push_back(tmp);
	}
	Instantiate_CSL(ins_ports_CSL, f2);
	f2 << "endmodule" << endl;
}

void FAST_MULT_V()
{
	ofstream f_FAST_MULT;
	stringstream ss;
	vector<int> output_ports_size;
	string module_name = "fast_mult";
	int input_ports_num = 2;
	vector<string> ports = { "a","b" };
	f_FAST_MULT.open((module_name + ".v").c_str());
	ports.push_back("clock");
	ports.push_back("out");
	get_output_ports_size(output_ports_size);
	verilog_template_FM(module_name, ports, f_FAST_MULT);
	function_fast_multiplier(ports, f_FAST_MULT);
	f_FAST_MULT.close();
}
