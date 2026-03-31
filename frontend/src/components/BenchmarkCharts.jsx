import {
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  CartesianGrid,
  ResponsiveContainer,
  BarChart,
  Bar,
} from "recharts";

function BenchmarkCharts({ benchmarkData, workloadData }) {
  return (
    <div
      className="
      bg-slate-800
      p-6
      rounded-xl
      shadow-lg
      space-y-10
      "
    >
      {/* Benchmark Chart */}

      <div>
        <h2
          className="
          text-xl
          font-semibold
          mb-4
          "
        >
          Operations vs Time
        </h2>

        <ResponsiveContainer width="100%" height={350}>
          <LineChart data={benchmarkData}>
            <CartesianGrid />

            <XAxis
              dataKey="operations"
              label={{
                value: "Operations",
                position: "insideBottom",
                offset: -5,
              }}
            />

            <YAxis
              label={{
                value: "Time (ms)",
                angle: -90,
                position: "insideLeft",
              }}
            />

            <Tooltip />

            <Line type="monotone" dataKey="time_ms" />
          </LineChart>
        </ResponsiveContainer>
      </div>

      {/* Workload Chart */}

      <div>
        <h2
          className="
        text-xl
        font-semibold
        mb-6
        "
        >
          Workload Analysis
        </h2>

        {/* Latency */}

        <div className="mb-10">
          <h3 className="mb-3">Latency Comparison</h3>

          <ResponsiveContainer width="100%" height={250}>
            <BarChart data={workloadData}>
              <CartesianGrid />

              <XAxis
                dataKey="workload"
                label={{
                  value: "Workload Type",
                  position: "insideBottom",
                  offset: -5,
                }}
              />

              <YAxis
                label={{
                  value: "Latency (ms)",
                  angle: -90,
                  position: "insideLeft",
                }}
              />
              <Tooltip />

              <Bar dataKey="latency" fill="#06b6d4" />
            </BarChart>
          </ResponsiveContainer>
        </div>

        {/* Hit Rate */}

        <div className="mb-10">
          <h3 className="mb-3">Hit Rate Comparison</h3>

          <ResponsiveContainer width="100%" height={250}>
            <BarChart data={workloadData}>
              <CartesianGrid />

              <XAxis
                dataKey="workload"
                label={{
                  value: "Workload Type",
                  position: "insideBottom",
                  offset: -5,
                }}
              />

              <YAxis
                label={{
                  value: "Hit Rate (%)",
                  angle: -90,
                  position: "insideLeft",
                }}
              />

              <Tooltip />

              <Bar dataKey="hit_rate" fill="#22c55e" />
            </BarChart>
          </ResponsiveContainer>
        </div>

        {/* Throughput */}

        <div>
          <h3 className="mb-3">Throughput Comparison</h3>

          <ResponsiveContainer width="100%" height={250}>
            <BarChart data={workloadData}>
              <CartesianGrid />

              <XAxis
                dataKey="workload"
                label={{
                  value: "Workload Type",
                  position: "insideBottom",
                  offset: -5,
                }}
              />

              <YAxis
                label={{
                  value: "Throughput (ops/sec)",
                  angle: -90,
                  position: "insideLeft",
                }}
              />

              <Tooltip />

              <Bar dataKey="throughput" fill="#f59e0b" />
            </BarChart>
          </ResponsiveContainer>
        </div>
      </div>
    </div>
  );
}

export default BenchmarkCharts;
