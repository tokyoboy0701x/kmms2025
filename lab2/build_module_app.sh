CPP_FILES="main.cpp menu_functions.cpp menu_items.cpp"
APP=example 
FOLDER=bin

mkdir -p $FOLDER
cd $FOLDER

if [ -f $APP ]; then rm $APP
fi

cd ..
g++ $CPP_FILES -o $FOLDER/$APP

./$FOLDER/$APP
