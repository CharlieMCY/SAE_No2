# Microsoft Developer Studio Project File - Name="SAE_No2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SAE_No2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SAE_No2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SAE_No2.mak" CFG="SAE_No2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SAE_No2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SAE_No2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SAE_No2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "D:\matcom45\lib" /I "include" /I "include\vsflex" /I "include\xydcap" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SAE_No2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "D:\matcom45\lib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mclmcrrt.lib libmx.lib libmat.lib mclmcr.lib measureRadius.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SAE_No2 - Win32 Release"
# Name "SAE_No2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGdiCore.cpp
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGdiPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGdiWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGraphCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXMeasureCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\ClutchModel.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\CommSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\CondSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\EditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\FGridCtrlLU.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\font.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\GdipButton.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\InMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\SAE_No2.cpp
# End Source File
# Begin Source File

SOURCE=.\SAE_No2.rc
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\SAE_No2Cmn.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\SAE_No2Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\ScaleSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\SerialPort.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\StaticEx.cpp
# End Source File
# Begin Source File

SOURCE=.\src\other\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsflex\vsflexdatasource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsflex\vsflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsflex\vsflexgridlu.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsflex\vsflexnode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\WaitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgcpp\WaveDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\xydcap\xydcapactivex.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGdiCore.h
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGdidef.h
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGdiPlot.h
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGdiWnd.h
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXGraphCtrl.h
# End Source File
# Begin Source File

SOURCE=.\include\GraphicCMN\AXMeasureCtrl.h
# End Source File
# Begin Source File

SOURCE=.\include\CGdiPlusBitmap.h
# End Source File
# Begin Source File

SOURCE=.\include\ClutchModel.h
# End Source File
# Begin Source File

SOURCE=.\include\CommSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\include\CondSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\include\EditEx.h
# End Source File
# Begin Source File

SOURCE=.\include\FGridCtrlLU.h
# End Source File
# Begin Source File

SOURCE=.\include\FGridDef.h
# End Source File
# Begin Source File

SOURCE=.\include\font.h
# End Source File
# Begin Source File

SOURCE=.\include\GdipButton.h
# End Source File
# Begin Source File

SOURCE=.\include\InMonitor.h
# End Source File
# Begin Source File

SOURCE=.\include\picture.h
# End Source File
# Begin Source File

SOURCE=.\include\resource.h
# End Source File
# Begin Source File

SOURCE=.\include\SAE_No2.h
# End Source File
# Begin Source File

SOURCE=.\include\SAE_No2Cmn.h
# End Source File
# Begin Source File

SOURCE=.\include\SAE_No2defs.h
# End Source File
# Begin Source File

SOURCE=.\include\SAE_No2Dlg.h
# End Source File
# Begin Source File

SOURCE=.\include\ScaleSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\include\SerialPort.h
# End Source File
# Begin Source File

SOURCE=.\include\StaticEx.h
# End Source File
# Begin Source File

SOURCE=.\include\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\include\vsflex\vsflexdatasource.h
# End Source File
# Begin Source File

SOURCE=.\include\vsflex\vsflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\include\vsflex\vsflexgridlu.h
# End Source File
# Begin Source File

SOURCE=.\include\vsflex\vsflexnode.h
# End Source File
# Begin Source File

SOURCE=.\include\WaitDlg.h
# End Source File
# Begin Source File

SOURCE=.\include\WaveDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\include\xydcap\xydcapactivex.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\private.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SAE_No2.ico
# End Source File
# Begin Source File

SOURCE=.\res\SAE_No2.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\LEDA.png
# End Source File
# Begin Source File

SOURCE=.\res\LEDL.png
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section SAE_No2 : {0A1D1AC8-C326-4456-B182-19991520F67D}
# 	2:5:Class:CXYDCapActiveX
# 	2:10:HeaderFile:xydcapactivex.h
# 	2:8:ImplFile:xydcapactivex.cpp
# End Section
# Section SAE_No2 : {1A3CB92F-89C0-44B8-982F-9421A6171BB6}
# 	2:21:DefaultSinkHeaderFile:xydcapactivex.h
# 	2:16:DefaultSinkClass:CXYDCapActiveX
# End Section
