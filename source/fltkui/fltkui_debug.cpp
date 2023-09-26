
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include "vector"
#include "string"
#include "nstcommon.h"
#include "fltkui_debug.h"

extern Emulator emulator;
extern nstpaths_t nstpaths;


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


void NstDebugSplitWindow::reset() {
	buff->text("");
}

void NstDebugSplitWindow::populate() {
	buff = new Fl_Text_Buffer();
	disp = new Fl_Text_Display(20, 20, w()-25, h()-80, "Debug");
	disp->textfont(FL_COURIER);
	disp->labelfont(FL_BOLD);
	disp->labelsize(14);
	disp->buffer(buff);

	Fl_Button *btn_close = new Fl_Button(disp->w()-30, this->h()-55, 50, 24, "Hide");
	btn_close->callback(cb_hide, 0);

	this->end();
}

void NstDebugSplitWindow::refresh() {
	buff->text("Registers:\n=====================\n");
	buff->append(emulator.DumpRegs().c_str());
	buff->append("\nStack:\n=====================\n");
	buff->append(emulator.DumpStack().c_str());
	disp->redraw();
}