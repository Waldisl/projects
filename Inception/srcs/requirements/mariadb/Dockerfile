FROM debian:buster

RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get -y install vim default-mysql-server procps

COPY mysql.sh ./
RUN chmod 755 ./mysql.sh
ENTRYPOINT ["./mysql.sh"]
CMD ["mysqld"]