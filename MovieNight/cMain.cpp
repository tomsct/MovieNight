#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_MENU(MENU_OPEN, cMain::OnMenuOpen)
	EVT_BUTTON(BUTTON_LOAD, OnButtonLoadClicked)
	EVT_BUTTON(BUTTON_SEARCH, OnButtonSearchClicked)
	EVT_LISTBOX(LISTBOX_MOVIES, OnItemSelected)
END_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Main", wxPoint(30, 30),wxSize(800, 600))
{
	// Menu Initalization	
	m_menu_bar = new wxMenuBar;

	m_menu_sort_by = new wxMenu;
	m_menu_sort_by->Append(wxID_ANY, "COSAS");

	this->SetMenuBar(m_menu_bar);
	wxMenu* m_menu_file = new wxMenu;
	m_menu_file->Append(MENU_OPEN, "Open");
	m_menu_bar->Append(m_menu_file, "File");

	m_dir_dialog = new wxDirDialog(this, "Open Folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	// End Initialization

	m_btn_load = new wxButton(this, BUTTON_LOAD, "LOAD", wxPoint(10, 10), wxSize(150, 50));
	m_btn_search = new wxButton(this, BUTTON_SEARCH, "SEARCH", wxPoint(170, 10), wxSize(150, 50));

	m_chkbox_serie = new wxCheckBox(this, CHECKBOX_SERIE, "SERIE", wxPoint(350, 50), wxSize(60, 50));
	m_chkbox_person = new wxCheckBox(this, wxID_ANY, "PERSON", wxPoint(350, 90), wxSize(100, 50));

	m_chkbox_omdb = new wxCheckBox(this, CHECKBOX_SEARCH, "OMDB", wxPoint(350, 10), wxSize(60, 50));
	m_txtbox_search = new wxTextCtrl(this, TEXTBOX_SEARCH, "", wxPoint(10, 70), wxSize(300, 30));

	m_list_movies = new wxListBox(this, LISTBOX_MOVIES, wxPoint(10, 110), wxSize(300, 500));
	m_list_movies->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(cMain::OnRightClickOnListBox), NULL, this);

	m_sbitmap_movie = new wxStaticBitmap(this, MOVIE_IMAGE, wxBitmap(), wxPoint(500, 100));
	
	m_stxt_title = new wxStaticText(this, TEXT_TITLE, "title", wxPoint(500, 50), wxSize(182, 50), wxALIGN_CENTRE_HORIZONTAL);

	m_movies = new std::map<std::string, MOVIE>;

	wxCommandEvent wxEVT_COMMAND_BUTTON_CLICKED;

	OnButtonLoadClicked(wxEVT_COMMAND_BUTTON_CLICKED);
}

cMain::~cMain()
{
	m_movies->clear();
	delete m_movies;
}

void cMain::OnMenuOpen(wxCommandEvent& evt)
{
	if (m_dir_dialog->ShowModal() == wxID_OK)
		m_path = m_dir_dialog->GetPath();
	
	evt.Skip();
	return;
}

void cMain::OnButtonLoadClicked(wxCommandEvent& evt)
{
	m_txtbox_search->Clear();
	m_list_movies->Clear();
	m_movies->clear();
	for (const auto& entry : std::filesystem::directory_iterator(m_path))
	{
		MOVIE movie;
		movie.imgPath = m_path + "/" + entry.path().filename().string() + "/" + entry.path().filename().string() + ".jpg";
		movie.Title = entry.path().filename().string();
		m_movies->insert(std::pair<std::string, MOVIE>(movie.Title, movie));
		m_list_movies->AppendString(entry.path().filename().string());
	}
	SelectItem(0);
	evt.Skip();
}

void cMain::OnButtonSearchClicked(wxCommandEvent& evt)
{	
	m_list_movies->Clear();
	if (m_chkbox_omdb->IsChecked())
	{
		m_movies->clear();

		std::string json = WebService::GetJson( getMoviesQuery + ParseSpaces(m_txtbox_search->GetValue().ToStdString()));

		if (json == "")return;

		rapidjson::Document document = ParseRequest(json);
		
		if (WebService::ValidateJson(document))
		{
			ParseArray(document, m_movies);

			for (auto it = m_movies->begin(); it != m_movies->end(); ++it)
				m_list_movies->AppendString(it->second.Title);
		}
	}
	else
	{
		for (auto it = m_movies->begin(); it != m_movies->end(); ++it)
			if ((*it).second.Title.find(m_txtbox_search->GetValue()) != std::string::npos)
				m_list_movies->AppendString((*it).second.Title);
	}
	evt.Skip();
}

void cMain::OnRightClickOnListBox(wxMouseEvent& evt)
{
	PopupMenu(m_menu_sort_by,wxPoint(evt.GetX(), evt.GetY() + 100));
	evt.Skip();
}

void cMain::OnThreadEnd(wxCommandEvent& evt)
{
	evt.Skip();
}

void cMain::OnItemSelected(wxCommandEvent& evt)
{
	cThread* thread = new cThread(this, evt.GetSelection());
	thread->Create();
	thread->Run();

	evt.Skip();
}

void cMain::SelectItem(unsigned int index)
{
	if (m_list_movies->GetCount() >= index)
	{
		std::string movieTitle = m_list_movies->GetString(index).ToStdString();

		std::string json = WebService::GetJson( getMovieQuery + ParseSpaces(movieTitle));

		if (json == "")return;

		rapidjson::Document movieInfo = ParseRequest(json);

		if (WebService::ValidateJson(movieInfo))
		{
			m_stxt_title->SetLabel(movieInfo["Title"].GetString());

			std::string path(m_movies->at(movieTitle).imgPath);

			if (!std::filesystem::exists(path) || path == "./tmp.jpg")
				if (!WebService::DownloadImage(movieInfo["Poster"].GetString(), path))
					path = "./404notfound.jpg";

			m_sbitmap_movie->SetBitmap(wxImage(path).Rescale(182, 268));
		}
	}
}