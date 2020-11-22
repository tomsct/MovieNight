#pragma once

#include <string>
#include <map>
#include "document.h"
#include "Movie.h"

static void ParseArray(rapidjson::Document& json, std::map<std::string, Movie>* m_movies)
{
    const rapidjson::Value& attributes = json["Search"];

    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr)
    {
        const rapidjson::Value& attribute = *itr;
        Movie movie;
        movie.SetTitle((*itr)["Title"].GetString());
        movie.SetImgPath("./tmp.jpg");
        m_movies->insert(std::pair<std::string, Movie>(movie.GetTitle(), movie));
    }
}
    
static rapidjson::Document ParseRequest(std::string json)
{
    rapidjson::Document document;

    if (json.empty())
        document.Parse("{}");
    else
        document.Parse(json.c_str());

    return document;
}

static std::string ParseSpaces(std::string str)
{
    if (str.find("(") != -1)
        str.erase(str.find(" ("), str.find(")"));

    std::string space = "%20";

    while (str.find(" ") != -1)
        str.replace(str.find(" "), 1, space);

    return str;
}
