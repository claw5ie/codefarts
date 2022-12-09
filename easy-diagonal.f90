module solution
  implicit none

contains

  function diagonal(n, p) result(res)
    integer, intent(in) :: n, p
    integer, parameter :: ikind = selected_int_kind(16)
    integer(ikind) :: res
    integer :: i

    res = 1
    do i = 0, p
       res = res * (n - p + 1 + i)
       res = res / (i + 1)
    end do
  end function diagonal
end module solution
