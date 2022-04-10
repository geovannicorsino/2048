FROM gcc:4.9
WORKDIR /app
COPY . .

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install sudo -y

RUN sudo apt-get install libncurses-dev

CMD ["sleep", "infinity"]