import { useState } from "react";

import {putValue,getValue} from "../services/api";

function CacheForm({ refresh }) {

    const [putKey, setPutKey] = useState("");
    const [putVal, setPutVal] = useState("");

    const [getKeyState, setGetKeyState] =
        useState("");

    const [message, setMessage] =
        useState("");

    const handlePut = async () => {

        try{

            await putValue(
                Number(putKey),
                Number(putVal)
            );

            setMessage("Inserted");

            refresh();
        }
        catch(error){

            setMessage("PUT Failed");
        }
    };

    const handleGet = async () => {

        try{

            const response =
                await getValue(
                    Number(getKeyState)
                );

            setMessage(
                `Value = ${response.data.value}`
            );

        }
        catch(error){

            setMessage("Key Not Found");
        }
        finally{
            refresh();
        }
    };

    return (

        <div>

            <h2>Cache Operations</h2>

            <input
                placeholder="Key"
                value={putKey}
                onChange={(e)=>
                    setPutKey(e.target.value)
                }
            />

            <input
                placeholder="Value"
                value={putVal}
                onChange={(e)=>
                    setPutVal(e.target.value)
                }
            />

            <button onClick={handlePut}>
                PUT
            </button>

            <br />
            <br />

            <input
                placeholder="Key"
                value={getKeyState}
                onChange={(e)=>
                    setGetKeyState(e.target.value)
                }
            />

            <button onClick={handleGet}>
                GET
            </button>

            <p>{message}</p>

        </div>
    );
}

export default CacheForm;