#include "commondefs.h"
#include <time.h>
#include "fcgi_stdio.h"

int strchragg(char* s, char sym)
{
    int i;
    for (i = 0; s[i]; s[i]==sym ? i++ : *s++);
    return i;
}

void remove_trailing_slash(char* uri)
{
    if (uri[strlen(uri) - 1] == '/' && uri[strlen(uri) - 2] != '/')
        uri[strlen(uri) - 1] = '\0';
}

static char* g_http_codes[] = { "OK", "Method not allowed", "Not found", "" };

char* convert_http_code_to_string(int httpcode)
{
    if (httpcode == 200)
        return g_http_codes[0];
    if (httpcode == 405)
        return g_http_codes[1];
    if (httpcode == 404)
        return g_http_codes[2];
    return g_http_codes[3];
}

int convert_retcode_to_http_code(int retcode)
{
    if (retcode == EBADRQC)
        return 405;
    if (retcode == ENOENT)
        return 404;
    return 200;
}

void print_response(int retcode, char* response)
{
    char date[256] = {0};
    time_t t1;
    struct tm *t2;
    t1 = time(NULL);
    t2 = localtime(&t1);
    strftime(date, sizeof(date), "%F, %T", t2);
    printf("HTTP/1.1 %d %s\n", convert_retcode_to_http_code(retcode), 
        convert_http_code_to_string(convert_retcode_to_http_code(retcode)));
    printf("Date: %s\n", date);
    printf("Server: %s\n", "nginx");
    printf("Content-Length: %d\n", strlen(response) + 1);
    printf("Content-Type: %s\n", "application/json");
    printf("\n%s\n", response);
}

print_not_found(char* uri)
{
    char resp[1024] = {0};
    snprintf(resp, sizeof(resp), "{\"error\" = \"404\", \"url\" = \"%s\"}", uri);
    print_response(ENOENT, resp);
}
