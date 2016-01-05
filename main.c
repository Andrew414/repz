#include "fcgi_stdio.h"
#include "commondefs.h"

int main()
{
    char * response = malloc(RESPONSE_LEN);
    db_init();

    while (FCGI_Accept() >= 0) {
        char* uri = getenv("REQUEST_URI");
        char* method = getenv("REQUEST_METHOD");

        memset(response, 0, RESPONSE_LEN);
        remove_trailing_slash(uri);

        if (0 == strcmp("/reports", uri))
        {
            int retcode = process_reports_list(uri, method, response, NULL);
            print_response(retcode, response);
            continue;
        }

        if (uri == strstr(uri, "/reports/") && strchragg(uri, '/')==2)
        {
            int retcode = process_reports_id(uri, method, response, NULL);
            if (!retcode)
                print_response(retcode, response);
            else   
                print_not_found(uri);
            continue;
        }

        if (0 == strcmp("/programs", uri))
        {
            int retcode = process_programs_list(uri, method, response, NULL);
            print_response(retcode, response);
            continue;
        }

        if (uri == strstr(uri, "/programs/") && strchragg(uri, '/')==2)
        {
            int retcode = process_programs_name(uri, method, response, NULL);
            print_response(retcode, response);
            continue;
        }

        if (uri == strstr(uri, "/programs/") && strchragg(uri, '/')==3 &&
            (uri + strlen(uri) - strlen("/reports")) == strstr(uri, "/reports"))
        {
            int retcode = process_programs_reports(uri, method, response, NULL);
            print_response(retcode, response);
            continue;
        }

        if (0 == strcmp("/errors", uri))
        {
            int retcode = process_programs_list(uri, method, response, NULL);
            print_response(retcode, response);
            continue;
        }

        if (uri == strstr(uri, "/errors/") && strchragg(uri, '/')==2)
        {
            int retcode = process_programs_name(uri, method, response, NULL);
            print_response(retcode, response);
            continue;
        }

        if (uri == strstr(uri, "/errors/") && strchragg(uri, '/')==3 &&
            (uri + strlen(uri) - strlen("/reports")) == strstr(uri, "/reports"))
        {
            int retcode = process_programs_reports(uri, method, response, NULL);
            print_response(retcode, response);
            continue;
        }

        print_not_found(uri);
    }

    free(response);
    return 0;
}
