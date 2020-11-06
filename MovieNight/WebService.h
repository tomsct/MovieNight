#pragma once

#include <curl/curl.h>
#include <string>
#include <map>
#include "wx/wx.h"
#include "Movie.h"
#include "document.h"

const std::string keyOMDB = "964c100e";
const std::string serverNameOMDB = "www.omdbapi.com";

const std::string keyTMDB = "d4500b18e7ad7dba70a8adc80d8b3d2c";
const std::string serverNameTMDB = "api.tmdb.org";
const std::string serverImageTMDB = "image.tmdb.org";

class WebService
{
public:
	static rapidjson::Document ParseRequest(std::string json);
	static std::string GetJson(std::string movieTitle, bool isArray);
	static void ParseArray(rapidjson::Document, std::map<std::string, movie>* m_movies);
	static long CurlRequest(std::string url, void(*fptr), void* buffer);
	static bool DownloadString(std::string url, std::string& str);
	static bool DownloadImage(std::string url, std::string path);
	static void ShowError(std::string response);
};

