mkdir -p tests/data_fails/detailled
DIR_NAME="tests/data_fails/"
FILE_NAME=data_fail_rate
i=-1
for line in $(cat $DIR_NAME$FILE_NAME.csv)
do
	i=$((i+1))
	if [ $i -eq 0 ]
	then
		continue
	fi
	echo date,exchange_rate > $DIR_NAME"detailled/"$FILE_NAME$i".csv"
	echo $line >> $DIR_NAME"detailled/"$FILE_NAME$i".csv"
done
FILE_NAME=data_fail_date
i=-1
for line in $(cat $DIR_NAME$FILE_NAME.csv)
do
	i=$((i+1))
	if [ $i -eq 0 ]
	then
		continue
	fi
	echo date,exchange_rate > $DIR_NAME"detailled/"$FILE_NAME$i".csv"
	echo $line >> $DIR_NAME"detailled/"$FILE_NAME$i".csv"
done
