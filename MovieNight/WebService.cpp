#include "WebService.h"

static size_t WriteFileCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t written = fwrite(contents, size, nmemb, (FILE*)userp);
    return written;
}

static size_t WriteStringCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

long WebService::CurlRequest(std::string url, void(*fptr), void* buffer)
{
    CURL* curl;
    CURLcode curl_code;
    long http_response_code = 0;

    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fptr);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);

        curl_code = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_response_code);

        curl_easy_cleanup(curl);
    }

    return http_response_code;
}

bool WebService::DownloadString(std::string url, std::string& str)
{
    return CurlRequest(url, WriteStringCallback, &str) == 200;
}

bool WebService::DownloadImage(std::string url, std::string path)
{
    FILE* file;
    errno_t error = fopen_s(&file, path.c_str(), "wb");
    if (error == 0)
    {
        long response = CurlRequest(url, WriteFileCallback, file);
        fclose(file);
        if (response != 200)
        {
            remove(path.c_str());
            return false;
        }
        return true;
    }
    return false;
}

std::string WebService::GetJson(std::string query)
{
    std::string json;

    if (!WebService::DownloadString(query, json))
        return "";

    return json;
}

bool WebService::ValidateJson(rapidjson::Document& json)
{
    if (json == "{}")
    {
        ShowError("Empy Json");
        return false;
    }
    else if (json.HasMember("Response") && !strcmp(json["Response"].GetString(), "False"))
    {
        ShowError(json["Error"].GetString());
        return false;
    }
    else if (json.HasMember("total_results") && json["total_results"].GetInt() == 0)
    {
        ShowError("Person not found");
        return false;
    }
    return true;
}

void WebService::ShowError(std::string response)
{
    wxMessageBox(response);
}
