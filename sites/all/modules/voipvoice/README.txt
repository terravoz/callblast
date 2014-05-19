VoIPVoice.module
--------------------------------------------------------------------------------
The VoIP Voice module enables users to personalize computer-based phone conversations by adding their own voices to VoIP Drupal scripts.

--------------------------
Dependencies
1.AudioRecorderField (http://drupal.org/project/audiorecorderfield)
2.Locale (comes with Drupal core but not enabled by default)
3.VoIP Drupal (http://drupal.org/project/voipdrupal)

--------------------------
Installation

1. Extract VoIP Voice to your sites/all/modules directory.
2. Enable the VoIP Voice module in admin/build/modules.
3. To configure the module go to admin/settings/voipvoice

--------------------------
General settings (admin/settings/voipvoice/settings)

In general settings you can configure allowed audio extensions for VoIP voices. Options are mp3 and wav. By default only wav is enabled.

--------------------------
Manage lexicons (admin/settings/voipvoice/lexicons)

A lexicon is considered to be a container for phrases. By default this module comes with "default" lexicon installed.
You can create new lexicon by clicking on Add Lexicon tab. You must select unique name for your lexicon. Description is optional.
Later you can change this info by clicking on settings link of your lexicon in Manage lexicons page.
View phrase link will take you to page that lists all phrases belonging to this lexicon. From that page you can delete individual phrases.
By clicking add phrase link you will be taken to page where you can add new phrases to your lexicon.
To delete your lexicon, click on the link delete. This will prompt you to confirm your choice once more. Note that deleting the lexion also deletes 
all voices and phrases in that lexicon as well as all voice files belonging to those phrases.

--------------------------
Manage VoIP voices (admin/settings/voipvoice/voices)

A VoIP voice is considered to be a container for phrases belonging to a single language. By default this module comes with "log" voice installed.
You can create new voice by clicking on Add Voice tab. You must select unique name for your voice (can not be changed later!), choose the lexicon this voice belongs to, 
choose the language of this voice (to get more languages available you must add them through Drupal languages page: admin/settings/language),
choose the gender of the voice (man, woman or neutral) and description which is optional.
Later you can change this info by clicking on setup link of your voice in Manage VoIP voices page.
To export voice click on export link. This will create export data as well as zipped archive of all voice recordings associated with exporting voice.
To delete the voice click on delete link. Note that this will delete all voice recordings associated with that voice.

--------------------------
Manage VoIP recordings

VoIP recordings are audio files that will be played by VoIP Drupal modules whenever the associated phrase is used. This enables you to record your own
voices instead of using computer generated voice of your VoIP provider.
You can view voice recordings by clicking on recordings link beside your voice in Manage VoIP voices. This will take you to page that lists all 
phrases of that voice together with associated recorded voice file. If the voice file doesn't exist you will have option to record it using 
AudioRecorderField default recorder or to upload your prerecorded file.
Translated phrase and Translate link are available only in voices that have different language than your Drupal default language. First will contain
translated version of the phrase, while the second contains link to Drupal translate interface where you can translate your phrases to the language 
if not already so.
By clicking advanced link, you will go to page containing some advanced information about the voice recording.

--------------------------
Import/Export

You can export voice with all its phrases and recordings. To do that go to Manage VoIP voices page (admin/settings/voipvoice/voices) and click on export link
beside the voice. Copy the export data code and download the voice recordings (optional).

To import the voice in another system go to Import voice page (admin/settings/voipvoice/voices/import) and follow the steps. If there are any name conflicts
in terms of lexicon, voice or phrase the code will merge it. So if both export and import sites are having same lexicon name, the code will consider this as 
update and will add associated voice to that lexicon. Same applies with voices and phrases. Note that the voice recordings will overwrite any existing recording
in importing site.

--------------------------
Usage

To use your newly created voice in VoIP Script simply add this to beggining of your script:
voipvoice_set_current_voice('my-voice-name');

Then whenever you want to read some text use v() function to wrap it:
$script->addSay(v('Welcome to the My Custom Hotline.'));

Optionally you can pass more parameters to v() to do some advanced things like:
Having variable names inserted in between your recording:
v('Welcome to the %mysitename Hotline.', array('%mysitename' => variable_get('sitename', t('Drupal'))));

Or to use different voice then in rest of the script:
v('Welcome to the My Custom Hotline.', NULL, NULL, 'my-other-voice-name');

Note: 
* Drush issues: Don't install this module using Drush utility as it will not create voice folders appopriately.


---
The VoIP Voice module is part of the VoIP Drupal framework.  This module has been originally developed by Tamer Zoubi and Leo Burd under the 
sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).