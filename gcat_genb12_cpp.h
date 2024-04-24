
//====================== gen cat in min lex order
void GEN_BANDES_12::InitBand1(int iw) {
	uint64_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;

	char band[28];	it16 = iw;
	strcpy(band, "12345678945");
	strncpy(&band[11], t416[it16], 16);
	for (int i = 0; i < 27; i++) {
		grid0[i] = band[i] - '1';
		gbit[i] = 1 << grid0[i];
	}
	for (int ic = 0; ic < 9; ic++)
		colband1[ic] = gbit[ic] | gbit[ic + 9] | gbit[ic + 18];
	n_auto_b1 = tblnauto[it16]; //ia 0-415 not index
	t_auto_b1 = &automorphsp[tblnautostart[it16]];
}

void GEN_BANDES_12::NewBand1(int iw) {
	InitBand1( iw);
	GoRow4();
}

#define CELLGO(N,G,R) 		while (gfree[N]) { \
bitscanforward(grid0[N], gfree[N]);gbit[N] = 1 << grid0[N]; \
gfree[N] ^= gbit[N];goto G;}goto R;
inline int CompRow(BANDMINLEX::PERM& p, int* ra, int* rb) {
	for (int i = 0; i < 9; i++) {// morph r5 < R4 ?
		int v = p.map[ra[p.cols[i]]];
		if (v < rb[i])return -1;
		if (v > rb[i])return 1;
	}
	return 0; // equal
}
inline void MorphRow(BANDMINLEX::PERM& p, int* ra, int* rb) {
	for (int i = 0; i < 9; i++)  rb[i] = p.map[ra[p.cols[i]]];
}

void GEN_BANDES_12::GoRow4() {
	grid0[27] = 1; gbit[27] = 2;// digit2 in r4c1
	gfree[28] = 0x1ff ^ (2 | colband1[1]);
r4c2l:	{CELLGO(28, r4c3,endr4	)}
endr4:
	return;

r4c3:b4dmr[0] = gbit[27] | gbit[28];
	 gfree[29] = 0x1ff ^ (b4dmr[0] | colband1[2]);
 r4c3l: {CELLGO(29, r4c4, r4c2l)}

r4c4: b4dmr[0] = gbit[27] | gbit[28] | gbit[29];
	 gfree[30] = 0x1ff ^ (b4dmr[0] | colband1[3]);
r4c4l:	 {CELLGO(30, r4c5,r4c3l)}

r4c5:gfree[31] = 0x1ff ^ (b4dmr[0] | gbit[30]|colband1[4]);
r4c5l:	{CELLGO(31, r4c6,r4c4l)}

r4c6:b5dmr[0] = gbit[30] | gbit[31];
	gfree[32] = 0x1ff ^ (b4dmr[0] | b5dmr[0] |colband1[5]);
r4c6l:	{CELLGO(32, r4c7,r4c5l)}

r4c7:b5dmr[0] = gbit[30] | gbit[31] | gbit[32];
	b4b5dmr[0] = b4dmr[0] | b5dmr[0];
	gfree[33] = 0x1ff ^ (b4b5dmr[0] | colband1[6]);
r4c7l:	{CELLGO(33, r4c8,r4c6l)}

r4c8:gfree[34] = 0x1ff ^ (b4b5dmr[0] | gbit[33] | colband1[7]);
r4c8l:	{CELLGO(34, r4c9,r4c7l)}

r4c9:gfree[35] = 0x1ff ^ (b4b5dmr[0] | gbit[33] | gbit[34] | colband1[8]);
	if (gfree[35]) {
		gbit[35] = gfree[35]; 
		bitscanforward(grid0[35], gfree[35]);// row 4 filled
		if (n_auto_b1) {// check  if row 4 minimal with auto morphs
			n_auto_b1r4 = 0;
			for (int imorph = 0; imorph < n_auto_b1; imorph++) {
				int ir = CompRow(t_auto_b1[imorph], &grid0[27], &grid0[27]);
				if (ir < 0) goto r4c8l;
				if (!ir)  t_auto_b1r4[n_auto_b1r4++] = t_auto_b1[imorph];
			}
		}
		p_cpt2g[4]++;		p_cpt[4] = 0;
		GoRow5();
		if (p_cpt[4]) {
			fout1 << it16 << ";";
			for (int i = 27; i < 36; i++) fout1 << grid0[i] + 1;
			fout1 << ";" << p_cpt2g[5] << " "<< p_cpt[4] << endl;
			//for (int i = 27; i < 36; i++)cout << grid0[i] + 1;
			//cout << "\t" << p_cpt[4] << "\t " << p_cpt2g[5] << endl;
			p_cpt2g[5] += p_cpt[4];

		}
	}
	goto r4c8l;
}
void GEN_BANDES_12::GoRow5() {

	b6dmr[0] = gbit[33] | gbit[34] | gbit[35];
	gfree[36] = 0xff & ~ (b4dmr[0] | colband1[0]);// can not be 9
r5c1l: {CELLGO(36, r5c2, endr5)}
endr5:return;

r5c2:; gfree[37] = 0x1ff ^ (b4dmr[0] | gbit[36] | colband1[1]);
r5c2l: {CELLGO(37, r5c3, r5c1l)}

r5c3:b4dmr[1] = gbit[36] | gbit[37];
	gfree[38] = 0x1ff ^ (b4dmr[0] | b4dmr[1] | colband1[2]);
r5c3l: {CELLGO(38, r5c4, r5c2l)}
//______________________________________________________ box5
r5c4: b4dmr[1] = gbit[36] | gbit[37] | gbit[38];
	b5dkmr[1] = b4dmr[1] | b5dmr[0];
	gfree[39] = 0x1ff ^ (b5dkmr[1] | colband1[3]);
r5c4l: {CELLGO(39, r5c5, r5c3l)}

r5c5:gfree[40] = 0x1ff ^ (b5dkmr[1] | gbit[39] | colband1[4]);
r5c5l: {CELLGO(40, r5c6, r5c4l)}

r5c6:b5dmr[1] = gbit[39] | gbit[40];
	gfree[41] = 0x1ff ^ (b5dkmr[1] | b5dmr[1] | colband1[5]);
r5c6l: {CELLGO(41, r5c7, r5c5l)}
//______________________________________________________ box6
r5c7:b5dmr[1] = gbit[39] | gbit[40] | gbit[41];
	b4b5dmr[1] = b4dmr[1] | b5dmr[1]|b6dmr[0];// row + box known
	gfree[42] = 0x1ff ^ (b4b5dmr[1] | colband1[6]);
r5c7l: {CELLGO(42, r5c8, r5c6l)}

r5c8:gfree[43] = 0x1ff ^ (b4b5dmr[1] | gbit[42] | colband1[7]);
r5c8l: {CELLGO(43, r5c9, r5c7l)}

r5c9:gfree[44] = 0x1ff ^ (b4b5dmr[1] | gbit[42] | gbit[43] | colband1[8]);
	if (gfree[44]) {
		gbit[44] = gfree[44];
		bitscanforward(grid0[44], gfree[44]);// row 5 filled
		//for (int i = 27; i <= 44; i++) cout << grid0[i] + 1;
		//cout << " r4r5 " << endl;
		GoRow6();
	}
	goto r5c8l;
}
void GEN_BANDES_12::GoRow6() {
	// check first if rows 4 5 stay minimal with auto morphs band1
	if (0 && p_cpt2g[4] == 121) {
		for (int i = 27; i < 45; i++)cout << grid0[i] + 1;
		cout << "new 5	"  << endl;
	}
	if (n_auto_b1) {
		n_auto_b1r4r5 = 0;
		for (int imorph = 0; imorph < n_auto_b1; imorph++) {
			BANDMINLEX::PERM& p = t_auto_b1[imorph];
			int ir = CompRow(p, &grid0[36], &grid0[27]);
			if (ir < 0) return;			if (ir) continue;
			// r4 eq r5 morph si if r4morph < r5
			ir = CompRow(p, &grid0[27], &grid0[36]);
			if (ir < 0) return;	 // a lower exists
			if(!ir)t_auto_b1r4r5[n_auto_b1r4r5++] = p;
		}
		for (int imorph = 0; imorph < n_auto_b1r4; imorph++) {
			BANDMINLEX::PERM& p = t_auto_b1r4[imorph];
			int ir = CompRow(p, &grid0[36], &grid0[36]);// r5 =>r5
			if (ir < 0) return;		
			if (!ir)  t_auto_b1r4r5[n_auto_b1r4r5++] = p;			
		}
	}
	b6dmr[1] = gbit[42] | gbit[43] | gbit[44];
	// check free mini rows have  all digits
	r6mfree[0]= 0x1ff ^ (b4dmr[0] | b4dmr[1]);
	r6mfree[1] = 0x1ff ^ (b5dmr[0] | b5dmr[1]);
	r6mfree[2] = 0x1ff ^ (b6dmr[0] | b6dmr[1]);
	if ((r6mfree[0] | r6mfree[1] | r6mfree[2]) != 0x1ff) return;

	gfree[45] = r6mfree[0] & ~colband1[0];
	// can not be below r5c1
	gfree[45] &= ~(gbit[36] - 1);
r6c1l: {CELLGO(45, r6c2, endr6)}
endr6:return;

r6c2:; gfree[46] = r6mfree[0] & ~(colband1[1]| gbit[45]);
r6c2l: {CELLGO(46, r6c3, r6c1l)}

r6c3:gfree[47] = r6mfree[0] & ~(colband1[2] | gbit[45] | gbit[46]);
	if (gfree[47]) {
		bitscanforward(grid0[47],gfree[47]);
		gbit[47] = gfree[47];
	}
	else    goto r6c2l;
	//______________________________________________________ box5 r6c4
	gfree[48] = r6mfree[1] & ~colband1[3];
r6c4l: {CELLGO(48, r6c5, r6c2l)}

r6c5:gfree[49] = r6mfree[1] & ~(colband1[4] | gbit[48]);
r6c5l: {CELLGO(49, r6c6, r6c4l)}

r6c6:gfree[50] = r6mfree[1] & ~(colband1[5] | gbit[48] | gbit[49]);
	if (gfree[50]) {
		bitscanforward(grid0[50], gfree[50]);
		gbit[50] = gfree[50];
	}
	else    goto r6c5l;
	//______________________________________________________ box6 r6c7
	gfree[51] = r6mfree[2] & ~colband1[6];
r6c7l: {CELLGO(51, r6c8, r6c5l)}

r6c8:gfree[52] = r6mfree[2] & ~(colband1[7] | gbit[51]);
r5c8l: {CELLGO(52, r6c9, r6c7l)}

r6c9:gfree[53] = r6mfree[2] & ~(colband1[8] | gbit[51] | gbit[52]);;
	if (gfree[53]) {
		bitscanforward(grid0[53], gfree[53]);// row 5 filled
		gbit[53] = gfree[53];
		GoNewBand2();
	}
	goto r5c8l;
}
void GEN_BANDES_12::GoNewBand2() {
	// build now the gangster band 3
	for (int i = 0, j = 27; i < 9; i++, j++)
		b3colfree[i] = 0x1ff ^ (colband1[i] | gbit[j] | gbit[j + 9] | gbit[j + 18]);
	for (int i = 0, j = 0; i < 3; i++, j += 3)
		if ((b3colfree[j] | b3colfree[j+1] | b3colfree[j+2]) != 0x1ff) return;

	// check if band2 stays minimal with auto morphs band1
	int ir = bandminlex.Getmin(&grid0[27], &pband2, 0);
	if (ir < 0) return; //would be bug  did not come in enumeration
	it16_2 = pband2.i416;
	if (it16_2 < it16) return;// lower band1 
	if (op.b2 < 416 && it16_2 != op.b2) return;
	if (0 &&p_cpt2g[4] == 115) {
		for (int i = 27; i < 54; i++)cout << grid0[i] + 1;
		cout << "new band2 " << it16 << " " << it16_2 << endl;

	}
	n_auto_b1b2 = n_auto_b2b1 = 0;
	if (n_auto_b1) {
		for (int imorph = 0; imorph < n_auto_b1; imorph++) {
			BANDMINLEX::PERM& p = t_auto_b1[imorph];
			int band[27];
			BandReShape(&grid0[27], band, p);
			int ir = BandCompare(band, &grid0[27]);
			if (ir < 0) return;			
			if (!ir)  t_auto_b1b2[n_auto_b1b2++] = p;
		}
	}	
	if (it16 == it16_2) {
		tww.InitAndMorph(grid0, pband2, 1); // init and morph band 1 first
		if (tww.BelowB1b2()) return;
	}
	{ // column 1 must be sorted lexically minimal
		register int v = b3colfree[0];
		bitscanforward(grid0[54], v);
		gbit[54] = 1 << grid0[54];  v ^= gbit[54];
		bitscanforward(grid0[63], v);
		bitscanreverse(grid0[72], v);
		gbit[63] = 1 << grid0[63]; gbit[72] = 1 << grid0[72];
	}
	GoBand3();
}
int GEN_BANDES_12::TWW::BelowB1b2() {
	memcpy(zsa, &zs0[27], sizeof zsa);
	int ir = BelowCompB1b2();
	if (ir<0) return 1;
	if (!ir) genb12.t_auto_b2b1 [ genb12.n_auto_b2b1++]= genb12.pband2;
	for (int imorph = 0; imorph < genb12.n_auto_b1; imorph++) {
		BANDMINLEX::PERM& p = genb12.t_auto_b1[imorph];
		BandReShape(&zs0[27], zsa, p);
		ir = BelowCompB1b2();
		if (ir<0) return 1;
		if (!ir)genb12.t_auto_b2b1[genb12.n_auto_b2b1++] = p;
	}
	return 0;
}
int GEN_BANDES_12::TWW::BelowCompB1b2() {
	int ir = BandCompare(zsa, &genb12.grid0[27]);
	if (ir < 0) return -1; if (ir) return 1;
	return 0;
}



void GEN_BANDES_12::GoBand3() {
	p_cpt2g[6]++;
	if (0 &&p_cpt2g[4]>120) {
		char ws[82];
		memset(ws, '.', 81); ws[81] = 0;
		for (int i = 0; i < 55; i++)ws[i] = grid0[i] + '1';
		ws[63] = grid0[63] + '1';
		ws[72] = grid0[72] + '1';
		cout << ws << " go to band 3" << endl;
		cout << "gangster" << endl;
		int wc[9],v; memcpy(wc, b3colfree, sizeof wc);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				bitscanforward(v, wc[j]);
				wc[j] ^= 1 << v;
				cout << v + 1;
			}
			cout << endl;
		}
	}
	//else return;
	gfree[55] = b3colfree[1] & ~gbit[54];
r7c2l: {CELLGO(55, r7c3, endr7)}
endr7: return;

r7c3:; gfree[56] = b3colfree[2] & ~(gbit[54]|gbit[55]);
r7c3l: {CELLGO(56, r7c4, r7c2l)}


//_________________________________________________ row 7 box8
r7c4:r7dmr[0] = gbit[54] | gbit[55] | gbit[56];
	gfree[57] = b3colfree[3] & ~(r7dmr[0]);
r7c4l: {CELLGO(57, r7c5, r7c3l)}

r7c5: gfree[58] = b3colfree[4] & ~(r7dmr[0] | gbit[57]);
r7c5l: {CELLGO(58, r7c6, r7c4l)}

r7c6: gfree[59] = b3colfree[5] & ~(r7dmr[0] | gbit[57] | gbit[58]);
r7c6l: {CELLGO(59, r7c7, r7c5l)}

// now only 0 or 1 possibility
r7c7:	r7dmr[1] = gbit[57] | gbit[58] | gbit[59];
	{
		register int v = 0x1ff ^ (r7dmr[0] | r7dmr[1]);
		gbit[60] = v & b3colfree[6]; 
		gbit[61] = v & b3colfree[7];
		gbit[62] = v & b3colfree[8];
		if (!gbit[60] || !gbit[61] || !gbit[62]) goto  r7c6l;
	}
	bitscanforward(grid0[60], gbit[60]);
	bitscanforward(grid0[61], gbit[61]);
	bitscanforward(grid0[62], gbit[62]);
	Gor8c2();
	goto r7c6l;
}

#define CELLGOR8A(M,N,G )bitscanforward(grid0[M], v);\
bitscanreverse(grid0[N], v);\
gbit[M] = 1 << grid0[M]; gbit[N] = 1 << grid0[N];G();

#define CELLGOR8B(M,N,G )bitscanforward(grid0[N], v);\
bitscanreverse(grid0[M], v);\
gbit[M] = 1 << grid0[M]; gbit[N] = 1 << grid0[N];G();

#define CELLGOR8(M,N,G )CELLGOR8A(M,N,G )CELLGOR8B(M,N,G )

void GEN_BANDES_12::Gor8c2() {
	if (n_auto_b1b2) {
		for (int imorph = 0; imorph < n_auto_b1b2; imorph++) {
			BANDMINLEX::PERM& p = t_auto_b1b2[imorph];
			int ir = CompRow(p, &grid0[54], &grid0[54]);
			if (ir < 0) return;			
		}
	}
	if (0 &&p_cpt2g[4] == 125) {
		for (int i = 54; i < 63; i++) cout << grid0[i] + 1;
		cout << "new row 7 after b1b2 " << endl;
	}
	if (n_auto_b2b1) {
		int rm[9]; MorphRow(pband2, &grid0[54], rm);
		//for (int i = 0; i < 9; i++) cout << rm[i] + 1;
		//cout << " morphed to pband2" << endl;

		for (int imorph = 0; imorph < n_auto_b2b1; imorph++) {
			BANDMINLEX::PERM& p = t_auto_b2b1[imorph];
			//int rm2[9]; MorphRow(p, rm, rm2);
			//for (int i = 0; i < 9; i++) cout << rm2[i] + 1;
			//cout << " morphed rm2 i="<<imorph << endl;
			int ir = CompRow(p,rm, &grid0[54]);
			if (ir < 0) return;
		}
	}
	if (0 &&p_cpt2g[4] == 125) {
		cout << "new row 7 ok" << endl;
	}
	int v= b3colfree[1] ^ gbit[55];// checked always possible
	CELLGOR8(64,73, Gor8c3)
}
inline void GEN_BANDES_12::Gor8c3() {
	int v= b3colfree[2] ^ gbit[56];
	CELLGOR8(65, 74, Gor8c4)
}
inline void GEN_BANDES_12::Gor8c4() {// also stack1
	{
		BANDMINLEX::PERM perm_ret;
		int gd[27]; // check diagonal
		for (int i = 0; i < 27; i++)gd[i] = grid0[C_transpose_d[i]];
		bandminlex.Getmin(gd, &perm_ret);
		idt16[0] = perm_ret.i416;
		if (idt16[0] < it16) return; //no minimal here

	}


	r8dmr[0] = gbit[63]| gbit[64]| gbit[65];
	r9dmr[0] = gbit[72] | gbit[73] | gbit[74];
	int v = (b3colfree[3] ^ gbit[57]), d1, d2;
	bitscanforward(d1, v); bitscanreverse(d2, v);
	int bit1 = 1 << d1, bit2 = 1 << d2;
	if ((!(bit1 & r8dmr[0]) && !(bit2 & r9dmr[0]))) {
		grid0[66] = d1; grid0[75] = d2;
		gbit[66] = bit1; gbit[75] = bit2;
		Gor8c5();
	}
	if ((!(bit2 & r8dmr[0]) && !(bit1 & r9dmr[0]))) {
		grid0[66] = d2; grid0[75] = d1;
		gbit[66] = bit2; gbit[75] = bit1;
		Gor8c5();
	}

}

inline void GEN_BANDES_12::Gor8c5() {
	//cout << "entry r8c5" << endl;
	int v = b3colfree[4] ^ gbit[58], d1, d2;
	bitscanforward(d1, v); bitscanreverse(d2, v);
	int bit1 = 1 << d1, bit2 = 1 << d2;
	if ((!(bit1 & r8dmr[0]) && !(bit2 & r9dmr[0]))) {
		grid0[67] = d1; grid0[76] = d2;
		gbit[67] = bit1; gbit[76] = bit2;
		Gor8c6();
	}
	if ((!(bit2 & r8dmr[0]) && !(bit1 & r9dmr[0]))) {
		grid0[67] = d2; grid0[76] = d1;
		gbit[67] = bit2; gbit[76] = bit1;
		Gor8c6();
	}
}
inline void GEN_BANDES_12::Gor8c6() {
	int v = b3colfree[5] ^ gbit[59], d1, d2;
	bitscanforward(d1, v); bitscanreverse(d2, v);
	int bit1 = 1 << d1, bit2 = 1 << d2;
	if ((!(bit1 & r8dmr[0]) && !(bit2 & r9dmr[0]))) {
		grid0[68] = d1; grid0[77] = d2;
		gbit[68] = bit1; gbit[77] = bit2;
		Gor8c7();
	}
	if ((!(bit2 & r8dmr[0]) && !(bit1 & r9dmr[0]))) {
		grid0[68] = d2; grid0[77] = d1;
		gbit[68] = bit2; gbit[77] = bit1;
		Gor8c7();
	}
}


inline void GEN_BANDES_12::Gor8c7() {
	// see if box 9 can be filled 
	r8dmr[1] = gbit[66] | gbit[67] | gbit[68];
	r9dmr[1] = gbit[75] | gbit[76] | gbit[77];
	{
		register int v = 0x1ff ^ (r8dmr[0] | r8dmr[1]);
		gbit[69] = v & b3colfree[6];
		gbit[70] = v & b3colfree[7];
		gbit[71] = v & b3colfree[8];
		if (!gbit[69] || !gbit[70] || !gbit[71]) return;
	}
	{
		register int v = 0x1ff ^ (r9dmr[0] | r9dmr[1]);
		gbit[78] = v & b3colfree[6];
		gbit[79] = v & b3colfree[7];
		gbit[80] = v & b3colfree[8];
		if (!gbit[78] || !gbit[79] || !gbit[80]) return;
	}
	{// get and check stack 2
		BANDMINLEX::PERM perm_ret;
		int gd[27]; // check diagonal
		for (int i = 0, j = 27; i < 27; i++, j++)gd[i] = grid0[C_transpose_d[j]];
		bandminlex.Getmin(gd, &perm_ret);
		idt16[1] = perm_ret.i416;
		if (idt16[1] < it16) return; //no minimal here
	}
	{
		// assign 6 last cells
		bitscanforward(grid0[69], gbit[69]);
		bitscanforward(grid0[70], gbit[70]);
		bitscanforward(grid0[71], gbit[71]);
		bitscanforward(grid0[78], gbit[78]);
		bitscanforward(grid0[79], gbit[79]);
		bitscanforward(grid0[80], gbit[80]);

	}

	{// get and check band3 3
		int ir = bandminlex.Getmin(&grid0[54], &pband3);
		if (ir < 0) return; //would be bug  never seen
		it16_3 = pband3.i416;
		//		if (op.bx3 < 416 && (op.bx3 != it16_3)) goto next;
		if (it16_3 < it16) return; //no minimal here
	}
	{// get and check stack 3
		BANDMINLEX::PERM perm_ret;
		int gd[27]; // check diagonal
		for (int i = 0, j = 54; i < 27; i++, j++)gd[i] = grid0[C_transpose_d[j]];
		bandminlex.Getmin(gd, &perm_ret);
		idt16[2] = perm_ret.i416;
		if (idt16[2] < it16) return; //no minimal here
	}
	GoCheckSol();
}

inline void GEN_BANDES_12::GoCheckSol() {
	if (n_auto_b1) {
		for (int imorph = 0; imorph < n_auto_b1; imorph++) {
			BANDMINLEX::PERM& p = t_auto_b1[imorph];
			int band[27];
			BandReShape(&grid0[54], band, p);
			int ir = BandCompare(band, &grid0[27]);
			if (ir < 0) return; if (ir)continue;
			//cout << "equal b3 morph b2 see reverse" << endl;
			// if band2 morph < band3 this is not a min lex
			BandReShape(&grid0[27], band, p);
			ir = BandCompare(band, &grid0[54]);
			if (ir < 0) return;
		}
		if (n_auto_b1b2) {
			for (int imorph = 0; imorph < n_auto_b1b2; imorph++) {
				BANDMINLEX::PERM& p = t_auto_b1b2[imorph];
				int band[27];
				BandReShape(&grid0[54], band, p);
				int ir = BandCompare(band, &grid0[54]);
				if (ir < 0) return;
			}
		}
	}

	if (0 &&p_cpt2g[4] == 69) {
		for (int i = 0; i < 81; i++)cout << grid0[i] + 1;
		cout << " one sol to check "
			<< it16 << " " << it16_2 << " " << it16_3
			<< " " << idt16[0] << " " << idt16[1] << " " << idt16[2] << endl;
		if (0 && p_cpt[4] >= 15) {
			for (int imorph = 0; imorph < n_auto_b1; imorph++) {
				cout << "check morph" << imorph << endl;
				BANDMINLEX::PERM& p = t_auto_b1[imorph];
				int band[27];
				BandReShape(&grid0[27], band, p);
				for (int i = 0; i < 27; i++)cout << band[i] + 1;
				cout << endl;
				//cout << "equal b3 morph b2 see reverse" << endl;
				// if band2 morph < band3 this is not a min lex
				BandReShape(&grid0[54], band, p);
				for (int i = 0; i < 27; i++)cout << band[i] + 1;
				cout << endl;
			}
			/*
*/
			int zd[81];
			BANDMINLEX::PERM perm_ret;
			for (int i = 0; i < 81; i++)	zd[i] = grid0[C_transpose_d[i]];
			bandminlex.Getmin(zd, &perm_ret);
			cout << " stack1 " << perm_ret.i416 << endl;
			bandminlex.Getmin(&zd[27], &perm_ret);
			cout << " stack2 " << perm_ret.i416 << endl;;
			bandminlex.Getmin(&zd[54], &perm_ret);
			cout << " stack2 " << perm_ret.i416 << endl;

		}


	}


	if (n_auto_b2b1) {
		int b3w[27], band[27];//first morph to band 2 min lexical
		BandReShape(&grid0[54], b3w, pband2);
		for (int imorph = 0; imorph < n_auto_b2b1; imorph++) {
			BANDMINLEX::PERM& p = t_auto_b2b1[imorph];
			BandReShape(b3w, band, p);
			int ir = BandCompare(band, &grid0[54]);
			if (ir < 0) return;
		}
	} 
	if (n_auto_b1 && (it16_2 == it16_3)) { //check perm b2 b3
		for (int imorph = 0; imorph < n_auto_b1; imorph++) {
			int band[27];//first morph to band 2 min lexical
			BANDMINLEX::PERM& p = t_auto_b1[imorph];
			BandReShape(&grid0[54], band, p);// could be lower ??
			int ir = BandCompare(band, &grid0[27]);
			if (ir < 0) return; if (ir) continue;
			// now b2 morph agains b3
			BandReShape(&grid0[27], band, p);// could be lower ??
			ir = BandCompare(band, &grid0[54]);
			if (ir < 0) return;
		}
	}
	if (it16 == it16_2) {//  try band 2 first
		tww.InitAndMorph(grid0, pband2, 1); // init and morph band 2 first
		if (tww.Below()) return;
	}

	if (it16 == it16_3) {//  try band 3 first
		tww.InitAndMorph(grid0, pband3, 2); // init and morph band 3 first
		if (tww.Below()) return;
	}
	//cout<< it16 << " look for check diagonal "<< idt16[0]<<" "
	//	<< idt16[1] << " " << idt16[2] << endl;
	if (idt16[0] == it16 || idt16[1] == it16 || idt16[2] == it16)
		GoCheckDiagonal();
	else 	Outcat();
}

inline void GEN_BANDES_12::GoCheckDiagonal() {
	//cout << "check diagonal" << endl;
	int gdiag[81];	// now check diagonal
	for (int i = 0; i < 81; i++)gdiag[i] = grid0[C_transpose_d[i]];
	for (int i = 0; i < 3; i++)	if (idt16[i] == it16) {
		BANDMINLEX::PERM p;
		bandminlex.Getmin(&gdiag[27 * i], &p);
		tww.InitAndMorph(gdiag, p, i); // init and morph band 3 first
		if (tww.Below()) return;
	}
	Outcat();
}

int GEN_BANDES_12::TWW::Below() {
	memcpy(zsa, &zs0[27], sizeof zsa);
	memcpy(zsb, &zs0[54], sizeof zsb);
	if (BelowComp()) return 1;
	for (int imorph = 0; imorph < genb12.n_auto_b1; imorph++) {
		BANDMINLEX::PERM& p = genb12.t_auto_b1[imorph];
		BandReShape(&zs0[27], zsa, p); 
		BandReShape(&zs0[54], zsb, p); 
		if (BelowComp()) return 1;
	}
	return 0;
}
int GEN_BANDES_12::TWW::BelowComp() {
	if (zsa[0] != 1) {
		int temp[27];
		memcpy(temp, zsa, sizeof temp);
		memcpy(zsa, zsb, sizeof temp);
		memcpy(zsb, temp, sizeof temp);
	}
	int ir = BandCompare(zsa, &genb12.grid0[27]);
	if (ir < 0) return 1; if (ir ) return 0;
	ir = BandCompare(zsb, &genb12.grid0[54]);
	if (ir < 0) return 1; 
	return 0;
}

int GEN_BANDES_12::TWW1::QuickCheckDiagMinlex() {
	GEN_BANDES_12& o = genb12;
	for (int i = 0; i < 81; i++)zs0[i] = o.grid0[C_transpose_d[i]];
	memcpy(ibx, o.idt16, sizeof ib);
	RigthOrder();
	if (ibx[0] < o.it16) return 1;	if (ibx[0] > o.it16) return 0;
	// same band 1 push to minimum
	if (ibx[1] < o.it16_2) return 1;	if (ibx[1] > o.it16_2) return 0;
	if (ibx[2] < o.it16_3) return 1;	if (ibx[2] > o.it16_3) return 0;
	// same both ways 
	MorphToB1First();
	return 2;
}
void GEN_BANDES_12::Outcat() {
	p_cpt[4]++;
	if (0 && p_cpt2g[4] ==69) {
		for (int i = 0; i < 81; i++)fout1 << grid0[i] + 1;
		fout1 << "  " << it16_2 << " " << it16_3<<"\t"<< p_cpt2g[4]<<" "<< p_cpt[4]		<< endl;

	}	
	return;
	if (op.out_entry < 0) return;
	for (int i = 0; i < 81; i++)fout1 << grid0[i] + 1;
	fout1 << "  " << it16_2 << " " << it16_3 << "\t" << p_cpt2g[4] << " " << p_cpt[4] << endl;
	
}

int GEN_BANDES_12::TWW1::CheckDiagMore_abc() {
	GEN_BANDES_12& o = genb12;
	// same both ways 3 different Bx
	if (!o.n_auto_b1) return 2;
	for (int i = 0; i < o.n_auto_b1; i++) {
		perm_ret = o.t_auto_b1[i];
		MorphToB1();
		if (Compare(o.grid0) > 0)return 0; // diag smaller
	}
	return 2;
}

//void BandReShape(int* s, int* d, BANDMINLEX::PERM p);
//void BandReOrder(int* d);
