FROM gcc:latest

COPY . /usr/src/
WORKDIR /usr/src/

RUN make

CMD ["make run"]

LABEL Name=tetris Version=0.0.1
