// notesDisplay.h

#ifndef __NOTESDISPLAY__
#define __NOTESDISPLAY__

struct notesDisplay: public showDisplay
{
	vector<annotations> Notes;

	notesDisplay():showDisplay(){}
	
	notesDisplay(uint _w=WIDTH, uint _h=HEIGHT,\
		            uint _mW=MAIN_WIDTH, uint _mH=MAIN_HEIGTH,\
		            uint _hS=H_SEP_SIZE, uint _vS=V_SEP_SIZE):showDisplay(_w, _h, _mW, _mH, _hS, _vS){}
	
};

#endif
