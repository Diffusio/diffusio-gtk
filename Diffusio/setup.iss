; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{D1AA0990-EAF6-46E8-BB59-E13167289671}
AppName=Diffusio
AppVersion=0.1
;AppVerName=Diffusio 0.1
AppPublisher=Pierre Jacquier & Gr�goire Duvauchelle
AppPublisherURL=http://www.diffusio.co
AppSupportURL=http://www.diffusio.co
AppUpdatesURL=http://www.diffusio.co
DefaultDirName={pf}\Diffusio
DefaultGroupName=Diffusio
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\pierr\Documents\GitHub\diffusio-gtk\Diffusio\diffusio.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\pierr\Documents\GitHub\diffusio-gtk\Diffusio\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Diffusio"; Filename: "{app}\diffusio.exe"
Name: "{commondesktop}\Diffusio"; Filename: "{app}\diffusio.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\diffusio.exe"; Description: "{cm:LaunchProgram,Diffusio}"; Flags: nowait postinstall skipifsilent

