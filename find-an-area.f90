module solution
  use preloaded
  implicit none

contains
  function findarea(points) result(area)
    type(point), intent(in) :: points(:)
    integer :: i
    real(8) :: area

    area = 0

    do i = 2, size(points)
       area = area + (points(i)%y + points(i - 1)%y) / 2 * (points(i)%x - points(i - 1)%x)
    end do
  end function findarea
end module solution
