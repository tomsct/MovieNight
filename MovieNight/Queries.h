#pragma once
#include <string>

const std::string keyOMDB = "964c100e";
const std::string serverNameOMDB = "www.omdbapi.com";

const std::string keyTMDB = "d4500b18e7ad7dba70a8adc80d8b3d2c";
const std::string serverNameTMDB = "api.tmdb.org";
const std::string serverImageTMDB = "image.tmdb.org";

const std::string getMovieQuery = serverNameOMDB + "/?apikey=" + keyOMDB + "&type=movie" + "&t=";
const std::string getMoviesQuery = serverNameOMDB + "/?apikey=" + keyOMDB + "&type=movie" + "&s=";

const std::string getPersonQuery = serverNameTMDB + "/3/search/person?api_key=" + keyTMDB + "&query=";
const std::string getPersonImage = serverImageTMDB + "/t/p/original";

const std::string getPersonFilmography = serverNameTMDB + "/3/person/";