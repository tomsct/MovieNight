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

rapidjson::Document WebService::ParseRequest(std::string json)
{
    rapidjson::Document document;
    document.Parse(json.c_str());

    return document;
}

std::string WebService::GetJson(std::string movieTitle, bool isArray)
{
    std::string query = serverNameOMDB + "/?apikey=" + keyOMDB;

    ParseTittle(&movieTitle);

    if (isArray)
        query += "&s=" + movieTitle;
    else
        query += "&t=" + movieTitle;

    std::string json;

    if (!WebService::DownloadString(query, json))
        return "";

    return json;
}

void WebService::ParseArray(rapidjson::Document json, std::map<std::string, movie>* m_movies)
{
    if (!strcmp(json["Response"].GetString(), "False"))
    {
        ShowError(json["Error"].GetString());
        return;
    }

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

void WebService::ShowError(std::string response)
{
    wxMessageBox(response);
}
