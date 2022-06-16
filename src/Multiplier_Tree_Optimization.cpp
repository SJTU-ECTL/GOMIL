/* Copyright 2018, Gurobi Optimization, LLC */

#include "gurobi_c++.h"
#include "Multiplier_Tree_Optimization.h"

void generate_input_patterns()
{
	//Construct input pattern
	for (int i = 1; i <= 2 * MULT_SIZE - 1; i++)
	{
		input_patterns.push_back(MULT_SIZE - abs(i - MULT_SIZE));
		//cout << *(input_patterns.end() - 1) << ",";
	}
}

void generate_variables_of_multiplier(vector<vector<GRBVar>>& variables_fa, vector<vector<GRBVar>>& variables_ha, vector<vector<GRBVar>>& variables_V, GRBModel& model)
{
	for (int i = 0; i < stages_num + 1; i++)
	{
		vector<GRBVar> variables_fa_of_each_stage;
		vector<GRBVar> variables_ha_of_each_stage;
		vector<GRBVar> variables_V_of_each_stage;
		stringstream ss;
		string tmp_s;
		for (int j = 0; j < input_patterns.size() + stages_num; j++)
		{
			if (i != 0)
			{
				ss << "f" << i << "_" << j;
				ss >> tmp_s;
				ss.clear();
				GRBVar variable_of_fa = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
				variables_fa_of_each_stage.push_back(variable_of_fa);

				ss << "h" << i << "_" << j;
				ss >> tmp_s;
				ss.clear();
				GRBVar variable_of_ha = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
				variables_ha_of_each_stage.push_back(variable_of_ha);
			}

			ss << "V" << i << "_" << j;
			ss >> tmp_s;
			ss.clear();
			GRBVar variable_of_V = model.addVar(0, INFINITY, 0, GRB_INTEGER, tmp_s);
			variables_V_of_each_stage.push_back(variable_of_V);
		}
		if (i != 0)
		{
			variables_fa.push_back(variables_fa_of_each_stage);
			variables_ha.push_back(variables_ha_of_each_stage);
		}
		variables_V.push_back(variables_V_of_each_stage);
	}

}

void Initial_constraints_of_V(vector<vector<GRBVar>> variables_V, GRBModel& model)
{
	for (int i = 0; i < input_patterns.size() + stages_num; i++)
	{
		if (i < stages_num)
		{
			model.addConstr(variables_V[0][i] == 0);
		}
		else
		{
			model.addConstr(variables_V[0][i] == input_patterns[i - stages_num]);
		}
		
	}
}

void generate_constraints_of_h_f_V(vector<vector<GRBVar>> variables_fa, vector<vector<GRBVar>> variables_ha, vector<vector<GRBVar>> variables_V, GRBModel& model)
{
	for (int i = 1; i < variables_V.size(); i++)
	{
		for (int j = 0; j < variables_V[i].size(); j++)
		{
			if (j == variables_V[i].size() - 1)
			{
				model.addConstr(variables_V[i][j] == 1);
				model.addConstr(variables_fa[i - 1][j] == 0);
				model.addConstr(variables_ha[i - 1][j] == 0);
			}
			else
			{
				model.addConstr(3 * variables_fa[i - 1][j] + 2 * variables_ha[i - 1][j] <= variables_V[i - 1][j]);
				model.addConstr(variables_V[i][j] == variables_V[i - 1][j] - variables_ha[i - 1][j] - 2 * variables_fa[i - 1][j] + (variables_ha[i - 1][j + 1] + variables_fa[i - 1][j + 1]));
			}
			

		}
	}
}

void generate_constraints_of_last_stage(vector<vector<GRBVar>> variables_V, GRBModel& model)
{
	for (int i = 0; i < variables_V[0].size() - 1; i++)
	{
		model.addConstr(variables_V[stages_num][i] <= 2);
		if (i >= stages_num)
		{
			model.addConstr(variables_V[stages_num][i] >= 1);
		}
	}
	//model.addConstr(variables_V[stages_num][variables_V[0].size() - 1] == 1);
}
void generate_cost_of_adders(vector<vector<GRBVar>> variables_fa, vector<vector<GRBVar>> variables_ha, GRBVar& fa_num, GRBVar& ha_num, GRBModel& model)
{
	GRBLinExpr obj = 0;
	GRBLinExpr fs = 0;
	GRBLinExpr hs = 0;

	for (int i = 0; i < variables_fa.size(); i++)
	{
		for (int j = 0; j < variables_fa[i].size(); j++)
		{
			fs += variables_fa[i][j];
			hs += variables_ha[i][j];
			//obj += (3 * variables_fa[i][j] + 2 * variables_ha[i][j]);
		}
	}
	ha_num = model.addVar(0, INFINITY, 0, GRB_INTEGER, "hs");
	fa_num = model.addVar(0, INFINITY, 0, GRB_INTEGER, "fs");
	model.addConstr(fs == fa_num);
	model.addConstr(hs == ha_num);
	//return obj;
}

