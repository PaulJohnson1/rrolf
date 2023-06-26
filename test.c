#include <curl/curl.h>
#include <assert.h>

int main()
{
    CURL *curl = curl_easy_init();
    assert(!curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8081"));
    assert(!curl_easy_setopt(curl, CURLOPT_PUT, 1));
    assert(!curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "testing"));
    assert(!curl_easy_setopt(curl, CURLOPT_VERBOSE, 1));
    puts("1");
    assert(!curl_easy_perform(curl));
    puts("2");

    int64_t response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    printf("response_code %ld\n", response_code);

    curl_easy_cleanup(curl);
}
