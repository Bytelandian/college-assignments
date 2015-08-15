import java.io.BufferedReader;						//Import package for BufferReader
import java.io.InputStreamReader;					//Import package for Input Reader
import java.util.*;							//Import package for Scanner and Arraylist
public class assignment							//Declaring Class
{			
	public static void main(String args[]) throws Exception		//Declaring Main Method
	{
		Process process;					//Declaring Process to run
		Scanner in=new Scanner(System.in);			//Declaring input
		System.out.println("Enter ClassPath:");			
		String path=in.next();					//Input of Byteclass Path
		String command="javap -c -p -classpath . "+path;	//Making Command
		process = Runtime.getRuntime().exec(command);		//Running Command
		BufferedReader input = new BufferedReader(new InputStreamReader(process.getInputStream()));	//Declaring Input Reader
		String line,f,param,clas,add;				//Declaring Variables
		ArrayList<String> ans=new ArrayList<String>();		
		ArrayList<Integer> num=new ArrayList<>();
		int nums=1;
		while ((line = input.readLine())!= null)		//Reading all the lines
		{
			if (line.indexOf("invokevirtual")!=-1)		//Checking if method is virtual or not
			{
				line=line.substring(line.indexOf("Method")+7);	
				if (line.indexOf(".")==-1) continue;	//If it does not contain class name
				clas=line.substring(0,line.indexOf("."));			//Extracting class name
				f=line.substring(line.indexOf(".")+1,line.indexOf(":"));	//Extracting Function name
				line=line.substring(line.indexOf("(")+1,line.indexOf(")"));
				add=clas+":"+f+"(";
				while (!line.equals(""))				//Extracting all the parameters
				{
					if (line.indexOf(";")!=-1)			//Extracting parameters
					{
						param=line.substring(0,line.indexOf(";"));
						line=line.substring(line.indexOf(";")+1);
						if (param.lastIndexOf("/")!=-1)
						param=param.substring(param.lastIndexOf("/")+1);
					}
					else
					{
						param=line;
						line="";
					}
					switch(param)					//Making the parameters full name (int for I)
					{
						case("I"):
							param="int";
							break;
						case("C"):
							param="char";
							break;
						case("F"):
							param="float";
							break;
						case("D"):
							param="double";
							break;
					}
					
					add+=param+",";				//adding parameters to the string
				}
				add+=")";
				nums=1;
				if (ans.contains(add))				//checking if it has already been invoked
				{
					nums=num.get(ans.indexOf(add))+1;	//No of earlier invokations
					num.remove(ans.indexOf(add));
					ans.remove(add);			//Removing earlier invokations
					add=add.substring(0,add.indexOf(")")+1);
				}
				ans.add(add);					//Adding to the list
				num.add(nums);
			}
		}
		System.out.println(" ___________________________________________________________________________");
		System.out.println(String.format("|%-4s| %-31s| %-25s| %-10s|","S.No","Class","Method","Occurances"));	//Formatted Output
		System.out.println(" ___________________________________________________________________________");
		for (int i=0;i<ans.size();i++)
		{
			add=ans.get(i);								//Extrating string
			clas=add.substring(0,add.indexOf(":"));					//Extracting Class name
			if (add.lastIndexOf(",")!=-1)						//Function name with parameters
			f=add.substring(add.indexOf(":")+1,add.lastIndexOf(","));
			else									//Function name without parameters
			f=add.substring(add.indexOf(":")+1,add.lastIndexOf(")"));
			f+=")";
			nums=num.get(i);								//No of occurances
			System.out.println(String.format("|%-4s| %-31s| %-25s| %-10s|",i+1,clas,f,nums));	//Formatting Output
		}
		System.out.println(" ___________________________________________________________________________");
	}
}
