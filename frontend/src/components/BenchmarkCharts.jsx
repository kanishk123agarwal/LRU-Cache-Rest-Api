import {
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  CartesianGrid,
  ResponsiveContainer,
} from "recharts";

function BenchmarkCharts() {
  const data = [
    { operations: 1000, time: 2 },
    { operations: 10000, time: 15 },
    { operations: 100000, time: 120 },
  ];

  return (
    <div
      className="
      bg-slate-800
      p-6
      rounded-xl
      shadow-lg
      "
    >
      <h2 className="text-xl mb-4">
        Benchmark Results
      </h2>

      <ResponsiveContainer
        width="100%"
        height={350}
      >
        <LineChart data={data}>
          <CartesianGrid />

          <XAxis dataKey="operations" />

          <YAxis />

          <Tooltip />

          <Line
            type="monotone"
            dataKey="time"
          />
        </LineChart>
      </ResponsiveContainer>
    </div>
  );
}

export default BenchmarkCharts;