import { useEffect, useState } from "react";

import CreateCache from "../components/CreateCache";
import CacheForm from "../components/CacheForm";
import StatsCards from "../components/StatsCards";
import CacheVisualization from "../components/CacheVisualization";

import { getStats,getCacheState} from "../services/api";

function Dashboard(){

    const [stats,setStats] =
        useState(null);

    const [cache,setCache] =
        useState([]);

    const loadData = async () => {

        try{

            const statsResponse =
                await getStats();

            setStats(
                statsResponse.data
            );

            const cacheResponse =
                await getCacheState();

            setCache(
                cacheResponse.data.cache
            );
        }
        catch(error){

            console.log(error);
        }
    };

    useEffect(()=>{

        loadData();

    },[]);

    return(

        <div>

            <h1>
                LRU Cache Dashboard
            </h1>

            <CreateCache
                onCreated={loadData}
            />

            <CacheForm
                refresh={loadData}
            />

            <StatsCards
                stats={stats}
            />

            <CacheVisualization
                cache={cache}
            />

        </div>
    );
}

export default Dashboard;