#include <stdio.h>

char *
human_readable_time(unsigned seconds, char *time)
{
  sprintf(time, "%02i:%02i:%02i", seconds / 3600, seconds / 60 % 60, seconds % 60);

	return time;
}
