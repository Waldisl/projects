FROM debian:buster

RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get -y install vim nginx openssl php-gd php-xml
COPY nginxn.sh ./
RUN chmod 755 ./nginxn.sh
COPY ./nginx.conf ./
RUN chmod 755 ./nginx.conf
RUN chown -R www-data:www-data /var/www/*
RUN chmod 755 -R /var/www/*
ENTRYPOINT [ "./nginxn.sh" ]
CMD ["nginx", "-g", "daemon off;"]