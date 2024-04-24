/*In line small functions to put bits in table
 in many cases,  the bit fields have a small number of bits set to 1
 in the program it appeared easier to first create the table of such bits index 
 the bitscan family of intrinsic instructions is a good way to do this

 here below some small inline functions to do it
 The calling program parameters are
 int * t the pointer to the  index table
 int & nt the number of index already occupied (0 at the start)
 value the value 32 bits or 64 bits ot scan

 v0 is the relative index for the first bit in the value
    eg: v0 shoul be set to 27 if value is the second band 
	for a bitfields of 81 cells split in 3 bands

 */

inline void BitsInTable64(int * t, int & nt, uint64_t v, int v0=0) {
	register uint64_t R = v;
	uint32_t register res, R0 = v0;
	while (R) {
		bitscanforward64(res, R);
		t[nt++] = res + R0;
		register uint64_t bit = 1; bit <<= res;
		R ^= bit;
	}
}
inline void BitsInTable32(int * t, int & nt, uint32_t v, int v0=0) {
	register uint32_t R = v, res, R0 = v0;
	while (R) {
		bitscanforward(res, R);
		t[nt++] = res + R0;
		R ^= 1 << res;
	}
}
inline void BitsInTable64Reverse(int * t, int & nt, uint64_t v, int v0 = 0) {
	register uint64_t R = v;
	uint32_t register res, R0 = v0;
	while (R) {
		bitscanreverse64(res, R);
		t[nt++] = res + R0;
		register uint64_t bit = 1; bit <<= res;
		R ^= bit;
	}
}
inline void BitsInTable32Reverse(int * t, int & nt, uint32_t v, int v0 = 0) {
	register uint32_t R = v, res, R0 = v0;
	while (R) {
		bitscanreverse(res, R);
		t[nt++] = res + R0;
		R ^= 1 << res;
	}
}


/* that file contains classes managing bit fields in the program and a specific class,
BF_CONVERT doing specific operations on bit fields to improve the overall performance.

The specific classes are
================================= basic bit fields
BF8 a bit field of size 8 to handle exotic patterns
BF16 a bit field of size 16 bits mainly used as a 9 bits field.
BF32 a bit field of size 32 bits used  as a27 bit field for regions
BF64 a bit field of size 64 bits  
BF128 a bit field of size 128 bits used  to work with 128 bits registers
      mostly used as 3x32   bit fields for a sudoku 81 bits field
RBF27 9 BF32, one per digit for the 27 sets per region/unit
PM3X is done of 9 BF128, one per digit
==============

===============obsoletes

BFCAND a bit field sized to a maximum of 320 bits but worked at the used dimension
that bit field is used to describe candidates properties.
the bit entry corresponds to the index in the table of candidates

BFSETS a bit field of 324 bits one bit per set
a set can be a cell (bits 0 80) of a (digit,region) (9 * 27 )
mainly used to build rank 0 logic, storing sets and link sets

*/

struct BF8 {
	UCHAR f;//bitfield
	inline void operator =(BF8 & e) {f = e.f;}
	inline void operator =(UCHAR fe) {f = fe;}
	
 	inline int On(int ch) const {return ((f & (1 << ch)));	}		
	inline int Off(int ch) const {	return (!(f & (1 << ch)));	}	
	inline void Set(USHORT ch) {f |= (1 << ch);	}	
	inline void Clear(USHORT ch) {	f &= ~(1 << ch);}
	inline BF8 operator &(BF8 & e) const {BF8 w;w.f = f & e.f;	return w;	}
	inline BF8 operator |(BF8 & e) {BF8 w;	w.f = f | e.f;	return w;}
	inline BF8 operator ^(BF8 & e) {BF8 w;	w.f = f ^ e.f;	return w;}
	inline BF8 operator -(BF8 & e) {BF8 w;	w.f = f ^ (e.f & f);return w;	}
	inline int  operator ==(BF8 & e) {return(e.f == f);	}
	inline void operator &=(BF8 & e) {f &= e.f;	}
	inline void operator |=(BF8 & e) {f |= e.f;	}
	inline void operator ^=(BF8 & e) {f ^= e.f;	}
	inline void operator -=(BF8 & e) {f ^= (f & e.f);	}
	inline void operator &=(UCHAR fe) {f &= fe;	}
	inline void operator |=(UCHAR fe) {f |= fe;	}
	inline void operator ^=(UCHAR fe) {f ^= fe;	}
	inline void operator -=(UCHAR fe) {f ^= (f & fe);	}
	inline unsigned int Count() {return _popcnt32((unsigned int)f);	}

}; // BF8

// a 9 bitfield to give position of candidate in a house and similar functions
struct BF16 {
	USHORT f;
	// constructors
	BF16() { f = 0; }
	BF16(int i1) { f = 1 << i1; }
	BF16(int i1, int i2) { f = (1 << i1) | (1 << i2); }
	BF16(int i1, int i2, int i3) { f = (1 << i1) | (1 << i2) | (1 << i3); }
	BF16(int i1, int i2, int i3, int i4) { f = (1 << i1) | (1 << i2) | (1 << i3) | (1 << i4); }
	BF16(int i1, int i2, int i3, int i4, int i5) { f = (1 << i1) | (1 << i2) | (1 << i3) | (1 << i4) | (1 << i5); }

	inline void SetAll_0() { f = 0; }
	inline void SetAll_1() { f = 0x1ff; }
	inline int isEmpty() const { return (!f); }
	inline int isNotEmpty() const { return f; }
	inline int On(int ch) const { return ((f & (1 << ch))); }
	inline int Off(int ch) const { return (!(f & (1 << ch))); }
	inline void Set(USHORT ch) { f |= (1 << ch); }
	inline void Clear(USHORT ch) { f &= ~(1 << ch); }
	inline BF16 operator &(BF16 & e) const { BF16 w;	w.f = f & e.f;	return w; }
	inline BF16 operator |(BF16 & e) const { BF16 w;	w.f = f | e.f;	return w; }
	inline BF16 operator ^(BF16 & e) const { BF16 w;	w.f = f ^ e.f;	return w; }
	inline BF16 operator -(BF16 & e) { BF16 w;	w.f = f ^ (e.f & f);	return w; }
	inline int  operator ==(BF16 & e) { return(e.f == f); }
	inline void operator &=(BF16 & e) { f &= e.f; }
	inline void operator |=(BF16 & e) { f |= e.f; }
	inline void operator ^=(BF16 & e) { f ^= e.f; }
	inline void operator -=(BF16 & e) { f ^= (f & e.f); }
	inline int paire() { return (_popcnt32(f) == 2); }

	USHORT CountEtString(char *s);
	char * String(char * ws, int lettre = 0);

}; // BF16
/* BIT32 is used mainly in that program as a 27 region bit field
describing some binary properties fo these regions
*/
struct BF32 {
	UINT f;   // bitfield
	BF32() { f = 0; }
	inline int On(int unit) { return ((f & (1 << unit))); }
	inline int Off(int unit) { return (!(f & (1 << unit))); }
	inline void Set(USHORT unit) { f |= (1 << unit); }
	inline void Clear(USHORT unit) { f &= ~(1 << unit); }
	inline void Inv(USHORT unit) { f ^= (1 << unit); }
	inline BF32 operator -(BF32 & e) {
		BF32 w;	w.f = f ^ (e.f & f); return w;
	}
	inline void operator -=(BF32 & e) { f ^= (f & e.f); }
	int Table (int * r); 
};

struct BF64 {
	GINT64 bf;
	inline void clear() { bf.u64 = 0; }
	inline void SetAll_0() { bf.u64 = 0; }
	inline void SetAll_1() { bf.u64 = BIT_SET_64; };

	inline BF64 operator| (const uint64_t &r) const { BF64 w; w.bf.u64 = bf.u64 | r; return w; }
	inline BF64 operator| (const BF64 &r) const { BF64 w; w.bf.u64 = bf.u64 | r.bf.u64; return w; }
	inline void operator|= (const uint64_t &r) { bf.u64 |= r; }
	inline void operator|= (const BF64 &r) { bf.u64 |= r.bf.u64; }

	//inline BF64 operator& (const uint64_t &r) const { BF64 w; w.bf.u64 = bf.u64 & r; return w; }
	inline BF64 operator& (const BF64& r) const { BF64 w; w.bf.u64 = bf.u64 & r.bf.u64; return w; }
	inline void operator&= (const uint64_t &r) { bf.u64 &= r; }
	inline void operator&= (const BF64& r) { bf.u64 &= r.bf.u64; }

	inline BF64 operator^ (const uint64_t &r) const { BF64 w; w.bf.u64 = bf.u64 ^ r; return w; }
	inline BF64 operator^ (const BF64& r) const { BF64 w; w.bf.u64 = bf.u64 ^ r.bf.u64; return w; }
	inline void operator^= (const uint64_t &r) { bf.u64 ^= r; }
	inline void operator^= (const BF64& r) { bf.u64 ^= r.bf.u64; };

	inline BF64 operator- (const uint64_t &r) const { BF64 w; w.bf.u64 = bf.u64 & ~r; return w; }
	inline BF64 operator- (const BF64 &r) const { BF64 w; w.bf.u64 = bf.u64 &~r.bf.u64; return w; }
	inline void operator-= (const uint64_t &r) { bf.u64 &= ~r; }
	inline void operator-= (const BF64& r) { bf.u64 &= ~r.bf.u64; };

	inline void operator= (const uint64_t &rhs) { bf.u64 = rhs; }

	inline bool operator== (const BF64& r) const { return (bf.u64 == r.bf.u64); }
	inline bool operator!= (const BF64 &r) const { return (bf.u64 != r.bf.u64); };
	inline void operator<<= (const int bits) { bf.u64 <<= bits; };
	inline void operator>>= (const int bits) { bf.u64 >>= bits; };

	inline int On(const int theBit) const { return  ( (uint64_t)bf.u64>>theBit) & 1; }
	inline int Off(const int theBit) const { return  ( ((uint64_t)bf.u64 >> theBit) & 1)^1; }
	inline void Set(const int theBit) { bf.u64|= (uint64_t)1<<theBit; }
	inline void SetToBit(const int theBit) { bf.u64 = (uint64_t)1 << theBit; }
	inline void Clear(const int theBit) { bf.u64 &= ~ ((uint64_t)1 << theBit); }

	inline uint64_t isNotEmpty() const { return bf.u64; }
	inline bool isEmpty() const { return (!bf.u64); }
	inline int Count() { return (int)_popcnt64(bf.u64); }
	uint64_t Convert_to_54(){ uint64_t w = bf.u32[1]; w <<= 27; w |= bf.u32[0]; return w; }// 2x27 to 54
	inline int getFirstCell() const {
		uint32_t res;
		if (bf.u32[0]) {
			bitscanforward(res, bf.u32[0]);
			return res;
		}
		if (bf.u32[1]) {
			bitscanforward(res, bf.u32[1]);
			return 27 + res;
		}
		return -1;
	}
	int SolRow(int col);// in a solution per digit find the row
};
class BF128 {
public:
	T128 bf;
	BF128() {}
	BF128(const BF128 &v) { bf.u128 = v.bf.u128; }
	BF128(const __m128i &v) { bf.u128 = v; }
	BF128(const T128 &v) { bf.u128 = v.u128; }

	inline void clear() { bf.u64[0] = bf.u64[1] = 0; }
	inline void SetAll_0() { bf.u64[0] = bf.u64[1] = 0; };
	inline void SetAll_1() { bf.u64[0] = bf.u64[1] = BIT_SET_64; };

	inline BF128 operator| (const BF128 &r) const { BF128 w; w.bf.u128 = _mm_or_si128(bf.u128, r.bf.u128); return w; }
	inline BF128 operator| (const __m128i r) const { BF128 w; w.bf.u128 = _mm_or_si128(bf.u128, r); return w; }
	inline void operator|= (const BF128& r) { bf.u128 = _mm_or_si128(bf.u128, r.bf.u128); }
	inline void operator|= (const __m128i r) { bf.u128 = _mm_or_si128(bf.u128, r); }

	inline BF128 operator& (const BF128 &r) const { BF128 w; w.bf.u128 = _mm_and_si128(bf.u128, r.bf.u128); return w; };
	inline BF128 operator& (const __m128i r) const { BF128 w; w.bf.u128 = _mm_and_si128(bf.u128, r); return w; }
	inline void operator&= (const BF128& r) { bf.u128 = _mm_and_si128(bf.u128, r.bf.u128); }
	inline void operator&= (const __m128i r) { bf.u128 = _mm_and_si128(bf.u128, r); }

	inline BF128 operator^ (const BF128 &r) const { BF128 w; w.bf.u128 = _mm_xor_si128(bf.u128, r.bf.u128); return w; }
	inline BF128 operator^ (const __m128i r) const { BF128 w; w.bf.u128 = _mm_xor_si128(bf.u128, r); return w; }
	inline void operator^= (const BF128& r) { bf.u128 = _mm_xor_si128(bf.u128, r.bf.u128); }
	inline void operator^= (const __m128i r) { bf.u128 = _mm_xor_si128(bf.u128, r); };

	inline BF128 operator- (const BF128 &r) const { BF128 w; w.bf.u128 = _mm_andnot_si128(r.bf.u128, bf.u128); return w; }
	inline BF128 operator- (const __m128i r) const { BF128 w; w.bf.u128 = _mm_andnot_si128(r, bf.u128); return w; }
	inline void operator-= (const BF128& r) { bf.u128 = _mm_andnot_si128(r.bf.u128, bf.u128); }
	inline void clearBits(const BF128& r) { bf.u128 = _mm_andnot_si128(r.bf.u128, bf.u128); }
	inline void operator-= (const __m128i r) { bf.u128 = _mm_andnot_si128(r, bf.u128); };

	inline void operator= (const BF128 &r) { bf.u128 = r.bf.u128; }
	inline void operator= (const void *p) { bf.u128 = _mm_loadu_si128((const __m128i*)p); }

	inline bool operator== (const BF128& r) const { return(bf.u64[0] == r.bf.u64[0] && bf.u64[1] == r.bf.u64[1]); }
	inline bool operator!= (const BF128 &r) const { return(bf.u64[0] != r.bf.u64[0] || bf.u64[1] != r.bf.u64[1]); };
	inline void MaskToBit(const int theBit) {
		register int R = theBit;		if (R >= 128)SetAll_1();
		else if (R <= 0)SetAll_0();
		else if (R < 64) {
			bf.u64[0] = 0;
			bf.u64[0] = ((uint64_t)1 << R) - 1;
		}
		else {
			bf.u64[0] = 1;
			bf.u64[0] = ((uint64_t)1 << (R - 64)) - 1;
		}
	}
	inline void Mask(const int theBit) { BF128 w; w.MaskToBit(theBit); *this &= w; }

#ifndef _MSC_VER
	inline void Set(const int theBit) {
		if (theBit < 64) {
			bf.u64[0] |= (uint64_t)1 << theBit;
		}
		else {
			bf.u64[1] |= (uint64_t)1 << (theBit - 64);
		}
	}
	inline void SetToBit(const int theBit) { 
		if (theBit < 64) {
			bf.u64[1] = (uint64_t)0;
			bf.u64[0]=(uint64_t) 1<< theBit;
		}
		else {
			bf.u64[0] = (uint64_t)0;
			bf.u64[1] = (uint64_t)1 << (theBit-64);
		}
	}
	inline int On(const int theBit) const { 
		if (theBit<64)	return  ((uint64_t)bf.u64[0] >> theBit) & 1;
		else return  ((uint64_t)bf.u64[1] >> (theBit-64)) & 1;
	}

	inline void Clear(const int theBit) {
		if (theBit < 64) {
			bf.u64[0] &= ~((uint64_t)1 << theBit)	;
		}
		else {
			bf.u64[1] &=~( (uint64_t)1 << (theBit - 64));
		}
	}
#else
	inline void Set(const int theBit) { _bittestandset64((long long*)&bf.u64[0], theBit); }
	inline void SetToBit(const int theBit) { clear(); _bittestandset64((long long*)&bf.u64[0], theBit); }
	inline unsigned char On(const int theBit) const { return  _bittest64((long long*)&bf.u64[0], theBit); }
	inline void Clear(const int theBit) { _bittestandreset64((long long*)&bf.u64[0], theBit); }
#endif


	inline int Off(const int theBit) const { return !On(theBit); }
	inline int isBitSet(const int theBit) const { return !On(theBit); }// double definition to clear
	inline void setBit(const int theBit) { Set(theBit); }// double definition to clear
	inline void clearBit(const int theBit) { Clear(theBit); }// double definition to clear

	//  code to use in a 3 bands pattern calling using a cell 0-80
	inline int On_c(const int cell) const { return On(C_To128[cell]); }
	inline int Off_c(const int cell) const { return Off(C_To128[cell]); }
	inline void Set_c(const int cell) { Set(C_To128[cell]); }
	inline void Clear_c(const int cell) { Clear(C_To128[cell]); }
	inline void SetDiagX(const int theBit){		Set_c(C_transpose_d[From_128_To_81[theBit]]);	}
	void ClearDiag(int clear, int stack);
	void ClearRow(int clear, int row);
	void ClearCol(int clear, int col);

	inline bool isZero() const { return bf.u64[0] == 0 && bf.u64[1] == 0; }
	inline bool isEmpty() const { return bf.u64[0]==0 && bf.u64[1] == 0; }
	inline bool isNotEmpty() const { return bf.u64[0] != 0 || bf.u64[1] != 0; }

	inline int Count(){ return (int)(_popcnt64(bf.u64[0]) + _popcnt64(bf.u64[1])); }
	inline int Count96(){ return (int)(_popcnt64(bf.u64[0]) + _popcnt32(bf.u32[2])); }

	inline int isSubsetOf(const BF128 &s) const { return  _mm_testc_si128(s.bf.u128, bf.u128); }
	inline int isDisjoint(const BF128& r) const { return _mm_test_all_zeros(r.bf.u128, bf.u128); }
	inline int Disjoint(const BF128& r) const { return _mm_test_all_zeros(r.bf.u128, bf.u128); }
	inline int SupersetOf(const BF128 &s) const { return  _mm_testc_si128(bf.u128, s.bf.u128); }

	inline int SupersetOf81(const BF128 &s) const { BF128 w = s; w.Mask(81); return  SupersetOf(w); }
	inline int SupersetOf96(const BF128 &s) const { BF128 w = s; w.Mask(96); return  SupersetOf(w); }
	inline bool operator< (const BF128 &rhs) const {
		if (bf.u64[1] < rhs.bf.u64[1]) return true;
		if (bf.u64[1] > rhs.bf.u64[1]) return false;
		return bf.u64[0] < rhs.bf.u64[0];
	}
	inline int Compare(const BF128 &r) const {
		if (*this == r) return 0;
		if (bf.u64[1] == r.bf.u64[1]){
			if (bf.u64[0] < r.bf.u64[0]) return -1;
			else return 1;
		}
		if (bf.u64[1] < r.bf.u64[1]) return -1;
		else return 1;
	}

	inline void Convert3X27to81(const BF128 & rhs){
		register uint64_t R0 = rhs.bf.u32[0],
			R1 = rhs.bf.u32[1],
			R2 = rhs.bf.u32[2];
		R1 <<= 27; R0 |= R1;
		R1 = R2; R1 <<= 54;
		bf.u64[0] = R0 | R1;
		bf.u64[1] = R2 >> 10;
	}
	inline void Convert81to3X27(const T128 & rhs){
		register uint64_t R0 = rhs.u64[0],
			R1 = rhs.u64[1];
		bf.u32[0] = R0 & BIT_SET_27;
		R0 >>= 27;
		bf.u32[1] = R0 & BIT_SET_27;
		R0 >>= 27;
		R1 <<= 10;
		R0 |= R1;
		bf.u32[2] = R0 & BIT_SET_27;
		bf.u32[3] = 0;
	}
	
	inline int mask8() const { return _mm_movemask_epi8(bf.u128); }
	inline int getFirst96() const {
		uint32_t res;
		if (bf.u64[0]) {
			bitscanforward64(res, bf.u64[0]);
			return res;
		}
		if (bf.u32[2]) {
			bitscanforward(res, bf.u32[2]);
			return 64 + res;
		}
		return -1;
	}
	inline int getLastCell() const {
		uint32_t res;
		if (bf.u32[2]) {
			bitscanreverse(res, bf.u32[2]);
			return 54 + res;
		}
		if (bf.u32[1]) {
			bitscanreverse(res, bf.u32[1]);
			return 27 + res;
		}
		if (bf.u32[0]) {
			bitscanreverse(res, bf.u32[0]);
			return res;
		}
		return -1;
	}
	inline int getFirst128() const {
		uint32_t res;
		if (bf.u64[0]) {
			bitscanforward64(res, bf.u64[0]);
			return res;
		}
		if (bf.u64[1]) {
			bitscanforward64(res, bf.u64[1]);
			return res+64;
		}
		return -1;
	}
	inline int getFirstCell() const {
		uint32_t res;
		if (bf.u32[0]) {
			bitscanforward(res, bf.u32[0]);
			return res;
		}
		if (bf.u32[1]) {
			bitscanforward(res, bf.u32[1]);
			return 27 + res;
		}
		if (bf.u32[2]) {
			bitscanforward(res, bf.u32[2]);
			return 54 + res;
		}
		return -1;
	}
	inline int getLast128() const {
		uint32_t res;
		if (bf.u64[1]) {
			bitscanreverse64(res, bf.u64[1]);
			return res + 64;
		}
		if (bf.u64[0]) {
			bitscanreverse64(res, bf.u64[0]);
			return res;
		}
		return -1;
	}
	void Diag3x27(BF128 & r);
	inline void Store(USHORT * tstore){ memcpy(tstore, this, 16); }
	inline void Re_Load(USHORT * tstore){ memcpy(this, tstore, 16); }

	int Table3X27(int * r);// cell 0_80 as output
	int Table128(int * r);// cell 0_127 as output
	int Table64_0(int * r);//  0_63 as output
	int Table64_1(int * r);//  64_127 as output


	char * String3X(char * ws);
	char * String3X_Rev(char * ws);
	char * String128(char * ws);
	void PrintCells();
	void Print(const char * lib) {
		cout << "BF128 status for " << lib << endl;
		uint64_t *w = bf.u64, id = 0;
		for (int i = 0; i < 2; i++, id += 64, w++)
			if (*w)cout << Char64out(*w) << " " << id << endl;

	}
	void Print3(const char * lib) {
		cout << "BF128 3x27 status for " << lib << endl;
		for (int i = 0; i < 3; i++)
			cout << Char27out(bf.u32[i])  << endl;
	}
};


/* BFSETS, is a bitfield used to account sets and link sets
in the rank 0 logic construction
*/

class BFSETS {
	BF128 ff[3];
public:
	void SetAll_0() {
		ff[0].clear();
		ff[1].clear();
		ff[2].clear();
	}
	inline int On(int v) const {
		return (ff[v >> 7].On(v & 127));
	}
	inline int Off(int v) const {
		return (On(v) == 0);
	}
	inline void SetCell(int v) {
		ff[0].setBit(v);
	}
	inline void SetRegion(int d, int el) {
		int v = 96 + (d << 5) + el;
		ff[v >> 7].setBit(v & 127);
	}

	UINT GetSetsDigit(USHORT d){ int dd = d + 3, ffi = dd>2, ffv = dd & 3;	return ff[ffi].bf.u32[4]; }
	inline bool IsEmpty() const
	{
		return (ff[0].isZero() && ff[1].isZero() && ff[2].isZero());
	}
	int Count() const;
	USHORT String(USHORT *r) const;
	char * XsudoPrint(int mode, char * output);
};

struct BF_FIX{ // tables used in BF processing
	USHORT tp3[3][2];	// relative pairs in exocet 3 digits
	USHORT tp6[6][2];   // relative pairs in exocet 4 digits
	UCHAR texset[8];   // mask defining a solution in an exocet
	USHORT texset4[4][2], texset5[8][2], texset6[16][2];
};
