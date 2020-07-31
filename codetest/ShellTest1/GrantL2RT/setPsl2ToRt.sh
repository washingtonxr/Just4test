#! /bin/bash
# Set process's TGID all to RT mode.
process="ps_l2"  #$1
echo "Target app is $process."

tgid=$(pidof $process)
echo "TGID = $tgid"

tid=$(pidstat -t | grep $process | grep -v grep | awk '{print $4}')
for i in $tid
do
	if [ "$i" != "-" ] ; then
		# Force to set TID to RT mode.
		chrt -p 99 $i
		echo "Set TID = $i to RT mode."
	fi
done

echo "Check again."
pidstat -t -p $tgid
pidstat -t -p $tgid -R
echo "Done."

