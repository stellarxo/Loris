#LORIS Neuroimaging Platform

LORIS is a web-accessible database solution for neuroimaging, providing a secure infrastructure to automate the flow of clinical data for complex multi-site neuroimaging studies.

This Readme covers installation of the <b>16.0</b> LORIS release on <b>Ubuntu</b>.
([CentOS Readme also available](https://github.com/aces/Loris/blob/16.04-dev/README.CentOS6.md))

Please consult the [LORIS Wiki Setup Guide](https://github.com/aces/Loris/wiki/Setup) notes on this [Install process](https://github.com/aces/Loris/wiki/Install-Script) for more information not included in this Readme. The [LORIS Developers mailing list](http://www.bic.mni.mcgill.ca/mailman/listinfo/loris-dev) may also provide installation guidance not covered in the Wiki. 

<b>⇾  Deploy on Heroku</b>
As an alternative to installing LORIS on your system (per instructions below), LORIS can now be deployed on Heroku.
Note: Your default credentials after deployment will be 'admin' as the username and your password will be the uniquely generated password used by ClearDB.
[![Deploy](https://www.herokucdn.com/deploy/button.png)](https://heroku.com/deploy)

# Prerequisites for Installation

 * LINUX (supported on Ubuntu 14.04 and CentOS 6.5) or Mac OS X (tested for Mavericks - OS X 10.9)
 * Apache2 (libapache2-mod-php5)
 * MySQL (libmysqlclient15-dev mysql-client mysql-server)
 * PHP 5.3+ (php5 php5-mysql php5-gd php5-sqlite)
 * PEAR (php-pear)
 * php5-json (for Debian/Ubuntu distributions)
 * Package manager (for LINUX distributions)
 * Composer

<b>Important:</b> Composer should be installed with --no-dev option.  
Consult the [LORIS Wiki](https://github.com/aces/Loris/wiki/Setup) page on this [Install process](https://github.com/aces/Loris/wiki/Install-Script) for more information.

# Installation

1. Set up LINUX user lorisadmin and create LORIS base directory:

    ```
    sudo useradd -U -m -G sudo -s /bin/bash lorisadmin
    sudo passwd lorisadmin
    su - lorisadmin
    ```

    <b>Important ⇾ All steps from this point forward must be executed by lorisadmin user</b>

    ```
    sudo mkdir -m 775 -p /var/www/$projectname
    sudo chown lorisadmin.lorisadmin /var/www/$projectname
    ```

    <i>$projectname ⇾ “loris” or one-word project name</i>

2. Get code:
    Download the latest release from the [releases page](https://github.com/aces/Loris/releases) and
    extract it to `/var/www/$projectname`

3. Run installer script to install core code, libraries, and MySQL schema (see LORIS Setup Schematic). The script will prompt for information, including usernames and folders which it will create automatically.

    For more information, please read the [Install Script wiki page](https://github.com/aces/Loris/wiki/Install-Script).

    ```
    cd /var/www/$projectname/tools
    ./install.sh
    ```

4. Apache configuration and restart 
LORIS requires Apache's mod_rewrite module to rewrite its URLs. Enable this module, then restart Apache: 

    ```
    sudo a2enmod rewrite
    sudo service apache2 reload
    ```

5. Go to http://localhost to verify that the LORIS core database has been successfully installed. Congratulations!
Log in with the username “admin” and the password you supplied for this user while running the Install script.

    _Note_: Apache config files will be installed as *.conf, per Ubuntu 14.04. If running an earlier version of Ubuntu, rename these files, then run the following commands. After, restart Apache.


    ```
    sudo a2dissite default
    sudo a2ensite $projectname
    ```
6. Note that the default Loris setup assumes that Loris is running on localhost. If this
is not the case, you'll have to manually update the URL and Host config variables in the
ConfigSettings table by running the following SQL commands from a MySQL prompt:

    ```SQL
    UPDATE Config SET Value='$yourURL' WHERE ConfigID=(SELECT ID FROM ConfigSettings WHERE Name='url');
    UPDATE Config SET Value='$yourHostname' WHERE ConfigID=(SELECT ID FROM ConfigSettings WHERE Name='host');
    ```

    Make sure that `$yourURL` above contains the "http://" or "https://" and `$yourHostname` does not. If your server is only being accessed from localhost, you can skip this step.

7. Follow the [Setup Guide in the LORIS Wiki](https://github.com/aces/Loris/wiki/Setup) to complete your post-installation setup and configuration, and for more documentation.

# Community
Please feel free to subscribe to the [LORIS Developers mailing list](http://www.bic.mni.mcgill.ca/mailman/listinfo/loris-dev) to ask any LORIS-related questions.
