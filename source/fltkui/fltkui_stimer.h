
#ifndef _FLTKUI_STIMER_H_
#define _FLTKUI_STIMER_H_

#include <FL/Fl_Text_Display.H>

#define SPLIT_WIN_W 400

class NstTimerSplitWindow : public Fl_Window {
private:
	int split_count;

public:
	NstTimerSplitWindow(int x, int y, int w, int h, const char* t = 0) : Fl_Window(x, y, w, h, t) { }
	virtual ~NstTimerSplitWindow() { }

	void populate();
	void refresh();
	void reset();
	Fl_Text_Display *disp;
	Fl_Text_Buffer *buff;
};


#endif
