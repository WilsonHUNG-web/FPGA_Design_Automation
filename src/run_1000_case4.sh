echo "Run case 4"
echo "HPWL, seed"
for i in {1..100000}
do
   cd ../bin
   #./project ../benchmarks/case1.arch ../benchmarks/case1.module ../benchmarks/case1.net ../outputs/case1.floorplan
#./project ../benchmarks/case2.arch ../benchmarks/case2.module ../benchmarks/case2.net ../outputs/case2.floorplan
    #./project ../benchmarks/case3.arch ../benchmarks/case3.module ../benchmarks/case3.net ../outputs/case3.floorplan
   ./project ../benchmarks/case4.arch ../benchmarks/case4.module ../benchmarks/case4.net ../outputs/case4.floorplan
   # ./project ../benchmarks/case5.arch ../benchmarks/case5.module ../benchmarks/case5.net ../outputs/case5.floorplan
   # ./project ../benchmarks/case6.arch ../benchmarks/case6.module ../benchmarks/case6.net ../outputs/case6.floorplan
   cd ../src
done