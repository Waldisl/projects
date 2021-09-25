#!/usr/bin/env bash
sed -i 's/bind-ad/#bind-ad/g' /etc/mysql/mariadb.conf.d/50-server.cnf
sed -i 's/#port/port /g' /etc/mysql/mariadb.conf.d/50-server.cnf
chown -R mysql:mysql /var/lib/mysql
if [ ! -d var/lib/mysql/wp ]; then
	service mysql start
	chmod 755 /var/run/mysqld/mysqld.sock
	mysql -u root -e "CREATE DATABASE IF NOT EXISTS $MDB_NAME"
	mysql -u root -e "CREATE USER IF NOT EXISTS '$MDB_USER'@'%' IDENTIFIED BY '$MDB_PASS'"
	mysql -u root -e "GRANT ALL PRIVILEGES ON $MDB_NAME.* TO '$MDB_USER'@'%'"
	mysql -u root -e "FLUSH PRIVILEGES"
	mysqladmin -u root password $MDB_ROOT_PASS
	service mysql stop
fi
if [ ! -d /var/run/mysqld ]; then
	mkdir /var/run/mysqld
	touch /var/run/mysqld/mysqld.pid
	mkfifo /var/run/mysqld/mysqld.sock
fi
chown -R mysql /var/run/mysqld
exec "$@"