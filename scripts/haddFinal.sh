#dir="/data_CMS/cms/amendola/TestSelections/TT_background/fullyHad"
dir="/data_CMS/cms/amendola/TestSelections/TT_background/fullyLep"
#dir="/data_CMS/cms/amendola/TestSelections/TT_background/semiLep"


cd $dir
hadd -f final_sel.root output_*_sel.root
#i=0
#haddInput=""
#for file in $dir/output_*_sel.root; do  
#    haddInput="hadd -f $dir/final_sel.root $dir/output_"
#    haddInput=$haddInput$i
#    haddInput=$haddInput"_sel.root"
#    i=$(( $i+1 ))
#    $haddInput   
#done
