#define APPNAME "AdventuresofCliche"
#define APPVERSION "0.0.1"
#define GROUPNAME "Dissension"
#define DEFDIR "{userappdata}"

[Setup]
AppName={#APPNAME}
AppVersion={#APPVERSION}
AppVerName={#APPNAME} {#APPVERSION}
WizardStyle=modern
DefaultDirName={#DEFDIR}\{#GROUPNAME}\Cliche
DefaultGroupName=Cliche
UninstallDisplayIcon={app}\cliche.exe
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
Source: "..\resources\font\*"; DestDir: "{app}\res\ttf"; Flags: ignoreversion recursesubdirs
Source: "..\resources\img\*"; DestDir: "{app}\res\img"; Flags: ignoreversion recursesubdirs
Source: "..\resources\audio\*"; DestDir: "{app}\res\aud"; Flags: ignoreversion recursesubdirs
; Source: "..\resources\video\*"; DestDir: "{app}\res\vid"; Flags: ignoreversion recursesubdirs
Source: "..\LICENSE"; DestDir: "{app}"; DestName: "LICENSE";
