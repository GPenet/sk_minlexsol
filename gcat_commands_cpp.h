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
	"7 band2 ok   ",	"8  ",
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
			if (op.ton>1) {
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
#include "gcat_gangminlex_cpp.h"    
#include "gcat_Minlex_cpp.h"    

void Go_c17_91() {// test band3 using gangster
	cout << "process 91 band3 using template " << endl;
	const char* tw = "569137248259346178248679135";
	cout << tw << " bug?? to see" << endl;
	gangminlex.Initd(tw,1);
	gangminlex.Status();
	gangminlex.DumpMappingN();
	int ig = gangminlex.igang;
	int istart = tfill_index[ig], iend = tfill_index[ig + 1];
	cout << "ig found" << ig
		<< " start end " << istart << " " << iend << " ";// << endl;
	for (int i = istart; i < iend; i++) {
		int bd = tfillband[i];
		const char* cx = t44fills[i];
		cout << cx << endl;
		int b3morphed[27];
		for (int i = 0; i < 9; i++) {
			int c = gangminlex.revcmap[i];
			int* m = gangminlex.revdmap;
			int v = cx[c] - '1';
			b3morphed[i] = m[cx[c] - '1'];
			b3morphed[i+9] = m[cx[c+9] - '1'];
			b3morphed[i + 18] = m[cx[c + 18] - '1'];
		}
		BandReOrder(b3morphed);
		for (int i = 0; i < 27; i++) cout << b3morphed[i] + 1;
		cout << "  fill to check band " <<bd << endl;

	}
	/*

	if (op.ton > 1) cout << " seen valid fills " << nokindex << endl;
	if (!nokindex)return;

	if (nokindex > 1)SortBandsMorphed(nokindex);
	else tfillorder[0] = 0;
	for (int i = 0; i < nokindex; i++) {
		p_cpt2g[7]++;
		int* myb = tfillbandmorphed[tfillorder[i]];
		if (op.ton > 1) {
			for (int i = 0; i < 27; i++) cout<< myb[i]+1;
			cout << "  fill to check " << p_cpt2g[7] << endl;
		}*/

	return;
	for (int ig = 0; ig < 44; ig++) {// 44 gangsters
		//if (ig < 19) continue;
		//if (ig !=40) continue;
		//if (ig >15) continue;
		const char* myg = t44g[ig];
		for (int i = 0; i < 27; i++) {
			cout << myg[i]; if (i == 8 || i == 17) cout << "  ";
		}
		cout << "igang=" << ig << endl;
		//for(int i=0;i<10000;i++)
		gangminlex.Initt(myg,0);
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
	cout << "extract row4>5100" << endl;
	for (uint32_t i = 0; i <= 300; i++) {
		genb12.InitBand1(i);
		int x1 = b1r4[i], x2 = b1r4[i + 1];
		for (int ix = x1; ix < x2; ix++) {
			int ns = tr4nsol[ix];
			if (ns < 55000) continue;
			uint32_t jr4index = tr4u[ix];
			genb12.InitRow4FromI10375(jr4index);
			for (int k = 0; k < 36; k++) fout1 << genb12.grid0[k] + 1;
			fout1 << ";" << ns << endl;


		}
	}
	return;

	/*
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
	*/

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