# Cowsay Docker Example
Perhaps the simplest docker example ever.  By executing the following 
commands, you will build a docker container with an entrypoint shell
script.

```bash
 docker build -t test/cowsay-dockerfile .
 docker run test/cowsay-dockerfile "Moo"
 docker run test/cowsay-dockerfile
 ```