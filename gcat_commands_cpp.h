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