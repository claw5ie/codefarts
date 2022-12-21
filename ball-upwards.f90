module solution
  implicit none

contains
  function maxball(v0) result(res)
    real :: v0, tmax
    real :: lower, upper
    integer :: res

    tmax = v0 * 1000 / (3600 * 2.0 * 0.5 * 9.81)
    lower = int(tmax * 10) / 10.0
    upper = (int(tmax * 10) + 1) / 10.0

    if (abs(tmax - lower) > abs(tmax - upper)) then
       lower = upper
    end if

    res = nint(lower * 10)
  end function maxball
end module solution
