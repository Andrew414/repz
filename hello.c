#include "fcgi_stdio.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define RESPONSE_LEN (128*1024*sizeof(char))

int process_reports_list(char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "[{\"id\": \"19582639\",\"program\" : \"UI\",\"error\" : \"7F\",\"info\" : \"KeBugCheckEx\"},"
            "{\"id\" : \"62857028\",\"program\" : \"compiler\",\"error\" : \"7F\",\"info\" : \"kernel_panic\"}]",
            outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }
    if (0 == strcmp(method, "POST"))
    {
        strncpy(outbuffer, "{\"id\" : \"19582639\",\"program\" : \"UI\",\"error\" : \"7F\",\"info\" : \"KeBugCheckEx\"}", outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_reports_id(char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "{\"id\" : \"19582639\",\"program\" : \"UI\",\"error\" : \"7F\",\"info\" : \"KeBugCheckEx\"}", outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

void remove_trailing_slash(char* uri)
{
    if (uri[strlen(uri) - 1] == '/')
        uri[strlen(uri) - 1] = '\0';
}

int main()
{

    int counter = 0;
    char * response = malloc(RESPONSE_LEN);

    while (FCGI_Accept() >= 0) {
        char* uri = getenv("REQUEST_URI");
        char* method = getenv("REQUEST_METHOD");

        remove_trailing_slash(uri);

        if (0 == strcmp("/reports", uri))
        {
            int retcode = process_reports_list(method, response, NULL);
            printf("HTTP/1.1 %d %s\n", retcode == 0 ? 200 : 400, "");
            printf("Date: %s\n", "today");
            printf("Server: %s\n", "Cool Task");
            printf("Content-Length: %d\n", strlen(response));
            printf("Content-Type: %s\n", "application/json");
            printf("\n%s", response);
            continue;
        }

        printf("HTTP/1.1 404 Not Found\r\n"
             "Content-type: text/html\r\n"
             "\r\n"
             "<html>\n"
             "  <head>\n"
             "    <title>Hello, World!</title>\n"
             "  </head>\n"
             "  <body>\n"
             "    <h1>Hello, World!</h1>\n"
             "    current counter = %d""<p>\n"
             "    requested URL = %s""<p>\n"
             "    requested METHOD = %s""\r\n"
             "  </body>\n"
             "</html>\n", 
	++counter,
	uri,
	method);
    }

    free(response);
    return 0;
}
