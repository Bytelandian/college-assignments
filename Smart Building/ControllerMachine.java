import java.util.Scanner;
public class ControllerMachine {             			//Main public class
	public static void main(String args[]) {		//Main function
		tube t[]=new tube[100];				//Array containg all the tubes
		ac a[]=new ac[100];				//Array containg all the acs
		fan f[]=new fan[100];				//Array containg all the fans
		door d[]=new door[100];				//Array containg all the doors
		for (int i=0;i<100;i++)				//Initialing all the arrays
		{
			t[i]=new tube();
			a[i]=new ac();
			f[i]=new fan();
			d[i]=new door();
		}
		Scanner in=new Scanner(System.in);		//Taking input from the user
		String o,p;
		int id,val;
		while (in.hasNext())				//while the user provides input
		{
			o=in.next();
			if (o.equals("sense"))			//If the operation is of type sense
			{
				o=in.next();  //Type of appliance
				id=in.nextInt()-1; // Id of the  appliance
				p=in.next();	//parameter of the appliance
				if (o.equals("fan")) System.out.println(sense(f[id],p)+".");		//Appliance=Fan
				else if (o.equals("tube")) System.out.println(sense(t[id],p)+".");	//Appliance=Tube
				else if (o.equals("ac")) System.out.println(sense(a[id],p)+".");	//Appliance=Ac
				else if (o.equals("door")) System.out.println(sense(d[id],p)+".");	//Appliance=Door
				else System.out.println("Invalid Appliance.");
			}
			else
			{
				o=in.next();	//type if the appliance
				id=in.nextInt()-1;	//id of the appliance
				p=in.next();		//parameter of the appliance
				val=in.nextInt();	//new value of the appliance
				if (o.equals("fan")) control(f[id],p,val);				//Appliance=Fan
				else if (o.equals("tube")) control(t[id],p,val);			//Appliance=Tube
				else if (o.equals("ac")) control(a[id],p,val);				//Appliance=ac
				else if (o.equals("door")) control(d[id],p,val);			//Appliance=door
				else System.out.println("Invalid Appliance");			
			}
		}
		in.close();
	}
	public static Object sense(Appliance a, String parameter) {				//Sense method to sense the parameter
		Object ob=a.getParamValue(parameter);
		if((ob instanceof Integer)&&(int)ob==-1)				// To check is the parameter was not invalid
		{
			System.out.print("The appliance does not have any parameter of type "+parameter);
			return "";
		}
		else 
		{
			System.out.print("The "+parameter+" of the "+a.getType()+" is ");
			return ob;							// returning sensed value
		}
	}

	public static void control(Appliance a, String parameter, Object paramValue) {   	//Control method
		if ((a.getParamValue(parameter) instanceof Integer)&&((int)a.getParamValue(parameter)==-1))	//To check valid parameter
		{
			System.out.println("The appliance does not have any parameter of type "+parameter+".");
		}
		else
		{
			a.setParamValue(parameter, paramValue);				//Controlling parameter
			System.out.println("The "+parameter+" of the "+a.getType()+" is now set to "+a.getParamValue(parameter)+".");
		}
	}
}
interface Appliance {				//Defining the interface
	String[] listParameterNames();		//Listing all the parameters
	String getType();			// To get the type of appliance
	int getIdentity();			//To get the id of the appliance
	String getState();			//To get the state of the appliance (On/Off)
	Object getParamValue(String paramName);	//to sense the parameter of the apppliance
	void setParamValue(String paramName, Object value);	//To control the parameter of the appliance
}
class ac implements Appliance{
	int temperature,humidity,id;
	String state;
	static int i;
	ac()		//Initialisn parameters
	{
		id=++i;	//Assigning id to each appliance of the same type
		state="OFF";
		temperature=23;
		humidity=30;
	}
	public String[] listParameterNames() {	//Listing all the parameters
		String[] para=new String[3];
		para[0]="temperature";
		para[1]="humidity";
		para[2]="state";
		return para;
	}
	public String getType() {	// To get the type of appliance
		return "AC";
	}
	public int getIdentity() {	//To get the id of the appliance
		return id;
	}
	public String getState() {	//To get the state of the appliance (On/Off)
		return state;	
	}
	public Object getParamValue(String paramName) {		//to sense the parameter of the apppliance
		if (paramName.equals("temperature")) return temperature;
		else if (paramName.equals("humidity")) return humidity;
		else if (paramName.equals("state")) return state;
		else return -1;
	}
	public void setParamValue(String paramName, Object value) {//To control the parameter of the appliance
		if (paramName.equals("temperature")) temperature=(int)value;
		else if (paramName.equals("humidity")) humidity=(int)value;
		else if (paramName.equals("state"))
		{
			if ((int)value==1) state="On";
			else state="Off";
		}
		else System.out.println("Invalid Parameter Type");
	}
}
class fan implements Appliance{

	String state;
	int speed;
	int id;
	static int i;
	fan()		//Initialisn parameters
	{
		state="Off";
		speed=0;
		id=++i;	//Assigning id to each appliance of the same type
	}
	public String[] listParameterNames() {//Listing all the parameters
		String Para[]=new String[2];
		Para[0]="speed";
		Para[1]="state";
		return Para;
	}
	public String getType() {		// To get the type of appliance
		return "Fan";
	}
	public int getIdentity() {		//To get the id of the appliance
		return id;
	}
	public String getState() {		//To get the state of the appliance (On/Off)
		return state;
	}
	public Object getParamValue(String paramName) {	//to sense the parameter of the apppliance
		if (paramName.equals("speed")) return speed;
		else if (paramName.equals("state")) return state;
		else return -1;
	}
	public void setParamValue(String paramName, Object value) {//To control the parameter of the appliance
		if (paramName.equals("speed")) speed=(int)value;
		else if (paramName.equals("state"))
		{
			if ((int)value==1) state="On";
			else state="Off";
		}
		else System.out.println("Invalid Parameter Type");
	}
}

class tube implements Appliance{

	String state;
	int id;
	static int i;
	tube()		//Initialisn parameters
	{
		id=++i;	//Assigning id to each appliance of the same type
		state="Off";
	}
	public String[] listParameterNames() {//Listing all the parameters
		String para[]=new String[1];
		para[0]="state";
		return para;
	}
	public String getType() {		// To get the type of appliance
		return "tube";
	}
	public int getIdentity() {	//To get the id of the appliance
		return id;
	}
	public String getState() {//To get the state of the appliance (On/Off)
		return state;
	}
	public Object getParamValue(String paramName) {	//to sense the parameter of the apppliance
		if (paramName.equals("state"))
		return state;
		else return -1;
	}
	public void setParamValue(String paramName, Object value) {	//To control the parameter of the appliance
		if (paramName.equals("state"))
		{
			if ((int)value==1) state="On";
			else state="Off";
		}
		else System.out.println("Invalid Parameter Type");
	}
}
class door implements Appliance {
	String state,lock;
	int id;
	static int i = 0;

	door() {			//Initialisn parameters
		id = ++i;		//Assigning id to each appliance of the same type
		state = "Off";
		lock = "Closed";
	}
	public String[] listParameterNames() {//Listing all the parameters
		String[] Para = new String[2];
		Para[0] = "state";
		Para[1] = "lock";
		return Para;
	}
	public String getType() {	// To get the type of appliance
		return "door";
	}
	public int getIdentity() {	//To get the id of the appliance
		return id;
	}
	public String getState() {	//To get the state of the appliance (On/Off)
		return state;
	}
	public Object getParamValue(String paramName) {//to sense the parameter of the apppliance
		if (paramName.equals("lock"))
			return lock;
		else if (paramName.equals("state"))
			return state;
		else
			return -1;
	}
	public void setParamValue(String paramName, Object value) {//To control the parameter of the appliance
		if (paramName.equals("state"))
		{
			if ((int)value==1) state="On";
			else state="Off";
		}
		else if (paramName.equals("lock"))
		{
			if ((int)value==1) lock="Closed";
			else lock="Open";
		}
		else System.out.println("Invalid Parameter type.");
	}
}
