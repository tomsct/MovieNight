#pragma once
#include <string>

typedef	struct movie
{
	std::string Title;
	std::string	Year;
	std::string Released;
	std::string Runtime;
	std::string Genre;
	std::string Director;
	std::string Writer;
	std::string Actors;
	std::string Plot;
	std::string Language;
	std::string Country;
	std::string Awards;
	std::string Poster;
	std::string imdbRating;
	std::string imdbVotes;
	std::string Type;
	std::string Production;
	std::string imgPath;
}MOVIE;

static void ParseTittle(std::string* str)
{
	if(str->find("(") != -1)
		str->erase(str->find(" ("), str->find(")"));

	std::string space = "%20";

	while (str->find(" ") != -1)
		str->replace(str->find(" "), 1, space);
}