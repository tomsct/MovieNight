#pragma once

#include <curl/curl.h>
#include "wx/wx.h"
#include "Parser.h"

class WebService
{
public:
	static std::string GetJson(std::string movieTitle);
	static long CurlRequest(std::string url, void(*fptr), void* buffer);
	static bool DownloadString(std::string url, std::string& str);
	static bool DownloadImage(std::string url, std::string path);
	static void ShowError(std::string response);
	static bool ValidateJson(rapidjson::Document& json);
};

