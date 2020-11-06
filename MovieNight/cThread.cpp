#include "cThread.h"

DEFINE_EVENT_TYPE(wxEVT_CTHREAD)

cThread::cThread(wxEvtHandler* evtHandler, unsigned int selectedItem) : wxThread(wxTHREAD_DETACHED), m_evtHandler(evtHandler)
{
	m_selected_item = selectedItem;
}

void* cThread::Entry()
{
	wxCommandEvent evt(wxEVT_CTHREAD, GetId());

	((cMain*)m_evtHandler)->SelectItem(m_selected_item);
	wxPostEvent(m_evtHandler, evt);

	return 0;
}