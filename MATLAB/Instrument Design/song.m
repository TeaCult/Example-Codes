clc; clear all;close all;
t=0:1/44100:3;

% s1=0.5*sin(440*pi*t).*1./exp(t);
% s2=0.5*sin(440*2*pi*t+0.1).*1./exp(t);
% s3=s1+s2;
% %sound(s3)
% %plot(s3);
% %sound(s3,44100);
% s4=0.5*sin(440*2*pi*t).*1./exp(5*t);
% s5=0.5*sin(440*2*pi*t+0.4).*1./exp(5*t);
% s6=s4+s5;
% %sound(s6,44100)
% s7=0.5*sin(440*2*pi*t+0.4).*1./exp(5*t);
% s8=0.2*sin(220*2*pi*t+0.4).*1./exp(5*t);
% s9=0.2*sin(880*2*pi*t+0.4).*1./exp(5*t);
% s10=s7+s8+s9;
% %sound(s10,44100);
% sing = [s10 s10];
% sound(sing,44100);
% for i=1:length(t)
%     w(i)=220+0*rand();
%     w2(i)=230;
%     w3(i)=330;
%     omega(i)=0*rand();
% end;
% s11=0.1*sin(w.*2*pi.*t+omega).*1./exp(5*t);

w=440;
s11=0.1*sin(0.1*w*2*pi.*t).*1./exp(2*t);
s12=0.3*sin(0.5*w*2*pi.*t).*1./exp(2*t);
s13=0.5*sin(w*2*pi.*t).*1./exp(2*t);
s14=0.3*sin(1.5*w*2*pi.*t).*1./exp(2*t);
s15=0.1*sin(2*w*2*pi.*t).*1./exp(2*t);
s16=s11+s12+s13+s14+s15;
s16=s16./max(s16).*0.5;
max(s16)
sound(s16,44100)
sound([s11 s12 s13 s14 s15 s16],44100)
