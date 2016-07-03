!Gediz Gursu 030990058 10 haftanin ödevi
program week10
real , dimension(500) :: sayi1,sayi2,sayi3,sayi4,normal1,normal2,normal3,normal4
real :: m1,m2,m3,m4
integer :: i,n,dur
character (len=35) :: fmt_1="Dosyadan alinan degerler......"
character (len=35) :: fmt_2="Normalize edilmis sayiciklar......"
!normalize edilecek sayilarin okunacagi "sayilar.ged" dosyasinin acilmasi
open(unit=5,file="sayilar.ged",status="old",action="read",iostat=dur)
write(unit=6,fmt="(3x,a)") fmt_1 
i=0
do
i=i+1
read(unit=5,fmt=*,iostat=dur) sayi1(i),sayi2(i),sayi3(i),sayi4(i)
if(dur<0)then
exit
end if
!Ekrana dosyadan okunan sayilarin gonderilmesi
write(unit=6,fmt="(7x,f5.2,7x,f4.3,7x,f17.0,7x,f8.3)") sayi1(i),sayi2(i),sayi3(i),sayi4(i)      
end do
n=i-1
close(unit=5,status="keep")
m1=maxval(sayi1)
m2=maxval(sayi2)
m3=maxval(sayi3)
m4=maxval(sayi4)
write(unit=6,fmt="(3x,a)") fmt_2
do i=1,n
normal1(i)=sayi1(i)/m1
normal2(i)=sayi2(i)/m2
normal3(i)=sayi3(i)/m3
normal4(i)=sayi4(i)/m4
!Ekrana normalize edilmis sayilarin gonderilmesi
write(unit=6,fmt="(4(7x,f6.4))")normal1(i),normal2(i),normal3(i),normal4(i)
end do													       
!normalize edilmis sayilari yazmak icin bi dosya acilmasi
open(unit=7,file="normalize.ged",action="write") 
!"normalize.ged" isimli dosyaya normalize edilmis sayilarin kaydedilmesi
do i=1,n
write(unit=7,fmt="(4(3x,f7.4),/)")normal1(i),normal2(i),normal3(i),normal4(i)
end do
end program 