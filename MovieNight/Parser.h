#pragma once

#include <string>
#include <map>
#include "document.h"
#include "Movie.h"

static void ParseArray(rapidjson::Document& json, std::map<std::string, movie>* m_movies)
{
    const rapidjson::Value& attributes = json["Search"];

    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr)
    {
        const rapidjson::Value& attribute = *itr;
        MOVIE movie;
        movie.Title = (*itr)["Title"].GetString();
        movie.imgPath = "./tmp.jpg";
        m_movies->insert(std::pair<std::string, MOVIE>(movie.Title, movie));
    }
}
    
static rapidjson::Document ParseRequest(std::string json)
{
    rapidjson::Document document;
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
