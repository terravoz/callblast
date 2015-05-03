# Introduction
Callblast is a free and open source Drupal installation profile that enables the creation and management of bulk SMS and voice calls.

# Features
Callblast provides a simple mechanism to manage contact lists with phone numbers, names, organizations, groups and related fields. It also supports the following kinds of blasts:
* Send SMS Announcement, which enables users to send single text messages to selected groups.
* SMS Opt-In Invitation, which enables users to send subscription invitations to selected contact groups.  The subscriptions will only be executed once the SMS recipients reply with the appropriate keyword. (NOTE: subscription, unsubscription and help keywords might be defined in admin/voip/sms_actions)
* Voice Announcement from Text, which converts your text input into and audio file and plays that file to each contact in the specified groups.
* Voice Announcement from Audio, which plays the specified audio file in calls to the target group.
* Voice Announcement using VoIP Script, which enables the creation of interactive voice calls that execute the given VoIP Script for each contact in the target group.

# Requirements
In order to install the Callblast, you will need:
* Drush (http://www.drush.org)
* PHP Curl extension enabled. For Debian systems, just run 
```sh
$ sudo apt-get install php5-curl 
$ sudo /etc/init.d/apache2 restart
```
# Installation

Installing Callblast requires a few basic steps:
1. Download the Callblast installation profile to your desired location and configure your web and database servers appropriately.
2. Run the Drupal installation for your site and choose the Callblast installation profile
3. Configure VoIP Drupal to connect your site to the VoIP provider of your choice. The instructions are included in the VoIP Drupal README.txt file.
Specific instructions for different providers (Plivo, Tropo, Twilio, etc.) can be found in their respective modules
4. Setup crontab in order to use advanced queue:
```sh
sudo crontab -e PATH=/usr/bin:/bin:/usr/sbin:/sbin */15 * * * * /usr/bin/drush -r {DRUPAL CALLBLAST DIRECTORY eg: /var/www/your_site_dir} advancedqueue --all --timeout=900 -l {http://yoursite.com}
```
5. Configure Callblast settings such as maximum call duration, maximum number of parallel calls, etc. by going to admin/voip/blast

# Usage
Once you login, you will find the following 4 tabs:

1. "Step 1: Import contacts"
Here you upload CSV files with a list of phone numbers to be included in your contacts. You can find a template file at http://yoursite.com/sites/default/files/feeds/testcontacts.csv
Note: Make sure that the "Opted in" field is set to 'yes'. The system will only make calls to phone numbers that are opted-in. This is mandatory in some countries.
Contacts might also be added via the following mechanisms:
Manually, by going to /node/add/phone-number?destination=contacts
Via SMS, by asking users to text XX to your site's phone number (defined in /admin/voip/call/settings)

2. "Step 2: Manage contacts"
Here you can perform a variety of operations on your contact list, including searching by keywords or groups, assigning groups to contacts, exporting contacts to csv, editing, deleting and more.

3. "Step 3: Send announcement"
This is where you actually create and send bulk voice or SMS messages. After you enter all required information, this blast will be scheduled to run with next available queue period.

4. "Step 4: History"
Here you can see all the callblasts sent or or being processed by the system, as well as the with status and phone numbers associated with each call and text message of the blast.

# About
This module has been originally developed by Leo Burd and Tamer Zoubi for [Terravoz](http://terravoz.net).
