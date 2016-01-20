make clean
for entry in `ls Sources`; do
    filename=$(echo $entry | cut -f1 -d.)
    ext=$(echo $entry | cut -f2 -d.)
    echo $entry
    echo $ext
    echo $filename
    if [ $ext == "cpp" ]
    then
	make NAME=$filename
    fi
done
