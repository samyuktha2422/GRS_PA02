import matplotlib.pyplot as plt

msg_sizes = [1024, 4096, 16384, 65536]

two_copy = [824, 3296, 13178, 52751]
one_copy = [810, 3532, 14000, 55000]
zero_copy = [780, 3544, 15000, 57000]

plt.plot(msg_sizes, two_copy, label="Two-Copy")
plt.plot(msg_sizes, one_copy, label="One-Copy")
plt.plot(msg_sizes, zero_copy, label="Zero-Copy")

plt.xlabel("Message Size (bytes)")
plt.ylabel("Throughput")
plt.legend()
plt.savefig("throughput_vs_msgsize.png")
plt.close()

two_copy_lat = [830, 3300, 13200, 52800]
one_copy_lat = [810, 3500, 14050, 55200]
zero_copy_lat = [790, 3600, 15100, 57000]

plt.figure()
plt.plot(msg_sizes, two_copy_lat, label="Two-Copy")
plt.plot(msg_sizes, one_copy_lat, label="One-Copy")
plt.plot(msg_sizes, zero_copy_lat, label="Zero-Copy")
plt.xlabel("Message Size (bytes)")
plt.ylabel("Latency")
plt.legend()
plt.savefig("plot_latency_vs_msgsize.png")
plt.close()


threads = [1, 2, 4, 8]

two_copy_thr_t = [3300, 3400, 3296, 3200]
one_copy_thr_t = [3450, 3600, 3532, 3400]
zero_copy_thr_t = [3500, 3700, 3544, 3450]

plt.figure()
plt.plot(threads, two_copy_thr_t, label="Two-Copy")
plt.plot(threads, one_copy_thr_t, label="One-Copy")
plt.plot(threads, zero_copy_thr_t, label="Zero-Copy")
plt.xlabel("Number of Threads")
plt.ylabel("Throughput")
plt.legend()
plt.savefig("plot_throughput_vs_threads.png")
plt.close()


two_copy_cpb = [1200, 850, 500, 200]
one_copy_cpb = [1100, 700, 420, 180]
zero_copy_cpb = [1000, 650, 380, 150]

plt.figure()
plt.plot(msg_sizes, two_copy_cpb, label="Two-Copy")
plt.plot(msg_sizes, one_copy_cpb, label="One-Copy")
plt.plot(msg_sizes, zero_copy_cpb, label="Zero-Copy")
plt.xlabel("Message Size (bytes)")
plt.ylabel("CPU Cycles per Byte")
plt.legend()
plt.savefig("plot_cycles_per_byte.png")
plt.close()