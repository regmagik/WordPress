RegmagiK WordPress 
======================================

This git repository is based on a WordPress package configured for deployment to OpenShift.  It has been customized to run on Heroku and
 serve as RegmagiK and Searchcut downloads web site.  You can download RegmagiK Registry Editor and other tools for Windows XP and later. Visit http://www.regmagik.com/downloads for a full list of tools.

The backend database is MySQL and the database connection is configured in Heroku configuration via environment variables.


Running on Heroku
----------------------------

To setup your own instance, you need an account Heroku. Create a project with two components: PHP and mySQL. 

Note: You may not be able to upload plugins and themes via WordPress built-in features if you choose the free OpenShift plan.  If you would like to add custom plugins or themes, download them, then check them directly into php/wp-content/themes, php/wp-content/plugins directories.

Security Considerations
-----------------------
Consult the WordPress documentation for best practices regarding securing your wordpress installation.  
