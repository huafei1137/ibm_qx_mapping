while read p; do
echo $p 
   ./build/ibm_qx_mapping examples/$p output > LLGresults/$p.txt
done < files.txt 


