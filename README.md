RegmagiK on WordPress and OpenShift
======================================

This git repository is based on a WordPress package configured for deployment to OpenShift.  It has been further customized
to serve as RegmagiK downloads web site.  You can download RegmagiK Registry Editor and other tools for Windows XP and later. Visit http://www.regmagik.com/downloads for a full list of tools.

The backend database is MySQL and the database connection is configured in OpenShift configuration via environment variables.


Running on OpenShift
----------------------------

To setup your own instance, you need an account at https://www.openshift.com and create a project with two components: PHP and mySQL. 

You'll be prompted to set an admin password and name your WordPress site the first time you visit this
page.

Note: You may not be able to upload plugins and themes via WordPress built-in features if you choose the free OpenShift plan.  If you would like to add custom plugins or themes, download them, then check them directly into php/wp-content/themes, php/wp-content/plugins directories, push changes into the repo and initiate the build in OpenShift or use webhooks to have the build start automatically.

Security Considerations
-----------------------
Consult the WordPress documentation for best practices regarding securing your wordpress installation.  
