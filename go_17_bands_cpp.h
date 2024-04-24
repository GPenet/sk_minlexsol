

// standard first band (or unique band)

void STD_B416::Initstd() {
	strcpy(band, "12345678945");
	for (int i = 0; i < 11; i++) band0[i] = band[i] - '1';
	for (int i = 0; i < 27; i++)map[i] = i;// no mapping
	dband = 0;
}
void STD_B416::GetBandTable(int i416e) {
	i416 = i416e;
	strncpy(&band[11], t416[i416e], 16);
	band[27] = 0;
	for (int i = 11; i < 27; i++) band0[i] = band[i] - '1';
}

void STD_B416::InitC10(int i) { // band 1 mode enum
	GetBandTable(i); SetGangster();
}
void STD_B416::SetGangster() {
	memset(gangster, 0, sizeof gangster);
	for (int ir = 0, i = 0; ir < 3; ir++)
		for (int ic = 0; ic < 9; ic++, i++)
			gangster[ic] |= 1 << band0[i];
}

void STD_B416::InitG12(int i) {// band 1 after initstd
	GetBandTable(i); SetGangster();
}

void STD_B416::InitBand2_3(int i16, char * ze, BANDMINLEX::PERM & p
,int iband) {
	i416 = i16;
	dband = 27*iband;
	strncpy(band, ze, 27);
	band[27] = 0;
	for (int i = 0; i < 27; i++) band0[i] = band[i] - '1';
	// create the cell map in output
	for (int i = 0; i < 3; i++) {
		int vr = 9 * p.rows[i], vr0 = 9 * i;
		for (int j = 0; j < 9; j++)
		map[vr0 + j] = vr + p.cols[j];
	}
	SetGangster();
}

void STD_B3::InitBand3(int i16, char* ze, BANDMINLEX::PERM& p) {
	InitBand2_3(i16, ze, p);
	//memset(&guas, 0, sizeof guas);
	memset(&g, 0, sizeof g);
	poutdone=aigskip=0;
	InitTg();// init tguam 
	// setup minirows bit fields
	for (int i = 0; i < 9; i++) {
		minirows_bf[i] = 0;
		int* p = &band0[3 * i];
		for (int j = 0; j < 3; j++)
			minirows_bf[i] |= 1 << p[j];
	}
	//cout << band << " " << oct << minirows_bf[0]
	//	<< " " << minirows_bf[1] << dec << endl;

}

void STD_B416::PrintStatus() {
	cout << "band status i=" << i416 << "\tstart=" << dband << endl << "map ";
	for (int i = 0; i < 27; i++)cout << map[i] << " ";
	cout << endl;
}


