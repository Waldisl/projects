FROM debian:buster

RUN apt-get update
RUN apt-get install -y default-mysql-server nginx php php-fpm php-mysql openssl wget

RUN service nginx start && service mysql start && service php7.3-fpm start

COPY ./srcs/start_server.sh /etc
COPY ./autoindex_off.sh /etc
COPY ./autoindex_on.sh /etc
COPY ./srcs/nginx.conf /etc
COPY ./srcs/wp-config.php /var
COPY ./srcs/msunspot.html /var/www

EXPOSE 80
EXPOSE 443

ENTRYPOINT ["bash", "/etc/start_server.sh"]