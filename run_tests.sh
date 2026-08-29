
for file in $(find $1 -type f -name *.c); do
    if cc $file $2 -o $file.test $3; then
        $file.test
        rm $file.test
    else
        echo "test $file failed"
    fi
done
