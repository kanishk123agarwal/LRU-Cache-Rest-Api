import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("workload_results.csv")

plt.figure(figsize=(8,5))

plt.bar(
    df["workload"],
    df["time_ms"]
)

plt.xlabel("Workload Type")
plt.ylabel("Time (ms)")
plt.title("LRU Cache Workload Comparison")

plt.grid(True)

plt.savefig(
    "reports/workload_comparison.png",
    bbox_inches="tight"
)

print("Graph Saved Successfully")