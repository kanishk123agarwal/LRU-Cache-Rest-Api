function CacheVisualization({ cache }) {

    return (

        <div>

            <h2>MRU → LRU</h2>

            <div
                style={{
                    display:"flex",
                    gap:"10px"
                }}
            >

                {
                    cache.map((item)=>(
                        <div
                            key={item.key}
                            style={{
                                border:"1px solid black",
                                padding:"10px"
                            }}
                        >
                            {item.key}
                        </div>
                    ))
                }

            </div>

        </div>
    );
}

export default CacheVisualization;