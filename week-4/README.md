### Setting up Server
1. Creating a `sockaddr_in`
2. Creating a `socket`
3. Setup `socket` for Server# Implementation of an HTTP Server


### Requirements
* Files are identified by names composed of up to **27** ASCII characters.
* File name characters include alphabet , digits, dash (-) and underscore (_)
* Parse simple HTTP version 1.1 requests
* Utilize **string** functions but NOT **FILE \*** functions
* If a request includes an invalid name, the server must fail the request and respond accordingly
* Need to be able to handle **Malformed** and **Erroneous** requests and respond appropriately
* Request no longer than 4 KiB = 4096 bytes, though the data that folloes it (for a PUT) MAY be longer.
* Similarly, responses will be less than 4 KiB, but data may be much longer
* **All file I/O for user data must be done via read() and write()**
* Max buffer size is **32 KiB** for your program.

### Useful Commands
```
socket, bind, listen, accept, send, recv, open, read, write, close
dprintf(3), sscanf(3)
```
**You may not use any calls for operating on files or network sockets other than those above.**


### Request Methods
```
GET
HEAD // responses are the same as GET, with corret Content-Length, but data is absent
PUT
```

### Status Codes
```
200 OK
201 Created
400 Bad Request
403 Forbidden
404 Not Found -- the case in GET and HEAD requests
500 Internal Server Error
```
A valid GET request may include any data, which includes NUL bytes.


## Run Server
```
./httpserver PORT
```

## Testing
Utilize the curl command to make requests
```
-T, --upload-file <file>
-I, --head
-w, --write-out <format>

curl -s http://localhost:8080/FILENAME
curl -s -T FILENAME http://localhost:8080/FILENAME
curl -s -I http://localhost:8080/FILENAME

Check http code only
curl -o /dev/null -s -w "%{http_code}\n" http://localhost:8080/FILENAME
Check content type
curl -o /dev/null -s -w "%{header_size}\n" http://localhost:8080/FILENAME

```

### Questions
What fraction of your design and code are there to handle errors properly?
How much of your time was spent ensuring that the server behaves 'reasonably'
in the face of errors?


List the 'errors' in a request message that your server must handle.
What response code are you returning for each error?


What happens in your implementation if, during a PUT with a Content-Length,
the connection is closed, ending the communication early?


Does endianess matter for the HTTP protocol? why or why not?


### Store HTTP Message
```
Design - Create some object to keep track of a HTTP messages components


struct httpObject {
    char method[METHOD_MAX_SIZE]
    char filename[FILENAME_MAX_SIZE]
    httpVersion[]
    ssize_t contentLength   // can only be a positive value thus use ssize_t
    int statusCode:         //200 Ok, 404 Not Found
    buffer
}
```






