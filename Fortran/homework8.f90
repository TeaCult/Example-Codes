!Home Work 8 Gediz Gürsu No 030990058
!modifying the module entitled by vectors_3d given in exercise 2 of week 8...
module vectors_3d
public :: vector_product                                     
type, public :: vector
real, dimension(3) :: elements
end type vector
contains
function vector_product(v1, v2) result(p)                    !name of function is changed and applied                                                         
type(vector), intent(in) :: v1, v2                           !to all strings
type(vector) :: p                                            !type of p is changed into a vector
p%elements(1) =  v1%elements(2) * v2%elements(3)-v1%elements(3) * v2%elements(2) ! added line
p%elements(2) =  v1%elements(3) * v2%elements(1)-v1%elements(1) * v2%elements(3) ! added line
p%elements(3) =  v1%elements(1) * v2%elements(2)-v1%elements(2) * v2%elements(1) ! added line
end function vector_product                                  !do loop disabled                      
end module vectors_3d

program test_vectors
use vectors_3d
real :: x1,y1,z1
real :: x2,y2,z2
type(vector) :: a,b,c                                        !a new vector type variable "c" is added
print *,"enter elements of first vector of the form (x1,y1,z1)"
read *, x1,y1,z1
a%elements(1) = x1
a%elements(2) = y1
a%elements(3) = z1
print *,"enter elements of second vector of the form (x1,y1,z1)"
read *, x2,y2,z2
b%elements(1) = x2
b%elements(2) = y2
b%elements(3) = z2
c = vector_product(a, b)                                     !"p" is changed to "c"
print *, "first vector a =(",x1,y1,z1,")"
print *, "second vector b =(",x2,y2,z2,")"
print *, "vector product of axb=",c                          !vector containing new element results is
end program test_vectors                                     !located
