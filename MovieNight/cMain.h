#pragma once
#include "wx/wx.h"
#include "Constants.h"
#include "Movie.h"
#include "WebService.h"
#include "cThread.h"
#include "Queries.h"
#include <filesystem>	
#include <algorithm>
#include <map>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	void SelectItem(unsigned int index);

private:
	std::string m_path = "./Movies";
	std::map<std::string , Movie>* m_movies = nullptr;

private:
	wxMenuBar* m_menu_bar = nullptr;

	wxMenu* m_menu_sort_by = nullptr;

	wxDirDialog* m_dir_dialog = nullptr;

	wxButton* m_btn_load = nullptr;
	wxButton* m_btn_search = nullptr;

	wxRadioButton* m_rd_btn_serie = nullptr;
	wxRadioButton* m_rd_btn_person = nullptr;

	wxRadioButton* m_rd_btn_omdb = nullptr;
	wxTextCtrl* m_txtbox_search = nullptr;

	wxListBox* m_list_movies = nullptr;

	wxStaticBitmap* m_sbitmap_movie = nullptr;

	wxStaticText* m_stxt_title = nullptr;

	void OnMenuOpen(wxCommandEvent& evt);
	void OnButtonLoadClicked(wxCommandEvent& evt);
	void OnButtonSearchClicked(wxCommandEvent& evt);
	void OnRightClickOnListBox(wxMouseEvent& evt);
	void OnItemSelected(wxCommandEvent& evt);
	void OnThreadEnd(wxCommandEvent& evt);
	void OnCheckBoxClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

