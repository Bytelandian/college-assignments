### Grammar for Smart Building

In this assignment, we first need to build a grammar to allow expressing the configuration of a smart building. And also create a program which reads such a configuration and creates necessary objects to simulate the scenario. Configuration of a smart building includes specifying what different types of appliances are installed in the building. Clearly, this will require the grammar to allow expressing the configuration of individual appliances as well.
Compile and run:

#### Design
The code is made in java to simulate a smart building . The input is user friendly and its grammar is defined below in the input part.The useful information is extracted from the input by finding the index of the various grammar 
like "IS AN APPLIANCE" , "OF" , etc. Then two classes are made one of builiding and other of appliances to store appliances and parameters respectively.Then initially all the appliances are initialized and then all the builidings are initialized.Then input is taken which is either SENSE OR CONTROL and then respective action is taken.

#### How to Run
1. To compile the code : javac ControllerMachine.java
2. To run the code : java ControllerMachine
3. To run the code using input and output files : java ControllerMachine < input > output
	
##### Input Format :
###### Input is written in a user friendly and readable form .

1. To declare the appliance : <appliance_name> IS AN APPLIANCE WITH PARAMETERS [<param_name>:(<lower_value>-<higher_value>),next parameter] where , appliance_name is the name of the appliance, param_name is the name of the parameter that the application have, lower_value is the lower limit of the value of the parameter, higher_value is the higher limit of the value of the parameter. next parameter is separated by a ","
		
2. To declare the builiding: <builiding_name> = <type of builiding> IS A BUILDING HAVING [<appliance_name>:<appliance_quantity>,next appliance] where , builiding name is the name of the builiding, appliance_name is the name of the different appliances that the building contains, appliance_quantity is the quantity of the appliances that the builiding contains. next appliance is separated by ","
	
3. To sense the value of the parameter : SENSE <parameter_name> OF <builiing_name> <appliance_name>[appliance_id] where , parameter_name is the name of the parameter whose value is to be sensed, builiding name is the name of the builiding, appliance_name is the name of the appliance, appliance_id is the id of the appliance.

4. TO Control the value of the appliance : CONTROL <parameter_name> OF <builiding_name> <appliance_name>[appliance_id] AS <new_value> where , parameter_name is the name of the parameter whose value is to be controlled, builiding_name is the name of the builiding, appliance_name is the name of the appliance, appliance_id is the id of the appliance, new_value is the value of the value to be set.
	
###### OUTPUT :
1. Output consists of the lines corresponding to the SENSE input: THE <parameter_name> OF THE APPLIANCE <appliance_name> <appliance_id> OF BUILDING <building_name> IS <value> where , parameter_name is the name of the parameter whose value is to sensed, appliance_name is the name of the appliance, appliance_id is the name of the appliance, building_name is the name of the builiding, value is the sensed value of the parameter of the appliance in the builiding.
