!Gediz Gursu 030990058 9.hafta ödevi
program zafhaftadokuz
real, dimension(5) :: reaction_A, reaction_B, reaction_C
real, dimension(3) :: sigma,sapma
! Do loop deðerleri baþlýyor
sigma=0	 
averageA=0			 
averageB=0			 
averageC=0			
!read "(f3.1)",reaction_A
!read "(f3.1)",reaction_B
!read "(f4.1)",reaction_C
reaction_A=(/20.6,31.2,10.9,15.4,12.1/)
reaction_B=(/16.9,20.2,30.7,30.2,30.0/)
reaction_C=(/90.6,100.2,98.7,117.2,88.6/)
!reaksiyon degerleri icin ortalama hesaplarý
do i=1,5
averageA=averageA+reaction_A(i)
averageB=averageB+reaction_B(i)
averageC=averageC+reaction_C(i)
end do
averageA=averageA/5
averageB=averageB/5
averageC=averageC/5
!ortalama hesabinin sonu
!standart sapma formulundeki toplam hesabinin acilimi
do i=1,5
sigma(1)=sigma(1)+(reaction_A(i)-averageA)**2
sigma(2)=sigma(2)+(reaction_B(i)-averageB)**2
sigma(3)=sigma(3)+(reaction_C(i)-averageC)**2
end do
!standart sapmanin son hali kare koku alimi
sapma=SQRT(sigma)
!tablo yazdirma
print "(7x,a,4x,a,4x,a)","Reaksiyon A","Reaksiyon B","Reaksiyon C"
!reaction arraylerini tabloda yazdirma 
do i=1,5
print "(12x,f4.1,10x,f4.1,10x,f5.1)", reaction_A(i), reaction_B(i), reaction_C(i)
end do
print*, "Reaksiyonlarin ortalama degerleri"
print "(11x,f6.2,8x,f6.2,9x,f6.2)",averageA,averageB,averageC
print *,"Standart sapma degerleri"
print "(10x,f9.4,5x,f9.4,6x,f9.5)",sapma(1),sapma(2),sapma(3)
end program zafhaftadokuz
