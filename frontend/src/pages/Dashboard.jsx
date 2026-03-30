import { useEffect, useState } from "react";

import Navbar from "../components/Navbar";
import CreateCache from "../components/CreateCache";
import CacheForm from "../components/CacheForm";
import StatsCards from "../components/StatsCards";
import CacheVisualization from "../components/CacheVisualization";
import BenchmarkCharts from "../components/BenchmarkCharts";

import {
  getStats,
  getCacheState,
} from "../services/api";

function Dashboard() {
  const [stats, setStats] = useState(null);

  const [cache, setCache] = useState([]);

  const loadData = async () => {
    try {
      const statsResponse =
        await getStats();

      setStats(statsResponse.data);

      const cacheResponse =
        await getCacheState();

      setCache(
        cacheResponse.data.cache
      );
    } catch (error) {
      console.log(error);
    }
  };

  useEffect(() => {
    loadData();
  }, []);

  return (
    <div>
      <Navbar />

      <div
        className="
        max-w-6xl
        mx-auto
        p-6
        space-y-6
        "
      >
        <CreateCache
          onCreated={loadData}
        />

        <CacheForm
          refresh={loadData}
        />

        <StatsCards stats={stats} />

        <CacheVisualization
          cache={cache}
        />

        <BenchmarkCharts />
      </div>
    </div>
  );
}

export default Dashboard;