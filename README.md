# Report Viewer
#### web programming task (web service)

This service is the simple "bugtracker". Its API allows:

- uploading bugreports (technically, bug is the pair of *program* and *error code* plus some additional not used *info*);

- viewing bugreports;

- viewing stats for the programs;

- viewing stats for the error codes;

See usage examples for more information.

##API

###Examples or requests and responses
####1. `/reports/`
```
GET    - returns LIST_OF_REPORTS
POST   - receives the following parameters: 
             program 
             error
             info, 
         returns new created REPORT
PUT    - invalid
DELETE - invalid
```

####2. `/reports/id`
```
GET    - returns REPORT 
POST   - invalid
PUT    - invalid
DELETE - invalid (will be implemented only if I have time
                 in this case will return HTTP status code)
```

####3. `/programs/`
```
GET    - returns global LIST_OF_PROGRAMS 
POST   - invalid
PUT    - invalid
DELETE - invalid
```

####4. `/programs/<name>/`
```
GET    - returns PROGRAM_INFO 
POST   - invalid
PUT    - invalid
DELETE - invalid
```

####5. `/programs/<name>/errors/`
```
GET    - returns LIST_OF_ERRORS, found in the particular program 
POST   - invalid
PUT    - invalid
DELETE - invalid
```

####6. `/errors/`
```
GET    - returns global LIST_OF_ERRORS 
POST   - invalid
PUT    - invalid
DELETE - invalid
```

####7. `/errors/<error>/`
```
GET    - returns ERROR_DESCRIPTION 
POST   - invalid
PUT    - invalid
DELETE - invalid
```

####8. `/errors/<error>/programs/`
```
GET    - returns LIST_OF_PROGRAMS, that have the particular error 
POST   - invalid
PUT    - invalid
DELETE - invalid
```

For invalid requests, errors **405** and **404** will be returned.

- 405 for valid URLs and invalid methods

- 404 for invalid URLs

###Examples of the response types (JSON)
####1. `REPORT`
```
{
    "id" : "19582639",
    "program" : "UI",
    "error" : "7F",
    "info" : "KeBugCheckEx"
}
```
####2. `LIST_OF_REPORTS`
Represents the JSON list of `REPORT` objects:
```
[
    {
        "id" : "19582639",
        "program" : "UI",
        "error" : "7F",
        "info" : "KeBugCheckEx"
    },
    {
        "id" : "62857028",
        "program" : "compiler",
        "error" : "7F",
        "info" : "kernel_panic"
    }
]
```
####3. `PROGRAM_INFO`
```
{
    "name" : "UI",
    "errcount" : "3"
}
```
####4. `LIST_OF_PROGRAMS`
Represents the JSON list of `PROGRAM_INFO` objects:
```
[
    {
        "name" : "compiler",
        "errcount" : "5"
    },
    {
        "name" : "UI",
        "errcount" : "3"
    }
]
```
####5. `ERROR_DESCRIPTION`
```
{
    "code" : "7F",
    "count" : "7"
}
```
####4. `LIST_OF_ERRORS`
Represents the JSON list of `ERROR_DESCRIPTION` objects:
```
[
    {
        "code" : "7F",
        "count" : "7"
    },
    {
        "code" : "DF",
        "count" : "3"
    },
    {
        "code" : "C0",
        "count" : "2"
    }
]
```

