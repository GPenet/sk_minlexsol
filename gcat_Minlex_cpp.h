
// index to the 416 band 1 after r2c4 r2c7 r2c8 r3c1 r3c2
int bminlex_tindex[50] = { 
	31, 65, 92, 110, 126, 135,		//00_ 123 
	139, 166, 186, 196, 208, 214,	//06_ 126 
	217, 234, 239,					//12_ 132 68 69 86(1)
	240, 262, 277, 284, 298, 303,	//15_ 162 
	309, 322, 332, 334, 343, 346,	//21_ 163  
	347, 349, 354, 357,				//27_ 216 68 69 86 89
	359,362, 366, 369, 375, 378,	//31_ 261
	379, 381, 382, 386, 392, 395,	//37_ 263
	397, 407,						//43_ 361 89 98
	409, 411,						//45_ 362 89 98
	412,415,416						//47_861_862 
};

struct BMINLEX {// receive a band send back i416 and morphing data
	int minirows[9], minicols[9], cx[9], minirr[9];
	int* minir0[3], * minic0[3],*minird[3];
	BMINLEX() {
		minir0[0] = minirows; minir0[1] = &minirows[3]; minir0[2] = &minirows[6];
		minic0[0] = minicols; minic0[1] = &minicols[3]; minic0[2] = &minicols[6];
	}
	int debug;
	BANDPERM pout;
	int* b0;
	int	indexlim,minindex,maxindex,  goback,  maxret,indexret,bindex;
	int cmap[9], dmap[9], r3mapped[9],crit4,crit4b,critcomp;
	char r3c[10];
	int ipr, ipst,ipb1, nxcols,nx3, nx2,mcnx3; // perms rows stacks
	int* rr, 
		r1, r2, r3, rd1, rd2, rd3, * mr1, * mr2, * mr3;
	int  * px;// minicols of the perm
	int *oc1,c1n, c2n, c3n, c4n, c5n, c6n, c7n, c8n, c9n;
	int m1, m2, m3, m4, m5, m6, m7, m8, m9;
	int mc1, mc2, mc3, mc4, mc5, mc6, mc7, mc8, mc9;
	int* ss, s1, s2, s3, m123, m456, m789, m457, m689, mx89;
	int m45, m89, mx, m12;
	int r2c7, r2c8, ir2c4, ir2c7,r3c1,r3c2;
	void InitMiniCols();
	void Init(int* grid, int lim,int debugging=0) ;

	void I457end();
	void DumpInit() ;
	int SetMinMax(int min, int max) ;
	inline void MapDigits();
	inline void EndMapping();
	void Mapping() ;
	int CheckMapping() ;
	void DumpMapping() ;
	void Map(int* d);
	inline int MapPat(int x) ;
	uint32_t Map4Pats(int a, int b, int c, int d) ;
	void Status(int op = 0) ;
	
	int ValidMinlex(int i,int endmap=1);
	inline int Vret();

	int GetforMinlex(int* grid, int myb1, int debugging = 0);

	int SetupRSC_A() ;
	void GoMinlex_0_30() ;
	void DoMapping0();
	void DoMapping1();
	void GoA_case6();
	void GoA_case71();
	void GoA_case70() ;
	void GoA_case8() ;
	void GoA_case9() ;


	void GoB_case6();
	void GoB_case70();
	void GoB_case71() ;
	void GoB_case8_3_go();
	void GoB_case8_1_go();
	void GoB_case8_2_go();

	void SetCrit(int ia);
	int GetIndex4(uint32_t* t, uint32_t v, uint32_t& r);
	int GetCrit9(uint32_t* t, uint32_t v, int i1, int i2);

	void GoB_case9_1_go();
	void GoB_case9_2_go();
	void T412p();
	void Go_412();
	void Go_413();
	void Go_414_415() ;
	void Status6() ;
	inline int Is456minir4x();
	void SetPout(int iret);
}bmlw;
int tbit9[9] = { 1,2,4,8,16,32,64,128,256 };
inline void  BMINLEX::MapDigits()
{
	register int r;
	bitscanforward(r, m1); dmap[r] = 0; bitscanforward(r, m2); dmap[r] = 1;
	bitscanforward(r, m3); dmap[r] = 2; bitscanforward(r, m4); dmap[r] = 3;
	bitscanforward(r, m5); dmap[r] = 4; bitscanforward(r, m6); dmap[r] = 5;
	bitscanforward(r, m7); dmap[r] = 6; bitscanforward(r, m8); dmap[r] = 7;
	bitscanforward(r, m9); dmap[r] = 8;
}
inline void  BMINLEX::EndMapping()
{
	register int* cm = pout.cols;
	cm[0] = px[c1n]; cm[1] =px[c2n]; cm[2] = px[c3n];
	cm[3] = px[c4n]; cm[4] = px[c5n]; cm[5] = px[c6n];
	cm[6] = px[c7n]; cm[7] = px[c8n]; cm[8] = px[c9n];
	memcpy(pout.map, dmap, sizeof dmap);
	memcpy(pout.rows, rr, 12);
	pout.i416 = minindex;
}

#define MAXLIMCHK(A) {if (A < maxindex) {maxindex = A; if (A < indexlim) {	goback = 1; return;}}}
#define PATS4TO_INT(X,A, B,C, D) {X = 1111;register int r;\
	bitscanforward(r, A); X += 1000 * dmap[r];	bitscanforward(r, B); X += 100 * dmap[r];\
	bitscanforward(r, C); X += 10 *  dmap[r];	bitscanforward(r, D); X +=  dmap[r];}
#define GOGO(N,G) MAXLIMCHK(N) I457end(); G; if (goback) return;break
//#define GOGO(N,G) MAXLIMCHK(N) I457end();Status(); G; if (goback) return;break
// if 1r2c4 reached, the min can be applied
#define GOGO1(M,N,G) if (SetMinMax(M,N)) return; I457end(); G; if (goback) return;break


int BMINLEX::GetforMinlex(int* grid, int myb1, int debugging ) {
	Init(grid, myb1,debugging);
	if (debugging)cout << " exit min max " << minindex << " " << maxindex << endl;
	return Vret();
}

inline int BMINLEX::Vret() {
	if (maxindex < indexlim)return -1;
	if (minindex > indexlim) return 1;
	return 0;
}
int BMINLEX::ValidMinlex(int i, int endmap ) {
	p_cpt2g[10]++;
	minindex = maxindex = i;
	goback = 1;
	if (endmap) {
		goback++;
		EndMapping();
	}
	return 1;
}
void  BMINLEX::InitMiniCols() {
	{
		minicols[0] = tbit9[b0[0]] | tbit9[b0[9]] | tbit9[b0[18]];
		minicols[1] = tbit9[b0[1]] | tbit9[b0[10]] | tbit9[b0[19]];
		minicols[2] = tbit9[b0[2]] | tbit9[b0[11]] | tbit9[b0[20]];
		minicols[3] = tbit9[b0[3]] | tbit9[b0[12]] | tbit9[b0[21]];
		minicols[4] = tbit9[b0[4]] | tbit9[b0[13]] | tbit9[b0[22]];
		minicols[5] = tbit9[b0[5]] | tbit9[b0[14]] | tbit9[b0[23]];
		minicols[6] = tbit9[b0[6]] | tbit9[b0[15]] | tbit9[b0[24]];
		minicols[7] = tbit9[b0[7]] | tbit9[b0[16]] | tbit9[b0[25]];
		minicols[8] = tbit9[b0[8]] | tbit9[b0[17]] | tbit9[b0[26]];

	}
}

void BMINLEX::Init(int* grid, int lim, int debugging) {
	goback = 0;// to stop at the first hit or over limit
	indexlim = lim;
	debug = debugging;
	if (debug)cout << "lim=" << lim << endl;
	b0 = grid;
	{// try 0_30 31_415
		minirows[0] = tbit9[grid[0]] | tbit9[grid[1]] | tbit9[grid[2]];
		minirows[5] = tbit9[grid[15]] | tbit9[grid[16]] | tbit9[grid[17]];
		if (minirows[0] == minirows[5]|| (!(minirows[0] & minirows[5]))) {
			minindex = 0; maxindex = 30;
			if (maxindex < indexlim)goback = 1;
			if (minindex > indexlim)goback = 1;
		}
		else {
			minindex = 31; maxindex = 415;
			if (maxindex < indexlim)goback = 1;
			if (minindex > indexlim)goback = 1;
		}
		if (goback) return;
		minirows[1] = tbit9[grid[3]] | tbit9[grid[4]] | tbit9[grid[5]];
		minirows[2] = tbit9[grid[6]] | tbit9[grid[7]] | tbit9[grid[8]];
		{
			minirows[3] = tbit9[grid[9]] | tbit9[grid[10]] | tbit9[grid[11]];
			minirows[4] = tbit9[grid[12]] | tbit9[grid[13]] | tbit9[grid[14]];
			minirows[6] = tbit9[grid[18]] | tbit9[grid[19]] | tbit9[grid[20]];
			minirows[7] = tbit9[grid[21]] | tbit9[grid[22]] | tbit9[grid[23]];
			minirows[8] = tbit9[grid[24]] | tbit9[grid[25]] | tbit9[grid[26]];
		}
	}
	if (debug) cout << "try min max " << minindex << " " << maxindex << endl;

	InitMiniCols();
	int vr;// for the case 7cols with triplet
	{// setup the column count
		nxcols = 1, cx[9];
		cx[0] = minicols[0];
		register int i, j;
		for (i = 1; i < 9; i++) {
			register int v = minicols[i];
			for (j = 0; j < nxcols; j++) {
				if (v == cx[j]) { vr = v; v = 0; break; }
			}
			if (v)  cx[nxcols++] = v;
		}
	}
	if (nxcols == 7) {// need the count of triplets
		register int vt = vr, n = 0, i;
		for (i = 0; i < 9; i++)if (vt == minicols[i])n++;
		if (n == 3)nx3 = 1; else nx3 = 0;
	}

	// 7  2 cases triplet or 2 pairs
	if (!minindex)GoMinlex_0_30(); // block 0-30   456 in minirow 4			
	else {// Block 457 in minirow 4

		if (SetMinMax(31, 415)) return;

		int smaller_r2c4 = 8;
		p_cpt2g[20]++;
		for (ipr = 0; ipr < 6; ipr++) {// 6 pairs rows
			{
				register int* p = tpermgang[ipr];
				rr = p;
				minird[0] = minir0[p[0]];
				minird[1] = minir0[p[1]];
				minird[2] = minir0[p[2]];
			}
			for (ipst = 0; ipst < 6; ipst++) {// 6 pairs stacks
				{
					register int* pc = tpermgang[ipst];
					px = tpermg9stk[ipst];
					// check validity of the perm
					{
						register int r1 = minird[0][pc[1]],
							r2 = minird[1][pc[0]],
							r3 = r1 & r2;
						if (_popcnt32(r3) != 2) continue;
						m456 = r1; m457 = r2; m45 = r3;
					}
					p_cpt2g[21]++;
					//continue;
					m123 = minird[0][pc[0]]; m789 = minird[0][pc[2]];
					mx89 = minird[1][pc[1]];
					m6 = m456 & ~m45; m7 = m457 & ~m45;
					m89 = m789 & ~m7; mx = mx89 & ~m89;
					// get ordered mini columns
					{
						register int* rc = minic0[pc[0]];
						memcpy(cx, rc, 12);
						rc = minic0[pc[1]];
						memcpy(&cx[3], rc, 12);
						rc = minic0[pc[2]];
						memcpy(&cx[6], rc, 12);
					}
				}
				if (debug) {
					cout << "try perm" << ipr << ipst
						<< " min max "<< minindex <<" "<< maxindex << endl;
					if (0){
						for (int i = 0; i < 9; i++)cout << Char9out(cx[i]) << " cx i=" << i << endl;
					}
				}
				// Find the 1,2,3 in mini row 4
				{ // get c6 get c3 get c4 get c1,2
					register int i, m = m6;
					// get c6 exit to 413p if x89 x in c6
					{
						if (m & cx[3])i = 3;
						else if (m & cx[4])i = 4;
						else i = 5;
						c6n = i;  mc6 = cx[i];
						if (debug) {
							cout << Char9out(m6) << " m6" << endl;
							cout << Char9out(mc6) << " mc6 6n=" << c6n << endl;
						}


						if (mx & mc6) {
							if (smaller_r2c4 < 8) continue;
							T412p(); if(goback) return ;
							continue;
						}

					}
					// get c3 m using m7  then c4 using mx m4 m5
					{
						m = m7;
						if (m & cx[0])i = 0;
						else if (m & cx[1])i = 1;
						else i = 2;
						c3n = i;  mc3 = cx[i];
						m3 = m123 & mc3;
						m = mx;
						if (m & cx[3])i = 3;
						else if (m & cx[4])i = 4;
						else i = 5;
						c4n = i;  mc4 = cx[i];
						m4 = m456 & mc4;
					}
					// get c1 using m4 then c2 m1,m2
					{
						m = m4;
						if (m & cx[0])i = 0;
						else if (m & cx[1])i = 1;
						else i = 2;
						c1n = i;  mc1 = cx[i];
						m1 = m123 & mc1;
						c2n = 3 - c1n - c3n; // cols 012
						mc2 = cx[c2n];
						m2 = m123 & mc2;
					}
					p_cpt2g[22]++;
					if (mx & m3) {
						if (smaller_r2c4 < 3) continue;
						else {
							smaller_r2c4 = ir2c4 = 3;
							MAXLIMCHK(411)
							switch (nxcols) {
							case 5:ValidMinlex(411); return;// cout << "thi is 411" << endl; return;
							case 6:if (SetMinMax(397, 403)) return;
								I457end(); GoB_case6(); if (goback) return;
								break;// can not be lower
							case 7:
								if (nx3) continue;
								else GOGO(408, GoB_case70());
							case 8: GOGO(410, GoB_case8_3_go());
							default: continue; // not valid
							}
						}
					}
					else 	if (mx & m2) {
						if (smaller_r2c4 < 2) continue;
						else { MAXLIMCHK(396)
							smaller_r2c4 = ir2c4 = 2;
						}
						switch (nxcols) {
						case 7:
							if (nx3) continue;
							else GOGO(396, GoB_case70());
						case 8:GOGO(387, GoB_case8_2_go());
						case 9:GOGO(395, GoB_case9_2_go());
						default: continue; // not valid
						}
					}
					else if (mx & m1) {
						//cout << nxcols << " cols" << endl;
						//MAXLIMCHK(346)
						smaller_r2c4 = ir2c4 = 1;
						switch (nxcols) {
						case 7:
							if (!nx3) continue;
							else GOGO1(223,306, GoB_case71());
						case 8:GOGO1(32,346, GoB_case8_1_go());
						case 9:GOGO1(31,345, GoB_case9_1_go());
						default: continue; // not valid
						}
					}
				}
				if (goback) {
					cout << " exit seen" << endl;
					if (debug)Status(1);
					return;
				}
			}// end ipst
			if (goback) return;
		}// end ipr		
	}
}
/*
 min max   457
	6	3 397 403
	70  2 392 396
	70	3 402 408
	71	1 223 306
	8	1  32 346
	8	2 361 387
	8	3 398 410
	9	1  31 345
	9	2 347 395
	*/

void BMINLEX::I457end() {
	m5 = m456 & ~(m4 | m6);
	c5n = 12 - c4n - c6n; // cols 3 4 5
	mc5 = cx[c5n]; m8 = mx89 & mc5; m9 = mx89 & mc6;
	MapDigits();
	// Get c7 c8 c9
	{
		register int i, m = m7;		
		if (m & cx[6])i = 6;
		else if (m & cx[7])i = 7;
		else i = 8;
		c7n = i;  mc7 = cx[i];
		m = m8;
		if (m & cx[6])i = 6;
		else if (m & cx[7])i = 7;
		else i = 8;
		c8n = i;  mc8 = cx[i];
		c9n = 21 - c8n - c7n; // cols 678
		mc9 = cx[c9n];
	}
	// get crit 8/9 digits 
	{
		register int mi6, mi7, mi8, mi9;// mini rows 6_9
		{
			register int* pc = tpermgang[ipst];
			mi6 = minird[1][pc[2]]; mi7 = minird[2][pc[0]];
			mi8 = minird[2][pc[1]]; mi9 = minird[2][pc[2]];
		}
		r2c7 = mi6 & mc7; r2c8 = mi6 & mc8;
		PATS4TO_INT(crit4, r2c7, r2c8, mi7 & mc1, mi7 & mc2)
		PATS4TO_INT(crit4b, mi8 & mc4, mi8 & mc5, mi9 & mc7, mi9 & mc8)
		critcomp= 100000000 * ir2c4+ 10000 * crit4 + crit4b;
	}

}



void BMINLEX::DumpInit() {
	for (int i = 0; i < 27; i++) cout << b0[i] + 1;
	cout << "nxcols=" << nxcols << endl;
	cout  << " minirows" << endl;;
	for (int ir = 0, i = 0; ir < 3; ir++) {
		for (int j = 0; j < 3; j++, i++)
			cout << Char9out(minirows[i]) << "_";
		cout << endl;
	}
	cout << "minicols" << endl;
	for (int ir = 0, i = 0; ir < 3; ir++) {
		for (int j = 0; j < 3; j++, i++)
			cout << Char9out(minicols[i]) << "_";
		cout << endl;
	}

}
int BMINLEX::SetMinMax(int min, int max) {
	if (min > minindex)minindex = min;
	if (max <  maxindex)maxindex = max;
	if (maxindex < indexlim)goback = 1;
	if (minindex > indexlim)goback = 1;
	return goback;
}
void BMINLEX::Mapping() {
	int dmr[9];
	// row map is given in *rr
	// colmap combine c.n and cx[]
	bitscanforward(dmr[0], m1); bitscanforward(dmr[1], m2);
	bitscanforward(dmr[2], m3); bitscanforward(dmr[3], m4);
	bitscanforward(dmr[4], m5); bitscanforward(dmr[5], m6);
	bitscanforward(dmr[6], m7); bitscanforward(dmr[7], m8);
	bitscanforward(dmr[8], m9);
	for (int i = 0; i < 9; i++)dmap[dmr[i]] = i;
	cmap[0] = px[c1n]; cmap[1] = px[c2n]; cmap[2] = px[c3n];
	cmap[3] = px[c4n]; cmap[4] = px[c5n]; cmap[5] = px[c6n];
	cmap[6] = px[c7n]; cmap[7] = px[c8n]; cmap[8] = px[c9n];
	
}
int BMINLEX::CheckMapping() {
	Mapping();
	int cx = 0, dx = 0;
	for (int i = 0; i < 9; i++) {
		int c = cmap[i], d = dmap[i];
		if (c < 0 || d < 0 || c>8 || d>8) return 1;
		cx |= 1 << c; dx |= 1 << d;
	}
	if (dx != 0x1ff || cx != 0x1ff) return 1;
	return 0;
}
void BMINLEX::DumpMapping() {
	cout << "Mapping status perms" << ipr << ipst << " rows " << r1 << r2 << r3 << endl;
	cout << "columns ";
	for (int i = 0; i < 9; i++) cout << cmap[i] << ",";
	cout << " digits ";
	for (int i = 0; i < 9; i++) cout << dmap[i] << ",";
	cout << endl;
	int d[27];
	Map(d);
}
void BMINLEX::Map(int* d) {
	for (int irow = 0; irow < 3; irow++) {
		int* rold = &b0[9 * rr[irow]],
			* dr = &d[9 * irow];
		for (int ic = 0; ic < 9; ic++) {
			dr[ic] = dmap[rold[cmap[ic]]];
			cout << dr[ic] + 1;
		}
	}
	cout << endl;
}

inline int BMINLEX::MapPat(int x) {// x digit pat to map
	int xn;
	bitscanforward(xn, x);
	return dmap[xn];
}
uint32_t BMINLEX::Map4Pats(int a, int b, int c, int d) {
	int x1 = MapPat(a), x2 = MapPat(b), x3 = MapPat(c), x4 = MapPat(d);
	return (1111 + 1000 * x1 + 100 * x2 + 10 * x3 + x4);
}


void BMINLEX::Status(int op) {
	cout << "setupr col perm " << ipr << ipst << " ir2c4=" << ir2c4 << endl;
	for (int i = 0; i < 9; i++) cout << dmap[i] + 1; cout << " dmap"
		<< endl;
	cout << critcomp <<" " << crit4 <<" " << crit4b << endl;
	if (op==0) return;

	cout << Char9out(m123) << " m123 " << endl;
	cout << Char9out(m456) << " m456 " << endl;
	cout << Char9out(m457) << " m457 " << endl;
	cout << Char9out(mx89) << " mx89 " << endl;
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

	cout << Char9out(r2c7) << " r2c7 " << endl;
	cout << Char9out(r2c8) << " r2c8 " << endl;


	cout << c1n << c2n << c3n << c4n << c5n << c6n << c7n << c8n << c9n << " cnn " << endl;
	cout << Char9out(mc1) << " mc1 " << endl;
	cout << Char9out(mc2) << " mc2 " << endl;
	cout << Char9out(mc3) << " mc3 " << endl;
	cout << Char9out(mc4) << " mc4 " << endl;
	cout << Char9out(mc5) << " mc5 " << endl;
	cout << Char9out(mc6) << " mc6 " << endl;
	cout << Char9out(mc7) << " mc7 " << endl;
	cout << Char9out(mc8) << " mc8 " << endl;
	cout << Char9out(mc9) << " mc9 " << endl;

}


int BMINLEX::SetupRSC_A() {

	for (ipr = 0; ipr < 6; ipr++) {// 6 rows order
		//if (ipr != 5) continue;
		{
			register int* p = tpermgang[ipr];
			rr = p;
			memcpy(minirr, minir0[p[0]], 12);
			memcpy(&minirr[3], minir0[p[1]], 12);
			memcpy(&minirr[6], minir0[p[2]], 12);
		}
		//cout << " ipr" << ipr << endl;
		//for (int i = 0; i < 9; i++)
		//	cout << Char9out(minirr[i]) << " i=" << i << endl;
		for (ipst = 0; ipst < 6; ipst++) {// 6  stacks order
			//if (ipst != 5) continue;
			{
				register int* pc = tpermgang[ipst];
				px = tpermg9stk[ipst];
				// check validity of the perm
				{
					register int r1 = minirr[pc[0] + 3],
						r2 = minirr[pc[1]];
					if (r1 != r2) continue;
					if(debug)cout << ipr << ipst << " go" << endl;
					m456 = r1;
					m123 = minirr[pc[0]];
					m789 = minirr[pc[2]];
				}
				// get ordered mini columns 
				{
					register int m123789 = m123 | m789,
						m123456 = m123 | m456,
						m456789 = m456 | 789;
					register int* rc = minic0[pc[0]];
					memcpy(cx, rc, 12);
					rc = minic0[pc[1]];
					memcpy(&cx[3], rc, 12);
					rc = minic0[pc[2]];
					memcpy(&cx[6], rc, 12);
				}

				for (ipb1 = 0; ipb1 < 6; ipb1++) {// 6  order columns in box 1
					register int* p1 = tpermgang[ipb1];
					// fing columns order
					{
						c1n = p1[0]; c2n = p1[1]; c3n = p1[2];	
						mc1 = cx[c1n]; mc2 = cx[c2n]; mc3 = cx[c3n];
						register int i, x, y, w, r = m456;
						m4 = x = r & mc1;	m5 = y = r & mc2;	m6 = r & mc3;
						for (i = 3; i < 6; i++) {
							w =  cx[i];
							if (w & x) {c4n = i;mc4= cx[c4n];}
							else if(w & y) { c5n = i; mc5 = cx[c5n]; }
							else { c6n = i; mc6 = cx[c6n]; }
						}
						r = m789;
						m7 = x = r & mc4;	m8 = y = r & mc5;	m9 = r & mc6;
						for (i = 6; i < 9; i++) {
							w = cx[i];
							if (w & x) { c7n = i; mc7 = cx[c7n]; }
							else if (w & y) { c8n = i; mc8 = cx[c8n]; }
							else { c9n = i; mc9 = cx[c9n]; }
						}
						r = m123;
						m1 = r & mc1; m2 = r & mc2; m3 = r & mc3;
					}
					if(debug)Status6();
					if ((m3 & mc7)||(m1 & mc8)|| (m9 & mc1)) continue;
					//cout << " go to check" << endl;
					MapDigits();
					// set crit comp
					{
						PATS4TO_INT(crit4, m123&mc7, m123&mc8,m789 & mc1, m789 & mc2)
						PATS4TO_INT(crit4b, m123 & mc4, m123 & mc5, m456 & mc7, m456 & mc8)
						critcomp =  10000 * crit4 + crit4b;

					}
					switch (nxcols) {
					case 6:if (SetMinMax(2, 26)) return 1;
						GoA_case6(); if (goback)return 1; break;
					case 7:if (SetMinMax(3, 20)) return 1;
						if (nx3) {
							if (SetMinMax(3, 8)) return 1;
							GoA_case71(); if (goback)return 1; break;
						}
						else {
							if (SetMinMax(4, 20)) return 1;
							GoA_case70(); if (goback)return 1; break;
						}
					case 8:
						if (SetMinMax(5, 27)) return 1;
						GoA_case8(); if (goback)return 1; break;
					case 9:
						if (SetMinMax(6, 30)) return 1;
						GoA_case9(); if (goback)return 1; break;
					}
				}
			}
		}
	}
	return 0;
}

void BMINLEX::GoMinlex_0_30() {
	p_cpt2g[30]++;
	if (SetMinMax(0, 30)) return;
	px = tpermg9stk[0];// default value
	if(debug)cout << "GoMinlex_0_30() ncols "<< nxcols << endl;
	if (nxcols > 5) SetupRSC_A();
	else {
		switch (nxcols) {
		case 3: {
			p_cpt2g[10]++;
			minindex = maxindex = 0;
			goback = 1;
			if (!indexlim) DoMapping0();
			return;
		}
		case 5: {
			p_cpt2g[10]++;
			minindex = maxindex = 1;
			goback = 1;
			if (indexlim == 1) DoMapping1();
			return;
		}
		}
	}

}
void BMINLEX::DoMapping0() {
	pout.InitBase(0);
	for (int i = 0; i < 9; i++)// init to morph on columns
		pout.map[i] = i;
	// align  the columns on box 1
	{
		int np = 0, n1 = 0;
		for (int i = 0; i < 3; i++) {
			register int r = cx[i], n = 0;
			for (int j = 3; j <6; j++) {
				if (minicols[j] == r)
					pout.cols[3 + i] = j;
			}
			for (int j = 6; j < 9; j++) {
				if (minicols[j] == r)
					pout.cols[6 + i] = j;
			}
		}
	}
	int bn[27];
	pout.Morph(b0, bn);
	for (int i = 0; i < 9; i++)// init map to row 1
		pout.map[bn[i]] = i;
	maxindex = minindex = 0; goback = 1;	return;
}
void BMINLEX::DoMapping1() {
	//123 456 789  
	//456 789 123  
	//789 123 465 5 1 2
	pout.InitBase(1);
	for (int i = 0; i < 9; i++)// init to morph on columns
		pout.map[i] = i;
	// find the columns analysing the 5 cx
	int cxn[5], cxvn[5][3], cxt, cxp[2], cx1[2];
	{
		int np = 0,n1=0;
		for (int i = 0; i < 5; i++) {
			int* vn = cxvn[i];
			register int r = cx[i],n=0;
			for (int j = 0; j < 9; j++) {
				if (minicols[j] == r)
					vn[n++] = j;
			}
			cxn[i] = n;
			if (n == 2)cxp[np++] = i;
			else if (n == 3)cxt = i;
			else cx1[n1++] = i;
		}

	}
	int st1, st2, st3;// get stacks
	{
		register int* y = cxvn[cxp[0]];// first pair
		st1 = y[0] / 3; st2 = y[1] / 3;
		y = cxvn[cx1[0]];// first single
		st3 = y[0] / 3;
	}
	// now assign the triplet in stack order
	// assign the pairs in entry order
	{
		register int* y = pout.cols,* w=cxvn[cxt];
		y[0]= w[st1];	y[3] = w[st2]; y[6] = w[st3];
		w = cxvn[cxp[0]]; y[1] = w[0]; y[4] = w[1];
		w = cxvn[cxp[1]]; y[2] = w[0]; y[5] = w[1];
	}
	// align singles on pairs 2 common digits
	{
		int ia = cx1[0], ib = cx1[1],
			cxa = cx[ia], cxr=cx[cxp[0]],
			ca = cxvn[ia][0], cb = cxvn[ib][0];
		if (_popcnt32(cxr & cxa) == 2) {
			pout.cols[7] = ca; pout.cols[8] = cb;
		}
		else {
			pout.cols[7] = cb; pout.cols[8] = ca;
		}
	}
	// take common digits columns 3 and 9
	// ad third digit column 9
	int x8 = minicols[pout.cols[8]],x3= minicols[pout.cols[2]],
		xc =x3 & x8,	x = x8 & ~xc, y = x3 & ~xc, y3n,x8n;
	bitscanforward(x8n, x); bitscanforward(y3n, y);
	int bn[27];
	pout.Morph(b0, bn);
	for (int i = 0; i < 3; i++) {
		if (bn[9 *i +2] == y3n)pout.rows[1] = i;
		if (bn[9 *i +8] == x8n)pout.rows[2] = i;
	}
	pout.rows[0] = 3 - pout.rows[1] - pout.rows[2];
	int* dr = &bn[9 * pout.rows[0]];
	for (int i = 0; i < 9; i++)// init map to row 1
		pout.map[dr[i]] = i;
	maxindex = minindex = 1; goback = 1;	return;
}


uint32_t tmin6_c6v[3] = { 12781256,13781254,23781264 };
uint32_t tmin6_c6i[3] = { 2,17,26 };

void BMINLEX::GoA_case6() {// 2 17 26
	//cout << "this is A 6 _ 2 17 26 " << critcomp << " goback="<<goback << endl;
	if (debug)cout << " entry case 6 cols min max "
		<< minindex << " " << maxindex << endl;
	int ir = GetCrit9(tmin6_c6v, critcomp, 0, 3);
	if (ir < 0) return;
	if (debug) {
		cout << "this is band " << tmin6_c6i[ir] << endl;
	}
	ValidMinlex(tmin6_c6i[ir]);

}

uint32_t tmin6_c71v[2] = { 12781346,12791346 };
uint32_t tmin6_c71i[2] = { 3,8, };
uint32_t tmin6_c70v[3] = { 12781354,13781354,13782145 };
uint32_t tmin6_c70i[3] = { 4,18,20 };

void BMINLEX::GoA_case71() {// 3 8
	//cout << "this is A 71 _ 3 8" << endl;
	int ir = GetCrit9(tmin6_c71v, critcomp, 0, 2);
	if (ir < 0) return;
	//cout << "this is band " << tmin6_c71i[ir] << endl;
	ValidMinlex(tmin6_c71i[ir]);

}
void BMINLEX::GoA_case70() {// 4 18 20
	//cout << "this is A 70 _ 4 18 20" << endl;
	int ir = GetCrit9(tmin6_c70v, critcomp, 0, 3);
	if (ir < 0) return;
	//cout << "this is band " << tmin6_c70i[ir] << endl;
	ValidMinlex(tmin6_c70i[ir]);

}

uint32_t tmin6_c8v[7] = {12781356,12791354,12791356,13781356,13782164,13782165,23781354,};
uint32_t tmin6_c8i[7] = { 5,9,10,19,21,22,27, };
void BMINLEX::GoA_case8() {// 5 9 10 19 21 22 27
	//cout << "this is A 8 _ 5 9 10 19 21 22 27" << endl;
	int ir = GetCrit9(tmin6_c8v, critcomp, 0, 7);
	if (ir < 0) return;
	//cout << "this is band " << tmin6_c8i[ir] << endl;
	ValidMinlex(tmin6_c8i[ir]);
}

uint32_t tmin6_c9v[14] = {
12782356,12782364,12792156,12792165,12792356,12792364,12892356,12892364,13782354,13782356,
13872356,23782356,23783145,23792164, };
uint32_t tmin6_c9i[14] = {6,7,11,12,13,14,15,16,23,24,25,28,29,30,};
void BMINLEX::GoA_case9() {// 6 7 11 12 13 14 15 16 23 24 25 28 29 30
	//cout << "this is A 9 _ 	6 7 11 12 13 14 15 16 23 24 25 28 29 30" << endl;
	int ir = GetCrit9(tmin6_c9v, critcomp, 0, 14);
	if (ir < 0) return;
	//cout << "this is band "<< tmin6_c9i[ir] << endl;
	ValidMinlex(tmin6_c9i[ir]);

}



//===============  processing 457 mini row 4

void BMINLEX::SetCrit(int ia) {
}
int BMINLEX::GetIndex4(uint32_t* t, uint32_t v, uint32_t& r) {
	int i = 0;
	while (i < 100) {// safety
		register uint32_t vc = t[i];
		if (vc > v) return 1;
		if (vc == v) {
			r = i >> 1;
			return 0;
		}
		i += 2;
	}
	return 1; // fail soul never happen
}
int BMINLEX::GetCrit9(uint32_t* t, uint32_t v, int i1, int i2) {
	register uint32_t crit = v;
	for (int i = i1; i < i2; i++) {
		register uint32_t x = t[i];
		if (x > crit) return -1;
		if (x == crit) return i;
	}
	return -1;
}


/*
389 612 896 127 345 band index397
389 612 896 172 345 band index399
389 612 896 217 345 band index401
389 612 896 271 345 band index403

*/
void BMINLEX::GoB_case6(){
	if(crit4!=6189) return;
	int a = crit4b / 100, b = crit4b - 100 * a, x;
	if (b != 34) return;
	if (a == 12)x = 397;
	else if (a == 17)x = 399;
	else if (a == 21)x = 401;
	else if (a == 27)x = 403;
	else return;
	ValidMinlex(x);
	//cout << "band is there " << x << endl;
}

uint32_t tmin_c71v[7] = {132683215,132683245,162683215,162687215,162687245,162983215,162983245};
uint32_t tmin_c71i[7] = { 223,224,246,251,253,304,306 };
void BMINLEX::GoB_case71() {
	if (debug)cout << "GoB_case71() "  << endl;
	int ir = GetCrit9(tmin_c71v, critcomp, 0, 7);
	if (ir < 0) return;
	ValidMinlex(tmin_c71i[ir]);
	if(debug)cout << "band is there " << tmin_c71i[ir] << endl;
	if (goback) return;;
}

uint32_t tmin_c70v[6] = { 263961325,263967325,263981325,361892135,361897135,361982135 };
uint32_t tmin_c70i[6] = { 392,394,396,402,405,408 };

void BMINLEX::GoB_case70() {
	int ir = GetCrit9(tmin_c70v, critcomp, 0, 6);
	if (ir < 0) return;
	ValidMinlex(tmin_c70i[ir]);
	//cout << "band is there " << tmin_c70i[ir] << endl;
	if (goback) return;;
}

//________________ 457 8 columns
uint32_t tmin_c8v[87] = {
123682315,123682345,123683214,123683215,123683241,123683245,123683251,123683254,123687214,123687215,//9
123687241,123687251,123687254,123687315,123692315,123697315,123867315,123892315,123897315,123962315,//19
123967315,123982315,123983215,126683215,126683241,126683251,126683254,126687214,126687215,126687245,//29
126983214,126983215,126983245,132682345,132682745,132683254,132687214,132687241,162682315,162682715,//39
162683214,162683715,162687214,162687241,162687251,162687254,162687315,162687345,162693215,162863215,//49
162893215,162893245,162963215,162983214,162983241,162983251,162983254,163683215,163687214,163687251,//59
163687315,163692314,163692315,163692714,163693214,163697314,163892314,163892341,163893214,163893714,//69
163983214,261687125,261693125,261867124,261867324,261891324,261893124,261897324,263867325,263891325,//79
361891235,361891735,361892735,361897235,361981735,362891234,362892135,
};
uint32_t tmin_c8i[87] = {
	32,34,43,44,45,46,47,48,55,56,//9
	57,58,59,61,66,89,109,111,124,126,//19
	134,135,137,148,149,150,151,157,158,159,//29
	214,215,216,217,221,225,228,229,241,243,//39
	245,248,250,252,254,255,257,259,268,281,//49
	291,293,299,303,305,307,308,313,316,317,//59
	319,322,323,325,326,330,334,335,336,340,//69
	346,361,364,366,367,369,371,373,385,387,//79
	398,400,404,406,407,409,410,
};
uint32_t tmin_c8_i4_toi6[31][2] = {
	{2368,0}, {2369,14},{2386,16},{2389,17},{2396,19},
	{2398,21},{2668,23},{2698,30},{3268,33},{6268,38},//10
	{6269,48},{6286,49},{6289,50},{6296,52},{6298,53},
	{6368,57},{6369,61},{6389,66},{6398,70},{9999,71},// 20//ends1
	{6168,71},{6169,72},{6186,73},{6189,75},{6386,78},
	{6389,79},{9999,80},{6189,80},{6198,84},{6289,85},//30// end2
	{9999,87},
};
void BMINLEX::GoB_case8_3_go() {
	uint32_t ir1;
	if (GetIndex4(tmin_c8_i4_toi6[27], crit4, ir1)) return;
	ir1 += 27;
	int ind1 = tmin_c8_i4_toi6[ir1][1], ind2 = tmin_c8_i4_toi6[ir1 + 1][1];
	register int ir = GetCrit9(tmin_c8v, critcomp, ind1, ind2);
	if (ir < 0) return;
	//cout << "band is there " << tmin_c8i[ir] << endl;
	ValidMinlex(tmin_c8i[ir]);
}
void BMINLEX::GoB_case8_1_go() {
	//cout << " GoB_case8_1_go() " << crit4 << " " << crit4b  << endl;

	uint32_t ir1;
	if (r2c7 == m2) {
		if (GetIndex4(tmin_c8_i4_toi6[0], crit4, ir1)) return;
	}
	else  {
		if (GetIndex4(tmin_c8_i4_toi6[8], crit4, ir1)) return;
		ir1 += 8;
	}

	int ind1 = tmin_c8_i4_toi6[ir1][1], ind2 = tmin_c8_i4_toi6[ir1 + 1][1];
	register int ir = GetCrit9(tmin_c8v, critcomp, ind1, ind2);
	if (ir < 0) return;
	ValidMinlex(tmin_c8i[ir]);
	//cout << "band is there " << tmin_c8i[ir] << endl;
}
void BMINLEX::GoB_case8_2_go() {
	//cout << " GoB_case8_2_go() " << endl;
	uint32_t ir1;
	if (GetIndex4(tmin_c8_i4_toi6[20], crit4, ir1)) return;
	ir1 += 20;

	int ind1 = tmin_c8_i4_toi6[ir1][1], ind2 = tmin_c8_i4_toi6[ir1 + 1][1];
	//cout << "ir1=" << ir1 << " ind1=" << ind1 << " ind2=" << ind2
	//	<< " crit=" << crit << endl;
	register int ir = GetCrit9(tmin_c8v, critcomp, ind1, ind2);
	if (ir < 0) return;
	//cout << "band is there " << tmin_c8i[ir] << endl;
	ValidMinlex(tmin_c8i[ir]);
}

//________________ 457 9 columns
uint32_t tmin_c9v[276] = {
123682314,123682341,123682351,123682354,123682714,123682715,123682741,123682745,123682751,123682754,//9
123683714,123683715,123683741,123683745,123683751,123683754,123687314,123687341,123687351,123687354,//19
123692314,123692341,123692351,123692354,123692714,123692715,123692741,123692751,123692754,123693214,//29
123693215,123693241,123693254,123693714,123693715,123693741,123693751,123693754,123697214,123697215,//39
123697241,123697251,123697314,123697341,123697351,123862314,123862351,123862714,123862715,123862741,//49
123862751,123863215,123863241,123863251,123863714,123863715,123863741,123863751,123867214,123867215,//59
123867251,123867314,123892314,123892351,123892714,123892715,123892751,123893214,123893215,123893251,//69
123893714,123893715,123893751,123897215,123897251,123897351,123962351,123962751,123963215,123963251,//79
123963715,123963751,123967215,123982715,123983715,126682314,126682341,126682345,126682351,126682715,//89
126682741,126682745,126682751,126682754,126683714,126683715,126683741,126683745,126683751,126687314,//99
126687315,126687341,126687345,126687351,126687354,126692315,126692341,126692345,126692351,126692714,//109
126692741,126692745,126692751,126693214,126693215,126693241,126693245,126693251,126693715,126693741,//119
126693751,126693754,126697314,126697315,126697345,126862315,126862341,126862351,126862745,126863241,//129
126863245,126863251,126863714,126863715,126863751,126892314,126892315,126892345,126893214,126893215,//139
126893241,126893245,126893251,126893254,126893714,126893715,126893745,126963214,126963215,126963241,//149
126963251,126963254,126963714,132682351,132682354,132682714,132682754,132683741,132683754,132687314,//159
132687341,132687351,132687354,132692314,132692354,132692751,132692754,132697341,132863751,162682314,//169
162682714,162682754,162683714,162683751,162687314,162687341,162687351,162687354,162692314,162692315,//179
162692354,162692714,162692715,162693214,162693251,162693714,162693715,162697314,162697315,162697341,//189
162697351,162697354,162862314,162862714,162862715,162862745,162863714,162863715,162892314,162892315,//199
162892341,162892345,162892351,162892354,162893214,162893241,162893251,162893714,162893715,162893745,//209
162963214,162963241,162963714,162963715,163682314,163682714,163682715,163682751,163683714,163683715,//219
163687314,163687351,163687354,163692351,163693215,163693254,163693715,163697351,163862714,163863714,//229
163893215,163893245,163893254,163893715,163893745,163963214,163963215,163963245,216681745,216687125,//239
216691342,216691352,216693125,216693152,216697125,216867124,216867324,216867352,216893124,216897352,//249
261681724,261687124,261691325,261693124,261697124,261867325,261891325,261893142,261897325,261961324,//259
261961325,261967324,261981324,263681724,263687125,263693125,263867124,263867125,263867324,263891324,//269
263891342,263893124,263893125,263897324,263967324,263981324,
};
uint32_t tmin_c9i[276] = {
31,33,35,36,37,38,39,40,41,42,//9
49,50,51,52,53,54,60,62,63,64,//19
65,67,68,69,70,71,72,73,74,75,//29
76,77,78,79,80,81,82,83,84,85,//39
86,87,88,90,91,92,93,94,95,96,//49
97,98,99,100,101,102,103,104,105,106,//59
107,108,110,112,113,114,115,116,117,118,//69
119,120,121,122,123,125,127,128,129,130,//79
131,132,133,136,138,139,140,141,142,143,//89
144,145,146,147,152,153,154,155,156,160,//99
161,162,163,164,165,166,167,168,169,170,//109
171,172,173,174,175,176,177,178,179,180,//119
181,182,183,184,185,186,187,188,189,190,//129
191,192,193,194,195,196,197,198,199,200,//139
201,202,203,204,205,206,207,208,209,210,//149
211,212,213,218,219,220,222,226,227,230,//159
231,232,233,234,235,236,237,238,239,240,//169
242,244,247,249,256,258,260,261,262,263,//179
264,265,266,267,269,270,271,272,273,274,//189
275,276,277,278,279,280,282,283,284,285,//199
286,287,288,289,290,292,294,295,296,297,//209
298,300,301,302,309,310,311,312,314,315,//219
318,320,321,324,327,328,329,331,332,333,//229
337,338,339,341,342,343,344,345,347,348,//239
349,350,351,352,353,354,355,356,357,358,//249
359,360,362,363,365,368,370,372,374,375,//259
376,377,378,379,380,381,382,383,384,386,//269
388,389,390,391,393,395, };
uint32_t tmin_c9_i4_toi6[42][2] = {
	{2368,0},{2369,20},{2386,45},{2389,62},{2396,76},
	{2398,83},{2668,85},{2669,105},{2686,125},{2689,135},//10
	{2696,147},{3268,153},{3269,163},{3286,168},{6268,169},
	{6269,178},{6286,192},{6289,198},{6296,210},{6368,214},//20
	{6369,223},{6386,228},{6389,230},{6396,235},{9999,238},// end 1xxx
	{1668,238},{1669,240},{1686,245},{1689,248},{6168,250},//30
	{6169,252},{6186,255},{6189,256},{6196,259},{6198,262},
	{6368,263},{6369,265},{6386,266},{6389,269},{6396,274},//40
	{6398,275},{9999,276}
};
void BMINLEX::GoB_case9_1_go() {
	//cout << "91go" << endl;
	//Status(1);
	uint32_t ir1;
	if (GetIndex4(tmin_c9_i4_toi6[0], crit4, ir1)) return;
	int ind1 = tmin_c9_i4_toi6[ir1][1], ind2 = tmin_c9_i4_toi6[ir1 + 1][1];
	register int ir = GetCrit9(tmin_c9v, critcomp, ind1, ind2);
	if (ir < 0) return;
	//cout << "band is there " << tmin_c9i[ir] << endl;
	ValidMinlex(tmin_c9i[ir]);
}
void BMINLEX::GoB_case9_2_go() {
	if (r2c7 == m3) return;
	if (r2c7 == m1 && r2c8 == m3) return;
	uint32_t ir1;
	if (r2c7 == m1) {
		if (GetIndex4(tmin_c9_i4_toi6[25], crit4, ir1)) return;
		ir1 += 25;
	}
	else if (r2c8 == m1) {
		if (GetIndex4(tmin_c9_i4_toi6[29], crit4, ir1)) return;
		ir1 += 29;
	}
	else {
		if (GetIndex4(tmin_c9_i4_toi6[35], crit4, ir1)) return;
		ir1 += 35;
	}

	int ind1 = tmin_c9_i4_toi6[ir1][1], ind2 = tmin_c9_i4_toi6[ir1 + 1][1];
	register int ir = GetCrit9(tmin_c9v, critcomp, ind1, ind2);
	if (ir < 0) return;
	//cout << "band is there " << tmin_c9i[ir] << endl;
	ValidMinlex(tmin_c9i[ir]);

}
//________________ 457 over 410 r2c4=8
/*
	
	123 456 789 _ 
	457 893 612 _
	896 217 354 _   414    	7 1 0
	//
	123 456 789 _ 
	457 893 612 _ 
	986 217 354 _   415    	7 1 0
*/
void BMINLEX::T412p() {
	if (debug)cout << "T412p() nxcols=" << nxcols << endl;
	if (nxcols == 3) {	Go_412(); return;	}
	if (nxcols == 5) { Go_413(); return; }
	if (nxcols != 7) return;	
	if(nx3!=1)return;// column 367 3 times
	Go_414_415();	
}
void BMINLEX::Go_412() {// mapping if 
	if (debug)cout << "this is band 412" << endl;
	if (indexlim != 412)	{
		maxindex = minindex = 412; goback = 1;	return;
	}
	// mapping to do <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	ValidMinlex(412);
}
void BMINLEX::Go_413() {//mapping if
	if (debug)cout << "this is band 413" << endl;
	if (indexlim != 413) {
		maxindex = minindex =  413;	 goback = 1; return;	}
	// mapping to do <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	ValidMinlex(413);

}
void BMINLEX::Go_414_415() {//mapping if
	if (indexlim < 414) {  minindex = 414;	goback = 1; return; }
	//cout << "Go_414_415() " << endl;
	//DumpInit();
	// get c3 m using m7  then c1 c2 m4 m5
	register int i, m = m7;
	{
		if (m & cx[0])i = 0;
		else if (m & cx[1])i = 1;
		else i = 2;
		c3n = i;  mc3 = cx[i]; m3 = m123 & mc3;
		int c12 = 7 ^ (1<<c3n);
		bitscanforward(c1n, c12);
		mc1 = cx[c1n]; m1 = m123 & mc1; m4 = m456 & mc1;
		bitscanreverse(c2n, c12);
		mc2 = cx[c2n]; m2 = m123 & mc2; m5 = m456 & mc2;
	}
	if(!(mc3&m6) )return;
	for (int i = 3; i < 6; i++){// get c4n  c5n c6n m8 m9
		m = cx[i];
		if (m4 & m) { c4n = i;  mc4 = m; m8 = m789 & mc4; }
		else if (m5 & m) { c5n = i;  mc5 = m; m9 = m789 & mc5; }
		else { c6n = i;  mc6 =m; }
	}
	if (!(mc4 & m2)) return; if (!(mc5 & m1)) return;
	for (int i = 6; i < 9; i++) {// get c7n  c8n c9n 
		m = cx[i];
		if (m7 & m) { c7n = i;  mc7 = m; }
		else if (m8 & m) { c8n = i;  mc8 = m; }
		else { c9n = i;  mc9 = m; }
	}
	if (!(mc7 & m6)) return; if (!(mc7 & m3)) return;
	if (!(mc8 & m1)) return; if (!(mc8 & m5)) return;

	MapDigits();
	//ir2c4 = 8;	
	//Status(1);	
	if (mc1 & m8) {
		if (indexlim != 414) {
			maxindex = minindex = 414;	 goback = 1; return;
		}
		//cout << "this is band 414"  << endl;
		ValidMinlex(414);
	}
	else {
		if (indexlim != 415) {
			maxindex = minindex = 415;	 goback = 1; return;
		}
		//cout << "this is band 415" << endl;
		ValidMinlex(415);
		//cout << " back minlex" << endl;
	}
}

/*
123 456 789 _
457 893 612 _
896 217 354 _   414    	7 1 0
123 456 789 _
457 893 612 _
986 217 354 _   415    	7 1 0	// get crit 8/9 digits
*/
	
	void BMINLEX:: Status6() {
		cout << "setupr col perm " << ipr << ipst <<  ipb1 << endl;
		cout << c1n << c2n << c3n << c4n << c5n << c6n << c7n << c8n << c9n << endl;
		cout << Char9out(m123) << " m123 " << endl;
		cout << Char9out(m456) << " m456 " << endl;
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

		cout << Char9out(mc1) << " mc1 " << endl;
		cout << Char9out(mc2) << " mc2 " << endl;
		cout << Char9out(mc3) << " mc3 " << endl;
		cout << Char9out(mc4) << " mc4 " << endl;
		cout << Char9out(mc5) << " mc5 " << endl;
		cout << Char9out(mc6) << " mc6 " << endl;
		cout << Char9out(mc7) << " mc7 " << endl;
		cout << Char9out(mc8) << " mc8 " << endl;
		cout << Char9out(mc9) << " mc9 " << endl;

	}
		inline int BMINLEX::Is456minir4x() {
		return ((minirows[0] == minirows[4]) || (minirows[0] == minirows[7]));
	}

	void BMINLEX::SetPout(int iret){};