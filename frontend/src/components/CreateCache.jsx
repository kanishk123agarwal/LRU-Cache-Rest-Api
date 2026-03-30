import { useState } from "react";
import { createCache } from "../services/api";

function CreateCache({ onCreated }) {
  const [capacity, setCapacity] = useState("");
  const [message, setMessage] = useState("");

  const handleCreate = async () => {
    try {
      const response = await createCache(Number(capacity));

      setMessage(response.data.message);

      setCapacity("");

      onCreated();
    } catch {
      setMessage("Failed To Create Cache");
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
      <h2 className="text-xl font-semibold mb-4">
        Create Cache
      </h2>

      <div className="flex gap-3">
        <input
          type="number"
          placeholder="Capacity"
          value={capacity}
          onChange={(e) => setCapacity(e.target.value)}
          className="
          bg-slate-700
          rounded-lg
          p-2
          "
        />

        <button
          onClick={handleCreate}
          className="
          bg-cyan-500
          text-black
          font-bold
          px-4
          rounded-lg
          "
        >
          Create
        </button>
      </div>

      <p className="mt-3 text-green-400">
        {message}
      </p>
    </div>
  );
}

export default CreateCache;