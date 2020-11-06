#pragma once

#include <wx/thread.h>
#include <wx/event.h>
#include "cMain.h"

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_CTHREAD, -1)
END_DECLARE_EVENT_TYPES()

class cThread : public wxThread
{
public:
	cThread(wxEvtHandler* evtHandler, unsigned int selectedItem);

private:
	void* Entry();
	unsigned int m_selected_item;

protected:
	wxEvtHandler* m_evtHandler;

};

