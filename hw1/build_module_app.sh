CPP_FILES="main.cpp shell_sort.cpp smooth_generator.cpp"
APP=example

if [ -f $APP ]; then rm $APP
fi

g++ $CPP_FILES -o $APP

./$APP
