import { useState } from "react";

import {
    runBenchmark
}
from "../services/api";

function BenchmarkRunner({
    refresh
}) {

    const [operations,setOperations] =
        useState(100000);

    const [workload,setWorkload] =
        useState("read-heavy");

    const [loading,setLoading] =
        useState(false);

    const [message,setMessage] =
        useState("");

    const handleRun = async() => {

        try{

            setLoading(true);

            setMessage(
                "Running benchmark..."
            );

            await runBenchmark(
                operations,
                workload
            );

            await refresh();

            setMessage(
                "Benchmark completed"
            );
        }
        catch(error){

            setMessage(
                "Benchmark failed"
            );
        }
        finally{

            setLoading(false);
        }
    };

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
                Interactive Benchmark
            </h2>

            <div
                className="
                grid
                md:grid-cols-2
                gap-4
                "
            >

                <div>

                    <label>
                        Operations
                    </label>

                    <input
                        type="number"
                        value={operations}
                        onChange={(e)=>
                            setOperations(
                                e.target.value
                            )
                        }
                        className="
                        w-full
                        mt-2
                        p-2
                        rounded-lg
                        bg-slate-700
                        "
                    />

                </div>

                <div>

                    <label>
                        Workload
                    </label>

                    <select
                        value={workload}
                        onChange={(e)=>
                            setWorkload(
                                e.target.value
                            )
                        }
                        className="
                        w-full
                        mt-2
                        p-2
                        rounded-lg
                        bg-slate-700
                        "
                    >

                        <option
                            value="read-heavy"
                        >
                            Read Heavy
                        </option>

                        <option
                            value="mixed"
                        >
                            Mixed
                        </option>

                        <option
                            value="write-heavy"
                        >
                            Write Heavy
                        </option>

                    </select>

                </div>

            </div>

            <button

                onClick={handleRun}

                disabled={loading}

                className="
                mt-6
                bg-cyan-500
                text-black
                px-5
                py-2
                rounded-lg
                font-bold
                "
            >

                {
                    loading
                    ?
                    "Running..."
                    :
                    "Run Benchmark"
                }

            </button>

            <p
                className="
                mt-4
                text-green-400
                "
            >
                {message}
            </p>

        </div>
    );
}

export default BenchmarkRunner;