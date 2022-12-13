module solution
  implicit none

contains

  function solve(a, b, c, alpha, beta, gamma)
    integer, intent(in) :: a, b, c, alpha, beta, gamma
    real(kind=16) :: pi = 3.14159265358979323846_16, v(2)
    integer :: solve(4), angle

    v(1) = a * cos(alpha / 180.0 * pi) - b * sin(beta / 180.0 * pi) - c * cos(gamma / 180.0 * pi)
    v(2) = a * sin(alpha / 180.0 * pi) + b * cos(beta / 180.0 * pi) - c * sin(gamma / 180.0 * pi)

    solve(1) = nint(norm2(v))
    angle = atan2(v(2), v(1)) * 180 / pi * 60 * 60
    solve(2) = angle / (60 * 60)
    angle = mod(angle, 60 * 60)
    solve(3) = angle / 60
    angle = mod(angle, 60)
    solve(4) = angle
  end function solve
end module solution
