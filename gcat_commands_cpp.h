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

const char * libs_c17_00_cpt2g[100] = {
	"0  ", 	"1  ", 	"2   ", 	"3   ",	
	"4 row4 ",	
	"5 row5  ",
	"6 goband3 ",
	"7   ",	"8  ",
	"9 compte band 2 ",

	"10 count hit valid band found ",	"11 ",	"12 ",	"13 ", 	"14 ",
	"15 ",	"16 ",	"17 ",	"18  ",	"19",
	"20 ", 	"21 ",	"22 ",	"23 ",	"24  ",
	"25 ",

	"26  ","27 dis4 trouve ",
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
void Go_c17_20() {// rank for an entry not min lex
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
		//cout << "start band " << i << " start count " << p_cpt2g[50] << endl;
		p_cpt[14] = 0;
		for (uint32_t j = ir4a; j <= ir4b; j++) {
			uint32_t jr4index = tr4u[j], jr4nsol = tr4nsol[j];
			if (j < sgo.vx[0]) { rank += jr4nsol; continue; }
			genb12.InitRow4FromI10375(jr4index);
			genb12.s_rank = rank;
			if (op.ton) {
				for (int k = 0; k < 36; k++) cout << genb12.grid0[k] + 1;
				cout << ";" << i << ";" << j << ";" << rank << ";" << jr4nsol					
					<< "\t p_cpt2g[9]=" << p_cpt2g[9] << endl;
			}
			genb12.GoRow5();
			rank += jr4nsol;
		}
		if(p_cpt[14])
			cout << "seen for band " << i << " " << p_cpt[14] 
			<< " expected "<< b1startcat[i+1]- b1startcat[i] << endl;
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
#include "gcat_tgang.h"    
int tpermgang[6][3] = { {0,1,2},{0,2,1},
	{1,0,2},{1,2,0},{2,0,1},{2,1,0} };
int tpermg9stk[6][9] = {
	{0,1,2,3,4,5,6,7,8},{0,1,2,6,7,8,3,4,5},{3,4,5,0,1,2,6,7,8 } ,
	{3,4,5,6,7,8,0,1,2}, {6,7,8,0,1,2,3,4,5},{6,7,8,3,4,5,0,1,2} };
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
	int debug;
	int gb3[9], gb3d[9][3], gdcols[9][3],g0[27]; 
	int tcols[9], tcols_cols[9], tcols_count[9], tcols_stk[9], ntcols ;
	int tcolss[9];
	int t2x3[3], t2x3i[3], nt2x3, t2x2[20], t2x2i[20], nt2x2;
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
	void Init(int* o, int debugging = 0) {
		debug = debugging;
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
		if (debug) {
			cout << " init ntcols=" << ntcols << endl;
			SortTcols();
			DumpSort();
		}
		if (ntcols == 7 || ntcols == 8)Go78();
		switch (ntcols) {
		case 3: Go3(); return;
		case 5: Go5(); return;
		case 6: Go6(); return;
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
	int Checkvalid() {
		int a = 0, b = 0;
		for (int i = 0; i < 9; i++) {
			if (colmap[i] < 0 || digitmap[i] < 0) break;
			if (colmap[i] >8 || digitmap[i] >8) break;
			a |=1<<colmap[i] ; b |=1<< digitmap[i];
		}
		if (a == 0x1ff && b == 0x1ff) return 1;
		cout << "invalid or missing in mapping igan="<<igang << endl;
		for (int i = 0; i < 9; i++) cout << colmap[i] << " ";
		cout << " columns mapping" << endl;
		for (int i = 0; i < 9; i++) cout << digitmap[i] << " ";
		cout << " digits mapping" << endl;
		igang = -1;
		return 0;

	}
	int BuildCellMap() {// just colmap to cellmap same rows
		if (!Checkvalid()) return 0;
		for (int irow = 0,i=0; irow < 3; irow++) {
			register int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++,i++)
				cellmap[i] = drow + colmap[icol];
		}
		return 1;
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
			int* gc = &g0[3 * colmap[i]];
			for (int j = 0; j < 3; j++) {
				int c = gc[j];
				cout << digitmap[c] + 1;
			}
			cout << " ";
		}
		cout << endl;



		int rdigm[9];
		for (int i = 0; i < 9; i++) {
			rdigm[digitmap[i]] = i;
		}
		cout << "reverse check" << endl;
		for (int i = 0; i < 9; i++) cout << rdigm[i] << " ";
		cout << " digits mapping reverse" << endl;

		for (int i = 0; i < 9; i++)		{
			int* gc = &g0[3 * colmap[i]];
			for (int j = 0; j < 3; j++) {
				int c = gc[j];
				cout << rdigm[c] + 1;
			}
			cout << " ";
		}
		cout << endl;

	}
	void DumpT2x2() {
		cout << " pairs status nt2x2=" << nt2x2 << endl;
		for (int i = 0; i < nt2x2; i++) {
			cout << Char9out(t2x2[i]) << " ";
			cout << Char9out(t2x2i[i]) << endl;
		}
	}
	void DumpT2x3() {
		cout << " triplet  status nt2x3=" << nt2x3 << endl;
		for (int i = 0; i < nt2x3; i++) {
			cout << Char9out(t2x3[i]) << " ";
			cout << Char9out(t2x3i[i]) << endl;
		}
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
	struct STACKS12 {
		int v2c[3], v2[3], v2ab, v5, v2i[3], v2j[3], v67,
			st1,st2,st3;
		void Perm() {
			int x;
			x = v2c[0]; v2c[0] = v2c[1]; v2c[1] = x;
			x = v2[0]; v2[0] = v2[1]; v2[1] = x;
			x = v2i[0]; v2i[0] = v2i[1]; v2i[1] = x;
			x = v2j[0]; v2j[0] = v2j[1]; v2j[1] = x;
		}
		void PermIJ() {// exchange stacks 1 2
			int x;
			x = v2i[0]; v2i[0] = v2j[0]; v2j[0] = x;
			x = v2i[1]; v2i[1] = v2j[1]; v2j[1] = x;
			x = st1; st1 = st2; st2 = x;
		}
		void Dump() {
			cout << "stack12 status  " << endl;
			cout << Char9out(v2[0]) << "   ";
			cout << Char9out(v2c[0]) << " i=" << v2i[0] << " j=" << v2j[0] << endl;
			cout << Char9out(v2[1]) << "   ";
			cout << Char9out(v2c[1]) << " i=" << v2i[1] << " j=" << v2j[1] << endl;
			cout << Char9out(v5) << "  v5 " << endl;;

		}

	}go9stx[3], go78w;
	struct SA {// to do match on 124 357 689
		int zi1, zj1, zi2, zj2; // 2 pairs first is 12 last is 89
		int vza, vzb, st1n, st2n, st12, st3, st3n;
		int id1, id2, id3;// first in stack
		int zi3, zj3;// third item in stacks 1,2
		int j6, j7, j8, v12x;
		int i1, i2, i3, wa, wb, wc;
		int is1, is2, is3, wsa, wsb, wsc;
		int v12, v89, v345, v34, v3, vs3_3, vs3_m, v4, v5, v6, v7, v8, v9;
		int v123, v456, v789, v124, v357, v689, v125;
		void Init(STACKS12& z) {
			zi1 = z.v2i[0]; zj1 = z.v2j[0];
			zi2 = z.v2i[1]; zj2 = z.v2j[1];
			v12 = z.v2c[0]; v89 = z.v2c[1];
			vza = z.v2[0]; vzb = z.v2[1];
			v5 = z.v5;
			InitEnd();
		}
		void InitEnd() {// redo after perm i,j
			st1n = zi1 / 3; st2n = zj1 / 3;
			st12 = (1 << st1n) | (1 << st2n); st3 = 7 & ~st12;
			bitscanforward(st3n, st3);
			id1 = 3 * st1n; id2 = 3 * st2n; id3 = 3 * st3n;
			zi3 = 3 * id1 + 3 - zi1 - zi2;
			zj3 = 3 * id2 + 3 - zj1 - zj2;
		}

		void SortOnV5() {
			if (wa & v5) { wsa = wb; wsb = wc; wsc = wa; is1 = i2; is2 = i3; is3 = i1; }
			else if (wb & v5) { wsa = wa; wsb = wc; wsc = wb; is1 = i1; is2 = i3; is3 = i2; }
			else { wsa = wa; wsb = wb; wsc = wc; is1 = i1; is2 = i2; is3 = i3; }
		}
		void ReverseStack1Stack2() {
			wa = wsa; wsa = wsb; wsb = wa;
			i1 = is1; is1 = is2; is2 = i1;
		}
	};
	struct SB {// to do match on 124 378 569
		int ip, single;
		int v12, v78, v56, v1, v2, v3, v4, v5, v6, v7, v8, v9;
		int* p = tpermg9stk[ip];// order of the columns 
		int id1, id2, id3;// start for stacks 
	};
	struct S78 {
		int c0,ci, cj, ci2, cj2,cjst3[3], v123,v456, v789, v457, v689, v45, v89, v67,v6, v7;
		int st1,st2,st3, st1n, st2n, st3n,mask1,mask2,mask3;
		void Init(STACKS12& s, GANGMINLEX& o) {
			st1 = s.st1; st2 = s.st2; st3 = s.st3;
			bitscanforward(st1n, st1);
			bitscanforward(st2n, st2);
			bitscanforward(st3n, st3);
			mask1 = 7 << 3 * st1n; mask2 = 7 << 3 * st2n; mask3 = 7 << 3 * st3n;
			c0 = o.tcolss[0];
			ci = s.v2i[0]; cj = s.v2j[0];
			ci2 = s.v2i[1]; cj2 = s.v2j[1];
			v123 = o.tcols[c0];
			v456 = o.tcols[ci]; v457 = o.tcols[cj];
			v789 = o.tcols[ci2]; v689 = o.tcols[cj2];
			v45 = s.v2c[0]; v67 = s.v67; v89 = s.v2c[1];
			v6 = v67 & v456; v7 = v67 & v457;
			int n = 0;
			for (int i = 0; i < o.ntcols; i++)
				if (o.tcols_stk[i] & st3) cjst3[n++] = i;
			if (o.debug) {
				cout << "Go78PS12b() " << st1n << st2n << st3n << endl;
				cout << Char9out(v123) << " 123" << endl;
				cout << Char9out(v456) << " 456 ci " <<ci<< endl;
				cout << Char9out(v457) << " 457 cj " <<cj<< endl;
				cout << Char9out(v45) << " 45" << endl;
				cout << endl;
				cout << Char9out(v67) << " 67" << endl;
				cout << Char9out(v789) << " 789 ci2 "<<ci2 << endl;
				cout << Char9out(v689) << " 689 cj2 "<<cj2 << endl;
				cout << Char9out(v89) << " 89" << endl;
				cout << endl;
				cout << "stack3" << endl;
				for(int i=0;i<3;i++)
					cout << Char9out(o.tcols[cjst3[i]]) << " " << cjst3[i] << endl;
			}
			o.MappingInit();
			int cc = o.tcols_cols[c0];
			o.MapC1(0, cc&mask1); o.MapC1(3, cc & mask2);
			o.MapC1(1, o.tcols_cols[ci] & mask1); o.MapC1(4, o.tcols_cols[cj] & mask2);
			o.MapC1(2, o.tcols_cols[ci2] & mask1); o.MapC1(5, o.tcols_cols[cj2] & mask2);
		}
	}xs78;

	void Go3(){
		MappingInit();
		igang = 0;
		for (int i = 0,j=0,k=0; i < 3; i++,k++) {
			int v = tcols[i], cc = tcols_cols[i];
			int d,  c;
			bitscanforward(d, v);	bitscanforward(c, cc);
			digitmap[j++] = d; colmap[k] = c;
			v ^= 1 << d; cc ^= 1 << c;
			bitscanforward(d, v);	bitscanforward(c, cc);
			digitmap[j++] = d; colmap[k+3] = c;
			bitscanreverse(d, v); bitscanreverse(c, cc);
			digitmap[j++] = d; colmap[k+6] = c;
		}
		BuildCellMap();
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
		if(debug)
			cout << "stackorder " << ostkx[0] << " " << ostkx[1] << " "
				<< ostkx[2] << endl;
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
		int vcoma = tcols[tcolss[1]] & tcols[tcolss[3]],
			va,vb,iva,ivb;
		if (_popcnt32(vcoma) == 2) {
			iva = tcolss[3], ivb = tcolss[4];
			va = vcoma; vb = tcols[tcolss[2]] & tcols[tcolss[4]];
		}
		else {
			ivb = tcolss[3], iva = tcolss[4];
			va = tcols[tcolss[1]] & tcols[iva];
			vb = tcols[tcolss[2]] & tcols[ivb];
		}
		if (debug) {
			cout <<Char9out(va)<< " va " <<iva<< endl;
			cout << Char9out(vb) << " vb "<<ivb << endl;
		}
		 MapC1(7, tcols_cols[iva]); MapC1(8, tcols_cols[ivb]);
		// map digits using stack 3
		for (int i = 0; i < 3; i++)
			digitmap[i] = gb3d[colmap[6]][i];
		Map_2_1(3, va, tcols[ivb] & ~vb  );
		Map_1_2(6, tcols[iva] & ~va, vb);
	//	Map_2_1(6,vb, tcols[iva] & ~va);
		BuildCellMap();
		if (debug) {	DumpMapping(); Check();	}
	}

	/*
	"123456789123456789 124357689",
	"123456789123456789 124378569",
	"123456789123456789 147258369",*/
	void Go6() {
		SortTcols();
		//DumpSort();
		int vstk=tcols_stk[tcolss[0]];
		bitscanforward(stackmap[0], vstk);
		bitscanreverse(stackmap[1], vstk);
		vstk = 7 - vstk;
		bitscanforward(stackmap[2], vstk);
		if(debug)
		cout << "stackorder " << stackmap[0] << stackmap[1] << stackmap[2] << endl;
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
		if(debug)
		cout << "n1=" << nx[0] << " n2=" << nx[1] << " n3=" << nx[2]
			<< " ig="<<igang << endl;
		if (igang == 3) {
			int i0 = tcolss[0];
			int v123 = tcols[i0], v12, v3, v4, c6;
			MapC2(0, tcols_cols[i0]);

			// look for v124
			for (int ii = 3; ii < 6; ii++) {
				int i = tcolss[ii], v = tcols[i], vc = v & v123;
				if (_popcnt32(vc) == 2) {
					v12 = vc; c6 = i; v3 = v123 & ~vc; v4 = v & ~vc;
					MapC1(6, tcols_cols[c6]);
					break;
				}
			}
			// look for v456
			int v456, v56, i456, i789, v789;
			for (int ii = 1; ii < 3; ii++) {
				int i = tcolss[ii], v = tcols[i];
				if (v & v4) {
					v456 = v; i456 = i; v56 = v & ~v4;
					i789 = tcolss[3 - ii];
					v789 = tcols[i789];
					MapC2(1, tcols_cols[i456]);
					MapC2(2, tcols_cols[i789]);
					break;
				}
			}
			// look for v378
			int v378, v78, c7;
			for (int ii = 3; ii < 6; ii++) {
				int i = tcolss[ii], v = tcols[i];
				if (v & v3) {
					v378 = v; c7 = i; v78 = v & ~v3;
					MapC1(7, tcols_cols[c7]);
					break;
				}
			}
			for (int ii = 3; ii < 6; ii++) {
				int i = tcolss[ii], v = tcols[i];
				if (v & (v3 | v4)) continue;
				MapC1(8, tcols_cols[i]);
				break;
			}
			Map_2_1(0, v12, v3);
			Map_1_2(3, v4, v56);
			Map_2_1(6, v78, v789&~v78);
			BuildCellMap();
			return;
		}
		int va, vac, var, vb, vbc, vbr, vc, vcc, vcr
			,va2,vb2,vc2;
		int ita1 = tcolss[0], ita2 = tcolss[iv2x[0]];
		int itb1, itb2, itc1, itc2;
		if(debug)
		cout << iv2x[0] <<" " << iv2x[1] << " ivx" << endl;
		//return;
		if (igang != 4) {
			// get first triplet
			if (!nx[0]) { ita1 = tcolss[1]; ita2 = tcolss[iv2x[1]]; }
			va = tcols[ita1]; vac=	va & tcols[ita2];
			var = tcols[ita2] & ~va;
			if (debug) {
				cout << Char9out(va) << " va ";
				cout << Char9out(var) << " var ita1_2="
						<< ita1 << ita2 << endl;
			}
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
			BuildCellMap();
			//DumpMapping();
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
			//DumpMapping();
		}

	}
	void Go78() {
		SortTcols();
		if(debug)
		  cout << "search of pattern for 7_8" << endl;
		if (tcols_count[tcolss[1]] == 2) {
			//cout << " 2211111 en test" << endl;
			int x = tcols_stk[tcolss[0]], y = tcols_stk[tcolss[1]],
				st1 = x & y, st2 = x & ~st1;
			//cout << " try " << st1 << st2 << endl;
			//DumpSort();
			if (Go722PS12(st1, st2)) return;
				//cout << "ok for "<<st1<<st2	<< endl;
			int a = tcolss[0]; tcolss[0] = tcolss[1]; tcolss[1] = a;
			st2 = y & ~st1;
			//cout << " try " << st1 << st2 << endl;
			//DumpSort();
			if (Go722PS12(st1, st2)) return;
				//cout << "ok for " << st1 << st2 << endl;
		}
		else {// 311... if 7    211.. if 8
			int i0 = tcolss[0];
			if (debug)
				cout << "mode " << tcols_stk[i0] <<" i0="<<i0 << endl;
			switch (tcols_stk[i0]) {
			case 7: 
				if (debug)cout << "try 12" << endl;
				if (Go78PS12(1, 2)) return;
				//cout <<"ok for 12" << endl;
				if (debug)cout << "try 14" << endl;
				if (Go78PS12(1, 4)) return;
				 //cout << "ok for 14" << endl;

			case 6: 
				if (debug)cout << "try 2 4" << endl;
				if (Go78PS12(2, 4)) return;
				//cout << "ok for 24" << endl;
				break;
			case 5:	  if (Go78PS12(1, 4)) return;
				//cout << "ok for 14" << endl;
				break;
			case 3: if (Go78PS12(1, 2)) return;
				//cout << "ok for 12" << endl;
			}
		}
	}
	int Go722PS12(int st1, int st2) {//123456789 123457689
		//cout << "search stacks =" << st1 << st2 << endl;
		//DumpSort();
		STACKS12& s = go78w; //storing results
		s.st1 = st1; s.st2 = st2; s.st3 = 7 & ~(st1 | st2);
		int v123 = tcols[tcolss[0]], v789 = tcols[tcolss[1]],
			v456=0x1ff &~(v123|v789);
		//cout << Char9out(v456) << " v456" << endl;
		s.v2i[1] = tcolss[1]; 
		for (int ii = 2; ii < ntcols; ii++) {
			int i = tcolss[ii], va = tcols[i];
			if (va == v456) {s.v2i[0] = i;	continue;	}
			if (tcols_stk[i] != st2) continue;
			//cout << Char9out(va) << " va" << endl;
			if (_popcnt32(  va & v789)==2) {
				s.v2c[1] = va & v789;
				s.v2j[1] = i;
				s.v2[1] = va | v789;
			}
			else {// v457
				s.v2c[0] = va & v456;
				s.v2j[0] = i;
				s.v2[0] = va | v456;
			}
		}
		s.v67 = s.v2[0] & ~s.v2c[0];
		//cout << Char9out(s.v67) << " v67" << endl;
		//cout << Char9out(s.v2[1]) << " s.v2[1]" << endl;
		//cout << Char9out(s.v2c[1]) << " s.v2c[1]" << endl;
		if ((s.v2[1] & ~s.v2c[1]) != s.v67) return 0;
		// possible stack pair, try all st1 st3 123 789 lockedlocked
		return Go78PS12b();
	}
	int Go78PS12(int st1, int st2) {//123456789 123457689
		if(debug)
		cout << "search stacks =" << st1 << st2 << endl;
		STACKS12& s = go78w; //storing results
		int n = 0;
		for (int ii = 1; ii < ntcols; ii++) {
			int i = tcolss[ii];
			if (tcols_stk[i] != st1) continue;
			int va = tcols[i];
			if (debug) 
				cout << Char9out(va) << " va i=" <<i<< endl;
			for (int jj = 1; jj < ntcols; jj++) {
				int j = tcolss[jj];
				if (tcols_stk[j] != st2) continue;
				int vb = tcols[j], vab_c = va & vb;
				if (debug)
					cout << Char9out(vb) << " vb j=" << j << endl;

				if (_popcnt32(vab_c) == 2) {// pair v1v2
					if (debug) 		cout << "pair" << i << j << endl;
					s.v2c[n] = vab_c;
					s.v2i[n] = i;
					s.v2j[n] = j;
					s.v2[n++] = va | vb;
					break;
				}
			}
		}
		if (n != 2) return 0;
		s.v67 = s.v2[0] & ~s.v2c[0];
		if (debug) {
			cout << Char9out(s.v67) << " v67" << endl;

		}
		if ((s.v2[1] & ~s.v2c[1]) != s.v67) return 0;
		// possible stachk pair, try all
		s.st1 = st1; s.st2 = st2; s.st3 = 7 & ~(st1 | st2);
		if (Go78PS12b()) return 1;
		s.PermIJ(); if (Go78PS12b()) return 1;
		s.Perm();		if (Go78PS12b()) return 1;
		s.PermIJ();  return Go78PS12b();
	}
	int Go78PS12b() {
		xs78.Init(go78w, *this);
		int ir;
		if (ntcols == 7) {
			if (tcols_count[tcolss[0]] == 3)ir=Go7_3();
			else ir= Go7_22();
		}
		else {
			ir = Go8();
		}
		if (!ir)return 0;
		if (!BuildCellMap()) return 0;;
		//DumpMapping();
		//Check();
		return 1; 
	}
	int Go7_3() {
		//  123 458 679igang expected=5
		//  123 468 579igang expected=6
		if (debug) {
			cout << "3111111 igang 5-6 " << endl
				<< "123 458 679igang expected=5" << endl
				<< "123 468 579igang expected=6" << endl;
			cout << Char9out(xs78.v6) << " v6 " << endl;
			cout << Char9out(xs78.v7) << " v7 " << endl;
		}
		int vj6 = tcolss[0];
		{// map c6 and v123
			int cc = tcols_cols[vj6],c6=cc& xs78.mask3;
			MapC1(6, cc & xs78.mask3); 
			Map3(xs78.v123);
		}
		// still to check and do columns 8 9
		int vc9, vj9, vc8, vj8;
		for (int i = 0; i < 3; i++) {
			int j = xs78.cjst3[i];
			if (j == vj6) continue; // 123 column index 6
			int v = tcols[j];
			if (debug) 
				cout << Char9out(v) << " v " << j << endl;
			if (v & xs78.v7) {	vc9 = v; vj9 = j;	}
			else { vc8 = v; vj8 = j; }
		}
		MapC1(7, tcols_cols[vj8]); MapC1(8, tcols_cols[vj9]);
		int v8 = vc8 & xs78.v89, v9 = vc9 & xs78.v89;
		if (debug) {
			DumpSort();
			cout <<Char9out(vc8)<<" vc8 "<<vj8<<endl;
			cout << Char9out(v8) << " v8" << endl;
			cout << Char9out(vc9) << " vc9 "<<vj9 << endl;
			cout << Char9out(v9) << " v9" << endl;
		}

		if ((!v8) || (!v9) ) return 0; 
		if (vc8 & xs78.v6) {// this is gang6 123 468 579
			igang = 6;
			int v4 = vc8 & xs78.v45, v5 = vc9 & xs78.v45;
			Map_1_1_1(3, v4, v5, xs78.v6);
			Map_1_1_1(6, xs78.v7, v8, v9);
		}
		else{// this is gang5 123 458 679
			igang = 5;
			Map_2_1(3, xs78.v45, xs78.v6);
			Map_1_1_1(6, xs78.v7, v8, v9);
		}
		return 1;

	}
	int Go7_22() {
		// 124 356 789 igang 7
		// 126 345 789 igang 12
		int stx = tcols_stk[tcolss[0]] & tcols_stk[tcolss[1]];
		if (stx != xs78.st1) return 0;
		//cout << " try 7_22" << endl;
		// locate v12x in stack 3
		int vj6,v;
		for (int i = 0; i < 3; i++) {
			vj6 = xs78.cjst3[i]; v = tcols[vj6];
			if (_popcnt32(v & xs78.v123)==2) break;
		}
		int c6 = tcols_cols[vj6];
		int  c8 = tcols_cols[tcolss[1]] & xs78.mask3;
		MapC1(6, c6); 
		MapC1(8, c8); 
		MapC1(7, xs78.mask3 & ~(c6 | c8));

		int v12 = v & xs78.v123,v3 = xs78.v123 & ~v12,	
			vx = v & ~v12;
		//cout << Char9out(vx) << " vx in 7_22" << endl;
		if (!((xs78.v45 | xs78.v6) & vx)) return 0;
		Map_2_1(0, v12, v3);
		Map_1_2(6, xs78.v7, xs78.v89);
		int vc8 = 0x1ff & ~(v | xs78.v789);
		//cout << Char9out(vc8) << " vc8 in 7_22" << endl;
		if (vc8 & xs78.v6) {// this is gang 7
			igang = 7;
			int v4 = v & xs78.v45, v5 = vc8 & xs78.v45;
			Map_1_1_1(3, v4, v5, xs78.v6);
		}
		else {// this is gang 12 // 126 345 789 igang 12
			igang = 12;
			Map_2_1(3, xs78.v45, xs78.v6);
		}
		return 1;
	}
	int Go8() {
		//cout << "go8" << endl;
		//DumpSort();
		int vc6 = -1, vc7, vc8, ci6, ci7, ci8, v3, v12, vx;
		for (int i = 0; i < 3; i++) {
			int j = xs78.cjst3[i], v = tcols[j], vc = v & xs78.v123;
			if (vc) {
				if (_popcnt32(vc) == 2) { v12 = vc; vc6 = v; vx = v & ~vc; ci6 = j; }
				else { vc7 = v; v3 = vc; ci7 = j; }
			}
			else { vc8 = v; ci8 = j; }
		}
		if (vc6 < 0) return Go8No12();

		//cout << " thid igang 8_14 " << endl;
		//cout << Char9out(vc6) << " vc6 " << ci6 << endl;
		//cout << Char9out(vc7) << " vc7 " << ci7 << endl;
		//cout << Char9out(vc8) << " vc8 " << ci8 << endl;
		MapC1(6, tcols_cols[ci6]); MapC1(7, tcols_cols[ci7]);MapC1(8, tcols_cols[ci8]);
		Map_2_1(0, v12, v3);

		if (vx & xs78.v45) {
			if (vc7 & xs78.v45) {// 124 358 679igang expected=8
				igang = 8;
				Map_1_1_1(3, vx, vc7 & xs78.v45, xs78.v6);
				Map_1_1_1(6, xs78.v7, vc7 & xs78.v89, vc8 & xs78.v89);
				return 1;
			}
			else if (vc7 & xs78.v6) {
				if (vc7 & xs78.v7) {// 124 367 589igang expected=9
					igang = 9;
					Map_1_1_1(3, vx, vc8 & xs78.v45, xs78.v6);
					Map_1_2(6, xs78.v7, xs78.v89);
					return 1;
				}
				else {// 124 368 579igang expected=10
					igang = 10;
					Map_1_1_1(3, vx, vc8 & xs78.v45, xs78.v6);
					Map_1_1_1(6, xs78.v7, vc7 & xs78.v89, vc8 & xs78.v89);
					return 1;
				}
			}
			else if ((vc7 & xs78.v89) == xs78.v89) {// 124 389 567igang expected=11
				igang = 11;
				Map_1_1_1(3, vx, vc8 & xs78.v45, xs78.v6);
				Map_1_2(6, xs78.v7, xs78.v89);
				return 1;
			}
			else return 0;


		}
		else if (vx & xs78.v6) {
			int v4 = vc7 & xs78.v45, v5 = vc8 & xs78.v45;
			if (!v4) return 0;
			Map_1_1_1(3, v4,v5, xs78.v6);
			if (vc7 & xs78.v7) {//126 347 589igang expected=13
				igang = 13;
				Map_1_2(6, xs78.v7, xs78.v89);
				return 1;
			}
			else {// 126 348 579igang expected=14
				igang = 14;
				Map_1_1_1(6, xs78.v7, vc7 & xs78.v89, vc8 & xs78.v89);
				return 1;
			}
		}
		return 0;
	}

	int Go8No12() {
		//cout << "go8 no 12" << endl;
		int vc6 , vc7, vc8 = -1, ci6, ci7, ci8, v3,  vx;
		for (int i = 0; i < 3; i++) {
			int j = xs78.cjst3[i], v = tcols[j], vc = v & xs78.v789;
			if (vc) {
				if (_popcnt32(vc) == 2) { vc8 = v; vx = v & ~vc; ci8 = j; }
				else { vc7 = v; v3 = vc; ci7 = j; }
			}
			else { vc6 = v; ci6 = j; }
		}


		if (vc8 < 0) {//148 259 367igang expected=18
			//cout << "could be igang 18" << endl;
			int n = 0;
			vc8 = -1;
			for (int i = 0; i < 3; i++) {
				int j = xs78.cjst3[i], v = tcols[j], vc = v & xs78.v67;
				if (vc) {
					if (_popcnt32(vc) != 2) return 0;
					vc8 = v; v3 = v & ~vc; ci8 = j;		
				}
				else if(n){ vc7 = v; ci7 = j; }
				else { vc6 = v; ci6 = j; n++; }
			}
			if (vc8 < 0) return 0;
			igang = 18;
			MapC1(6, tcols_cols[ci6]); MapC1(7, tcols_cols[ci7]); MapC1(8, tcols_cols[ci8]);
			register int r = xs78.v123;
			Map_1_1_1(0, vc6 & r,  vc7 & r,  vc8 & r);
			r= xs78.v456;
			Map_1_1_1(3, vc6 & r, vc7 & r, vc8 & r);
			r = xs78.v789;
			Map_1_1_1(6, vc8 & r, vc6 & r, vc7 & r);
			return 1;
		}

		//cout << " thid igang 15_17 " << endl;

		//cout << Char9out(vc6) << " vc6 " << ci6 << endl;
		//cout << Char9out(vc7) << " vc7 " << ci7 << endl;
		//cout << Char9out(vc8) << " vc8 " << ci8 << endl;

		MapC1(6, tcols_cols[ci6]); MapC1(7, tcols_cols[ci7]); MapC1(8, tcols_cols[ci8]);
		Map_1_1_1(0, vc6 & xs78.v123, vc7 & xs78.v123, vc8 & xs78.v123);

		if (vc6 & xs78.v6){// 146 258 379i gang expected=17
			igang = 17;
			if(! (vc8 & xs78.v7)) return 0;
			Map_1_1_1(3, vc6 & xs78.v45, vc7 & xs78.v45, xs78.v6);
			Map_1_1_1(6, xs78.v7, vc7 & xs78.v89, vc8&xs78.v89);
			return 1;
		}
		if ((vc6 & xs78.v45) != xs78.v45)return 0;
		if (vc7 & xs78.v7) {//145 267 389i gang expected = 15
			igang = 15;
			Map_2_1(3, vc6 & xs78.v45,  xs78.v6);
			Map_1_2(6, xs78.v7,  xs78.v89);
			return 1;
		}
		else { //145 268 379igang expected=16
			igang = 16;
			Map_2_1(3, vc6 & xs78.v45, xs78.v6);
			Map_1_1_1(6, xs78.v7, vc7&xs78.v89,vc8 & xs78.v89);
			return 1;

		}
		return 0;

	}
	

	//================ all columns different patterns
	// 123 456 789 and 124 357 689 or 124 378 569
	void Go9SetTripletsPairs() {
		nt2x2 = nt2x3 = 0;
		for (int i = 0; i < 3; i++) {
			int v1 = tcols[i];
			for (int j = 3; j < 6; j++) {
				int v1v2 = v1 & tcols[j];
				if (_popcnt32(v1v2) != 2) continue;
				int nt2x3r = nt2x3;
				for (int k = 6; k < 9; k++) {
					int v1v2v3 = v1v2 & tcols[k];
					if (v1v2v3 == v1v2) {
						t2x3[nt2x3] = v1v2v3;
						t2x3i[nt2x3++] = (1 << i) | (1 << j) | (1 << k);
					}
				}
				if(nt2x3r == nt2x3){// pair v1v2
					t2x2[nt2x2] = v1v2;
					t2x2i[nt2x2++] = (1 << i) | (1 << j);
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			int v1 = tcols[i];
			for (int j = 6; j < 9; j++) {
				int v1v2 = v1 & tcols[j];
				if (_popcnt32(v1v2) == 2) {// pair v1v2
					t2x2[nt2x2] = v1v2;
					t2x2i[nt2x2++] = (1 << i) | (1 << j);
				}
			}
		}
		for (int i = 3; i < 6; i++) {
			int v1 = tcols[i];
			for (int j = 6; j < 9; j++) {
				int v1v2 = v1 & tcols[j];
				if (_popcnt32(v1v2) == 2) {// pair v1v2
					t2x2[nt2x2] = v1v2;
					t2x2i[nt2x2++] = (1 << i) | (1 << j);
				}
			}
		}
		//cout << "go9 see triplets nt2x3=" << nt2x3 << "  nt2x2=" << nt2x2 << endl;
	}

		/* typical pattern for stacks12   123 456 789   123 457 689
	... . 1 1 ..1   most common pattern by far
	..1 . . . 11.
	11. 1 . . ...

	... . . . 111
	... 1 1 1 ...
	111 . . . ... */
	int g9stxv, g9stx5,g9stx56,g9stxv5ors3, g9stxv5or;

	int Go9PS12_78(int ip,int x123) {//123456789 123457689
		cout << "search ip =" << ip << endl;
		int* p = tpermg9stk[ip];// order of the columns 
		STACKS12& s = go9stx[ip]; //storing results
		int n = 0;
		for (int ii = 0; ii < 3; ii++) {
			int i = p[ii], v1 = tcols[i];
			if (v1 == x123) continue;
			for (int jj = 3; jj < 6; jj++) {
				int j = p[jj], v2 = tcols[j], v1v2 = v1 & v2;
				if (v2 == x123) continue;
				if (_popcnt32(v1v2) == 2) {// pair v1v2
					cout << "pair" << i << j << endl;
					s.v2c[n] = v1v2;
					s.v2i[n] = i;
					s.v2j[n] = j;
					s.v2[n++] = v1 | v2;
				}
			}
		}
		if (n != 2) return 0;
		s.v67 = s.v2[0] & ~s.v2c[0];
		cout << Char9out(s.v67) << " v67" << endl;

		if ((s.v2[1] & ~s.v2c[1]) != s.v67) return 0;
		return 1;
	}

	int Go9PS12(int ip) {
		int* p = tpermg9stk[ip];// order of the columns 
		STACKS12& s = go9stx[ip]; //storing results
		int n = 0;
		for (int ii = 0; ii < 3; ii++) {
			int i = p[ii], v1 = tcols[i];
			for (int jj = 3; jj < 6; jj++) {
				int j = p[jj], v2 = tcols[j], v1v2 = v1 & v2;
				if (_popcnt32(v1v2) == 2) {// pair v1v2
					if (n == 2) return 0;
					s.v2c[n] = v1v2;
					s.v2i[n] = i;
					s.v2j[n] = j;
					s.v2[n++] = v1 | v2;
				}
			}
		}
		if (n != 2) return 0;
		int w = s.v2[0] | s.v2[1];
		if (_popcnt32(w) != 8) return 0;
		s.v5 = 0x1ff ^ w;
		//cout << Char9out(s.v5) << " v5 after ip= " << ip << endl;
		return 1;
	}
	int Go9PS12B(int ip) {
		int* p = tpermg9stk[ip];// order of the columns 
		STACKS12& s = go9stx[ip]; //storing results
		int n = 0;
		for (int ii = 0; ii < 3; ii++) {
			int i = p[ii], v1 = tcols[i];
			for (int jj = 3; jj < 6; jj++) {
				int j = p[jj], v2 = tcols[j], v1v2 = v1 & v2;
				if (_popcnt32(v1v2) == 2) {// pair v1v2
					s.v2c[n] = v1v2;
					s.v2[n++] = v1 | v2;
				}
			}
		}
		if (n != 3) return 0;
		int w = s.v2c[0] | s.v2c[1] | s.v2c[2];
		s.v5 = 0x1ff ^ w;
		//cout << Char9out(w) << " ";
		//cout << Char9out(s.v5) << " pat b after ip= " << ip << endl;
		return 1;
	}
	void Go9SetPossibleStacks12() {
		g9stxv = g9stx5 = g9stx56 = g9stxv5or = g9stxv5ors3 = 0;
		for (int ip = 0; ip < 3; ip++) {
			int* p = tpermg9stk[ip];// order of the columns 
			STACKS12& s = go9stx[ip]; //storing results
			int ir = Go9PS12(ip);
			if (ir) {
				int x5 = s.v5;
				g9stxv5or |= x5;
				//cout << Char9out(s.v5) << " v5 for  possible ip= " << ip << endl;
				if (nt2x3) {
					for (int i = 6; i < 9; i++) {
						int it = p[i], v = tcols[it];
						if (v & x5) {
							int x12 = v & ~x5;
							if (x12 == s.v2c[0] || x12 == s.v2c[1]) {
								if (!g9stx5)g9stx56 = g9stxv = 0;
								g9stx5 |= 1 << ip;
								g9stxv5ors3 |= x5;
								break;
							}
						}
					}
					g9stx56 |= 1 << ip;
				}
				else if (g9stx56) continue;
				//cout << " possible added  " << endl;
				g9stxv |= 1 << ip;
			}
		}
	}
	void Go9SetPossibleStacks12B() {
		g9stxv = g9stx5 = g9stx56 = 0;
		for (int ip = 0; ip < 3; ip++) {
			int* p = tpermg9stk[ip];// order of the columns 
			STACKS12& s = go9stx[ip]; //storing results
			int ir = Go9PS12B(ip);
			if (ir) {
				g9stxv |= 1 << ip;
			}
		}
	}
	int Go9End(int ir) {
		if(ir!=1 )return 0;
		if (!BuildCellMap()) return 0;
		//DumpMapping();
		//Check();
		return 1;
	}
	void Go9() {
		Go9SetTripletsPairs();
		Go9SetPossibleStacks12();
		//SortTcols();
		//DumpSort();
		//cout << "go9 nt2x3=" << nt2x3 << "  nt2x2=" << nt2x2
			//<< " g9stxv = " << g9stxv << " x5 = " << g9stx5
			//<< " x56 = " << g9stx56 << endl;
		if(!g9stxv) { Go9_no_2a(); return; }
//==========================  pattern 123 456 789 124 357 689 somewhere
		for (int i = 0, bit = 1; i < 3; i++, bit <<= 1) if (bit & g9stxv) {
			STACKS12 z = go9stx[i];//int v2c[3], v2[3], v2ab, v5;
			//z.Dump();
			int ir;
			if (nt2x3) {
				for (int ii = 0; ii < nt2x3; ii++) {
					int va = t2x3[ii], ita = t2x3i[ii];
					if (va == z.v2c[1])z.Perm();
					if (va != z.v2c[0]) continue;
					//cout << "must go with" << endl;
					//z.Dump();
					ir = Go9a(z);
					//cout << ir << " back from goa" << endl;
					if (Go9End(ir)) return;
					if (ir < 0) {
						//cout << " try reverse stack1 stack2" << endl;
						z.PermIJ();
						ir = Go9a(z);
						//cout << ir << " back from goa" << endl;
						if (Go9End(ir)) return;
					}
				}
			}
			else {// try both
				//cout << "try first " << endl;
				//z.Dump();
				ir = Go9a(z);
				//cout << ir << " back from goa first" << endl;
				if (Go9End(ir)) return;
				if (ir < 0) {
					//cout << " try reverse stack1 stack2" << endl;
					z.PermIJ();
					int ir = Go9a(z);
					//cout << ir << " back from goa first reverse" << endl;
					if (Go9End(ir)) return;
				}

				z.Perm();
				//cout << "try second  " << endl;
				//z.Dump();
				ir = Go9a(z);
				//cout << ir << " back from goa second" << endl;
				if (Go9End(ir)) return;
				if (ir < 0) {
					//cout << " try reverse stack1 stack2" << endl;
					z.PermIJ();
					ir = Go9a(z);
					//cout << ir << " back from goa second reverse" << endl;
					if (Go9End(ir)) return;
				}
			}
		}
	}
	void Go9DoSt12(SA & s) {
		InitNoMap();
		s.v123 = tcols[s.zi1]; s.v456 = tcols[s.zi3]; s.v789 = tcols[s.zi2];
		s.v124 = tcols[s.zj1]; s.v357 = tcols[s.zj3]; s.v689 = tcols[s.zj2];
		if (0) {
			cout << Char9out(s.v123) << " v 123 i1=" << s.zi1 << endl;
			cout << Char9out(s.v456) << " v 456 i3=" << s.zi3 << endl;
			cout << Char9out(s.v789) << " v 789 i2=" << s.zi2 << endl;
			cout << "----" << endl;
			cout << Char9out(s.v124) << " v 124 j1=" << s.zj1 << endl;
			cout << Char9out(s.v357) << " v 357 j3=" << s.zj3 << endl;
			cout << Char9out(s.v689) << " v 689 j2=" << s.zj2 << endl;
			cout << "======" << endl;
			cout << Char9out(s.v12) << " v12" << endl;
			cout << Char9out(s.v89) << " v89" << endl;
			cout << Char9out(s.v5) << " v5" << endl;
		}
		MapC1(0, tcols_cols[s.zi1]);
		MapC1(1, tcols_cols[s.zi3]);
		MapC1(2, tcols_cols[s.zi2]);
		MapC1(3, tcols_cols[s.zj1]);
		MapC1(4, tcols_cols[s.zj3]);
		MapC1(5, tcols_cols[s.zj2]);
		s.v3=s.v123&~s.v12; s.v4 = s.v124 & ~s.v12;
		s.v6 = s.v689 & ~s.v89; s.v7 = s.v789 & ~s.v89;
		s.v34 = s.v3 | s.v4;
	}
	int Go9a(STACKS12& z) {
		SA s; s.Init(z);
		Go9DoSt12(s); // find columns stacks 1 and 2
		Map_1_1_1(3, s.v4, s.v5, s.v6);
		if (nt2x3) {
			//cout << "look for 12x 125 126 128 id3=" << s.id3 << endl;
			Map_2_1(0, s.v12, s.v3);
			for (int i = 0, j = s.id3; i < 3; i++, j++) {// find v3
				int vy = tcols[j];
				if (vy & s.v3) {
					s.vs3_3 = vy;
					s.j7 = j;
					MapC1(7, tcols_cols[j]);
					break;
				}
			}
			for (int i = 0, j = s.id3; i < 3; i++, j++) {
				int vy = tcols[j];
				if (vy & s.v12) {// this must be 125 126 128
					s.v12x = vy;
					s.j6 = j;
					s.j8 = 3 * s.id3 + 3 - s.j6 - s.j7;
					MapC1(8, tcols_cols[s.j8]);
					s.vs3_m = tcols[s.j8];
					MapC1(6, tcols_cols[j]);
					int x = s.vs3_3 & ~s.v3;
					if (vy & s.v5) {// 348 367 368 378 
						//cout << " 125" << endl;
						if (x & s.v4 ) {// 348 679
							if (!(x & s.v89)) return -1;
							s.v8 = x & ~s.v4; s.v9 = s.v89 & ~s.v8;
							igang = 19;;
							Map_1_1_1(6, s.v7, s.v8, s.v9);
							return 1;
						}
						else if (x & s.v6) {//  367 368 g 20 21
							//cout << "367 368" << endl;
							if (x & s.v7) {
								igang = 20;
								Map_1_2(6, s.v7, s.v89);
								return 1;
							}
							else if (x & s.v89) {
								s.v8 = x & ~s.v6; s.v9 = s.v89 & ~s.v8;
								igang = 21;
								Map_1_1_1(6, s.v7, s.v8, s.v9);
								return 1;
							}
							else return -1;
						}
						else if (x & s.v7) {//378
							//cout << " 378" << endl;
							s.v8 = x & ~s.v7; s.v9 = s.v89 & ~s.v8;
							igang = 22;
							Map_1_1_1(6, s.v7, s.v8, s.v9);
							return 1;

						}
						else return -1;
					}
					else if (vy & s.v6) {//	358 378 389
						//cout << " 126" << endl;
						if (!(x & s.v89)) return -1;
						if (x & s.v5) {
							s.v8 = x & ~s.v5; s.v9 = s.v89 & ~s.v8;
							igang = 23;
							Map_1_1_1(6, s.v7, s.v8, s.v9);
							return 1;
						}
						else if (x & s.v7) {//378
							s.v8 = x & ~s.v7; s.v9 = s.v89 & ~s.v8;
							igang = 24;
							Map_2_1(0, s.v12, s.v3);
							Map_1_1_1(3, s.v4, s.v5, s.v6);
							Map_1_1_1(6, s.v7, s.v8, s.v9);
							return 1;
						}
						else if (x == s.v89) {
							igang = 25;
							Map_2_1(0, s.v12, s.v3);
							Map_1_1_1(3, s.v4, s.v5, s.v6);
							Map_1_2(6, s.v7, s.v89);
							return 1;
						}
						else return -1;
					}
					else if (vy & s.v89) {// 128 and 345 356 359
						if (!(x & s.v5)) return -1;
						s.v8 = vy & ~s.v12; s.v9 = s.v89 & ~s.v8;
						Map_1_1_1(6, s.v7, s.v8, s.v9);
						if (x &s.v4 ) { igang = 26; return 1; }
						if (x &s.v6 ) { igang = 27; return 1; }
						if (x &s.v9 ) { igang = 28; return 1; }
						return -1;
					}
					else return -1;
					break;
				}
			}
			return -1; // should never be here
		}
		else {// 134 135 136 137 138 158 
			for (int i = 0, j = s.id3; i < 3; i++, j++) {// find v3
				int vy = tcols[j];
				if (vy & s.v3) {
					int x = vy & ~s.v3;
					if (!(x & s.v12)) {// 158 267 349 ig 38
						//cout << "158 in stack 3" << endl;
						if (!(x & s.v4)) return -1;
						if (!(x & s.v89)) return -1;

						igang = 38;
						MapC1(8, tcols_cols[j]);
						s.v9 = x & s.v89; s.v8 = s.v89 & ~s.v9;
						int j1=s.id3, j2, v1,v2;
						for (int i = 0; i < 3; i++, j1++) {// find v5
							int vj1 = tcols[j1];
							if (vj1 & s.v5) {// expected 158
								if (!(vj1 & s.v8)) return -1;
								if (!(vj1 & s.v12)) return -1;
								v1 = vj1 & s.v12; v2 = s.v12 & ~v1;
								MapC1(6, tcols_cols[j1]);
								break;
							}
						}
						j2 = 3 * s.id3 + 3 - j - j1;
						MapC1(7, tcols_cols[j2]);
						Map_1_1_1(0,v1, v2, s.v3);
						Map_1_1_1(6, s.v7, s.v8, s.v9);
						return 1;
					}
					//cout << "13x in stack 3" << endl;
					// 134 135 136 137 138
					MapC1(6, tcols_cols[j]);
					s.j6 = j;
					int v1 = s.v12 & x,v2= s.v12&~v1;
					Map_1_1_1(0, v1, v2, s.v3);
					int j2= s.id3,vj2;// find 2..
					for (int i = 0; i < 3; i++, j2++) {// find v3
						vj2 = tcols[j2];
						if (vj2 & v2) {
							MapC1(7, tcols_cols[j2]);
							break;
						}
					}
					int j3 = 3 * s.id3 + 3 - s.j6 - j2,vj3= tcols[j3];
					//cout << Char9out(vj2) << " vj2 j2=" << j2 << endl;
					//cout << Char9out(vj3) << " vj3 j3=" << j3 << endl;
					MapC1(8, tcols_cols[j3]);
					int y = x & ~v1;
					if (y == s.v4) {//134 258 679 or  268 579  29 30
						//cout << "134 in stack 3" << endl;

						if (vj2 & s.v7) return -1;
						if(! (vj2 & s.v89) )return -1;
						if (!(vj3 & s.v89))return -1;
						s.v8 = vj2 & s.v89;	s.v9 = vj3 & s.v89;
						Map_1_1_1(6, s.v7, s.v8, s.v9);
						if (vj2 & s.v5)  igang = 29;
						else igang = 30;
						return 1;
					}
					else if (y == s.v5) {//135 268 479 or  278 469  31 32
						//cout << "135 in stack 3" << endl;
						if (!(vj3 & s.v4))return -1;
						if (!(vj2 & s.v89))return -1;
						if (!(vj3 & s.v89))return -1;
						s.v8 = vj2 & s.v89;	s.v9 = vj3 & s.v89;
						Map_1_1_1(6, s.v7, s.v8, s.v9);
						if (vj2 & s.v6)  igang = 31;
						else igang = 32;
						return 1;

					}
					else if (y == s.v6) {//136 258 479 or  278 459  33 34
						//cout << "136 in stack 3" << endl;
						if (!(vj3 & s.v4))return -1;
						if (!(vj2 & s.v89))return -1;
						if (!(vj3 & s.v89))return -1;
						s.v8 = vj2 & s.v89;	s.v9 = vj3 & s.v89;
						Map_1_1_1(6, s.v7, s.v8, s.v9);
						if (vj2 & s.v5)  igang = 33;
						else igang = 34;
						return 1;
					}
					else if (y == s.v7) {//137  268 459  35
						//cout << "137 in stack 3" << endl;
						if (!(vj2 & s.v6))return -1;
						if (!(vj2 & s.v89))return -1;
						s.v8 = vj2 & s.v89;	s.v9 = vj3 & s.v89;
						Map_1_1_1(6, s.v7, s.v8, s.v9);
						igang = 35;
						return 1;
					}
					else {// 138 259 467 or 269 457
						//cout << "138 in stack 3" << endl;
						if (!(vj3 & s.v4))return -1; 
						if (!(vj3 & s.v7))return -1;
						if (!(y & s.v89)) return -1;
						if (!(vj2 & s.v89)) return -1;
						s.v8 = y & s.v89;	s.v9 = vj2 & s.v89;
						Map_1_1_1(6, s.v7, s.v8, s.v9);
						if (vj2 & s.v5)  igang = 36;
						else igang = 37;
						return 1;
					}
				}
			}
		}
		return -1;// not implemented

	}

	//====================================  39_43 no 
	/*
	123456789 124378569 129356478  39 2   3 6
	123456789 124378569 135279468  40 8   0 6
	123456789 124378569 137245689  41 9   0 9
	123456789 124378569 157268349  42 6   0 3

	123456789 147258369 159267348  43 2   0 0
*/
	void Go9_no_2a() {// 39_43
		if (!nt2x2) { Go9_43(); return; }
		Go9SetPossibleStacks12B();
		//cout << "pattern b g9stxv = " << g9stxv << endl;
		InitNoMap();
		//SortTcols();
		//DumpSort();
		SB s;
		if ((!nt2x3)) {
			if (nt2x2 == 6) { Go40(); return; }
			else if (nt2x2 == 9) { Go41(); return ; }
		}
		if (g9stxv & 1)if (Go39_42(s, 0) > 0)return;
		if (g9stxv & 2) if(Go39_42(s, 1) > 0)return;
		if (g9stxv & 4) if (Go39_42(s, 2) > 0)return;

	}

/*
		// stack 3 minlex  nt2x3  nt2x2  gangster
		// 129356478		3		6		39
		// 135279468		0		6		40
		// 137245689		0		9		41
		// 157268349		0		3		42
*/
	int  Go39_42(SB & s,int ipe) {
		//cout << "expand for ip=" << ipe << endl;
		s.ip = ipe;
		InitNoMap();
		if (nt2x3) { if (!Go39(s)) return 0; }
		else { if (!Go42(s)) return 0; }
		if (!BuildCellMap()) return 0;
		return 1;
	}
	void Go39Pat12(SB& s) {// 129356478
		// any triplet should work as start
		s.p = tpermg9stk[s.ip];// order of the columns
		s.id1 = s.p[0]; s.id2 = s.p[3]; s.id3 = s.p[6];
		STACKS12& ss = go9stx[s.ip]; //stored results
		s.single = ss.v5;
		int v = tcols[s.id1];
		s.v3 = v & s.single; s.v12 = v & ~s.v3;
		// look for 378 in stack 2
		for (int i = 0, j = s.id2; i < 3; i++, j++) {
			int vy = tcols[j];
			if (!(vy & s.v3)) continue;
			s.v78 = vy & ~s.v3;
			MapC1(4, tcols_cols[j]);
			break;
		}
		MapC1(0, tcols_cols[s.id1]);
		// look for 789  456 in stack 1
		{
			int id1 = s.id1+1;
			int vx = tcols[id1], vy, cx, cy;
			//cout << Char9out(vx) << " vx id1=" << id1 << endl;

			if (vx & s.v78) {
				cx = tcols_cols[id1];
				id1++;
				vy = tcols[id1]; cy = tcols_cols[id1];
			}
			else {
				vy = vx; 	cy = tcols_cols[id1];
				id1++;
				vx = tcols[id1]; cx = tcols_cols[id1];
			}
			s.v9 = vx & s.single;
			s.v4 = vy & s.single; s.v56 = vy & ~s.v4;
			MapC1(2, cx); MapC1(1, cy);

		}
		// look for 124 569 in stack 2 to map columns
		for (int i = 0, j = s.id2; i < 3; i++, j++) {
			int vy = tcols[j];
			if (vy & s.v12)MapC1(3, tcols_cols[j]);
			else if (vy & s.v9)MapC1(5, tcols_cols[j]);
		}

	}
	int Go39(SB& s) {//	129 356 478
		igang = 39;
		Go39Pat12(s);// apply common pattern stacks 1/2
		for (int i = 0, j = s.id3; i < 3; i++, j++) {
			int vy = tcols[j];
			if (vy & s.v9)MapC1(6, tcols_cols[j]);
			else if (vy & s.v3)MapC1(7, tcols_cols[j]);
			else MapC1(8, tcols_cols[j]);
		}
		Map_2_1(0, s.v12, s.v3); Map_1_2(3, s.v4, s.v56); Map_2_1(6, s.v78, s.v9);
		return 1;
	}
	int Go40() {//135 279 468
		igang = 40;
		//DumpT2x2();
		// look for possible starts 2 pairs 3 digits
		for (int i = 0; i < nt2x2-1; i++) {
			int v1=t2x2[i],ix1= t2x2i[i];
			for (int j =i+1; j < nt2x2 ; j++) {
				int v2 = t2x2[j], ix2 = t2x2i[j];
				if ((v1 & v2) && (ix1 & ix2))
					if (Go40go(i, j)) return 1;
					else return 0;
			}
		}
		return 0;
	}
	int Go40go( int i1x, int i2x) {// try a start
		InitNoMap();
		int va = t2x2[i1x], vb = t2x2[i2x], v123 = va|vb,
			ita = t2x2i[i1x], itb = t2x2i[i2x], it0 = ita&itb,
			it1=ita&~it0,it2=  itb & ~it0;
		int item0,item1, item2;
		bitscanforward(item0, it0);
		bitscanforward(item1, it1);
		bitscanforward(item2, it2);
		MapC1(0, tcols_cols[item0]);	
		MapC1(3, tcols_cols[item1]);	
		MapC1(6, tcols_cols[item2]);
		int v124 = tcols[item1], v135 = tcols[item2], v12 = v123 & v124;
		int v3 = v123 & ~v12, v4 = v124 & ~v12, v13 = v123 & v135, v5 = v135 & ~v13;
		int v1 = v135 & v12, v2 = v12 & ~v1;
		int v456, v789, v378, v569, v279, v468;
		for (int i = 0, j = 3 * (item0 / 3); i < 3; i++, j++) {
			if (j == item0) continue;
			int vy = tcols[j];
			if (vy & v4) { v456 = vy;	MapC1(1, tcols_cols[j]); }
			else { v789= vy;	MapC1(2, tcols_cols[j]); }
		}
		for (int i = 0, j = 3 * (item1 / 3); i < 3; i++, j++) {
			if (j == item1) continue;
			int vy = tcols[j];
			if (vy & v3) { v378 = vy;	MapC1(4, tcols_cols[j]); }
			else { v569 = vy;	MapC1(5, tcols_cols[j]); }
		}
		for (int i = 0, j = 3 * (item2 / 3); i < 3; i++, j++) {
			if (j == item2) continue;
			int vy = tcols[j];
			if (vy & v2) { v279 = vy;	MapC1(7, tcols_cols[j]); }
			else { v468 = vy;	MapC1(8, tcols_cols[j]); }
		}
		Map_1_1_1(0, v1, v2, v3); Map_1_1_1(3, v4, v5, v569&v468);
		Map_1_1_1(6, v378&v279, v378&v468 ,v569&v279);
		if (!BuildCellMap()) return 0;
		//DumpMapping();
		//Check();
		return 1;
	}
	int Go41() {//137 245 689
		igang = 41;
		//DumpT2x2();
		// look for possible starts 2 pairs 3 digits
		//cout << " pairs status nt2x2=" << nt2x2 << endl;
		for (int i = 0; i < nt2x2 - 1; i++) {
			int v1 = t2x2[i], ix1 = t2x2i[i];
			for (int j = i + 1; j < nt2x2; j++) {
				int v2 = t2x2[j], ix2 = t2x2i[j];
				if ((v1 & v2) && (ix1 & ix2))
					if (Go41go(i, j)) return 1;
					else return 0;
			}
		}
		return 0;
	}
	int Go41go(int i1x, int i2x) {// try a start 137 245 689
		InitNoMap();
		int va = t2x2[i1x], vb = t2x2[i2x], v123 = va | vb,
			ita = t2x2i[i1x], itb = t2x2i[i2x], it0 = ita & itb,
			it1 = ita & ~it0, it2 = itb & ~it0;
		int item0, item1, item2;
		bitscanforward(item0, it0);
		bitscanforward(item1, it1);
		bitscanforward(item2, it2);
		MapC1(0, tcols_cols[item0]);
		MapC1(3, tcols_cols[item1]);
		MapC1(6, tcols_cols[item2]);
		int v124 = tcols[item1], v137 = tcols[item2], v12 = v123 & v124;
		int v3 = v123 & ~v12, v4 = v124 & ~v12, v13 = v123 & v137, v7 = v137 & ~v13;
		int v1 = v137 & v12, v2 = v12 & ~v1;
		int v456, v789, v378, v569, v245, v689;
		for (int i = 0, j = 3 * (item0 / 3); i < 3; i++, j++) {
			if (j == item0) continue;
			int vy = tcols[j];
			if (vy & v4) { v456 = vy;	MapC1(1, tcols_cols[j]); }
			else { v789 = vy;	MapC1(2, tcols_cols[j]); }
		}
		for (int i = 0, j = 3 * (item1 / 3); i < 3; i++, j++) {
			if (j == item1) continue;
			int vy = tcols[j];
			if (vy & v3) { v378 = vy;	MapC1(4, tcols_cols[j]); }
			else { v569 = vy;	MapC1(5, tcols_cols[j]); }
		}
		for (int i = 0, j = 3 * (item2 / 3); i < 3; i++, j++) {
			if (j == item2) continue;
			int vy = tcols[j];
			if (vy & v2) { v245= vy;	MapC1(7, tcols_cols[j]); }
			else { v689 = vy;	MapC1(8, tcols_cols[j]); }
		}
		int v69 = v569 & v689;
		Map_1_1_1(0, v1, v2, v3); Map_1_1_1(3, v4, v569&v245, v69 & v456);
		Map_1_1_1(6, v7, v378 & v689, v69 & v789);
		if (!BuildCellMap()) return 0;
		//DumpMapping();
		//Check();
		return 1;
	}

	void Go42Pat12(SB& s) {//157 268 349
		s.p = tpermg9stk[s.ip];// order of the columns
		s.id1 = s.p[0]; s.id2 = s.p[3]; s.id3 = s.p[6];
		STACKS12& ss = go9stx[s.ip]; //stored results
		s.single = ss.v5;
		int v = tcols[s.id1];
		s.v3 = v & s.single; s.v12 = v & ~s.v3;

		// look for 378 in stack 2
		for (int i = 0, j = s.id2; i < 3; i++, j++) {
			int vy = tcols[j];
			if (!(vy & s.v3)) continue;
			s.v78 = vy & ~s.v3;
			MapC1(4, tcols_cols[j]);
			break;
		}
		MapC1(0, tcols_cols[s.id1]);
		// look for 789  456 in stack 1
		{
			int id1 = s.id1+1;
			int vx = tcols[id1], vy, cx, cy;
			//cout << Char9out(vx) << " vx id1=" << id1 << endl;

			if (vx & s.v78) {
				cx = tcols_cols[id1];
				id1++;
				vy = tcols[id1]; cy = tcols_cols[id1];
			}
			else {
				vy = vx; 	cy = tcols_cols[id1];
				id1++;
				vx = tcols[id1]; cx = tcols_cols[id1];
			}
			s.v9 = vx & s.single;
			s.v4 = vy & s.single; s.v56 = vy & ~s.v4;
			MapC1(2, cx); MapC1(1, cy);

		}
		// look for 124 569 in stack 2 to map columns
		for (int i = 0, j = s.id2; i < 3; i++, j++) {
			int vy = tcols[j];
			if (vy & s.v12)MapC1(3, tcols_cols[j]);
			else if (vy & s.v9)MapC1(5, tcols_cols[j]);
		}

	}
	int Go42(SB& s) {//157 268 349
		igang = 42;
		Go42Pat12(s);// apply common pattern stacks 1/2
		int n = 0;
		for (int i = 0, j = s.id3; i < 3; i++, j++) {
			int vy = tcols[j];
			if (vy & s.single) {// 349
				MapC1(8, tcols_cols[j]);
			}
			else if (n) {//268
				MapC1(7, tcols_cols[j]);
				s.v2 = vy & s.v12; s.v6 = vy & s.v56; s.v8 = vy & s.v78;
			}
			else {//157
				n++;
				MapC1(6, tcols_cols[j]);
				s.v1 = vy & s.v12; s.v5 = vy & s.v56;  s.v7 = vy & s.v78;
			}
		}
		Map_1_1_1(0, s.v1, s.v2, s.v3);
		Map_1_1_1(3, s.v4, s.v5, s.v6);
		Map_1_1_1(6, s.v7, s.v8, s.v9);
		return 1;
	}
	void Go9_43() {//123 456 789 147 258 369 159 267 348	
		InitNoMap();
		igang = 43;
		int v123 = tcols[0], vx = 0x1ff & ~v123, v1, v2, v3;
		{// start using first
			int v1n, v3n;
			bitscanforward(v1n, v123); v1 = 1 << v1n;
			bitscanreverse(v3n, v123); v3 = 1 << v3n;
			v2 = v123 & ~(v1 | v3);
			Map_1_1_1(0, v1, v2, v3);
			MapC1(0, tcols_cols[0]);
			MapC1(1, tcols_cols[1]);
			MapC1(2, tcols_cols[2]);
		}
		int v14759 = 0, v25867 = 0, v36948 = 0;
		for (int i = 3; i < 9; i++) {
			int v = tcols[i];
			if (v & v1)v14759 |= v;
			else if (v & v2)v25867 |= v;
			else v36948 |= v;
		}
		int v68 = vx & ~v14759, v49 = vx & ~v25867,
			v57 = vx & ~v36948;
		int v4, v5, v6, v7, v8, v9;
		{ // find v4 v5 v6 v7 v8 v9
			register int V = tcols[1];
			v4 = V & v49; v5 = V & v57; v6 = V & v68;
			V = tcols[2];
			v9= V & v49; v7 = V & v57;  v8 = V & v68;
			Map_1_1_1(3, v4, v5, v6);
			Map_1_1_1(6, v7, v8, v9);
		}
		int v147 = v1 | v4 | v7, v258 = v2 | v5 | v8, v369 = v3 | v6 | v9;
		int v159 = v1 | v5 | v9, v267 = v2 | v6 | v7, v348 = v3 | v4 | v8;
		if (debug) {
			cout << Char9out(v147) << " v147" << endl;
			cout << Char9out(v258) << " v258" << endl;
			cout << Char9out(v369) << " v369" << endl;
			cout << Char9out(v159) << " v159" << endl;
			cout << Char9out(v267) << " v267" << endl;
			cout << Char9out(v348) << " v348" << endl;
		}

		for (int i =3; i < 9; i++) {
			int v = tcols[i],c= tcols_cols[i];
			if (v == v147) MapC1(3,c);
			else if (v == v258) MapC1(4, c);
			else if (v == v369) MapC1(5, c);
			else if (v == v159) MapC1(6, c);
			else if (v == v267) MapC1(7, c);
			else  MapC1(8, c);
		}
		BuildCellMap();
	}
}gangminlex;
#include "gcat_Minlex_cpp.h"    

void Go_c17_91() {// test band3 using gangster
	cout << "process 91 band3 using template " << endl;
	for (int ig = 0; ig < 44; ig++) {// 44 gangsters
		const char* myg = t44g[ig];
		for (int i = 0; i < 27; i++) {
			cout << myg[i]; if (i == 8 || i == 17) cout << "  ";
		}
		cout << "igang expected=" << ig << endl;
		for(int i=0;i<10000;i++)
		gangminlex.Initt(myg);
	}

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
	int ntot = 0;
	B3PAT b3pats[9][2];
	B3PATCUM b3c1[2], b3c2[4], b3c3[8], b3c4[16], b3c5[32], b3c6[32],
		b3c7[32], b3c8[32], b3c9[32];
	for (int ig = 0; ig < 44; ig++) {// 44 gangsters
		//if (ig != 4)continue;
		memset(gb3, 0, sizeof gb3);
		const char* myg = t44g[ig];
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
				perm2[jp2] = gb3d[1][tpermgang[ip2][jp2]];
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
					perm3[jp3] = gb3d[2][tpermgang[ip3][jp3]];
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
							ntot++;
							B3PATCUM& myb3c = b3c9[nb3c9++];
							myb3c.Cum(b3c8[j], b3pats[d9][i], 20, d9);
							myb3c.SetIndex();
							//fout1 << '"';
							//for (int i = 0; i < 27; i++)
								//fout1 << myb3c.b0[i] + 1;
							//fout1 << '"' << ",";
							//fout1 << myb3c.index << ',' ;
							//if (!(ntot & 15)) fout1<<"//"<<ntot-1 << endl;

							//fout1 << ";" << ig << ";" << nvalid << "," << myb3c.index << endl;
							//fout1 << ";" << ig << ";" << nvalid << "," << myb3c.index << endl;
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
		fout1 << ntot << ',';
	}
	fout1 << endl;
	cout << " end max 4 5 6 =" << max4 << " " << max5 << " " << max6 << endl
		<< " max  7 8 9=" << max7 << " " << max8 << " " << max9	<< endl;

}

void Go_c17_93aaaa() {// analysis the 416 bands
	int* a = genb12.grid0, * b = genb12.colband1;
	for (uint32_t ib = 0; ib <= 415; ib++) {
		if (ib < 30 ) continue;
		//if (ib < 346) continue;
		//if (ib  >400) continue;

		//if (ib >20) continue;
		genb12.InitBand1(ib);
		//int vr=bmlw.GetforMinlex(a, ib);
		int vr = bmlw.GetforMinlex(a, 30);
		if (bmlw.maxindex == bmlw.minindex) continue;
		if (bmlw.goback)continue;
		for (int i = 0; i < 27; i++) cout << a[i] + 1;
		cout << " band index" << ib <<" vr = "<< vr << endl;;
		//bmlw.GetMinIfNotBelow(a, ib);
	}
	cout << p_cpt2g[10] << " hits on valid bands"<<endl;
}

void Go_c17_93() {// analysis of the 30 first bands
	int* a = genb12.grid0, * b = genb12.colband1;

	int g[27];
	for (uint32_t i = 0; i <= 415; i++) {
		genb12.InitBand1(i);
		BANDMINLEX::PERM  p = automorphsp[100];
		for (int ir = 0; ir < 3; ir++) {
			int ior = p.rows[ir] * 9, idr = 9 * ir;
			for (int ic = 0; ic < 9; ic++) {
				int ocell = ior + p.cols[ic], dcell = idr + ic;
				g[dcell] = p.map[a[ocell]];
			}
		}
		for(int j=0;j<100000;j++)
			bmlw.GetforMinlex(a, 0);
		//bmlw.GetMinIfNotBelow(a, i);

	}
	cout << p_cpt2g[10] << " hits on valid bands" 
		<< " [20] " << p_cpt2g[20] << " [21] " << p_cpt2g[21]
		<< " [22] " << p_cpt2g[22] << " [23] " << p_cpt2g[23]
		<< " [30] " << p_cpt2g[30] << endl;

	return;
	


	//for (uint32_t i = 0; i <= 30; i++) {

	for (uint32_t ib = 0; ib <= 415; ib++) {
		genb12.InitBand1(ib);
		int n = 1, cx[9], ncx[9];
		memset(ncx, 0, sizeof ncx);
		cx[0] = b[0], ncx[0] = 1;
		for (int i = 1; i < 9; i++) {
			int v = b[i];
			for (int j = 0; j < n; j++) {
				if (v == cx[j]) {
					ncx[j]++; v = 0; break;
				}
			}
			if (v) { ncx[n] = 1; cx[n++] = v; }
		}
		int nx3 = 0, nx2 = 0;
		for (int i = 0; i < n; i++) {
			int x = ncx[i];
			if (x == 3)nx3++;
			if (x == 2)nx2++;

		}

		if (n == 9 && ib<=30) {
			/*
				for (int i = 0, x = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++, x++)cout << a[x] + 1;
					cout << " ";
				}
				cout << "_ ";
			}
			cout << "  " << ib << " " << ++p_cpt2g[10] << endl;
			*/
			register uint32_t v = 111111111 +
				100000000 * a[12] + 10000000 * a[15] + 1000000 * a[16];
			v += 100000 * a[18] + 10000 * a[19];
			v += 1000 * a[21] + 100 * a[22];
			v += 10 * a[24] + a[25];
			cout << v << ",";
			fout1 << ib << ",";
			if (++p_cpt2g[10] == 10) {
				cout << "//" << p_cpt2g[11] << endl;
				fout1 << "//" << p_cpt2g[11] << endl;
				p_cpt2g[10] = 0;
			}
			p_cpt2g[11]++;
			continue;
		}
		else 	continue;
		for (int i = 0, x = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for(int k=0;k<3;k++,x++)cout << a[x] + 1;
				cout << " ";
			}
			cout << "_ ";
		 }

		//for (int i = 0; i < 27; i++) cout << a[i] + 1;
		cout << "  " << ib //<< "\tnauto=" <<(int) tblnauto[ib] 
			<< "    \t" << n << " " <<nx3<<" " <<nx2<< endl;
		if (1)for (int i = 0; i < n; i++) {
			if (ncx[i] > 1) {
				int x = cx[i];
				cout << Char9out(x) << " ncx= " << ncx[i] << "\t";
				for (int j = 0; j < 9; j++) if (x == b[j])
					cout << j << " ";
				cout << endl;

			}
		}
	}


}