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

##CAP theorem
#####This service will be AP-service, based on MongoDB. 

Since it's supposed that bugreports will be *automatically* uploaded by some applications, and not by users, there is no much need of the consistensy, from my point of view.

I believe it's enough for uploader to be confident that at some point its report will be processed, maybe a bit later. 
It's not important to get the immediate confirmation that report is processed and saved on all needed machines.

Regarding the availability and partition tolerance - I believe it's more important. 
Unlike the user, the automatic uploader can't wait until the service gets available after some partitial crash. 
So, I think, in case of such crash, the service should accept new reports, maybe making the data not 100% consistent.

I think MongoDB supports such configuration - it continues accepting the ADD requests even being divided into subparts, with consistensy recovered eventually.  
