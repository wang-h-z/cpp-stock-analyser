FROM gcc:latest
WORKDIR /app
COPY backend/ /app/
RUN apt-get update && apt-get install -y cmake libasio-dev && rm -rf /var/lib/apt/lists/*
RUN cmake . && make
CMD ["./app"]
