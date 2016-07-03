;Human Input Mimicing Functions

Func SleepRandomSecs($Secs)
	Sleep($Secs * (900 + Floor(Random(0, 200))))
EndFunc   ;==>SleepRandomSecs
;##########################################################################
Func Wait($var) ;encapsulation
	SleepRandomSecs($var)
EndFunc   ;==>Wait
;##########################################################################
Func WriteLikeHuman($aString)
	For $i = 1 To StringLen($aString) Step 1
		;Changing Stroke Delays
		Opt("SendKeyDelay", 6/$WRITINGSPEED + Floor(Random(0, 14/$WRITINGSPEED))) ;5 milliseconds
		Opt("SendKeyDownDelay", 12/$WRITINGSPEED + Floor(Random(0, 21/$WRITINGSPEED))) ;1 millisecond
		;Mistype
		$isATypo = Floor(Random(0, 35));
		If $isATypo == 32 Then
			SendLikeHuman(String(StringMid($aString, $i - 1, 2)))
			Sleep(270/$WRITINGSPEED+ Floor(Random(0, 162/$WRITINGSPEED)))
			SendLikeHuman("{BACKSPACE}")
			Sleep(20/$WRITINGSPEED + Floor(Random(0, 10/$WRITINGSPEED)))
			SendLikeHuman("{BACKSPACE}")
		EndIf
		;Type key by key
		$keyToSend = StringMid($aString, $i, 1)
		SendLikeHuman(String($keyToSend))

	Next
EndFunc   ;==>WriteLikeHuman
;##########################################################################
Func SendLikeHuman($aString)
	Wait(0.05)
	Send($aString)
EndFunc   ;==>SendLikeHuman
;##########################################################################
;NEEDS TO BE FURTHER DEVELOPED
;##########################################################################
Func MouseMoveLikeHuman($xLocation, $yLocation, $SPEED)
	MouseMove($xLocation + Random(5, 10), $yLocation + Random(5, 10), $SPEED)
	Wait(0.1)
	MouseMove($xLocation, $yLocation, $SPEED)
EndFunc   ;==>MouseMoveLikeHuman
;##########################################################################
Func MouseClickLikeHuman()
EndFunc   ;==>MouseClickLikeHuman