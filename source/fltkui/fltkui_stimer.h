
#ifndef _FLTKUI_STIMER_H_
#define _FLTKUI_STIMER_H_

#include <FL/Fl_Text_Display.H>

class NstTimerSplitWindow : public Fl_Double_Window {
private:
	int split_count;

public:
	NstTimerSplitWindow(int w, int h, const char* t) : Fl_Double_Window(w, h, t) { }
	virtual ~NstTimerSplitWindow() { }

	void populate();
	void refresh();
	Fl_Text_Display *disp;
	Fl_Text_Buffer *buff;
};


#endif
