module Solution
  implicit none
  private
  public :: pofi

contains
  pure function pofi(n)
    integer, intent(in) :: n
    character(:), allocatable :: pofi
    integer :: rem = mod(n, 4)

    if (rem == 0) then
       pofi = '1'
    else if (rem == 1) then
       pofi = '-1'
    else if (rem == 2) then
       pofi = '-i'
    else if (rem == 3) then
       pofi = 'i'
    end if
  end function pofi
end module Solution
