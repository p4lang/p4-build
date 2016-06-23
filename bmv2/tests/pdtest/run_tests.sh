./pdtest > test.output 2>/dev/null
DIFF=$(diff test.output test.output.ref) 
if [ $? -ne 0 ] 
then
    echo "FAIL!"
    exit 1
else
    echo "PASS!"
    exit 0
fi
