/* Copyright 2018, Gurobi Optimization, LLC */

#include "gurobi_c++.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "Adder_Tree_Optimization.h"
#include "Multiplier_Tree_Optimization.h"
#include <string>

//using namespace std;
//vector<GRBVar> final_stage = { /*0,0,*/1,2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1   ,2,1,2,2,1 };
//string filename1 = "Tune_WL//10//W5L7//gurobi_glo_adder_10";
//string filename2 = "Tune_WL//10//W5L7//split10";


void generate_variables_obj(vector<vector<GRBVar>>& variables_obj, vector<GRBVar> final_stage, GRBModel& model)
{
	for (int i = 0; i < final_stage.size(); i++)
	{
		vector<GRBVar> variables_obj_of_each_stage;
		for (int j = 0; j < final_stage.size() - i; j++)
		{
			GRBVar variable_obj;
			stringstream ss;
			string tmp_s;
			ss << "obj" << i << "_" << j;
			ss >> tmp_s;
			ss.clear();
			variable_obj = model.addVar(0, GRB_INFINITY, 0, GRB_INTEGER, tmp_s);
			variables_obj_of_each_stage.push_back(variable_obj);
		}
		variables_obj.push_back(variables_obj_of_each_stage);
	}
}
void generate_variables(vector<vector<GRBVar>>& variables_x, vector<vector<GRBVar>>& variables_b, vector<GRBVar> final_stage, GRBModel& model)
{
	for (int i = 0; i < final_stage.size(); i++)
	{
		vector<GRBVar> variables_x_of_each_stage;  
		vector<GRBVar> variables_b_of_each_stage;
		for (int j = 0; j < final_stage.size() - i; j++)
		{
			GRBVar variable_x, variable_b;
			stringstream ss;
			string tmp_s;
			ss << "x" << i << "_" << j;
			ss >> tmp_s;
			ss.clear();
			variable_x = model.addVar(0, GRB_INFINITY, 0, GRB_INTEGER, tmp_s);
			ss << "b" << i << "_" << j;
			ss >> tmp_s;
			ss.clear();
			variable_b = model.addVar(0, 1, 0, GRB_INTEGER, tmp_s);
			variables_x_of_each_stage.push_back(variable_x);
			variables_b_of_each_stage.push_back(variable_b);
		}
		variables_x.push_back(variables_x_of_each_stage);
		variables_b.push_back(variables_b_of_each_stage);
	}
}

void generate_variables_of_indicators(vector<vector<GRBVar>>& variables_indicator, vector<GRBVar> final_stage, GRBModel& model)
{
	for (int i = 0; i < final_stage.size(); i++)
	{
		vector<GRBVar> variables_indicator_of_each_stage;
		for (int j = 0; j < final_stage.size() - i; j++)
		{
			GRBVar variable_indicator;
			stringstream ss;
			string tmp_s;
			ss << "id" << i << "_" << j;
			ss >> tmp_s;
			ss.clear();
			variable_indicator = model.addVar(0, 1, 0, GRB_BINARY, tmp_s);
			variables_indicator_of_each_stage.push_back(variable_indicator);
		}
		variables_indicator.push_back(variables_indicator_of_each_stage);
	}
}

//split position of each variable
void generate_variables_of_sp(vector<vector<GRBVar>>& variables_sp, vector<GRBVar> final_stage, GRBModel& model)
{
	for (int i = 0; i < final_stage.size(); i++)
	{
		vector<GRBVar> variables_sp_of_each_stage;
		for (int j = 0; j < final_stage.size() - i; j++)
		{
			stringstream ss;
			string tmp_s;
			ss << "sp" << i << "_" << j;
			ss >> tmp_s;
			ss.clear();
			GRBVar variable_sp = model.addVar(-1, INFINITY, 0, GRB_INTEGER, tmp_s);
			variables_sp_of_each_stage.push_back(variable_sp);
		}
		variables_sp.push_back(variables_sp_of_each_stage);
	}
}

//new constraints for delay
void generate_variables_of_delay(vector<vector<GRBVar>>& variables_d, vector<GRBVar> final_stage, GRBModel& model)
{
	for (int i = 0; i < final_stage.size(); i++)
	{
		vector<GRBVar> variables_d_of_each_stage;
		for (int j = 0; j < final_stage.size() - i; j++)
		{
			GRBVar variable_d;
			stringstream ss;
			string tmp_s;
			ss << "d" << i << "_" << j;
			ss >> tmp_s;
			ss.clear();
			variable_d = model.addVar(0, GRB_INFINITY, 0, GRB_INTEGER, tmp_s);
			variables_d_of_each_stage.push_back(variable_d);
		}
		variables_d.push_back(variables_d_of_each_stage);
	}
}

void Initial_constraints_b_x_d_sp_id_0(vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_b, vector<vector<GRBVar>> variables_d, vector<vector<GRBVar>> variables_sp, vector<vector<GRBVar>> variables_indicator, vector<GRBVar> final_stage, GRBModel& model)
{
	for (int i = 0; i < final_stage.size(); i++)
	{
		model.addConstr(variables_b[0][i] == final_stage[i] - 1);
		model.addConstr(variables_x[0][i] == 0);
		model.addConstr(variables_d[0][i] == 0);
		model.addConstr(variables_sp[0][i] == -1);
		//GRBLinExpr tmp = final_stage[i];
		//model.addGenConstrIndicator(variables_indicator[0][i], 1, tmp, GRB_EQUAL, 0);
	}
}

void generate_constraints_b(vector<vector<GRBVar>> variables_b, GRBModel& model)
{
	for (int i = 1; i < variables_b.size(); i++)
	{
		for (int j = 0; j < variables_b[i].size(); j++)
		{
			GRBVar tmp[2] = { variables_b[0][j],variables_b[i - 1][j + 1] };
			model.addGenConstrOr(variables_b[i][j], tmp, 2);
			//model.addGenConstrMax(variables_b[i][j], tmp, 2);
		}
	}
}

void generate_constraints_id(vector<vector<GRBVar>> variables_indicator, GRBModel& model)
{
	for (int i = 1; i < variables_indicator.size(); i++)
	{
		for (int j = 0; j < variables_indicator[i].size(); j++)
		{
			GRBVar tmp[2] = { variables_indicator[0][j],variables_indicator[i - 1][j + 1] };
			model.addGenConstrAnd(variables_indicator[i][j], tmp, 2);
		}
	}
}

void generate_constraints_x(vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_b, GRBModel& model)
{
	for (int i = 1; i < variables_x.size(); i++)
	{
		for (int j = 0; j < variables_x[i].size(); j++)
		{
			GRBVar* compare_array = (GRBVar*)malloc(i * sizeof(GRBVar));
			for (int k = 0; k < i; k++)
			{
				stringstream ss;
				string tmp_s;
				ss << "tmp" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar tmp = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
				ss << "tmptmp" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar tmptmp = model.addVar(-1, 1, 0, GRB_INTEGER, tmp_s);
				GRBVar and_op[2] = { variables_b[k][j],variables_b[i - k - 1][j + k + 1] };
				model.addGenConstrMin(tmptmp, and_op, 2);
				model.addQConstr(variables_x[k][j] + variables_x[i - k - 1][j + k + 1] + tmptmp/*variables_b[k][j] * variables_b[i - k - 1][j + k + 1]*/ + variables_b[i - k - 1][j + k + 1] - tmp <= -1);
				//model.addQConstr(variables_x[k][j] + variables_x[i - k - 1][j + k + 1] + variables_b[k][j] * variables_b[i - k - 1][j + k + 1] + variables_b[i - k - 1][j + k + 1] - tmp >= -1);
				compare_array[k] = tmp;
			}
			model.addGenConstrMin(variables_x[i][j], compare_array, i);
			free(compare_array);
		}
	}
}

void generate_constraints_obj(vector<vector<GRBVar>> variables_obj, vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_d, GRBModel& model)
{
	for (int i = 0; i < variables_obj.size(); i++)
	{
		for (int j = 0; j < variables_obj[i].size(); j++)
		{
			model.addConstr(variables_x[i][j] + PARAMETER_W * variables_d[i][j] == variables_obj[i][j]);
		}
	}
}

void generate_constraints_x_d_sp_id(vector<vector<GRBVar>> variables_x, vector<vector<GRBVar>> variables_b, vector<vector<GRBVar>> variables_d, vector<vector<GRBVar>> variables_sp, GRBModel& model, int level)
{
	for (int i = 1; i < /*variables_x.size()*/level; i++)
	{
		for (int j = 0; j < variables_x[i].size(); j++)
		{
			GRBVar* compare_array = (GRBVar*)malloc(i * sizeof(GRBVar));
			GRBVar* tmp_b_array = (GRBVar*)malloc(i * sizeof(GRBVar));
			GRBQuadExpr x_quad_expr = 0;
			GRBQuadExpr d_quad_expr = 0;
			GRBQuadExpr sp_quad_expr = 0;
			GRBLinExpr b_lin_expr = 0;
			stringstream ss;
			string tmp_s;
			for (int k = 0; k < i; k++)
			{

				ss << "addx" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar addx = model.addVar(0, 2, 0, GRB_INTEGER, tmp_s);
				/*new added linearization*/
				/*ss << "add_tmpx" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar add_tmpx = model.addVar(1, 2, 0, GRB_INTEGER, tmp_s);
				model.addConstr(add_tmpx == variables_b[k][j] + 1);
				model.addConstr(addx <= add_tmpx);
				model.addConstr(addx >= add_tmpx - 2 * (1 - variables_b[i - k - 1][j + k + 1]));
				model.addConstr(addx >= variables_b[i - k - 1][j + k + 1]);
				model.addConstr(addx <= 2 * variables_b[i - k - 1][j + k + 1]);*/

				model.addQConstr(variables_b[k][j] * variables_b[i - k - 1][j + k + 1] + variables_b[i - k - 1][j + k + 1] - addx == 0);
				//model.addQConstr(variables_b[k][j] * variables_b[i - k - 1][j + k + 1] + variables_b[i - k - 1][j + k + 1] - addx >= 0);


				/*model.addQConstr(add_tmpx * variables_b[i - k - 1][j + k + 1] - addx <= 0);
				model.addQConstr(add_tmpx * variables_b[i - k - 1][j + k + 1] - addx >= 0);*/
				ss << "tmpx" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar tmpx = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
				model.addConstr(variables_x[k][j] + variables_x[i - k - 1][j + k + 1] + addx /** (1 - variables_indicator[k][j])*/ - tmpx == -1);
				//model.addQConstr(variables_x[k][j] + variables_x[i - k - 1][j + k + 1] + addx /** (1 - variables_indicator[k][j])*/ - tmpx >= -1);
				ss << "tmpd" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar tmpd = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
				/*ss << "tmp" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();*/
				GRBVar compare_delay[2] = { variables_d[k][j], variables_d[i - k - 1][j + k + 1] };
				model.addGenConstrMax(tmpd, compare_delay, 2);
				ss << "addd" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar addd = model.addVar(0, 1, 0, GRB_INTEGER, tmp_s);

				/*new added linearization*/
				/*model.addConstr(addd <= variables_b[k][j]);
				model.addConstr(addd <= variables_b[i - k - 1][j + k + 1]);
				model.addConstr(addd >= variables_b[k][j] + variables_b[i - k - 1][j + k + 1] - 1);*/

				model.addQConstr(variables_b[k][j] * variables_b[i - k - 1][j + k + 1] - addd == 0);
				//model.addQConstr(variables_b[k][j] * variables_b[i - k - 1][j + k + 1] - addd <= 0);
				ss << "delay" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar delay = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
				model.addConstr(tmpd + addd/* * (1 - variables_indicator[k][j])*/ - delay == -1);
				//model.addConstr(tmpd + addd/* * (1 - variables_indicator[k][j])*/ - delay >= -1);

				ss << "tmpb" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				tmp_b_array[k] = model.addVar(0, 1, 0, GRB_BINARY, tmp_s);
				x_quad_expr += tmp_b_array[k] * tmpx;
				d_quad_expr += tmp_b_array[k] * delay;
				sp_quad_expr += tmp_b_array[k] * (j + k);
				b_lin_expr += tmp_b_array[k];
				ss << "tmp" << i << "_" << j << "_" << k;
				ss >> tmp_s;
				ss.clear();
				GRBVar tmp = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
				model.addConstr(tmpx + PARAMETER_W * delay - tmp == 0);
				compare_array[k] = tmp;
			}
			ss << "obj_tmp" << i << "_" << j << "_";
			ss >> tmp_s;
			ss.clear();
			GRBVar obj_tmp = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
			model.addGenConstrMin(obj_tmp, compare_array, i);
			model.addConstr(b_lin_expr == 1);
			model.addQConstr(x_quad_expr + PARAMETER_W * d_quad_expr == obj_tmp);

			model.addQConstr(x_quad_expr == variables_x[i][j]);
			model.addQConstr(d_quad_expr == variables_d[i][j]);
			model.addConstr(sp_quad_expr == variables_sp[i][j]);
			free(compare_array);
			free(tmp_b_array);
		}
	}
}

int glo_opt_adder_tree(vector<int> last_stage, int last_split_size, GRBEnv env)
{
	string filename1 = "Tune_WL//" + to_string(MULT_SIZE) + "//W" + to_string(PARAMETER_W) + "L" +
		to_string(PARAMETER_L) + "//gurobi_glo_adder_" + to_string(MULT_SIZE);


	GRBModel model = GRBModel(env);
	model.set(GRB_INT_PAR_PRESOLVE, "2");
	vector<vector<GRBVar>> variables_x;
	vector<vector<GRBVar>> variables_b;
	vector<vector<GRBVar>> variables_d;
	vector<vector<GRBVar>> variables_sp;
	vector<vector<GRBVar>> variables_indicator;
	vector<vector<GRBVar>> variables_obj;
	vector<GRBVar> final_stage;
	stringstream ss;
	string tmp;
	for (int i = 0; i < last_stage.size(); i++)
	{
		ss << "var_f" << i;
		ss >> tmp;
		ss.clear();
		GRBVar var_f = model.addVar(1, 2, 0, GRB_INTEGER, tmp);
		model.addConstr(var_f == last_stage[i]);
		final_stage.push_back(var_f);
	}

	generate_variables(variables_x, variables_b, final_stage, model);
	generate_variables_of_delay(variables_d, final_stage, model);
	generate_variables_of_sp(variables_sp, final_stage, model);
	generate_variables_obj(variables_obj, final_stage, model);
	Initial_constraints_b_x_d_sp_id_0(variables_x, variables_b, variables_d, variables_sp, variables_indicator, final_stage, model);
	generate_constraints_b(variables_b, model);
	generate_constraints_obj(variables_obj, variables_x, variables_d, model);
	generate_constraints_x_d_sp_id(variables_x, variables_b, variables_d, variables_sp, model, final_stage.size());

	//objective function
	GRBLinExpr obj = variables_obj[final_stage.size() - 1][0];
	model.setObjective(obj, GRB_MINIMIZE);
	model.write(filename1 + ".lp");
	//model.write("gurobi.log");
	//MIP start
	/*model.read("gurobi1.sol");
	model.read("gurobi2.sol");*/
	// Optimize model
	//model.update();
	model.optimize();

	//Save solution

	model.write(filename1 + ".sol");
	display_split(variables_sp, last_split_size);
	return variables_obj[final_stage.size() - 1][0].get(GRB_DoubleAttr_X);
}

void display_split(vector<vector<GRBVar>> variables_sp, int last_split_size)
{
	string filename2 = "Tune_WL//" + to_string(MULT_SIZE) + "//W" + to_string(PARAMETER_W) + "L" +
		to_string(PARAMETER_L) + "//split" + to_string(MULT_SIZE);
	ofstream f1;
	f1.open(filename2 + ".txt");
	cout << "******Display split******" << endl;
	f1 << "******Display split******" << endl;
	vector<pair<int, int>> tuples = { make_pair(0,variables_sp.size() - 1) };
	cout << "(" << last_split_size << "," << variables_sp.size() + last_split_size - 1 << ")" << endl;
	while (1)
	{
		
		vector<pair<int, int>> tmp_tuples;
		for (int i = 0; i < tuples.size(); i++)
		{
			int split_index;
			int start_index, end_index;
			int size;


			start_index = tuples[i].first;
			end_index = tuples[i].second;
			size = end_index - start_index + 1;
			split_index = variables_sp[size - 1][start_index].get(GRB_DoubleAttr_X);
			cout << "(" << start_index + last_split_size << "," << split_index + last_split_size << ") ";
			cout << "(" << split_index + last_split_size + 1 << "," << end_index + last_split_size << ") ";
			f1 << "(" << start_index + last_split_size << "," << split_index + last_split_size << ") ";
			f1 << "(" << split_index + last_split_size + 1 << "," << end_index + last_split_size << ") ";

			if (start_index != split_index)
			{
				tmp_tuples.push_back(make_pair(start_index, split_index));
			}
			if (split_index + 1 != end_index)
			{
				tmp_tuples.push_back(make_pair(split_index + 1, end_index));
			}
		}
		cout << endl;
		f1 << endl;
		tuples = tmp_tuples;
		if (tuples.size() == 0)
		{
			break;
		}
	}
	cout << endl << endl;
	f1 << endl << endl;
	f1.close();
}
