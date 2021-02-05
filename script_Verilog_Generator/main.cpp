#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "basic_block.h"
#include "Compress_Tree.h"
#include "Prefex_Tree.h"
#include "CSL.h"
#include "fast_mult.h"

using namespace std;

int main(int argc, char* argv[])
{
	FA_V();		HA_V();
	MUX_V();
	INF1_V();	INF2_V();
	PREF_ELEM1_V();	   PREF_ELEM2_V();    PREF_ELEM3_V();
	PRODUCTION_V();
	COMPRESS_TREE_V();
	Prefex_Tree_V();
	CSL_V();
	FAST_MULT_V();
	return 0;
}
