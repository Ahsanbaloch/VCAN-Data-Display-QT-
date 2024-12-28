# # FROM gcc:latest

# #set a directory for the app
# WORKDIR /app


# #copy all the files to the container
# COPY . .

# #install depecdencies
# RUN make

# CMD ["./speed_feeder"]


# #docker build -t speed .
# #docker run -it speed

# RUN apt update &&\
#     apt install software-properties-common  build-essential -y &&\
#     add-apt-repository ppa:lely/ppa -y &&\
#     apt update &&\
#     apt install make net-tools iproute2 can-utils kmod liblely-coapp-dev liblely-co-tools python3-dcf-tools libncurses5-dev libncursesw5-dev -y


FROM ubuntu:24.04


RUN apt update &&\
    apt install build-essential -y &&\
    add-apt-repository ppa:lely/ppa -y &&\
    apt update &&\
    apt install make net-tools iproute2 can-utils liblely-coapp-dev liblely-co-tools libncurses5-dev libncursesw5-dev -y

# ADD /scripting/speed_feeder.sh .
ADD . /speed_feeder

WORKDIR /speed_feeder
RUN chmod +x /speed_feeder/scripting/speed_feeder.sh


ENTRYPOINT [ "sh", "/speed_feeder/scripting/speed_feeder.sh" ]