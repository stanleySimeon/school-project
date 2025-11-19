# this a Dockerfile for building and running the C++ backend server
FROM gcc:12

WORKDIR /app

# this a installer for build dependencies
RUN apt-get update && apt-get install -y \
  make \
  curl \
  && rm -rf /var/lib/apt/lists/*

# this a copier for source files
COPY . .

# this a downloader for JSON library and builder for application
RUN make download_json && make

# this a exposer for port 8080
EXPOSE 8080

# this a runner for server
CMD ["./school_server"]
