
echo "Timing tests 1-20 (max string size is 10): "
( time sh -c "sed -n 1,10p tests.sh | sh > /dev/null" ) 2>&1 | grep real

echo ""
echo "Timing tests 21-40 (max string size is 100): "
( time sh -c "sed -n 21,40p tests.sh | sh > /dev/null" ) 2>&1 | grep real

echo ""
echo "Timing tests 41-60 (max string size is 1000): "
( time sh -c "sed -n 41,60p tests.sh | sh > /dev/null" ) 2>&1 | grep real

echo ""
echo "Timing tests 61-80 (max string size is 10000): "
( time sh -c "sed -n 61,80p tests.sh | sh > /dev/null" ) 2>&1 | grep real

echo ""
echo "Timing tests 81-100 (max string size is 100000): "
( time sh -c "sed -n 81,100p tests.sh | sh > /dev/null" ) 2>&1 | grep real
