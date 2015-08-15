import java.util.Scanner;							//IMPORTING SCANNER
class appliance									//CLASS TO STORE THE APPLIANCE
{
	String type;								//TO STORE THE TYPE OF THE APPLIANCE(AC,TUBELIGHT,etc)
	String paramname[]=new String[20];					//TO STORE THE Parameters OF THE APPLIANCE(State,RPM,etc)
	int paramvalue[]=new int[20];						//TO STORE THE value OF THE Parameter("ON","OFF",etc)
	int parammax[]=new int[20];						//TO STORE THE max value OF THE Parameter("ON",5000,etc)
	int parammin[]=new int[20];						//TO STORE THE min value OF THE Parameter("OFF",0,etc)
	int parameters;								//TO STORE THE number of parameters
	int id;									//TO STORE THE id of the appliance
	appliance(String name,String param[],int min[],int max[],int ids,int n)	//TO INITIALIZE
	{
		int i;
		id=ids;
		type=name;
		parameters=n;
		for (i=0;i<n;i++)
		{
			paramname[i]=param[i];
			parammax[i]=max[i];
			parammin[i]=min[i];
			paramvalue[i]=min[i];					//INITIALLLY VALUE IS SET TO min value("OFF",0,etc)
		}
	}
	int sense(String para)							//TO SENSE THE value OF THE Parameter("ON",5000,etc)
	{
		for (int i=0;i<parameters;i++)
		{
			if (paramname[i].equals(para))
			{
				return paramvalue[i];
			}
		}
		System.out.println("Not a valid parameter");			//IF THERE IS NO SUCH PARAMETER
		return -1;
	}
	void control(String para,int value)					//TO CONTROL THE value OF THE Parameter("ON",5000,etc)
	{
		for (int i=0;i<parameters;i++)
		{
			if (paramname[i].equals(para))
			{
				if (value<=parammax[i]&&value>=parammin[i])
				{
					paramvalue[i]=value;
					return ;
				}
				else
				{
					System.out.println("Not a valid value to be set");//If value is not in range 
					return ;
				}
			}
		}
		System.out.println("Not a valid parameter");				//IF THERE IS NO SUCH PARAMETER
	}
};
class building										//CLASS TO STORE THE APPLIANCE
{
	String name;									//TO STORE THE Name of the building
	appliance app[]=new appliance[1000];						//TO STORE THE Appliances in the building
	int apps;									//TO STORE THE Number of the appliances in building
	building(String names,String a[],int nos[],String param[][],int min[][],int max[][],int n[],int no) //INITIALIZING
	{
		name=names;
		apps=0;
		for (int i=0;i<no;i++)
		{
			for (int j=0;j<nos[i];j++)
			{
				app[apps]=new appliance(a[i],param[i],min[i],max[i],j,n[i]);
				apps+=1;
			}
		}
	}
	int sense(String name,int no,String param)					//TO SENSE THE value of the appliance
	{
		for (int i=0;i<apps;i++)
		{
			if ((app[i].type).equals(name)&&app[i].id==no)
			{
				return app[i].sense(param);
			}
		}
		System.out.println("Building does not have any appliance of this type");//IF there is no such appliance in building
		return -1;
	}
	void control(String name,int no,String param,int value)				//TO CONTROL THE value of the appliance
	{
		for (int i=0;i<apps;i++)
		{
			if ((app[i].type).equals(name)&&app[i].id==no)
			{
				app[i].control(param,value);
				return;
			}
		}
		System.out.println("Building does not have any appliance of this type");//IF there is no such appliance in building
		return;
	}
};

class ControllerMachine
{
	public static void main(String args[])
	{
		building buildings[]=new building[100];			//Variable of the building
		appliance appliances[]=new appliance[100];		//Variable of the appliances
		int apps=0;	
		int bui=0,i,j,app_no,new_value;
		int tp_n[]=new int[20];
		String line,type,buil_no,param_type;
		String param[]=new String[20];
		int min[]=new int[20];
		int max[]=new int[20];
		String tp_type[]=new String[1000];
		int tp_nos[]=new int[1000];
		String tp_para[][]=new String[1000][20];
		int tp_min[][]=new int[1000][20];
		int tp_max[][]=new int[1000][20];
		Scanner in=new Scanner(System.in);
		while (in.hasNext())				//while the user provides input
		{
			line=in.nextLine();
			//System.out.println(line);
			if (line.indexOf("IS AN APPLIANCE")!=-1)	//To chec if it is declaration of appliance
			{
				type=(String)line.substring(0,line.indexOf("IS AN APPLIANCE")-1);
				line=line.substring(line.indexOf("[")+1,line.indexOf("]"));
				i=0;
				while (line.indexOf(":")!=-1)		//Collecting all the parameters
				{
					param[i]=(String)line.substring(0,line.indexOf(":"));
					if (param[i].equals("State"))
					{
						min[i]=0;
						max[i]=1;
					}
					else
					{
						min[i]=Integer.parseInt((String)line.substring(line.indexOf("(")+1,line.indexOf("-")));
						max[i]=Integer.parseInt((String)line.substring(line.indexOf("-")+1,line.indexOf(")")));
					}
					if (line.indexOf(")")+2<line.length())
					line=line.substring(line.indexOf(")")+2);
					else line="";
					i++;
				}
				appliances[apps]=new appliance(type,param,min,max,0,i);	//declaring apppliances
				apps++;
			}
			else if (line.indexOf("IS A BUILDING HAVING")!=-1)	//To chec if it is declaration of Builiding
			{
				type=(String)line.substring(0,line.indexOf("=")-1);
				line=(String)line.substring(line.indexOf("[")+1,line.indexOf("]"));
				i=0;
				while (line.indexOf(":")!=-1)	//collecting all the appliances
				{
					tp_type[i]=(String)line.substring(0,line.indexOf(":"));
					if (line.indexOf(",")==-1)
					tp_nos[i]=Integer.parseInt((String)line.substring(line.indexOf(":")+1));
					else
					tp_nos[i]=Integer.parseInt((String)line.substring(line.indexOf(":")+1,line.indexOf(",")));
					for (j=0;j<apps;j++)
					{
						if ((appliances[j].type).equals(tp_type[i]))
						{
							tp_para[i]=appliances[j].paramname;
							tp_min[i]=appliances[j].parammin;
							tp_max[i]=appliances[j].parammax;
							tp_n[i]=appliances[j].parameters;
							break;
						}
					}
					i++;
					if (j==apps)
					{
						System.out.println(tp_type+" appliance does not exist ");
					}
					if (line.indexOf(",")!=-1)
					line=line.substring(line.indexOf(",")+1);
					else line="";
				}
				buildings[bui]=new building(type,tp_type,tp_nos,tp_para,tp_min,tp_max,tp_n,i);	//declaring the builiding
				bui++;
			}
			else if (line.indexOf("SENSE")!=-1)	//To sense the value of the parameter
			{
				param_type=(String)line.substring(line.indexOf("SENSE")+6,line.indexOf("OF")-1);
				line=line.substring(line.indexOf("OF")+3);
				buil_no=(String)line.substring(0,line.indexOf(" "));
				type=(String)line.substring(line.indexOf(" ")+1,line.indexOf("["));
				app_no=Integer.parseInt((String)line.substring(line.indexOf("[")+1,line.indexOf("]")));
				for (i=0;i<bui;i++)
				{
					if ((buildings[i].name).equals(buil_no))
					{
						if (param_type.equals("State"))
						{
							if (buildings[i].sense(type, app_no, param_type)==1)
							System.out.println("THE "+param_type+" OF THE APPLIANCE "+type+" "+app_no+" OF BUILDING "+buil_no+" IS "+"ON");					 //Printing the output
							else
							System.out.println("THE  "+param_type+" OF THE APPLIANCE "+type+" "+app_no+" OF BUILDING "+buil_no+" IS "+"OFF");				 //Printing the output
						}
						else	
						System.out.println("THE  "+param_type+" OF THE APPLIANCE "+type+" "+app_no+" OF BUILDING "+buil_no+" IS "+buildings[i].sense(type, app_no, param_type));    //Printing the output
						break;
					}
				}
			}
			else if (line.indexOf("CONTROL")!=-1) //To control the value of the parameter
			{
				param_type=(String)line.substring(line.indexOf("CONTROL")+8,line.indexOf("OF")-1);
				line=line.substring(line.indexOf("OF")+3);
				buil_no=(String)line.substring(0,line.indexOf(" "));
				type=(String)line.substring(line.indexOf(" ")+1,line.indexOf("["));
				app_no=Integer.parseInt((String)line.substring(line.indexOf("[")+1,line.indexOf("]")));
				if (param_type.equals("State"))
				{
					if (line.substring(line.indexOf("AS")+3).equals("ON"))
					new_value=1;
					else
					new_value=0;
				}
				else
				new_value=Integer.parseInt((String)line.substring(line.indexOf("AS")+3));
				for (i=0;i<bui;i++)
				{
					if ((buildings[i].name).equals(buil_no))
					{
						buildings[i].control(type, app_no, param_type,new_value);	//controlling
						break;
					}
				}
			}
		}
		in.close();			//closing the input
	}
}
