
RUN_VALGRIND="no"

for arg in $@; do
    if [[ $arg == "--valgrind" ]]; then
        RUN_VALGRIND="yes"
    fi
done

for file in $(find ./tests/ -type f -name *.c); do
    echo "====================================================="
    echo "|| $file"
    echo "====================================================="
    if cc $file -Iinclude ./build/libmini.c.a -o $file.test $3; then
        if [[ $RUN_VALGRIND == "yes" ]]; then
            valgrind $file.test
        else
            $file.test
        fi
        rm $file.test
    else
        echo "test $file failed"
    fi
    echo
done
