#pragma once
#ifndef FAST_MULT
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Instantiate_Compress_Tree(vector<string> ports, ofstream& f2);
void Instantiate_Prefex_Tree(vector<string> ports, ofstream& f2);
void Instantiate_CSL(vector<string> ports, ofstream& f2);
void verilog_template_FM(string module_name, vector<string> ports, ofstream& f2);
void function_fast_multiplier(vector<string> ports, ofstream& f2);
void FAST_MULT_V();
#endif // !FAST_MULT

