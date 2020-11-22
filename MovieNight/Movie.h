#pragma once
#include <string>
#include<document.h>

class Movie
{
private:
	std::string Title;
	std::string	Year;
	std::string Runtime;
	std::string Genre;
	std::string Director;
	std::string Actors;
	std::string Plot;
	std::string Awards;
	std::string Poster;
	std::string imdbRating;
	std::string imdbVotes;
	std::string imgPath;

private:
	bool ParseMovie(rapidjson::Document& json);

public:
	std::string GetTitle();
	void SetTitle(std::string  title);
	std::string GetImgPath();
	void SetImgPath(std::string imgPath);

	Movie();
	Movie(rapidjson::Document& json);
};

