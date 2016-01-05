#include "commondefs.h"

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

int process_programs_list(char* method, char* outbuffer, int* outbufsize)
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

int process_programs_name(char* method, char* outbuffer, int* outbufsize)
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

int process_programs_reports(char* method, char* outbuffer, int* outbufsize)
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

int process_errors_list(char* method, char* outbuffer, int* outbufsize)
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

int process_errors_desc(char* method, char* outbuffer, int* outbufsize)
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

int process_errors_reports(char* method, char* outbuffer, int* outbufsize)
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
