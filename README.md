RegmagiK WordPress 
======================================

This git repository is based on a WordPress package.  It has been customized to run on Heroku and
 serve as RegmagiK and Searchcut downloads web site.  You can download RegmagiK Registry Editor and other tools for Windows XP and later. Visit http://www.regmagik.com/downloads for a full list of tools.

The backend database is MySQL and the database connection is configured in Heroku configuration via environment variables.


Running on Heroku
----------------------------

To setup your own instance, you need an account Heroku. Create an app and add ClearDB mySQL add-on. On the Settings tab, add environment variables for mySQL connection: BORISDB, BORISQLSERVER, BORIS, BORISECRET. The values are provided by ClearDB add-on. 

Note: If you would like to add custom plugins or themes, add them into php/wp-content/themes, php/wp-content/plugins directories.

Security Considerations
-----------------------
Consult the WordPress documentation for best practices regarding securing your wordpress installation.  
