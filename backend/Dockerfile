# this a Dockerfile for building and running the C++ backend server
FROM gcc:12

WORKDIR /app

# installer for build dependencies
RUN apt-get update && apt-get install -y \
  make \
  curl \
  && rm -rf /var/lib/apt/lists/*

# copier for source files
COPY . .

# downloader for JSON library and builder for application
RUN make clean || true && make download_json && make

# exposer for port 8080
EXPOSE 8080

# runner for server
CMD ["./school_server"]
