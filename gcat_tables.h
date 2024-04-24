#pragma once
//================== compare band morphed and source 
extern void G17BuildSort(int * band, int * tsort);
extern int G17ComparedOrderedBandx(int * zs0, int * band);
extern int G17ComparedOrdered2Bandsx(int * zs0, int * band);

// minlex starts and gangsters minlex processing t416
struct BANDMINLEX{// receive a band send back i416 and morphing data
	int diag;//temp for debugging
	int * band0; //0 based band int band0 [27] in the calling program
	int box_morphed[3][9], box_mapped[3][9],map[9];
	int minirows[9], *bbx, *ccx, *rrx, ccx2[3], ccx3[3];


	struct PERM{
		int i416;
		int rows[3], cols[9], map[9];
		//uint16_t i416;
		//uint8_t rows[3], cols[9], map[9];
		inline void InitBase(int i16 = 0 ){
			i416 = i16;
			for (int i = 0; i < 9; i++)		cols[i] = map[i] = i;
			for (int i = 0; i < 3; i++)		rows[i] = i;
		}
		void Dump() {
			cout << "perm status i416=" <<i416<< endl; 
			cout << "rows " << rows[0] << rows[1] << rows[2] << endl;
			cout << "cols " << cols[0] << cols[1] << cols[2] 
				<<cols[3] << cols[4] << cols[5] << cols[6]
				<< cols[7] << cols[8]  << endl;  
			cout << "digs " << map[0] << map[1] << map[2]
				<<map[3] << map[4] << map[5] << map[6]
				<< map[7] << map[8]   << endl;
		}
	}*pout;
	void MorphBox(int imbox, int ibox, int * rx, int * cx);
	inline void PermCols(int * source, int * dest, int * cc){
		// unchecked dest must have same first 2 digits  as source
		cc[2] = 3;//0+1+2 sum of indexes
		for (int i = 0; i < 2; i++){
			register int c = source[i]; // digit 0_8 to find in the second minirox
			for (int j = 0; j < 3; j++)
				if (c == dest[j]){ cc[i] = j; cc[2] -= j;	break; }
		}
	}
	int CheckR3c49(int *istart_iend);
	void SetPout(int iret);
	int Getmin(int * b0,PERM * pout_user,int diag=0);
	int Getmin6();
	int Getmin6_Switch();
	int Getmin7();
	int Getmin7_Switch();
	int GetAutoMorphs(int ei416, PERM * tpout);
};

const extern char * t416[416];

//==================
extern BANDMINLEX bandminlex;
extern  BANDMINLEX::PERM automorphsp[519];
extern char tblnauto[416];
extern uint16_t tblnautostart[416];
