#include <bson.h>
#include <bcon.h>
#include <mongoc.h>

mongoc_client_t      *g_client;
mongoc_database_t    *g_database;
mongoc_collection_t  *g_collection_report,
                     *g_collection_error,
                     *g_collection_program;
bson_t               *g_response,
                     *g_insert,
                     *g_query;
mongoc_cursor_t      *g_select;
bson_error_t          g_error;
char                 *g_str;
bool                  g_retval;

void db_init()
{
    mongoc_init ();
    g_client = mongoc_client_new ("mongodb://localhost:27017");
    g_database = mongoc_client_get_database (g_client, "test");
    g_collection_report  = mongoc_client_get_collection (g_client, "test", "reports");
    g_collection_error   = mongoc_client_get_collection (g_client, "test", "errors");
    g_collection_program = mongoc_client_get_collection (g_client, "test", "programs");
}

void get_reports(char* program, char* error, char* generated)
{
    g_query = bson_new();
    if (program) 
    {
        BSON_APPEND_UTF8 (g_query, "program", program);
    }
    if (error) 
    {
        BSON_APPEND_UTF8 (g_query, "error", error);
    }
    g_select = mongoc_collection_find (g_collection_report, MONGOC_QUERY_NONE, 0, 0, 0, g_query, NULL, NULL);
    
    strcpy(generated, "[     \r\n");
    while (mongoc_cursor_next (g_select, &g_response)) 
    {
        g_str = bson_as_json (g_response, NULL);
        strcat(generated,"\t");
        strcat(generated, g_str);
        strcat(generated,",\r\n");
    }
    generated[strlen(generated) - 3] = '\r';
    generated[strlen(generated) - 2] = '\n';
    generated[strlen(generated) - 1] = ']';
    generated[strlen(generated) - 0] = 0;

    bson_destroy (g_query);
    mongoc_cursor_destroy(g_select);
    bson_free(g_str);
}

int get_report(char* id, char* generated)
{
    g_query = BCON_NEW ("$query", "{", "_id", id, "}"); 
       
    g_select = mongoc_collection_find (g_collection_report, MONGOC_QUERY_NONE, 0, 1 /*one element*/, 0, g_query, NULL, NULL);
    if (mongoc_cursor_next(g_select, &g_response))
    {
        g_str = bson_as_json (g_response, NULL);
        strcpy(generated, g_str);
        bson_destroy (g_query);
        mongoc_cursor_destroy(g_select);
        bson_free(g_str);

        return 1;
    }

    
    strcpy(generated, "{}");

    bson_destroy (g_query);
    mongoc_cursor_destroy(g_select);
    return 0;
}

void add_report(char* program, char* error, char* info, char* generated)
{
    bson_oid_t oid;
    bson_oid_init (&oid, NULL);
    char coid[26] = {0};
    snprintf(coid, 25, "%x%x%x%x%x%x%x%x%x%x%x%x", oid.bytes[0], oid.bytes[1], oid.bytes[2], oid.bytes[3],
        oid.bytes[4], oid.bytes[5], oid.bytes[6], oid.bytes[7],
        oid.bytes[8], oid.bytes[9], oid.bytes[10], oid.bytes[11]);

    g_insert = BCON_NEW ("_id", coid, "program", BCON_UTF8 (program), "error", BCON_UTF8(error), "info", BCON_UTF8(info));
    mongoc_collection_insert (g_collection_report, MONGOC_INSERT_NONE, g_insert, NULL, &g_error);

    g_query = BCON_NEW ("$query", "{", "_id", coid, "}");    
    g_select = mongoc_collection_find (g_collection_report, MONGOC_QUERY_NONE, 0, 1 /*one element*/, 0, g_query, NULL, NULL);
    mongoc_cursor_next(g_select, &g_response);
    g_str = bson_as_json (g_response, NULL);

    strcpy(generated, g_str);

    bson_destroy (g_insert);
    bson_destroy (g_query);
    mongoc_cursor_destroy(g_select);
    bson_free(g_str);
}

void get_programs(char* generated)
{
    g_query = BCON_NEW( "pipeline", "[", 
                            "{",
                                "$group", 
                                    "{",
                                        "_id", "$program", 
                                        "count", 
                                            "{", 
                                                "$sum", BCON_INT32(1), 
                                            "}", 
                                    "}", 
                            "}", 
                        "]" );
    g_select = mongoc_collection_aggregate (g_collection_report, MONGOC_QUERY_NONE, g_query, NULL, NULL);
    
    strcpy(generated, "[    \r\n");
    while (mongoc_cursor_next (g_select, &g_response)) 
    {
        g_str = bson_as_json (g_response, NULL);
        strcat(generated,"\t");
        strcat(generated, g_str);
        strcat(generated,",\r\n");
    }
    generated[strlen(generated) - 3] = '\r';
    generated[strlen(generated) - 2] = '\n';
    generated[strlen(generated) - 1] = ']';
    generated[strlen(generated) - 0] = 0;

    bson_destroy (g_query);
    mongoc_cursor_destroy(g_select);
    bson_free(g_str);
}

void get_errors(char* generated)
{
    g_query = BCON_NEW( "pipeline", "[", 
                            "{",
                                "$group", 
                                    "{",
                                        "_id", "$error", 
                                        "count", 
                                            "{", 
                                                "$sum", BCON_INT32(1), 
                                            "}", 
                                    "}", 
                            "}", 
                        "]" );
    g_select = mongoc_collection_aggregate (g_collection_report, MONGOC_QUERY_NONE, g_query, NULL, NULL);
    
    strcpy(generated, "[    \r\n");
    while (mongoc_cursor_next (g_select, &g_response)) 
    {
        g_str = bson_as_json (g_response, NULL);
        strcat(generated,"\t");
        strcat(generated, g_str);
        strcat(generated,",\r\n");
    }
    generated[strlen(generated) - 3] = '\r';
    generated[strlen(generated) - 2] = '\n';
    generated[strlen(generated) - 1] = ']';
    generated[strlen(generated) - 0] = 0;

    bson_destroy (g_query);
    mongoc_cursor_destroy(g_select);
    bson_free(g_str);
}

int get_program(char* name, char* generated)
{
     g_query = BCON_NEW( "pipeline", "[", 
                            "{",
                                "$group", 
                                    "{",
                                        "_id", "$program", 
                                        "count", 
                                            "{", 
                                                "$sum", BCON_INT32(1), 
                                            "}", 
                                    "}", 
                            "}", 
                        "]" );
    g_select = mongoc_collection_aggregate (g_collection_report, MONGOC_QUERY_NONE, g_query, NULL, NULL);
    
    while (mongoc_cursor_next (g_select, &g_response)) 
    {
        g_str = bson_as_json (g_response, NULL);
        char * found = strstr(g_str, name);
        if (found && *(found-1) == '\"' && *(found+strlen(name)) == '\"')
        {
            strcpy(generated, g_str);
            bson_destroy (g_query);
            mongoc_cursor_destroy(g_select);
            bson_free(g_str);
            return 1;
        }
    }
    strcpy(generated, "{}");
    bson_destroy (g_query);
    mongoc_cursor_destroy(g_select);

    return 0;
}

int get_error(char* name, char* generated)
{
     g_query = BCON_NEW( "pipeline", "[", 
                            "{",
                                "$group", 
                                    "{",
                                        "_id", "$error", 
                                        "count", 
                                            "{", 
                                                "$sum", BCON_INT32(1), 
                                            "}", 
                                    "}", 
                            "}", 
                        "]" );
    g_select = mongoc_collection_aggregate (g_collection_report, MONGOC_QUERY_NONE, g_query, NULL, NULL);
    
    while (mongoc_cursor_next (g_select, &g_response)) 
    {
        g_str = bson_as_json (g_response, NULL);
        char * found = strstr(g_str, name);
        if (found && *(found-1) == '\"' && *(found+strlen(name)) == '\"')
        {
            strcpy(generated, g_str);
            bson_destroy (g_query);
            mongoc_cursor_destroy(g_select);
            bson_free(g_str);
            return 1;
        }
    }
    strcpy(generated, "{}");
    bson_destroy (g_query);
    mongoc_cursor_destroy(g_select);

    return 0;
}
