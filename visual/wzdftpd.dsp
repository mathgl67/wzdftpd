# Microsoft Developer Studio Project File - Name="wzdftpd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=wzdftpd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wzdftpd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wzdftpd.mak" CFG="wzdftpd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wzdftpd - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "wzdftpd - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wzdftpd - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WZD_MULTITHREAD" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 Release/libwzd.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "wzdftpd - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "DEBUG" /D "_DEBUG" /D "WZD_MULTITHREAD" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Debug/libwzd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "wzdftpd - Win32 Release"
# Name "wzdftpd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\ls.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_ClientThread.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_data.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_init_lex.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_init_lex.l

!IF  "$(CFG)" == "wzdftpd - Win32 Release"

!ELSEIF  "$(CFG)" == "wzdftpd - Win32 Debug"

# Begin Custom Build
InputDir=\HOMEDIR\wzdftpd\src
InputPath=..\src\wzd_init_lex.l
InputName=wzd_init_lex

"$(InputName).l.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	.\flex\Release\flex.exe -o$(InputDir)\$(InputName).c $(InputDir)\$(InputName).l > $(InputDir)\$(InputName).l.c

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\wzd_main.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_perm.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_ratio.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_savecfg.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_ServerThread.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_site.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_site_group.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_site_user.c
# End Source File
# Begin Source File

SOURCE=..\src\wzd_socket.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\ls.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_action.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_ClientThread.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_data.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_hardlimits.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_init.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_opts.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_perm.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_ratio.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_savecfg.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_ServerThread.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_site.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_site_group.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_site_user.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_socket.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_structs.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_tls.h
# End Source File
# Begin Source File

SOURCE=..\src\wzd_types.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\gnu_regex_dist\gnu_regex.lib
# End Source File
# End Target
# End Project