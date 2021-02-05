#pragma once
#ifndef COMPRESS_TREE
#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

extern int wordlength;
extern int stage_number;
void verilog_template_PT(string module_name, vector<string> ports, int input_ports_num, ofstream& f2);
void verilog_template_CPT(string module_name, vector<string> ports, int input_ports_num, ofstream& f2, vector<int> output_ports_size);
void function_production(vector<string> ports, int input_ports_num, ofstream& f2);
void update_remain_vector(vector<int>& output_ports_size, vector<int>& fa_V, vector<int>& ha_V, vector<int>& remain_V);
void Instantiate_Full_Adder(vector<string> ports, ofstream& f2);
void Instantiate_Half_Adder(vector<string> ports, ofstream& f2);
void Instantiate_MUX(vector<string> ports, ofstream& f2);
void function_compress_tree(vector<string> ports, int input_ports_num, ofstream& f2);
void PRODUCTION_V();
void COMPRESS_TREE_V();
void split(vector<int>& output_ports_size, vector<int>& fa_V, vector<int>& ha_V, string target_str);
void get_output_ports_size(vector<int>& output_ports_size);
#endif // !COMPRESS_TREE
