if [ ! -f hello_world ]
then
    make hello_world;
fi

if [ ! -f mp_hello_world ]
then
    make mp_hello_world;
fi

function do_test {
    ./$1 -n $2 > out;
    while IFS= read line
    do
        if [ ! "$line" == "Hello World!" ]
        then
            echo "Failed with parameter $2";
            return;
        fi
    done < "out"
    echo "Success with parameter $2";
    rm out;
}

echo "Testing the standard version."
do_test hello_world 30
do_test hello_world 50
do_test hello_world 100
do_test hello_world 1000

echo "Testing the Message Passing (MP) version."
do_test mp_hello_world 30
do_test mp_hello_world 50
do_test mp_hello_world 100
do_test mp_hello_world 1000
