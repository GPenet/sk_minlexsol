
#define _CRT_SECURE_NO_DEPRECATE
#define SEARCH17SOL


/* program organisation
	main is the standard frame including the basic brute force 
*/

#define GTEST17_ON 1
//============================================== 

#include <sys/timeb.h>
#include "main.h"  // main and main tables and basic brute force
#include "gcat_tables.h"     
extern SGO sgo;
//_________________ brute force handling 1 2 3 bands 

FINPUT finput;
ofstream  fout1, fout2;

#include "sk_gcath.h"   //main classes of the project
GEN_BANDES_12 genb12;


//tables of potential bands 1+2

uint64_t p_cptg[40], p_cpt1g[20], p_cpt2g[100];
uint64_t p_cpt[40], p_cpt1[20];

#include "gcat_commands_cpp.h" 
#include "gcat_genb12_cpp.h"     



void Go_0() {
	// open  outputs files 1.txt
	if (sgo.foutput_name) {
		char zn[200];
		strcpy(zn, sgo.foutput_name);
		int ll = (int)strlen(zn);
		strcpy(&zn[ll], "_file1.txt");
		fout1.open(zn);
	}
	int need_input_file[2] = { 20,90 },need=0;
	for(int i=0;i<1;i++)
		if (sgo.command == need_input_file[i]) { need = 1; break; }
	if (need){// input file expected
		if (!sgo.finput_name) {
			cerr << "missing input file name" << sgo.finput_name << endl; return;
		}
		finput.open(sgo.finput_name);
		if (!finput.is_open()) {
			cerr << "error open file " << sgo.finput_name << endl;
			return;
		}
	}
	cerr << "running command " << sgo.command << endl;
	switch (sgo.command) {
	case 10: Go_c17_10(); break; // test sample cat rank
	case 11: Go_c17_11(); break; // give sol for one rank
	case 20: Go_c17_20(); break; // rank on entry not min
	case 80: Go_c17_80(); break; // enumeration
	case 81: Go_c17_81(); break; // enumeration
	case 90: Go_c17_90(); break; // enumeration

	}
	cerr << "go_0 return" << endl;
}

