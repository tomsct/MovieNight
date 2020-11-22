#include "Movie.h"

std::string Movie::GetTitle() { return this->Title; }
void Movie::SetTitle(std::string title) { this->Title = title; }
std::string Movie::GetImgPath() { return this->imgPath; }
void Movie::SetImgPath(std::string imgPath) { this->imgPath = imgPath; }

Movie::Movie() {}

Movie::Movie(rapidjson::Document& json)
{
	ParseMovie(json);
}

bool Movie::ParseMovie(rapidjson::Document& json)
{
	this->Title = json["Title"].GetString();
	this->Year = json["Year"].GetString();
	this->Runtime = json["Runtime"].GetString();
	this->Genre = json["Genre"].GetString();
	this->Director = json["Director"].GetString();
	this->Actors = json["Actors"].GetString();
	this->Plot = json["Plot"].GetString();
	this->Awards = json["Awards"].GetString();
	this->Poster = json["Poster"].GetString();
	this->imdbRating = json["imdbRating"].GetString();
	this->imdbVotes = json["imdbVotes"].GetString();

	return true;
}