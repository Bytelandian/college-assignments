import java.net. Socket ;							//Importing package for Socket
import java.util.*;								//Importing packages for Scanner
import java.math.*;								//Importing packages for BigInteger
import java.awt. event . ActionEvent ;					
import java.awt. event . ActionListener ;
import java.io. BufferedReader ;					//Importing packages for the input from server		
import java.io. IOException ;			
import java.io. InputStreamReader ;			
import java.io. PrintWriter ;					//Importing input for the output to server

public class Client 
{
	private BufferedReader in ;								//Declaring input variable
	private PrintWriter out ;								//Declaring output variable
	Scanner input=new Scanner(System.in);					//Scanner input
	String inputs,userinput,method="synchronous";
	Socket socket;
	BigInteger a,b,c;
	public Client () throws IOException
	{
		System.out.println("Enter the IP Address of the Server");
		String serverAddress = input.next();									//Server address
		System.out.println("Enter the port Number to Connect to server");
		int port=input.nextInt();												//Port Number
		socket = new Socket (serverAddress, port);								//Socket starting
		in = new BufferedReader (new InputStreamReader (socket.getInputStream()));//Initialing variables
		out = new PrintWriter (socket.getOutputStream(), true );
	}
	public void connectToServer() throws IOException {
		while(true)
		{
			System.out.println("Do you want a Client[C] or Server[S] Service or Bye[Bye]:");	//Choice of service
			userinput=input.nextLine();
			while (userinput.equals("\n")||userinput.equals(""))
			{
				userinput=input.nextLine();
			}
			if (userinput.equals("S")||userinput.equals("s"))		//Server service
			serviceByServer();
			else if (userinput.equals("C")||userinput.equals("c"))	//Client service
			serviceByClient();
			else if (userinput.equals("Bye"))						//Client Stops
			{
				out.println("HI");
				out.println("Bye");
				break;
			}
			else
			System.out.println("Wrong Choice!!!");
		}	
	}
	public void serviceByClient()
	{
		System.out.println("Choose a Service:");
		System.out.println("Available Services are :");
		System.out.println("1.Add two Big numbers.");
		System.out.println("2.Subtract Two Big numbers");
		System.out.println("3.Multiply two big numbers.");
		System.out.println("4.Divide Two Big numbers");
		System.out.println("5.Factorial of Big nmuber");
		System.out.println("Enter your Choice");
		userinput = input.nextLine();
		if (userinput.equals("1"))										//Adding two big numbers
		{
			System.out.println("Enter First Number:");
			a=input.nextBigInteger();
			System.out.println("Enter Second Number:");
			b=input.nextBigInteger();
			System.out.println("The sum of the numbers is: "+a.add(b));
		}
		else if (userinput.equals("2"))								//Subtracting two big numbers
		{
			System.out.println("Enter First Number:");
			a=input.nextBigInteger();
			System.out.println("Enter Second Number:");
			b=input.nextBigInteger();
			System.out.println("The difference of the numbers is: "+a.subtract(b));
		}
		else if (userinput.equals("3"))							//Multiplying two big numbers
		{
			System.out.println("Enter First Number:");
			a=input.nextBigInteger();
			System.out.println("Enter Second Number:");
			b=input.nextBigInteger();
			System.out.println("The product of the numbers is: "+a.multiply(b));
		}
		else if (userinput.equals("4"))							//Dividing two big numbers
		{
			System.out.println("Enter First Number:");
			a=input.nextBigInteger();
			System.out.println("Enter Second Number:");
			b=input.nextBigInteger();
			if (b.compareTo(BigInteger.valueOf(0))!=0)
			System.out.println("The quotient of the numbers is: "+a.divide(b));
			else 
			System.out.println("Wrong input!!!");
		}
		else if (userinput.equals("5"))								//Factorial of big numbers
		{
			System.out.println("Enter Number:");
			a=input.nextBigInteger();
			c=BigInteger.valueOf(1);
			while (a.compareTo(BigInteger.valueOf(0))==1)
			{
				c=c.multiply(a);
				a=a.subtract(BigInteger.valueOf(1));
			}
			System.out.println("The factorial of the numbers is: "+c);
		}
		else
		System.out.println("Wrong input!!!");
	}
	public void serviceByServer() throws IOException
	{
		out.println("Hi");						//Saying HI to server
		inputs=in.readLine();
		while (!inputs.equals("Enter your Choice"))
		{
			System.out.println( inputs);
			inputs=in.readLine();			
		}
		System.out.println( inputs);
		userinput=input.nextLine();
		while (userinput.equals("\n")||userinput.equals(""))
		{
			userinput=input.nextLine();
		}
		out.println(userinput);
		System.out.println("Do you want Synchronous[S] or Asynchronous[A] service:");	//Synchronous or Asynchronous service
		while (true)
		{
			userinput=input.nextLine();
			while (userinput.equals("\n")||userinput.equals(""))
			{
				userinput=input.nextLine();
			}
			method=userinput;
			if (method.equals("S")||method.equals("s"))
			{
				break;
			}
			else if (method.equals("A")||method.equals("a"))
			{
				break;
			}
			else 
			{
				System.out.println("Wrong Input!!");
			}
		}
		while (!inputs.equals("Processing"))				//Giving input to server
		{
			inputs=in.readLine();
			if (!inputs.equals("OK"))
			System.out.println(inputs);
			if (inputs.equals("Processing")) break;
			userinput=input.nextLine();
			while (userinput.equals("\n")||userinput.equals(""))
			{
				userinput=input.nextLine();
			}
			out.println(userinput);
		}
		if (method.equals("S")||method.equals("s"))
		{
			System.out.println("Wait while the Server completes your request!!!");
			inputs=" ";
			while (!inputs.equals("Processed"))			//Giving output to user
			{
				out.println("check");
				inputs=in.readLine();
				if (!inputs.equals("Still Processing"))
				{
					System.out.println("Request have been completed!!");
					while (!inputs.equals("Processed"))
					{
						System.out.println(inputs);
						inputs=in.readLine();
					}
					System.out.println(inputs);
				}
			}
		}
		else if (method.equals("A")||method.equals("a"))
		{
			boolean exit=false;
			while (!exit)
			{
				System.out.println("Do you want to perform a client[C] servie meanwhile while server complete requests[check]");
				userinput=input.nextLine();
				while (userinput.equals("\n")||userinput.equals(""))
				{
					userinput=input.nextLine();
				}
				if (userinput.equals("C")||userinput.equals("c"))			//Client service meanwhile server process request
				serviceByClient();
				else
				{
					out.println("check");								//checking if request have been completed
					inputs=in.readLine();
					if (inputs.equals("Still Processing"))
					{
						System.out.println("Server is still processing!!!");
					}
					else
					{
						System.out.println(inputs);
						while (!inputs.equals("Processed"))
						{
							inputs=in.readLine();
							System.out.println(inputs);
						}
						exit=true;
					}	
				}
			}
		}
	}
	public static void main( String [] args) throws Exception 
	{
		Client client = new Client ();								//Starting client
		client.connectToServer();
	}
}
