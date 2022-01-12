cd ../bin
echo "case1"
./verifier ../benchmarks/case1.arch ../benchmarks/case1.module ../benchmarks/case1.net ../outputs/case1.floorplan
echo "case2"
./verifier ../benchmarks/case2.arch ../benchmarks/case2.module ../benchmarks/case2.net ../outputs/case2.floorplan
echo "case3"
./verifier ../benchmarks/case3.arch ../benchmarks/case3.module ../benchmarks/case3.net ../outputs/case3.floorplan
echo "case4"
./verifier ../benchmarks/case4.arch ../benchmarks/case4.module ../benchmarks/case4.net ../outputs/case4.floorplan
echo "case5"
./verifier ../benchmarks/case5.arch ../benchmarks/case5.module ../benchmarks/case5.net ../outputs/case5.floorplan
echo "case6"
./verifier ../benchmarks/case6.arch ../benchmarks/case6.module ../benchmarks/case6.net ../outputs/case6.floorplan
cd ../src