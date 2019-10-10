
**4.** Considere um programa em java que usa um banco de dados chave-valor que implementa a interface Map ([https://docs.oracle.com/javase/8/docs/api/java/util/Map.html](https://docs.oracle.com/javase/8/docs/api/java/util/Map.html)). Operações que alteram o estado desse banco (p.ex put e remove) são bastante lentas; uma vez que os dados modificações precisam ser enviados para o disco de maneira síncrona. Operações de leitura são mais rápidas (entretanto, mais lentas que em uma implementação de Map, digamos HashMap, que mantém os dados em memória). Você deve implementar um cache como um Decorator --- em resumo, uma nova implementação de Map que repassa algumas chamadas para o banco de dados Map) ---- para acelerar o desempenho. Essa sua implementação precisa ser thread-safe e não relaxar a consistência da estrutura de dados. Múltiplas threads podem acessar o eu CacheMap. O construtor do seu Map deve receber três parâmetros: 1) uma referência para banco de dados Map, 2) um número inteiro que indica a quantidade máxima de pares chave-valor que podem ser mantidos em memória por sua implementação; e 3) um inteiro que indica o tempo máximo, em segundos, que o banco pode ficar sem ser atualizado. Da interface de Map, implemente os seguintes métodos:
    
 - clear
 -  containsKey
 - get
 - isEmpty
 - put
 - remove(key, object)
 - size


Nessa atividade, utilizamos a coleção HTreeMap como bd do Map, e o Hashmap como a chache da aplicação.


### clear
![clear](https://drive.google.com/uc?export=view&id=1MWaEsW3XI7W5zBavagDM7_69acZgs_mv)

> O método é chamado quando deseja limpar todos os dados, tanto da chache quando do bd.

### containsKey

![contaiskey](https://drive.google.com/uc?export=view&id=1Pk1idrByDloXXdjROrIaIy-1V3Kzbi0_)

>Verifica se a chave existe na cache ou no map.

### get
![get](https://drive.google.com/uc?export=view&id=1cRVBKzwjQvjiqxCtQOwI8rNIzd555y91)

> Ele pega um determinado elemento, verificando primeiro se está na cache e caso não esteja presente ele verifica no bd.


### isEmpty

![isEmpty](https://drive.google.com/uc?export=view&id=1B2iOg-mH2nvjuYM9r4fcS3v_psauQdMt)

> Verifica se a cache e o bd está vazio.


### put
![put](https://drive.google.com/uc?export=view&id=1T6nplsDM46zOIOlfDWP64jUA5bKhZ_6t)

> Método que verifica se a cache já atingiu o limite estabelecido, caso essa condição ocorra ele coloca os elementos da cache para o bd pelo método moveCacheToMap().


![moveCache](https://drive.google.com/uc?export=view&id=1dB2YyXH3g4P3-x91DwDyOxvxvhOyQZ7T)

> Esse método auxiliar é responsável por passar todos os elementos presentes na cache para o bd map. 

### remove(key, object)

![remove](https://drive.google.com/uc?export=view&id=1frMpuLemcUdEhCYQxqVrZ_PT3s1XNNwC)

> Remove o elemento pela chave, caso o elemento estiver presente na cache e no map é removido de ambos os locais ou especificamente em um dos.


### size

![size](https://drive.google.com/uc?export=view&id=12iqtKrbAORxpF4BBkgxtW3i98x7lZu6b)

> Retorna o tamanho do map + cache desconsiderando elementos repetidos (Elementos presentes tanto na cache quando no map só é contabilizado uma única vez)



# Testes

> Para uma verificação do programa, realizamos alguns cenários de teste afim de observar se as condições estabelecidas estão funcionando.


### Testando Time e a CacheMap cheia

>  - Verifica o caso do Time acabar e passar os elementos para o bd
>  - Verifica o caso da CacheMap cheia

![teste1](https://drive.google.com/uc?export=view&id=1vb2Eeq4cDCmWdQO5AROfy8V__GflRY3E)