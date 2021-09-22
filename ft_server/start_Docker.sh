#!/bin/bash

docker build -t msun .
docker run --name msun_server -it -p 80:80 -p 443:443 msun