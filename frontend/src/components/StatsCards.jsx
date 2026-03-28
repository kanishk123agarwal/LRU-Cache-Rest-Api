function StatsCards({ stats }) {

    if(!stats) return null;

    return (

        <div>

            <h2>Statistics</h2>

            <p>
                Requests :
                {stats.totalRequests}
            </p>

            <p>
                Hits :
                {stats.hits}
            </p>

            <p>
                Misses :
                {stats.misses}
            </p>

            <p>
                Hit Rate :
                {stats.hit_rate}%
            </p>

            <p>
                Evictions :
                {stats.evictions}
            </p>

            <p>Current Size : {stats.size}</p>

            <p>Capacity : {stats.capacity}</p>

        </div>
    );
}

export default StatsCards;