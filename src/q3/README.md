### 3.  (exp) Threads, processos leves. Escreve dois programas em clang. O primeiro, cria N threads e em seguida, executa join para cada um delas. Cada thread deve simplesmente dormir por um tempo (alguns segundos), e em seguida executar thread_exit(0). Faça um segundo programa, equivalente ao anterior, que cria N processos, que dormem por um tempo determinado, e os esperar terminar. Avalie as diferenças de desempenho, tanto em tempo decorrido para executar as operações importantes), quanto no consumo de memória. 
Critérios que serão usados na avaliação:
-   explicação da metodologia experimental
-   corretude dos resultados obtidos
-   discussão dos resultados obtidos

Nesse experimento criamos os scripts _exp.c_ e _exp2.c_, o primeiro é responsável por criar N Threads (parâmetro passado para o script), colocá-las para dormir e executar _thread_exit(0)_, e o segundo é similar ao primeiro, porém, são criados processos no lugar de Threads. O tempo para a criação das Threads e dos processos foi calculado utilizando a função _clock()_ da biblioteca _time.h_.

A execução do experimento foi automatizada através do script _build.sh_, ele executa os experimentos variando N de 100 até 1000 (com um intervalo de 100), salva os dados em um arquivo csv e por fim executa um script em R para a geração do plot. Os resultados são salvos na pasta _/results_. 

De acordo com os resultados obtidos, fica claro que ao aumentar a variável N, o tempo da criação dos processos são bem maiores do que o tempo de criação das Threads. 


# Resultados obtidos

## Memoria 
![tempo](https://drive.google.com/uc?export=view&id=1POh5mhCSllYfB3_HqOIveQHAMxEcfHfH)

A cada 0.1 segundos analisamos quanto de memória o processo está consumindo.

## Tempo
![tempo](https://drive.google.com/uc?export=view&id=1x7Fau0fAUy_VvoQexEqo0CVTNWwefUz1)

Obtivemos os dados a partir da subtração do timestamp final assim que termina de criar menos o inicial antes da criação da thread ou processo e assim pegando esse valor.


## Conclusão

Em memória temos aspectos semelhantes para ambas as estruturas, já se tratando de tempo as threads foram mais custosas. Esses resultados, foi bastante curioso para o experimento e um pouco diferente das expectativas que tínhamos sobre essas estruturas.