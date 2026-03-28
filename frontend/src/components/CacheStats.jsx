function CacheStats({ stats }) {

    if (!stats) return null;

    return (

        <div>

            <h2>Statistics</h2>

            <p>Total Requests: {stats.totalRequests}</p>

            <p>Hits: {stats.hits}</p>

            <p>Misses: {stats.misses}</p>

            <p>Hit Rate: {stats.hit_rate}%</p>

            <p>Evictions: {stats.evictions}</p>

        </div>
    );
}

export default CacheStats;