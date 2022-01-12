# FPGA_design_automation

Please firstly refer to file ```./2021 floorplan project.pdf``` for detailed problem description and specs.<br/>
## I. How to compile <br/>
In ```./src/```, enter the command below,
```
$ make clean
$ make 
```
## II. How to run <br/>
In ```./bin/```, enter the command below,
```
$ ./project [../benchmarks/{casename}.arch] [../benchmarks/{casename}.module] [../benchmarks/{casename}.net] [../outputs/{casename}.floorplan]
```
E.g. <br/>
```
$ ./project ../benchmarks/case2.arch ../benchmarks/case2.module ./benchmarks/case2.net ../outputs/case2.floorplan 
```
## III. How to draw floorplan figures <br/>
In ```./python/```, enter the command below,
```
$ python figure.py [case name without file extension]
```
E.g. <br/>
```
$ python figure.py case1
```
## IV. How to verify whether a solutions is valid <br/><br/>
In ```./src/```, enter the command below,
```
$ ../bin/verify [../benchmarks/{casename}.arch] [../benchmarks/{casename}.module] [../benchmarks/{casename}.net] [../outputs/{casename}.floorplan]
```
E.g. <br/>
```
$ ../bin/verify ../benchmarks/case2.arch ../benchmarks/case2.module ./benchmarks/case2.net ../outputs/case2.floorplan 
```