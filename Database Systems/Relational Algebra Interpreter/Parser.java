public class Parser {
	static int level = 0;

	// This Function is to extract the Relation string that is to be parsed by finding the matching parenthesis	
	public static String getString(String input) {
		String output = "";
		int count = 1;
		int i = 0;
		while (input.charAt(i) == ' ')
			i += 1;
		while (i < input.length()) {
			output += input.charAt(i);
			if (input.charAt(i) == '[')
				count++;
			else if (input.charAt(i) == ']')
				count--;
			if (count == 0)
				break;
			i += 1;
		}
		return output.substring(0, output.length() - 1);
	}

	public static String parse(String input) {
		// To trim spaces from beginning and end of a string
		input = input.trim();
		String output = null;
		int relationStartIndex = -1;
		boolean isNested = false;

		if (input.startsWith("select") || input.startsWith("project")) {
			// Checking whether nested or not and assigning variables
			// accordingly
			if (input.contains("[")) {
				relationStartIndex = input.indexOf('[');
				isNested = true;
			} else
				relationStartIndex = input.lastIndexOf(" ") + 1;

			// Recursively parsing the relation
			String relation = input.substring(relationStartIndex);
			if (isNested) {
				relation = "("
						+ parse(relation.substring(1, relation.length() - 1))
						+ ") as q" + String.valueOf(level);
				level += 1;
			}

			// Framing the query
			if (input.startsWith("select")) {
				String predicate = input.substring(7, relationStartIndex);
				output = "SELECT * from " + relation + " WHERE " + predicate;
			} else if (input.startsWith("project")) {
				String columnList = input.substring(8, relationStartIndex);
				output = "SELECT " + columnList + " from " + relation;
			}

		}
		// In case of Natural Join Recursively form relation1 and relation 2 and then frame the query
		if (input.startsWith("naturaljoin")) {
			String first, second;
			int i = 11;
			// multiple spaces
			while (input.charAt(i) == ' ')
				i++;

			// Creating relation 1 (Recursively)
			if (input.charAt(i) == '[') {
				first = getString(input.substring(i + 1));
				i += first.length() + 2;
				first = "( " + parse(first) + " ) as q" + String.valueOf(level);
				level += 1;
			} else {
				// string till next space
				first = "";
				while (input.charAt(i) != ' ') {
					first += input.charAt(i);
					i += 1;
				}
			}

			while (input.charAt(i) == ' ')
				i++;

			// Creating Relation 2 (Recursively)
			if (input.charAt(i) == '[') {

				second = getString(input.substring(i + 1));
				i += second.length() + 2;
				second = "( " + parse(second) + " ) as q"
						+ String.valueOf(level);
				level += 1;

			} else {
				// string till next space
				second = "";
				while (i < input.length() && input.charAt(i) != ' ') {
					second += input.charAt(i);
					i += 1;
				}
			}

			// Framing the query
			String relation = first + " natural join " + second;
			output="Select * from "+relation; 
		}
		
		// In cartesianproduct create Relation1,2..k recursively , crossjoin them and then frame the query.
		else if (input.startsWith("cartesianproduct")) {
			String out = "";
			int i = 16;
			
			// Parsing the relations  
			while (i < input.length()) {
				String temp = "";
				while (input.charAt(i) == ' ')
					i += 1;
				while (i < input.length() && input.charAt(i) != ',') {
					temp += input.charAt(i);
					i += 1;
				}
				// naming them if nested
				if (temp.charAt(0) == '[') {
					out += " ( " + parse(getString(temp.substring(1)))
							+ " ) as q" + String.valueOf(level);
					level += 1;
				} else {
					out += temp;
				}
				out += " CROSS JOIN ";
				i += 1;
			}

			// Framing the query
			String relation= out.substring(0, out.length() - 12);
			output="Select * from "+relation; 
		}

		return output;
	}
}
