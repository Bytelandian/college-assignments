### Smart Building Grammar using ANTLR

#### Design
The code is made in java to simulate a smart building .The input is user friendly and its grammar is defined below in the input part. The useful information is extracted from the input , using the GRAMMAR parser .
To make the grammar parser tokens are defined .

> Firstly letter and digit are defined as follows :
1. fragment LETTER : ('a'..'z' | 'A'..'Z') ;
2. fragment DIGIT : '0'..'9';
3. Then Integer and ident are defined .
4. INTEGER : DIGIT+ ;
5. IDENT : LETTER (LETTER | DIGIT)*;

After this the programs is called from the test java file . In the programs grammar there are series of input expressions which are either applications declarations ,  building declaration , sense statement or the control statement .

`
programs
	: ( expr)*
	;
`

`
expr
	:	app|bui|sense|control
	;
`	
Then one by one all the expressions are defined that is app , bui , sense , control .

`
app
	: IDENT 'IS AN APPLIANCE WITH PARAMETERS ' '[' (','? param)* ']'
	;
`

`
param 
	: IDENT ':' '(' value  '-'  value ')'
	;
`

value is either a Integer(eg-0-500) or Ident (eg-ON-OFF)

`
value 
	: INTEGER | IDENT
	;
`

`
bui 
	: IDENT '= ' IDENT 'IS A BUILDING HAVING ' '[' (','? appl)* ']'
	;
`	
	
appl is the number of the appliances of the particular applications.

`
appl
	: IDENT ':' INTEGER
	;
`

`
sense
	: 'SENSE' IDENT ' OF ' IDENT IDENT '[' INTEGER ']'
	;
`

`
control
	: 'CONTROL ' IDENT ' OF ' IDENT IDENT '[' INTEGER ']' 'AS ' value
	;
`

Then two classes are made one of builiding and other of appliances to store appliances and parameters 
respectively.Then initially all the appliances are initialized and then all the builidings are initialized.
Then input is taken which is either SENSE OR CONTROL and then respective action is taken.

#### How To Run
##### Compile and run:
1. The code is made in Eclipse using the antlr plugin .
2. The code is run in Eclipse after installing the ANTLR plugin .
3. The grammar file is made Sample.g and a test java file is made to take the input from the user and then process it.
	
##### Input Format :
Input is written in a user friendly and readable form .

1. To declare the appliance : <appliance_name> IS AN APPLIANCE WITH PARAMETERS [<param_name>:(<lower_value>-<higher_value>),next parameter]
	where ,
		appliance_name is the name of the appliance
		param_name is the name of the parameter that the application have
		lower_value is the lower limit of the value of the parameter
		higher_value is the higher limit of the value of the parameter
		next parameter is separated by a ","

2. To declare the builiding:
	<builiding_name> = <type of builiding> IS A BUILDING HAVING [<appliance_name>:<appliance_quantity>,next appliance]
	where ,
		builiding name is the name of the builiding
		appliance_name is the name of the different appliances that the building contains
		appliance_quantity is the quantity of the appliances that the builiding contains
		next appliance is separated by ","
	
3. To sense the value of the parameter :
	SENSE <parameter_name> OF <builiing_name> <appliance_name>[appliance_id]
	where ,
		parameter_name is the name of the parameter whose value is to be sensed
		builiding name is the name of the builiding
		appliance_name is the name of the appliance
		appliance_id is the id of the appliance

4. TO Control the value of the appliance :
	CONTROL <parameter_name> OF <builiding_name> <appliance_name>[appliance_id] AS <new_value>
	where ,
		parameter_name is the name of the parameter whose value is to be controlled
		builiding_name is the name of the builiding
		appliance_name is the name of the appliance
		appliance_id is the id of the appliance
		new_value is the value of the value to be set
	
##### OUTPUT :
1. Output consists of the lines corresponding to the SENSE input:
	THE <parameter_name> OF THE APPLIANCE <appliance_name> <appliance_id> OF BUILDING <building_name> IS <value>
	where ,
		parameter_name is the name of the parameter whose value is to sensed
		appliance_name is the name of the appliance
		appliance_id is the name of the appliance
		building_name is the name of the builiding
		value is the sensed value of the parameter of the appliance in the builiding
