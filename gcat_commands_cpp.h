//========== tables used as indexes for the catalog
// in gcat_r4_cpp.cpp
extern uint32_t b1r4[417];
extern uint64_t b1startcat[417];

extern int GetMinir4id9992(int band, int* er4);
extern int GetMinir4id9992(int band, uint64_t rank);
extern void GetR4PointersFrom_minir4(int i9992, uint64_t& rstartcat,
	uint32_t& istartr4, uint32_t& iendr4);

extern int64_t row4t[10375];
extern int GetRow4tIndex(int64_t v);

extern uint16_t tr4u[652408];
extern uint16_t tr4nsol[652408];
//========================================
const char * zh_g_cpt[10] = { "npuz", "guess", "close_d ", "upd1 ", "upd2 ",
"fupd ", "hpair ", "htripl ", " ", " " };

const char * libs_c17_00_cpt2g[100] = {
	"0 bands1+2 processed entries M10",//0
	"1 total bands 3",//1
	"2 new 7_8 ",//2
	"3 3 clues ",	
	"4 6 clues ",	
	"5 after [4] ",
	"6 9 clues",
	"7 set b12 ",
	"8 go b3",
	"9 min ok g2 g3",

	"10 cpt nc128",
	"11 new 4_6 go",

	"12 expand 7",
	"13 cpt uas 7", 
	"14 active new6",
	"15 active exp 7",
	"16 entry expand 8",
	"17 uas expand 8",
	"18 active expand 8 ",

	"19 add guam",
	"20 addg2", 
	"21 addg3",
	"22  build9",
	"23 goa call",
	"24 after goa ",
	"25 gob call ",

	"26  dis5 trouve","27 dis4 trouve ",
	"28 dis3 trouve","29 dis2 trouve",

	"30 check valid2",
	"31 check valid3",
	"32 go subcrit ","33 ","34  ","35 ","36  ",	
	"37  old 7 ",
	"38 old 8", 
	"39 ",
	"40 40 filter  ",
	"41 7-8 cpt gtua8",
	"42 max gtua8",
	"43 max one gtu8",
	"44 ng2_8","45 ng2_9","46 n build9","47 ","48 ","49 ",
	"50 cpt 4","51 cpt 5 ",
	"52 cpt 7","53 cpt 7ok","54 cpt 7nc ",
	"55 crit 7","56 crit7ok ",
	"57 ","58 ","59  ",
	"60 cpt 8","61 cpt 8ok",
	"62 8 crit","63 8 critok",
	"64 8 ncrit","65 ","66 ","67 ","68 ","69 ",
	"70 ","71 ","72 ","73 ","74 ","75 ","76 ","77 ","78 ","79 ",
	"80 cumul ntg2","81 ","82 ","83 ","84 ","85 ","86 ","87 ","88 ","89 ",
	"90 ","91 ","92 ","93 ","94 ","95 ","96 ","97 ","98 ","99 ",

};


void BandReShape(int* s, int* d, BANDMINLEX::PERM p) {
	int * pc = p.cols;
	//uint8_t* pc = p.cols;
	for (int irow = 0; irow < 3; irow++) {
		int drow = 9 * irow;
		for (int icol = 0; icol < 9; icol++)
			d[drow + icol] = p.map[s[drow + pc[icol]]];
	}
	int temp[9];// now reorder 
	if (d[0] > d[9]) {
		memcpy(temp, &d[0], sizeof temp);
		memcpy(&d[0], &d[9], sizeof temp);
		memcpy(&d[9], temp, sizeof temp);
	}
	if (d[0] > d[18]) {
		memcpy(temp, &d[0], sizeof temp);
		memcpy(&d[0], &d[18], sizeof temp);
		memcpy(&d[18], temp, sizeof temp);
	}
	if (d[9] > d[18]) {
		memcpy(temp, &d[9], sizeof temp);
		memcpy(&d[9], &d[18], sizeof temp);
		memcpy(&d[18], temp, sizeof temp);
	}
}
void BandReOrder(int* d) {
	int temp[9];// now reorder 
	if (d[0] > d[9]) {
		memcpy(temp, &d[0], sizeof temp);
		memcpy(&d[0], &d[9], sizeof temp);
		memcpy(&d[9], temp, sizeof temp);
	}
	if (d[0] > d[18]) {
		memcpy(temp, &d[0], sizeof temp);
		memcpy(&d[0], &d[18], sizeof temp);
		memcpy(&d[18], temp, sizeof temp);
	}
	if (d[9] > d[18]) {
		memcpy(temp, &d[9], sizeof temp);
		memcpy(&d[9], &d[18], sizeof temp);
		memcpy(&d[18], temp, sizeof temp);
	}
}
int BandCompare(int* a, int* b) {
	for (int i = 0; i < 27; i++) {
		if (a[i] > b[i]) return 1;
		if (a[i] < b[i]) return -1;
	}
	return 0;

}
void BandDump(int* a, const char * lib) {
	for (int i = 0; i < 27; i++) cout << a[i] + 1;
	cout << " " << lib << endl;
}
void GridDump(int* a,const  char* lib) {
	for (int i = 0; i < 81; i++) cout << a[i] + 1;
	cout << " " << lib << endl;
}
void Table54Dump(uint64_t* tin, uint32_t ntin) {
	for (uint32_t i = 0; i < ntin; i++)
		cout << Char54out(tin[i]) << " " << i 
		<<" "<<_popcnt64(tin[i]) << endl;
}


struct CLBS {// clues band stack
	uint16_t b[3];
	uint16_t s[3];
	inline void Init(uint64_t bf54, uint16_t n) {
		register uint64_t U = bf54;
		b[0] = (uint16_t)_popcnt64(U & BIT_SET_27);
		b[1] = n - b[0];
		b[2] = 0;
		register uint64_t S = stack1_54;
		s[0] = (uint16_t)_popcnt64(U & S);
		S <<= 3;
		s[1] = (uint16_t)_popcnt64(U & S);
		s[2] = n - s[0] - s[1];
	}
	inline void Add(uint32_t cell) {
		b[cell / 27]++;
		s[C_stack[cell]]++;
	}
	
	void Status() {
		cout << " bx " << b[0] << b[1] << b[2]
			<< " sx " << s[0] << s[1] << s[2];

	}
};

void PermBands(char* z163, int* pi1, int* pi2, int i1, int i2) {
	register int ix = *pi1; *pi1 = *pi2; *pi2 = ix;
	char temp[27];
	memcpy(temp, &z163[27 * i1], 27);
	memcpy(&z163[27 * i1], &z163[27 * i2], 27);
	memcpy(&z163[27 * i2], temp, 27);
	memcpy(temp, &z163[27 * i1 + 82], 27);
	memcpy(&z163[27 * i1 + 82], &z163[27 * i2 + 82], 27);
	memcpy(&z163[27 * i2 + 82], temp, 27);
}
void BandReShapewithknown(int* s, char* d, char* sk, char* dk, BANDMINLEX::PERM p) {
	int* pc = p.cols;
	//uint8_t* pc = p.cols;
	for (int irow = 0; irow < 3; irow++) {
		int drow = 9 * irow;
		for (int icol = 0; icol < 9; icol++) {
			int x = p.map[s[drow + pc[icol]]];
			char c = sk[drow + pc[icol]],
				cx = (char)x + '1';
			d[drow + icol] = cx;
			if (c == '.')dk[drow + icol] = '.';
			else dk[drow + icol] = cx;
		}
	}
	char temp[9];// now reorder 
	char tempk[9];
	if (d[0] > d[9]) {
		memcpy(temp, &d[0], 9);
		memcpy(&d[0], &d[9], 9);
		memcpy(&d[9], temp, 9);
		memcpy(tempk, &dk[0], 9);
		memcpy(&dk[0], &dk[9], 9);
		memcpy(&dk[9], tempk, 9);
	}
	if (d[0] > d[18]) {
		memcpy(temp, &d[0], 9);
		memcpy(&d[0], &d[18], 9);
		memcpy(&d[18], temp, 9);
		memcpy(tempk, &dk[0], 9);
		memcpy(&dk[0], &dk[18], 9);
		memcpy(&dk[18], tempk, 9);
	}
	if (d[9] > d[18]) {
		memcpy(temp, &d[9], 9);
		memcpy(&d[9], &d[18], 9);
		memcpy(&d[18], temp, 9);
		memcpy(tempk, &dk[9], 9);
		memcpy(&dk[9], &dk[18], 9);
		memcpy(&dk[18], tempk, 9);
	}
}

struct T12A {
	char* ze, * zke;
	char zs[164], *zks;
	char zsr[164], * zksr;
	int zs0[82], ib1, ib2, ib3, ib1a, ib2a, ib3a,na;
	int  band2min[27], band2minr[27], tmini[108],nmini,
		band3min[27], tmini3[108], nmini3;
	BANDMINLEX::PERM* t_autom;

	void MorphToPerm(char* z, BANDMINLEX::PERM& p) {
		int z0[81];
		char s[164], * ks=&s[82],*ke=&z[82];	
		s[81] = ';'; ks[81] = 0;
		for (int i = 0; i < 81; i++) z0[i] = z[i] - '1';
		BandReShapewithknown(z0, s, ke, ks, p);
		BandReShapewithknown(&zs0[27], &s[27], &ke[27], &ks[27], p);
		BandReShapewithknown(&zs0[54], &s[54], &ke[54], &ks[54], p);
		memcpy(z, s, 164);

	}


	void Init(char* e) {
		ze = e;		
		zke = &ze[82]; zks = &zs[82];
		zs[81] = ';'; zks[81] = 0;
		BANDMINLEX::PERM perm_ret;
		bandminlex.Getmin(zs0, &perm_ret);
		ib1 = perm_ret.i416;  
		bandminlex.Getmin(&zs0[27], &perm_ret);
		ib2 = perm_ret.i416; 
		bandminlex.Getmin(&zs0[54], &perm_ret);
		ib3 = perm_ret.i416;  
		RigthOrder();
	}
	void RigthOrder() {
		if (ib2a < ib1a)PermBands(ze, &ib1a, &ib2a, 0, 1);
		if (ib3a < ib1a)PermBands(ze, &ib1a, &ib3a, 0, 2);
		if (ib3a < ib2a)PermBands(ze, &ib2a, &ib3a, 1, 2);
	}
	void Init13(char* e)
	{
		ze = e;
		zke = &ze[82]; zks = &zs[82];
		zs[81] = ';'; zks[81] = 0;
		BANDMINLEX::PERM perm_ret;
		bandminlex.Getmin(zs0, &perm_ret);
		ib1 = perm_ret.i416;  
		bandminlex.Getmin(&zs0[27], &perm_ret);
		ib2 = perm_ret.i416;  
		bandminlex.Getmin(&zs0[54], &perm_ret);
		ib3 = perm_ret.i416;  
	}

};
struct T12 {
	T12A zw, zwd;
	char zed[164]; 
	int mode;
	void Init(char* ze) {
		zed[81] = ';';
		zed[163] = 0;
		for (int i = 0; i < 81; i++) {
			register int id = C_transpose_d[i];
			zed[i] = ze[id];
			zed[82 + i] = ze[id + 82];
			zw.zs0[i] = ze[i] - '1';
			zwd.zs0[i] = ze[id] - '1';
		}
		zw.Init(ze); zwd.Init(zed);
	}
	void SetMode() {
		mode =0;
		if (zwd.ib1a > zw.ib1a) return;
		if (zwd.ib1a < zw.ib1a) { mode = 1; return; }
		if (zwd.ib2a > zw.ib2a) return;
		if (zwd.ib2a < zw.ib2a) { mode = 1; return; }
		if (zwd.ib3a < zw.ib3a) { mode = 1; }

	}
	void Init13(char* ze) {
		for (int i = 0; i < 81; i++) 			zw.zs0[i] = ze[i] - '1';
		zw.Init13(ze); 
	}

};
void Go_c17_10() {// test every..
	//for (int i = 0; i < 417; i++) cout << b1startcat[i] << " " << i << endl;
	//return;
	cout << "test every ???" << endl;
	cout << sgo.vx64[0] << " -v0- first sol" << endl;
	cout << sgo.vx64[1] << " -v1- every " << endl;
	cout << sgo.vx[2] << " -v2- if 1 printout asked" << endl;
	int it16_start = sgo.vx[0], it16_end = sgo.vx[1];
	memset(&op, 0, sizeof op);
	op.opcode = 10;
	op.b2 = sgo.vx[5];
	op.ton = sgo.vx[2];
	op.out_entry = op.ton;
	if (sgo.vx64[1] < 100000) {
		cout << "increment - v1 - too low" << endl;
		return;
	}
	uint64_t rank = sgo.vx64[0];
	int n = 0;
	while (rank < 5472730538) {
		genb12.s_rank = rank;
		if(!genb12.FindSolForRank())	genb12.GoSolForRank();

		rank += sgo.vx64[1];
		if(++n >10 )break;
	}
}
void Go_c17_11() {// search one given rank
	cout << "check one given rank" << endl;
	cout << sgo.vx64[0] << " -v0- rank searched" << endl;
	cout << sgo.vx[2] << " -v2- if 1 test find back" << endl;
	memset(&op, 0, sizeof op);
	op.opcode = 11;
	op.b2 = sgo.vx[5];
	op.ton = sgo.vx[2];
	op.out_entry = op.ton;

	genb12.s_rank = sgo.vx64[0];
	if (!genb12.FindSolForRank())	genb12.GoSolForRank();
	if (!sgo.vx[2]) return;
	cout << " test find back rank" << endl;
	if (genb12.FindRankForSolMin()) {
		genb12.GoSolForRank();
		char ze[82]; ze[81] = 0;
		for (int i = 0; i < 81; i++)
			ze[i] = genb12.s_grid0[C_transpose_rm[i]]+'1';
		cout << ze << " after rotate" << endl;
		genb12.GoSolForSearchRankFromNotMinSol(ze);
	}

}
void Go_c17_20() {// process 17 file to get CFX mode
	// search 17 using a file having known  as entry and one 17 given 6 6 5
	char* ze = finput.ze;
	uint64_t npuz = 0;
	op.ton = sgo.vx[0];
	cout << "Go_c17_20() band analysis build min get rank"
		<< " op.ton=" << op.ton << endl;
	while (finput.GetLigne()) {
		if (strlen(ze) < 81)continue;
		ze[81] = 0;
		if (npuz++ < sgo.vx[0])continue;
		//if (op.ton > 1)
		cout << ze << endl;
		genb12.GoSolForSearchRankFromNotMinSol(ze);

		if (npuz >= sgo.vx[1])return;
	}
}

void Go_c17_30() {// print the table or rows4
	cout << "print part of the row 4 table" << endl;
	cout << sgo.vx[0] << " -v0- first band 0-415" << endl;
	cout << sgo.vx[1] << " -v1- last band 0-415 " << endl;
	if (sgo.vx[1] < sgo.vx[0] || sgo.vx[1] >415) {
		cout << "illegal chunk of band 1" << endl;
		return;
	}
	for (uint32_t i = sgo.vx[0]; i <= sgo.vx[1]; i++) {
		genb12.InitBand1(i);
		uint32_t ir4a = b1r4[i], ir4b = b1r4[i + 1];
		uint64_t rank = b1startcat[i];
		for (uint32_t j = ir4a; j < ir4b; j++) {
			uint32_t jr4index = tr4u[j], jr4nsol=tr4nsol[j];
			genb12.InitRow4FromI10375(jr4index);
			for (int k = 0; k < 36;k++) fout1 << genb12.grid0[k] + 1;
			fout1 << ";" << i << ";" << j << ";" << rank <<";"<< jr4nsol << endl;
			rank += jr4nsol;
		}
	}

}
void Go_c17_31() {// print part of the cat for given rows 4
	cout << "print part of the row 4 table" << endl;
	cout << sgo.vx[0] << " -v0- first row4" << endl;
	cout << sgo.vx[1] << " -v1- last row4 " << endl;
	//if (!sgo.vx[0])sgo.vx[0] = 1;
	if (sgo.vx[1] < sgo.vx[0] || sgo.vx[1] >652408) {
		cout << "illegal chunk of rows4" << endl;
		return;
	}
	memset(&op, 0, sizeof op);
	op.opcode = 31;
	op.b2 = sgo.vx[5];
	op.ton = sgo.vx[2];
	op.out_entry = op.ton;
	memset(p_cptg, 0, sizeof p_cptg);// used in debugging sequences only
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	// Find the start using the band 
	for (uint32_t i = 0; i <= 415; i++) {
		genb12.InitBand1(i);
		uint32_t ir4a = b1r4[i], ir4b = b1r4[i + 1]-1;
		if (ir4a > sgo.vx[1])return;
		if (ir4b > sgo.vx[1])ir4b = sgo.vx[1] ;
		uint64_t rank = b1startcat[i];
		cout << "start band " << i << " start count " << p_cpt2g[50] << endl;
		p_cpt[14] = 0;
		for (uint32_t j = ir4a; j <= ir4b; j++) {
			uint32_t jr4index = tr4u[j], jr4nsol = tr4nsol[j];
			if (j < sgo.vx[0]) { rank += jr4nsol; continue; }
			genb12.InitRow4FromI10375(jr4index);
			genb12.s_rank = rank;
			if (1) {
				for (int k = 0; k < 36; k++) cout << genb12.grid0[k] + 1;
				cout << ";" << i << ";" << j << ";" << rank << ";" << jr4nsol << endl;
			}
			genb12.GoRow5();
			rank += jr4nsol;
		}
		cout << "seen for band " << i << " " << p_cpt[14] << endl;
		p_cpt2g[50] += p_cpt[14];
		if (ir4b == sgo.vx[1])break;
	}
	cout << "end count "<< p_cpt2g[50] << endl;
}
void Go_c17_80() {// enumeration test
	//return; // revise command line
	cout << "Go_c17_80 enumeration test  " << endl;
	cout << sgo.vx[0] << " -v0- first id 0_415" << endl;
	cout << sgo.vx[1] << " -v1- second id 0_415" << endl;
	cout << sgo.vx[2] << " -v2- if 1 printout asked" << endl;
	cout << sgo.vx[5] << " -v5- band 2 index if not 999" << endl;
	cout << sgo.vx[11] << " -vx- band 3 index if not 999" << endl;
	int it16_start = sgo.vx[0], it16_end = sgo.vx[1];
	memset(&op, 0, sizeof op);
	op.opcode = 81;
	op.ton = sgo.vx[2];
	op.b2 = sgo.vx[5];
	op.bx3 = sgo.vx[11];
	op.out_entry = op.ton;
	if (it16_start > 415 || it16_end > 415 || it16_start > it16_end) {
		cerr << "invalid it16_start it16_end" << endl;
		return;
	}
	memset(p_cptg, 0, sizeof p_cptg);// used in debugging sequences only
	memset(p_cpt2g, 0, sizeof p_cpt2g);
	p_cpt2g[5] = b1startcat[it16_start];
	for (int i416 = it16_start; i416 <= it16_end; i416++) {
		genb12.NewBand1(i416);
	}
}

void Go_c17_81() {// enumeration test using row4
	//return; // revise command line
	cout << "Go_c17_81 phase 2a enumeration test using r4" << endl;
	cout << sgo.vx[0] << " -v0- first id 0_415" << endl;
	cout << sgo.vx[1] << " -v1- second id 0_415" << endl;
	cout << sgo.vx[2] << " -v2- if 1 printout asked" << endl;
	int it16_start = sgo.vx[0], it16_end = sgo.vx[1];
	memset(&op, 0, sizeof op);
	op.opcode = 81;
	op.b2 = sgo.vx[5];
	op.ton = sgo.vx[2];
	op.out_entry = op.ton;
	if (it16_start > 415 || it16_end > 415 || it16_start > it16_end) {
		cerr << "invalid it16_start it16_end" << endl;
		return;
	}
	memset(p_cptg, 0, sizeof p_cptg);// used in debugging sequences only
	memset(p_cpt2g, 0, sizeof p_cpt2g);// used in debugging sequences only
	for (int i416 = it16_start; i416 <= it16_end; i416++) {
		int start = b1r4[i416], end = b1r4[i416 + 1];
		if (start == end) continue;
		genb12.InitBand1(i416);
		p_cpt2g[5] = b1startcat[i416];
		cout << i416 << " " << start << " "<<end << endl;
		for (int ir4 = start; ir4 < end; ir4++) {
			genb12.GoRow4From(ir4);
		}
	}
}

void Go_c17_90() {// read index extract first
	/*
// minus 1 in  b1startr4[417]
	{
		int n = 0,iw = 10, it = 0;;
		for (int i = 0; i < 417; i++) {
			uint64_t v = b1r4[i] - 1;
			fout1 << v << ",";
			iw--; it++;
			if (!iw) {
				iw = 10;
				fout1 << " //" << it << endl;
			}
		}
	}
	return;
	*/
	/*
	cout << "check dichotomy" << endl;
	//for (int i = 1023; i < 1024; i++) {

	for (int i = 0; i < 10375; i++) {
		int64_t v = row4t[i];
		int ir= GetRow4tIndex(v);
		if (ir != i) {
			cout<< i << " error search r4 "<<ir << endl;
			cout << v;
			if (ir >= 0)cout << " " << row4t[ir] << endl;
			else cout << endl;
			return;
		}
	}
	cout << "check dichotomy end" << endl;

	return;
	*/
/*
	int cum = 0;
	cout << "check b1r4" << endl;
	for (int i = 0; i < 416; i++) {
		int n = b1r4[i + 1] - b1r4[i];
		cum += n;
		cout << i << " " << n <<" "<<cum << endl;
	}
	return;
*/
	/*
	int max = 0;
	cout << "check minir4" << endl;
	for (int i = 0; i < 9992; i++) {

		uint16_t x=tr4u[i],y= tr4nsol[i];
		uint32_t istartr4, iendr4;
		uint64_t rstartcat;
		GetR4PointersFrom_minir4( i,  rstartcat, istartr4,  iendr4);
		int n =iendr4- istartr4;
		if (n > max) max = n;
		cout << i << " " << n << " "  << endl;
	}
	cout << " max count" << max << endl;


	return;	*/


	char* ze = finput.ze;
	int iw = 10, it = 0;
	//int iw = 9, it = 1;
	//fout1 << 0 << ",";// first 
	//cout << 0 << ",";// first 

	int oldb = -1, startitems = 0, oldstart = 0,
		maxnsol = 0, oldminir = 0, nminir = 0;;
	while (finput.GetLigne()) {
		startitems++;
		int band,minir4;
		int64_t nsol, r4, start;
		sgo.Parse_zin();
		//cout<<ze<<endl << sgo.nitems << " parameters" << endl;
		if (sgo.nitems < 4) {
			cout << " ligne invalide" << endl;
			return;
		}
		//for (int i = 0; i < sgo.nitems; i++)
		//	cout << sgo.items[i]<<" ";
		//cout << endl;
		band = atoi(sgo.items[0]);
		//r4=_atoi64(sgo.items[1]);
		r4 = strtoll( sgo.items[1],0,10);
		//start= _atoi64(sgo.items[2]);
		start = strtoll(sgo.items[2],0,10);
		//nsol = _atoi64(sgo.items[3]);
		nsol = strtoll(sgo.items[3],0,10);
		sgo.items[1][3] = 0;
		minir4 = atoi(sgo.items[1]);
/*
		if (band != oldb) {
			oldminir = 0;
			oldb = band;
		}
		if (minir4 != oldminir) {
			oldminir = minir4;
			fout1 << band << ";" << minir4
				<< ";"<< start << ";" << startitems-1 << endl;
		}
*/
/*
		if (nsol > maxnsol)maxnsol = nsol;
		fout1 << nsol << ",";
		iw--; it++;
		if (!iw) {
			iw = 10;
			fout1 << " //" << it << endl;
		}
*/
		//int64_t v = row4t[i];
		// 
/*
		int ir = GetRow4tIndex(r4);
		if (ir < 0) {
			cout << startitems << " error search r4 " << ir << endl;
			return;
		}
		int64_t v = row4t[ir];
		if (v != r4) {
			cout << startitems << "  r4 not ok  " << ir << endl;
			cout << v << " " << row4t[ir] << endl;
			return;
		}
		fout1 << ir << ",";
		iw--; it++;
		if (!iw) {
			iw = 10;
			fout1 << " //" << it << endl;
		}

*/
		fout1 << nsol << ",";
		iw--; it++;
		if (!iw) {
			iw = 10;
			fout1 << " //" << it << endl;
		}

/*
		if (band == oldb) continue;
		for (int i = oldb; i < band; i++) {
			fout1 << startitems-1 << ",";
			iw--; it++;
			if (!iw) {
				iw = 10;
				fout1 << " //" << it << endl;
			}
		}
		oldb = band;
*/

		//cout << band << " " << startitems - oldstart << endl;
		//oldstart = startitems;

	}
	//cout << " maxnsol" << maxnsol << endl;
	//fout1 << startitems  << endl;
}

const char* t444g[44] = {
"123456789123456789123456789","123456789123456789123457689",
"123456789123456789124357689","123456789123456789124378569",
"123456789123456789147258369","123456789123457689123458679",
"123456789123457689123468579","123456789123457689124356789",
"123456789123457689124358679","123456789123457689124367589",
"123456789123457689124368579","123456789123457689124389567",
"123456789123457689126345789","123456789123457689126347589",
"123456789123457689126348579","123456789123457689145267389",
"123456789123457689145268379","123456789123457689146258379",
"123456789123457689148259367","123456789124357689125348679",
"123456789124357689125367489","123456789124357689125368479",
"123456789124357689125378469","123456789124357689126358479",
"123456789124357689126378459","123456789124357689126389457",
"123456789124357689128345679","123456789124357689128356479",
"123456789124357689128359467","123456789124357689134258679",
"123456789124357689134268579","123456789124357689135268479",
"123456789124357689135278469","123456789124357689136258479",
"123456789124357689136278459","123456789124357689137268459",
"123456789124357689138259467","123456789124357689138269457",
"123456789124357689158267349","123456789124378569129356478",
"123456789124378569135279468","123456789124378569137245689",
"123456789124378569157268349","123456789147258369159267348",
};

int tpermgand[6][3] = { {0,1,2},{0,2,1},
	{1,0,2},{1,2,0},{2,0,1},{2,1,0} };
void Getpats18(int row, int* cols, int* pats) {
	int rowsx = 7 ^ (1 << row), row1, row2;
	bitscanforward(row1, rowsx); bitscanreverse(row2, rowsx);
	int c1 = 9 * row1 + cols[1], c2 = 9 * row2 + cols[2],
		c3 = 9 * row1 + cols[2], c4 = 9 * row2 + cols[1];
	pats[0] = 1 << c1 | 1 << c2;
	pats[1] = 1 << c3 | 1 << c4;
}
// minlex starts and gangsters minlex processing t416
struct GANGMINLEX {// receive a band send back i416 and morphing data
	int gb3[9], gb3d[9][3], gdcols[9][3],g0[27]; 
	int tcols[9], tcols_cols[9], tcols_count[9], tcols_stk[9], ntcols ;
	int tcolss[9];
	int t2x3[3], t2x3i[3], nt2x3, t2x2[20], t2x2i[20], nt2x2;
	int pat2sc[2], pat2s[2],pat2sv5;
	int cellmap[27], digitmap[9],igang,colmap[9],stackmap[3],stackmapb[3];
	void MappingInit() {
		for (int i = 0; i < 27; i++) cellmap[i] = i;
		for (int i = 0; i < 9; i++) digitmap[i] = i;
	}
	void SortTcols() {
		int n = 0;
		for (int i = 0; i < ntcols; i++)
			if (tcols_count[i] == 3)tcolss[n++] = i;
		for (int i = 0; i < ntcols ; i++)
			if (tcols_count[i] == 2)tcolss[n++] = i;
		for (int i = 0; i < ntcols ; i++)
			if (tcols_count[i] == 1)tcolss[n++] = i;

	}

	//int box_morphed[3][9], box_mapped[3][9], map[9];
	//int minirows[9], * bbx, * ccx, * rrx, ccx2[3], ccx3[3];
	void Init(int* o) {
		memcpy(g0, o, sizeof g0);
		memset(gb3, 0, sizeof gb3);
		ntcols = 0;
		for (int istk = 0, k = 0, icol = 0; istk < 3; istk++)
			for (int i = 0; i < 3; i++, icol++) {
				for (int j = 0; j < 3; j++, k++) {
					register int c = g0[k];
					gb3[icol] |= 1 << c;
					gb3d[icol][j] = c;
					gdcols[c][istk] = icol;
				}
				register int v = gb3[icol];
				for (int j = 0; j < ntcols; j++) {
					if (v == tcols[j]) {
						tcols_count[j]++;
						tcols_cols[j] |= 1 << icol;
						tcols_stk[j] |= 1 << istk;
						v = 0; break;
					}
				}
				if (v) {
					tcols_count[ntcols]=1; 
					tcols_cols[ntcols] = 1 << icol;
					tcols_stk[ntcols] = 1 << istk;
					tcols[ntcols++] = v; }
			}
		switch (ntcols) {
		case 3: Go3(); return;
		case 5: Go5(); return;
		case 6: Go6(); return;
		case 7: Go7(); return;
		case 8: Go8(); return;
		case 9: Go9(); return;
		}
	}
	void InitDump() {
		for (int i = 0; i < 27; i++) cout << g0[i] + 1;
		cout << " gangster  studied ntcols = " << ntcols << endl;
		for (int i = 0; i < ntcols; i++) {
			cout << Char9out(tcols[i]) << " count " << tcols_count[i];
			cout << " cols " << Char9out(tcols_cols[i]) 
				<< "  stk=" << tcols_stk[i] << endl;
		}

	}
	void InitNoMap() {
		memset(cellmap, 255, sizeof cellmap);
		memset(colmap, 255, sizeof colmap);
		memset(digitmap, 255, sizeof digitmap);
	}
/*
... . 1 1 ..1 
..1 . . . 11. 
11. 1 . . ... 

... . . . 111 
... 1 1 1 ... 
111 . . . ... */
	int IsPat2stkA(int* a, int* b) {//123456789 123457689
		int n  = 0;
		for (int i = 0; i < 3; i++) {
			int v1 = a[i];
			for (int j =0; j < 3; j++) {
				int v2= b[j],v1v2 = v1 & v2;
				if (_popcnt32(v1v2) == 2) {// pair v1v2
					if (n == 2) return 0;
					pat2sc[n ] = v1v2;
					pat2s[n ++] =v1|v2;
				}
			}
		}
		if (n != 2) return 0;
		int w = pat2s[0] | pat2s[1];
		if (_popcnt32(w) != 8) return 0;
		pat2sv5 = 0x1ff ^ w;
		return 1;
	}
	void DumpSort() {
		for (int i = 0; i < 27; i++) cout << g0[i] + 1;
		cout << " gangster  studied ntcols = " << ntcols << endl;
		for (int ix = 0; ix < ntcols; ix++) {
			int i= tcolss[ix];
			cout << Char9out(tcols[i]) << " count " << tcols_count[i];
			cout << " cols " << Char9out(tcols_cols[i])
				<< "  stk=" << tcols_stk[i]
				<< " isort="<<i << endl;
		}

	}	
	void DumpSort8() {
		for (int i = 0; i < 27; i++) cout << g0[i] + 1;
		cout << " gangster  studied ntcols = " << ntcols << endl;
		for (int ix = 1; ix < 4; ix++) {
			int i = tcolss[ix];
			cout << Char9out(tcols[i]) << " count " << tcols_count[i];
			cout << " cols " << Char9out(tcols_cols[i])
				<< "  stk=" << tcols_stk[i]
				<< " isort=" << i << endl;
		}

	}
	void Initt(const char* o) {// for test scrambled entry
		int d[27];
		for (int ic = 0,i=0; ic < 9; ic++) {
			const char* oic = &o[3 * (8 - ic)];
			for (int j = 0; j < 3; j++, i++)
				d[i] = oic[j]-'1';
		}
		Init(d);
	}
	inline void Map3( int v) {
		bitscanforward(digitmap[0], v);
		v ^= 1 << digitmap[0];
		bitscanforward(digitmap[1], v);
		bitscanreverse(digitmap[2], v);
	}
	inline void Map_2_1(int d0, int v1, int v2) {
		int d1, d2,d3;
		bitscanforward(d1, v1);
		bitscanreverse(d2, v1);
		bitscanforward(d3, v2);
		digitmap[d0++] = d1;
		digitmap[d0++] = d2;
		digitmap[d0] = d3;
	}
	inline void Map_1_2(int d0, int v1, int v2) {
		int d1, d2, d3;
		bitscanforward(d1, v1);
		bitscanforward(d2, v2);
		bitscanreverse(d3, v2);
		digitmap[d0++] = d1;
		digitmap[d0++] = d2;
		digitmap[d0] = d3;
	}
	inline void Map_1_1_1(int d0,int v1,int v2,int v3) {
		int d1, d2, d3;
		bitscanforward(d1, v1);
		bitscanforward(d2, v2);
		bitscanforward(d3, v3);
		digitmap[d0++] = d1;
		digitmap[d0++] = d2;
		digitmap[d0] = d3;
	}
	inline void MapC3(int c0, int v) {
		bitscanforward(colmap[c0], v);
		v ^= 1 << colmap[c0];
		bitscanforward(colmap[c0+3], v);
		bitscanreverse(colmap[c0 + 6], v);
	}
	inline void MapC2(int c0, int v) {
		bitscanforward(colmap[c0], v);
		bitscanreverse(colmap[c0+3], v);
	}
	inline void MapC1(int c0, int v) {
		bitscanforward(colmap[c0], v);
	}
	void BuildCellMap() {// just colmap to cellmap same rows
		for (int irow = 0,i=0; irow < 3; irow++) {
			register int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++,i++)
				cellmap[i] = drow + colmap[icol];
		}
	}
	void DumpMapping() {
		for (int i = 0; i < 27; i++) cout << g0[i] + 1;
		cout << " gangster  studied igang=" << igang << endl;
		for (int i = 0; i < 27; i++) cout << cellmap[i]<<" ";
		cout << " cells mapping" << endl;
		for (int i = 0; i < 9; i++) cout << colmap[i]<<" ";
		cout << " columns mapping" << endl;
		for (int i = 0; i < 9; i++) cout << digitmap[i]<<" ";
		cout << " digits mapping" << endl;

	}	
	void Check() {
		cout << "check mapping igang=" << igang << endl;
		for (int i = 0; i < 9; i++) {
			int* gc =&g0[ 3 * colmap[i]];
			for (int j = 0; j < 3; j++) {
				int c = gc[j];
				cout <<digitmap[c] + 1;
			}
			cout << " ";
		}
		cout << endl;
	}

	struct PERM {
		int i416;
		int rows[3], cols[9], map[9];
		inline void InitBase(int i16 = 0) {
			i416 = i16;
			for (int i = 0; i < 9; i++)		cols[i] = map[i] = i;
			for (int i = 0; i < 3; i++)		rows[i] = i;
		}
		void Dump() {
			cout << "perm status i416=" << i416 << endl;
			cout << "rows " << rows[0] << rows[1] << rows[2] << endl;
			cout << "cols " << cols[0] << cols[1] << cols[2]
				<< cols[3] << cols[4] << cols[5] << cols[6]
				<< cols[7] << cols[8] << endl;
			cout << "digs " << map[0] << map[1] << map[2]
				<< map[3] << map[4] << map[5] << map[6]
				<< map[7] << map[8] << endl;
		}
	}*pout;
	void Go3(){
		MappingInit();
		igang = 0;
		for (int i = 0; i < 9; i++)digitmap[i] = g0[i];
		DumpMapping();
	}
	void Go5() {
		igang = 1;
		int ostk12, ostk3,ostkx[3];
		SortTcols();
		//DumpSort();
		ostk12 = tcols_stk[tcolss[1]];// 
		ostk3 =7- ostk12;
		bitscanforward(ostkx[0], ostk12);
		bitscanreverse(ostkx[1], ostk12);
		bitscanforward(ostkx[2], ostk3);
		//cout << "stackorder " << ostkx[0] << " " << ostkx[1] << " "
		//	<< ostkx[2] << endl;
		for (int istk = 0; istk < 3; istk++) {
			register int mask = 7 << (3* ostkx[istk]),  c0 = 3 * istk,
				v= tcols_cols[tcolss[0]]&mask;
			bitscanforward(colmap[c0], v);
			if (istk < 2) {
				v = tcols_cols[tcolss[1]] & mask;
				bitscanforward(colmap[c0 + 1], v);
				v = tcols_cols[tcolss[2]] & mask;
				bitscanforward(colmap[c0 + 2], v);
			}
		}
		//for (int i = 0; i < 7; i++)cout << colmap[i];
		//cout << " column order 1-7" << endl;
		int vcoma = tcols[tcolss[1]] & tcols[tcolss[3]],
			va,vb,iva,ivb;
		if (_popcnt32(vcoma) == 2) {
			iva = tcolss[3], ivb = tcolss[4];
			va = vcoma; vb = tcols[tcolss[2]] & tcols[tcolss[4]];
		}
		else {
			ivb = tcolss[3], iva = tcolss[4];
			vb = vcoma; va = tcols[tcolss[2]] & tcols[iva];
		}
		//cout <<Char9out(va)<< " va " <<iva<< endl;
		//cout << Char9out(vb) << " vb "<<ivb << endl;
		colmap[7] = iva;		colmap[8] = ivb;
		// map digits using stack 3
		for (int i = 0; i < 3; i++)
			digitmap[i] = gb3d[colmap[6]][i];
		Map_2_1(3, va, tcols[iva]& ~va );
		Map_1_2(6, tcols[ivb] & ~vb, vb);
		BuildCellMap();
		DumpMapping();
	}
	void Go6() {
		SortTcols();
		//DumpSort();
		int vstk=tcols_stk[tcolss[0]];
		bitscanforward(stackmap[0], vstk);
		bitscanreverse(stackmap[1], vstk);
		vstk = 7 - vstk;
		bitscanforward(stackmap[2], vstk);
		//cout << "stackorder " << stackmap[0] << stackmap[1] << stackmap[2] << endl;
		int iv2x[3]={0,0,0}, nx[3];
		for (int i = 0; i < 3; i++) {
			register int vi = tcols[tcolss[i]];
			nx[i] = 0;
			for (int j = 3; j < 6; j++) {
				register int vj = tcols[tcolss[j]];
				if (_popcnt32(vi & vj) == 2) {
					nx[i] = 1; iv2x[i] = j;
					break;
				}
			}
		}
		int nt = nx[0] + nx[1] + nx[2];
		igang = (nt == 2) ? 2 : (nt == 3)?3 : 4;
		//cout << "n1=" << nx[0] << " n2=" << nx[1] << " n3=" << nx[2]
		//	<< " ig="<<igang << endl;
		int va, vac, var, vb, vbc, vbr, vc, vcc, vcr
			,va2,vb2,vc2;
		int ita1 = tcolss[0], ita2 = tcolss[iv2x[0]];
		int itb1, itb2, itc1, itc2;
	//	cout << iv2x[0] <<" " << iv2x[1] << " ivx" << endl;
		//return;
		if (igang != 4) {
			// get first triplet
			if (!nx[0]) { ita1 = tcolss[1]; ita2 = tcolss[iv2x[1]]; }
			va = tcols[ita1]; vac=	va & tcols[ita2];
			var = tcols[ita2] & ~va;
			//cout << Char9out(va) << " va ";
			//cout << Char9out(var) << " var ita1_2="
			//	<< ita1 << ita2 << endl;
			for (int i = 0; i < 3; i++) {
				vb = tcols[tcolss[i]];
				if (vb & var) {
					itb1 = tcolss[i];
					break;
				}
			}
			itc1 = tcolss[0]+ tcolss[1]+ tcolss[2] - ita1 - itb1;
			//cout << Char9out(vb) << " vb  itb1=" << itb1 << " itc1=" << itc1 << endl;
			vc = tcols[itc1];
			for (int i = 3; i < 6; i++) {
				vcc =vc& tcols[tcolss[i]];
				if (_popcnt32(vcc) == 2) {
					itc2 = tcolss[i];
					vcr = tcols[tcolss[i]] & ~vc ;
					break;
				}
			}
			itb2 = tcolss[3] + tcolss[4] + tcolss[5] - ita2 - itc2;
			vbc= vb & tcols[itb2];
			vbr= tcols[itb2] & ~vb;
			vcc = vc & tcols[itc2];
			vcr = tcols[itc2] & ~vc;
			//cout << Char9out(vb) << " vb ";
			//cout  << Char9out(vbr) << " vbr itb1_2="
			//	<< itb1 << itb2 << endl;
			//cout << Char9out(vc) << " vc ";
			//cout << Char9out(vcc) << " vcc ";
			//cout << Char9out(vcr) << " vcr itc1_2="
			//	<< itc1 << itc2 << endl;
			MapC2(0, tcols_cols[ita1]);
			MapC2(1, tcols_cols[itb1]);
			MapC2(2, tcols_cols[itc1]);
			MapC1(6, tcols_cols[ita2]);
			MapC1(7, tcols_cols[itb2]);
			MapC1(8, tcols_cols[itc2]);
			if (igang == 2) {// digits map
				Map_2_1(0, vac, va&~vac);
				Map_1_1_1(3, vb & var, vbc, vb & vcr);
				Map_1_2(6, vc & ~ vcc, vcc);
			}
			if (igang == 3) {// digits map
				Map_2_1(0, vac, va & ~vac);
				Map_1_2(3, var, vb & ~var);
				Map_1_2(6,vbr, vc & ~vbr);
			}
			BuildCellMap();
			DumpMapping();
		}
		else {//igang=4  no 2 digit match
			ita1 = tcolss[0]; itb1 = tcolss[1]; itc1 = tcolss[2];
			ita2 = tcolss[3]; itb2 = tcolss[4]; itc2 = tcolss[5];
			va = tcols[ita1]; va2 = tcols[ita2];
			vb = tcols[itb1]; vb2 = tcols[itb2];
			vc = tcols[itc1]; vc2 = tcols[itc2];
			MapC2(0, tcols_cols[ita1]);
			MapC2(1, tcols_cols[itb1]);
			MapC2(2, tcols_cols[itc1]);
			MapC1(6, tcols_cols[ita2]);
			MapC1(7, tcols_cols[itb2]);
			MapC1(8, tcols_cols[itc2]);
			Map_1_1_1(0, va & va2, va&vb2, va & vc2);
			Map_1_1_1(3, vb & va2, vb & vb2, vb & vc2);
			Map_1_1_1(6, vc & va2, vc & vb2, vc & vc2);
			BuildCellMap();
			DumpMapping();
		}

	}

	void Go7() {
		//InitDump();
		SortTcols();
		//DumpSort();
		InitNoMap();
		if (tcols_count[tcolss[0]] == 3)Go7_3();
		else Go7_22();
	}
	void Go7_3() {
		cout << "3111111 igang 5-6" << endl;
		int cmapdone = tcols_cols[tcolss[0]],icmx[3],
			col0= tcols[tcolss[0]];
		MapC3(0, cmapdone);
		Map3(col0);

		int vc, nc;
		for (int i = 1; i < 7; i++) {
			nc = 0;
			icmx[0] = tcolss[i];
			int  v = tcols[tcolss[i]];
			for (int j = i + 1; j < 8; j++) {
				int js = tcolss[j],v2 = tcols[js],
					v2c = v & v2;
				if (_popcnt32(v2c) == 2) {
					if (!nc) { nc++; vc = v2c; icmx[1] = js; continue; }
					if (v2c != vc) { nc = 0; break; }
					nc = 2; icmx[2] = js; break;
				}
			}
			if (nc == 2)break;
		}
		if (nc == 2) {// priority to colmap
			cout << "this is igang5" << endl;
			igang = 5;
			MapC1(1, tcols_cols[icmx[0]]);
			MapC1(4, tcols_cols[icmx[1]]);
			MapC1(7, tcols_cols[icmx[2]]);
			int va = tcols[icmx[0]], vb = tcols[icmx[1]],
				vc= tcols[icmx[2]];// 456 457 458
			int vx = tcols[tcolss[0]] | va | vb | vc;
			Map_2_1(3, va & vb, va & ~vb);
			Map_1_1_1(6, vb & ~va, vc & ~va, 0x1ff & ~(vx));
			cout << Char9out(vx) << " vx" << endl;

			cmapdone |= tcols_cols[icmx[0]] |
				tcols_cols[icmx[1]] | tcols_cols[icmx[2]];
			cout << Char9out(cmapdone) << " cmapdone" << endl;
			for (int j = 0,i=2; j <7; j++) {
				if (tcols_cols[j] & cmapdone) continue;
				MapC1(i, tcols_cols[j]);
				i += 3;
			}
			for (int j = 0; j < 8; j++)cout <<colmap[j];
			cout << "col mapping" << endl;
			BuildCellMap();
			DumpMapping();
			Check();
		}
		else {
			cout << "this is igang6" << endl;
			igang = 6;
			int ita = tcolss[1], sta = tcols_stk[ita],stan,
				va = tcols[ita], vac = tcols_cols[ita];
			int itb,itc,vb, vbc,vc,vcc,stb,stc,stbn,stcn,
				va2,vb2,vc2;
			bitscanforward(stan, sta);
			va2 = 0x1ff ^ (va | col0);
			int maska = 7 << (3 * stan),maskb,maskc;
			for (int j = 3; j < 5; j++) {
				itb = tcolss[j];
				vb = tcols[itb];
				vbc = tcols_cols[itb];
				vb2 = 0x1ff ^ (vb | col0);
				if (_popcnt32(va & vb) != 2) continue;
				stb = tcols_stk[itb];
				bitscanforward(stbn, stb);
				maskb = 7 << (3 * stbn);
				break;
			}
			for (int j = 5; j < 7; j++) {
				itc = tcolss[j];
				vc = tcols[itc];
				vcc = tcols_cols[itc];
				vc2 = 0x1ff ^ (vc | col0);
				if (_popcnt32(va & vc) != 2) continue;
				stc = tcols_stk[itc];
				bitscanforward(stcn, stc);
				maskc = 7 << (3 * stcn);
				break;
			}
			/*
			cout << Char9out(col0) << " 123" << endl;
			cout << Char9out(va) << " va 456" << endl;
			cout << Char9out(vb) << " vb 457" << endl;
			cout << Char9out(vc) << " vc 468" << endl;
			cout<< endl;
			cout << Char9out(va2) << " va2 789" << endl;
			cout << Char9out(vb2) << " vb2 689" << endl;
			cout << Char9out(vc2) << " vc2 579" << endl;
			*/
			int vab=va&vb,v4 = vab & vc,v5= vab & ~v4;
			Map_1_1_1(3, v4, vab & ~v4, va & ~vab);
			Map_1_1_1(6, vb & ~vab, vc & ~(va&vc), va2 &vb2&vc2);

			MapC1(0, maska & cmapdone); 
			MapC1(3, maskb & cmapdone);
			MapC1(6, maskc & cmapdone);
			MapC1(1, maska & vac);
			MapC1(2, maska &~( vac| cmapdone));
			MapC1(4, maskb & vbc);
			MapC1(5, maskb & ~(vbc | cmapdone));
			MapC1(7, maskc & vcc);
			MapC1(8, maskc & ~(vcc | cmapdone));
			BuildCellMap();
			DumpMapping();

		}
	}
	void Go7_22() {
		//cout << "2211111 igng 7_12" << endl;
		int stka = tcols_stk[tcolss[0]], stkb = tcols_stk[tcolss[1]];
		int stk1 = stka & stkb, stk2 = stka ^ stk1, stk3 = stkb ^ stk1;
		//cout << " stack order " << stk1 << stk2 << stk3 << endl;
		int stk1n, stk2n, stk3n;
		bitscanforward(stk1n, stk1);
		bitscanforward(stk2n, stk2);
		bitscanforward(stk3n, stk3);
		//cout << " stack order n " << stk1n << stk2n << stk3n << endl;

		int vc, nc,v123,v456,v789,v12,v45, v89, v3,v4,v6,v7,vx456;
		int it0 = tcolss[0], it1 = tcolss[1],it2;
		v123 = tcols[it0];
		for (int i = 2; i < 7; i++) {
			int it = tcolss[i], v = tcols[it], st = tcols_stk[it];
			if (st != stk2) continue;
			if (v & v123) {// this is v789
				it2 = it0; it0 = it1; it1 = it2;// perm  ito it1
			}
		}
		v123 = tcols[it0];
		v789 = tcols[tcolss[1]];
		v456 = 0x1ff & ~(v123 | v789);
		{//map columns for 123/789
			int cols = tcols_cols[it0], c1 = cols & (7 << 3 * stk1n);
			MapC1(0, c1); MapC1(3, cols & ~c1);
			cols = tcols_cols[it1]; c1 = cols & (7 << 3 * stk1n);
			MapC1(2, c1); MapC1(8, cols & ~c1);
		}
		for (int i = 2; i < 7; i++) {//st1 456 st2 457 689
			int it = tcolss[i], st = tcols_stk[it],
				v = tcols[it], col = tcols_cols[it];
			if (st == stk1) { MapC1(1, col); continue; }
			if (st == stk3)  continue;
			vc = v456 & v;	nc = _popcnt32(vc);
			if (nc == 2) {
				v45 = vc; v7 = v & ~vc;
				MapC1(4, col);
			}
			else {
				v6 = vc; v89 = v & ~vc;
				MapC1(5, col);
			}
		}
		for (int i = 2; i < 7; i++) {//stack3 124/356 or 126/345
			int it = tcolss[i], st = tcols_stk[it],
				v = tcols[it], col = tcols_cols[it];
			if (st!= stk3)  continue; 
			vc = v123 & v;	nc = _popcnt32(vc);
			if (nc == 2) {
				int  vr = v&~v123;
				v12 = vc; 
				if (vr == v6) {igang = 12;}
				else { igang = 7; v4 = vr; }
				MapC1(6, col);
			}
			else {
				v3 = vc; vx456 = v & ~vc;
				MapC1(7, col);
			}
		}
		Map_2_1(0, v12, v3);
		Map_1_2(6, v7, v89);
		if (igang == 7) Map_1_1_1(3, v4, v45&~v4, v6);
		else Map_2_1(3,  v45 , v6);
		BuildCellMap();
		DumpMapping();
		Check();
	}

	void Go8() {
		SortTcols();
		DumpSort8();
		InitNoMap();
		// all 123 456 789 |   123 457 689
		int v12,v45,v89,v3,v4,v5,v6,v7,v8,v9;
		int it1 = tcolss[0],st12= tcols_stk[it1],v123= tcols[it1],
			cols12= tcols_cols[it1];
		int itk12[45], itk3[3];// split tcolss
		// split tcolss stacks12/stack3
		{
			int n1 = 0, n2 = 0;
			for (int i = 1; i < 8; i++) {
				int j = tcolss[i];
				if (tcols_stk[j] & st12)itk12[n1++] = j;
				else itk3[n2++] = j;
			}
		}
		// find digits 67 and  45 or 89
		int vaxc, vbxc, vabxr;//45 or 89 and 67

		{
			int va = tcols[itk12[0]];
			for (int i = 2; i < 4; i++) {
				int va2 = tcols[itk12[i]];
				vaxc = va & va2;
				if (_popcnt32(vaxc) == 2) {
					vabxr = (va | va2) & ~vaxc;
					break;
				}
			}
			vbxc = tcols[itk12[1]] & ~vabxr;
			int v6n;// default v6 v7
			bitscanforward(v6n, vabxr);
			v6 = 1 << v6n;
			v7 = vabxr & ~v6;

			//cout << Char9out(vaxc) << " vaxc" << endl;
			//cout << Char9out(vbxc) << " vbxc" << endl;
			//cout << Char9out(vabxr) << " vabxr" << endl;
		}
		int st3it[3],st3is2=0;// sort stack3 on match with 123
		{
			int  st3it_1[3],n1 = 0;
			for (int i = 0; i < 3; i++) {
				int it = itk3[i],v= tcols[it],
					vc= v123&v,nvc= _popcnt32(vc);
				switch (nvc) {
					case 0:st3it[2] = it; break;
					case 1:st3it_1[n1++] = it; break;
					case 2:st3it[0] = it; st3is2 = 1; v12 = vc; break;
				}
			}
			if (st3is2)st3it[1] = st3it_1[0];
			else memcpy(st3it, st3it_1, sizeof st3it);
			cout << st3it[0] << st3it[1] << st3it[2] << " order is2=" << st3is2 << endl;
		}
		if (st3is2) {
			cout << " 124 8-11 or 126 13-14" << endl;
			// map cols 789
			{
				MapC1(6, tcols_cols[st3it[0]]); 
				MapC1(7, tcols_cols[st3it[1]]);
				MapC1(8, tcols_cols[st3it[2]]);		
			}

			int it = st3it[0], v = tcols[it], vc = v123 & v, vr = v & ~vc;
			v12 = vc;	v3 = v123 & ~vc;
			if (vr & vabxr) {
				cout << " 126 13-14" << endl;
				v6 = vr;
				v7 = vabxr & ~vr;
				int  vv = tcols[st3it[1]];
				if (vv & v7) igang = 13;	else igang = 14;
				switch (igang) {
				case 13: // 126 347 589
					v4 = tcols[st3it[1]] & ~(vabxr | v123);
					if (vaxc & v4) { v45 = vaxc; v89 = vbxc; }
					else { v45 = vbxc; v89 = vaxc; }
					int v8n;// default v8 v9
					bitscanforward(v8n, v89);
					v8 = 1 << v8n;
					v9 = v89 & ~v8;
					break;
				case 14:;// 126 348 579
					v45 = vaxc; v89 = vbxc;// default
					v4 = tcols[st3it[1]] & v45;
					v8 = v89 & tcols[st3it[1]];
					v9 = v89 & tcols[st3it[2]];
				}
			}		
			else {
				cout << " 124 8-11 " << endl;
				v4 = vr;
				if (vaxc & v4) {v45 = vaxc; v89 = vbxc; }
				else { v45 = vbxc; v89 = vaxc; }
				int v8n;// default v8 v9
				bitscanforward(v8n, v89);
				v8 = 1 << v8n;
				v9 = v89 & ~v8;

				int v2 = tcols[st3it[1]];
				if (v2 & v45) igang = 8;
				else if (!(v2 & vabxr)) igang = 11;
				else if (v2 & v89) igang = 10;
				else igang = 9;
				cout << "igang=" << igang << endl;
				switch (igang) {
					case 8: // 124 358 679
						v9 = v89 & tcols[st3it[2]];
						v8 = v89 & tcols[st3it[1]];
						break;
					//case 9: // 124 367 589 67 neutral 89 neutral
					//	break;
					case 10:// 124 368 579
						v6 = vabxr & tcols[st3it[1]];
						v7 = vabxr & tcols[st3it[2]];
						v8 = v89 & tcols[st3it[1]];
						v9 = v89 & tcols[st3it[2]];
						break;
					//case 11:// 124 389 567 67 neutral 89 neutral
					//	break;
				}

			}
			v5 = v45 & ~v4;
			// mapping digits and columns
			{
				Map_2_1(0, v12, v3);
				Map_1_1_1(3, v4, v5, v6);
				Map_1_1_1(6, v7, v8, v9);
				for (int i = 0; i < 3; i++)
					MapC1(6 + 7, tcols_cols[st3it[i]]);
				int v457 = v45 | v7, v456 = v45 | v6,
					v89 = v8 | v9, v689 = v6 | v89, v789 = v7 | v89;
				for (int i = 0; i < 4; i++) {
					int it = itk12[i], v = tcols[it], col = tcols_cols[it];
					if (v == v456) {
						MapC1(1, col);
						int stkn;
						bitscanforward(stkn, tcols_stk[it]);
						int mask = 7 << (3 * stkn);
						MapC1(0, cols12 & mask);
						MapC1(3, cols12 & ~mask);
					}
					else if (v == v457)MapC1(4, col);
					else if (v == v789)MapC1(2, col);
					else MapC1(5, col);
				}
			}
			BuildCellMap();
			DumpMapping();
			Check();
		}
		else {// 15-18 14/568 
			cout << " expected 15-18" << endl;
			v45 = vaxc;		v89 = vbxc; //  default
			int it1,xc1, x1;
			for (int i = 0; i < 3; i++) {
				it1 = st3it[i]; x1 = tcols[it1];
				xc1 = v45 & x1;
				if (xc1) break;
			}
			if (xc1 == v45) {
				//15 145 267 389
				//16 145 268 379
				int it2, xc2, x2;
				for (int i = 0; i < 3; i++) {
					it2 = st3it[i]; x2 = tcols[it1];
					xc2 = v89 & x2;
					if (xc2) break;
				}
			}
			else {
				int it2, xc2, x2;
				for (int i = 0; i < 3; i++) {
					it2 = st3it[i]; x2 = tcols[it1];
					xc2 = vabxr & x2;//67
					if (xc2) break;
				}
				//17 146 258 379
				//18 148 259 367
			}
			 
		}
	}
	void Go9() 	{
		int ispat2a = 0;
		int v12, v45, v89, v3, v4, v5, v6, v7, v8, v9;
		if (IsPat2stkA(&tcols[0], &tcols[3])) {
			cout << " possible 01 " << endl;
			ispat2a = 1;
			for (int i = 0; i < 9; i++)tcolss[i]=i;
		}
		else if (IsPat2stkA(&tcols[0], &tcols[6])) {
			cout << " possible 02 " << endl;
			ispat2a = 1;
			for (int i = 0; i < 3; i++)tcolss[i] = i;
			for (int i = 6; i < 9; i++)tcolss[i-3] = i;
			for (int i = 3; i < 6; i++)tcolss[i + 3] = i;
		}
		else if (IsPat2stkA(&tcols[3], &tcols[6])) {
			ispat2a = 1;
			cout << " possible 12 " << endl;
			for (int i = 3; i < 9; i++)tcolss[i - 3] = i;
			for (int i = 0; i < 3; i++)tcolss[i+6] = i;
		}
		if (!ispat2a) {	Go9_no_2a(); return;}
		v5 =pat2sv5;
		cout << Char9out(v5) << "  v5 " << endl;
		for (int i = 6; i < 9; i++) {
			int it=tcolss[i],v= tcols[it];
			if (v & v5) {
				int v12 = v & ~v5;
				if (v12 == pat2sc[0])	cout << Char9out(v12) << " v12="  << endl;
				if (v12 == pat2sc[1])	cout << Char9out(v12) << " v12="  << endl;
				else v12 = 0;
			}
			
		}
		DumpSort();
		return;
		nt2x2 = nt2x3 = 0;
		for (int i = 0; i < 3; i++) {
			int v1 = tcols[i];
			for (int j = 3; j < 6; j++) {
				int v1v2=v1& tcols[j];
				if (_popcnt32(v1v2) != 2) continue;
				for (int k = 6; k < 9; k++) {
					int v1v2v3 = v1v2 & tcols[k];
					if (v1v2v3==v1v2) {
						t2x3[nt2x3] = v1v2v3;
						t2x3i[nt2x3++] = (1 << i) | (1 << j) | (1 << k);
					}
					else {// pair v1v2
						t2x2[nt2x2] = v1v2;
						t2x2i[nt2x2++] = (1 << i) | (1 << j);
					}	
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			int v1 = tcols[i];
			for (int j = 6; j < 9; j++) {
				int v1v2 = v1 & tcols[j];
				if (_popcnt32(v1v2) == 2)  {// pair v1v2
					t2x2[nt2x2] = v1v2;
					t2x2i[nt2x2++] = (1 << i) | (1 << j);					
				}
			}
		}
		for (int i = 3; i <6; i++) {
			int v1 = tcols[i];
			for (int j = 6; j < 9; j++) {
				int v1v2 = v1 & tcols[j];
				if (_popcnt32(v1v2) == 2) {// pair v1v2
					t2x2[nt2x2] = v1v2;
					t2x2i[nt2x2++] = (1 << i) | (1 << j);
				}
			}
		}
		cout << "go9 see triplets nt2x3="<< nt2x3 <<"  nt2x2=" << nt2x2 << endl;
		switch (nt2x3) {
			case 0: Go9_0t(); return;
			case 1: Go9_1t(); return;
			case 2: Go9_2t(); return;
			case 3: Go9_3t(); return;
		}
	}
	void Go9_no_2a() {//0;43 2;38 3;42 4;33,36 5;34 6 ;40
		//10;29,31,35,37 11;32 13;30 15;41
		for (int i = 0; i < 27; i++) cout << g0[i] + 1;
		cout << " gangster  studied 9 cols "  << endl;

	}

	void Go9_0t(){//0;43 2;38 3;42 4;33,36 5;34 6 ;40
		//10;29,31,35,37 11;32 13;30 15;41

	}
	void Go9_1t() {//9;19,21,23,28 10;24,27 11;20 13;22,26
	}
	void Go9_2t() {// 11;20 12;25
	}
	void Go9_3t() {
		cout << "xpected 39 123456789 124378569 129356478" << endl;
		SortTcols();
		DumpSort();
	}

	inline void PermCols(int* source, int* dest, int* cc) {
		// unchecked dest must have same first 2 digits  as source
		cc[2] = 3;//0+1+2 sum of indexes
		for (int i = 0; i < 2; i++) {
			register int c = source[i]; // digit 0_8 to find in the second minirox
			for (int j = 0; j < 3; j++)
				if (c == dest[j]) { cc[i] = j; cc[2] -= j;	break; }
		}
	}

}gangminlex;

void Go_c17_91() {// test band3 using gangster
	cout << "process 91 band3 using template " << endl;
	int gb3[9], gb3d[9][3], gdcols[9][3];
	//int tpcols[4] = { 0111,0110,0101,011 };// column patterns
	int max4 = 0, max5 = 0, max6 = 0, max7 = 0, max8 = 0, max9 = 0;
	for (int ig = 15; ig < 44; ig++) {// 44 gangsters
		if (ig == 12)continue;
		//if (ig > 18)continue;
		cout << "igang expected=" << ig << endl;
		memset(gb3, 0, sizeof gb3);
		int tcolsx[9], count_tcolx[9], ntcolx = 0;
		memset(count_tcolx, 0, sizeof count_tcolx);
		const char* myg = t444g[ig];

		gangminlex.Initt(myg);
		continue;
		for (int istk = 0, k = 0, icol = 0; istk < 3; istk++)
			for (int i = 0; i < 3; i++, icol++) {
				for (int j = 0; j < 3; j++, k++) {
					register int c = myg[k] - '1';
					gb3[icol] |= 1 << c;
					gb3d[icol][j] = c;
					gdcols[c][istk] = icol;
				}
				register int v = gb3[icol];
				for (int j = 0; j < ntcolx; j++) {
					if (v == tcolsx[j]) {
						count_tcolx[j]++;
						v = 0; break;
					}
				}
				if (v) { count_tcolx[ntcolx]++; tcolsx[ntcolx++] = v; }
			}
		cout << myg << " gangster " << ig << "  studied ntcolx = " << ntcolx << endl;
		for (int i = 0; i < ntcolx; i++) {
			cout << Char9out(tcolsx[i]) << " " << count_tcolx[i] << endl;
		}
		switch (ntcolx) {
		case 3: cout << "gangster 0" << endl;
			continue;
		case 5: cout << "gangster 1" << endl;
			continue;
		case 6: {
			cout << "gangster 2,3,4 see minis with 2 fits" << endl;
			int n2fits = 0;
			for (int i = 0; i < ntcolx; i++) {
				if (count_tcolx[i] != 2) continue;
				for (int j = 0; j < ntcolx; j++) {
					if (count_tcolx[j] == 2) continue;
					if (_popcnt32(tcolsx[j] & tcolsx[i]) == 2)n2fits++;
				}
			}
			switch (n2fits) {
			case 0:cout << "gangster 4" << endl;
				continue;
			case 2:cout << "gangster 2" << endl;
				continue;
			case 3:cout << "gangster 3" << endl;
				continue;
			}
			continue;

		}
		case 7: {
			cout << "gangsters 5,6,7,12" << endl;
			int n2fits = 0;
			for (int i = 0; i < ntcolx; i++) {
				if (count_tcolx[i] != 1) continue;
				for (int j = i + 1; j < ntcolx; j++) {
					if (count_tcolx[j] != 1) continue;
					if (_popcnt32(tcolsx[j] & tcolsx[i]) == 2)n2fits++;
				}
			}
			cout << "n2fits=" << n2fits << endl;
			switch (n2fits) {
			case 2:cout << "gangster 7" << endl;
				continue;
			case 3:cout << "gangster 12" << endl;
				continue;
			case 6: {cout << "gangster 5 or 6" << endl;
				int done = 0;
				for (int i = 0; i < ntcolx; i++) {
					if (count_tcolx[i] != 1) continue;
					int n2fitsv = 0;
					for (int j = i + 1; j < ntcolx; j++) {
						if (count_tcolx[j] != 1) continue;
						if (_popcnt32(tcolsx[j] & tcolsx[i]) == 2)
							if (!n2fitsv) n2fitsv = tcolsx[j] & tcolsx[i];
							else if ((tcolsx[j] & tcolsx[i]) == n2fitsv) {
								cout << "gangster  5" << endl;
								done = 1; break;
							}
					}
					if (done)break;
				}
				if(!done){
					cout << "gangster  6" << endl;
				}
				continue;
			}
			}


			continue;
		}

		}

	}
	return;

}
struct B3PAT {
	int cx[2], pat;
	 
};
struct B3PATCUM {
	int b0[27], pat, index;
	BANDMINLEX::PERM p;
	void Init(B3PAT& o,int c1,int dig) {
		memset(b0, 255, sizeof b0);//  init to -1
		pat = o.pat;
		b0[c1] = b0[o.cx[0]] = b0[o.cx[1]] = dig;
	}
	void Cum(B3PATCUM & oc,B3PAT& o, int c1, int dig) {
		*this=oc;//  previous status
		pat |= o.pat;
		b0[c1] = b0[o.cx[0]] = b0[o.cx[1]] = dig;
	}
	void SetIndex() {
		bandminlex.Getmin(b0, &p);
		index = p.i416;	}
	void DumpB0() {
		for (int i = 0; i < 27; i++) cout <<b0[i] + 1;
		cout <<"\t"<<Char27out(pat) << endl;
	}

};
void Getpats18_b(int row, int* cols,  B3PAT* b3pats) {
	int rowsx = 7 ^ (1 << row), row1, row2;
	bitscanforward(row1, rowsx); bitscanreverse(row2, rowsx);
	int c1 = 9 * row1 + cols[1], c2 = 9 * row2 + cols[2],
		c3 = 9 * row1 + cols[2], c4 = 9 * row2 + cols[1];
	b3pats[0].pat = 1 << c1 | 1 << c2;
	b3pats[1].pat = 1 << c3 | 1 << c4;
	b3pats[0].cx[0] = c1;
	b3pats[0].cx[1] = c2;
	b3pats[1].cx[0] = c3;
	b3pats[1].cx[1] = c4;
}


void Go_c17_92() {// test band3 using gangster
	cout << "process 91 band3 using template " << endl;
	int gb3[9], gb3d[9][3], gdcols[9][3];
	//int tpcols[4] = { 0111,0110,0101,011 };// column patterns
	int max4 = 0, max5 = 0, max6 = 0, max7 = 0, max8 = 0, max9 = 0;
	B3PAT b3pats[9][2];
	B3PATCUM b3c1[2], b3c2[4], b3c3[8], b3c4[16], b3c5[32], b3c6[32],
		b3c7[32], b3c8[32], b3c9[32];
	for (int ig = 0; ig < 44; ig++) {// 44 gangsters
		//if (ig != 4)continue;
		memset(gb3, 0, sizeof gb3);
		const char* myg = t444g[ig];
		cout << myg << " gangster studied" << endl;
		for(int istk=0, k = 0,icol=0;istk<3;istk++)
			for(int i=0;i<3;i++,icol++)
				for (int j = 0; j < 3; j++,k++) {
					register int c = myg[k] - '1';
					gb3[icol] |= 1 << c;
					gb3d[icol][j] = c;
					gdcols[c][istk] = icol;
				}
		// build start compat
		int  nvalid=0,nb3c2 = 0, nb3c3 = 0,	perm2[3], perm3[3];


		for (int i = 0; i < 3; i++)
			Getpats18_b(i, gdcols[i], b3pats[i]);

		for (int i = 0; i < 2; i++) 
			b3c1[i].Init(b3pats[0][i], 0,0);

		for (int i = 0; i < 2; i++) {
			register int p = b3pats[1][i].pat;
			for (int j = 0; j < 2; j++) {
				register int pj = b3c1[j].pat;
				if (!(p & pj))
					b3c2[nb3c2++].Cum(b3c1[j], b3pats[1][i], 9, 1);
			}
		}
		for (int i = 0; i < 2; i++) {
			register int p = b3pats[2][i].pat;
			for (int j = 0; j < nb3c2; j++) {
				register int pj = b3c2[j].pat;
				if (!(p & pj))
					b3c3[nb3c3++].Cum(b3c2[j], b3pats[2][i], 18,2);
			}
		}
		if (1) {
			cout << "found " << nb3c3 << " triplets" << endl;
			for (int j = 0; j < nb3c3; j++)
				b3c3[j].DumpB0();
			//continue;
		}
		// push to col2 digits 3 4 5 / 4 5 6
		for (int ip2 = 0; ip2 < 6; ip2++) {
			int nb3c4 = 0, nb3c5=0, nb3c6 = 0;
			for (int jp2 = 0; jp2 < 3; jp2++)
				perm2[jp2] = gb3d[1][tpermgand[ip2][jp2]];
			for (int i = 0; i < 3; i++) {
				register int dig = perm2[i];
				Getpats18_b(i, gdcols[dig], b3pats[dig]);
			}
			// add cell row 1
			int d4 = perm2[0];
			for (int i = 0; i < 2; i++) {
				register int p = b3pats[d4][i].pat;
				for (int j = 0; j < nb3c3; j++) {
					register int pj = b3c3[j].pat;
					if (!(p & pj))
						b3c4[nb3c4++].Cum(b3c3[j], b3pats[d4][i], 1, d4);
				}
			}

			int d5 = perm2[1];
			for (int i = 0; i < 2; i++) {
				register int p = b3pats[d5][i].pat;
				for (int j = 0; j < nb3c4; j++) {
					register int pj = b3c4[j].pat;
					if (!(p & pj))
						b3c5[nb3c5++].Cum(b3c4[j], b3pats[d5][i], 10, d5);
				}
			}
			int d6 = perm2[2];
			for (int i = 0; i < 2; i++) {
				register int p = b3pats[d6][i].pat;
				for (int j = 0; j < nb3c5; j++) {
					register int pj = b3c5[j].pat;
					if (!(p & pj))
						b3c6[nb3c6++].Cum(b3c5[j], b3pats[d6][i], 19, d6);
				}
			}
			if (!nb3c6) continue;
			if (1) {
				cout << "found " << nb3c6 << " six" << endl;
				for (int j = 0; j < nb3c6; j++)b3c6[j].DumpB0();
				//continue;
			}
			for (int ip3 = 0; ip3 < 6; ip3++) {
				int nb3c7 = 0, nb3c8 = 0, nb3c9 = 0;
				for (int jp3 = 0; jp3 < 3; jp3++)
					perm3[jp3] = gb3d[2][tpermgand[ip3][jp3]];
				for (int i = 0; i < 3; i++) {
					register int dig = perm3[i];
					Getpats18_b(i, gdcols[dig], b3pats[dig]);
				}

				int d7 = perm3[0];
				for (int i = 0; i < 2; i++) {
					register int p = b3pats[d7][i].pat;
					for (int j = 0; j < nb3c6; j++) {
						register int pj = b3c6[j].pat;
						if (!(p & pj))
							b3c7[nb3c7++].Cum(b3c6[j], b3pats[d7][i], 2, d7);
					}
				}
				if (!nb3c7) continue;
				int d8 = perm3[1];
				for (int i = 0; i < 2; i++) {
					register int p = b3pats[d8][i].pat;
					for (int j = 0; j < nb3c7; j++) {
						register int pj = b3c7[j].pat;
						if (!(p & pj))
							b3c8[nb3c8++].Cum(b3c7[j], b3pats[d8][i], 11, d8);
					}
				}
				if (!nb3c8) continue;
				int d9 = perm3[2];
				for (int i = 0; i < 2; i++) {
					register int p = b3pats[d9][i].pat;
					for (int j = 0; j < nb3c8; j++) {
						register int pj = b3c8[j].pat;
						if (!(p & pj)) {
							nvalid++;
							B3PATCUM& myb3c = b3c9[nb3c9++];
							myb3c.Cum(b3c8[j], b3pats[d9][i], 20, d9);
							myb3c.SetIndex();
							for (int i = 0; i < 27; i++)
								fout1 << myb3c.b0[i] + 1;
							fout1 << ";" << ig << ";" << nvalid << "," << myb3c.index << endl;
						}
					}
				}
				if (!nb3c9) continue;
				cout << "found " << nb3c9 << " nine full cum="
					<< nvalid<< endl;
				if (nb3c9 > max9) max9 = nb3c9;
				if (nb3c8 > max8) max8 = nb3c8;
				if (nb3c7 > max7) max7 = nb3c7;
			}

			if (nb3c6 > max6) max6 = nb3c6;
			if (nb3c5 > max5) max5 = nb3c5;
			if (nb3c4 > max4) max4 = nb3c4;
		}

	}
	cout << " end max 4 5 6 =" << max4 << " " << max5 << " " << max6 << endl
		<< " max  7 8 9=" << max7 << " " << max8 << " " << max9	<< endl;

}

