./oftest 2> /dev/null

if  [ $? -eq 0 ]
then
    echo "PASS"
    exit 0
else
    echo "FAIL"
    exit 1
fi
