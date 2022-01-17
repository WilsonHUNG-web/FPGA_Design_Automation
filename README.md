# FPGA_design_automation

This is a floorplaner for FPGA with constraints of fixed-outline and heterogeneous structure of CLBs of height 1 and MUXs of height 3.<br/>
Please firstly refer to file ```./2021 floorplan project.pdf``` for detailed problem description, file formats and specs.<br/>
## I. How to compile <br/>
In ```./src/```, enter the command below to remove the old executable file and compile a new one,
```
$ make clean
$ make 
```
## II. How to run <br/>
In ```./src/```, enter the command below,
```
$ ../bin/project ../benchmarks/{casename}.arch ../benchmarks/{casename}.module ../benchmarks/{casename}.net ../outputs/{casename}.floorplan
```
E.g. <br/>
```
$ ../bin/project ../benchmarks/case2.arch ../benchmarks/case2.module ./benchmarks/case2.net ../outputs/case2.floorplan 
```

## III. How to verify whether a solutions ```{casename}.floorplan``` is valid <br/><br/>
Use the provided executable file ```../bin/verify``` to verify a solution. In ```./src/```, enter the command below,
```
$ ../bin/verify ../benchmarks/{casename}.arch ../benchmarks/{casename}.module ../benchmarks/{casename}.net ../outputs/{casename}.floorplan
```
E.g. <br/>
```
$ ../bin/verify ../benchmarks/case2.arch ../benchmarks/case2.module ./benchmarks/case2.net ../outputs/case2.floorplan 
```
## IV. How to draw floorplan figures <br/>
In ```./python/```, enter the command below,
```
$ python figure.py {casename}
```
E.g. <br/>
```
$ python figure.py case1
```
The figure ```{casename}.png``` will be saved in ```./outputs/```.
