import { useState } from "react";
import { putValue, getValue } from "../services/api";

function CacheForm({ refresh }) {
  const [putKey, setPutKey] = useState("");
  const [putVal, setPutVal] = useState("");

  const [getKeyState, setGetKeyState] =
    useState("");

  const [message, setMessage] = useState("");

  const handlePut = async () => {
    try {
      await putValue(
        Number(putKey),
        Number(putVal)
      );

      setMessage("Inserted Successfully");

      setPutKey("");
      setPutVal("");

      refresh();
    } catch {
      setMessage("PUT Failed");
    }
  };

  const handleGet = async () => {
    try {
      const response = await getValue(
        Number(getKeyState)
      );

      setMessage(
        `Value = ${response.data.value}`
      );

      setGetKeyState("");
    } catch {
      setMessage("Key Not Found");

      setGetKeyState("");
    } finally {
      refresh();
    }
  };

  return (
    <div
      className="
      grid
      grid-cols-1
      md:grid-cols-2
      gap-6
      "
    >
      <div
        className="
        bg-slate-800
        rounded-xl
        p-6
        shadow-lg
        "
      >
        <h2 className="text-xl font-semibold mb-4">
          PUT Operation
        </h2>

        <div className="flex flex-col gap-3">
          <input
            placeholder="Key"
            value={putKey}
            onChange={(e) =>
              setPutKey(e.target.value)
            }
            className="
            bg-slate-700
            rounded-lg
            p-2
            "
          />

          <input
            placeholder="Value"
            value={putVal}
            onChange={(e) =>
              setPutVal(e.target.value)
            }
            className="
            bg-slate-700
            rounded-lg
            p-2
            "
          />

          <button
            onClick={handlePut}
            className="
            bg-cyan-500
            text-black
            font-bold
            rounded-lg
            p-2
            "
          >
            PUT
          </button>
        </div>
      </div>

      <div
        className="
        bg-slate-800
        rounded-xl
        p-6
        shadow-lg
        "
      >
        <h2 className="text-xl font-semibold mb-4">
          GET Operation
        </h2>

        <div className="flex flex-col gap-3">
          <input
            placeholder="Key"
            value={getKeyState}
            onChange={(e) =>
              setGetKeyState(e.target.value)
            }
            className="
            bg-slate-700
            rounded-lg
            p-2
            "
          />

          <button
            onClick={handleGet}
            className="
            bg-cyan-500
            text-black
            font-bold
            rounded-lg
            p-2
            "
          >
            GET
          </button>

          <p className="text-green-400">
            {message}
          </p>
        </div>
      </div>
    </div>
  );
}

export default CacheForm;