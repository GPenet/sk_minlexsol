  
int tpermgang[6][3] = { {0,1,2},{0,2,1},
	{1,0,2},{1,2,0},{2,0,1},{2,1,0} };
int tpermg9stk[6][9] = {
	{0,1,2,3,4,5,6,7,8},{0,1,2,6,7,8,3,4,5},{3,4,5,0,1,2,6,7,8 } ,
	{3,4,5,6,7,8,0,1,2}, {6,7,8,0,1,2,3,4,5},{6,7,8,3,4,5,0,1,2} };

struct GANGMINLEX {// receive a band send back i44 and morphing data
	struct PAIR_TRIPLET {
		int v, ip, c1, c2;
		inline void Enter(int ve, int ipe, int c1e, int c2e) {
			v = ve; ip = ipe; c1 = c1e; c2 = c2e;
		}
		inline void ChangeStack() {
			register int cx = c1; c1 = c2; c2 = cx;
		}
		void Dump() {
			cout << Char9out(v) << " ip=" << ip << " c1=" << c1 << " c2=" << c2 << endl;
		}
	}spairs[40],striplets[9],
		got,go3t[3],gota,gotb,gotc,gop[3],gopa,gopb,gopc;
	int debug;
	int gb3[9], gb3d[9][3], gdcols[9][3],g0[27],goback; 
	int tcols[9], tcols_cols[9], tcols_count[9], tcols_stk[9], ntcols,ngop ;

	int tcolss[9],  vxc[6], vxcc[6], ntcs3;
	int* tcols_dstack[3];
	GANGMINLEX() {
		tcols_dstack[0] = gb3;
		tcols_dstack[1] = &gb3[3];
		tcols_dstack[2] = &gb3[6];

	}
	int npst[3], ntst[3], isp2;

	int t2x3[3], t2x3i[3], nt2x3, t2x2[20], t2x2i[20], nt2x2;
	int dmap[9], cmap[9];
	int cellmap[27], digitmap[9],igang,colmap[9],stackmap[3],stackmapb[3];
	int c1n, c2n, c3n, c4n, c5n, c6n, c7n, c8n, c9n;
	int m1, m2, m3, m4, m5, m6, m7, m8, m9;
	int m123, m456, m789, m457, m689, m12x,m12;
	int m45, m89, m67;

	void MappingInit() {
		for (int i = 0; i < 27; i++) cellmap[i] = i;
		for (int i = 0; i < 9; i++) digitmap[i] = i;
	}
	void SortTcols() {
		int n = 0;
		for (int i = 0; i < ntcols; i++)
			if (tcols_count[i] == 3)tcolss[n++] = i;
		ntcs3 = n;
		for (int i = 0; i < ntcols ; i++)
			if (tcols_count[i] == 2)tcolss[n++] = i;
		for (int i = 0; i < ntcols ; i++)
			if (tcols_count[i] == 1)tcolss[n++] = i;

	}
	inline void SetColbfNtcols();
	int NpairsStack(int ip, int s1, int s2, int n0);
	int NtripletsStack(int ip, int s1, int s2, int n0);
	void SetPairscols();
	void Settripletscols();
	void Init(int* o, int debugging = 0);
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
	void Initt(const char* o, int debugging = 0) {// for test scrambled entry
		int d[27]; 
		p_cpt2g[19] = 0;
		for (int i0 = 0; i0 < 6; i0++) {
			int* p = tpermgang[i0];
			for (int ip2 = 0; ip2 < 6; ip2++) {
				int* p2 = tpermgang[ip2];
				for (int i1 = 0, j = 0; i1 < 3; i1++) {
				int ip = p[i1], idip = 9 * ip;
					for (int i2 = 0; i2 < 3; i2++) {
						int idcol = idip + 3 * p2[i2];
						for (int i3 = 0; i3 < 3; i3++, j++) {
							d[j] = o[idcol + i3] - '1';
						}
					}
				}
				Init(d, debugging);
			}
		}
		cout << p_cpt2g[19] << " hit " <<igang<< endl;
	}
	void Initd(const char* o, int debugging = 0) {// for test 
		int d[27];
		for (int i = 0; i < 27; i++) {
				d[i] = o[i] - '1';
		}

		Init(d, debugging);
	}

	int ValidGangMinlex(int i);
	int CheckMap();
	void Status();
	
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
	void DumpMappingN() {
		for (int i = 0; i < 27; i++) cout << g0[i] + 1;
		cout << " gangster  studied igang=" << igang << endl;
		for (int i = 0; i < 27; i++) cout << cellmap[i] << " ";
		cout << " cells mapping" << endl;
		for (int i = 0; i < 9; i++) cout << cmap[i] << " ";
		cout << " columns mapping" << endl;
		for (int i = 0; i < 9; i++) cout << dmap[i] << " ";
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

	void Go3();
	void Go5();
	int Go5b();
	void Go6();
	int Go6b();
	void Go78();
	int Go78b();

	//================ all columns different patterns
	// 123 456 789 and 124 357 689 or 124 378 569

	void Go9();
	void Go9_19_38();
	int Go9_19_38B();
	int Go9_39_42();
	void Go9_43();

}gangminlex;
inline void GANGMINLEX::SetColbfNtcols() {
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
				tcols_count[ntcols] = 1;
				tcols_cols[ntcols] = 1 << icol;
				tcols_stk[ntcols] = 1 << istk;
				tcols[ntcols++] = v;
			}
		}

}
int GANGMINLEX::NpairsStack(int ip, int s1, int s2, int n0) {
	int n = 0, * d1 = tcols_dstack[s1], * d2 = tcols_dstack[s2];
	for (int i = 0; i < 3; i++) {
		int v1 = d1[i];
		for (int j = 0; j < 3; j++) {
			int v1v2 = v1 & d2[j];
			if (_popcnt32(v1v2) == 2)
				spairs[n0 + n++].Enter(v1v2, ip, 3 * s1 + i, 3 * s2 + j);
		}
	}
	return n;
}
int GANGMINLEX::NtripletsStack(int ip, int s1, int s2, int n0) {
	int n = 0, * d1 = tcols_dstack[s1], * d2 = tcols_dstack[s2];
	for (int i = 0; i < 3; i++) {
		int v1 = d1[i];
		for (int j = 0; j < 3; j++) {
			int v1v2 = v1 & d2[j];
			if (_popcnt32(v1v2) == 3) {
				int nx = n0 + n ;
				//cout << "found triplet nx=" << nx << endl;
				striplets[n0 + n++].Enter(v1v2, ip, 3 * s1 + i, 3 * s2 + j);
				//striplets[nx].Dump();
				//striplets[n0 + n++].Enter(v1v2, ip, 3 * s1 + i, 3 * s2 + j);

			}
		}
	}

	return n;
}
void GANGMINLEX::SetPairscols() {
	isp2 = 0;
	if ((npst[0] = NpairsStack(0, 0, 1, 0)) == 2) isp2 = 1;
	if ((npst[1] = NpairsStack(1, 0, 2, npst[0])) == 2) isp2 = 1;
	if ((npst[2] = NpairsStack(2, 1, 2, npst[0] + npst[1])) == 2) isp2 = 1;
	nt2x2 = npst[0] + npst[1] + npst[2];
	if (debug)
		cout << " nc=" << ntcols << " P9cols= " << npst[0] << " "
		<< npst[1] << " " << npst[2] << "\t" << nt2x2 << " isp2 " << isp2 << endl;
}
void GANGMINLEX::Settripletscols() {
	ntst[0] = NtripletsStack(0, 0, 1, 0);
	ntst[1] = NtripletsStack(1, 0, 2, ntst[0]);
	ntst[2] = NtripletsStack(2, 1, 2, ntst[0] + ntst[1]);
	nt2x3 = ntst[0] + ntst[1] + ntst[2];
	if (debug)
		cout << " trip= " << ntst[0] << " " << ntst[1] << " " << ntst[2] << endl;
}


void GANGMINLEX::Init(int* o, int debugging ) {
	debug = debugging;
	goback = 0;
	memcpy(g0, o, sizeof g0);
	SetColbfNtcols();
	if (ntcols > 5) SetPairscols();
	else
		if (debug) 		cout << " init ntcols=" << ntcols << endl;
	if (ntcols < 9) {
		SortTcols();
		Settripletscols();
		if (debug)DumpSort();
	}
	switch (ntcols) {
	case 3: Go3(); return;
	case 5: Go5(); return;
	case 6: Go6(); return;
	case 7:
	case 8:Go78(); return;
	case 9: Go9(); return;
	}
}
int GANGMINLEX::ValidGangMinlex(int i) {
	igang = i;
	goback = 1;
	// build cmap dmap cellmap
	{
		register int r;
		bitscanforward(r, m1); dmap[r] = 0; bitscanforward(r, m2); dmap[r] = 1;
		bitscanforward(r, m3); dmap[r] = 2; bitscanforward(r, m4); dmap[r] = 3;
		bitscanforward(r, m5); dmap[r] = 4; bitscanforward(r, m6); dmap[r] = 5;
		bitscanforward(r, m7); dmap[r] = 6; bitscanforward(r, m8); dmap[r] = 7;
		bitscanforward(r, m9); dmap[r] = 8;
	}
	{
		cmap[0] = c1n; cmap[1] = c2n; cmap[2] = c3n;
		cmap[3] = c4n; cmap[4] = c5n; cmap[5] = c6n;
		cmap[6] = c7n; cmap[7] = c8n; cmap[8] = c9n;
	}
	{// just colmap to cellmap same rows
		if (!CheckMap()) { Status(); return 2; }
		for (int irow = 0, i = 0; irow < 3; irow++) {
			register int drow = 9 * irow;
			for (int icol = 0; icol < 9; icol++, i++)
				cellmap[i] = drow + cmap[icol];
		}
	}
	if (igang < 0) { Status();	DumpMappingN();	}
	else  p_cpt2g[19]++;// cout << "seen gang" << igang << endl;
	return goback;
}
int GANGMINLEX::CheckMap() {
	int a = 0, b = 0;
	for (int i = 0; i < 9; i++) {
		if (cmap[i] < 0 || dmap[i] < 0) break;
		if (cmap[i] > 8 || dmap[i] > 8) break;
		a |= 1 << cmap[i]; b |= 1 << dmap[i];
	}
	if (a == 0x1ff && b == 0x1ff) return 1;
	cout << "invalid or missing in mapping igan=" << igang << endl;
	for (int i = 0; i < 9; i++) cout << cmap[i] << " ";
	cout << " columns mapping" << endl;
	for (int i = 0; i < 9; i++) cout << dmap[i] << " ";
	cout << " digits mapping" << endl;
	igang = -1;
	return 0;

}

void GANGMINLEX::Status() {

	cout << Char9out(m123) << " m123 " << endl;
	cout << Char9out(m456) << " m456 " << endl;
	cout << Char9out(m457) << " m457 " << endl;
	cout << Char9out(m789) << " m789 " << endl;

	cout << Char9out(m1) << " m1 " << endl;
	cout << Char9out(m2) << " m2 " << endl;
	cout << Char9out(m3) << " m3 " << endl;
	cout << Char9out(m4) << " m4 " << endl;
	cout << Char9out(m5) << " m5 " << endl;
	cout << Char9out(m6) << " m6 " << endl;
	cout << Char9out(m7) << " m7 " << endl;
	cout << Char9out(m8) << " m8 " << endl;
	cout << Char9out(m9) << " m9 " << endl;


	cout << c1n <<" " << c2n<<" " << c3n << " "
		<< c4n << " " << c5n << " " << c6n << " " 
		<< c7n << " " << c8n << " " << c9n << " cnn " << endl;

}

#define LOCATEUSING(A,B,C) 	{ register int r = C, * p = &gb3[st3d];\
if (r & *p) { A = *p; B = st3d; }else if (r & *++p) {A = *p; B = st3d + 1; }\
else { A = *++p; B = st3d + 2; }}

#define SPLIT3(X,A,B,C) int a, b;	bitscanforward(a, X);\
	bitscanreverse(b, X);A = 1 << a; C = 1 << b;B=X&~(A|C);

#define SPLIT3N(X,A,B,C) bitscanforward(A, X);	bitscanreverse(C, X);\
X^= 1 << A;bitscanforward(B, X);

#define SPLIT2(C,A,B) int a, b;	bitscanforward(a, C);\
	bitscanreverse(b, C);A = 1 << a; B = 1 << b;

#define END89(I) SPLIT2(m89, m8, m9) ValidGangMinlex(I);return 0
#define END8_9(I) m8 = mc8 & m89; m9 = mc9 & m89; ValidGangMinlex(I);return 0

#define END89F(I) SPLIT2(m89, m8, m9) return ValidGangMinlex(I)
#define END8_9F(I) m8 = mc8 & m89; m9 = mc9 & m89;return ValidGangMinlex(I) 

void GANGMINLEX::Go3() {
	{SPLIT3(tcols[0], m1,m2,m3) }
	{SPLIT3(tcols[1], m4, m5, m6) }
	{SPLIT3(tcols[2], m7, m8, m9) }
	{SPLIT3N(tcols_cols[0], c1n, c4n,c7n) }	
	{SPLIT3N(tcols_cols[1], c2n, c5n, c8n) }
	{SPLIT3N(tcols_cols[2], c3n, c6n, c9n) }
	ValidGangMinlex(0);	
}
void GANGMINLEX::Go5() {
	SortTcols();
	//DumpSort();
	for (int i = 0; i < 5; i++)  {
		register int ii = tcolss[i];
		vxc[i] = tcols[ii];
		vxcc[i] = tcols_cols[ii];
	}
	int ip = 0;
	for ( ; ip < 3; ip++)if (ntst[ip]==3) {
		//cout << "try stacks 12 for ip " << ip << endl;
		{
			int n = 0;
			for (int j = 0; j < nt2x3; j++)  {
				//striplets[j].Dump();
				if(striplets[j].ip==ip)		go3t[n++] = striplets[j];
			}
		}
		//match triplets to sorted values 
		for (int i = 0; i < 3; i++) {
			got = go3t[i];
			register int v = got.v;
			if (v == vxc[0]) gota = got;
			else if (v == vxc[1]) gotb = got;
			else gotc = got;
		}
		//gota.Dump(); gotb.Dump(); gotc.Dump();
		c1n = gota.c1; c4n = gota.c2; m123 = gota.v;
		c2n = gotb.c1; c5n = gotb.c2; m456 = gotb.v;
		c3n = gotc.c1; c6n = gotc.c2; m789 = gotc.v;
		int c3 = vxcc[0] & ~((1 << c1n) | (1 << c4n));
		bitscanforward(c7n, c3);
		// match stack 3 not triplet to stack 2
		{
			register int v1 = vxc[3], c1 = vxcc[3],
				v2 = vxc[4], c2 = vxcc[4], x = v1 & m456;
			if (_popcnt32(x) == 2) {
				m457 = v1; m689 = v2;
				bitscanforward(c8n, c1);
				bitscanforward(c9n, c2);
			}
			else {
				m457 = v2; m689 = v1;
				bitscanforward(c8n, c2);
				bitscanforward(c9n, c1);
			}
		}
	}
	{SPLIT3(m123, m1, m2, m3) }
	m6 = m456 & m689; m45 = m456 & ~m6;
	m7 = m789 & m457; m89 = m789 & ~m7;
	{SPLIT2(m45, m4, m5)}
	{SPLIT2(m89, m8, m9)}
	ValidGangMinlex(1);
	return;
}


void GANGMINLEX::Go6() {
	SortTcols();
	//DumpSort();
	for (int i = 0; i < 6; i++) {
		register int ii = tcolss[i];
		vxc[i] = tcols[ii];
		vxcc[i]= tcols_cols[ii];
	}
	// catch pairs
	{
		ngop = 0;
		for (int j = 0; j < nt2x2 / 2; j++) {
			gop[ngop++] = spairs[j];
		}
		//for (int i = 0; i < ngop; i++)	gop[i].Dump();

	}
	// call process for any triplet perm
	for (int i = 0; i < 6; i++) {
		int* p = tpermgang[i];
		gota = striplets[p[0]]; gotb = striplets[p[1]]; gotc = striplets[p[2]];
		if (Go6b())return;
	}
	return;
}

int GANGMINLEX::Go6b() {
	int  vc8, vc9;
	// align pairs on triplets
	if (nt2x2) {
		gopa.v = gopb.v = gopc.v = 0;
		for (int i = 0; i < ngop; i++) {
			register int x = gop[i].v;
			if (x & gota.v)gopa = gop[i];
			else if(x& gotb.v)gopb = gop[i];
			else gopc = gop[i];
		}
		if ((!gopa.v) || (!gopc.v)) return 0;
	}
	c1n = gota.c1; c4n = gota.c2; m123 = gota.v;
	c2n = gotb.c1; c5n = gotb.c2; m456 = gotb.v;
	c3n = gotc.c1; c6n = gotc.c2; m789 = gotc.v;
	if (!nt2x2) goto gog4;
	else {
		// pairs 12  shared must be 124
		{
			register int y = gopa.v; // y is "12"
			for (int i = 3; i < 6; i++) {
				register int x = vxc[i], xc = vxcc[i];
				if (x & y) {// this is 124
					bitscanforward(c7n, xc);
					m4 = x & m456; m12 = y ;
					if (!m4)  return 0;		
					m3 = m123 & (~m12);
					{  SPLIT2(m12, m1, m2)}
					break;
				}
			}
		}
		{
			for (int i = 3; i < 6; i++) {
				register int x = vxc[i], xc = vxcc[i];
				if (!(x & m123)) {// this is  689 or 569
					bitscanforward(c9n, xc);
					vc9 = x;
				}
				else if(x & m3) {// this is 357 or 378
					bitscanforward(c8n, xc);
					vc8 = x;
				}
			}
		}
		//cout << endl;
		//gopa.Dump(); if (gopb.v)	gopb.Dump(); gopc.Dump();
		//gota.Dump(); gotb.Dump(); gotc.Dump();
		if (nt2x2 == 4) {//  124 357 689igang=2 
			m5 = vc8 & m456; m6 = vc9 & m456; m7 = vc8 & m789;
			{  SPLIT2(vc9 & m789, m8, m9)}
			return	ValidGangMinlex(2);

		}
		else {//  124 378 569igang=3 
			{  SPLIT2(m456 & (~m4), m5, m6)}
			m9 = vc9 & m789;
			{  SPLIT2(m789 & (~m9), m7, m8)}
			return 	ValidGangMinlex(3);
		}

	}

gog4: {	//  147 258 369igang=4 
	{SPLIT3(m123, m1, m2, m3) }// assign 123
	for (int i = 3; i < 6; i++) {
		register int x = vxc[i], xc = vxcc[i];
		if (x & m1) {// this is 147
			bitscanforward(c7n, xc);
			m4 = x & m456; m7 = x & m789;
		}
		else if (x & m2) {// this is 258
			bitscanforward(c9n, xc);
			m5 = x & m456; m8 = x & m789;
		}
		else {// this is 369
			bitscanforward(c8n, xc);
			m6 = x & m456; m9 = x & m789;
		}
	}
	return ValidGangMinlex(4);

}



	return 0;
}


void GANGMINLEX::Go78() {
	//cout << "entry go 78" << endl;
	for (int i = 0; i < 3; i++)if (ntst[i]) {
		//cout << "try stacks 12 for ip " << i << endl;
		{
			for (int j = 0; j < nt2x3; j++) {
				got = striplets[j];
				if (got.ip == i)  break;
			}
			int n = 0;
			for (int j = 0; j < nt2x2; j++) {
				if (spairs[j].ip == i)  gop[n++] = spairs[j];
			}
		}
		//got.Dump(); gop[0].Dump(); gop[1].Dump();
		gopa = gop[0]; gopb = gop[1];	if (Go78b()) return;
		gopa = gop[1]; gopb = gop[0];	if (Go78b()) return;
		got.ChangeStack(); gop[0].ChangeStack(); gop[1].ChangeStack();
		gopa = gop[0]; gopb = gop[1];	if (Go78b()) return;
		gopa = gop[1]; gopb = gop[0];	if (Go78b()) return;
	}
}
int GANGMINLEX::Go78b() {
	//got.Dump(); gopa.Dump(); gopb.Dump();
	int st3 = 2 - got.ip, st3d = 3 * st3;

	{
		m123 = got.v; m45 = gopa.v; m89 = gopb.v;
		m67 = 0x1ff ^ (m123 | m45 | m89);
		c1n = got.c1; c4n = got.c2;
		c2n = gopa.c1; c5n = gopa.c2;
		c3n = gopb.c1; c6n = gopb.c2;
		m456 = gb3[c2n]; m789 = gb3[c3n];
		m457 = gb3[c5n]; m689 = gb3[c6n];
		m6 = m67 & m456; m7 = m67 & m457;
		m12x = 0;

	}
	// locate 12x if exists
	{
		register int r = m123,*p=&gb3[st3d];
		if (_popcnt32(r & *p) >= 2) { m12x = *p; c7n = st3d; }
		else if (_popcnt32(r & *++p) >= 2) { m12x = *p; c7n = st3d+1; }
		else if (_popcnt32(r & *++p) >= 2) { m12x = *p; c7n = st3d + 2; }
	}
	if (m12x) {
		if (m12x == m123)goto go123;
		else {
			//cout<< Char9out(m12x) << " cas 12x" << endl;
			m12 = m123 & m12x;
			m3 = m123 & ~m12;
			if (m12x & m6)goto go126;
			else if (m12x & m45)goto go124;
			else  return 0;
		}
	}
	else {
		//cout << " cas 14 x " << endl;
		// use number of pairs to split the task
		if (nt2x2 == 6)goto go145;
		else if (nt2x2 == 4)goto go146;
		else if (nt2x2 == 2)goto go148;
		else return 0;
	}

	return 0;
go123: {//  123 458679 ig=5 123 468579 ig=6
	//cout << " cas 123" << endl;
	int mc9 = 0;	LOCATEUSING(mc9,c9n, m7)
	int x = mc9 & m456, y = mc9 & m89;
	if (!(x*y)) return 0; // must be one of each
	{  SPLIT2(m123, m1, m3)}
	m2 = m123 & ~(m1 | m3);
	int ns = 3 +3* st3d;// sum of the columns of the stack 3
	c8n = ns - c7n - c9n;
	m9 = y; m8 = m89 & (~m9);
	int mc8 = gb3[c8n];
	if (x & m6) {//  458 679 ig=5
		{  SPLIT2(m45, m4, m5)}
		return 	ValidGangMinlex(5);	
	}
	else {// 468 579 ig = 6
		m4 = mc8 & m45; m5 = mc9 & m45;
		return 	ValidGangMinlex(6);
	}
	return 0;

}
go124: {
	//cout << " cas 124" << endl;
	m4 = m12x & m45;
	{  SPLIT2(m12, m1, m2)}// assign 12
	int mc8 = 0; LOCATEUSING(mc8, c8n, m3)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c9n = ns - c7n - c8n;
	int mc9 = gb3[c9n];
	if (mc8 & m45) {//356 789 ig=7  358 679 ig=8 
		if (!(mc9 & m7)) return 0;
		 m5 = mc8 & m45;
		 if (mc8 & m6) { END89F(7); }//356 789 ig=7
		else { END8_9F(8); }//	358 679 ig = 8
	}
	if (mc8 & m6) {//367 589 ig=9 368 579 ig=10
		m5 = mc9 & m45;
		if (mc8 & m7) {	END89F(9);	}
		else { END8_9F(10); }
	}
	if (mc8 & m7) return 0;//389 567 ig=11
	END89F(11);
}
go126: {// 7c 345 789 ig=12  8c 347 589 ig=13 348 579 ig=14
//cout << " cas 126" << endl;
{  SPLIT2(m12, m1, m2)}// assign 12
int mc8 = 0; LOCATEUSING(mc8, c8n, m3)
int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
c9n = ns - c7n - c8n;
int mc9 = gb3[c9n];
if (!(mc8 & m45)) return 0;
m4 = mc8 & m45;	m5 = mc9 & m45;
if (mc8 & m7) { END89F(13); } //347 589 ig = 13	
else if(mc8 & m89) {END8_9F(14);}//348 579 ig=14
	
else {// 7c 345 789 ig=12
	{  SPLIT2(m45, m4, m5)}// assign 4 5
	{ END89F(12); }
}
return 0;
}

go145: {// 267 389 ig=15   268 379 ig=16 
	// locate 145 if exists
	int mc7 = 0;
	{
		register int r = m45, * p = &gb3[st3d];
		if (_popcnt32(r & *p) == 2) { mc7 = *p; c7n = st3d; }
		else if (_popcnt32(r & *++p) == 2) { mc7 = *p; c7n = st3d + 1; }
		else if (_popcnt32(r & *++p) == 2) { mc7 = *p; c7n = st3d + 2; }
	}
	if (!mc7)return 0;
	if (!(mc7 & m123)) return 0;
	int mc8 = 0; LOCATEUSING(mc8, c8n, m6)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c9n = ns - c7n - c8n;
	int mc9 = gb3[c9n];
	m1 = mc7 & m123; m2 = mc8 & m123; m3 = mc9 & m123;
	if ((!m1) || (!m2) || (!m3)) return 0;
	{  SPLIT2(m45, m4, m5)}// assign 4 5
	if (mc8 & m7) { END89F(15); } // 267 389 ig=15	
	else { END8_9F(16); }//  268 379 ig=16 
}
go146: {//146 258 379 ig = 17
	int mc7 = 0; LOCATEUSING(mc7, c7n, m6)
	int mc9 = 0; LOCATEUSING(mc9, c9n, m7)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c8n = ns - c7n - c9n;
	int mc8 = gb3[c8n];
	m1 = mc7 & m123;m2 = mc8 & m123; m3 = mc9 & m123;
	m4 = mc7 & m45;	m5 = mc8 & m45;
	if (!m4) return 0;
	{END8_9F(17); }

}
go148: {// 148 259 367 ig=18 
	int mc9 = 0; LOCATEUSING(mc9, c9n, m7)
		m3 = mc9 & m123; m12=m123 & ~m3;
	if(!(mc9&m6)) return 0;	if (!m3) return 0;
	{  SPLIT2(m12, m1, m2)}// assign 12
	int mc7 = 0; LOCATEUSING(mc7, c7n, m1)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c8n = ns - c7n - c9n;
	int mc8 = gb3[c8n];
	m4 = mc7 & m45;	m5 = mc8 & m45;
	m8 = mc7 & m89;	m9 = mc8 & m89;
	return 	ValidGangMinlex(18);
}
return 0;
}

void GANGMINLEX::Go9() {
	//cout << "entry go 9 nt2x2="<<nt2x2 << endl;
	if (!nt2x2) { Go9_43(); return; }
	for (int j = 0; j < 3; j++)
		if (npst[j] == 2) { Go9_19_38(); return; }	
	// now 39_42
	for (int i = 0; i < 3; i++) if (npst[i]) {
		//cout << "try stacks 12 for ip " << i << endl;
		{			
			int n = 0;
			for (int j = 0; j < nt2x2; j++) {
				if (spairs[j].ip == i)  gop[n++] = spairs[j];
			}
		}
		//gop[0].Dump(); gop[1].Dump(); gop[2].Dump();
		for (int j = 0; j < 3; j++) {
			//cout << "try pair first " << j << endl;
			gopa = gop[j];
			if (Go9_39_42()) return;
			gopa.ChangeStack();
			if (Go9_39_42()) return;
		}
	}

}

/*
int GANGMINLEX::Go78b() {
	got.Dump(); gopa.Dump(); gopb.Dump();
	int st3 = 2 - got.ip, st3d = 3 * st3;

	{
		m123 = got.v; m45 = gopa.v; m89 = gopb.v;
		m67 = 0x1ff ^ (m123 | m45 | m89);
		c1n = got.c1; c4n = got.c2;
		c2n = gopa.c1; c5n = gopa.c2;
		c3n = gopb.c1; c6n = gopb.c2;
		m456 = gb3[c2n]; m789 = gb3[c3n];
		m457 = gb3[c5n]; m689 = gb3[c6n];
		m6 = m67 & m456; m7 = m67 & m457;
		m12x = 0;

	}
	// locate 12x if exists
	{
		register int r = m123,*p=&gb3[st3d];
		if (_popcnt32(r & *p) >= 2) { m12x = *p; c7n = st3d; }
		else if (_popcnt32(r & *++p) >= 2) { m12x = *p; c7n = st3d+1; }
		else if (_popcnt32(r & *++p) >= 2) { m12x = *p; c7n = st3d + 2; }
	}
	if (m12x) {
		if (m12x == m123)goto go123;
		else {
			cout<< Char9out(m12x) << " cas 12x" << endl;
			m12 = m123 & m12x;
			m3 = m123 & ~m12;
			if (m12x & m6)goto go126;
			else if (m12x & m45)goto go124;
			else  return 0;
		}
	}
	else {
		cout << " cas 14 x " << endl;
		// use number of pairs to split the task
		if (nt2x2 == 6)goto go145;
		else if (nt2x2 == 4)goto go146;
		else if (nt2x2 == 2)goto go148;
		else return 0;
	}

	return 0;

go124: {
	//cout << " cas 124" << endl;
	m4 = m12x & m45;
	{  SPLIT2(m12, m1, m2)}// assign 12
	int mc8 = 0; LOCATEUSING(mc8, c8n, m3)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c9n = ns - c7n - c8n;
	int mc9 = gb3[c9n];
	if (mc8 & m45) {//356 789 ig=7  358 679 ig=8
		if (!(mc9 & m7)) return 0;
		 m5 = mc8 & m45;
		 if (mc8 & m6) { END89F(7); }//356 789 ig=7
		else { END8_9F(8); }//	358 679 ig = 8
	}
	if (mc8 & m6) {//367 589 ig=9 368 579 ig=10
		m5 = mc9 & m45;
		if (mc8 & m7) {	END89F(9);	}
		else { END8_9F(10); }
	}
	if (mc8 & m7) return 0;//389 567 ig=11
	END89F(11);
}

go148: {// 148 259 367 ig=18
	int mc9 = 0; LOCATEUSING(mc9, c9n, m7)
		m3 = mc9 & m123; m12=m123 & ~m3;
	if(!(mc9&m6)) return 0;	if (!m3) return 0;
	{  SPLIT2(m12, m1, m2)}// assign 12
	int mc7 = 0; LOCATEUSING(mc7, c7n, m1)
	int ns = 3 + 3 * st3d;// sum of the columns of the stack 3
	c8n = ns - c7n - c9n;
	int mc8 = gb3[c8n];
	m4 = mc7 & m45;	m5 = mc8 & m45;
	m8 = mc7 & m89;	m9 = mc8 & m89;
	return 	ValidGangMinlex(18);
}
return 0;
}
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
*/
void GANGMINLEX::Go9_19_38() {
	//cout << " see 19_38" << endl;
	for (int i = 0; i < 3; i++)		if (npst[i] == 2) {
		//cout << "try stacks 12 for ip " << i << endl;
		{
			int n = 0;
			for (int j = 0; j < nt2x2; j++) {
				if (spairs[j].ip == i)  gop[n++] = spairs[j];
			}
		}
		//gop[0].Dump(); gop[1].Dump();

		gopa = gop[0]; 	gopb = gop[1];
		if (Go9_19_38B()) return;
		gopa.ChangeStack(); gopb.ChangeStack();
		if (Go9_19_38B()) return;
		gopa = gop[1]; 	gopb = gop[0];
		if (Go9_19_38B()) return;
		gopa.ChangeStack(); gopb.ChangeStack();
		if (Go9_19_38B()) return;

	}


}
int GANGMINLEX::Go9_19_38B() {
	// pattern stacks 1 2   123 456 789  124 357 689
	//gopa.Dump(); gopb.Dump();
	c1n = gopa.c1; c4n = gopa.c2;
	c3n = gopb.c1; c6n = gopb.c2;
	m12 = gopa.v; m89 = gopb.v;

	int s1 = c1n / 3, s2 = c4n / 3, s3 = 3 - s1 - s2,
		s1d = 3 * s1, s2d = 3 * s2, s3d = 3 * s3;
	c2n = (3 + 3 * s1d) - c1n - c3n;
	c5n = (3 + 3 * s2d) - c4n - c6n;
	int v124, v357;
	m123 = gb3[c1n]; m456 = gb3[c2n]; m789 = gb3[c3n];
	v124 = gb3[c4n]; v357 = gb3[c5n]; m689 = gb3[c6n];
	{
		register int r = m123 | v124 | m789 | m689;
		if (_popcnt32(r) != 8) return 0;
		m5 = 0x1ff ^ r;

	}
	m3 = m123 & ~m12; m4 = v124 & ~m12;
	m6 = m689 & ~m89; m7 = m789 & ~m89;
	if (0) {
		cout << Char9out(m123) << " m123 " << endl;
		cout << Char9out(m456) << " m456 " << endl;
		cout << Char9out(m789) << " m789 " << endl;
		cout << Char9out(v124) << " v124 " << endl;
		cout << Char9out(v357) << " v357 " << endl;
		cout << Char9out(m689) << " m689 " << endl;

		cout << Char9out(m12) << " m12 " << endl;
		cout << Char9out(m89) << " m89 " << endl;

		cout << Char9out(m3) << " m3 " << endl;
		cout << Char9out(m4) << " m4 " << endl;
		cout << Char9out(m5) << " m5 " << endl;
		cout << Char9out(m6) << " m6 " << endl;
		cout << Char9out(m7) << " m7 " << endl;

		cout << c1n << " " << c2n << " " << c3n << " "
			<< c4n << " " << c5n << " " << c6n << endl;

	}
	if (nt2x2 == 2)goto go38;
	int v7n=0,v8n,v9n;
	for (int i = 0, j = s3d; i < 3; i++, j++) {
		register int vy = gb3[j],x=vy&m123;
		if (_popcnt32(x)==2) {//12 or 13
			c7n = j; v7n = vy; break;
		}
	}
	if (!v7n) return 0;
	if (v7n & m3) {
		//cout << " seen 29_37" << endl;
		m1 = v7n & m12; m2 = m12 & ~m1;
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			int vy = gb3[j];
			if (vy & m2) { c8n = j; v8n = vy; break; }
		}
		{
			int ns = 3 + 3 * s3d;// sum of the columns of the stack 3
			c9n = ns - c7n - c8n;
			v9n = gb3[c9n];
		}
		if (v8n & m4) return 0;	if (!(v8n & m89)) return 0;
		int vx = v7n & ~m123;
		if (vx & m4) {//258 679 ig=29 268 579 ig=30
			m8 = v8n & m89; m9 = v9n & m89;
			if (v8n & m5) return	ValidGangMinlex(29);	
			else if (v8n & m6) return	ValidGangMinlex(30);
			else return 0;

		}
		else if (vx & m5) {//268 479 ig=31 278 469 ig=32
			m8 = v8n & m89; m9 = v9n & m89;
			if (v8n & m6) return	ValidGangMinlex(31);
			else if (v8n & m7) return	ValidGangMinlex(32);
			else return 0;
		}
		else if (vx & m6) {//258 479 ig=33 278 459 ig=34
			m8 = v8n & m89; m9 = v9n & m89;
			if (v8n & m5) return ValidGangMinlex(33);
			else if (v8n & m7) return	ValidGangMinlex(34);	
			else return 0;

		}
		else if (vx & m7) {//268 459 ig=35
			if (!(v8n & m6)) return 0;
			m8 = v8n & m89; m9 = v9n & m89;
			return ValidGangMinlex(35);	
		}
		else {//138 259 467 ig=36 138 269 457 ig=37
			m8 = vx; m9 = m89 & ~m8;
			if (v8n & m5) return ValidGangMinlex(36);
			else if (v8n & m6) 	return ValidGangMinlex(37);	
			else return 0;
		}
	}
	else {
		//cout << " seen 19_28" << endl;
		{  SPLIT2(m12, m1, m2)}// assign 12
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			int vy = gb3[j];
			if (vy & m3) {	c8n = j; v8n = vy; break;	}
		}
		{
			int ns = 3 + 3 * s3d;// sum of the columns of the stack 3
			c9n = ns - c7n - c8n;
			v9n = gb3[c9n];
		}

		int vx = v7n & ~m12;
		if (vx & m5) {	//348 679 ig=19  367 489 ig=20
			//368 479 ig=21   378 469 ig=22
			if (v8n & m4) {
				m8 = v8n & m89; if (!m8) return 0;
				m9=v9n & m89;
				return ValidGangMinlex(19); 
			}
			else if (v9n & m6) {
				if (!(v8n & m7)) return 0;
				m8 = v8n & m89; if (!m8) return 0;
				m9 = v9n & m89;
				return ValidGangMinlex(22);	 
			}
			else if (v8n & m7) {
				if (!(v8n & m6)) return 0;
				{  SPLIT2(m89, m8, m9)}// assign 89
				return ValidGangMinlex(20);	 
			}
			else if (v8n & m6) {
				m8 = v8n & m89; if (!m8) return 0;
				m9 = v9n & m89;
				return ValidGangMinlex(21); 
			}
			else return 0;
		}
		else if (vx & m6) {// 358 479 ig=23 378 459 ig=24
			//389 457 ig=25
			if (v8n & m5) {
				m8 = v8n & m89; if (!m8) return 0;
				m9 = v9n & m89;
				return ValidGangMinlex(23);	 
			}
			else if (v8n & m7) {
				m8 = v8n & m89; if (!m8) return 0;
				m9 = v9n & m89;
				return ValidGangMinlex(24);	 

			}
			else if (!(v9n & m89)) {
				{  SPLIT2(m89, m8, m9)}// assign 89
				return ValidGangMinlex(25);	 

			}
			else return 0;
		}
		else if (vx & m89) {//345 679 ig=26 356 479 ig=27
			//359 467 ig=28
			if (!(v8n & m5)) return 0;
			m8 = vx; m9 = m89 & ~m8;
			if (v8n & m4)	return ValidGangMinlex(26);	 			
			else if (v8n & m6) return ValidGangMinlex(27);	
			else if (v8n & m9) return ValidGangMinlex(28);	
			else return 0;
		}
		else return 0;
	}


go38: {// 158 267 349 ig=38 
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & m5) {//158
				c7n = j;
				m1 = vy & m12; if (!m1) return 0;
				m8 = vy & m89; if (!m8) return 0;
			}
			else if (vy & m6) {//267
				c8n = j; if (!(vy & m7)) return 0;
				m2 = vy & m12; if (!m2) return 0;
			}
			else {//349
				c9n = j; if (!(m4 & vy)) return 0;
				if (!(vy & m3)) return 0;
				m9 = vy & m89;	if (!m9) return 0;
			}
		}
		return ValidGangMinlex(38);	
	}
	return 0;
}



/*
  134 258 679 ig=29 = 2 2 2	6
  134 268 579 ig=30 = 2 2 3	7
  135 268 479 ig=31 = 2 2 2	6
  135 278 469 ig=32 = 2 3 2	7
  136 258 479 ig=33 = 2 2 0	4
  136 278 459 ig=34 = 2 3 0	5
  137 268 459 ig=35 = 2 2 2	6
  138 259 467 ig=36 = 2 2 0	4
  138 269 457 ig=37 = 2 2 2	6

*/

int GANGMINLEX::Go9_39_42() {
	//gopa.Dump();
	c1n = gopa.c1; c4n = gopa.c2;
	int s1 = c1n / 3, s2 = c4n / 3, s3 = 3 - s1 - s2,
		s1d = 3 * s1, s2d = 3 * s2, s3d = 3 * s3;
	//cout << Char9out(gopa.v) << " Go9_39_42()" << c1n << c4n << " " << s1 << s2 << s3 << endl;
	int v125678 = gop[0].v | gop[1].v | gop[2].v, v349 = 0x1ff ^ v125678;
	m12 = gopa.v; m123 = gb3[c1n];
	m3 = m123 & v349; m4 = gb3[c4n] & v349; m9 = v349 & ~(m3 | m4);
	int v56, v78;
	// look for 378 in stack 2
	for (int i = 0, j = s2d; i < 3; i++, j++) {
		register int vy = gb3[j];
		if (!(vy & m3)) continue;
		v78 = vy & ~m3;	c5n = j;	break;
	}
	v56 = v125678 & ~(m12 | v78);
	// find missing columns stacks 1 and 2
	{
		int ns = 3 + 3 * s2d;// sum of the columns of the stack 3
		c6n = ns - c4n - c5n;
		for (int i = 0, j = s1d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & v56) c2n = j;
			else if (vy & v78) c3n = j;
		}
	}

	// now check stack3 depending on the gang(s) expected
	if (nt2x2 == 3)goto gog42;
	else if (nt2x2 == 6) goto gog40;
	// now can be /129 356 478 igang=39 137 245 689 igang=41
	{ 
		int cx3n, v3n, cx4n, v4n, cx9n, v9n;
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & m3) {	cx3n = j; v3n = vy; }
			else if (vy & m4) { cx4n = j; v4n = vy; }
			else if (vy & m9) { cx9n = j; v9n = vy; }
			else return 0;
		}
		if (cx3n == cx4n || cx3n == cx9n || cx4n == cx9n) return 0;
		if (v9n & v56) {//	137 245 689 igang = 41
			c7n = cx3n; c8n = cx4n; c9n = cx9n;
			m1 = v3n & m12; m2 = v4n & m12;
			m5 = v4n & v56; m6 = v9n & v56;
			m7 = v3n & v78; m8 = v9n & v78;
			return ValidGangMinlex(41);
		}
		else {//129 356 478 igang=39
			c7n = cx9n; c8n = cx3n; c9n = cx4n;
			if ((m12 & v9n) != m12) return 0;
			{SPLIT2(m12,m1, m2)}
			if ((v56 & v3n) != v56) return 0;
			{SPLIT2(v56, m5, m6)}
			{SPLIT2(v78, m7, m8)}
			return ValidGangMinlex(39);
		}
	return 0; 
	}
gog40: {//135 279 468 igang=40 
	{
		for (int i = 0, j = s3d; i < 3; i++, j++) {
			register int vy = gb3[j];
			if (vy & m3) {//135
				m5= vy & v56;
				c7n = j; m1 = vy & m12; if (!m1) return 0;
			}
			else if (vy & m9) {//279
				c8n = j; 
				m7 = vy & v78; m2 = vy & m12;
				if ((!m2) ||(!m7)) return 0;
			}
			else {//468
				c9n = j; if (!(m4 & vy)) return 0;
				m6 = vy & v56; m8 = vy & v78;
				if ((!m6) || (!m8)) return 0;
			}
		}
	}
	return ValidGangMinlex(40);
	}
gog42: {//157 268 349 igang=42 
		{
			int n = 0;
			for (int i = 0, j = s3d; i < 3; i++, j++) {
				int vy = gb3[j];
				if (vy & v349)  c9n = j;
				else if (n) {//268
					c8n = j;
					m2 = vy & m12; m6 = vy & v56; m8 = vy & v78;
				}
				else {//157
					n++; c7n = j;
					m1 = vy & m12; m5 = vy & v56;  m7 = vy & v78;
				}
			}
		}
		return ValidGangMinlex(42);
	}// end go 42
	return 0;
}

void GANGMINLEX::Go9_43() {//123 456 789 147 258 369 159 267 348	
	//cout << " see 43" << endl;
	// use first stack as start an set m1 m2 m3
	{
		c1n = 0; c2n = 1; c3n = 2;
		m123 = gb3[0]; m456 = gb3[1]; m789 = gb3[2];
		{  SPLIT2(m123, m1, m3)}
		m2 = m123 & ~(m1 | m3);
	}
	// find columns match in  stack2 3
	int v14759 = 0, v25867 = 0, v36948 = 0;
	int vx = 0x1ff & ~m123;
	{
		for (int i = 3; i < 9; i++) {
			register int v = gb3[i];
			if (v & m1)  v14759 |= v;
			else if (v & m2)  v25867 |= v;
			else v36948 |= v;
		}
	}
	int v68 = vx & ~v14759, v49 = vx & ~v25867,
		v57 = vx & ~v36948;
	// find m4 to m9
	{
		register int r = m456;
		m4 = r & v49; m5 = r & v57; m6 = r & v68;
		r = m789;
		m9 = r & v49; m7 = r & v57;  m8 = r & v68;
	}
	// find columnns
	{
		register int v147 = m1 | m4 | m7, v258 = m2 | m5 | m8,
			v369 = m3 | m6 | m9, v159 = m1 | m5 | m9,
			v267 = m2 | m6 | m7, v348 = m3 | m4 | m8;
		for (int i = 3; i < 9; i++) {
			int v = gb3[i];
			if (v == v147) c4n=i;
			else if (v == v258) c5n = i;
			else if (v == v369) c6n = i;
			else if (v == v159) c7n = i;
			else if (v == v267) c8n = i;
			else  c9n = i;
		}

	}
	ValidGangMinlex(43);
}
