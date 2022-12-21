module solution
  implicit none

contains
  integer function find_nb(n)
    integer, parameter :: ikind = selected_int_kind(16)
    integer(ikind), intent(in) :: n
    real :: lower, middle, upper
    logical :: lsign, msign, usign

    lower = 0
    upper = real(n) ** 0.33

    lsign = eval(lower) >= 0
    usign = eval(upper) >= 0

    if (lsign .eqv. usign) then
       find_nb = -1
    else
       do while (upper - lower > 0.05)
          middle = (lower + upper) / 2
          msign = eval(middle) >= 0

          if (lsign .neqv. msign) then
             upper = middle
             usign = msign
          else
             lower = middle
             lsign = msign
          end if
       end do
    end if

    find_nb = nint((lower + upper) / 2)
    if (poly(int(find_nb, ikind)) /= n) then
       find_nb = -1
    end if

  contains
    real function eval(x)
      real, intent(in) :: x
      eval = x * x * (0.25 + x * (0.25 * x + 0.5)) - real(n)
    end function eval

    integer(ikind) function poly(x)
      integer(ikind), intent(in) :: x
      poly = x * x * (1 + x * (x + 2)) / 4
    end function poly

  end function find_nb
end module solution
