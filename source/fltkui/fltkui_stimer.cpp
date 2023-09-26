
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Check_Button.H>

#include "vector"
#include "string"
#include "nstcommon.h"
#include "config.h"
#include "fltkui_stimer.h"

extern Emulator emulator;
extern nstpaths_t nstpaths;
extern settings_t conf;

static void cb_autorun_timer(Fl_Widget *w, long) {
	conf.autorun_timer = ((Fl_Check_Button*)w)->value();
}

// Callback to hide the time splits window and resize the main view
static void cb_hide(Fl_Widget *w, long) {
    auto par = w->parent();
	par->hide();
    // resize the parent to remove the space that this window was taking up
	par->parent()->size(
        par->parent()->w() - par->w(),
        par->h()
    );
}

// Callback to clear the text buffer and reset the splits UI
static void cb_clear(Fl_Widget *w, long) {
	((NstTimerSplitWindow*)w->parent())->reset();
}

// Callback to save the splits window text buffer to disk
static void cb_save_splits(Fl_Widget *w, long) {
	char savepath[1024] = {0};
	std::string dt = return_current_date_iso();
	snprintf(savepath, sizeof(savepath), "%snestopia-splits-%s.log", nstpaths.splitlogdir, dt.c_str());
	int res = ((NstTimerSplitWindow*)w->parent())->buff->savefile(savepath);
	fprintf(stderr, "Saved splits to file: %s\n", savepath);
}


void NstTimerSplitWindow::reset() {
	split_count = 0;
	buff->text("");
}

void NstTimerSplitWindow::populate() {
	split_count = 0;
	buff = new Fl_Text_Buffer();
	disp = new Fl_Text_Display(20, 20, w()-25, h()-80, "Splits");
	disp->labelfont(FL_BOLD);
	disp->labelsize(14);
	disp->buffer(buff);

	Fl_Button *btn_save = new Fl_Button(20, this->h()-55, 50, 24, "Save");
	btn_save->callback(cb_save_splits, 0);

	Fl_Button *btn_clear = new Fl_Button((80), this->h()-55, 50, 24, "Clear");
	btn_clear->callback(cb_clear, 0);

	Fl_Button *btn_close = new Fl_Button(140, this->h()-55, 50, 24, "Hide");
	btn_close->callback(cb_hide, 0);

	Fl_Check_Button *chk_autorun = new Fl_Check_Button(disp->w()-80, h()-55, 75, 25, "Auto-restart");
	chk_autorun->value(conf.autorun_timer);
	chk_autorun->callback(cb_autorun_timer);


	this->end();
}

void NstTimerSplitWindow::refresh() {
	const char* basefmt = "[%s] Split %4d:\t%s\n";
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
		std::string dt = return_current_time();
		snprintf(line, sizeof(line), basefmt, dt.c_str(), split_count, timestring.c_str());

		// update the text buffer
		buff->append(line);

		// we remove the entry from the vec after we've rendered
		splits->pop_back();
        disp->redraw();
	}
}