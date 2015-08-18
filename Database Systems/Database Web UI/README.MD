### Database Web UI

#### Design
1. The web UI first connects with the psql database.
2. Then it fetches the table and columns information using information schema.
3. Then it displays the current contents of the database.
4. Functionality to edit, add and delete tupes is provided.

#### Features

1. PHP is used as the scripting language to communicate with the postgres database.
2. Javascript, JQuery are used for client side functioning
3. Bootstrap is used for styling(CSS)
4. This is a generic code which can display any relations of any database(not just to one particular database schema) 

#### How to Run
1. Make Sure that your Apache server connects with the postgres 
2. Edit your credentials in config.php(i.e. postgres username,password,host address,db_name etc.)
3. Copy all The files to your hosting folder(www or htdocs depending on the stack).
4. open localhost/home.php or (host_address/home.php) on your browser 
5. Make sure user has the permission to view and edit the database. 

#### Testing
1. For testing a sample db is created using named test.
2. Add the tables using the test-ddl.txt.
3. Add all the contents using test-data.txt.

