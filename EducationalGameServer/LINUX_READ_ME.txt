HOW TO SET UP MYSQL FOR LINUX:

1. First, you need to install the mysql client by executing the following command in the terminal:
    sudo apt-get install libmysqlclient-dev

2. Next, you need to download and install the mysql workbench community edition from http://dev.mysql.com/downloads/workbench/
    When it asks you to create a password, just set it to 'pass'

3. Next, go into the mysql workbench and log into the local instance database. 

4. Next, add the schema from the github repo called EduAppSchemaWithConstraints.sql by doing the following steps:
    file->Open SQL Script->load location
    then refresh your schemas and verify that the schema called eduapp exists

That should be it!

Let Justin know if you have any issues. 
