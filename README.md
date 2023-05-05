**tau-Lop library** is a tool for automatizing the procedure of 
modeling and quantifying the cost of parallel algorithms using
the tau-Lop analytic communication model.

Version: 1.2
Date: May 4th, 2023

--------------------------------------------------------------------------

## MPIBlib Library 

Description: tau-lop library allows to write code to represent analytic communication models for MPI applications based on the tau-lop model. The library uses model parameter values to solve (quantify) the models. tau-lop library does not include utilities for measuring parameters, and it relies upon other libraries as **mpiblib** (Heterogeneous Computing Laboratory, University College Dublin <https://hcl.ucd.ie/project/mpiblib>) for this task.


Following, the steps to build the **mpiblib** library from the parameter measurement is described:


1) Parameters measurement using MPIBlib.

MPIBLib has been modified to measure tau-lop parameters and to output text files to be incorporated to tau-lop. To install mpiblib library:

1) Install GSL (GNU Scientific Library) and Boost library: both could be instaled with default options.

2) Install a MPI distribution, for example, Open MPI or MPICH.

3) To install mpilib, download modified version (or apply path to the original HCL version) from <https://github.com/hpc-unex/parameters> (please, read the Readme.md file for detailed instructions), decompress and run:

``$ ./configure --with-gsl-dir=/home/jarico/gsl-2.7.1 --with-boost-dir=/home/jarico/boost_1_64_0``

``$ make``

``$ sudo make all install``

Modificationes performed to mpiblib-1.2.0 are mainly for:
1) Updating MPI deprecated calls (MPI_Type_extent and MPI_Type_struct).
2) Measure and print files with tau-lop parameters.

To execute benchmarks and generate taulop parameters, run command similar to:

``$ mpiexec -n 8 --map-by core --bind-to core -report-bindings --display-map  -nooversubscribe ./tools/p2p -b taulop -m 1 -M 1048576 -S 65536 -C SHM -o overhead_SHM.txt -t transfertimes_SHM.txt -H 131072 -c 0.995 -e 0.01 -r 100 -R 1000 -v``

Previous example measures communication parameters in shared memory (*mpiexec* maps by core), using ``p2p``benchmark for taulop parameters (-b), messages sizes from 1 Byte to 1024 KBytes, and specify message segments of 64 KBytes (-s) and threshold for eager to rendezvous protocol change at 128 KBytes (-H). Output files are ``overhead_SHM.txt`` and ``transfertimes_SHM.txt``. Argument -C is only to label the test and -c, -e are level of confidence and error used in mpiblib to perform efficient measurement. Number of repetitions is in the range 100 to 1000 (-r to -R).

Another example to measure parameters in a TCP/Ethernet network is:

``$ mpiexec --mca btl tcp,self -n 16 -hostfile hosts --map-by node --bind-to core -report-bindings --display-map  -nooversubscribe ./tools/p2p -b taulop -S 65536 -C TCP -o overhead_TCP.txt -t transfertime_TCP.txt -sizes sizes.txt -H 131072 -c 0.995 -e 0.01 -r 100 -R 1000 -v``

Text files (-o and -t) generated by *mpilib* should be transformed to the tau-lop format.



--------------------------------------------------------------------------

## tau-lop Library 

Installing **tau-lop library** follows the GNU standard procedure. Download it from <https://github.com/hpc-unex/libtaulop>. 

At this point, if you have a set of parameter files generated by mpiblib you should transform them to the tau-Lop format. The code of tau-Lop library comes with a Python scripting utility to convert files. Just got to the ~/libtaulop/params/transform folder and execute:

``$ python transform_params.py <args>``

You will get taulop ready to use parameter files. Options are:

- Positional Argument:

  channel               Communication Channel. The transformation depends on the communication channel features (SHM, TCP, IB, ARIES, etc.)

- optional arguments:

  -h, --help:            show help message and exit.

  -v, --verbose:         Verbose mode.

  -o OVERHEAD, --overhead OVERHEAD:
                        Overhead input file (default <overhead.txt>).

  -t TRANSFERT, --transfert TRANSFERT:
                        Transfer tiimie input file (default <transfert.txt>)

  -w WRITEFILE, --writefile WRITEFILE:
                        Parameters output file (default <parameters.txt>).

  -p PLOT, --plot PLOT:  Output plot png file (default: no png file.


As well, a ``transform_script.py`` example is included to execute transforms over a set of *mpiblib* output files from different machines and cmomunication channels.


1) To **install** tau-lop library:

``$ ~/libtaulop/configure CXXFLAGS='-O3' --prefix=~/taulop --with-params=~/libtaulop/params/metropolis``

Previous commend configure the tau-lop library (from a different folder) to use the parameter values in the folder ``params/metropolis``. Then,

``$ make``

``$ make install``

``$ make tests``

Last command compile a set of tests for the library, where you can find code examples to start. 


2) tau-Lop model is deeply described in the following **papers**:

- Rico-Gallego, J.A., Díaz-Martín, J.C., Calvo-Jurado, C. et al. Analytical Communication Performance Models as a metric in the partitioning of data-parallel kernels on heterogeneous platforms. J Supercomput 75, 1654–1669 (2019). https://doi.org/10.1007/s11227-018-2724-8

- Rico-Gallego, J.A., Moreno-Álvarez, S., Díaz-Martín, J.C. et al. A tool to assess the communication cost of parallel kernels on heterogeneous platforms. J Supercomput 76, 4629–4644 (2020). https://doi.org/10.1007/s11227-019-02919-1

- J. -A. Rico-Gallego, A. L. Lastovetsky and J. -C. Díaz-Martín, "Model-Based Estimation of the Communication Cost of Hybrid Data-Parallel Applications on Heterogeneous Clusters," in IEEE Transactions on Parallel and Distributed Systems, vol. 28, no. 11, pp. 3215-3228, 1 Nov. 2017, doi: 10.1109/TPDS.2017.2715809.

- Juan-Antonio Rico-Gallego, Juan-Carlos Díaz-Martín, Alexey L. Lastovetsky, Extending τ-Lop to model concurrent MPI communications in multicore clusters, Future Generation Computer Systems, Volume 61, 2016, Pages 66-82, ISSN 0167-739X, https://doi.org/10.1016/j.future.2016.02.021.

- Juan-Antonio Rico-Gallego, Juan-Carlos Díaz-Martín, τ-Lop: Modeling performance of shared memory MPI, Parallel Computing, Volume 46, 2015, Pages 14-31, ISSN 0167-8191, https://doi.org/10.1016/j.parco.2015.02.006.

3) Please, visit <http://hpc.unex.es/taulop> for more information and advanced examples.

**Contacting information:**
- **Juan A. Rico  (<jarico@unex.es>)**
- Juan C. Díaz  (<juancarl@unex.es>)
- Sergio Moreno (<smoreno@unex.es>)

University of Extremadura,
Avd. Universidad s/n,
10004, Cáceres,
Spain

--------------------------------------------------------------------------

## Intel Micro-Benchmarks (IMB) and tau-lop IMB

Intel Micro Benchmarks (IMB) is a benchmark utility to measure the performance of point to point and collective MPI operations (<https://github.com/intel/mpi-benchmarks>). Once installed, a benchmark could be executed as:

``$ mpirun -n $1  --hostfile hosts_p2p --bind-to core  --map-by core -report-bindings --display-map  -nooversubscribe -mca coll_tuned_priority 100 -mca coll_tuned_use_dynamic_rules 1 ./IMB-MPI1  PingPong -off_cache -1 -iter $2 -msglen $3 > metropolis_pingpong_SHM.txt``

to measure a PingPong benchmark in the *shared memory* communication channel and *Open MPI*, and:

``$ mpirun -n $1  --mca opal_common_ucx_opal_mem_hooks 1 --hostfile hosts_p2p --bind-to core  --map-by node -report-bindings --display-map  -nooversubscribe -mca coll_tuned_priority 100 -mca coll_tuned_use_dynamic_rules 1 ./IMB-MPI1  PingPong -off_cache -1 -iter $2 -msglen $3 > metropolis_pingpong_IB.txt``

to run a PingPong benchmark using the Infiniband network using *Open MPI* library.

taulop library provides with an utility to compare outputs from Intel MPI benchmark operations to the estimations made by the library:

1)After installing tau-lop, run: 

``$ make tests``

2) At installation folder you will find ``bin/imb_taulop``. Execute a command like:

``$ ~/imb_taulop -npmin 2 -msglen sizes.txt -input benchmarks.txt -channels channels.txt -machines machines.txt``

Parameters -msglen, -npmin and -input (containing the names of benchmarks to run one per line). The values should be the same as actually measured by IMB.

*-channels* specifies a file with the names of the communication channels (one per line, for instance, SHM, TCP, IB, ARIES, etc.) to compare. 
*-machines* specifies a file with the names (one per line) of the machines (clusters) to use.

**Note: by now, imb_taulop performs a comparison of only one benchmark at a time, for several channels and machines (under development)**.


3) Go to the taulop library ``~/tests/imb/compare`` and execute the Python script with the appropiate files (output from IMB and taulop estimations). It will show (and generate PNG files) to compare estimations and actual values.




