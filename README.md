Overview: 

Analyzing the performance impact of data movement in TCP based network I/O on linux.
Three different I/O strategies are implemented and evaluated:
	1.	Two-copy I/O using send() / recv()
	2.	One-copy I/O using sendmsg() with scatter-gather I/O (iovec)
	3.	Zero-copy I/O using sendmsg() with MSG_ZEROCOPY

The implementations are compared across different message sizes and thread counts using Linux performance counters (perf stat). Metrics such as throughput, latency, CPU cycles, branch misses, and context switches are analyzed.


System Requirements
	•	Linux (x86_64)
	•	GCC compiler
	•	Python 3 (for plotting)
	•	perf tool (Linux performance counters)
	•	pthread support

Makefile : this compiles all the programs with a command "make"

commands for running the programs : 

Two-copy : 

./MT24134_Part_A1_Server <threads> <field_size>
./MT24134_Part_A1_Client <duration_seconds> <field_size>

One-copy :

./MT24134_Part_A2_Server <threads> <field_size>
./MT24134_Part_A2_Client <duration_seconds> <field_size>

Zero-copy :

./MT24134_Part_A3_Server <threads> <field_size>
./MT24134_Part_A3_Client <duration_seconds> <field_size>


for performance measurements : 
Ensuring the perf access is enabled by the below commands 

cat /proc/sys/kernel/perf_event_paranoid
sudo sysctl -w kernel.perf_event_paranoid=1

Now, making the script executable : 
chmod +x MT24134_Part_C_RunExperiments.sh
Running it : "./MT24134_Part_C_RunExperiments.sh"
By doing this it : 
	•	Runs all three implementations
	•	Varies message sizes and thread counts
	•	Collects perf stat output
	•	Stores results in CSV files


Plots are generated using hardcoded values :
"python3 MT24134_Part_D_Plots.py"

Observations: 
	•	Throughput increases with message size for all implementations
	•	Zero-copy performs best for large messages
	•	One-copy outperforms two-copy at moderate message sizes
	•	High thread counts introduce contention and reduce performance
	•	Zero-copy has higher setup overhead and is not optimal for small messages

Author : 

SAMYUKTHA CHILAKA - MT24134