#pragma warning(disable : 4996)
#include "Compress_Tree.h"
#include <cstring>
int wordlength = 10;
int stage_number = 5;
int full_adder_num = 0;
int half_adder_num = 0;
int mux_num = 0;
string filename1 = "..//Tune_WL//10_10.txt";
void verilog_template_PT(string module_name, vector<string> ports, int input_ports_num, ofstream& f2)
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
			f2 << "\t" << "input" << "[" << wordlength - 1 << ":" << 0 << "] " << ports[i] << ";" << endl;
		}
		else
		{
			if (i == input_ports_num | i == ports.size() - 1)
			{
				f2 << "\t" << ("output " + ports[i]) << ";" << endl;
			}
			else
			{
				f2 << "\t" << "output" << "[" << (wordlength - 1 - abs(i - input_ports_num - wordlength + 1)) << ":" << 0 << "] " << ports[i] << ";" << endl;
			}
		}
	}
}


void verilog_template_CPT(string module_name, vector<string> ports, int input_ports_num, ofstream& f2, vector<int> output_ports_size)
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
			f2 << "\t" << "input" << "[" << wordlength - 1 << ":" << 0 << "] " << ports[i] << ";" << endl;
		}
		else
		{
			//if (output_ports_size[i - 2] == 2)
			//{
			f2 << "\t" << "output" << "[" << output_ports_size[i - 2] - 1 << ":" << 0 << "] " << ports[i] << ";" << endl;
			//}
			/*else
			{
				f2 << "\t" << "output " << ports[i] << ";" << endl;
			}*/
		}
	}
}

void function_production(vector<string> ports, int input_ports_num, ofstream& f2)
{
	//(0,1),(2,3),(3,4) ..(7,8),(8,7)
	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		for (int j = 0; j < (wordlength - abs(i - wordlength + 1)); j++)
		{
			if (i == 0 | i == 2*wordlength - 2)
			{
				f2 << "\tassign " << ports[input_ports_num + i] << " = " << ports[0] << "[" << (wordlength - i / 2 - 1) << "]";
				f2 << " & " << ports[1] << "[" << (wordlength - 1 - i / 2) << "];" << endl;
			}
			else
			{
				if (i >= 0 && i <= wordlength - 1)
				{
					f2 << "\tassign " << ports[input_ports_num + i] << "[" << j << "]" << " = " << ports[0] << "[" << (wordlength - i - 1 + j) << "]";
					f2 << " & " << ports[1] << "[" << (wordlength - 1 - j) << "];" << endl;
				}
				else
				{    
					f2 << "\tassign " << ports[input_ports_num + i] << "[" << j << "]" << " = " << ports[0] << "[" << j << "]";
					f2 << " & " << ports[1] << "[" << (2 * wordlength - i - 2 - j) << "];" << endl;
				}
			}
		}
	}
	f2 << "endmodule" << endl;
}

void update_remain_vector(vector<int>& output_ports_size, vector<int>& fa_V, vector<int>& ha_V, vector<int>& remain_V)
{
	for (int i = 0; i < fa_V.size(); i++)
	{
		if (i != fa_V.size() - 1)
		{
			remain_V.push_back(output_ports_size[i] - fa_V[i] - ha_V[i] - fa_V[i + 1] - ha_V[i + 1]);
		}
		else
		{
			remain_V.push_back(output_ports_size[i] - fa_V[i] - ha_V[i]);
		}
	}
}

void Instantiate_MUX(vector<string> ports, ofstream& f2)
{
	f2 << "\tMUX " << "M" << mux_num << "(" << ".a(" << ports[0] << ")," << ".b(" << ports[1] << ")," << ".sel(" << ports[2] << "),";
	f2 << ".z(" << ports[3] << "));" << endl;
	mux_num++;
}

void Instantiate_Full_Adder(vector<string> ports, ofstream& f2)
{
	
	//f2 << "\tassign {" << ports[4] << "," << ports[3] << "}=" << ports[0] << "+" << ports[1] << "+" << ports[2] << ";" << endl;
	/*f2 << "\t//synopsys dc_script_begin" << endl;
	f2 << "\t//set_implementation apparch " << "F" << full_adder_num << endl;
	f2 << "\t//set_dont_touch F" << full_adder_num << endl;
	f2 << "\t//synopsys dc_script_end" << endl;
	f2 << "\t//instantiate DW01_add" << endl;*/
	/*f2 << "\tDW01_add " <<"#("<<1<<") "<< "F" << full_adder_num << "(" << ".A(" << ports[0] << ")," << ".B(" << ports[1] << ")," << ".CI(" << ports[2] << "),";
	f2 << ".SUM(" << ports[3] << ")," << ".CO(" << ports[4] << "));" << endl;*/
	f2 << "\tFA " << "F" << full_adder_num << "(" << ".a(" << ports[0] << ")," << ".b(" << ports[1] << ")," << ".cin(" << ports[2] << "),";
	f2 << ".sum(" << ports[3] << ")," << ".cout(" << ports[4] << "));" << endl;
	full_adder_num++;
}

void Instantiate_Half_Adder(vector<string> ports, ofstream& f2)
{
	//f2 << "\tassign {" << ports[3] << "," << ports[2] << "}=" << ports[0] << "+" << ports[1] << ";" << endl;
	f2 << "\tHA " << "H" << half_adder_num << "(" << ".a(" << ports[0] << ")," << ".cin(" << ports[1] << "),";
	f2 << ".sum(" << ports[2] << ")," << ".cout(" << ports[3] << "));" << endl;
	half_adder_num++;
}


void function_compress_tree(vector<string> ports, int input_ports_num, ofstream& f2)
{
	
	stringstream ss;
	/*use a production block*/
	f2 << endl;
	f2 << "\t//pre-processing block : production" << endl;
	//wire output variables of module "production"
	vector<string> ins_ports = { "a","b" };

	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		/*if (i == 0 | i == 2 * wordlength - 2)
		{
			f2 << "\t" << "wire out" << i << ";" << endl;
		}*/
		string tmp;
		ss << "out" << i;
		ss >> tmp;
		ss.clear();   ss.str("");
		f2 << "\t" << "wire" << "[" << (wordlength - 1 - abs(i - wordlength + 1)) << ":" << 0 << "] " << tmp << ";" << endl;
		ins_ports.push_back(tmp);
	}
	//instantiate a production block
	string instance_name = "PD0";
	f2 << "\tproduction " << instance_name << "(";
	//input/output ports
	vector<string> production_ports = { "a","b" };
	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		string tmp;
		ss << "out" << i;
		ss >> tmp;
		ss.clear();
		production_ports.push_back(tmp);
	}
	for (int i = 0; i < ports.size(); i++)
	{
		f2 << "." << production_ports[i] << "(" << ins_ports[i] << ")";
		if (i != ports.size() - 1)
		{
			f2 << ",";
		}
	}
	f2 << ");" << endl << endl;

	//Stages of compress tree
	ifstream f_txt;
	f_txt.open(filename1.c_str());
	string txt_line;
	for (int i = 0; i < stage_number; i++)
	{
		f2 << endl;
		vector<int> output_ports_size;
		vector<int> last_stage_output_ports_size;
		vector<int> fa_V, ha_V;
		vector<int> remain_V;
		getline(f_txt, txt_line);
		split(output_ports_size, fa_V, ha_V, txt_line);
		update_remain_vector(output_ports_size, fa_V, ha_V, remain_V);
		f2 << "\t//****The " << i + 1 << "th stage****" << endl;
		//declare wire ports
		for (int j = 0; j < output_ports_size.size(); j++)
		{
			//if (output_ports_size[j] != 1)
			//{
			f2 << "\t" << "wire" << "[" << output_ports_size[j] - 1 << ":" << 0 << "] " << "data" << j << "_s" << i + 1 << ";" << endl;
			//}
			/*else
			{
				f2 << "\t" << "wire " << "data" << j << "_s" << i + 1 << ";" << endl;
			}*/
		}
		//function block
		for (int j = 0; j < output_ports_size.size(); j++)
		{
			if (i == 0)
			{
				//full adder
				for (int k = 0; k < fa_V[j]; k++)
				{
					stringstream ss;
					string port1, port2, port3, output_port1, output_port2;
					ss << "out" << j << "[" << 3 * k << "]";
					ss >> port1;
					ss.clear();
					ss << "out" << j << "[" << 3 * k + 1 << "]";
					ss >> port2;
					ss.clear();
					ss << "out" << j << "[" << 3 * k + 2 << "]";
					ss >> port3;
					ss.clear();
					ss << "data" << j <<"_s1"<< "[" << k << "]";
					ss >> output_port1;
					ss.clear();
					ss << "data" << j - 1 << "_s1" << "[" << k + fa_V[j - 1] + ha_V[j - 1] + remain_V[j - 1] << "]";
					ss >> output_port2;
					ss.clear();
					vector<string> ports = { port1,port2,port3,output_port1,output_port2 };
					Instantiate_Full_Adder(ports, f2);
				}
				//half adder
				for (int k = 0; k < ha_V[j]; k++)
				{
					stringstream ss;
					string port1, port2, output_port1, output_port2;
					ss << "out" << j << "[" << 3 * fa_V[j] + 2 * k << "]";
					ss >> port1;
					ss.clear();
					ss << "out" << j << "[" << 3 * fa_V[j] + 2 * k + 1 << "]";
					ss >> port2;
					ss.clear();
					ss << "data" << j << "_s1" << "[" << fa_V[j] + k << "]";
					ss >> output_port1;
					ss.clear();
					ss << "data" << j - 1 << "_s1" << "[" << k + fa_V[j - 1] + ha_V[j - 1] + fa_V[j] + remain_V[j - 1] << "]";
					ss >> output_port2;
					ss.clear();
					vector<string> ports = { port1,port2,output_port1,output_port2 };
					Instantiate_Half_Adder(ports, f2);
				}
				
				//remaining ports
				for (int k = 0; k < remain_V[j]; k++)
				{
					
					f2 << "\tassign " << "data" << j << "_s1" << "[" << fa_V[j] + ha_V[j] + k << "] = " << "out" << j << "[" << 3 * fa_V[j] + 2 * ha_V[j] + k << "];" << endl;
				}
			}
			else
			{
				//full adder
				for (int k = 0; k < fa_V[j]; k++)
				{
					stringstream ss;
					string port1, port2, port3, output_port1, output_port2;
					ss << "data" << j << "_s" << i << "[" << 3 * k << "]";
					ss >> port1;
					ss.str("");
					ss.clear();
					ss << "data" << j << "_s" << i << "[" << 3 * k + 1 << "]";
					ss >> port2;
					ss.str("");
					ss.clear();
					ss << "data" << j << "_s" << i << "[" << 3 * k + 2 << "]";
					ss >> port3;
					ss.str("");
					ss.clear();
					ss << "data" << j << "_s" << i + 1 << "[" << k << "]";
					ss >> output_port1;
					ss.str("");
					ss.clear();
					ss << "data" << j - 1 << "_s" << i + 1 << "[" << k + fa_V[j - 1] + ha_V[j - 1] + remain_V[j - 1] << "]";
					ss >> output_port2;
					ss.clear();
					vector<string> ports = { port1,port2,port3,output_port1,output_port2 };
					Instantiate_Full_Adder(ports, f2);
				}
				//half adder
				for (int k = 0; k < ha_V[j]; k++)
				{
					stringstream ss;
					string port1, port2, output_port1, output_port2;
					ss << "data" << j << "_s" << i << "[" << 3 * fa_V[j] + 2 * k << "]";
					ss >> port1;
					ss.clear();
					ss << "data" << j << "_s" << i << "[" << 3 * fa_V[j] + 2 * k + 1 << "]";
					ss >> port2;
					ss.clear();
					ss << "data" << j << "_s" << i + 1 << "[" << fa_V[j] + k << "]";
					ss >> output_port1;
					ss.clear();
					ss << "data" << j - 1 << "_s" << i + 1 << "[" << k + fa_V[j - 1] + ha_V[j - 1] + fa_V[j] + remain_V[j - 1] << "]";
					ss >> output_port2;
					ss.clear();
					vector<string> ports = { port1,port2,output_port1,output_port2 };
					Instantiate_Half_Adder(ports, f2);
				}

				//remaining ports
				for (int k = 0; k < remain_V[j]; k++)
				{
					f2 << "\tassign " << "data" << j << "_s" << i + 1 << "[" << fa_V[j] + ha_V[j] + k << "] = " << "data" << j << "_s" << i << "[" << 3 * fa_V[j] + 2 * ha_V[j] + k << "];" << endl;
				}

			}
			
		}
	}
	f_txt.close();
	f2 << "endmodule" << endl;
}

void PRODUCTION_V()
{
	stringstream ss;
	ofstream f_PRODUCTION;
	string module_name = "production";
	int input_ports_num = 2;
	vector<string> ports = { "a","b" };
	f_PRODUCTION.open((module_name + ".v").c_str());
	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		string tmp;
		ss << "out" << i;
		ss >> tmp;
		ss.clear();
		ports.push_back(tmp);
	}
	verilog_template_PT(module_name, ports, input_ports_num, f_PRODUCTION);
	function_production(ports, input_ports_num, f_PRODUCTION);
	f_PRODUCTION.close();
}

void split(vector<int>& output_ports_size, vector<int>& fa_V, vector<int>& ha_V, string target_str)
{
	stringstream ss;
	//target_str.data()
	char* sp = strtok(const_cast<char*>(target_str.c_str()), " ");
	while (sp != NULL)
	{
		string tmp = string(sp);
		float port_size;
		float fa, ha;
		string test = tmp.substr(tmp.find_last_of("/") + 1, tmp.size() - tmp.find_last_of("/") - 1);
		ss << test;
		ss >> port_size;
		ss.str("");
		ss.clear();
		tmp.erase(tmp.begin() + tmp.find_last_of("/"), tmp.end());
		ss << tmp.substr(tmp.find_last_of("/") + 1, tmp.size() - tmp.find_last_of("/") - 1);
		ss >> ha;
		ss.str("");
		ss.clear();
		tmp.erase(tmp.begin() + tmp.find_last_of("/"), tmp.end());
		ss << tmp.substr(tmp.find_last_of(":") + 1, tmp.size() - tmp.find_last_of(":") - 1);
		ss >> fa;
		ss.str("");
		ss.clear();
		tmp.erase(tmp.begin() + tmp.find_last_of(":"), tmp.end());
		if (port_size != 0)
		{
			output_ports_size.push_back(port_size);
			fa_V.push_back(fa);
			ha_V.push_back(ha);
		}
		sp = strtok(NULL, " ");
	}

}

void get_output_ports_size(vector<int>& output_ports_size)
{
	ifstream f_txt;
	f_txt.open(filename1.c_str());
	string tmp;
	vector<int> fa_V, ha_V;
	for (int i = 0; i < stage_number; i++)
	{
		getline(f_txt, tmp);
	}
	split(output_ports_size, fa_V, ha_V, tmp);
	f_txt.close();
}

void COMPRESS_TREE_V()
{
	ofstream f_COMPRESS_TREE;
	stringstream ss;
	vector<int> output_ports_size;
	string module_name = "Compress_Tree";
	int input_ports_num = 2;
	vector<string> ports = { "a","b" };
	f_COMPRESS_TREE.open((module_name + ".v").c_str());
	for (int i = 0; i < 2 * wordlength - 1; i++)
	{
		string tmp;
		ss << "data" << i << "_s" << stage_number;
		ss >> tmp;
		ss.clear();
		ports.push_back(tmp);
	}
	get_output_ports_size(output_ports_size);
	verilog_template_CPT(module_name, ports, input_ports_num, f_COMPRESS_TREE, output_ports_size);
	function_compress_tree(ports, input_ports_num, f_COMPRESS_TREE);
	f_COMPRESS_TREE.close();
}


