import { useEffect, useState } from "react";

import Navbar from "../components/Navbar";
import CreateCache from "../components/CreateCache";
import CacheForm from "../components/CacheForm";
import StatsCards from "../components/StatsCards";
import CacheVisualization from "../components/CacheVisualization";
import BenchmarkCharts from "../components/BenchmarkCharts";
import BenchmarkRunner from "../components/BenchmarkRunner";

import {
    getStats,
    getCacheState,
    getBenchmarkResults,
    getWorkloadResults
}
from "../services/api";

function Dashboard() {

    const [stats, setStats] = useState(null);

    const [cache, setCache] = useState([]);

    const [benchmarkData, setBenchmarkData] =
        useState([]);

    const [workloadData, setWorkloadData] =
        useState([]);

    // ---------------------------------
    // Cache Data
    // ---------------------------------

    const loadCacheData = async () => {

        try {

            const statsResponse =
                await getStats();

            setStats(
                statsResponse.data
            );

        }
        catch {

            setStats(null);
        }

        try {

            const cacheResponse =
                await getCacheState();

            setCache(
                cacheResponse.data.cache
            );
        }
        catch {

            setCache([]);
        }
    };

    // ---------------------------------
    // Benchmark Data
    // ---------------------------------

    const loadBenchmarkData = async () => {

        try {

            const benchmarkResponse =
                await getBenchmarkResults();

            setBenchmarkData(
                benchmarkResponse.data
            );

        }
        catch(error){

            console.log(
                "Benchmark Error",
                error
            );
        }

        try {

            const workloadResponse =
                await getWorkloadResults();

            setWorkloadData(
                workloadResponse.data
            );

        }
        catch(error){

            console.log(
                "Workload Error",
                error
            );
        }
    };

    // ---------------------------------
    // Load Everything
    // ---------------------------------

    const loadData = async () => {

        await loadCacheData();

        await loadBenchmarkData();
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
                    onCreated={loadCacheData}
                />

                <CacheForm
                    refresh={loadCacheData}
                />

                <StatsCards
                    stats={stats}
                />

                <CacheVisualization
                    cache={cache}
                />

                <BenchmarkRunner
                    refresh={loadBenchmarkData}
                />

                <BenchmarkCharts
                    benchmarkData={benchmarkData}
                    workloadData={workloadData}
                />

            </div>

        </div>
    );
}

export default Dashboard;