#Region ;**** Directives created by AutoIt3Wrapper_GUI ****
#AutoIt3Wrapper_icon=source java.ico
#AutoIt3Wrapper_outfile=NetCheck.exe
#AutoIt3Wrapper_Compression=4
#AutoIt3Wrapper_UseX64=n
#EndRegion ;**** Directives created by AutoIt3Wrapper_GUI ****
;**** WRITTEN BY GEDIZ GURSU  21-6-2011*****
;*** WOW LOGIN AUTOMATION PROGRAM in AUTOIT ***
#include <WinAPI.au3>
#include <Array.au3>
#include <Date.au3>
#include <WindowsConstants.au3>
#include <gg_WOW_Maintainance.au3>

WOWEnvCheckAndMaintainance()

MsgBox(0, "DO NOT PRESS OK IF VPN HAVE NOT STARTED YET", "Waiting for HMA VPN To Start",200)

	RunWait('"' & @ComSpec & '" /c shutdown /a', '', @SW_HIDE)
	RunWait('"' & @ComSpec & '" /c shutdown /f /r /t 10800', '', @SW_HIDE)

$Connected=True;
while($Connected)
sleep(300);Drastically improves performance -----DONT REMOVE------
$connect = _GetNetworkConnect()
If $connect Then
    ;MsgBox(64, "Connections", $connect)
Else
    MsgBox(48, "Warning", "There is no connection")
			$Connected=False;
			KillFableClones()
			KillWoWandHB()
			RestartIn20Seconds()
EndIf

	$isW=isWorkingTime()
	$isB=isBankingTime()
	$PExB=ProcessExists("FABLE(B).exe")
	$PExW=ProcessExists("FABLE(W).exe")

	If $isW and (not $isB) and (not $PExW) Then
		KillFableClones()
		KillWoWandHB()
		sleep(60)
		Run("D:\WORKBENCH 1\FABLE(W).exe")
		msgBox(0,"","Switching To Workers",10)
	EndIf

	if $isB and (not $isW) and (not $PExB) Then
		KillFableClones()
		KillWoWandHB()
		sleep(60)
		Run("D:\WORKBENCH 1\FABLE(B).exe")
		msgBox(0,"","Switching To Bankers",10)
	Endif

	;Prefer Banking when timetables are crossing

	if $isB and $isW and (not $PExB) Then
		KillFableClones()
		KillWoWandHB()
		sleep(60)
		Run("D:\WORKBENCH 1\FABLE(B).exe")
		msgBox(0,"","Banking Session and Working Session overlaps Running Bankers",10)
	Endif

	If not($isB or $isW) and ($PExB or $PExW) Then
		KillFableClones()
		KillWoWandHB()
		msgBox(0,"","Neither Banking Nor Working Time Standing By",10)
	EndIf

WEnd
;########################################################################
Func isBankingTime()
	$temp1 = _Date_Time_GetLocalTime()
	$localtime = _Date_Time_SystemTimeToTimeStr($temp1)
		If false Then; ($localtime> "08:00:00" And $localtime < "09:00:00") or ($localtime> "13:00:00" And $localtime < "14:00:00")  or  ($localtime> "18:00:00" And $localtime < "19:00:00") or ($localtime> "23:00:00" And $localtime < "24:00:00") Then
			Return true;
		Else
			Return False
		EndIf
EndFunc
;##########################################################################
Func isWorkingTime()
	$temp1 = _Date_Time_GetLocalTime()
	$localtime = _Date_Time_SystemTimeToTimeStr($temp1)
		If True then ;($localtime> "06:00:00" And $localtime < "24:00:00") ;or ($localtime> "0:00:00" And $localtime < "06:00:00")  or ($localtime> "19:00:00" And $localtime < "24:00:00")  Then ;or ($localtime> "00:01:00" And $localtime < "06:00:00")
			Return true;
		Else
			Return False
		EndIf
EndFunc
;##########################################################################
Func KillFableClones()
	RunWait('"' & @ComSpec & '" /c taskkill /F /T /IM FABLE(B).exe', '', @SW_HIDE)
	RunWait('"' & @ComSpec & '" /c taskkill /F /T /IM FABLE(W).exe', '', @SW_HIDE)
EndFunc
;##########################################################################
Func KillWoWandHB()
	RunWait('"' & @ComSpec & '" /c taskkill /F /T /IM wow.exe', '', @SW_HIDE)
	RunWait('"' & @ComSpec & '" /c taskkill /F /T /IM honorbuddy.exe', '', @SW_HIDE)
EndFunc
;##########################################################################
Func RestartIn20Seconds()
	RunWait('"' & @ComSpec & '" /c shutdown /a', '', @SW_HIDE)
	RunWait('"' & @ComSpec & '" /c shutdown /f /r /t 20', '', @SW_HIDE)
EndFunc
;##########################################################################

Func _GetNetworkConnect()
	if @error==0 and (_WinAPI_IsNetworkAlive()) Then
		return("RAS is connected")
	Else
		return("RAS is not connected")
	EndIf

EndFunc
;##########################################################################
Func _WinAPI_IsNetworkAlive() ;Checks only network not internet (WAN)/RAS connection :(

	Local $Ret = DllCall('sensapi.dll', 'int', 'IsNetworkAlive', 'int*', 0)

	If (@error) Or (Not $Ret[0]) Or (_WinAPI_GetLastError()) Then
		Return SetError(1, 0, 0)
	EndIf
	Return $Ret[1]
EndFunc   ;==>_WinAPI_IsNetworkAlive
;##########################################################################

#cs
Func _GetNetworkConnect()
    Local Const $NETWORK_ALIVE_LAN = 0x00000001  ;net card connection
    Local Const $NETWORK_ALIVE_WAN = 0x00000002  ;RAS (internet) connection

    Local $aRet, $iResult

    $aRet = DllCall("sensapi.dll", "int", "IsNetworkAlive", "int*", 0)

	ConsoleWrite($aRet)
	If BitAND($aRet[1], $NETWORK_ALIVE_LAN) Then $iResult &= "LAN connected" & @LF
    If BitAND($aRet[1], $NETWORK_ALIVE_WAN) Then $iResult &= "WAN connected" & @LF


; It may not always be practical for an application to call IsNetworkAlive to determine whether or not a local system is
; disconnected from a LAN, because IsNetworkAlive can be slow, and it may take too much time for the function to detect that
;a local system is disconnected. However, IsNetworkAlive can always identify a WAN connectivity at the moment.


	Return $iResult
EndFunc
#ce
