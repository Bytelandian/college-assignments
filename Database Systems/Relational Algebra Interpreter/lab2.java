//
// tryjdbc0.java
//
//  Connects to the rating database and retrieves all tuples in the
//  movie relation. It is assumed that the rating database exists in
//  local server. You can use the accompanying rating.txt file to
//  create and populate the database.
//
//  Created by Narayanan Chatapuram Krishnan on 12/02/15.
//

/* import the sql package and not the postgresql package. */
import java.sql.*;
import java.util.Scanner;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class lab2 {
	public static void main(String args[]) {
		/* create a successful connection to the database server. */
		Connection c = null;
		try {
			Class.forName("org.postgresql.Driver");
			// login details from the file login
			List<String> lines = Files.readAllLines(Paths.get("login"), Charset.defaultCharset());
			String username=lines.get(0);
			String password=lines.get(1);
			c = DriverManager.getConnection(
					"jdbc:postgresql://localhost:5432/rating", username,
					password);
		} catch (Exception e) {
			e.printStackTrace();
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(0);
		}
		System.out.println("Opened database successfully");

		try {
			Statement stmt = c.createStatement();
			/* execute a query on the server */
			Scanner in = new Scanner(System.in);
			String query = in.nextLine();
			// To lower case to compare with 'select' 'Select'!='select'
			query = query.toLowerCase();
			query = Parser.parse(query) + ";";
			System.out.println(query);
			ResultSet rs = stmt.executeQuery(query);
			/* obtain information about the resulting relation */
			ResultSetMetaData rsm = rs.getMetaData();
			/* first, print the names of the attributes */
			int ncolumns = rsm.getColumnCount();
			for (int i = 1; i <= ncolumns; i++) {
				if (i > 1)
					System.out.print(",  ");
				System.out.print(rsm.getColumnName(i));
			}
			System.out.print("\n");
			/* print the result of the qeury */
			while (rs.next()) {
				for (int i = 1; i <= ncolumns; i++) {
					if (i > 1)
						System.out.print(",  ");
					String columnValue = rs.getString(i);
					System.out.print(columnValue);
				}
				System.out.println("");
			}
			in.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(0);
		}
	}
}
