#include "Compress_Tree.h"
#include "CSL.h"
#include "basic_block.h"

/*32*32*/
//vector<vector<int>> splits = { {0,7},{8,15},{16,22},{23,28},{29,36},{37,44},{45,52},{53,60},{61,62} };
//vector<int> cssa_skip_points = { 4,12,20,26,33,41,49,57,-1 };

/*20*20*/
vector<vector<int>> splits = { {0,5},{6,13},{14,21},{22,29},{30,36},{37,38} };
vector<int> cssa_skip_points = { 2,10,18,26,34,-1 };

/*16*16*/
//vector<vector<int>> splits = { {0,7},{8,15},{16,21},{22,28},{29,31} };
//vector<int> cssa_skip_points = { 4,12,19,25,-1 };

/*10*10*/
//vector<vector<int>> splits = { {0,3},{4,7},{8,12},{13,15},{16,18} };
//vector<int> cssa_skip_points = { -1,-1,-1,-1,-1 };

/*8*8*/
//vector<vector<int>> splits = { {0,7},{8,12},{13,14}};
//vector<int> cssa_skip_points = { 4,10,-1 };

/*7*7*/
//vector<vector<int>> splits = { {0,2},{3,6},{7,10},{11,12} };
//vector<int> cssa_skip_points = { -1,-1,-1,-1};

/*6*6*/
//vector<vector<int>> splits = { {0,3},{4,8},{9,10}};
//vector<int> cssa_skip_points = { -1,-1,-1 };

/*5*5*/
// vector<vector<int>> splits = { {0,3},{4,5},{6,8}};
// vector<int> cssa_skip_points = { -1,-1,-1};


void verilog_template_CSL(string module_name, vector<string> ports, int input_ports_num, ofstream& f2, vector<int> input_ports_size)
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
			if (i < input_ports_size.size())
			{
				f2 << "\t" << "input" << "[" << input_ports_size[i] - 1 << ":" << 0 << "] " << ports[i] << ";" << endl;
			}
			else
			{
				f2 << "\tinput " << ports[i] << ";" << endl;
			}
		}
		else
		{
			//if (output_ports_size[i - 2] == 2)
			//{
			f2 << "\t" << "output " << ports[i] << ";" << endl;
			//}
			/*else
			{
				f2 << "\t" << "output " << ports[i] << ";" << endl;
			}*/
		}
	}
}

void function_csl(vector<string> ports, vector<int> input_ports_size, int input_ports_num, ofstream& f2)
{
	f2 << endl;
	int flag = 0;
	for (int i = splits.size() - 1; i >= 0; i--)
	{
		
		f2 << endl;
		vector<pair<int,int>> tmp_ports_size;//the number of sum bits
		vector<vector<vector<string>>> tmp_ports;
		string select_port;
		//select port
		if (i == splits.size() - 1)
		{
			select_port = "1'b0";
		}
		else
		{
			//select_port = ports[input_ports_size.size() + i - 1];
			select_port = ports[input_ports_size.size() + splits.size() - i - 2];
		}
		//declare ports
		for (int j = splits[i][1]; j >= splits[i][0]; j--)
		{
			string tmp0, tmp1;
			string outs_tmp0, outs_tmp1, outc_tmp0, outc_tmp1;
			stringstream ss;
			ss << "out" << j + 1 << "_c0";
			ss >> tmp0;
			ss.clear(); ss.str("");
			ss << "out" << j + 1 << "_c1";
			ss >> tmp1;
			ss.clear(); ss.str("");
			ss << "out" << j << "_c0";
			ss >> outc_tmp0;
			ss.clear(); ss.str("");
			ss << "out" << j << "_c1";
			ss >> outc_tmp1;
			ss.clear(); ss.str("");
			ss << "out" << j << "_s0";
			ss >> outs_tmp0;
			ss.clear(); ss.str("");
			ss << "out" << j << "_s1";
			ss >> outs_tmp1;
			ss.clear(); ss.str("");
			vector<vector<string>> tmp_tmp_ports;
			if (j == splits[i][1])
			{
				if (input_ports_size[j] == 1)
				{
					f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
					f2 << "\twire out" << j << "_c1;" << endl;
					tmp_tmp_ports.push_back({ ports[j],outs_tmp0 });
					tmp_tmp_ports.push_back({ ports[j],"1'b1" ,outs_tmp1,outc_tmp1 });
					tmp_ports_size.push_back(make_pair(1, 2));
				}
				else if (input_ports_size[j] == 2)
				{
					f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
					f2 << "\twire out" << j << "_c1, " << "out" << j << "_c0;" << endl;
					tmp_tmp_ports.push_back({ ports[j] + "[0]",ports[j] + "[1]",outs_tmp0,outc_tmp0 });
					tmp_tmp_ports.push_back({ ports[j] + "[0]",ports[j] + "[1]","1'b1",outs_tmp1,outc_tmp1 });
					tmp_ports_size.push_back(make_pair(2, 3));
				}
			}
			else
			{
				
				if (input_ports_size[j] == 1)
				{

					if (j == cssa_skip_points[i] - 1 && cssa_skip_points[i] != -1)
					{
						f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
						f2 << "\twire out" << j << "_c1, " << "out" << j << "_c0;" << endl;
						string tmp;
						ss << "cssa" << flag;
						ss >> tmp;
						ss.clear();   ss.str("");
						f2 << "\twire " << tmp << ";" << endl;
						int cssa_skip_point_index;
						cssa_skip_point_index = input_ports_size.size() + splits.size() + 2 * flag - 1;
						tmp_tmp_ports.push_back({ ports[j],ports[cssa_skip_point_index],outs_tmp0 ,outc_tmp0 });
						f2 << "\tassign cssa" << flag << " = " << ports[cssa_skip_point_index] << "|" << ports[cssa_skip_point_index + 1] << ";" << endl;
						tmp_tmp_ports.push_back({ ports[j],tmp,outs_tmp1 ,outc_tmp1 });
						tmp_ports_size.insert(tmp_ports_size.begin(), make_pair(2, 2));
					}
					else
					{
						if (tmp_ports_size[0] == make_pair(1, 2))
						{
							f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
							f2 << "\twire out" << j << "_c1;" << endl;
							tmp_tmp_ports.push_back({ ports[j],outs_tmp0 });
							tmp_tmp_ports.push_back({ ports[j],tmp1,outs_tmp1,outc_tmp1 });
							tmp_ports_size.insert(tmp_ports_size.begin(), make_pair(1, 2));
						}
						else
						{
							f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
							f2 << "\twire out" << j << "_c1, " << "out" << j << "_c0;" << endl;
							tmp_tmp_ports.push_back({ ports[j],tmp0,outs_tmp0,outc_tmp0 });
							tmp_tmp_ports.push_back({ ports[j],tmp1,outs_tmp1,outc_tmp1 });
							tmp_ports_size.insert(tmp_ports_size.begin(), make_pair(2, 2));
						}
					}
					
					
				}
				else if (input_ports_size[j] == 2)
				{
					if (j == cssa_skip_points[i] - 1 && cssa_skip_points[i] != -1)
					{
						f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
						f2 << "\twire out" << j << "_c1, " << "out" << j << "_c0;" << endl;
						string tmp;
						ss << "cssa" << flag;
						ss >> tmp;
						ss.clear();   ss.str("");
						f2 << "\twire " << tmp << ";" << endl;
						int cssa_skip_point_index;
						cssa_skip_point_index = input_ports_size.size() + splits.size() + 2 * flag - 1;
						tmp_tmp_ports.push_back({ ports[j] + "[0]",ports[j] + "[1]",ports[cssa_skip_point_index],outs_tmp0 ,outc_tmp0 });
						f2 << "\tassign cssa" << flag << " = " << ports[cssa_skip_point_index] << "|" << ports[cssa_skip_point_index + 1] << ";" << endl;
						tmp_tmp_ports.push_back({ ports[j]+"[0]",ports[j] + "[1]",tmp,outs_tmp1 ,outc_tmp1 });
						tmp_ports_size.insert(tmp_ports_size.begin(), make_pair(3, 3));
					}
					else
					{
						if (tmp_ports_size[0] == make_pair(1, 2))
						{
							f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
							f2 << "\twire out" << j << "_c1, " << "out" << j << "_c0;" << endl;
							tmp_tmp_ports.push_back({ ports[j] + "[0]",ports[j] + "[1]",outs_tmp0,outc_tmp0 });
							tmp_tmp_ports.push_back({ ports[j] + "[0]",ports[j] + "[1]",tmp1,outs_tmp1,outc_tmp1 });
							tmp_ports_size.insert(tmp_ports_size.begin(), make_pair(2, 3));
						}
						else
						{
							f2 << "\twire out" << j << "_s1, " << "out" << j << "_s0;" << endl;
							f2 << "\twire out" << j << "_c1, " << "out" << j << "_c0;" << endl;
							tmp_tmp_ports.push_back({ ports[j] + "[0]",ports[j] + "[1]",tmp0,outs_tmp0,outc_tmp0 });
							tmp_tmp_ports.push_back({ ports[j] + "[0]",ports[j] + "[1]",tmp1,outs_tmp1,outc_tmp1 });
							tmp_ports_size.insert(tmp_ports_size.begin(), make_pair(3, 3));
						}
					}
					
				}
			}

			tmp_ports.insert(tmp_ports.begin(), tmp_tmp_ports);
		}

		//function block
		for (int j = tmp_ports.size() - 1; j >= 0; j--)
		{
			string tmp_output_port;
			stringstream ss;
			ss << "out" << j + splits[i][0] + 1;
			ss >> tmp_output_port;
			ss.clear();   ss.str("");

			if (tmp_ports_size[j] == make_pair(1, 2))
			{
				f2 << "\tassign " << tmp_ports[j][0][1] << " = " << tmp_ports[j][0][0] << ";" << endl;
				Instantiate_Half_Adder(tmp_ports[j][1], f2);
				Instantiate_MUX({ tmp_ports[j][1][2],tmp_ports[j][0][1],select_port,tmp_output_port }, f2);
			}
			else if (tmp_ports_size[j] == make_pair(2, 2))
			{
				Instantiate_Half_Adder(tmp_ports[j][0], f2);
				Instantiate_Half_Adder(tmp_ports[j][1], f2);
				Instantiate_MUX({ tmp_ports[j][1][2],tmp_ports[j][0][2],select_port,tmp_output_port }, f2);
			}
			else if (tmp_ports_size[j] == make_pair(2, 3))
			{
				Instantiate_Half_Adder(tmp_ports[j][0], f2);
				Instantiate_Full_Adder(tmp_ports[j][1], f2);
				Instantiate_MUX({ tmp_ports[j][1][3],tmp_ports[j][0][2],select_port,tmp_output_port }, f2);
			}
			else if (tmp_ports_size[j] == make_pair(3, 3))
			{
				Instantiate_Full_Adder(tmp_ports[j][0], f2);
				Instantiate_Full_Adder(tmp_ports[j][1], f2);
				Instantiate_MUX({ tmp_ports[j][1][3],tmp_ports[j][0][3],select_port,tmp_output_port }, f2);
			}

			//out0
			if (i == 0 && j == 0)
			{
				if (tmp_ports_size[j].first != 1)
				{
					Instantiate_MUX({ "out0_c1","out0_c0",select_port,"out0" }, f2);
				}
				else
				{
					Instantiate_MUX({ "out0_c1","1'b0",select_port,"out0" }, f2);
				}
			}
		}
		if (cssa_skip_points[i] != -1)
		{
			flag++;
		}
		
	}
	f2 << "endmodule" << endl;
}

void CSL_V()
{
	stringstream ss;
	ofstream f_CSL;
	string module_name = "CSL";
	vector<int> input_ports_size;
	vector<string> ports;
	get_output_ports_size(input_ports_size);//However, not all of the output ports of compress tree are transferred to prefex tree
	f_CSL.open((module_name + ".v").c_str());
	//the output of compress tree
	for (int i = 0; i < input_ports_size.size(); i++)
	{
		string tmp;
		ss << "in" << i;
		ss >> tmp;
		ss.clear();
		ss.str("");
		ports.push_back(tmp);
	}

	//the output of prefex tree
	for (int i = 0; i < splits.size() - 1; i++)
	{
		string tmp;
		ss << "out" << i << "_g";
		ss >> tmp;
		ss.clear();  ss.str("");
		ports.push_back(tmp);
	}
	//new added cssa skip points
	int flag = 0;
	for (int i = 0; i < cssa_skip_points.size(); i++)
	{
		if (cssa_skip_points[i] != -1)
		{
			string tmp;
			ss << "out_cssa" << flag << "_g";
			ss >> tmp;
			ss.clear();  ss.str("");
			ports.push_back(tmp);
			ss << "out_cssa" << flag << "_p";
			ss >> tmp;
			ss.clear();  ss.str("");
			ports.push_back(tmp);
			flag++;
		}
		
	}

	//output ports
	for (int i = 0; i < input_ports_size.size() + 1; i++)
	{
		string tmp;
		ss << "out" << i;
		ss >> tmp;
		ss.clear();  ss.str("");
		ports.push_back(tmp);
	}
	
	verilog_template_CSL(module_name, ports, input_ports_size.size() + splits.size() + 2 * flag - 1, f_CSL, input_ports_size);
	function_csl(ports, input_ports_size, input_ports_size.size() + splits.size() + 2 * flag - 1, f_CSL);
	f_CSL.close();
}
