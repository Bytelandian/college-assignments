
## Client Server Services

### Introduction

We need to build a system where any machine which is connected to a network can offer certain services to local or remote machine. The services should be published on a well known port, and use a standard interface. The standard interface here means the programming API which the clients of such a service should use to call the service. The service can be invoked synchronously or asynchronously. Here, synchronous invocation means that a client invoking this service blocks until the server completes the service request and returns results to client. Asynchronous invocation of service means that the client can submit the service request using one function and keep checking (polling) the status of service completion via a different function, and finally obtain the results in yet another function call.

### Services Offered :
#### Server Side:

There are 3 services which the server can serve :
1. Multiply two matrices. [To multiply 2 matrices]
2. Scale Image. [To scale two Images]
3. Delay service .	[To make the server sleep for some time]

#### Client Side:
These services are made to demonstrate the Asynchronous request by the client to the server.
1. Add two big Numbers.
2. Subtract two big Numbers.
3. Multiply two big Numbers.
4. Divide two big Numbers.
5. Factorial of a Number.

#### Synchronous services:
These services are made such that the client gives the input and wait till the server completes the request . It can not perform any other task in the time server responds to the request.

#### Asynchronous services:
These services are made such that the client gives the input and then can perform other activities in the time server processes the request. The client can choose to perform a check whether the server had completed the request by invoking the server to check if request have been completed or choose a client side service to perform .The server when invoked tell if the request have been completed or not. If the request have not been completed , then the server responds by telling that the request have not been completed, then the client can perform other activities or again check if the server has processed the request. If the request have been completed , then the server responds by telling that the request have been completed and gives the output to the client. Then the client can choose to perform next service (among client side or server side).

A sample delay service is made to check asynchronous service as other services would be fast and so the server will reply the answer on first check. So to check its working a delay service is made , such that the server sleeps for some time and responds after that.In this time the client can check by invoking the server and server would respond that the service has not yet been completed.

#### Design:
The code is made in Java.
For the implementation of connection between server and client **socket programming** is used.

##### Server Side
1. Firstly the server creates a socket to listen to the clients on that port.
2. To accept the listeners(clients) listener.accept() is used.
3. Then after listening to each client it creates a new Thread for that client.
Then it asks the client what type of service to serve.
4. Then when the client confirms the service it takes the input and then creates a new thread for that service. Then it process the service in the new thread created and in the present thread for that client waits for the user to ask for answer.
5. If the service has been processed , it responds the answer else it responds the service has not yet been completed. To check if the service has been completed or not a boolean variable is taken in the new thread of the service , which is false if the service is not processed , and after processing of the service it is set to true.
In this way server works.

##### Client Side 
1. Firstly it connects to the server using port on which server is listening using Socket.
2. Then it choses a client service or a server service .It can choose a Synchronous or Asynchronous service based on its needs.Both are implemented in nearly same way , but in asynchronous service the user can process other things ,meanwhile the server completes request.

Client services are implement using BigInteger in java.All the services (add, multiply, subtract, divide, factorial) are basic services but it is implemented for bigger number. For the factoial even 100 factorial is or the range of 10^150 which is very big so to implement that BigInteger is used.
For the matrix multiplication simple maths is used and for Image Scaling **Basic Image manipulation APIs** are used .

### How to Run

##### Compile and run:
The code is made in java.
To run the system , we need to run both the server and the client.
##### For the server :
1. Firstly the server is compiled using : javac Server.java
2. To run the server : java Server

##### For the Client:
1. Firstly the Client is complied using : javac Client.java
2. To run the client : java Client

To run the client the server should be running else an error will be thrown.

#### Input :
The server will ask the user to input the port on which the Socket should start running.Then the server will start listening to that port.
Then we can start clients listening to that port.
Client will ask for IP and port number to connect.
Then after connecting it will ask the user to have Client service and Server Service.
Based on the input further queries can be answered.

##### Output:
Based on the Choice of service the Server and Client will output.
1. On the start of the server the Server will output : The server started on port <portnumber> , if portnumber is free and have permissions.
2. On connection with a new client the server will output : Client <clientNumber> have been connected on port number and say HI to the client.
