#include "commondefs.h"
#include "fcgi_stdio.h"

#include <bson.h>
#include <bcon.h>
#include <mongoc.h>

char* parse(char* paramname, char* params)
{
    return strstr(params, paramname) + strlen(paramname)+1;
}

void split_params(char* params)
{
    for (; *params; params++)
        if (*params == '&')
            *params = 0;
}

int process_reports_list(char* url, char* method, char* outbuffer, int* outbufsize)
{
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        get_reports(0, 0, result);
        strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }
    if (0 == strcmp(method, "POST"))
    {
        char* program = 0;
        char* error   = 0;
        char* info    = 0;
        
        gets(result);
        program = parse("program", result);
        error   = parse("error",   result);
        info    = parse("info",    result);
        split_params(result);
        add_report(program, error, info, result);
        strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_reports_id(char* url, char* method, char* outbuffer, int* outbufsize)
{
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        if (get_report(strstr(url, "reports/") + strlen("reports/"), result))
        {
            strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN);      
            return 0;
        }
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_programs_list(char* url, char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "[{\"name\" : \"compiler\",\"errcount\" : \"5\",\"repcount\" : \"6\"},{\"name\" : \"UI\",\"errcount\" : \"3\",\"repcount\" : \"2\"}]",
            outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }
    
    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_programs_name(char* url, char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "{\"name\" : \"UI\",\"errcount\" : \"3\",\"repcount\" : \"2\"}",
            outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }
    
    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_programs_reports(char* url, char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "[{\"id\" : \"62857028\",\"program\" : \"compiler\",\"error\" : \"7F\",\"info\" : \"kernel_panic\"}]",
            outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_errors_list(char* url, char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "[{\"code\" : \"7F\",\"count\" : \"7\"},{\"code\" : \"DF\",\"count\" : \"3\"},{\"code\" : \"C0\",\"count\" : \"2\"}]",
            outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_errors_desc(char* url, char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "{\"code\" : \"7F\",\"count\" : \"7\"}",
            outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_errors_reports(char* url, char* method, char* outbuffer, int* outbufsize)
{
    if (0 == strcmp(method, "GET"))
    {
        strncpy(outbuffer, "[{\"id\" : \"62857038\",\"program\" : \"compiler\",\"error\" : \"7F\",\"info\" : \"kernel_panic\"}]",
            outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}
