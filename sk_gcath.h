#define stack1_54 07007007007007007
struct OPCOMMAND {// decoding command line option for this rpocess
	// processing options 
	int opcode;
	int  bx3;// 
	int out_entry; //output of the entry file for test DLL .bfx[2] & 2
	// bfx[2] & 8 special use b2_is as limit b3
	int b1;//band 1 in process 
	int b2;//bands b2  forced
	int ton;//test on and test level
	int searchrank;
	void SetUp(int opcod, int k = 0, int print = 1) {// init known or not
		memset(this, 0, sizeof * this);
		opcode = opcod;
		bx3 = sgo.vx[11];
		b1 = sgo.vx[0];
		ton = sgo.vx[1];
		if (sgo.bfx[2] & 2) out_entry = 1;
		if (print) {
			cout << "standard processing commands_______________" << endl;
			cout << sgo.vx[0] << " b1  -v0- band 0_415" << endl;
			if (out_entry)  cout << " file1 contains attached solution grids" << endl;
			cout << "debugging commands___________________" << endl;
			if (b2)		cout << b2 << " b2 -v5- filter band 2 index" << endl;
			if (bx3 < 416)		cout << bx3 << " b3 index" << endl;

			if (ton)cout << ton << "  test on  -v1- verbose mode " << endl;
		}
	}
}op;



//____ entry builder
void BandReShape(int* s, int* d, BANDMINLEX::PERM p);
void BandReOrder(int* d);
struct GEN_BANDES_12 {// encapsulating global data 
	int modeb12, go_back, diagmore, diagbug, 
		it16, it16_2, it16_3;
	int idt16[3];// diagonal
	int irtw2,iret_diag;
	char zsol[82], rband2[28];
	int grid0[81],gbit[81],gfree[81],colband1[9],
		grid1[81], gw[81], tc[6], ntc;
	int zsa[27], zsb[27], zsmin[81];

//	uint64_t   nb12;
	BANDMINLEX::PERM *t_auto_b1, * t_auto_p1,// maxi is 107
		t_auto_b1b2[108], t_auto_b2b1[108], t_auto_b1r4[108], t_auto_b1r4r5[108],
		pband2, pband3;
	int n_auto_b1, n_auto_p1, n_auto_b1b2, n_auto_b2b1,
		n_auto_b1r4, n_auto_b1r4r5;
	int b4dmr[3], b5dmr[3], b6dmr[3], r7dmr[2], r8dmr[2], r9dmr[2],
		b4b5dmr[3], b7b8dmr[3];
	int b5dkmr[3], r6mfree[3], b3colfree[9],b9free[3],r8free[9];
	//_________________ gangster 
	int gangcols[9];// 9 bits fields band3 for each colum (see valid band2)
	int gangb12[9]; // digit bf bands 12 per column
	//____________________________ find link solution rank
	uint64_t s_rank, s_rank_r4, s_r4start,s_vr4;
	int s_band, s_minir4, s_r4_index;
	int s_row4[9], s_grid0[81];

	void BuildVr4() {
		s_vr4 = grid0[27]+1;
		for (int i = 28; i < 36; i++) {
			s_vr4=10*s_vr4+ grid0[i]+1;
		}
	}
	struct TWW {
		int zs0[81], zs0b[81], zsa[27],zsb[27], zs1[81], ib[3], *zco;
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
			int temp[27];
			memcpy(temp, &zs0[27 * i1], sizeof temp);
			memcpy(&zs0[27 * i1], &zs0[27 * i2], sizeof temp);
			memcpy(&zs0[27 * i2], temp, sizeof temp);
		}
		void RigthOrder() {
			if (ib[1] < ib[0])PermB(  0, 1);
			if (ib[2] < ib[0])PermB(  0, 2);
			if (ib[2] < ib[1])PermB(  1, 2);
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
		void InitAndMorph( int first) {
			if (first <= 0) return;
			if (first >2) return;
			memcpy(zs0b, zs0, sizeof zs0);
			int temp[27];
			memcpy(temp, &zs0b[27 * first], sizeof temp);
			memcpy(&zs0b[27 * first], zs0, sizeof temp);
			memcpy(zs0b, temp, sizeof temp);
			bandminlex.Getmin(zs0b, &perm_ret);
			BandReShape(zs0b, zs1, perm_ret);
			BandReShape(&zs0b[27], &zs1[27], perm_ret);
			BandReShape(&zs0b[54], &zs1[54], perm_ret);
			if (zs1[27] != 1) {// put band 2 band 3 in the right order
				memcpy(temp, &zs1[27 ], sizeof temp);
				memcpy(&zs1[27],&zs1[54], sizeof temp);
				memcpy(&zs1[54], temp, sizeof temp);
			}
		}

		int BelowB1b2();
		int BelowCompB1b2();

		int Below();
		int BelowComp();

		void InitCom() {
			bandminlex.Getmin(zs0, &perm_ret);
			ib[0] = perm_ret.i416;
			bandminlex.Getmin(&zs0[27], &perm_ret);
			ib[1] = perm_ret.i416;
			bandminlex.Getmin(&zs0[54], &perm_ret);
			ib[2] = perm_ret.i416;
			RigthOrder();
			MorphToB1First();
		}
		void InitD(int * o) {
			for (int i = 0; i < 81; i++)
				zs0[i] = o[C_transpose_d[i]];
			InitCom();
		}
		void Init(int* o) {	memcpy(zs0, o, sizeof zs0);
		InitCom();
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


		void DumpP1(const char*  lib) {
			cout << "ib " << ib[0] << " " << ib[1] << " " << ib[2] << endl;
			for (int i = 0; i < 81; i++) cout << zs0[i] + 1;
			cout << lib  << endl;
		}

	}tww,tww2,tww3;



	void InitBand1(int iw);
	void InitRow4FromI10375(int i10375);
	void NewBand1(int iw);
	void GoRow4();
	void GoRow4From(int itr4);

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
	//===============  
	int FindSolForRank();
	int GetBandIndex();
	void GoSolForRank();
	int FindRankForSolMin();
	void GoSolForSearchRank();
	// start with not minlex
	int ZminCompare54(int* o);
	void CompUpdateZmin();
	void ZminSeeMorphs( int * o);
	void SeeNewMorph(int* o);
	void GoSolForSearchRankFromNotMinSol(char * ze);



};
