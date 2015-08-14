### List APIs

#### Design:
The code is made in java. To find the number of occurences of all the API in the code, javap command is run . To run the command Runtime.getRuntime.exec() is used. It creates a process and then the output of the process is read using Bufferreader.

Since , we have to find the occurences of the function of various classes, we need to find the number of occurences of the method with invokevirtual.
So firstly, a line is read , then it is checked if it is invokevirtual or not.
Then , if it invoke virtual , the classname , functionname and parameters are extracted using handcode.
All the useful information are extracted and added to a string .
To maintain the record of all the methods arraylist is used.
Then it is checked if this method has already been called or not.
If it has already been called , then it is deleted from the arraylist and then added back with increased number of occurence.
To maintain a record of the number of occurence , a separate arraylist is used .

Then after processing of all the lines , the output is produced.
The output is produced in the form of a table using stringformat.

#### How To Run
##### Compile and run:
1. To compile the code: javac assignment.java
2. To run the code: java assignment

#### Input:
The input is the path of the bytecode(.class) file of whose API are to be found out.

#### Output:
The output Consists of all the API for the given .class file.

	S.no. Class Method Occurences
	where,
		class is the class of the API
		Method is the function of the API
		Occurences is the number of Occurences of the given API
		

