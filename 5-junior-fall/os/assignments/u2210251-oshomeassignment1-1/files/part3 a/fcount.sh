 #!/bin/bash
echo =================================================
echo -n Enter a filename to find number of characters, words and lines:
read FNAME
cat $FNAME
echo -n No of lines:
wc -l $FNAME
echo -n No of words:
wc -w $FNAME
echo -n No of bytes:
wc -c $FNAME
echo =================================================
