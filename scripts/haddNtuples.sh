OUTDIRR="TestSelections"
mkdir /data_CMS/cms/amendola/$OUTDIRR/
mkdir /data_CMS/cms/amendola/$OUTDIRR/hadd_ntuples/
touch /data_CMS/cms/amendola/$OUTDIRR/README.txt
echo $AMESSAGE > /data_CMS/cms/amendola/$OUTDIRR/README.txt

BEG=0
END=74
inputfilelistFolder="inputFiles/Files80X_22Giu"
for x in $(seq $BEG $END); do
    inputfilelist=
    len=${#x} 
    if [ $len -eq 1 ]; then
	inputfilelist="$inputfilelistFolder/1_TT_files_00$x"
    elif [ $len -eq 2 ]; then
        inputfilelist="$inputfilelistFolder/1_TT_files_0$x"
    elif [ $len -eq 3 ]; then
        inputfilelist="$inputfilelistFolder/1_TT_files_$x"
    fi
    echo $inputfilelist
    i=0
    while read line; do
	inputfiles[$i]=$line
	#echo ${inputfiles[$i]} 
	i=$(( $i+1 ))
    done <$inputfilelist
    #i=$(( $i-1 ))
    haddInput=""
    haddInput="hadd -f /data_CMS/cms/amendola/$OUTDIRR/hadd_ntuples/total_HTauTauAnalysis_$x.root ${inputfiles[*]}"
    $haddInput
done