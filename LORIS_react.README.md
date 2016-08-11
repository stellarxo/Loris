#LORIS meets ReactJS

##1. Setting up Grunt

<<<<<<< HEAD
In order to run the grunt build step you will have to install the following dependencies
=======
In order to run the grunt build step, you will have to install the following dependencies:
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

* NodeJS
* NPM

###1.1 Installing dependencies 

####1.1.1 NodeJS

<<<<<<< HEAD
To check weather or not NodeJS is installed on your machine run the following:
=======
To check whether or not NodeJS is installed on your machine, run the following:
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

```
node -v
```

<<<<<<< HEAD
If not installed use one of the following steps to install for your OS
=======
If not installed, use one of the following steps to install for your OS:
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

#####Ubuntu

For this install you will need sudo rights

```
curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
sudo apt-get install -y nodejs
sudo apt-get install -y build-essential
```

#####CentOS

```
curl --silent --location https://rpm.nodesource.com/setup_6.x | bash -
yum -y install nodejs
yum install gcc-c++ make
```

#####MacOS

Download the NodeJS package from [here](https://nodejs.org/en/)

####1.1.2 NPM

<<<<<<< HEAD
Once NodeJS is installed use the following to instal NPM
=======
Once NodeJS is installed, use the following to install NPM
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

```
curl -L https://www.npmjs.com/install.sh | sudo sh
```

###1.2 Installing Grunt

<<<<<<< HEAD
Once NodeJS and NPM are installed you are ready to install Grunt. First in your terminal ```cd``` into the LORIS home directory. 
Once there run the following command:
=======
Once NodeJS and NPM are installed, you are ready to install Grunt. First, ```cd``` into the LORIS home directory in your terminal. 
Then run the following command:
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

```
npm install --only=dev
```

<<<<<<< HEAD
Grunt should now be installed 
=======
Grunt should now be installed.
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

##2. Compiling JSX

###2.1 Using Grunt to compile all JSX

<<<<<<< HEAD
To compile all JSX files in LORIS use the following command
=======
To compile all JSX files in LORIS, use the following command:
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

```
node_modules/.bin/grunt jsx
```

<<<<<<< HEAD
**NOTE:** If you create a new react file, ensure you add it to the ```Grunt.js``` file under the ```babel.compile.files``` object
with the formate
=======
**NOTE:** If you create a new React file, ensure you add it to the ```Grunt.js``` file under the ```babel.compile.files``` object
with the following format:
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108

```
'desc/file.js' : 'src/file.js'
```

###2.2 Using Babel to compile JSX

There are four major ways you can compile JSX with Babel. You can compile once or continuously a single or a directory. Using 
continuous compilation becomes useful when you are constantly making changes to the JSX file.

####2.2.1 Compile single file

To compile a single file use the following command:

```
./node_modules/.bin/babel src/file.js --out-file desc/file.js
```

####2.2.2 Compile a directory

To compile a directory use the following command:

```
./node_modules/.bin/babel src/ --out-dir desc/
```

####2.2.3 Continuously compile single file

To compile a single file continuously use the following command:

```
./node_modules/.bin/babel --watch src/file.js --out-file desc/file.js
```

####2.2.4 Continuously compile a directory

To compile a directory continuously use the following command:

```
./node_modules/.bin/babel --watch src/ --out-dir desc/
```

##3. LORIS JSX file structure

<<<<<<< HEAD
Within LORIS we have two main ways off adding JSX and their compiled files. When creating a new JSX file **always** use the ```.js```
=======
Within LORIS, we have two main ways of adding JSX and their compiled files. When creating a new JSX file **always** use the ```.js```
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108
extension or the continuous compilation will not work as expected. The file name of the JSX and its compiled file should have the
same name. 

###3.1 Adding generic JSX files

Within LORIS we have many React components that can be used throughout the different modules. When adding a new generic file, the
JSX file should be placed in the ```jsx/``` directory and its compiled file in the ```htdocs/js/components``` directory.

###3.2 Adding module specific JSX files

<<<<<<< HEAD
In many cases React components are designed for a specific LORIS module. In such cases the JSX file should be placed in the 
=======
In many cases, React components are designed for a specific LORIS module. In such cases the JSX file should be placed in the 
>>>>>>> ad993d6e5e6b42195252d00e96d8a9f42442d108
```module/$DESIRED_MODULE/jsx/``` and its compiled file in the ```module/$DESIRED_MODULE/js/``` directory.
