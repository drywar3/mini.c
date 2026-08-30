
for file in $(find ./tests/ -type f -name *.c); do
    echo "====================================================="
    echo "|| $file"
    echo "====================================================="
    if cc $file -Iinclude ./build/libmini.c.a -o $file.test $3; then
        valgrind $file.test
        rm $file.test
    else
        echo "test $file failed"
    fi
    echo
done
