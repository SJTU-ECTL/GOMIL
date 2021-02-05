#pragma once
#ifndef BASIC_BLOCK
#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void verilog_template(string module_name, vector<string> ports, int input_ports_num, ofstream& f2);
void function_A(vector<string> ports, int input_ports_num, ofstream& f2);
void function_mux(vector<string> ports, int input_ports_num, ofstream& f2);
void function_inf1(vector<string> ports, int input_ports_num, ofstream& f2);
void function_inf2(vector<string> ports, int input_ports_num, ofstream& f2);
void function_pref_elem1(vector<string> ports, int input_ports_num, ofstream& f2);
void function_pref_elem2(vector<string> ports, int input_ports_num, ofstream& f2);
void function_pref_elem3(vector<string> ports, int input_ports_num, ofstream& f2);
void FA_V();
void HA_V();
void MUX_V();
void INF1_V();
void INF2_V();
void PREF_ELEM1_V();
void PREF_ELEM2_V();
void PREF_ELEM3_V();
#endif // !BASIC_BLOCK


