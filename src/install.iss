#define APPNAME "Dissension"
#define APPVERSION "0.0.1"
#define GROUPNAME "Ascension"
#define DEFDIR "{userappdata}"

[Setup]
AppName={#APPNAME}
AppVersion={#APPVERSION}
AppVerName={#APPNAME} {#APPVERSION}
WizardStyle=modern
DefaultDirName={#DEFDIR}\{#GROUPNAME}\{#APPNAME}
DefaultGroupName={#APPNAME}
UninstallDisplayIcon={app}\dissension.exe
OutputDir="..\"
OutputBaseFilename="install"
LicenseFile="..\LICENSE"
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
AppPublisher={#APPVERSION}
PrivilegesRequired=none

[Dirs]
Name: "{app}\saves"
Name: "{app}\res"
Name: "{app}\res\img"
Name: "{app}\res\aud"
Name: "{app}\res\vid"
Name: "{app}\res\ttf"

[Files]
Source: "..\bin\release\*"; DestDir: "{app}";
Source: "..\resources\font\*"; DestDir: "{app}\resources\font"; Flags: ignoreversion recursesubdirs
Source: "..\resources\img\*"; DestDir: "{app}\resources\img"; Flags: ignoreversion recursesubdirs
Source: "..\resources\audio\*"; DestDir: "{app}\resources\audio"; Flags: ignoreversion recursesubdirs
; Source: "..\resources\video\*"; DestDir: "{app}\res\video"; Flags: ignoreversion recursesubdirs
Source: "..\LICENSE"; DestDir: "{app}"; DestName: "LICENSE";
