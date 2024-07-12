FROM ubuntu:20.04
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
RUN make re -C libft
RUN make re

# Set the entrypoint command to run the minishell program
CMD ["./minishell"]
