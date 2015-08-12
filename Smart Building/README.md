### Smart Building

#### Introduction
We need to write program(s) for emulating a smart building. In a smart building one would have a controller machine whose purpose is to take instructions for controlling appliances like electric lighting, air conditioning and doors etc. in the building. 

Instruction set for this machine consists of two instructions:
1. <Sensed parameter value> = SENSE(<appliance>, <parameter>)
2. CONTROL(<appliance>, <parameter>, <new value>)

Here, <appliance> is the identity of an appliance and <parameter> is the attribute of the appliance that needs to be sensed or controlled. E.g., temperature setting can be a parameter for an AC.

#### Design:
For all the different appliances, different classes are made.In all the classes interface appliance have been implemented . Each class contain all the parameters and id of that particular appliance .  Each class also contain various methods that can be used to controll , sense  , gettype , getid etc.

In the main method arrays are been made of all the different classes that contain multiple appliances of the same type.
Then they all are initialised and input is taken from the user to control and sense various appliane usong appliance name, appliance id etc.

#### How to Run
##### Compile and run the code:
1. Firstly the code is compiled using : javac ControllerMachine.java
2. To run the code : java ControllerMachine

##### Input/Output Format :
1. To sense the parameter value of an appliance.

    1. **Input**  sense <appliance_name> <appliance_id> <parameter> where , sense is the keyword to sense the value.appliance_name is the name of the application whose parameter is to be sensed . appliance_id is the id of the appliance whose parameter is to be sensed as there can be multiple appliances.parameter is the parameter whose value is to sensed.
    2. **Output** The <parameter> of the <appliance_name> is <sensed_value> .where , parameter is the parameter whose value is being sensed. appliance_name is the name of the appliance whose value is being sensed. sensed_value is the value of the parameter .

2. To control the parameter value of the appliance 
    1. **Input**  control <appliance_name> <appliance_id> <parameter> <new_value> where , control is the keyword to control the appliance. appliance_name is the name of the application whose parameter is to be controlled . appliance_id is the id of the appliance whose parameter is to be changed as there can be multiple appliances. parameter is the parameter whose value is to controlled. new_value is the new value of the parameter that has to be changed.
    2. **Output** The <parameter> of the <appliance_name> is now set to <new_value> . where , parameter is the parameter whose value is being controlled. appliance_name is the name of the appliance whose value is being controlled. new_value is the value of the parameter to be changed.

Appliances used.

Appliances |	Parameters |  Initial state
---         |        ---    | ---
AC		|	temperature	| 23
AC		|	humidity	|	30
AC		|	state		|	OFF	
Fan     |    state		|	OFF
Fan 	|	speed		|	0	
Door	|	state		|	OFF
Door	|	lock		|	Closed
tube	|	state		| OFF
