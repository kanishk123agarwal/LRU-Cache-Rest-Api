import axios from "axios";

const API = axios.create({
    baseURL: "http://127.0.0.1:8000"
});

export const createCache = (capacity) =>
    API.post("/create-cache", { capacity });

export const putValue = (key, value) =>
    API.put("/put", { key, value });

export const getValue = (key) =>
    API.get(`/get/${key}`);

export const getStats = () =>
    API.get("/stats");

export const getCacheState = () =>
    API.get("/cache-state");