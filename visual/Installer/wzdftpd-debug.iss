; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP
; SCRIPT FILES!



[Setup]

AppName=wzdftpd
AppVerName=wzdftpd debug 0.5cvs-20041004
AppPublisher=pollux
AppPublisherURL=http://www.wzdftpd.net/
AppSupportURL=http://www.wzdftpd.net/
AppUpdatesURL=http://www.wzdftpd.net/
DefaultDirName={pf}\wzdftpd
DefaultGroupName=wzdftpd


OutputBaseFilename=wzdftpd-debug-0.5cvs-20041004
ShowLanguageDialog=yes

[Tasks]

; NOTE: The following entry contains English phrases
; ("Create a desktop icon" and "Additional icons"). You are
; free to translate them into another language if required.

; Name: desktopicon; Description: Create a &desktop icon; GroupDescription: Additional icons:; Flags: unchecked


[Dirs]

Name: "{app}\etc"
Name: "{app}\logs"
Name: "{app}\ftproot"
Name: "{app}\modules"
Name: "{app}\tools"

[Files]

Source: ..\debug\wzdftpd.exe; DestDir: {app}; Flags: ignoreversion
Source: ..\debug\libwzd_core.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\libwzd\debug\libwzd.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\gnu_regex_dist\gnu_regex.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\iconv\bin\libiconv-2.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\openssl\lib\ssleay32.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\openssl\lib\libeay32.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\zlib\zlib1.dll; DestDir: {app}; Flags: ignoreversion
Source: ..\..\src\file_*.txt; DestDir: {app}\etc; Flags: onlyifdoesntexist ignoreversion
Source: ..\..\AUTHORS; DestDir: {app}; Flags: ignoreversion
Source: ..\..\ChangeLog; DestDir: {app}; Flags: ignoreversion
Source: ..\..\COPYING; DestDir: {app}; Flags: ignoreversion
Source: ..\..\INSTALL; DestDir: {app}; Flags: ignoreversion
Source: ..\..\NEWS; DestDir: {app}; Flags: ignoreversion
Source: ..\..\Permissions.ReadMeFirst; DestDir: {app}; Flags: ignoreversion
Source: ..\..\README; DestDir: {app}; Flags: ignoreversion
Source: ..\..\TLS.ReadmeFirst; DestDir: {app}; Flags: ignoreversion
Source: ..\..\wzd_tls.cnf; DestDir: {app}; Flags: onlyifdoesntexist ignoreversion
Source: ..\..\src\wzd.pem; DestDir: {app}; Flags: onlyifdoesntexist ignoreversion

Source: ..\wzd.cfg; DestDir: {app}; Flags: onlyifdoesntexist uninsneveruninstall


Source: ..\backends\plaintext\debug\libwzd_plaintext.dll; DestDir: {app}\backends; Flags: ignoreversion
Source: ..\users; DestDir: {app}; Flags: onlyifdoesntexist uninsneveruninstall

Source: ..\modules\perl\debug\libwzd_perl.dll; DestDir: {app}\modules; Flags: ignoreversion
Source: ..\modules\sfv\debug\libwzd_sfv.dll; DestDir: {app}\modules; Flags: ignoreversion
Source: ..\modules\tcl\debug\libwzd_tcl.dll; DestDir: {app}\modules; Flags: ignoreversion

Source: ..\tools\siteconfig\debug\siteconfig.exe; DestDir: {app}\tools; Flags: ignoreversion
Source: ..\tools\siteuptime\debug\siteuptime.exe; DestDir: {app}\tools; Flags: ignoreversion
Source: ..\tools\sitewho\debug\sitewho.exe; DestDir: {app}\tools; Flags: ignoreversion

;Source: wzdftpd\*; DestDir: {app}; Flags: ignoreversion recursesubdirs

; NOTE: Don't use "Flags: ignoreversion" on any shared system files



[INI]

Filename: {app}\wzdftpd.url; Section: InternetShortcut; Key: URL; String: http://www.wzdftpd.net/



[Icons]

Name: {group}\wzdftpd; Filename: {app}\wzdftpd.exe

; NOTE: The following entry contains an English phrase ("on
; the Web"). You are free to translate it into another
; language if required.

Name: {group}\wzdftpd on the Web; Filename: {app}\wzdftpd.url

; NOTE: The following entry contains an English phrase
; ("Uninstall"). You are free to translate it into another
; language if required.

Name: {group}\Uninstall wzdftpd; Filename: {uninstallexe}

; Name: {userdesktop}\wzdftpd; Filename: {app}\wzdftpd.exe; Tasks: desktopicon



[UninstallDelete]

Type: files; Name: {app}\wzdftpd.url


