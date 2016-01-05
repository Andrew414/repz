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
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        get_programs(result);
        strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN); 
        return 0;
    }
    
    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_programs_name(char* url, char* method, char* outbuffer, int* outbufsize)
{
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        if (get_program(strstr(url, "programs/") + strlen("programs/"), result))
        {
            strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN);      
            return 0;
        }
    }
    
    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_programs_reports(char* url, char* method, char* outbuffer, int* outbufsize)
{
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        char* prog = strstr(url + 1, "/");
        char* tail = strstr(prog + 1, "/");
        *tail = 0;
        get_reports(prog + 1, 0, result);
        strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_errors_list(char* url, char* method, char* outbuffer, int* outbufsize)
{
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        get_errors(result);
        strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN); 
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_errors_desc(char* url, char* method, char* outbuffer, int* outbufsize)
{
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        if (get_error(strstr(url, "errors/") + strlen("errors/"), result))
        {
            strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN);      
            return 0;
        }
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}

int process_errors_reports(char* url, char* method, char* outbuffer, int* outbufsize)
{
    char result [RESPONSE_SHR] = {0};
    if (0 == strcmp(method, "GET"))
    {
        char* prog = strstr(url + 1, "/");
        char* tail = strstr(prog + 1, "/");
        *tail = 0;
        get_reports(0, prog + 1, result);
        strncpy(outbuffer, result, outbufsize ? *outbufsize : RESPONSE_LEN);
        return 0;
    }

    strncpy(outbuffer, "{}", outbufsize ? *outbufsize : RESPONSE_LEN);
    return EBADRQC;
}
