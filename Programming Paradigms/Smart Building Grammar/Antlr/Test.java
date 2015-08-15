import org.antlr.runtime.ANTLRStringStream;
import org.antlr.runtime.CharStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.TokenStream;
import java.util.Scanner;

public class Test {
	public static void main(String[] args) throws RecognitionException {
		Scanner in=new Scanner(System.in);
		String input=new String("");
		while (in.hasNext())
		{
		//	System.out.println(input);
			input+=in.nextLine();
			input+="\n";
		}
	//	System.out.println(input);
//		CharStream stream =	new ANTLRStringStream("AC IS AN APPLIANCE WITH PARAMETERS [CoolingLevel:(0-40),AHLevel:(0-100),State:(ON-OFF)]\nTubeLight IS AN APPLIANCE WITH PARAMETERS [State:(ON-OFF)]\nLightSensor IS AN APPLIANCE WITH PARAMETERS [AmbientLux:(0-100000)]\nFan IS AN APPLIANCE WITH PARAMETERS [RPM:(0-5000),MotorTemperature:(0-200)]\nL5 = ClassRoom IS A BUILDING HAVING [AC:3,TubeLight:10]\nJUP = JupiterHostel IS A BUILDING HAVING [TubeLight:150,Fan:100,LightSensor:2]\nSENSE State OF L5 AC[2]\nSENSE RPM OF JUP Fan[1]\nCONTROL RPM OF JUP Fan[1] AS 2000\nCONTROL State OF L5 AC[2] AS ON\nSENSE RPM OF JUP Fan[1]");
		CharStream stream = new ANTLRStringStream(input);
		GrammarLexer lexer = new GrammarLexer(stream);
		TokenStream tokenStream = new CommonTokenStream(lexer);
		GrammarParser parser = new GrammarParser(tokenStream);
		parser.programs();
		System.out.println("Done!!!");
		in.close();
	}
}
