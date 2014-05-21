Callblast Demo
========

Import database from mysqldump/callblast.sql
Setup crontab to call advanced queue:
sudo crontab -e
PATH=/usr/bin:/bin:/usr/sbin:/sbin
*/15 * * * * /usr/bin/drush -r /var/www/callblast advancedqueue --all --timeout=900 -l http://yourserver.com

Login to Drupal using:
admin:callblast
