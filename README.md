# FPGA_design_automation
I. How to compile <br/>
```
$ cd src 
$ make clean
$ make 
$ cd ../bin 
```
II. How to run <br/>
```
$ ./project [../benchmarks/{casename}.arch]  [../benchmarks/{casename}.module]  [../benchmarks/{casename}.net]  [../benchmarks/{casename}.floorplan]
```
E.g. <br/>
```
$ ./project ../benchmarks/case2.arch ../benchmarks/case2.module ./benchmarks/case2.net ../outputs/case2.floorplan 
```
III. How to draw floorplan figures <br/>
```
$ python figure.py [case name without file extension]
```
E.g. <br/>
```
$ python figure.py case1
```
IV. How to verify whether a solutions is valid <br/><br/>

In ```/src/```, enter the command below,
```
$ ../bin/verify [../benchmarks/{casename}.arch]  [../benchmarks/{casename}.module]  [../benchmarks/{casename}.net]  [../benchmarks/{casename}.floorplan]
```
E.g. <br/>
```
$ ../bin/verify ../benchmarks/case2.arch ../benchmarks/case2.module ./benchmarks/case2.net ../outputs/case2.floorplan 
```