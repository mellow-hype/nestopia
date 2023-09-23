
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include "vector"
#include "string"
#include "nstcommon.h"
#include "fltkui_stimer.h"

extern Emulator emulator;

static void cb_ok(Fl_Widget *w, long) {
	w->parent()->hide();
}

void NstTimerSplitWindow::populate() {
	split_count = 0;
	buff = new Fl_Text_Buffer();
	disp = new Fl_Text_Display(20, 20, 400-40, 400-60, "Splits");
	disp->buffer(buff);

	Fl_Button *btn_close = new Fl_Button(350, 370, 40, 24, "&Close");
	btn_close->callback(cb_ok, 0);

	this->end();
}

void NstTimerSplitWindow::refresh() {
	const char* basefmt = "Split %d: %s\n";
	char line[100] = {0};

	// get splits from the emulator
	std::vector<time_ms>* splits = emulator.timer.getSplits();

	// create the full text buf with the splits info; because we pop the
	// split from the splits vector, we use a size > 0 as a signal to know
	// when a new split was created.
	if (splits->size() > 0) {
		split_count++;

		// fetch the last split
        std::string timestring = emulator.timer.lastSplitString();
		snprintf(line, sizeof(line), basefmt, split_count, timestring.c_str());

		// update the text buffer
		buff->append(line);
		disp->redraw();

		// we remove the entry from the vec after we've rendered
		splits->pop_back();
	}
}