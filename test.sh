if [ ! -f hello_world ]
then
    make;
fi

function do_test {
    ./hello_world -n $1 > out;
    while IFS= read line
    do
        if [ ! "$line" == "Hello World!" ]
        then
            echo "Failed with parameter $1";
            return;
        fi
    done < "out"
    echo "Success with parameter $1";
    rm out;
}

do_test 30
do_test 50
do_test 100
do_test 1000
