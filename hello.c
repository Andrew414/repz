#include "fcgi_stdio.h"
#include <stdlib.h>

int main() {

    int counter = 0;

    while (FCGI_Accept() >= 0) {
        char* uri = getenv("REQUEST_URI");
        char* method = getenv("REQUEST_METHOD");

        printf("Content-type: text/html\r\n"
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

    return 0;
}
