# RelatórioRPC

## Dados

* Disciplina: Fundamentos de Sistemas Operacionais
* Professor: Fernando W Cruz
* Alunos:

	* Nome: Arthur Temporim
	* Matr�cula: 14/0016759

	* Nome: �caro Pires
	* Matr�cula: 15/0129815
* Reposit�rio:

	* [GitHub](https://github.com/icaropires/Fundamentos_Sistemas_Operacionais)

## Introdu��o

Este projeto consiste na implementa��o de um exemplo de RPC, a aplica��o aqui descrita � capaz de somar e subtrair 2 n�meros inseridos pelo usu�rio, e por meio do RPC, efetuar a comunica��o entre o **client** e o **server** para efetuar os calculos desejados.

## Descri��o da Solu��o

### Exemplo base

* A primeira parte do projeto consiste em aplicar o exemplo de RPC dado na apostila, para isso foi utilizado 2 VMs com as dependências instaladas. O tutorial abaixo foi usado para configurar o NFS nas VMs:

[Tutorial](http://mpitutorial.com/tutorials/running-an-mpi-cluster-within-a-lan/)

* Depois os passos do enunciado do projeto foram seguidos.

* Houve um problema com o RPC ent�o os seguintes comandos foram usados para solucionar:

`sudo -i service portmap stop`

`sudo -i rpcbind -i -w`

`sudo -i service portmap start`

* Ap�s os passos anteriores os comandos de execu��o do projeto foram feitos.

### Exerc�cio 1

As seguintes mudan�as foram observadas:

1. Os m�todos no calcula_server.c e em outros arquivos que tinham o n�mero **100** agora possuem o n�mero **101** pois este foi o novo n�mero da vers�o.

2. Ap�s gerar o novo bin�rio, e rodar o comando `rpcinfo -p` a seguinte sa�da foi gerada:

```
   program vers proto   port  service
    100000    4   tcp    111  portmapper
    100000    3   tcp    111  portmapper
    100000    2   tcp    111  portmapper
    100000    4   udp    111  portmapper
    100000    3   udp    111  portmapper
    100000    2   udp    111  portmapper
  55555555  100   udp  58402
  55555555  100   tcp  40215
  55555555  101   udp  50283
  55555555  101   tcp  36185
```
� observ�vel que aa nova vers�o est� usando outra porta.

## Conclus�o

A implementa��o do projeto utilizando RPC foi bem mais simples do que o projeto de MPI, mesmo a complexidade dos problemas serem diferentes, foi not�vel que as facilita��es que o RPC traz ajuda na contru��o de aplica��es em que suas "partes" estejam distribu�das.

# Instru��es para execu��o

* Sever:

./calcula_server

* Client

./calcula_client [ip do server] n�1 n�2

