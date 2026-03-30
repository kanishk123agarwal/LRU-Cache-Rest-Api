import { motion } from "framer-motion";

function CacheVisualization({ cache }) {

    if (!Array.isArray(cache)) {
        return null;
    }

    return (

        <div
            className="
            bg-slate-800
            rounded-xl
            p-6
            shadow-lg
            "
        >

            <h2
                className="
                text-xl
                font-semibold
                mb-6
                "
            >
                Cache Visualization
            </h2>

            <div
                className="
                text-sm
                text-slate-400
                mb-4
                "
            >
                Most Recently Used (MRU)
            </div>

            <div
                className="
                flex
                flex-wrap
                items-center
                gap-2
                "
            >

                {
                    cache.length === 0 ? (

                        <div
                            className="
                            text-slate-400
                            "
                        >
                            Cache is empty
                        </div>

                    ) : (

                        cache.map((item, index) => (

                            <div
                                key={item.key}
                                className="
                                flex
                                items-center
                                "
                            >

                                <motion.div
                                    initial={{
                                        scale: 0.8,
                                        opacity: 0
                                    }}
                                    animate={{
                                        scale: 1,
                                        opacity: 1
                                    }}
                                    transition={{
                                        duration: 0.3
                                    }}
                                    className="
                                    bg-cyan-500
                                    text-black
                                    font-bold
                                    rounded-lg
                                    shadow-lg
                                    px-5
                                    py-4
                                    min-w-[100px]
                                    text-center
                                    "
                                >

                                    <div
                                        className="
                                        text-xs
                                        "
                                    >
                                        Key
                                    </div>

                                    <div
                                        className="
                                        text-xl
                                        "
                                    >
                                        {item.key}
                                    </div>

                                    <div
                                        className="
                                        text-xs
                                        mt-2
                                        "
                                    >
                                        Value
                                    </div>

                                    <div>
                                        {item.value}
                                    </div>

                                </motion.div>

                                {
                                    index !== cache.length - 1 && (

                                        <span
                                            className="
                                            text-2xl
                                            text-slate-300
                                            mx-3
                                            "
                                        >
                                            →
                                        </span>

                                    )
                                }

                            </div>

                        ))

                    )
                }

            </div>

            <div
                className="
                text-sm
                text-slate-400
                mt-4
                "
            >
                Least Recently Used (LRU)
            </div>

        </div>

    );
}

export default CacheVisualization;