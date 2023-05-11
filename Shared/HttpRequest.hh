#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <thread>

#ifndef EMSCRIPTEN
#include <curl/curl.h>
#else
#include <emscripten.h>
#endif
namespace app
{
    struct HttpHeader
    {
        std::string m_Name;
        std::string m_Value;
    };

    template <typename T>
    void PerformHttpRequest(T OnFinish, std::string const &uri, std::vector<HttpHeader> const &, std::string const &postData = "", bool post = false)
    {
        std::string response;

#ifndef EMSCRIPTEN
        std::cout << "making http request to " << uri << '\n';
        curl_slist *list = nullptr;
        CURL *curl = curl_easy_init();
        assert(curl);
        for (auto i = headers.begin(); i < headers.end(); ++i)
        {
            HttpHeader const &header = *i;
            std::string headerString = header.m_Name + ": " + header.m_Value;
            list = curl_slist_append(list, headerString.c_str());
        }

        if (post)
        {
            assert(curl_easy_setopt(curl, CURLOPT_POST, 1) == CURLE_OK);
            assert(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str()) == CURLE_OK);
        }
        assert(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list) == CURLE_OK);
        assert(curl_easy_setopt(curl, CURLOPT_URL, uri.c_str()) == CURLE_OK);
        assert(curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response) == CURLE_OK);
        assert(curl_easy_setopt(curl, CURLOPT_WRITEDATA, [](char *data, size_t size, size_t nmemb, void *userdata)
                                {
            std::string *response = (std::string *)userdata;
            size_t bytes = size * nmemb;
            response->append(data, bytes);
            return bytes; }) == CURLE_OK);

        assert(curl_easy_perform(curl) == CURLE_OK);
        curl_easy_cleanup(curl);
        curl_slist_free_all(list);
#else
        std::string headersString;
        for (auto i = headers.begin(); i < headers.end(); ++i)
        {
            HttpHeader const &header = *i;
            headersString += header.m_Name + ": " + header.m_Value + '\n';
        }

        if (!headersString.empty() && headersString.back() == '\n')
            headersString.pop_back(); // remove trailing \n
        EM_ASM({
            function ToString(i)
            {
                let string = "";
                while (Module.HEAPU8[i])
                {
                    string += String.fromCharCode(Module.HEAPU8[i]);
                    i++;
                };
                return string;
            }

            const url = ToString($0);
            const headers = ToString($1);
            const postData = ToString($2);
            const post = $4;

            console.log("uploading", postData, "to", url, "with headers", headers);

            var xhr = new XMLHttpRequest();
            xhr.open(post ? "POST" : "GET", url);
            xhr.setRequestHeader("Content-Type", "application/json");
            headers.split('\n').forEach(function(header) {
                var headerParts = header.split(':');
                if (headerParts.length != = 2)
                    throw "how did this happen lol";
                xhr.setRequestHeader(headerParts[0].trim(), headerParts[1].trim());
            });
            xhr.onload = function()
            {
                if (xhr.status == = 200)
                {
                    console.log(url, "success");
                }
                else
                {
                    console.log(url, "failed:", xhr.status);
                }
            };
            xhr.send(postData);
        },
               uri.c_str(), headersString.c_str(), postData.c_str(), post);
#endif

        OnFinish(response);
    }
    bool IsSafeJson(std::string const &json);
}
