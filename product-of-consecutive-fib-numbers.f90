module solution
  implicit none
  integer, parameter :: int64 = selected_int_kind(16)

  integer(int64), parameter :: zer = 0_int64
  integer(int64), parameter :: one = 1_int64

  public :: productfib

contains

  function productfib(prod) result(ivec)
    integer(int64), intent(in) :: prod
    integer(int64), dimension(3) :: ivec
    integer(int64) :: x, y, z

    x = 0
    y = 1
    z = 1

    do while (x * y < prod)
       x = y
       y = z
       z = x + y
    end do

    ivec = [x, y, one]

    if (x * y /= prod) then
       ivec(3) = zer
    end if
  end function productfib
end module solution
