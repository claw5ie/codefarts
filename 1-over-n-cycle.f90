module solution
  implicit none
contains
  integer function cycl(n)
    integer, intent(in) :: n
    integer :: i, j

    cycl = -1

    i = 0
    do j = 1, n
       i = mod(i * 10 + 9, n)

       if (i == 0) then
          cycl = j
          exit
       end if
    end do
  end function cycl
end module solution
