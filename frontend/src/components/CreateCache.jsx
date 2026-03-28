import { useState } from "react";
import { createCache } from "../services/api";

function CreateCache({ onCreated }) {

    const [capacity, setCapacity] = useState("");

    const [message, setMessage] = useState("");

    const handleCreate = async () => {

        try {

            const response =
                await createCache(Number(capacity));

            setMessage(response.data.message);

            onCreated();

        }
        catch(error){

            setMessage("Failed To Create Cache");
        }
    };

    return (

        <div>

            <h2>Create Cache</h2>

            <input
                type="number"
                placeholder="Capacity"
                value={capacity}
                onChange={(e)=>
                    setCapacity(e.target.value)
                }
            />

            <button onClick={handleCreate}>
                Create
            </button>

            <p>{message}</p>

        </div>
    );
}

export default CreateCache;