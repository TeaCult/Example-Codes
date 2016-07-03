function [] = gg_frf(X,Y,T,shouldtrans)
s=0;
if(shouldtrans==1)
    s=1;
end

[FREQ,AMP1]=gg_fft(T,X,s);
AMP1(1)=0;
[FREQ,AMP2]=gg_fft(T,Y,s);
AMP2(1)=0;
plot(FREQ,AMP2./AMP1);

