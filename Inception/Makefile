start:
	sudo sed -i 's/localhost/msunspot.42.fr/g' /etc/hosts 
	mkdir -p /home/msunspot/data/wp
	mkdir -p /home/msunspot/data/db
	docker-compose -f srcs/docker-compose.yaml up

down:
	docker-compose -f srcs/docker-compose.yaml down

re:
	docker-compose -f srcs/docker-compose.yaml up --build

clean:
	sudo rm -rf /home/msunspot/data/wp/* 
	sudo rm -rf /home/msunspot/data/db/* 
	docker rm $$(docker ps -qa) 
	docker volume rm $$(docker volume ls -q) 
	docker network rm $$(docker network ls -q)

fclean:
	docker rmi $$(docker image ls -q)