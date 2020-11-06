#include "cApp.h"

wxIMPLEMENT_APP(cApp);
#define ASIO_STANDALONE

bool cApp::OnInit()
{
	wxInitAllImageHandlers();
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}
