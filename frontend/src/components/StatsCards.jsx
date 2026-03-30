function StatsCards({ stats }) {
  if (!stats) return null;

  const cards = [
    ["Hits", stats.hits],
    ["Misses", stats.misses],
    ["Hit Rate", `${stats.hit_rate}%`],
    ["Evictions", stats.evictions],
    ["Size", stats.size],
    ["Capacity", stats.capacity],
  ];

  return (
    <div
      className="
      grid
      grid-cols-1
      md:grid-cols-3
      gap-4
      "
    >
      {cards.map(([title, value]) => (
        <div
          key={title}
          className="
          bg-slate-800
          rounded-xl
          p-5
          shadow-lg
          flex
          justify-between
          items-center
          "
        >
          <span className="text-slate-400">
            {title}
          </span>

          <span
            className="
            text-2xl
            font-bold
            "
          >
            {value}
          </span>
        </div>
      ))}
    </div>
  );
}

export default StatsCards;