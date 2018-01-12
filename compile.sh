NAME="square_sum"
CC="gcc"
ARGS="-Wall -Wextra -Werror -lm"
SRC="*.c"

clear;
if [ $# -ne 1 ]; then
	echo "Wrong number of parameters";
	exit;
fi
if $CC -o $NAME $ARGS $SRC; then
	./$NAME $1;
else
	echo "Compilation Failed";
fi
