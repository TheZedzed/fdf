# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    start.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/16 11:53:04 by azeraoul          #+#    #+#              #
#    Updated: 2021/09/10 11:55:03 by azeraoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

printf "\033[1;31mclean\n\033[0m"
NB_RUN=$(docker ps -aq | wc -l)
NB_IMG=$(docker images -aq | wc -l)

if [[ $NB_RUN != "0" ]]
then
	docker stop $(docker ps -aq)
	docker rm $(docker ps -aq)
	docker system prune
else
	printf "no containers running\n"
fi
if [[ $NB_IMG != "0" ]]
then
	docker rmi $(docker images -aq)
else
	printf "no images\n"
fi

if [[ $1 == "build" ]]
then
	printf "\033[1;33mbuild\n\033[0m"
	docker build -t eval .
	printf "\033[1;32mexec\n\033[0m"
	xhost local:docker
	docker run -e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -it --init --rm --name="eval" eval
fi
