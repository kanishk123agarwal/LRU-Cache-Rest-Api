from threading import Lock
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware
import subprocess
import json
import os

# ------------------------------------------------
# Create FastAPI App
# ------------------------------------------------

app = FastAPI()
command_lock = Lock()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
# ------------------------------------------------
# Start Persistent C++ Cache Process
# ------------------------------------------------

cache_process = subprocess.Popen(
    ["./cache"],
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE,
    text=True,
    bufsize=1
)

# ------------------------------------------------
# Request Models
# ------------------------------------------------

class CreateCacheRequest(BaseModel):
    capacity: int

class PutRequest(BaseModel):
    key: int
    value: int

class BenchmarkRequest(BaseModel):
    operations: int
    workload: str

# ------------------------------------------------
# Helper Function
# ------------------------------------------------

def send_command(command: str):

    with command_lock:

        print("SEND:", command)

        cache_process.stdin.write(command + "\n")
        cache_process.stdin.flush()

        response = cache_process.stdout.readline().strip()

        print("RECV:", response)

        return response

# ------------------------------------------------
# Root Route
# ------------------------------------------------

@app.get("/")
def home():

    return {
        "message": "LRU Cache REST API Running"
    }

# ------------------------------------------------
# API 1 → CREATE CACHE
# ------------------------------------------------

@app.post("/create-cache")
def create_cache(data: CreateCacheRequest):

    response = send_command(
        f"create {data.capacity}"
    )

    return {
        "message": response
    }

# ------------------------------------------------
# API 2 → PUT
# ------------------------------------------------

@app.put("/put")
def put_data(data: PutRequest):

    response = send_command(
        f"put {data.key} {data.value}"
    )

    if response == "Cache Not Initialized":

        raise HTTPException(
            status_code=400,
            detail=response
        )

    return {
        "message": response
    }

# ------------------------------------------------
# API 3 → GET
# ------------------------------------------------

@app.get("/get/{key}")
def get_data(key: int):

    response = send_command(
        f"get {key}"
    )

    if response == "Cache Not Initialized":

        raise HTTPException(
            status_code=400,
            detail=response
        )

    if response == "Key Not Found":

        raise HTTPException(
            status_code=404,
            detail=response
        )

    return {
        "key": key,
        "value": int(response)
    }

# ------------------------------------------------
# API 4 → STATS
# ------------------------------------------------

@app.get("/stats")
def get_stats():

    response = send_command("stats")

    if response == "Cache Not Initialized":

        raise HTTPException(
            status_code=400,
            detail=response
        )

    return json.loads(response)
    
@app.get("/cache-state")
def cache_state():

    response = send_command("state")

    if response == "Cache Not Initialized":
        raise HTTPException(
            status_code=400,
            detail=response
        )

    return {
        "cache": json.loads(response)
    }

@app.get("/workload-results")
def workload_results():

    with open(
        "reports/workload_results.json"
    ) as file:

        return json.load(file)
    
@app.get("/benchmark-results")
def benchmark_results():

    with open(
        "reports/benchmark_results.json",
        "r"
    ) as file:

        return json.load(file)
    
@app.post("/run-benchmark")
def run_benchmark(data: BenchmarkRequest):

    try:

        subprocess.run(
            [
                "./tests/workload_benchmark",
                str(data.operations),
                data.workload
            ],
            check=True
        )

        return {
            "message":
            "Benchmark completed successfully"
        }

    except Exception as e:

        raise HTTPException(
            status_code=500,
            detail=str(e)
        )