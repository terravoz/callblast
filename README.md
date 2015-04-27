== Introduction ==

Callblast is open-source ready to use system built on Drupal, for delivering voice and SMS to a group of people.

== Features ==
1. Send SMS Announcement: This allows an authenticated and a privileged user to send Bulk SMS to a targeted group.

2. SMS Opt In Invitation: This enables a privileged user to send message to target group to
reply by texting a keyword to opt-in to receive a message.

3. Voice Announcement from Text: converts your input text into an .mp3 format file with voice
and plays the file to the target group.

4. Voice Announcement from Audio: This allows the system to send recorded mp3 audio file to
a targeted group.
The default maximum length of an individual outgoing call in seconds is 15.
The default maximum number of retries for an individual call is 2.
The default number of seconds between retries is 60; and default Maximum number of parallel calls is 10.

5. Voice Announcement using VOIP SCRIPT: This is used to conduct prewritten VoIP Script to a targeted group.

== Requirements ==

In order to install the Callblast, you will need:

1. Drush (http://www.drush.org)

2. The PHP Curl extension in your system. For Debian systems, just run
  $ sudo apt-get install php5-curl
  $ sudo /etc/init.d/apache2 restart


== Installation ==

Installing Callblast is very simple. Just choose Callblast installation profile
when first time installing your website.

== Post-Installation ==

Postinstallation requires a few configuration steps on your Drupal and server side before you can use the system.

Drupal configuration:

1. Enable and configure one of supported VoIP providers (currently VoIP Drupal supports: Twilio, Tropo, Plivo, Kookoo, other modules might
support more). For details refer to README of each individual VoIP provider in their respective modules.

2. Set that provider as default one in VoIP Server configuration (/admin/voip/servers)

3. Setup crontab in order to use advanced queue:
   sudo crontab -e
   PATH=/usr/bin:/bin:/usr/sbin:/sbin
   */15 * * * * /usr/bin/drush -r {DRUPAL CALLBLAST DIRECTORY eg: /var/www/callblast} advancedqueue --all --timeout=900 -l {http://yourserver.com}


== Usage ==
Instructions: System is pretty straightforward once you login you will find 6 tabs:

Step 1: Import contacts
- Here you upload CSV file with phone numbers. You can find template at
http://yoursite.com/sites/default/files/feeds/testcontacts.csv

!Make sure that Opted in field is set to 'yes'. System will only make calls to phone numbers that are
opted-in (this is regulatory in some countries).

-you can also manually add contacts here: /node/add/phone-number?destination=contacts

-there is also option that people add their numbers (subscribe or unsubscribe) by SMSing any word
to phone number you setup in Default call configuration (/admin/voip/call/settings)

Step 2: Manage contacts
View all contacts in system, search by keywords or groups, mass assign groups to contacts, export
to csv, and bulk actions for edit/deleting/etc...

Step 3: Send announcement
This is where you send bulk voice or SMS announcements. There are two types:
SMS announcement - where you enter SMS text to be sent
Opt-In invitation - here the system sends SMS Opt-In invitation
Voice announcement - where you enter voice to be played
Voice announcement using VoIP Script - here instead you select predefined VoIP Script.
After you enter all required information, this blast will be scheduled to run with next available
queue.

Step 4: History
Here you see all announcements sent or pending to be processed, together with status and phone
numbers to which this announcement was sent. You can click on phone numbers in order to see
detailed call log for each phone number.
Also you can see Ongoing calls, and access Callblast configuration.

== About ==

This module has been originally developed by Leo Burd and Tamer Zoubi