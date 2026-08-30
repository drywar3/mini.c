
for file in $(find $1 -type f -name *.c); do
    echo "====================================================="
    echo "|| $file"
    echo "====================================================="
    if cc $file $2 -o $file.test $3; then
        valgrind $file.test
        rm $file.test
    else
        echo "test $file failed"
    fi
    echo
done
