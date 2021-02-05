#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
string filename0 = "..//Tune_WL//gurobi_10_10.sol";
string filename1 = "10_10.txt"; // path of generated compressor tree result file
int stage_num = 5;
int num_of_elements = 19; //2*m-1

void sci2db(string& strSci, string& value_int)
{
	int value_s;
	stringstream ss;
	int value;
	int    iPower = 0;  //幂
	double dMntsa = 0;  //尾数
	double dCoefficient = 1;  //系数

	std::string strPower, strMntsa;

	if (std::string::npos == strSci.find("e"))
	{
		ss << round(atof(strSci.c_str()));
		ss >> value_int;
	}
	else
	{
		strMntsa = strSci.substr(0, strSci.find("e"));
		strPower = strSci.substr(strSci.find("e") + 1);

		dMntsa = atof(strMntsa.c_str());
		iPower = atoi(strPower.c_str());

		while (iPower != 0)
		{
			if (iPower > 0)
			{
				dCoefficient *= 10;
				iPower--;
			}
			else
			{
				dCoefficient *= 0.1;
				iPower++;
			}
		}
		value_s = round(dMntsa * dCoefficient);
		ss << value_s;
		ss >> value_int;
		//return dMntsa * dCoefficient;
	}
	
}

void get_name_value(string tmp, string &tmp_name, string &tmp_value, ifstream& f0)
{
	string tmp_s, tmp_v;
	tmp_name = tmp.substr(0, tmp.find(' '));
	tmp_s = tmp.substr(tmp.find(' ') + 1, tmp.size() - tmp.find(' '));
	sci2db(tmp_s, tmp_v);
	tmp_value = tmp_v;
	getline(f0, tmp);
	tmp_name += ("/" + tmp.substr(0, tmp.find(' ')));
	tmp_s = tmp.substr(tmp.find(' ') + 1, tmp.size() - tmp.find(' '));
	sci2db(tmp_s, tmp_v);
	tmp_value += ("/" + tmp_v);
	getline(f0, tmp);
	tmp_name += ("/" + tmp.substr(0, tmp.find(' ')));
	tmp_s = tmp.substr(tmp.find(' ') + 1, tmp.size() - tmp.find(' '));
	sci2db(tmp_s, tmp_v);
	tmp_value += ("/" + tmp_v);
}

void get_index(string tmp, int& index)
{
	stringstream ss;
	string s_index = tmp.substr(tmp.find('_') + 1, tmp.find(' ') - tmp.find('_'));
	ss << s_index;
	ss >> index;
	ss.clear();
}


int main(int argc, char* argv[])
{
	ifstream f0;
	ofstream f1;
	string tmp;
	/*vector<int> test(4, 0);
	test[4] = 2;*/

	int flag = 0;
	//flag = INT_MAX + 4;
	f0.open(filename0.c_str());
	f1.open(filename1.c_str());
	while (getline(f0, tmp))
	{
		if (tmp[0] == 'f')
		{
			string tmp_name;
			string tmp_value;
			int index;
			get_name_value(tmp, tmp_name, tmp_value, f0);
			f1 << (tmp_name + ":" + tmp_value) << "    ";
			get_index(tmp, index);
			if (index == num_of_elements + stage_num - 1)
			{
				f1 << endl;
			}
		}
	}
	f1.close();
	f0.close();
	return 0;
}

