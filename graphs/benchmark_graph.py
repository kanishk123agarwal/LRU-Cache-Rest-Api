import pandas as pd
import matplotlib.pyplot as plt

# Read CSV
df = pd.read_csv("benchmark_results.csv")

# Create Graph
plt.figure(figsize=(8,5))

plt.plot(
    df["operations"],
    df["time_ms"],
    marker="o"
)

plt.xlabel("Operations")
plt.ylabel("Time (ms)")
plt.title("LRU Cache Scalability Benchmark")

plt.grid(True)

# Save Graph
plt.savefig(
    "reports/operations_vs_time.png",
    bbox_inches="tight"
)

print("Graph Saved Successfully")