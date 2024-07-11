# Use an appropriate base image (example: Ubuntu 20.04)
FROM ubuntu:20.04
# Update package list and install necessary tools
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        libc6-dev \
        libreadline-dev \
        git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN git submodule init && git submodule update
RUN make re

# Set the entrypoint command to run the minishell program
CMD ["./minishell"]
