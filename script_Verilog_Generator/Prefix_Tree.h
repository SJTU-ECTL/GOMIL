#pragma once
#ifndef PREFEX_TREE
#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Transform_Split(vector<vector<pair<int, int>>>& transform_split, vector<vector<int>>& circuits_distribution, vector<int> input_ports_size);
void verilog_template_PF(string module_name, vector<string> ports, int input_ports_num, ofstream& f2, vector<int> input_ports_size);
void Instantiate_Prefex_Element1(vector<string> ports, ofstream& f2);
void Instantiate_Prefex_Element2(vector<string> ports, ofstream& f2);
void Instantiate_Prefex_Element3(vector<string> ports, ofstream& f2);
void Instantiate_Inf1(vector<string> ports, ofstream& f2);
void Instantiate_Inf2(vector<string> ports, ofstream& f2);
void function_prefex_tree(vector<string> ports, vector<int> input_ports_size, int input_ports_num, ofstream& f2);
void Prefex_Tree_V();

#endif // !PREFEX_TREE

