#define stack1_54 07007007007007007
struct OPCOMMAND {// decoding command line option for this rpocess
	// processing options 
	int opcode;
	int tbn, bx3;// 
	int t18, p1, p2, p2b,//17 of 18 clues, pass or 2 (2a or 2b)
		p2min,
		b2slice, // runing a slice of bands 2 in 18 mode bfx[0] & 8
		b3low, // running band 1 pass1 for slices in pass2 bfx[0] & 16
		out_one,// limit output to one per band 3 .bfx[2] & 1
		out_entry, //output of the entry file for test DLL .bfx[2] & 2
		known; // 1 if known process 2 if known filter active .bfx[2] & 4
	// bfx[2] & 8 special use b2_is as limit b3
	int b1;//band 1 in process 
	int b2, b2_is;//bands b2  forced
	char* b2start;
	int first, last;
	int ton;//test on and test level
	uint64_t f0, f3, f4, f7, f10; // filters p_cpt2g [3] [4) [7]
	int upto3, upto4; // active below f3 below f4
	int dv12, dv3;// print fresh uas bands 1 2 band 3
	int dumpa;
	int test_ned;
	void SetUp(int opcod, int k = 0, int print = 1) {// init known or not
		memset(this, 0, sizeof * this);
		opcode = opcod;
		known = k;
		test_ned = sgo.bfx[5];
		if (!test_ned )test_ned = 63;// take all good in NED
		tbn = sgo.vx[10];
		bx3 = sgo.vx[11];
		f0 = sgo.vx[12];
		if (sgo.bfx[0] & 1)t18 = 1;
		if (sgo.bfx[0] & 6) {// pass 1 2a 2b
			p2 = 1;
			if (sgo.bfx[0] & 4) p2b = 1;
			if (p2b && t18) { p2b = 0; }
		}
		else p1 = 1;
		if (t18 && (sgo.bfx[0] & 8)) {// slice of bands 
			b2slice = 1;
		}
		if (p1 && (sgo.bfx[0] & 16))b3low = 1;

		b1 = sgo.vx[0];
		first = sgo.vx[2];
		last = sgo.vx[3];
		if (last == 0) if (last == 0) { last = first; sgo.vx[3] = first; }  // default if no -v3- given
		b2_is = sgo.vx[4];
		b2 = sgo.vx[5];
		if (sgo.s_strings[0])	if (strlen(sgo.s_strings[0]))
			b2start = sgo.s_strings[0];
		ton = sgo.vx[1];

		f3 = sgo.vx[6];	f4 = sgo.vx[7];
		f7 = sgo.vx[8]; f10 = sgo.vx[9];

		if (sgo.bfx[1] & 1)upto3 = 1;
		if (sgo.bfx[1] & 2)upto4 = 1;
		if (sgo.bfx[1] & 4)dv12 = 1;
		if (sgo.bfx[1] & 8)dumpa = 1;
		if (sgo.bfx[1] & 16)dv3 = 1;

		if (sgo.bfx[2] & 1) out_one = 1;
		if (sgo.bfx[2] & 2) out_entry = 1;
		if(out_entry && ton==5)out_entry = -1;
		if (known)if (sgo.bfx[2] & 4) known = 2;
		if (print) {
			cout << Char9out(sgo.bfx[0]) << " sgo.bfx[0 " << endl;
			cout << "standard processing commands_______________" << endl;
			if (t18) cout << "\t\tsearch 18 clues via -b0-x." << endl;
			else cout << "\t\tsearch 17 clues via -b0-x." << endl;
			if (p1)cout << "\t\tpass1 via -b0-.x." << endl;
			if (p2)cout << "\t\tpass2 via -b0-.x." << endl;
			if (p2b)cout << "\t\tpass2b via -b0-..x." << endl;
			cout << sgo.vx[0] << " b1  -v0- band 0_415" << endl;
			cout << sgo.vx[2] << " first  -v2- first slice to process" << endl;
			cout << sgo.vx[3] << " last  -v3- last slice to process must be >= vx[2]" << endl;
			if (b2slice) {
				cout << "running a slice of bands 2 index from="
					<< b2_is << " to=" << b2 << endl;
			}
			if (b3low)
				cout << " pass1 with limit in band 3 index <= band1 index " << endl;
			if (out_one) cout << " max one out per band 3 sgo.bfx[2] & 1 " << endl;
			if (out_entry)  cout << " file1 contains attached solution grids" << endl;
			cout << "debugging commands___________________" << endl;
			if (known) {
				cout << "processing solution grids with known" << endl;
				if (known > 1)cout << "\tfilter on path active  sgo.bfx[2] & 2" << endl;
			}
			if (b2)		cout << b2 << " b2 -v5- filter band 2 index" << endl;
			if (bx3 < 416)		cout << bx3 << " b3 index" << endl;
			if (b2start)	cout << b2start << " filter band 2 start" << endl;

			if (ton)cout << ton << "  test on  -v1- verbose mode " << endl;
			if (f0)cout << f0 << "  f0  -vz- diag skip pairs b1b2" << endl;
			if (f3)cout << f3 << "  f3  -v6- diag filter 3 clues [3]" << endl;
			if (f4)cout << f4 << "  f4  -v7- diag filter 6 clues [6]" << endl;
			if (f7)cout << f7 << "  f7  -v8- diag filter go full [7]" << endl;
			if (dv12)cout << "  -b1-..x  dump add in valid b12" << endl;
			if (dumpa)cout << "  -b1-...x  dump uas b12 at the start" << endl;
			if (upto3)cout << "upto debugging [3]  sgo.bfx[1] & 1 " << endl;
			if (upto4)cout << "upto debugging [4]  sgo.bfx[1] & 2 " << endl;
			if (dv3)cout << " -b1-...x print fresh adds " << endl;
			cout << test_ned << "  option de test pout entrée" << endl;
		}
	}
	void SetUp79() {// init 
		memset(this, 0, sizeof * this);
		opcode = 79;
	}
}op;
#define UACNBLOCS 15


struct STD_B416 {
	char band[28];// band in char mode
	int i416,// id 0-415 in minlex mode of the band
		map[27],// mapping cells from minlex to solution grid
		band0[27], // band in 0-8 integer mode
		gangster[9], // bit field digits per column
		dpat[9],// solution pat per digit
		dpmi[9],// initial map gangster per digit
		dband;
	void Initstd();// first band initial (once)
	void GetBandTable(int i416e);//pick up band 1 from table
	void InitG12(int i416e);// end init band 1 
	void InitBand2_3(int i16, char* ze, BANDMINLEX::PERM& p
		, int iband = 1);

	void InitC10(int i);// known mode
	void SetGangster();


	void PrintStatus();
};
struct STD_B3 :STD_B416 {// data specific to bands 3
	// permanent gangster information
	struct G {
		BF128 gsocket2, gsocket3;// active i81 mode 81 bits
		BF128 gsocket4, gsocket6;//g2 with 4 cells in band 3
		BF128 gsocket2all;
		int pat2[81], pat3[81]; // storing ua bitfields
		int pat2_27[27]; // storing ua bitfields
		int ua2_imini[81], ua3_imini[81], ua2bit27[81];
	}g;
	char isg2[81],isg3[81];
	uint32_t  mg2, mg3,minc,ming2_1, ming2_2, ming2_3;
	int minirows_bf[9];
	int triplet_perms[9][2][3];
	uint32_t i_27_to_81[27], i_9_to_81[9]; //band i81 for guas guas3
	uint32_t i_81_to_27[81]; //band i81 for guas guas3
	uint32_t  poutdone, aigskip,
		tg2_4[50], ntg2_4, tg2_6[50], ntg2_6;
	//_______________________
	void InitBand3(int i16, char* ze, BANDMINLEX::PERM& p);



	void Pat_to_digitsx(int bf, int* tcells, int* tdigits, int& nt) {
		register int cell;
		nt = 0;
		while (bitscanforward(cell, bf)) {
			bf ^= 1 << cell;
			tcells[nt] = cell;
			tdigits[nt++] = band0[cell];
		}
	}
	int Is_Pat_For_Mex(int* tcells, int* tdigits, int nt) {
		for (int i = 0; i < nt; i++) {
			if (band0[tcells[nt]] != tdigits[nt]) return 0;
		}
		return 1;
	}
	void DumpIndex() {
		cout << "index 27 to 81 " << endl;
		for (int i = 0; i < 27; i++) {
			register uint32_t i81 = i_27_to_81[i];
			cout << i << " i81=" << i81 << " " << Char27out(g.pat2[i81]) << endl;
		}
		cout << "index 9 to 81 " << endl;
		for (int i = 0; i < 9; i++) {
			register uint32_t i81 = i_9_to_81[i];
			cout << i << " i81=" << i81 << " " << Char27out(g.pat3[i81]) << endl;
		}

	}

#define GM_NB4 50
#define GM_NBM 50

	struct GUM64 {
		uint64_t v0,  vc[55];//vc[54] is for 6 clues
		uint32_t tb3[64], n;
		void Init() {
			n = 0;		v0 = 0;
			memset(vc, 255, sizeof vc);
			vc[54] = 0;
		}
		int Add(uint64_t bf, uint32_t patb3) {
			if (n >= 64) return 0;//safety
			tb3[n] = patb3;
			uint64_t bit = (uint64_t)1 << n++;
			v0 |= bit; vc[54] |= bit;
			register uint64_t B = bf, nbit = ~bit;
			int cell;
			while (bitscanforward64(cell, B)) {
				B ^= (uint64_t)1 << cell;
				vc[cell] &= nbit;
			}
			return 1;
		}
		inline void Set6(uint32_t* t) {
			register uint64_t v = v0;
			for (int i = 0; i < 6; i++) v &= vc[t[i]];
			vc[54] = v;
		}
		inline uint64_t Getv(uint32_t* t, int nt) {
			register uint64_t v = vc[54];
			for (int i = 0; i < nt; i++) v &= vc[t[i]];
			return v;
		}

		void Dump(int i0) {
			for (uint32_t i = 0; i < n; i++) {
				uint64_t bit = (uint64_t)1 << i;
				cout <<Char27out(tb3[i]) << "\t";
				for (int j = 0; j < 54; j++)
					if (vc[j] & bit) cout << ".";
					else cout << "1";
				cout << "  " << i + i0 << endl;
			}
		}

		uint64_t bf12;// mode 54
		uint32_t bf3;
		inline int Count() {
			return ((int)_popcnt64(bf12) + _popcnt32(bf3));
		}
		void Print() {
			cout << Char54out(bf12) << "\t";
			cout << Char27out(bf3)
				<< " " << Count() << endl;
		}
	}tgm64[GM_NB4], tgm64m[GM_NBM];
	uint32_t nbgm,  nbbgm, nbgmm, nbbgmm;
	void InitTg() {
		nbgm = nbbgm =  0;
		nbgmm = nbbgmm = 0;
		for (int i = 0; i < GM_NB4; i++) tgm64[i].Init();
		for (int i = 0; i < GM_NBM; i++) tgm64m[i].Init();
	}
	inline void Addm4(BF128 &w) {// entry mode 3x
		if (nbgm >= 64 * GM_NB4) return;
		nbbgm = nbgm++ >> 6; // new last bloc 
		register uint64_t U = w.bf.u64[0];
		U = (U & BIT_SET_27) | ((U & BIT_SET_B2) >> 5);// mode 54
		tgm64[nbbgm].Add(U, w.bf.u32[2]);
	}
	inline void Addmm(BF128& w) {// entry mode 3x
		if (nbgmm >= 64 * GM_NBM) return;
		nbbgmm = nbgmm++ >> 6; // new last bloc 
		register uint64_t U = w.bf.u64[0];
		U = (U & BIT_SET_27) | ((U & BIT_SET_B2) >> 5);// mode 54
		tgm64m[nbbgmm].Add(U, w.bf.u32[2]);
	}

	inline void Set6clues(uint32_t * tc) {
		for (uint32_t i = 0; i <= nbbgm; i++) 
			tgm64[i].Set6(tc);
		for (uint32_t i = 0; i <= nbbgmm; i++) 
				tgm64m[i].Set6(tc);
	}

};


//____ entry builder
void BandReShape(int* s, int* d, BANDMINLEX::PERM p);
void BandReOrder(int* d);
struct GEN_BANDES_12 {// encapsulating global data 
	int modeb12, go_back, diagmore, diagbug, ip20,
		it16, it16_2, it16_3;// , imin16_1, imin16_2, imin16_3;
	int idt16[3];// diagonal
	int irtw2,iret_diag;
	char zsol[82], rband2[28];
	int grid0[81],gbit[81],gfree[81],colband1[9],
		grid1[81], gw[81], tc[6], ntc;

	uint64_t   nb12;
	int sliceread, current_slice, bit_slice, maxbits;
	BANDMINLEX::PERM *t_auto_b1, * t_auto_p1,// maxi is 107
		t_auto_b1b2[108], t_auto_b2b1[108], t_auto_b1r4[108], t_auto_b1r4r5[108],
		pband2, pband3;
	int n_auto_b1, n_auto_p1, n_auto_b1b2, n_auto_b2b1,
		n_auto_b1r4, n_auto_b1r4r5;
	int cold[9], coldf[9], rowd[6], boxd[6], rowdb3[3], boxdb3[3]; //free digits 
	int b4dmr[3], b5dmr[3], b6dmr[3], r7dmr[2], r8dmr[2], r9dmr[2],
		b4b5dmr[3], b7b8dmr[3];
	int b5dkmr[3], r6mfree[3], b3colfree[9],b9free[3],r8free[9];

	// stack 1 builder
	int colds[3], rowds[6], boxds[3]; //free digits 
	int istack1[27];
	char stack1[28];
	//_________________ gangster 
	int gangcols[9];// 9 bits fields band3 for each colum (see valid band2)
	int gangb12[9]; // digit bf bands 12 per column


	struct TWW {
		int zs0[81],zsa[27],zsb[27], zs1[81], ib[3], ibx[3],*zco;
		BANDMINLEX::PERM perm_ret;
		void PutBandFirst(int i1) {
			if (!i1)return;
			int temp[27];
			memcpy(temp, &zs0[27 * i1], sizeof temp);
			memcpy(&zs0[27 * i1], zs0, sizeof temp);
			memcpy(zs0, temp, sizeof temp);
		}
		void PermB2B3() {
			int temp[27];
			memcpy(temp, &zs0[27], sizeof temp);
			memcpy(&zs0[27], &zs0[54], sizeof temp);
			memcpy(&zs0[54], temp, sizeof temp);

		}
		void PermB( int i1, int i2) {
			register int ix = ib[i1];  ib[i1] = ib[i2]; ib[i2] = ix;
			ix = ibx[i1];  ibx[i1] = ibx[i2]; ibx[i2] = ix;
			int temp[27];
			memcpy(temp, &zs0[27 * i1], sizeof temp);
			memcpy(&zs0[27 * i1], &zs0[27 * i2], sizeof temp);
			memcpy(&zs0[27 * i2], temp, sizeof temp);
		}
		void RigthOrder() {
			if (ibx[1] < ibx[0])PermB(  0, 1);
			if (ibx[2] < ibx[0])PermB(  0, 2);
			if (ibx[2] < ibx[1])PermB(  1, 2);
		}
		void MorphToB1() {
			BandReShape(zs0, zs1, perm_ret);
			BandReShape(&zs0[27], &zs1[27], perm_ret);
			BandReShape(&zs0[54], &zs1[54], perm_ret);
		}
		void MorphToB1First() {
			bandminlex.Getmin(zs0, &perm_ret);
			MorphToB1();
			memcpy(zs0, zs1, sizeof zs0);
		}


		void InitAndMorph(int* zo, BANDMINLEX::PERM& p,int first) {
			memcpy(zs0, zo, sizeof zs0);
			PutBandFirst(first);
			perm_ret = p;
			MorphToB1();
			memcpy(zs0, zs1, sizeof zs0);
		}
		int BelowB1b2();
		int BelowCompB1b2();

		int Below();
		int BelowComp();

		void InitD(int * o) {
			for (int i = 0; i < 81; i++)
				zs0[i] = o[C_transpose_d[i]];
			bandminlex.Getmin(zs0, &perm_ret);
			ib[0] = perm_ret.i416;  
			bandminlex.Getmin(&zs0[27], &perm_ret);
			ib[1] = perm_ret.i416;  
			bandminlex.Getmin(&zs0[54], &perm_ret);
			ib[2] = perm_ret.i416;  
			RigthOrder();
		}
		void Init(int* o) {	memcpy(zs0, o, sizeof zs0);	}
		void InitPermb1b2(int* o) {
			memcpy(zs0, o, sizeof zs0);
			PermB(0, 1);	MorphToB1First();	}
		void InitPermb3(int* o) {// a;b;c to c;a;b
			memcpy(zs0, o, sizeof zs0);
			PermB(0, 2); PermB(1,2);
			MorphToB1First();
		}
		int Compare0(int* o) {
			for (int i = 0; i < 81; i++) {
				if (o[i] > zs0[i]) return 1;
				if (o[i] < zs0[i]) return -1;
			}
			return 0;
		}
		int Compare(int* o) {
			for (int i = 0; i < 81; i++) {
				if (o[i] > zs1[i]) return 1;
				if (o[i] < zs1[i]) return -1;
			}
			return 0;
		}
		int Compare54(int* o) {
			for (int i = 0; i < 54; i++) {
				if (o[i] > zs1[i]) return 1;
				if (o[i] < zs1[i]) return -1;
			}
			return 0;
		}


		void DumpP1(char* const lib) {
			for (int i = 0; i < 81; i++) cout << zs0[i] + 1;
			cout << lib  << endl;
		}

	}tww,tww2;

	struct TWW1:TWW  {// diagonal morph check
		int QuickCheckDiagMinlex();
		int CheckDiagMore_abc();
		void Dump(char* const lib) {
			for (int i = 0; i < 81; i++) cout << zs0[i] + 1;
			cout << lib <<"\t" << ibx[0] << " " << ibx[1] << " " << ibx[2] << "\t"
				<< ib[0] << " " << ib[1] << " " << ib[2]	 << endl;
		}

	}tww1;

	// __________________________  primary UAs tables and creation of such tables
	uint64_t* ptua2;// pointer to current table cycle search 2/3
	uint32_t   nua2; // nua2 for cycle search 2/3  
	//================== bands 3 and gangster band 3 analysis
	int nband3;
	int   tcolok[2], ncolok;

	int ngua6_7, c1, c2, band, floors, digp, i81;
	uint64_t wua0, ua;// partial gua ua to check
	uint64_t tuacheck[100], tua_for_check[500];
	uint32_t uadigs_for_check[500], nua_for_check, nua_check;

	void InitBand1(int iw);
	void NewBand1(int iw);
	void GoRow4();
	void GoRow5();
	void GoRow6();
	void GoNewBand2();
	void GoBand3();
	void Gor8c2();
	inline void Gor8c3();
	inline void Gor8c4();
	inline void Gor8c5();
	inline void Gor8c6();
	inline void Gor8c7();
	inline void GoCheckSol();
	inline void GoCheckDiagonal();

	void Outcat();

	void Get28Stack1();
	void GoOneOf28();
	void GoOneOf28B();
	void Find_band3B(int m10 = 1);;
	void OutEntry();
	int F3B_See_NED1();// pass p2a   

	//============= loops control for UAs 5;6;7 digits collection (collect more=
	int iband, ibox, iminirow, ibox2, iminirow2, pat1, pat2, ncells;
	int tcells[6], tcols[6];
	int bcols[2][9], mycols[9], myfloors;
	uint64_t mybf;
};
