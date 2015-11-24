; example1.nsi
;
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The installer simply 
; prompts the user asking them where to install, and drops a copy of example1.nsi
; there. 

;--------------------------------

; The name of the installer
Name "ClubCoin Setup"
Caption "ClubCoin cryptocurrency coin setup"

; The file to write
OutFile "clubcoin-setup.exe"

; The default installation directory
InstallDir $PROGRAMFILES\ClubCoin

; Request application privileges for Windows Vista
RequestExecutionLevel admin

Icon "clubcoin.ico"
BrandingText "(c) 2015 ClubCoin Developers"

SetDatablockOptimize on

;--------------------------------

; Pages

Page license
LicenseData "clubcoin-license.rtf"

Page directory
Page instfiles

!define MUI_FINISHPAGE_RUN "$INSTDIR\clubcoin-qt.exe"

UninstPage uninstConfirm
UninstPage instfiles


;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File ..\release\clubcoin-qt.exe
  File libwinpthread-1.dll
  
  ; write uninstall strings
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ClubCoin" "DisplayName" "ClubCoin (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ClubCoin" "UninstallString" '"$INSTDIR\cc-uninst.exe"'
  WriteUninstaller "cc-uninst.exe"
  
  CreateShortcut "$DESKTOP\ClubCoin.lnk" "$INSTDIR\clubcoin-qt.exe"
  
SectionEnd ; end the section

Function .onInstSuccess
  ExecShell open "$DESKTOP\ClubCoin.lnk"
FunctionEnd


;--------------------------------

; Uninstaller

UninstallText "This will uninstall ClubCoin. Hit next to continue."
UninstallIcon "clubcoin.ico"

Section "Uninstall"

  Delete "$DESKTOP\ClubCoin.lnk"
  Delete "$INSTDIR\clubcoin-qt.exe"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\cc-uninst.exe"
  
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ClubCoin"
SectionEnd
