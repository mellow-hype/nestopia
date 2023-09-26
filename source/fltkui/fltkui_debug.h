
#ifndef _FLTKUI_DEBUG_H_
#define _FLTKUI_DEBUG_H_

#include <FL/Fl_Text_Display.H>
#include "fltkui_stimer.h"

// #define SPLIT_WIN_W 440

class NstDebugSplitWindow : public SplitWindow {
private:

public:
	NstDebugSplitWindow(int x, int y, int w, int h, const char* t = 0) : SplitWindow(x, y, w, h, t) { }
	virtual ~NstDebugSplitWindow() { }

	void populate();
	void refresh();
	void reset();
	Fl_Text_Display *disp;
	Fl_Text_Buffer *buff;
};


#endif
