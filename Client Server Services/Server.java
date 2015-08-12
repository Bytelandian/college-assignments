import java.io. BufferedReader ;				//Importing package for input
import java.io. IOException ;
import java.io. InputStreamReader ;
import java.io. PrintWriter ;					//Importing package for output
import java.net. ServerSocket ;
import java.net. Socket ;						//Importing package for socket
import java.awt.AlphaComposite;					//Importing package for image
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.util.*;							//Importing package for Scanner
public class Server 
{
	static int a1,a2,i,j,k;
	static int[][] ans=new int[1000][1000];		//Variables for Matrix multiplication
	static int[][] a=new int[1000][1000];
	static int b1,b2;
	static int[][] b=new int[1000][1000];
	static String path;							//Variables for Image Manipulation
	static String newpath;
	static int height,width;
	static int seconds;
	static Scanner user=new Scanner(System.in);		//Starting user input variable
	public static void main( String [] args) throws Exception 
	{
		System.out.print("Enter the port number to start Server:");
		int port=user.nextInt();					//Port number to start server
		int clientNumber = 0;
		ServerSocket listener = new ServerSocket (port);
		System . out .println("The Server is running on port "+port+".");
		try 
		{
			while ( true ) 
			{
				new Capitalizer (listener.accept(), clientNumber++).start();	//New Clients
			}
		} 
		finally 
		{
			listener.close();
		}
	}
	private static class Capitalizer extends Thread 	//Each new client is served on a new Thread 
	{
		private Socket socket;						//Socket number (same for each client)
		private int clientNumber;					//Client Number
		BufferedReader in;							//Input for this client
		PrintWriter out;							//Output for this client
		String ints[],input;		
		public Capitalizer ( Socket socket, int clientNumber) throws IOException	//Initialinzg and starting connection with client
		{
			this .socket = socket;
			this .clientNumber = clientNumber;
			log("New connection with client# " + clientNumber + " at " + socket);
			in = new BufferedReader (new InputStreamReader (socket.getInputStream()));
			out = new PrintWriter (socket.getOutputStream(), true );
			out .println("Hello, you are client #" + clientNumber + ".");
		}
		public void run() 
		{
			try 
			{
				while (true)
				{
					in.readLine();
					out.println("Choose a Service:");	//Asking for choice of service
					out.println("Available Services are :");
					out.println("1.Multiply two Matrices.");
					out.println("2.Scale Image");
					out.println("3.Delay Service");
					out.println("Enter your Choice");
					input = in .readLine();
					if (input.equals("1"))
					{
						System.out.println("Client "+clientNumber+" choose a service to multiply Matrices");	//Matrix multiplication service
						Multiplyservice();
					}
					else if (input.equals("2"))
					{
						System.out.println("Client "+clientNumber+" choose a service to Scale Image");		//Image Manipulation service
						Scaleservice();
					}
					else if (input.equals("3"))
					{
						System.out.println("Client "+clientNumber+" choose a service to Delay Service");		//Delay service
						Delayservice();
					}
					else if (input.equals("Bye"))
					{
						break;
					}
				}
			} 
			catch ( IOException e)
			{
				log("client# " + clientNumber + "cannot be handled properly :" + e);
			}
			finally 
			{
				try 
				{
					socket.close();
				}
				catch ( IOException e) 
				{
					log("Couldn't close a socket.");
				}
				log("Connection with client# " + clientNumber + " closed");
			}
		}
		public void Multiplyservice() throws IOException			//Taking input for Matrix Multiplication
		{
			System.out.println("Fetching input from client");
			out.println("Enter the dimensions of the first Matrix: ");
			input = in .readLine();
			ints=input.split(" ");
			a1=Integer.parseInt(ints[0]);
			a2=Integer.parseInt(ints[1]);
			out.println("Enter the First Matrix of dimension "+a1+"x"+a2+": ");
			for (i=0;i<a1;i++)
			{
				input = in .readLine();
				ints=input.split(" ");
				if (i<a1-1)
				out.println("OK");
				for (j=0;j<a2;j++)
				{
					a[i][j]=Integer.parseInt(ints[j]);
				}
			}
			out.println("Enter the dimensions of the Second Matrix: ");
			ints=in.readLine().split(" ");
			b1=Integer.parseInt(ints[0]);
			b2=Integer.parseInt(ints[1]);
			out.println("Enter the Second Matrix of dimension "+b1+"x"+b2+": ");
			for (i=0;i<b1;i++)
			{
				ints=in.readLine().split(" ");
				if (i<b1-1)
				out.println("OK");
				for (j=0;j<b2;j++)
				{
					b[i][j]=Integer.parseInt(ints[j]);
				}
			}
			if (a2!=b1)
			{
				System.out.println("Invalid Input!!!Wrong Dimensions");
			}
			System.out.println("Input Fetched , Processing Request!");
			multiply m=new multiply(socket,clientNumber);			//Starting processing
			m.start();
			out.println("Processing");
			input = in .readLine();
			boolean exit=false;
			while (!exit)						//While output is not given
			{
				if (m.isComplete==false)			//Service not yet completed
				{
					out.println("Still Processing");
				}
				else					//Producing output
				{
					System.out.println("Request Processed , giving results back to client "+clientNumber);
					out.println("The product of the two matrices is:");
					for (i=0;i<a1;i++)
					{
						for (j=0;j<b2;j++)
						{
							out.print(ans[i][j]+" ");
						}
						out.println("");
					}
					out.println("Processed");
					exit=true;
				}
				if (!exit)
				input = in .readLine();
			}
		}
		public void Scaleservice() throws IOException		//Taking input for Image Manipulation
		{
			System.out.println("Fetching input from client");
			out.println("Enter the path of the image to Scale:");
			path=in.readLine();
			out.println("Enter the new path of the image to Scale:");
			newpath=in.readLine();
			out.println("Enter the New Height of the image:");
			height=Integer.parseInt(in.readLine());
			out.println("Enter the New Width of the image:");
			width=Integer.parseInt(in.readLine());
			System.out.println("Input Fetched , Processing Request!");
			scale s=new scale(socket,clientNumber);
			s.start();											//Starting processing
			out.println("Processing");
			input = in .readLine();
			boolean exit=false;
			while (!exit)								//While output is not given
			{
				if (s.isComplete==false)				//Service not yet completed
				{
					out.println("Still Processing");
				}
				else							//Producing output
				{
					System.out.println("Request Processed , giving results back to client "+clientNumber);
					out.println("Processed");
					exit=true;
				}
				if (!exit)
				input = in .readLine();
			}
		}
		public void Delayservice() throws IOException		//Taking input for Delay service
		{
			System.out.println("Fetching input from client");
			out.println("Enter the no of seconds to delay:");
			seconds=1000*Integer.parseInt(in.readLine());
			System.out.println("Input Fetched , Processing Request!");
			delays d=new delays(socket,clientNumber);
			d.start();												//Start processing
			out.println("Processing");
			input = in .readLine();
			boolean exit=false;
			while (!exit)							//While output is not given
			{
				if (d.isComplete==false)			//Service yet not completed
				{
					out.println("Still Processing");
				}
				else											//Producing outpu
				{
					System.out.println("Request Processed , giving results back to client "+clientNumber);
					out.println("Processed");
					exit=true;
				}
				if (!exit)
				input = in .readLine();
			}
		}
		private void log( String message) 
		{
			System . out .println(message);
		}
	}
	private static class scale extends Thread 			//Processing Image Scaling service on a new thread
	{
		int clientNumber;
		boolean isComplete;
		Socket socket;
		public scale (Socket sockets,int clientno) 	//Initialising
		{
			this.clientNumber=clientno;
			this .isComplete =false;
			this.socket=sockets;
		}
		public void run()					//Processing service
		{
			try{
				BufferedImage original = ImageIO.read(new File(path));
				int typeOfImage = original.getType() == 0? BufferedImage.TYPE_INT_ARGB : original.getType();
		
				BufferedImage resizedImage = new BufferedImage(width, height, typeOfImage);
				Graphics2D g = resizedImage.createGraphics();
				g.drawImage(original, 0, 0, width, height, null);
				g.dispose();
				ImageIO.write(resizedImage, "jpg", new File(newpath));  
			}
			catch(IOException e)
			{
				System.out.println(e.getMessage());
			}
			this.isComplete=true;				//Service Processed
		}
	}
	private static class delays extends Thread 					//Starting Delay service on a new thread
	{
		int clientNumber;
		boolean isComplete;
		Socket socket;
		public delays (Socket sockets,int clientno) 	//Initialising
		{
			this.clientNumber=clientno;
			this .isComplete =false;
			this.socket=sockets;
		}
		public void run()		//Processing service
		{
			try 
			{
				Thread.sleep(seconds);
			} 
			catch (Exception e) 
			{
				System.out.println(e);
			}			
			this.isComplete=true;		//Service Processed
		}
	}
	private static class multiply extends Thread 		//Processing Multiplication service on a new thread
	{
		int clientNumber;
		boolean isComplete;
		Socket socket;
		public multiply (Socket sockets,int clientno) //Initialising
		{
			this.clientNumber=clientno;
			this .isComplete =false;
			this.socket=sockets;
		}
		public void run() //Processing service
		{
			for (i=0;i<a1;i++)
			{
				for (j=0;j<b2;j++)
				{
					ans[i][j]=0;
					for (k=0;k<a2;k++)
					{
						ans[i][j]+=a[i][k]*b[k][j];
					}
				}
			}
			this.isComplete=true;			//Service Processed
		}
	}
}
