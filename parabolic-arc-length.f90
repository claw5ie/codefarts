module solution
  implicit none

contains
  function len_curve(n) result(l)
    integer, intent(in) :: n
    integer, parameter :: ikind = selected_real_kind(p=18)
    integer :: i
    real(kind=ikind) :: l, dx, dy

    l = 0
    dx = 1.0 / n

    do i = 1, n
       dy = (i * dx) ** 2 - ((i - 1) * dx) ** 2
       l = l + sqrt(dx ** 2 + dy ** 2)
    end do
  end function len_curve
end module solution
