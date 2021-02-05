#include "Prefex_Tree.h"
#include "Compress_Tree.h"
//int prefex_tree_stages = 6;
int Inf1_num = 0;
int Inf2_num = 0;
int Prefex_elem1_num = 0;
int Prefex_elem2_num = 0;
int Prefex_elem3_num = 0;

/*input: 5*5; */
vector<vector<vector<int>>> splits = {
	{/*{0,1},{2,3},*/{4,5},{6,7},{8}},
	{{4,5},{6,8}},
	{{4,8}}
};
vector<int> carry_bit_index = { 6,4 };
vector<int> cssa_skip_point = { -1,-1,-1};
vector<vector<vector<int>>> compensated_nodes;

/*input: 6*6; */
//vector<vector<vector<int>>> splits = {
//	{/*{0,1},{2,3},*/{4,5},{6},{7,8},{9,10} },
//	{{4,5},{6,8},{9,10}},
//	{{4,8,},{9,10}},
//	{{4,10}}
//};
//vector<int> carry_bit_index = { 9,4 };
//vector<int> cssa_skip_point = { -1,-1,-1 };
//vector<vector<vector<int>>> compensated_nodes;

/*input: 7*7; */
//vector<vector<vector<int>>> splits = {
//	{/*{0,1},*/{3,4},{5,6},{7,8},{9,10},{11,12}},
//	{{3,6},{7,10},{11,12}},
//	{{3,6},{7,12}},
//	{{3,12}}
//};
//vector<int> carry_bit_index = { 11,7,3 };
//vector<int> cssa_skip_point = { -1,-1,-1,-1};
//vector<vector<vector<int>>> compensated_nodes;


/*input: 8*8; */
//vector<vector<vector<int>>> splits = {
//	{/*{0,1},{2,3},*/{4,5},{6,7},{8,9},{10,11},{12},{13,14}},
//	{{4,7},{8,9},{10,12},{13,14}},
//	{{4,7},{8,12},{13,14}},
//	{{4,7},{8,14}}
//};
//vector<int> carry_bit_index = { 13,8 };
//vector<int> cssa_skip_point = { -1,10,4};
//vector<vector<vector<int>>> compensated_nodes;

/*input: 10*10; */
//vector<vector<vector<int>>> splits = {
//	{/*{0,1},{2,3},*/{4},{5},{6},{7},{8},{9},{10,11},{12},{13},{14,15},{16,17},{18} },
//	{{4,5},{6,7}, {8,9},{10,12}, {13,15},{16,18}},
//	{{4,7},{8,12},{13,18}},
//	{{4,7},{8,18}},
//	{{4,18}}
//};
//vector<int> carry_bit_index = { 16,13,8,4 };
//vector<int> cssa_skip_point = { -1,-1,-1,-1,-1};
//vector<vector<vector<int>>> compensated_nodes;


/*input: 16*16;*/
//vector<vector<vector<int>>> splits = {
//	{/*{0},{1},{2},{3},*/{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20},{21},{22,23},{24},{25,26},{27,28},{29},{30,31}},
//	{/*{0,1},{2,3},*/{4,5},{6,7},{8,9},{10,11},{12,13},{14,15},{16},{17,18},{19,20},{21},{22,24},{25,28},{29,31}},  
//	{/*{0,3},*/{4,7},{8,11},{12,15},{16,18},{19,21},{22,28},{29,31}},
//	{/*{0,7},*/{4,7}, {8,15},{16,21},{22,31}},
//	{/*{0,15}*/{4,7}, {8,15},{16,31}},
//	{/*{0,30}*/{4,7}, {8,31}}
//};
//vector<int> carry_bit_index = { 29,22,16,8 };
//vector<int> cssa_skip_point = { -1,25,19,12,4 };
//vector<vector<vector<int>>> compensated_nodes;

/*input: 20*20;*/
//vector<vector<vector<int>>> splits = {
//	{/*{0},{1},*/{2,3},{4,5}, {6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20},{21},{22},{23},{24},{25},{26},{27},{28},{29},{30,31},{32,33},{34},{35,36},{37},{38} },
//	{/*{0,1},{2,3},*/{2,5}, {6,7},{8,9},{10,11},{12,13},{14,15},{16,17},{18,19},{20,21},{22,23},{24,25} ,{26,27},{28,29},{30,33},{34,36},{37,38} },
//	{/*{0,3},*/{2,5}, {6,9},{10,13},{14,17},{18,21},{22,25},{26,29}, {30,36},{37,38}},
//	{/*{0,7},*/{2,5}, {6,13},{14,21},{22,29},{30,38}},
//	{/*{0,15}*/{2,5}, {6,21},{22,38}},
//	{/*{0,30}*/{2,5}, {6,38}}
//};
//vector<int> carry_bit_index = { 37,30,22,6 };
//vector<int> cssa_skip_point = { -1,34,26,18,10,2 };
//vector<vector<vector<int>>> compensated_nodes = { {{14,21},{22,38}}};


/*input: 32*32*/
//vector<vector<vector<int>>> splits = {
//	{/*{0},{1},{2},{3},*/{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20},{21},{22},{23},
//	{24},{25},{26},{27},{28},{29},{30},{31},{32},{33},{34},{35},{36},{37},{38},{39},{40},{41},{42},{43},{44},{45},{46},
//	{47},{48},{49},{50},{51},{52},{53,54},{55,56},{57,58},{59,60},{61},{62}},//the first stage
//	{/*{0,1},{2,3},*/{4,5},{6,7},{8,9},{10,11},{12,13},{14,15},{16,17},{18,19},{20,21},{22},{23},{24},{25},{26},{27},{28},
//	{29,30}, {31,32},{33,34},{35,36},{37,38},{39,40},{41,42},{43,44},{45,46},{47,48},{49,50},{51,52},{53,56},{57,60},{61},{62}},//the second stage
//	{/*{0,3},*/{4,7},{8,11},{12,15},{16,19},{20,22},{23}, {24,25},{26,27},{28}, {29,32},{33,36},{37,40},{41,44},{45,48},{49,52},{53,60},{61,62}},//the third stage
//	{/*{0,7},*/{4,7}, {8,15},{16,22},{23,25}, {26,28},{29,36},{37,44},{45,52},{53,62}},//the fourth  stage
//	{/*{0,15},*/{4,7},{8,22}, {23,28},{29,44},{45,62}},//the fifth stage
//	{/*{0,29},*/{4,7},{8,28}, {29,62}},//the sixth stage
//	{/*{0,62}*/{4,7},{8,62}}//the seventh stage
//};
//vector<int> carry_bit_index = { 61,53,45,29,8};
//vector<int> cssa_skip_point = { -1,57,49,41,33,26,20,12,4};
//vector<vector<vector<int>>> compensated_nodes =  {/* { {4,7},{8,14} } */{{37,44},{45,62}},{{23,28},{29,62}},{{16,22},{23,62}}};



void Insert_Compensated_Port(int port)
{
	int i;
	for (i = 0; i < carry_bit_index.size(); i++)
	{
		if (i != carry_bit_index.size() - 1)
		{
			if (carry_bit_index[i] > port&& carry_bit_index[i + 1] < port)
			{
				break;
			}
		}
		else
		{
			if (carry_bit_index[i] > port)
			{
				break;
			}
		}
		
	}
	carry_bit_index.insert(carry_bit_index.begin() + i + 1, port);
}

void Transform_Split(vector<vector<pair<int, int>>>& transform_split, vector<vector<int>>& circuits_distribution, vector<int> input_ports_size)
{
	for (int i = 0; i < splits.size(); i++)
	{
		vector<pair<int, int>> tmp_split;
		vector<int> tmp_circuits_distribution;
		int flag = 0;
		for (int j = 0; j < splits[i].size(); j++)
		{
			if (i == 0)
			{
				if (splits[i][j].size() == 1)
				{
					tmp_split.push_back(make_pair(splits[i][j][0], -1));
					if (input_ports_size[splits[i][j][0]] == 1)
					{
						tmp_circuits_distribution.push_back(-1);
					}
					else
					{
						tmp_circuits_distribution.push_back(-2);
					}
				}
				else
				{
					tmp_split.push_back(make_pair(splits[i][j][0], splits[i][j][1]));
					if (make_pair(input_ports_size[splits[i][j][0]], input_ports_size[splits[i][j][1]]) == make_pair(1, 1))
					{
						tmp_circuits_distribution.push_back(2);
					}
					else if (make_pair(input_ports_size[splits[i][j][0]], input_ports_size[splits[i][j][1]]) == make_pair(2, 1))
					{
						tmp_circuits_distribution.push_back(4);
					}
					else if (make_pair(input_ports_size[splits[i][j][0]],input_ports_size[splits[i][j][1]]) == make_pair(1, 2))
					{
						tmp_circuits_distribution.push_back(3);
					}
					else
					{
						tmp_circuits_distribution.push_back(1);
					}
				}
			}
			else
			{
				
				if (splits[i][j].size() == 1)
				{
					tmp_split.push_back(make_pair(flag, -1));
					if (circuits_distribution[i - 1][flag] == -1)
					{
						tmp_circuits_distribution.push_back(-1);
					}
					else
					{
						tmp_circuits_distribution.push_back(-2);
					}
					flag++;
				}
				else
				{
					if (*(splits[i][j].end() - 1) != *(splits[i - 1][flag].end() - 1))
					{
						tmp_split.push_back(make_pair(flag, flag + 1));
						//if (make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(1, 1) || make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(2, 2))
						if (circuits_distribution[i - 1][flag + 1] == 2 | circuits_distribution[i - 1][flag + 1] == -1)
						{
							if (circuits_distribution[i - 1][flag] == 2 | circuits_distribution[i - 1][flag] == -1)
							{
								tmp_circuits_distribution.push_back(2);
							}
							else
							{
								tmp_circuits_distribution.push_back(4);
							}
						}
						else if (make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(2, 1) |
								 make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(2, 3) |
								 make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(2, 4)|
								 make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(-1, 1)|
								 make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(-1, 3)|
								 make_pair(circuits_distribution[i - 1][flag], circuits_distribution[i - 1][flag + 1]) == make_pair(-1, 4))
						{
							tmp_circuits_distribution.push_back(3);
						}
						else
						{
							tmp_circuits_distribution.push_back(1);
						}
						flag += 2;
					}
					else
					{
						tmp_split.push_back(make_pair(flag, -1));
						//tmp_circuits_distribution.push_back(-1);
						if (circuits_distribution[i - 1][flag] == 2 | circuits_distribution[i - 1][flag] == -1)
						{
							tmp_circuits_distribution.push_back(-1);
						}
						else
						{
							tmp_circuits_distribution.push_back(-2);
						}
						flag += 1;
					}
					
				}
			}
		}
		transform_split.push_back(tmp_split);
		circuits_distribution.push_back(tmp_circuits_distribution);
	}

}

void verilog_template_PF(string module_name, vector<string> ports, int input_ports_num, ofstream& f2, vector<int> input_ports_size)
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
			f2 << "\t" << "input" << "[" << input_ports_size[i] - 1 << ":" << 0 << "] " << ports[i] << ";" << endl;
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

void Instantiate_Prefex_Element1(vector<string> ports, ofstream& f2)
{
	f2 << "\tpref_elem1 PF1_" << Prefex_elem1_num << "(" << ".g1(" << ports[0] << ")," << ".p1(" << ports[1] << "),";
	f2 << ".g2(" << ports[2] << ")," << ".p2(" << ports[3] << ")," << ".g_out(" << ports[4] << ")," << ".p_out(" << ports[5] << "));" << endl;
	Prefex_elem1_num++;
}

void Instantiate_Prefex_Element2(vector<string> ports, ofstream& f2)
{
	f2 << "\tpref_elem2 PF2_" << Prefex_elem2_num << "(" << ".g1(" << ports[0] << ")," << ".p1(" << ports[1] << "),";
	f2 << ".g2(" << ports[2] << ")," << ".p2(" << ports[3] << ")," << ".g_out(" << ports[4] << ")," << ".p_out(" << ports[5] << "));" << endl;
	Prefex_elem2_num++;
}

void Instantiate_Prefex_Element3(vector<string> ports, ofstream& f2)
{
	f2 << "\tpref_elem3 PF3_" << Prefex_elem3_num << "(" << ".g1(" << ports[0] << ")," << ".p1(" << ports[1] << "),";
	f2 << ".g2(" << ports[2] << ")," << ".p2(" << ports[3] << ")," << ".g_out(" << ports[4] << ")," << ".p_out(" << ports[5] << "));" << endl;
	Prefex_elem3_num++;
}

void Instantiate_Inf1(vector<string> ports, ofstream& f2)
{
	f2 << "\tInf1 I" << Inf1_num << "(" << ".a(" << ports[0] << ")," << ".b(" << ports[1] << "),";
	f2 << ".p(" << ports[2] << ")," << ".g(" << ports[3] << ")" << ");" << endl;
	Inf1_num++;
}

void Instantiate_Inf2(vector<string> ports, ofstream& f2)
{
	f2 << "\tInf2 U" << Inf2_num << "(" << ".a(" << ports[0] << "),";
	f2 << ".p(" << ports[1] << ")," << ".g(" << ports[2] << ")" << ");" << endl;
	Inf2_num++;
}

void get_index(int& row_index, int& col_index, vector<int> find_vec, bool& flag)
{
	flag = 0;
	for (int i = 0; i < splits.size(); i++)
	{
		for (int j = 0; j < splits[i].size(); j++)
		{
			if (splits[i][j] == find_vec)
			{
				row_index = i;
				col_index = j;
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			break;
		}
	}
}

void function_prefex_tree(vector<string> ports, vector<int> input_ports_size, int input_ports_num, ofstream& f2)
{
	//preparation
	vector<vector<pair<int, int>>> transform_split;
	vector<vector<int>> circuits_distribution;
	Transform_Split(transform_split, circuits_distribution, input_ports_size);

	//the first stage --pre-processing
	f2 << endl << endl;
	f2 << "\t//The first stage --pre-processing" << endl;
	//declare ports
	f2 << "\twire[" << input_ports_num - 1 << ":" << 0 << "] P_s1;" << endl;
	f2 << "\twire[" << input_ports_num - 1 << ":" << 0 << "] G_s1;" << endl;
	//function block
	for (int i = splits[0][0][0]; i < input_ports_size.size(); i++)
	{
		if (input_ports_size[i] == 1)
		{
			stringstream ss;
			string port1,output_port1, output_port2;
			port1 = ports[i] + "[0]";
			ss << "P_s1" << "[" << i << "]";
			ss >> output_port1;
			ss.clear();
			ss.str("");
			ss << "G_s1" << "[" << i << "]";
			ss >> output_port2;
			ss.clear();
			ss.str("");
			vector<string> ports = { port1,output_port1,output_port2 };
			Instantiate_Inf2(ports, f2);
		}
		else
		{
			stringstream ss;
			string port1, port2, output_port1, output_port2;
			port1 = ports[i] + "[0]";
			port2 = ports[i] + "[1]";
			ss << "P_s1" << "[" << i << "]";
			ss >> output_port1;
			ss.clear();
			ss.str("");
			ss << "G_s1" << "[" << i << "]";
			ss >> output_port2;
			ss.clear();
			ss.str("");
			vector<string> ports = { port1,port2,output_port1,output_port2 };
			Instantiate_Inf1(ports, f2);
		}
	}

	//the following stages
	
	for (int i = 0; i < transform_split.size(); i++)
	{
		f2 << endl;
		//declare ports
		f2 << "\t//The " << i + 2 << "-th stage" << endl;
		f2 << "\twire[" << transform_split[i].size() - 1 << ":" << 0 << "] P_s" << i + 2 << ";" << endl;
		f2 << "\twire[" << transform_split[i].size() - 1 << ":" << 0 << "] G_s" << i + 2 << ";" << endl;
		//function block
		for (int j = 0; j < transform_split[i].size(); j++)
		{

			if (transform_split[i][j].second != -1 && transform_split[i][j].second != -2)
			{
				stringstream ss;
				vector<string> ports;
				string port1, port2, port3, port4, output_port1, output_port2;
				ss << "G_s" << i + 1 << "[" << transform_split[i][j].first << "]";
				ss >> port1;
				ss.clear();
				ss.str("");
				ss << "P_s" << i + 1 << "[" << transform_split[i][j].first << "]";
				ss >> port2;
				ss.clear();
				ss.str("");
				ss << "G_s" << i + 1 << "[" << transform_split[i][j].second << "]";
				ss >> port3;
				ss.clear();
				ss.str("");
				ss << "P_s" << i + 1 << "[" << transform_split[i][j].second << "]";
				ss >> port4;
				ss.clear();
				ss.str("");
				ss << "G_s" << i + 2 << "[" << j << "]";
				ss >> output_port1;
				ss.clear();
				ss.str("");
				ss << "P_s" << i + 2 << "[" << j << "]";
				ss >> output_port2;
				ss.clear();
				ss.str("");
				ports = { port1,port2,port3,port4,output_port1,output_port2 };
				if (circuits_distribution[i][j] == 1)
				{
					Instantiate_Prefex_Element1(ports, f2);
				}
				else if (circuits_distribution[i][j] == 2 | circuits_distribution[i][j] == 4)
				{
					Instantiate_Prefex_Element2(ports, f2);
				}
				else if (circuits_distribution[i][j] == 3)
				{
					Instantiate_Prefex_Element3(ports, f2);
				}
			}
			else
			{
				f2 << "\tassign G_s" << i + 2 << "[" << j << "]" << " = " << "G_s" << i + 1 << "[" << transform_split[i][j].first << "];" << endl;
				f2 << "\tassign P_s" << i + 2 << "[" << j << "]" << " = " << "P_s" << i + 1 << "[" << transform_split[i][j].first << "];" << endl;
			}
		}
	}
	//compensated ports
	f2 << endl << "\t//compensated ports!!!" << endl;
	vector<int> compensated_circuits_distribution;
	bool Flag0, Flag1;
	for (int i = 0; i < compensated_nodes.size(); i++)
	{
		f2 << "\twire " << "G_com" << i << ";" << endl;
		f2 << "\twire " << "P_com" << i << ";" << endl;
		stringstream ss;
		vector<string> ins_ports;
		vector<int> tmp_circuits_distribution;
		string port1, port2, port3, port4, output_port1, output_port2;
		int row_index0, col_index0;
		int row_index1, col_index1;
		get_index(row_index0, col_index0, compensated_nodes[i][0],Flag0);
		get_index(row_index1, col_index1, compensated_nodes[i][1],Flag1);
		Insert_Compensated_Port(compensated_nodes[i][0][0]);
		if (!(Flag0 && Flag1))
		{
			//find the index in compensated ports
			if (Flag0 == 0 && Flag1 == 1)
			{
				for (int k = 0; k < compensated_nodes.size(); k++)
				{
					if (compensated_nodes[i][0][0] == compensated_nodes[k][0][0] && compensated_nodes[i][0][1] == compensated_nodes[k][1][1])
					{
						ss << "G_com" << k;
						ss >> port1;
						ss.clear();
						ss.str("");
						ss << "P_com" << k;
						ss >> port2;
						ss.clear();
						ss.str("");
						ss << "G_s" << row_index1 + 2 << "[" << col_index1 << "]";
						ss >> port3;
						ss.clear();
						ss.str("");
						ss << "P_s" << row_index1 + 2 << "[" << col_index1 << "]";
						ss >> port4;
						ss.clear();
						ss.str("");
						tmp_circuits_distribution = { compensated_circuits_distribution[k],circuits_distribution[row_index1][col_index1] };
					}
				}
			}
			else if (Flag0 == 1 && Flag1 == 0)
			{
				for (int k = 0; k < compensated_nodes.size(); k++)
				{
					if (compensated_nodes[i][1][0] == compensated_nodes[k][0][0] && compensated_nodes[i][1][1] == compensated_nodes[k][1][1])
					{
						ss << "G_com" << k;
						ss >> port3;
						ss.clear();
						ss.str("");
						ss << "P_com" << k;
						ss >> port4;
						ss.clear();
						ss.str("");
						ss << "G_s" << row_index0 + 2 << "[" << col_index0 << "]";
						ss >> port1;
						ss.clear();
						ss.str("");
						ss << "P_s" << row_index0 + 2 << "[" << col_index0 << "]";
						ss >> port2;
						ss.clear();
						ss.str("");
						tmp_circuits_distribution = { circuits_distribution[row_index0][col_index0],compensated_circuits_distribution[k] };
					}
				}
			}
			else
			{
				for (int k = 0; k < compensated_nodes.size(); k++)
				{
					if (compensated_nodes[i][0][0] == compensated_nodes[k][0][0] && compensated_nodes[i][0][1] == compensated_nodes[k][1][1])
					{
						ss << "G_com" << k;
						ss >> port1;
						ss.clear();
						ss.str("");
						ss << "P_com" << k;
						ss >> port2;
						ss.clear();
						ss.str("");
						tmp_circuits_distribution.push_back(compensated_circuits_distribution[k]);
					}
					if (compensated_nodes[i][1][0] == compensated_nodes[k][0][0] && compensated_nodes[i][1][1] == compensated_nodes[k][1][1])
					{
						ss << "G_com" << k;
						ss >> port3;
						ss.clear();
						ss.str("");
						ss << "P_com" << k;
						ss >> port4;
						ss.clear();
						ss.str("");
						tmp_circuits_distribution.push_back(compensated_circuits_distribution[k]);
					}
					
				}
			}
			
		}
		else
		{
			
			ss << "G_s" << row_index0 + 2 << "[" << col_index0 << "]";
			ss >> port1;
			ss.clear();
			ss.str("");
			ss << "P_s" << row_index0 + 2 << "[" << col_index0 << "]";
			ss >> port2;
			ss.clear();
			ss.str("");
			ss << "G_s" << row_index1 + 2 << "[" << col_index1 << "]";
			ss >> port3;
			ss.clear();
			ss.str("");
			ss << "P_s" << row_index1 + 2 << "[" << col_index1 << "]";
			ss >> port4;
			ss.clear();
			ss.str("");
			tmp_circuits_distribution = { circuits_distribution[row_index0][col_index0],circuits_distribution[row_index0][col_index0] };
			
		}
		ss << "G_com" << i;
		ss >> output_port1;
		ss.clear();
		ss.str("");
		ss << "P_com" << i;
		ss >> output_port2;
		ss.clear();
		ss.str("");
		ins_ports = { port1,port2,port3,port4,output_port1,output_port2 };
		if ((tmp_circuits_distribution[0] == 2 | tmp_circuits_distribution[0] == -1) && (tmp_circuits_distribution[1] == 2 | tmp_circuits_distribution[1] == -1))
		{
			compensated_circuits_distribution.push_back(2);
			Instantiate_Prefex_Element2(ins_ports, f2);

		}
		else if ((tmp_circuits_distribution[0] != 2 | tmp_circuits_distribution[0] != -1) && (tmp_circuits_distribution[1] == 2 && tmp_circuits_distribution[1] == -1))
		{
			compensated_circuits_distribution.push_back(4);
			Instantiate_Prefex_Element2(ins_ports, f2);
		}
		else if ((tmp_circuits_distribution[0] == 2 | tmp_circuits_distribution[0] == -1) && (tmp_circuits_distribution[1] != 2 && tmp_circuits_distribution[1] != -1))
		{
			compensated_circuits_distribution.push_back(3);
			Instantiate_Prefex_Element3(ins_ports, f2);
		}
		else
		{
			compensated_circuits_distribution.push_back(1);
			Instantiate_Prefex_Element1(ins_ports, f2);
		}
	}


	//output ports 
	int flag0 = 0;
	int flag1 = 0;
	int flag2 = 0;
	for (int i = 0; i < carry_bit_index.size(); i++)
	{
		for (int j = flag0; j < splits.size(); j++)
		{
			bool id = 0;
			int m;
			for (m = 0; m < compensated_nodes.size(); m++)
			{
				if (compensated_nodes[m][0][0] == carry_bit_index[i])
				{
					id = 1;
					break;
				}
			}
			if (id)
			{
				f2 << "\tassign " << ports[input_ports_num + 2 * i] << " = " << "G_com" << m << ";" << endl;
				f2 << "\tassign " << ports[input_ports_num + 2 * i + 1] << " = " << "P_com" << m << ";" << endl;
			}
			else
			{
				if (splits[j][splits[j].size() - 1][0] == carry_bit_index[i])
				{
					f2 << "\tassign " << ports[input_ports_num + 2 * i] << " = " << "G_s" << j + 2 << "[" << splits[j].size() - 1 << "];" << endl;
					f2 << "\tassign " << ports[input_ports_num + 2 * i + 1] << " = " << "P_s" << j + 2 << "[" << splits[j].size() - 1 << "];" << endl;
					flag0 = j + 1;
					break;
				}
			}
			
		}
		//compensated nodes
		//for (int j = flag1; j < compensated_nodes.size(); j++)
		//{
		//	if (compensated_nodes[j][0][0] == carry_bit_index[i])
		//	{
		//		//get the ports' address
		//		int row_index0, col_index0;
		//		int row_index1, col_index1;
		//		get_index(row_index0, col_index0,compensated_nodes[j][0]);
		//		get_index(row_index1, col_index1,compensated_nodes[j][1]);
		//		stringstream ss;
		//		vector<string> ins_ports;
		//		string port1, port2, port3, port4, output_port1, output_port2;
		//		ss << "G_s" << row_index0 + 2 << "[" << col_index0 << "]";
		//		ss >> port1;
		//		ss.clear();
		//		ss.str("");
		//		ss << "P_s" << row_index0 + 2 << "[" << col_index0 << "]";
		//		ss >> port2;
		//		ss.clear();
		//		ss.str("");
		//		ss << "G_s" << row_index1+2 << "[" << col_index1 << "]";
		//		ss >> port3;
		//		ss.clear();
		//		ss.str("");
		//		ss << "P_s" << row_index1 + 2 << "[" << col_index1 << "]";
		//		ss >> port4;
		//		ss.clear();
		//		ss.str("");
		//		ss << "G_com" << j;
		//		ss >> output_port1;
		//		ss.clear();
		//		ss.str("");
		//		ss << "P_com" << j;
		//		ss >> output_port2;
		//		ss.clear();
		//		ss.str("");
		//		ins_ports = { port1,port2,port3,port4,output_port1,output_port2 };
		//		if (circuits_distribution[i][j] == 1)
		//		{
		//			Instantiate_Prefex_Element1(ins_ports, f2);
		//		}
		//		else if (circuits_distribution[i][j] == 2 | circuits_distribution[i][j] == 4)
		//		{
		//			Instantiate_Prefex_Element2(ins_ports, f2);
		//		}
		//		else if (circuits_distribution[i][j] == 3)
		//		{
		//			Instantiate_Prefex_Element3(ins_ports, f2);
		//		}
		//		f2 << "\tassign " << ports[input_ports_num + 2 * i] << " = " << "G_com" << j << ";" << endl;
		//		f2 << "\tassign " << ports[input_ports_num + 2 * i + 1] << " = " << "P_com" << j << ";" << endl;
		//	}
		//	
		//}

		//cssa skip point
		bool tmp_id;
		if (cssa_skip_point[i] != -1)
		{
			int row_index, col_index;
			if (i == 0)
			{
				
				get_index(row_index, col_index, { cssa_skip_point[i],30 },tmp_id);
				
			}
			else
			{
				get_index(row_index, col_index, { cssa_skip_point[i], carry_bit_index[i - 1] - 1 },tmp_id);
			}
			f2 << "\tassign " << ports[input_ports_num + 2 * carry_bit_index.size() + 2 * flag2] << " = " << "G_s" << row_index + 2 << "[" << col_index << "]" << ";" << endl;
			f2 << "\tassign " << ports[input_ports_num + 2 * carry_bit_index.size() + 2 * flag2 + 1] << " = " << "P_s" << row_index + 2 << "[" << col_index << "]" << ";" << endl;
			flag2++;
		}

	}
	//the last cssa skip point
	bool tmp_id;
	if (cssa_skip_point[cssa_skip_point.size() - 1] != -1)
	{
		int row_index, col_index;
		get_index(row_index, col_index, { *(cssa_skip_point.end() - 1), *(carry_bit_index.end() - 1) - 1 }, tmp_id);
		f2 << "\tassign " << ports[input_ports_num + 2 * carry_bit_index.size() + 2 * flag2] << " = " << "G_s" << row_index + 2 << "[" << col_index << "]" << ";" << endl;
		f2 << "\tassign " << ports[input_ports_num + 2 * carry_bit_index.size() + 2 * flag2 + 1] << " = " << "P_s" << row_index + 2 << "[" << col_index << "]" << ";" << endl;
	}
	f2 << "endmodule" << endl;
}

void Prefex_Tree_V()
{
	stringstream ss;
	ofstream f_PREFEX_TREE;
	string module_name = "Prefex_Tree";
	vector<int> input_ports_size;
	vector<string> ports;
	get_output_ports_size(input_ports_size);//However, not all of the output ports of compress tree are transferred to prefex tree
	//input_ports_size.erase(input_ports_size.begin(), input_ports_size.begin() + splits[0][0][0]);
	f_PREFEX_TREE.open((module_name + ".v").c_str());
	for (int i = 0; i < input_ports_size.size(); i++)
	{
		string tmp;
		ss << "in" << i;
		ss >> tmp;
		ss.clear();
		ss.str("");
		ports.push_back(tmp);
	}
	for (int i = 0; i < /*carry_bit_index.size()*/cssa_skip_point.size() - 1; i++)
	{
		string tmp;
		ss << "out" << i << "_g";
		ss >> tmp;
		ss.clear();
		ss.str("");
		ports.push_back(tmp);
		ss << "out" << i << "_p";
		ss >> tmp;
		ss.clear();
		ss.str("");
		ports.push_back(tmp);
	}
	//add cssa skip point
	int flag = 0;
	for (int i = 0; i < cssa_skip_point.size(); i++)
	{
		if (cssa_skip_point[i] == -1)
		{
			continue;
		}
		string tmp;
		ss << "out_cssa" << flag << "_g";
		ss >> tmp;
		ss.clear();
		ss.str("");
		ports.push_back(tmp);
		ss << "out_cssa" << flag << "_p";
		ss >> tmp;
		ss.clear();
		ss.str("");
		ports.push_back(tmp);
		flag++;
	}
	verilog_template_PF(module_name, ports, input_ports_size.size(), f_PREFEX_TREE, input_ports_size);
	function_prefex_tree(ports, input_ports_size, input_ports_size.size(), f_PREFEX_TREE);
	f_PREFEX_TREE.close();
}	
