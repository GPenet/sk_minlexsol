
#include "sk_t.h"

USHORT BF16::CountEtString(char *s) {
	USHORT n = 0;
	for (int i = 0; i < 9; i++) {
		if (On(i))
			s[n++] = (char)(i + '1');
	}
	s[n] = 0;
	return n;
}
char * BF16::String(char * ws, int lettre ) {
	int n = 0;
	for (int i = 0; i < 9; i++) {
		if (On(i))
			ws[n++] = (char)(lettre ? i + 'A' : i + '1');
	}
	ws[n] = 0;
	return ws;
}

int BF32::Table(int * r) {
	if (!f)	return 0;
	int n = 0;
	BitsInTable32(r, n, f, 0);
	return n;
}
int  BF64::SolRow(int col) {
	uint64_t wcol = (uint64_t)Zhoucol64 << col,
		w=bf.u64&wcol;
	if(_popcnt64(w)!=1 )return 0;
	uint32_t res;
	bitscanforward64(res, w);
	return From_128_To_81[res]/9;
}

void  BF128::ClearDiag(int band, int stack) {
	// stack appears here as a band
	int tp[32], ntp=0;
	BitsInTable32(tp, ntp, band);
	for (int i = 0; i < ntp; i++) {
		int cell=tp[i], celld = C_transpose_d[cell + 27 * stack];
		Clear_c(celld);
	}
}
void BF128::ClearRow(int clear, int row) {
	for (int i = 0,bit=1; i < 9; i++,bit<<=1) {
		if(bit&clear)Clear_c(9 * row + i);
	}
}
void BF128::ClearCol(int clear, int col) {
	for (int i = 0, bit = 1; i < 9; i++, bit <<= 1) {
		if (bit&clear)Clear_c(9 * i + col);
	}
}
void BF128::Diag3x27(BF128 & r){
	bf.u64[0] = bf.u64[1] = 0;
	if (r.isEmpty()) return;
	for (int iband = 0; iband < 3; iband++){// build diagonal sym
		int tc[27], ntc=0;
		BitsInTable32(tc, ntc, r.bf.u32[iband], 27 * iband);
		for (int i = 0; i < ntc; i++) {
			int celld = C_transpose_d[tc[i]];
			Set_c(celld);
		}
	}
}

int BF128::Table3X27(int * r) {	
	int n = 0;
	BitsInTable32(r, n, bf.u32[0]);
	BitsInTable32(r, n, bf.u32[1],27);
	BitsInTable32(r, n, bf.u32[2], 54);
	return n;
}
int BF128::Table128(int * r) {
	int n = 0;
	BitsInTable64(r, n, bf.u64[0]);
	BitsInTable64(r, n, bf.u64[1], 64);
	return n;
}
int BF128::Table64_0(int * r) {
	int n = 0;
	BitsInTable64(r, n, bf.u64[0]);
	return n;
}
int BF128::Table64_1(int * r) {
	int n = 0;
	BitsInTable64(r, n, bf.u64[1], 64);
	return n;
}

char * BF128::String3X_Rev(char * ws){
	strcpy(ws, empty_puzzle);
	uint32_t *bfw = bf.u32;
	unsigned int w = bfw[0];
	for (int j = 26; j >= 0; j--) if (w & (1 << j))
		ws[j] = '1';
	w = bfw[1];
	for (int j = 26; j >= 0; j--) if (w & (1 << j))
		ws[j + 27] = '1';
	w = bfw[2];
	for (int j = 26; j >= 0; j--) if (w & (1 << j))
		ws[j + 54] = '1';
	return ws;

}
char * BF128::String3X(char * ws){
	strcpy(ws, empty_puzzle);
	for (int j = 0; j<81; j++) if (On(C_To128[j]))
		ws[j] = '1';
	return ws;
}
char * BF128::String128(char * ws){
	ws[128] = 0;
	for (int j = 0; j<128; j++)
		if (On(j))		ws[j] = '1';		else ws[j] = '.';
	return ws;

}
void BF128::PrintCells() {// assumed not empty checked by caller
	for (int ib = 0; ib < 3; ib++) {// three bands
		uint32_t v = bf.u32[ib];
		if (!v) continue;
		for (int irr = 0; irr < 3; irr++, v >>= 9) {
			int row = v & 0x1ff;
			if (!row)continue;
			cout << " R" << 3 * ib + irr + 1 << "C";
			for (int ic = 0, bit = 1; ic < 9; ic++, bit <<= 1)
				if (row&bit) cout << ic + 1;
		}
	}
	cout << endl;
}

