### Relational Algebra Interpreter

#### Design

First the input is parsed and it is converted to an equivalent postgre sql query.
Then the converted query is run on the connected database.

##### Parsing :
The nested queries should be in square brackets. The nested queries are recursively parsed and then the whole query is generated.

Queries can be of four types :
1. Select : `Select predicate relation` : This query is converted to Select * from relation where predicate. If the query is nested then the nested query should be in brackets [,] .
`Select predicate [relation]` : In this first the relation is parsed recursively, and then it is renamed as a temporary variable. and then the query is converted to `Select * from ( relation ) as q0`.
	
2. Project : `project column list relation` : This query is converted to Select column list from relation.If the query is nested then the nested query should be in brackets [,] . 
`project predicate [relation]` In this first the relation is parsed recursively, and then it is renamed as a temporary variable and then the query is converted to `Select column list from ( relation ) as q0`.
3. Natural Join : `naturaljoin relation1 relation2` : This query is converted to Select * from relation1 natural join relation2. If the query is nested then the nested queries should be in brackets [,] . 
`naturaljoin [relation1] [relation2]` : In this first the nested queries are parsed recursively, and then they are renamed as a temporary variables. and then the query is converted to `Select * from ( relation1 ) as q0 natural join ( relation1 ) as q2`.

4. Cartesian Product : `cartesianproduct relation1, ..., relationK` : This query is converted to Select * from relation1 cross join relation2 cross join .... relationK. If the query is nested then the nested queries should be in brackets [,]. `cartesianproduct [relation1],relation2 ...,[relationK]` : In this first the nested queries are parsed recursively, and then they are renamed as a temporary variables. and then the query is converted to `Select * from ( relation1 ) as q0 cross join relation2 cross join ....   ( relationK ) as qK` .

#### How to run :

Change the username and password in the file `login`  to the postgre sql user . First line contains username and second line is password.
Make sure that this user has the permissions to the database (rating).

	Compile : 
		javac lab2.java
	Run :
		java -cp .:jdbc.jar lab2  

    Enter the relational algebra statement you wish to execute.
	    Eg:- project mid,title movie
		

##### Files :
**login** : This file contains the login details of the database.First line is the username and second line contains the password of the user.

**Lab2.java** : This is the class which contains the main function and communicates with postgresql. it first connects with the database named "rating" and take input from the user, and then call the parser function to parse the command to convert into postgre sql query.

**Parse.java** : This is the file in which parsing of the input is done. Input is parsed and then it is returned to the main function.
 
 **Sample Queries.txt** : This files contain sample queries for testing.
