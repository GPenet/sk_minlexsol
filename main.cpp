
#define _CRT_SECURE_NO_DEPRECATE
#include "main.h"
extern uint64_t  p_cpt2g[100];


// catching time as seconds+millis  (seconds since year 1970)
long GetTimeMillis() {
	struct _timeb tbuf;
	_ftime64_s(&tbuf); 
	return ((long)(1000 * tbuf.time) + tbuf.millitm);
}
// builing an appropriate message depending on the elapsed time te-ts
void PrintTime(long ts,long te){	 
	UINT dt=te-ts,dtmil=dt%1000,dts=dt/1000,dth=dts/3600;   dth=dth%1000;
	cerr << endl<<"total elapsed time "; 
    UINT dtm=dts/60; dts=dts%60 ,   dth=dtm/60, dtm=dtm%60;
    if(dth) cerr <<dth<<"h "; 
	if(dth || dtm) cerr <<dtm<<"m "; 
	cerr	<<dts <<"s ";
	if(dtmil<10) cerr << "00"; else  if(dtmil<100) cerr << '0';
	cerr <<dtmil<<"ms "<<endl;   return;
}

void PrintTimeCout(long ts, long te){
	UINT dt = te - ts, dtmil = dt % 1000, dts = dt / 1000, dth = dts / 3600;   dth = dth % 1000;
	cout << endl << "total elapsed time ";
	UINT dtm = dts / 60; dts = dts % 60, dth = dtm / 60, dtm = dtm % 60;
	if (dth) cout << dth << "h ";
	if (dth || dtm) cout << dtm << "m ";
	cout << dts << "s ";
	if (dtmil<10) cout << "00"; else  if (dtmil<100) cout << '0';
	cout << dtmil << "ms " << endl;   return;
}


int Search_ccd(char * ww)
{	// List of 2 char command, 9 commands
	const char * ccd[]={"-i" ,    // input name including extension
				  "-o" ,	//	output or second filename
				  "-c",  // main command option + check boxes
				  "-v" ,  // value   0 to 9 default 0
				  "-b" ,  // bit field 0 to 9 default is 0
				  "-s",  // strings 0 to 9
	};   // puzzle processing specificities
	char wt[4]; 
	strncpy_s(wt,4,ww,2);
	wt[2]=0;
	for(int i=0;i<6;i++)
		if(!strcmp(wt,ccd[i])) 
			return i;
	return -1;
}


SGO sgo;
extern void Go_0();
extern FINPUT finput;
int main(int narg, char *argv[]) {
	cerr << "mainstart" << endl;
	sgo.tdeb=GetTimeMillis();
	char * finput_name=0,*foutput_name=0,* ww;
	char * s_strings[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//optionnal 10 strings

	uint32_t command = 0, 
		vx[13] = { 0, 0, 0, 0, 0, 999, 0, 0, 0, 0,0,999,0 }, //integers 0 to 9 + bxz
		bfx[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };// bit fields 

	for(int i=0;i<narg;i++)	{
		ww = argv[i];
		int ir=Search_ccd(ww);
		if(ir<0) continue;
		if (ir == 3){// -vn-xxxx
			if (ww[3] - '-') continue; //must be -vn-  with n 0_9 b x
			if (ww[2] == 'b')      vx[10] = atoi(&ww[4]);  // JIM  -vb- for TBN
			else if (ww[2] == 'x') vx[11] = atoi(&ww[4]);  // JIM  -vx- for BX3
			else if (ww[2] == 'z') vx[12] = atoi(&ww[4]);  // -vz- for "skip pair c_pt2g[0]
			else {
				int ind = ww[2] - '0';
				if (ind < 0 || ind > 9) continue;
				//sgo.vx64[ind] = _atoi64(&ww[4]);
				sgo.vx64[ind]= strtoll( &ww[4],0,10);

				vx[ind] = atoi(&ww[4]);
			}
			continue;
		}	
		else if (ir == 4){//  -bn- followed by a bit field bits rigth to left max 8 bits
			if (ww[3] - '-') continue; 
			int ind = ww[2] - '0';
			if (ind < 0 || ind>9)continue;
			int length = (int)strlen(&ww[4]);
			if (length > 8)continue; 
			for (int i = 0; i < length; i++) if (ww[4 + i] == '1') bfx[ind] |= (1 << i);
		}
		else if (ir == 5){//  -sn- followed by a string
			if (ww[3] - '-') continue; //must be -vn-  with n 0_9
			int ind = ww[2] - '0';
			if (ind < 0 || ind>9)continue;
			s_strings[ind] = &ww[4];
		}
		else{
			switch (ir)	{
			case 0: finput_name = &ww[2]; 	break;  // -i
			case 1: foutput_name = &ww[2]; 	break;  // -o
			case 2: command = atoi(&ww[2]);	break; //-c
			}// end command  
		}
	}// end loop on options
	if(finput_name) cerr <<" file1 (input) " << finput_name<<endl;
	if(foutput_name) cerr <<" file2 (output) " << foutput_name<<endl;
	cerr << "command " << command<<endl;
	// store command line parameters 
	sgo.command = command;
	sgo.bfx = bfx;
	sgo.finput_name = finput_name;
	sgo.foutput_name = foutput_name;
	sgo.s_strings = s_strings;
	sgo.vx = vx;
	Go_0();
	cerr << " print cout time "  << endl;

	long tfin=GetTimeMillis();
    PrintTimeCout(sgo.tdeb,tfin);
	PrintTime(sgo.tdeb, tfin);
	return (int) p_cpt2g[1];
}

void SGO::ParseInt(char * ze, int  delimiter){
// bfx[0] 1 to 8 parameters
	memset(tparse, 0, sizeof tparse);
	nparse = 0;
	if (!bfx[0]) return;
	//cout << ze << "go parse  delimiter "<<(char) delimiter << endl;
	char * w = ze,temp[20];
	int pos = 0, i = -1;
	while (1){// scan the entry
		++i;
		if (i > 200) break; // safety code
		if (w[i] == delimiter || w[i]==0){
			//cout << &w[i] << " seen param" << endl;
			int n = i - pos; // length of the parameter
			if (n > 15 || n < 1)goto next;
			if (!(bfx[0] & (1 << nparse))) goto next;
			strncpy(temp, &w[pos], n); temp[n] = 0;
			//cout << temp << "parse" << endl;
			tparse[nparse] = atoi_nodot(temp);
		next:
			if (!w[i]) return;
			if (++nparse > 7)return;
			pos = i + 1;
		}
	}
	return;
}
void SGO::Parse_zin() {
	strcpy(zinparsed, finput.ze);
	nitems = 1; items[0] = zinparsed;
	int ll = (int)strlen(zinparsed);
	for (int i = 0; i < ll; i++) {
		if (!zinparsed[i]) return;
		if (zinparsed[i] == ';') {
			items[nitems++] = &zinparsed[i + 1];
			zinparsed[i] = 0;
		}
	}
}

int SGO::atoi_nodot(char * o) {// ignore dot in entry
	//this is to convert serate a.b in integer 10a+b
	int ll = (int)strlen(o), n = 0;
	char zs[10];
	if (ll > 8)ll = 8;
	for (int i = 0; i < ll; i++) if (o[i] - '.') zs[n++] = o[i];
	zs[n] = 0;
	return atoi(zs);
}
int SGO::Canonical_serate(char  * d, char  * o) {// send back aa.b or a.b
	int ctl = 0;
	while (o[0] < '0' || o[0]>'9') {
		o++; // kill leading not digit
		if (++ctl > 3) return 0;
	}

	d[0] = o[0]; d[1] = o[1]; d[2] = o[2];
	if (o[1] == '.') {//a.??
		if (d[2]<'0' || d[2]>'9')d[2] = '0';
		return 3;
	}
	else if (o[2] == '.') {//aa.
		d[3] = o[3];
		if (d[3]<'0' || d[3]>'9')d[3] = '0';
		return 4;
	}
	else {
		if (d[1]<'0' || d[1]>'9') {
			d[1] = '.'; d[2] = '0';
			return 3;
		}
		else {
			d[2] = '.'; d[3] = '0';
			return 4;
		}
	}

}
int SGO::Canonical_EREPED() {
	strcpy(zinparsed, finput.ze);
	strcpy(&zinparsed[81], " ED=");
	int ll = (int)strlen(finput.ze);
	for (int i = 81; i < ll - 9; i++) {// locate first ED=
		if (finput.ze[i] - 'E') continue;
		char * w = &finput.ze[i];
		if (!strncpy(w, "ED=", 3)) return 0;
		w += 3;
		char * wd = &zinparsed[85];
		int ir = Canonical_serate(wd, w);
		if (!ir) return 0; //failed to recognize 
		wd += ir;		*wd++ = '/'; // ER done
		while (w[0] != '/') {
			if (!w[0])return 0;// missing ep ed
			w++;
		}
		w++; //skip /
		ir = Canonical_serate(wd, w);
		if (!ir) return 0; //failed to recognize 
		wd += ir;		*wd++ = '/'; // EP done
		while (w[0] != '/') {
			if (!w[0])return 0;// missing ep ed
			w++;
		}
		w++; //skip /
		ir = Canonical_serate(wd, w);
		if (!ir) return 0; //failed to recognize 
		wd += ir;		*wd = 0; // finished
		return 1; // now zeparsed in canonical form

	}
	return 0; // failed to recognize
}
int SGO::Canonical_401_11() {
	strcpy(zinparsed, finput.ze);
	//	fout1 << zinparsed << "studied" << endl;
	zinparsed[81] = ';';
	int ll = (int)strlen(finput.ze);
	for (int i = 81; i < ll - 9; i++) {// locate first ED=
		if (finput.ze[i] - 'E') continue;
		char * w = &finput.ze[i];
		if (!strncpy(w, "ED=", 3)) return 0;
		w += 3;
		char * wd = &zinparsed[82];
		int ir = Canonical_serate(wd, w);
		if (!ir) return 0; //failed to recognize 
		wd += ir;		*wd++ = ';'; // ER done
		while (w[0] != '/') {
			if (!w[0])return 0;// missing ep ed
			w++;
		}
		w++; //skip /
		ir = Canonical_serate(wd, w);
		if (!ir) return 0; //failed to recognize 
		wd += ir;		*wd++ = ';'; // EP done
		while (w[0] != '/') {
			if (!w[0])return 0;// missing ep ed
			w++;
		}
		w++; //skip /
		ir = Canonical_serate(wd, w);
		if (!ir) return 0; //failed to recognize 
		wd += ir;		*wd = 0; // finished
		return 1; // now zeparsed in canonical form

	}
	return 0; // failed to recognize
}