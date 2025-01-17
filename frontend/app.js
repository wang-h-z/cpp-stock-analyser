document.getElementById("stockForm").addEventListener("submit", async function (e) {
    e.preventDefault();
    const stockSymbol = document.getElementById("stockSymbol").value;
    const response = await fetch("http://localhost:8080", {
        method: "POST",
        headers: {
            "Content-Type": "text/plain",
        },
        body: stockSymbol + "\n",
    });
    const result = await response.text();
    document.getElementById("result").innerText = result;
});