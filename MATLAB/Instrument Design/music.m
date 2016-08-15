function out = music(noteQue)
%To Run function
%%s=struct('note',{'F5';'G5';'C6';'G5';'D5';'S'},'beat',{'1/16';'1/8';'1/16';'1/16';'1/8';'1'});music(s);


%% Buid instrument sound 
imc=[1 4 1 2 10 5 1 1 7 6 1]; %instrument modal coefficients
ipc=[0 .25 .52 .72 1.21 1.45 1.79 2 2.25 2.5 3]; %instrument phase coeffients

fundTone=440; %hz in frequency 
for i = 1:5
    subharmonics(i) = fundTone/(i+1);
    overtones(i) = i*fundTone;
end
w=[subharmonics fundTone overtones];

%ripped piano from GM midi library - predefined
imc=[0.0979442269723713;0.0252157905168951;0.0243248580016378;0.0213070221452342;0.0203879062018315;0.0155254256625059;0.0138000233541889;0.0129541812283203;0.0110599665221740;0.0108402509084310;0.0107560755981841]
ipc=[2.71281016554826;-0.637899062864777;-0.589739030090182;2.80489446270531;-0.418176155174036;-1.70005750715497;2.70238846179140;2.51450154729588;0.348735950180204;0.713969869995008;-2.80472407086906]
w=[293.750796850035;587.501593700070;1762.37457241366;1468.62377556363;293.620588163488;2056.12536926370;293.881005536582;587.371385013523;881.122181863558;2937.24755112725;881.252390550105]

fs=44100; %samplng frequency
dur=2;
t=0:1/fs:dur;
isamp=zeros(1,length(t));
for i=1:10
    temp=imc(i)*sin(w(i)*t*(2*pi)+ipc(i));
isamp=isamp+temp;
end

%fade
isamp=isamp.*exp(-3*t);
%safe
isamp=isamp/max(isamp)*0.5;

A4=isamp;
As4=resample(isamp,466,440);
B4=resample(isamp,494,440);
C5=resample(isamp,523,440);
Cs5=resample(isamp,554,440);
D5=resample(isamp,587,440);
Ds5=resample(isamp,622,440);
E5=resample(isamp,659,440);
F5=resample(isamp,698,440);
Fs5=resample(isamp,739,440);
G5=resample(isamp,783,440);
Gs5=resample(isamp,830,440);
A5=resample(isamp,880,440);
As5=resample(isamp,923,440);
B5=resample(isamp,987,440);
C6=resample(isamp,1046,440);
S=C6.*0;

shift=0;
temp(100)=0;
   for i=1:length(noteQue)
    currentNote=eval(noteQue(i).note);
    L=length(currentNote)*eval(noteQue(i).beat);

    temp((1+shift):shift+L)=currentNote(1:L);
    shift=shift+L;
   end
out=temp;
sound(temp,44100)
end
